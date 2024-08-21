/*************************************************************

FILE:		receiverSim.c

DESCRIPTION:	
This program is an example of a receiver simulator. 
It is used for receiving messages from the broadcaster
softwareIC.

AUTHOR:			R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2000, 2002, 2007 FCSoftware Inc. 

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

    If you discover a bug or add an enhancement contact us on the
    SIMPL project mailing list. 

-----------------------------------------------------------------------
Revision history:
=======================================================
$Log: receiverSim.c,v $
Revision 1.2  2011/09/08 16:36:11  bobfcsoft
header cleanup

Revision 1.1  2007/07/27 14:13:04  bobfcsoft
new cvs file

Revision 1.4  2003/04/03 16:43:02  root
more warning cleanup

Revision 1.3  2003/04/03 16:35:29  root
fixed RedHat 7.x warnings

Revision 1.2  2002/12/03 21:05:25  root
v2.0 compatible

Revision 1.1  2002/10/30 16:00:12  root
Initial revision

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/select.h>

#include "fcMgrMsgs.h"

#define _ALLOC
#include "receiverSim.h"
#undef _ALLOC

#include "recvSimProto.h"
#include "simplProto.h"
#include "loggerProto.h"

/*--------------------------------------
	receiverSim - entry point
--------------------------------------*/
int main(int argc, char **argv, char **envp)
{
static char *fn="recvSim";
int x_it=0;
char line[80];

initialize(argc, argv);

printf("-> ");
fflush(stdout);
while(!x_it)
	{
	inset = watchset;
	select(maxfd+1, &inset, NULL, NULL, NULL);

// Is this from keyboard
	if(FD_ISSET(my_fds[0], &inset))  //  keyboard is ready
		{
		fgets(line, 79, stdin);

		switch(line[0])
			{
			case '?':	// help
				printf("receiverSim commands:\n");
				printf("r - register\n");
				printf("d - deregister\n");
				printf("q - quit\n");
				break;

			case 'r': 	// register
				{
				FCM_REGISTER_MSG *outMsg;

				outMsg=(FCM_REGISTER_MSG *)outArea;
				outMsg->token=FCM_REGISTER;
				sprintf(outMsg->name,"%.19s",myName);
				outMsg->myPid = getpid();

#if 0
				loadSend(outArea,sizeof(FCM_REGISTER_MSG));
				sendMsgx(fcMgrID);
#endif
				Send(fcMgrID, outArea, NULL, sizeof(FCM_REGISTER_MSG), MAX_MSG_SIZE);
				}
				break;

			case 'd':	// deregister
				{
				FCM_REGISTER_MSG *outMsg;

				outMsg=(FCM_REGISTER_MSG *)outArea;
				outMsg->token=FCM_DEREGISTER;
				outMsg->myPid = getpid();

#if 0
				loadSend(outArea,sizeof(FCM_REGISTER_MSG));
				sendMsgx(fcMgrID);
#endif

				Send(fcMgrID, outArea, NULL, sizeof(FCM_REGISTER_MSG), MAX_MSG_SIZE);
				}
				break;

			case 'q':
				x_it=1;
				break;

			default:
				printf("%s: unknown keypress <%c>\n",
					fn,
					line[0]);
				break;
			} // end switch

		printf("-> ");
		fflush(stdout);
		} // end if keyboard
	else
// Is this from receive fifo
	if(FD_ISSET(my_fds[1], &inset))  //  receive is ready
		{
		int nbytes;			
		char *sender;
		UINT16 *token;

		token=(UINT16 *)inArea;

#if 0
		sender = receiveMsg(&msg, &nbytes);
		memcpy(inArea,msg,nbytes);
#endif
		nbytes=Receive(&sender, inArea, MAX_MSG_SIZE);

		switch(*token)
			{
			case FCM_TEST:
				{
				FCM_TEST_MSG *inMsg;

				inMsg=(FCM_TEST_MSG *)inArea;

				fcLogx(__FILE__, fn,
					globalMask,
					RECV_SIM_MISC,
					"TEST str=<%s>",
					inMsg->str
					);

printf("%s:TEST str=<%s>\n",
	fn,
	inMsg->str
	);
			
printf("-> ");
fflush(stdout);
#if 0
				loadReply(sender,NULL,0);
				replyMsg(sender);
#endif
				Reply(sender, NULL, 0);
				}
				break;

			default:
				printf("%s:unknown token=%d\n",fn,*token);
#if 0
				loadReply(sender,NULL,0);
				replyMsg(sender);
#endif
				Reply(sender, NULL, 0);
				break;
			}
		} // end else receive is ready
	} // end while

fcLogx(__FILE__, fn,
	globalMask,
	RECV_SIM_MISC,
	"done");

name_detach();

exit(0);

}// end receiverSim
