/***********************************************************************

FILE:			fcnet.c

DATE:			05 Dec 1

DESCRIPTION:	This program checks networks via ICMP. It is necessary to send
				a known canned query to the relevant ICMP kernel software and
				receive a canned response. Here, we are using the time stamp
				message, thus getting the system time on the host in question
				and in the case of an error, reporting the nature of the
				failure. The algorithm is based on a ping.c type methodology
				which is again based on the general ideas as illustrated by the
				TCP/IP books by W.R. Stevens.
				ie. TCP/IP Illustrated. Volume 1 Chapter 6 specifically.

				Since ping is at our disposal in any case, it was decided that
				a new utility would be of more use as well as acting as a
				trouble-shooting device. So, in a sense this program is nothing
				more than a time stamp gatherer with a fleshed-out error
				reporting scheme.

				Since we are using a raw socket, this program will receive all
				ICMP messages. This governs the design of the receiving part
				of the program. Note that this program will receive its own
				time stamp request if the host destination is the local host. 

AUTHOR:			FC Software Inc.
-----------------------------------------------------------------------
    Copyright (C) 2005, 2007 FCSoftware Inc. 

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

    If you discover a bug or add an enhancement contact us on the
    SIMPL project mailing list. 

-----------------------------------------------------------------------

REVISIONS:
$Log: fcnet.c,v $
Revision 1.2  2007/07/24 20:44:50  bobfcsoft
new contact info

Revision 1.1  2005/12/20 15:31:34  bobfcsoft
initial commit

***********************************************************************/

// application header
#include "fcnet.h"

int main(int argc, char **argv)
{
int icmpSock;
struct sockaddr dest;
struct sockaddr_in *to;
struct hostent *hp;
struct protoent *proto;
char host[MAX_HOST_NAME_LEN];

// initialize various variables as necessary
if (initialize(argc, argv, host) == -1)
	{
	usage();
	exit(-1);
	}

// zero destination message structure
bzero( (char *)&dest, sizeof(struct sockaddr) );

// line up on and fill in socket structure
to = (struct sockaddr_in *)&dest;
to->sin_family = AF_INET;

// try to convert as dotted decimal address, if that fails assume it's a hostname
if ( !inet_aton(host, &(to->sin_addr)) )
	{
	hp = gethostbyname(host);
	if (hp == NULL)
		{
		printf("%s: unknown host %s\n", fn, host);
		exit(-1);
		}
	
	to->sin_family = hp->h_addrtype;
	bcopy(hp->h_addr, (caddr_t)&to->sin_addr, hp->h_length);
	}

// set the protocol type
proto = getprotobyname("icmp");
if (proto == NULL)
	{
	printf("%s: unknown protocol icmp-%s\n", fn, strerror(errno));
	exit(-1);
	}

// set up a raw socket
icmpSock = socket(AF_INET, SOCK_RAW, proto->p_proto);
if ( icmpSock < 0)
	{
	printf("%s: socket error-%s\n", fn, strerror(errno));
	exit(-1);
	}

// we send one request and wait up to timeLimit seconds for a reply
signal(SIGALRM, sigAlrm);
alarm(timeLimit);

// send the time stamp request 
if (sendMsg(icmpSock, &dest) == -1)
	{
	exit(-1);
	}

// receive any responses and process the relevant messages
if (recvMsg(icmpSock) == -1)
	{
	exit(-1);
	}

return(0);
}

/**********************************************************************
FUNCTION:	int initialize(int, char **, char *)	

PURPOSE:	Initialize variables as necessary based on the command line. 

RETURNS:	success:  0
			failure: -1
***********************************************************************/

