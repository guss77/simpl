/*************************************************************

FILE:		receiverSim.c

DESCRIPTION:	
This program is an example of a receiver simulator. 
It is used for receiving messages from the relay 
SIMPL softwareIC.

AUTHOR:			R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2006 iCanProgram Inc. 

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
Revision 1.2  2011/09/08 16:44:25  bobfcsoft
explicit select header

Revision 1.1  2006/06/21 21:05:45  bobfcsoft
new proxy code

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/select.h>

#include "proxyMsgs.h"

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
char fn[20];
int x_it=0;
char line[80];
int msgCount=0;

initialize(argc, argv);

sprintf(fn,"recvSim_%02d",myID);

if(!backgroundMode)
	{
	printf("-> ");
	fflush(stdout);
	}
while(!x_it)
	{
	inset = watchset;
	select(maxfd+1, &inset, NULL, NULL, NULL);

// Is this from keyboard
	if(FD_ISSET(my_fds[1], &inset))  //  keyboard is ready
		{
		fgets(line, 79, stdin);

		switch(line[0])
			{
			case '?':	// help
				printf("receiverSim commands:\n");
				printf("q - quit\n");
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
	if(FD_ISSET(my_fds[0], &inset))  //  receive is ready
		{
		int nbytes;			
		char *sender;
		UINT16 *token;

		token=(UINT16 *)inArea;

		nbytes = Receive(&sender, inArea, MAX_MSG_SIZE);

		switch(*token)
			{
			case RELAY_TEST:
				{
				RELAY_TEST_MSG *inMsg;
				RELAY_TEST_MSG *outMsg;

				inMsg=(RELAY_TEST_MSG *)inArea;

				fcLogx(__FILE__, fn,
					globalMask,
					TRACE_MISC,
					"TEST str=<%s>",
					inMsg->str
					);

printf("%s:TEST str=<%s>\n",
	fn,
	inMsg->str
	);
			

				outMsg=(RELAY_TEST_MSG *)outArea;
				outMsg->token=RELAY_TEST;
				sprintf(outMsg->str,"reply #%d",msgCount++);

				Reply(sender,outArea,sizeof(RELAY_TEST_MSG));
if(!backgroundMode)
	{
	printf("-> ");
	fflush(stdout);
	}
				sleep(10);
				postmyID(myID);
				}
				break;

			default:
				printf("%s:unknown token=%d\n",fn,*token);
				Reply(sender,NULL,0);
				break;
			}
		} // end else receive is ready
	} // end while

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MISC,
	"done");

name_detach();

exit(0);

}// end receiverSim
