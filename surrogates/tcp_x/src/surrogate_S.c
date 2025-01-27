/***********************************************************************

FILE:			surrogate_S.c

DATE:			05 Oct 31

DESCRIPTION:	This program runs as a fork from surrogate.c
 
NOTES:			surrogate_S (parent) receives the following messages:
				1. SUR_NAME_LOCATE_TEXT_MSG/SUR_NAME_LOCATE_MSG

-----------------------------------------------------------------------
    Copyright (C) 2005 FCSoftware Inc. 

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

    If you discover a bug or add an enhancement here's how to reach us: 

	fcsoft@allstream.net
-----------------------------------------------------------------------

REVISIONS:
$Log: surrogate_S.c,v $
Revision 1.4  2006/01/10 15:32:22  bobfcsoft
v3.0 changes

***********************************************************************/

// application header
#define _ALLOC extern
#include "surrogate.h"
#undef _ALLOC

/**********************************************************************
FUNCTION:	surrogate_S()

PURPOSE:	Acts as a receiver for remote name locate messages.

RETURNS:	void
**********************************************************************/	

void surrogate_S()
{
// surSock is global
// dupSock is global
// a_port is global
// rserver is global
// sock_len is global
// memArea is global
// rFp is global;
// wrFp is global;
char *me = SURROGATE_TCP_S_PARENT;
int fds[1];
fd_set watchset; 
fd_set inset; 
int sock;
int token;
pid_t childPid;

#ifdef SUR_CHR	/********** char message **********/
	const static int hdrSize = sizeof(SUR_MSG_CHR_HDR);
	SUR_MSG_CHR_HDR *msg;
#else			/********** binary message **********/
	const static int hdrSize = sizeof(SUR_MSG_HDR);
	SUR_MSG_HDR *msg;
#endif 

// make socket for receiving SUR_NAME_LOCATE queries
sock = initRsock(a_port);
if (sock == -1)
	{
	_simpl_log("%s: socket creation error on port=%d\n", me, a_port);
	exit(-1);
	}

// global message memory for parent, set to largest message encountered
if (adjustMemory(sizeof(SUR_NAME_LOCATE_MSG)) == -1)
	{
	_simpl_log("%s: memory allocation error-%s\n", me, strerror(errno));
	exit(-1);
	}

// arm select for TCP connections
fds[0] = sock;
FD_ZERO(&watchset);
FD_SET(fds[0], &watchset);

while (1)
	{
	// reset inset every time
	inset = watchset;

	if (select(fds[0] + 1, &inset, NULL, NULL, NULL) < 0)
		{
		_simpl_log("%s: select error-%s\n", me, strerror(errno));
		continue;
		}	

	// socket message from an external surrogate
	// accept this connection
	surSock = accept(sock, (struct sockaddr *)&rserver, &sock_len);
	if (surSock < 0)
		{
		_simpl_log("%s: accept error-%s\n", me, strerror(errno));
		exit(-1);
		}
	
	#ifdef BUFFERED
		// open a file pointer for reading alone
		rFp = fdopen(surSock, "r");
		if (rFp == NULL)
			{
			_simpl_log("%s: rFp error-%s\n", me, strerror(errno));
			exit(-1);
			}
	
		// make a duplicate of surSock
		dupSock = dup(surSock);
	
		// open a file pointer for writing alone
		wFp = fdopen(dupSock, "w");
		if (wFp == NULL)
			{
			_simpl_log("%s: wFp error-%s\n", me, strerror(errno));
			exit(-1);
			}

		/*
		At his point you may want to augment the file stream functionality with 
		calls to setbuf(), setbuffer(), setlinebuf() or setvbuf() with modes
		such as _IOFBF, _IOLBF or _IONBF. For _IONBF (no buffering) you will not
		need a call to fflush() after fwrite() for example. fflush() is merely a
		call to the more primitive write() system call.
		*/
	#endif
		
	// read the message header
	if (surRead(memArea, hdrSize) == -1)
		{
		_simpl_log("%s: read error on header-%s\n", me, strerror(errno));
		exit(-1);;
		}
		
	// interpret message header
	#ifdef SUR_CHR	/********** char message **********/
		msg = (SUR_MSG_CHR_HDR *)memArea;
		token = stobSI(msg->token, intWidth);
	#else			/********** binary message **********/
		msg = (SUR_MSG_HDR *)memArea;
		token = msg->token;
	#endif

	if (token == SUR_NAME_LOCATE)
		{
		// fork child (surrogate) to handle messaging
		childPid = fork();
		if (childPid < 0) // forking failure
			{
			_simpl_log("%s: fork error-%s\n", me, strerror(errno));
			nameLocateReply(-1);
			}
		else if (childPid == 0) // child
			{
			// child does not need this socket
			close(sock);
			surrogate_s();
			}
		}
	else
		{
		_simpl_log("%s: unknown msg token=%d\n", me, token);
		}

	// parent does not need these
	#ifdef BUFFERED
		fclose(rFp);
		fclose(wFp);
		close(dupSock);
	#endif
	close(surSock);

	// check for zombie children
	killZombies();
	}
}
