/*************************************************************

FILE:		logmasker.c

DESCRIPTION:	
This program is an example of a utility process 
used for sending logmask messages to a SIMPL enable app.

AUTHOR:			R.D. Findlay

-------------------------
FCsoftware Inc. 1999, 2002

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

If you discover a bug or add an enhancement 
contact us on the SIMPL project mailing list. 

-------------------------

Revision history:
=======================================================
$Log: logmasker.c,v $
Revision 1.1  2007/07/24 20:57:54  bobfcsoft
new file

=======================================================

*************************************************************/
#include <stdio.h>
#include <stdlib.h>  // atoi
#include <unistd.h>
#include <time.h> // select stuff

#include "receiverMsgs.h"  // FC_SET_LOG_MASK stuff
#define _ALLOC
#include "logmasker.h"
#undef _ALLOC

/*  Prototypes  */
#include "logmaskerProto.h"
#include "simplProto.h"
#include "loggerProto.h"
#include "simplmiscProto.h"   //atoh etc.

/*==============================================
	main - entry point
==============================================*/
void main(int argc, char **argv)
{
static char *fn="logmasker";
int n;
int maxfd;
char *p;
int x_it=0;

p=data;

initialize(argc,argv);
maxfd=my_fds[0];

printf("=============================================\n");
printf(" logmasker - send messages to change log mask\n");
printf(" current recipient is <%s>\n",toName);
printf("\n");

while(!x_it)
	{
	printf("Enter command: ");
	fflush(stdout);

	inset = watchset;
	select(maxfd+1, &inset, NULL, NULL, NULL);

// check which file descriptors are ready to be read from

// Is this from keyboard
	if(FD_ISSET(my_fds[0], &inset))  // keyboard is ready
		{
		n=read(my_fds[0],p,80);
		p[n-1]=0; // remove CR

		fcLogx(__FILE__, fn,
			globalMask,
			LOGMASKER_MARK,
			"%d bytes recd str=<%s>",n,p);

		switch(data[0])
			{
			case '?':  // help
				showUsage();
				break;

			case 'm':  // set new log mask
				{
				FC_SET_LOG_MASK_MSG *sMsg;
				int newMask;

				newMask = atoh(&p[2]);

				fcLogx(__FILE__, fn,
					globalMask,
					LOGMASKER_MARK,
					"new log mask=%X", newMask);

				sMsg = (FC_SET_LOG_MASK_MSG *)outArea;

				sMsg->token= FC_SET_LOG_MASK;
				sMsg->logMask= newMask;

				Send(toPid, outArea, inArea, sizeof(FC_SET_LOG_MASK_MSG), MAX_MSG_BUFFER_SIZE);
				}
				break;
			
			case 'r':	// reset recipient name
				{
				sprintf(toName,"%.19s",&p[2]);

				toPid=name_locate(toName);

				fcLogx(__FILE__, fn,
					globalMask,
					LOGMASKER_MARK,
					"new recipient=<%s> id=%d",
					toName,
					toPid);

				if(toPid == -1)
					{
					printf("unable to find recipient <%s>\n",toName);
					x_it=1;
					}
				else	
					printf("new recipient is <%s>\n",toName);
				}
				break;

			case 'q':	// quit
				x_it=1;
				break;

			default:
				break;
			} // end switch
		}
	} // end for

fcLogx(__FILE__, fn,
	globalMask,
	LOGMASKER_MARK,
	"done");

name_detach();

} // end main

/*==================================================
	showUsage - entry point
==================================================*/
void showUsage()
{
printf("m <mask> - set new log mask\n");
printf("r <name> - reconnect to a new recipient\n");
printf("q(uit)  - exit the logmasker process\n");
} // end showUsage
