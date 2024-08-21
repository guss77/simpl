/*************************************************************

FILE:		eventStim.c

DESCRIPTION:	
This program is throws events at the statemachine module. 

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
$Log: eventStim.c,v $
Revision 1.2  2011/09/08 16:52:25  bobfcsoft
explicit select header

Revision 1.1  2006/06/26 18:03:18  bobfcsoft
statemachine

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/select.h>

#include "statemachineDefs.h"

#include "statemachineMsgs.h"

#include "doorDefs.h"
#include "doorMsgs.h"

#define _ALLOC
#include "eventStim.h"
#undef _ALLOC

#include "eventStimProto.h"
#include "simplmiscProto.h"
#include "loggerProto.h"

/*=====================================================
	eventStim - entry point
=====================================================*/
int main(int argc, char **argv, char **envp)
{
static char *fn="eventStim";
int x_it=0;
char line[80];
char *p;

printf("%s:starting\n",fn);

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
		fgets(line,80,stdin);
		line[strlen(line)-1]=0; // get rid of CR
		p=skipOverWhiteSpace(line);

		switch(line[0])
			{
			case '?':
				showHelp();
				break;

			case 'a':       // add new door
				{
				SM_REC_MSG *outMsg;
				DOOR_REC *doorRec;
				int sbytes;

				outMsg=(SM_REC_MSG *)outArea;
				doorRec=(DOOR_REC *)&outMsg->mydata;

				outMsg->token=SM_ADD_REC;
				outMsg->list=DOOR_LIST;
				outMsg->nbytes=sizeof(DOOR_REC);
				doorRec->doorID=atoi(p);
				sbytes=sizeof(SM_REC_MSG)+outMsg->nbytes;

				fcLogx(__FILE__, fn,
					globalMask,
					TRACE_MISC,
					"ADD door %d",
					doorRec->doorID);

				Send(statemachineID,
					outArea,
					inArea,
					sbytes,
					sizeof(MSG_SIZE));
				}
				break;

			case 'd':       // delete door
				{
				SM_DELETE_MSG *outMsg;
				int sbytes;

				outMsg=(SM_DELETE_MSG *)outArea;

				outMsg->token=SM_DELETE_REC;
				outMsg->list=DOOR_LIST;
				outMsg->ID=atoi(p);
				sbytes=sizeof(SM_DELETE_MSG);

				fcLogx(__FILE__, fn,
					globalMask,
					TRACE_MISC,
					"DELETE door %d",
					outMsg->ID);

				Send(statemachineID,
					outArea,
					inArea,
					sbytes,
					sizeof(MSG_SIZE));
				}
				break;

			case 'O':       // overwrite door
				{
				SM_REC_MSG *outMsg;
				DOOR_REC *doorRec;
				int sbytes;

				outMsg=(SM_REC_MSG *)outArea;
				doorRec=(DOOR_REC *)&outMsg->mydata;

				outMsg->token=SM_OVERWRITE_REC;
				outMsg->list=DOOR_LIST;
				outMsg->nbytes=sizeof(DOOR_REC);
				doorRec->doorID=atoi(p);

				p=skipOverWhiteSpace(p);
				doorRec->opentime=atoi(p);

				sbytes=sizeof(SM_REC_MSG)+outMsg->nbytes;

				fcLogx(__FILE__, fn,
					globalMask,
					TRACE_MISC,
					"OVERWRITE door %d",
					doorRec->doorID);

				Send(statemachineID,
					outArea,
					inArea,
					sbytes,
					sizeof(MSG_SIZE));
				}
				break;

			case 'D':       // dump internal datastore
				{
				SM_DUMP_MSG *outMsg;
				
				fcLogx(__FILE__, fn,
					globalMask,
					TRACE_MISC,
					"DUMP");

				outMsg=(SM_DUMP_MSG *)outArea;
				outMsg->token=SM_DUMP;
				Send(statemachineID,
					outArea,
					inArea,
					sizeof(SM_DUMP_MSG),
					sizeof(MSG_SIZE));

				}
				break;

			case 'R':       // resync from text file
				{
				SM_RESYNC_MSG *outMsg;
				
				outMsg=(SM_RESYNC_MSG *)outArea;
				outMsg->token=SM_RESYNC;
				sprintf(outMsg->filename,"%s/%s",mypath,p);

				fcLogx(__FILE__, fn,
					globalMask,
					TRACE_MISC,
					"RESYNC from %s",
					outMsg->filename);

				Send(statemachineID,
					outArea,
					inArea,
					sizeof(SM_RESYNC_MSG),
					sizeof(MSG_SIZE));

				}
				break;

			case 'c':       // close door
				{
				DOOR_EVENT_MSG *outMsg;
				
				outMsg=(DOOR_EVENT_MSG *)outArea;
				outMsg->token=DOOR_CLOSE;
				outMsg->doorID=atoi(p);

				fcLogx(__FILE__, fn,
					globalMask,
					TRACE_MISC,
					"CLOSE door %d",
					outMsg->doorID);

				Send(statemachineID,
					outArea,
					inArea,
					sizeof(DOOR_EVENT_MSG),
					sizeof(MSG_SIZE));
				}
				break;

			case 'o':       // open door
				{
				DOOR_EVENT_MSG *outMsg;
				
				outMsg=(DOOR_EVENT_MSG *)outArea;
				outMsg->token=DOOR_OPEN;
				outMsg->doorID=atoi(p);

				fcLogx(__FILE__, fn,
					globalMask,
					TRACE_MISC,
					"OPEN door %d",
					outMsg->doorID);

				Send(statemachineID,
					outArea,
					inArea,
					sizeof(DOOR_EVENT_MSG),
					sizeof(MSG_SIZE));
				}
				break;

			case 't':       // timeout door
				{
				DOOR_TIMER_MSG *outMsg;
				
				outMsg=(DOOR_TIMER_MSG *)outArea;
				outMsg->token=DOOR_TIMER;
				outMsg->doorID=atoi(p);

				p=skipOverWhiteSpace(p);
				outMsg->session=atoi(p);

				fcLogx(__FILE__, fn,
					globalMask,
					TRACE_MISC,
					"TIMER door %d",
					outMsg->doorID);

				Send(statemachineID,
					outArea,
					inArea,
					sizeof(DOOR_TIMER_MSG),
					sizeof(MSG_SIZE));
				}
				break;

			case 'u':       // unlock door
				{
				DOOR_EVENT_MSG *outMsg;
				
				outMsg=(DOOR_EVENT_MSG *)outArea;
				outMsg->token=DOOR_UNLOCK;
				outMsg->doorID=atoi(p);

				fcLogx(__FILE__, fn,
					globalMask,
					TRACE_MISC,
					"UNLOCK door %d",
					outMsg->doorID);

				Send(statemachineID,
					outArea,
					inArea,
					sizeof(DOOR_EVENT_MSG),
					sizeof(MSG_SIZE));
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
		UINT32 *token;

		token=(UINT32 *)inArea;

		nbytes = Receive(&sender, inArea, MSG_SIZE);

		switch(*token)
			{
			case DOOR_ALARM:
				{
				DOOR_ALARM_MSG *inMsg;

				inMsg = (DOOR_ALARM_MSG *)inArea;

				printf("door %d ALARM\n", inMsg->doorID);
		printf("-> ");
		fflush(stdout);
				}
				break;

			default:
				break;
			} // end switch
		} // end if receive ready
	
	} // end while

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"done");

name_detach();

return(1);

}// end eventStim

/*===================================================
	showHelp - entry point
===================================================*/
void showHelp()
{
printf("a <id>        - add new door <id>\n");
printf("d <id>        - delete door <id>\n");
printf("O <id> <time>       - overwrite door <id> with new <time>\n");
printf("D             - dump interal datastore\n");
printf("R <filename>  - resync from filename\n");
printf("c <id>        - close door <id>\n");
printf("o <id>        - open door <id>\n");
printf("u <id>        - unlock door <id>\n");
printf("t <id> <session> - timeout for door <id> and <session>\n");
printf("q             - quit\n");
} // end showHelp
