/*************************************************************

FILE:		receiver.c

DESCRIPTION:	
This program is the receiver for the stimulator SIMPL softwareIC. 

AUTHOR:			R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2000, 2002 FCSoftware Inc. 

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

    If you discover a bug or add an enhancement here's how to reach us: 

	fcsoft@attcanada.ca
-----------------------------------------------------------------------
Revision history:
=======================================================
$Log: receiver.c,v $
Revision 1.1  2008/04/28 18:00:22  bobfcsoft
new in CVS

Revision 1.3  2003/04/03 16:50:44  root
fixed RedHat 7.x warning

Revision 1.2  2002/12/03 21:25:10  root
v2.0 compatible

Revision 1.1  2002/12/03 20:23:05  root
Initial revision

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#if 0
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/timeb.h>
#include <sys/time.h>
#endif

#include "receiverMsgs.h"

#define _ALLOC
#include "receiver.h"
#undef _ALLOC

#include "receiverProto.h"
#include "simplProto.h"
#include "loggerProto.h"

/*===============================================
	receiver - entry point
===============================================*/
int main(int argc, char **argv, char **envp)
{
static char *fn="receiver";
int x_it=0;
int nbytes;			
char *sender;
UINT16 *token;
int msgCount=0;

initialize(argc, argv);

fcLogx(__FILE__, fn,
	globalMask,
	RECV_MARK,
	"starting"
	);

while(!x_it)
	{
	token=(UINT16 *)inArea;

	nbytes = Receive(&sender, inArea, MAX_MSG_SIZE);

	switch(*token)
		{
		case RECV_TEST:
			{
			RECV_TEST_MSG *inMsg;
			RECV_TEST_MSG *outMsg;

			inMsg=(RECV_TEST_MSG *)inArea;

			fcLogx(__FILE__, fn,
				globalMask,
				RECV_MISC,
				"TEST str=<%s>",
				inMsg->str
				);

			outMsg=(RECV_TEST_MSG *)outArea;
			outMsg->token = RECV_TEST;
			sprintf(outMsg->str,"reply #%d",msgCount++);

			fcLogx(__FILE__, fn,
				globalMask,
				RECV_MISC,
				"TEST reply str=<%s>",
				outMsg->str
				);


			Reply(sender,outArea,sizeof(RECV_TEST_MSG));
			}
			break;

		default:
			Reply(sender,NULL,0);

			fcLogx(__FILE__, fn,
				globalMask,
				RECV_MARK,
				"unknown token=%d",
				*token
				);
			printf("%s:unknown token=%d\n",fn,*token);
			break;

		} // end switch
	} // end while

fcLogx(__FILE__, fn,
	globalMask,
	RECV_FUNC_IO,
	"done");

name_detach();

exit(0);

}// end receiver
