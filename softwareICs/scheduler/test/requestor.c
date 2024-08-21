/*************************************************************

FILE:		requestor.c

DESCRIPTION:	
It will be used to stimulate the scheduler 
SIMPL softwareIC. 

AUTHOR:			R.D. Findlay

-------------------------
iCanProgram Inc. 2006

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

If you discover a bug or add an enhancement 
contact the SIMPL project mailing list.
-------------------------

Revision history:
=======================================================
$Log: requestor.c,v $
Revision 1.2  2011/09/08 16:47:54  bobfcsoft
explicit select header

Revision 1.1  2006/06/19 22:32:45  bobfcsoft
new files

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/select.h>

#include "schedulerMsgs.h"

#define _ALLOC
#include "requestor.h"
#undef _ALLOC

#include "requestorProto.h"
#include "simplProto.h"
#include "loggerProto.h"

/*--------------------------------------
	requestor - entry point
--------------------------------------*/
int main(int argc, char **argv, char **envp)
{
static char *fn="requestor";
int x_it=0;
char line[80];

initialize(argc, argv);

fcLogx(__FILE__, fn,
	globalMask,
	REQ_MARK,
	"starting"
	);

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
		line[strlen(line)-1]=0; /* get rid of CR */

		switch(line[0])
			{
			case '?':	// help
				printf("requestor commands:\n");
				printf("d <+secs> <str> - schedule daily +sec from now\n");
				printf("s <+secs> <str> - schedule this +sec from now\n");
				printf("w <+secs> <str> - schedule weekly +sec from now\n");
				printf("q       - quit\n");

				printf("-> ");
				fflush(stdout);
				break;

			case 'd':	//schedule daily
				{
				SCHEDULE_THIS_MSG *outMsg;
				AGENT_TEST_MSG *testMsg;
				time_t now;
				time_t midnight;
				struct tm *t;
				int sbytes;
				char *p;
				int fromnow;

				p=skipOverWhiteSpace(line);
				fromnow=atoi(p);
				
				p=skipOverWhiteSpace(p);

				fcLogx(__FILE__, fn,
					globalMask,
					REQ_MISC,
					"TEST str=<%s> %d sec from now",
					p,
					fromnow
					);

				now=time(NULL);
				t=localtime(&now);
				t->tm_hour=0;
				t->tm_min=0;
				t->tm_sec=0;
				midnight=mktime(t);

				outMsg=(SCHEDULE_THIS_MSG *)outArea;
				outMsg->token=SCHEDULE_THIS;
				outMsg->stamp=now+fromnow; 
				outMsg->offset=outMsg->stamp-midnight;
				outMsg->flags |= SCHEDULER_DAILY; 

				testMsg=(AGENT_TEST_MSG *)&outMsg->mark;
				testMsg->token=AGENT_TEST;
				memcpy(testMsg->str,p, 79);

				outMsg->nbytes=sizeof(AGENT_TEST_MSG);

				sbytes=sizeof(SCHEDULE_THIS_MSG)+outMsg->nbytes;

				Send(agencyID, outArea, inArea, 
					sbytes,
					MAX_MSG_SIZE);
				

				printf("-> ");
				fflush(stdout);
				}
				break;

			case 's':	//schedule this
				{
				SCHEDULE_THIS_MSG *outMsg;
				AGENT_TEST_MSG *testMsg;
				time_t now;
				int sbytes;
				char *p;
				int fromnow;

				p=skipOverWhiteSpace(line);
				fromnow=atoi(p);
				
				p=skipOverWhiteSpace(p);

				fcLogx(__FILE__, fn,
					globalMask,
					REQ_MISC,
					"TEST str=<%s> %d sec from now",
					p,
					fromnow
					);

				now=time(NULL);

				outMsg=(SCHEDULE_THIS_MSG *)outArea;
				outMsg->token=SCHEDULE_THIS;
				outMsg->stamp=now+fromnow; 
				outMsg->flags=0;

				testMsg=(AGENT_TEST_MSG *)&outMsg->mark;
				testMsg->token=AGENT_TEST;
				memcpy(testMsg->str,p, 79);

				outMsg->nbytes=sizeof(AGENT_TEST_MSG);

				sbytes=sizeof(SCHEDULE_THIS_MSG)+outMsg->nbytes;

				Send(agencyID, outArea, inArea, 
					sbytes,
					MAX_MSG_SIZE);
				

				printf("-> ");
				fflush(stdout);
				}
				break;

			case 'w':	//schedule weekly
				{
				SCHEDULE_THIS_MSG *outMsg;
				AGENT_TEST_MSG *testMsg;
				time_t now;
				time_t midnight;
				struct tm *t;
				int sbytes;
				char *p;
				int fromnow;

				p=skipOverWhiteSpace(line);
				fromnow=atoi(p);
				
				p=skipOverWhiteSpace(p);

				fcLogx(__FILE__, fn,
					globalMask,
					REQ_MISC,
					"TEST str=<%s> %d sec from now",
					p,
					fromnow
					);

				now=time(NULL);
				t=localtime(&now);
				t->tm_hour=0;
				t->tm_min=0;
				t->tm_sec=0;
				midnight=mktime(t);

				outMsg=(SCHEDULE_THIS_MSG *)outArea;
				outMsg->token=SCHEDULE_THIS;
				outMsg->stamp=now+fromnow; 
				outMsg->offset=outMsg->stamp-midnight;
				outMsg->flags |= SCHEDULER_WEEKLY; 

				testMsg=(AGENT_TEST_MSG *)&outMsg->mark;
				testMsg->token=AGENT_TEST;
				memcpy(testMsg->str,p, 79);

				outMsg->nbytes=sizeof(AGENT_TEST_MSG);

				sbytes=sizeof(SCHEDULE_THIS_MSG)+outMsg->nbytes;

				Send(agencyID, outArea, inArea, 
					sbytes,
					MAX_MSG_SIZE);
				

				printf("-> ");
				fflush(stdout);
				}
				break;

			case 'q':
				x_it=1;
				break;

			default:
				printf("%s: unknown keypress <%c>\n",
					fn,
					line[0]);
				printf("-> ");
				fflush(stdout);
				break;
			} // end switch

		} // end if keyboard

	} // end while

fcLogx(__FILE__, fn,
	globalMask,
	REQ_MISC,
	"done");

name_detach();

exit(0);
}// end requestor
