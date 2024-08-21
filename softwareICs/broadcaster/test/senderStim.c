/*************************************************************

FILE:		senderStim.c

DESCRIPTION:	
This program is an example of a stimulator process.
It will be used to stimulate the broadcaster softwareIC. 

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
$Log: senderStim.c,v $
Revision 1.2  2011/09/08 16:37:06  bobfcsoft
header cleanup

Revision 1.1  2007/07/27 14:13:04  bobfcsoft
new cvs file

Revision 1.4  2003/04/03 16:43:48  root
more warning cleanup

Revision 1.3  2003/04/03 16:36:24  root
fixed RedHat 7.x warnings

Revision 1.2  2002/12/03 21:06:29  root
v2.0 compatible

Revision 1.1  2002/10/30 16:00:47  root
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
#include "senderStim.h"
#undef _ALLOC

#include "sendStimProto.h"
#include "simplProto.h"
#include "loggerProto.h"

/*--------------------------------------
	senderStim - entry point
--------------------------------------*/
int main(int argc, char **argv, char **envp)
{
static char *fn="sendStim";
int x_it=0;
char line[80];

initialize(argc, argv);

fcLogx(__FILE__, fn,
	globalMask,
	SEND_STIM_MARK,
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
				printf("senderStim commands:\n");
				printf("t <str> - send test string\n");
				printf("q       - quit\n");
				break;

			case 't':	//string
				{
				FCM_TEST_MSG *outMsg;
				char str[80];

				sprintf(str,"%s",&line[2]);

				fcLogx(__FILE__, fn,
					globalMask,
					SEND_STIM_MISC,
					"TEST str=<%s>",
					str
					);

				outMsg=(FCM_TEST_MSG *)outArea;

				outMsg->token=FCM_TEST;
				sprintf(outMsg->str,"%s",str);

				fcLogx(__FILE__, fn,
					globalMask,
					SEND_STIM_MISC,
					"sending <%s> to fcMgr at slot=%d",
					outMsg->str,
					fcMgrID
					);

				Send(fcMgrID, outArea, NULL, sizeof(FCM_TEST_MSG), MAX_MSG_SIZE);
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

	} // end while

fcLogx(__FILE__, fn,
	globalMask,
	SEND_STIM_MISC,
	"done");

name_detach();

exit(0);

}// end senderStim