int initialize(int argc, char **argv, char *host)
{
register int i;

// check command line
if (argc < 2)
	{
	return(-1);
	}

// is the host to be reached
memset(host, 0, 128);

// timeLimit is a global variable measured in seconds
// this is the maximum time allowed to negotiate a remote ICMP call
// TIME_LIMIT is the default macro set in fcnet.h
timeLimit = TIME_LIMIT;

// reportTime is a global variable
// it is boolean 1/0 as flag to report the system time on another host or not
reportTime = 1;

// process command line arguments (if any)
for (i = 1; i <= argc; ++i) 
	{	
	char *p = argv[i];

	if (p == NULL)
		{
		continue;
		}

	if (*p == '-')
		{             
		switch (*++p)
			{
			case 's':
				reportTime = (!reportTime) ? 1 : 0;   
				break;

				if (*++p == 0)

			case 't':
					{
					p++;
					}
				timeLimit = atoi(p); 
				break;

			default:
				printf("%s: bad command line arg `%c'\n", fn, *p);
				return(-1);
			}
		}
	else
		{
		strcpy(host, argv[i]);
		}
	}	

if (strlen(host) == 0)
	{
	printf("%s: no host\n", fn);
	return(-1);
	}

return(0);
}

/**********************************************************************
FUNCTION:	int sendMsg(int, struct sockaddr *)

PURPOSE:	Builds and sends a time stamp request. 

RETURNS:	success:  0
			failure: -1
***********************************************************************/

int sendMsg(int sock, struct sockaddr *dest)
{
const char *fn = "sendMsg";
int	ret;
int cc;
struct icmp	*icp;
struct timeval tvorig;
char out[MAX_SIZE];

// build outgoing time stamp message
icp = (struct icmp *)out;
// message type
icp->icmp_type = ICMP_TSTAMP;
// unnecessary 
icp->icmp_code = 0;
// filled in later when outgoing message has been comosed 
icp->icmp_cksum = 0;	
// sent back and used for checking 
icp->icmp_seq = 12345;
// sent back and used for checking 
icp->icmp_id = getpid();
/*
fill in original timestamp: have to convert tv_sec
from seconds since the Epoch to milliseconds since
midnight, then add in microseconds
*/
gettimeofday(&tvorig, (struct timezone *)NULL);
tsorig = (tvorig.tv_sec % (24 * 60 * 60)) * 1000 + tvorig.tv_usec / 1000;
// this time stamp will be echoed back for comparison
icp->icmp_otime = htonl(tsorig);
// filled in by receiver
icp->icmp_rtime = 0;
// filled in by receiver
icp->icmp_ttime = 0;

// 8 bytes of header, 12 bytes of data
cc = 8 + DATA_LEN;

// compute ICMP checksum
icp->icmp_cksum = getCksum((unsigned short *)icp, cc);

// send message
ret = sendto(sock, (char *)out, cc, 0, dest, sizeof(struct sockaddr));
if (ret < 0)
	{
	printf("%s: sendto error-%s\n", fn, strerror(errno));
	printf("wrote %d chars, ret=%d\n", cc, ret);
	return(-1);
	}

// did we get the whole or the right message?
if (ret != cc)
	{
	printf("tried to write %d chars, wrote %d chars\n", cc, ret);
	return(-1);
	}

return(0);
}

/**********************************************************************
FUNCTION:	int recvMsg(int)

PURPOSE:	Receives and processes incoming messages. 

RETURNS:	success:  0
			failure: -1
***********************************************************************/

int recvMsg(int sock)
{
unsigned msgLen;
char *in;
struct sockaddr_in from;
int ret;
socklen_t fromlen = sizeof(struct sockaddr_in);
int hlen;
struct icmp	*icp;
struct ip *ip;
		
// set the expected message size 
msgLen = DATA_LEN + MAXIP_LEN + MAXICMP_LEN;

in = (unsigned char *)malloc(msgLen);
if (in == NULL)
	{
	printf("%s: malloc error-%s\n", fn, strerror(errno));
	return(-1);
	}

while (1)
	{
	// receive an ICMP message
	ret = recvfrom(sock, (char *)in, msgLen, 0, (struct sockaddr *)&from, &fromlen);
	if (ret < 0)
		{
		if (errno != EINTR)
			{
			printf("%s: receive error-%s\n", fn, strerror(errno));
			return(-1);
			}
					
		continue;
		}

	// check the IP header
	ip = (struct ip *)in;
	hlen = ip->ip_hl << 2;
	if (ret < hlen + ICMP_MINLEN)
		{
		printf("%s: packet too short (%d bytes)\n", fn, ret);
		return(-1);
		}

	// get the ICMP part
	ret -= hlen;
	icp = (struct icmp *)(in + hlen);

	// with a raw ICMP socket we get all ICMP packets that come into the kernel
	if (icp->icmp_type == ICMP_TSTAMPREPLY)
		{
		// reply to original request
		if (hndlTimeStampReply(icp, ret) == -1)
			{
			return(-1);
			}
		}
	// error 
	else if (icp->icmp_type == ICMP_DEST_UNREACH)
		{
		hndlError(icp);
		}
	// all other message types are ignored
	else
		{
		continue;
		}

	return(0);
	}
}

