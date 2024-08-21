/*************************************************************

FILE:		receiver.c

DESCRIPTION:	
This program is an example of a SIMPL enabled receiver module. 

AUTHOR:			R.D. Findlay

-------------------------
FCsoftware Inc. 1999, 2002, 2007

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
$Log: receiver.c,v $
Revision 1.1  2007/07/24 20:57:54  bobfcsoft
new file

=======================================================

*************************************************************/
#include <stdio.h>
#include <unistd.h>

#include "receiverMsgs.h"
#define _ALLOC
#include "receiver.h"
#undef _ALLOC

#include "receiverProto.h"
#include "loggerProto.h"
#include "simplProto.h"

/*=========================================================
	main - entry point
=========================================================*/
void main(int argc, char **argv)
{
static char *fn="receiver";
int x_it=0;
int nbytes;			
char *sender;

// parse the command line args
initialize(argc, argv);

fcLogx(__FILE__, fn,
	globalMask,
	RECV_FUNC_IO,
	"ding");

while(!x_it)
	{
	nbytes = Receive(&sender, inArea, MAX_MSG_BUFFER_SIZE);

// send back a NULL reply immediately
	Reply(sender,NULL,0);

// process the message rec'd
	hndlWorld();

	fcLogx(__FILE__, fn,
		globalMask,
		RECV_MARK,
		"This one is logged at RECV_MARK level=%X",
		RECV_MARK);

	fcLogx(__FILE__, fn,
		globalMask,
		RECV_FUNC_IO,
		"This one is logged at RECV_FUNC_IO level=%X",
		RECV_FUNC_IO);

	fcLogx(__FILE__, fn,
		globalMask,
		RECV_STRUCTS,
		"This one is logged at RECV_STRUCTS level=%X",
		RECV_STRUCTS);

	} // end while

} // end receiver

/*==============================================
	hndlWorld - entry point
==============================================*/
void hndlWorld()
{
static char *fn="hndlWorld";
int *token;

token = (int *)inArea;
		
switch(*token)
	{
	case FC_SET_LOG_MASK:
		{
		FC_SET_LOG_MASK_MSG *inMsg;

		inMsg=(FC_SET_LOG_MASK_MSG *)inArea;
		globalMask=inMsg->logMask;

		fcLogx(__FILE__, fn,
			0xff,      // this will force this message out
			RECV_MARK,
			"new log mask=%X",
			globalMask);
		}
		break;

	default:
		printf("%s:unknown token=%d\n",fn,*token);
		break;
	} // end switch
} // end hndlWorld
