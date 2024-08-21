/*************************************************************

FILE:		scheduler.c

DESCRIPTION:	
This program is an example of a SIMPL enabled scheduler module. 

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
$Log: scheduler.c,v $
Revision 1.2  2011/09/08 16:45:44  bobfcsoft
explicit select header

Revision 1.1  2006/06/19 22:32:45  bobfcsoft
new files

=======================================================

*************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/select.h>

#include "schedulerMsgs.h"
#define _ALLOC
#include "scheduler.h"
#undef _ALLOC

#include "schedulerProto.h"
#include "loggerProto.h"
#include "simplProto.h"

/*=========================================================
	main - entry point
=========================================================*/
int main(int argc, char **argv)
{
static char *fn="scheduler";
int x_it=0;
int nbytes;			
char *sender;
UINT16 *token;
struct timeval tv;
int rc;

tv.tv_sec=10;  // 10 sec interval
tv.tv_usec=0;

initialize(argc, argv);

token=(UINT16 *)inArea;
while(!x_it)
	{
	inset = watchset;
	rc=select(maxfd+1, &inset, NULL, NULL, &tv);

	if (rc == 0) // timer expired
		{
		fcLogx(__FILE__, fn,
			globalMask,
			SCHEDULER_MISC,
			"timer click"
			);

		if(checkForExpired() == 1)
			{
		fcLogx(__FILE__, fn,
			globalMask,
			SCHEDULER_MISC,
			"got expired with agentPending=0x%X",
			agentPending
			);

			if (agentPending != NULL)
				dequeueMsg(agentPending);			
			}

		tv.tv_sec=10;  // 10 sec interval
		tv.tv_usec=0;
		}
	else
// Is this from SIMPL
	if(FD_ISSET(my_fds[0], &inset))  //  receiver is ready
		{

	nbytes = Receive(&sender, inArea, MAX_MSG_BUFFER_SIZE);
		
	switch(*token)
		{
		case AGENT_WHAT_YA_GOT:
			fcLogx(__FILE__, fn,
				globalMask,
				SCHEDULER_MISC,
				"WHAT_YA_GOT"
				);

			dequeueMsg(sender);
			break;

		case SCHEDULE_THIS:
			{
			void *msgArea;

			fcLogx(__FILE__, fn,
				globalMask,
				SCHEDULER_MISC,
				"SCHEDULE_THIS"
				);

			msgArea=createMsg(nbytes);
			if(msgArea != NULL)
				{
				memcpy(msgArea,inArea,nbytes);
					
				queueMsg(msgArea,nbytes);
				}
			else
				{
				fcLogx(__FILE__, fn,
					globalMask,
					SCHEDULER_MARK,
					"unable to process message"
					);
				}
			Reply(sender, NULL, 0);
			}
			break;

		case VIEW_NEXT:
			{
			VIEW_MSG *inMsg;

			inMsg=(VIEW_MSG *)inArea;

			fcLogx(__FILE__, fn,
				globalMask,
				SCHEDULER_MISC,
				"VIEW %d",
				inMsg->count
				);
			
			fetchRecord(inMsg->count);

			Reply(sender, outArea, sizeof(VIEW_MSG));
			}
			break;

		default:
			printf("%s:unknown token=%d\n",fn,*token);
// send back a NULL reply immediately
			Reply(sender, NULL, 0);
			break;
		} // end switch
		} // end if FD_ISSET

	} // end while

name_detach();

exit(0);
} // end scheduler
