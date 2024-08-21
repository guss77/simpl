/*************************************************************

FILE:		queueSim.c

DESCRIPTION:	
This program is an example of a queue simulator. 
It is used for receiving messages from the emitter poller 
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
$Log: queueSim.c,v $
Revision 1.2  2011/09/08 16:40:43  bobfcsoft
explicit select header

Revision 1.1  2006/06/19 22:32:44  bobfcsoft
new files

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/select.h>

#include "emitterMsgs.h"

#define _ALLOC
#include "queueSim.h"
#undef _ALLOC

#include "queueSimProto.h"
#include "simplProto.h"
#include "loggerProto.h"

/*===============================================
	queueSim - entry point
================================================*/
int main(int argc, char **argv, char **envp)
{
static char *fn="queueSim";
int x_it=0;
char line[80];
char callHomeStr[80];

initialize(argc, argv);

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
		line[strlen(line)-1]=0; /* get rid of CR */

		switch(line[0])
			{
			case '?':	// help
				printf("queueSim commands:\n");
				printf("c <str>  - call home\n");
				printf("q - quit\n");
				break;

			case 'c': // call home
				{
				UINT32 *flags;
				char *p;

				flags=(UINT32 *)shmPtr;

				*flags=0x01;	

				p=skipOverWhiteSpace(line);

				memcpy(callHomeStr,p,strlen(p));
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
	if(FD_ISSET(my_fds[0], &inset))  //  receive is ready
		{
		int nbytes;			
		char *sender;
		UINT16 *token;

		token=(UINT16 *)inArea;

		nbytes = Receive(&sender, inArea, MAX_MSG_SIZE);

		switch(*token)
			{
			case EMITTER_REGISTER:
				{
				EMITTER_REGISTER_MSG *inMsg;

				inMsg=(EMITTER_REGISTER_MSG *)inArea;

				fcLogx(__FILE__, fn,
					globalMask,
					RECV_SIM_MISC,
					"REGISTER shmid=%d",
					inMsg->shmid
					);

// attach the shmem for messages to this process
				shmPtr = shmat(inMsg->shmid, 0, 0);

				Reply(sender,NULL,0);
				}
				break;

			case EMITTER_CALL_HOME:
				{
				UINT32 *flags;
				EMITTER_DATA_MSG *outMsg;

				flags=(UINT32 *)shmPtr;

				*flags=0x00;	

				fcLogx(__FILE__, fn,
					globalMask,
					RECV_SIM_MISC,
					"CALLING HOME"
					);

				outMsg=(EMITTER_DATA_MSG *)outArea;
				outMsg->token=EMITTER_DATA;
				memcpy(outMsg->msg,callHomeStr,79);

				Reply(sender,outArea,sizeof(EMITTER_DATA_MSG));
				}
				break;

			case EMITTER_DATA:
				{
				EMITTER_DATA_MSG *inMsg;

				inMsg=(EMITTER_DATA_MSG *)inArea;

				fcLogx(__FILE__, fn,
					globalMask,
					RECV_SIM_MISC,
					"msg=<%s>",
					inMsg->msg
					);

printf("%s:msg=<%s>\n",
	fn,
	inMsg->msg
	);
			


				Reply(sender,NULL,0);
if(!backgroundMode)
	{
	printf("-> ");
	fflush(stdout);
	}
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
	RECV_SIM_MISC,
	"done");

name_detach();

exit(0);

}// end queueSim