/**********************************************************************
FUNCTION:	int hndlTimeStamp(struct icmp *, int)

PURPOSE:	Processes an incoming time stamp message. 

RETURNS:	success:  0
			failure: -1
***********************************************************************/

int hndlTimeStampReply(struct icmp *icp, int ret)
{
int tsrecv;
// struct timeval tvdelta;
// int tsdiff;a

// check that original time stamp has been correctly echoed back
if (ntohl(icp->icmp_otime) != tsorig)
	{
	printf("originate timestamp not echoed: sent=%u, received=%u\n",
			tsorig, ntohl(icp->icmp_otime));
	return(-1);
	}
	
// is the message the correct size?
if (ret != 20)
	{
	printf("message size=%d not 20\n", ret);
	return(-1);
	}
	
// check that the sequence number has been correctly echoed back
if (icp->icmp_seq != 12345)
	{
	printf("received sequence # %d\n", icp->icmp_seq);
	return(-1);
	}
	
// check that the pid has been correctly echoed back
if (icp->icmp_id != getpid())
	{
	printf("received id %d\n", icp->icmp_id);
	return(-1);
	}

// do we print out the time?
if (reportTime)
	{
	/*
	tsorig and tsrecv are both signed ints.  The icmp_[ort]time
	members in the structure are unsigned, but the max value
	for the #millisec since midnight is (24*60*60*1000 - 1)
	or 85,399,999, which easily fits into a signed long.
	We want them signed to compute a signed difference.
	*/
	tsrecv = ntohl(icp->icmp_rtime);
	printf("%s: orig=%d, recv=%d\n", fn, tsorig, tsrecv);

	/*
	// difference in millisec
	tsdiff = tsrecv - tsorig;
	printf("%s: adjustment=%d ms\n", fn, tsdiff);
	// normally 0 
	tvdelta.tv_sec  = tsdiff / 1000;
	tvdelta.tv_usec = (tsdiff % 1000) * 1000;
	
	printf("%s: correction = %ld sec, %ld usec\n",
			fn, tvdelta.tv_sec, tvdelta.tv_usec);

	At this point you may want to adjust the local time clock
	if (adjtime(&tvdelta, (struct timeval *) 0) < 0)
		{
		printf("%s: adjtime error-%s\n", fn, strerror(errno));
		return-1);
		}
	*/
	}
else
	{
	printf("%s: successful line of communication\n", fn);
	}

return(0);
}

/**********************************************************************
FUNCTION:	int hndlError(struct icmp *)

PURPOSE:	Display the relevant error in case of problems. 

RETURNS:	success:  0
			failure: -1
***********************************************************************/

