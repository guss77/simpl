/*************************************************************

FILE:		stimulator.c

DESCRIPTION:	
This program is an example of a stimulator SIMPL software IC. 

AUTHOR:			R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2000, 2002 FCSoftware Inc. 

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
$Log: stimulator.c,v $
Revision 1.2  2011/09/08 16:54:09  bobfcsoft
explicit select header

Revision 1.1  2008/04/28 17:59:06  bobfcsoft
new in CVS

Revision 1.3  2003/04/03 16:30:47  root
fixed RedHat 7.x warnings

Revision 1.2  2002/12/03 21:23:58  root
v2.0 compatible

Revision 1.1  2002/12/03 20:21:10  root
Initial revision

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/select.h>


#include "stimulatorMsgs.h"
#include "receiverMsgs.h"

#define _ALLOC
#include "stimulator.h"
#undef _ALLOC

#include "stimulatorProto.h"
#include "simplProto.h"
#include "loggerProto.h"

/*--------------------------------------
	stimulator - entry point
--------------------------------------*/
int main(int argc, char **argv, char **envp)
{
static char *fn="stimulator";
int x_it=0;
char line[80];

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

		switch(line[0])
			{
			case '?':	// help
				printf("stimulator commands:\n");
				printf("t <str> - send test string\n");
				printf("q - quit\n");
				break;

			case 't':	//string
				{
				RECV_TEST_MSG *outMsg;
				char str[80];

				sprintf(str,"%s",&line[2]);

				fcLogx(__FILE__, fn,
					globalMask,
					STIM_MISC,
					"TEST str=<%s>",
					str
					);

				outMsg=(RECV_TEST_MSG *)outArea;

				outMsg->token=RECV_TEST;
				sprintf(outMsg->str,"%s",str);

				fcLogx(__FILE__, fn,
					globalMask,
					STIM_MISC,
					"msg=<%s> -> recvr at slot=%d",
					outMsg->str,
					recvID
					);

				Send(recvID, outArea, inArea, sizeof(RECV_TEST_MSG), MAX_MSG_SIZE);
				hndlReply(inArea);
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
			case STIM_TEST:
				{
				STIM_TEST_MSG *inMsg;
				RECV_TEST_MSG *outMsg;

				inMsg=(STIM_TEST_MSG *)inArea;

				fcLogx(__FILE__, fn,
					globalMask,
					STIM_MISC,
					"TEST str=<%s>",
					inMsg->str
					);

printf("%s:TEST str=<%s>\n",
	fn,
	inMsg->str
	);
			
				outMsg=(RECV_TEST_MSG *)outArea;
				outMsg->token=RECV_TEST;
				sprintf(outMsg->str,"%s",inMsg->str);

				Send(recvID, outArea, inArea, sizeof(RECV_TEST_MSG), MAX_MSG_SIZE);

				hndlReply(inArea);

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
	STIM_MISC,
	"done");

name_detach();

exit(0);

}// end stimulator
