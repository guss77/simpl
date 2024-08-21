/*************************************************************

FILE:		viewer.c

DESCRIPTION:	
It will be used to service the scheduler softwareIC. 

AUTHOR:			R.D. Findlay

-------------------------
iCanProgram Inc. 2006

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
$Log: viewer.c,v $
Revision 1.2  2011/09/08 16:47:54  bobfcsoft
explicit select header

Revision 1.1  2006/06/19 22:32:46  bobfcsoft
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
#include "viewer.h"
#undef _ALLOC

#include "viewerProto.h"
#include "simplProto.h"
#include "loggerProto.h"

/*===============================================
	viewer - entry point
===============================================*/
int main(int argc, char **argv, char **envp)
{
static char *fn="viewer";
int x_it=0;
UINT16 *token;
char line[80];
char stampStr[80];
char str[20];

initialize(argc, argv);

token=(UINT16 *)inArea;

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
				printf("viewer commands:\n");
				printf("s - show all scheduled events\n");
				printf("q       - quit\n");

				printf("-> ");
				fflush(stdout);
				break;

			case 's':	//show all
				{
				VIEW_MSG *outMsg;
				VIEW_MSG *inMsg;
				time_t now;
				int sbytes;
				int i;

				now=time(NULL);

printf("======================================================\n");
printf("current time %s",
	ctime(&now)
	);	
printf("======================================================\n");

				for(i=0; i<100; i++)
					{
					outMsg=(VIEW_MSG *)outArea;
					outMsg->token=VIEW_NEXT;
					outMsg->count=i;
					sbytes=sizeof(VIEW_MSG);

					Send(agencyID, outArea, inArea, 
						sbytes,
						MAX_MSG_SIZE);
				
					inMsg=(VIEW_MSG *)inArea;

fcLogx(__FILE__, fn,
	globalMask,
	AGENT_MARK,
	"incount=%d",
	inMsg->count
	);

					if(inMsg->count == -1) break;

					sprintf(stampStr,"%s", ctime(&inMsg->stamp));
					stampStr[strlen(stampStr)-1]=0;

					if(inMsg->flags & SCHEDULER_DAILY)
						sprintf(str,"DAILY");
					else
					if(inMsg->flags & SCHEDULER_WEEKLY)
						sprintf(str,"WEEKLY");
					else
						sprintf(str,"ONE SHOT");
printf("%d: %d bytes on %s %s\n",
	inMsg->count,
	inMsg->nbytes,
	stampStr,
	str
	);	

					} // end for
printf("======================================================\n");
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
	AGENT_FUNC_IO,
	"done");

name_detach();

exit(0);

}// end viewer