int hndlError(struct icmp *icp)
{
switch (icp->icmp_code)
	{
	// network unreachable
	case ICMP_NET_UNREACH:
		printf("%s: network unreachable ... no route to host.\n", fn);
		break;

	// host unreachable
	case  ICMP_HOST_UNREACH:
		printf("%s: host unreachable ... no route to host.\n", fn);
		break;

	// protocol unreachable
	case  ICMP_PROT_UNREACH:
		printf("%s: protocol unreachable ... connection refused.\n", fn);
		break;
		
	// port unreachable
	case  ICMP_PORT_UNREACH:
		printf("%s: port unreachable ... connection refused.\n", fn);
		break;

	// fragmentation needed but DF bit set
	case ICMP_FRAG_NEEDED:
		printf("%s: fragmentation needed but DF bit set ... message too long.\n", fn);
		break;
	
	// source route failed
	case ICMP_SR_FAILED:
		printf("%s: source route failed ... no route to host.\n", fn);
		break;
	
	// destination network unknown
	case ICMP_NET_UNKNOWN:
		printf("%s: destination network unknown ... no route to host.\n", fn);
		break;
	
	// destination host unknown
	case ICMP_HOST_UNKNOWN:
		printf("%s: destination host unknown ... no route to host.\n", fn);
		break;
	
	// source host obsolete
	case ICMP_HOST_ISOLATED:
		printf("%s: source host obsolete ... no route to host.\n", fn);
		break;
	
	// destination network administratively prohibited
	case ICMP_NET_ANO:
		printf("%s: destination network administratively prohibited ... no route to host.\n", fn);
		break;
	
	// destination host administratively prohibited
	case ICMP_HOST_ANO:
		printf("%s: destination host administratively prohibited ... no route to host.\n", fn);
		break;
	
	// network unechable for TOS
	case ICMP_NET_UNR_TOS:
		printf("%s: network unreachable for TOS ... no route to host.\n", fn);
		break;
	
	// host unreachable for TOS
	case  ICMP_HOST_UNR_TOS:
		printf("%s: host unreachable for TOS ... no route to host.\n", fn);
		break;
	
	// communication administratively prohibited
	case ICMP_PKT_FILTERED:
		printf("%s: communication administratively prohibited.\n", fn);
		break;
	
	// host precedence violation
	case ICMP_PREC_VIOLATION:
		printf("%s: host precedence violation.\n", fn);
		break;
	
	// precedence cutoff in effect
		case ICMP_PREC_CUTOFF:
		printf("%s: precedence cutoff in effect.\n", fn);
		break;
	
	default:
		printf("%s: unknown error code=%u\n", fn, icp->icmp_code);
	}

return(0);
}

/**********************************************************************
FUNCTION:	unsigned short getCksum(unsigned short *, int)

PURPOSE:	Calculate the required cksum for the ICMP message header. 

RETURNS:	the calculated cksum
***********************************************************************/

unsigned short getCksum(unsigned short *addr, int len)
{
unsigned short *w = addr;
int nleft = len;
unsigned short answer;
int sum = 0;

/*
Our algorithm is simple, using a 32 bit accumulator (sum),
we add sequential 16 bit words to it, and at the end, fold
back all the carry bits from the top 16 bits into the lower
16 bits.
*/
while (nleft > 1)
	{
	sum += *w++;
	nleft -= 2;
	}

// mop up an odd byte, if necessary
if (nleft == 1)
	{
	*(unsigned char *)(&answer) = *(unsigned char *)w ;
	sum += answer;
	}

// add back carry outs from top 16 bits to low 16 bits; add hi 16 to low 16
sum = (sum >> 16) + (sum & 0xffff);
// add carry 
sum += (sum >> 16);
// truncate to 16 bits
answer = ~sum;
	
return(answer);
}

/**********************************************************************
FUNCTION:	void sigAlrm(int)

PURPOSE:	Provide a time out for this program. 

RETURNS:	nothing
***********************************************************************/

void sigAlrm(int signo)
{
printf("%s: Timed out ... exiting.\n", fn);
exit(0);
}

/**********************************************************************
FUNCTION:	void usage(void)

PURPOSE:	Display fcnet progarm usage. 

RETURNS:	nothing
***********************************************************************/

void usage()
{
printf("Usage: fcnet -t timeout -s y/n hostname\n");
printf("-t timeout is length of time in seconds to give up on reply message\n");
printf("-s toggles the report kernel time on or off depending on the default\n");
printf("hostname is either a name or an ip address\n");
}

