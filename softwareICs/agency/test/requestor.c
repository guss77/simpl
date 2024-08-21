/*************************************************************

FILE:		requestor.c

DESCRIPTION:	
It will be used to stimulate the agency 
SIMPL softwareIC. 

AUTHOR:			R.D. Findlay

-------------------------
FCsoftware Inc. 2000, 2002, 2007

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
$Log: requestor.c,v $
Revision 1.3  2011/09/08 16:32:13  bobfcsoft
added sys/select.h for portability

Revision 1.2  2008/08/11 21:23:19  bobfcsoft
wrapped message from requestor

Revision 1.1  2007/07/27 14:10:49  bobfcsoft
new cvs file

Revision 1.3  2003/04/03 16:26:55  root
cleanup RedHat 7.x warnings

Revision 1.2  2002/12/03 21:02:04  root
v2.0 compatible

Revision 1.1  2002/10/29 18:47:57  root
Initial revision

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/select.h>

#include "agencyMsgs.h"

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

		switch(line[0])
			{
			case '?':	// help
				printf("requestor commands:\n");
				printf("t <str> - test string\n");
				printf("q       - quit\n");

				printf("-> ");
				fflush(stdout);
				break;

			case 't':	//string
				{
				AGENCY_WRAP_MSG *wrapMsg;
				AGENT_TEST_MSG *outMsg;
				int sbytes;
				char str[80];

				sprintf(str,"%s",&line[2]);

				fcLogx(__FILE__, fn,
					globalMask,
					REQ_MISC,
					"TEST str=<%s>",
					str
					);

				wrapMsg=(AGENCY_WRAP_MSG *)outArea;
				wrapMsg->token=AGENCY_PROCESS_THIS;
				wrapMsg->nbytes=sizeof(AGENT_TEST_MSG);
				sbytes=sizeof(AGENCY_WRAP_MSG)+wrapMsg->nbytes;

				outMsg=(AGENT_TEST_MSG *)&wrapMsg->mark;

				outMsg->token=AGENT_TEST;
				sprintf(outMsg->str,"%s",str);

				fcLogx(__FILE__, fn,
					globalMask,
					REQ_MISC,
					"token=%d msg=<%s> -> agency at slot=%d",
					outMsg->token,
					outMsg->str,
					agencyID
					);

				Send(agencyID, outArea, inArea, 
					sbytes,
					MAX_MSG_SIZE);
				
				hndlReply(inArea);
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
