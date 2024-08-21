/*************************************************************

FILE:		proxyStim.c

DESCRIPTION:	
It will be used to stimulate the proxy 
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
$Log: proxyStim.c,v $
Revision 1.2  2011/09/08 16:44:25  bobfcsoft
explicit select header

Revision 1.1  2006/06/21 21:05:45  bobfcsoft
new proxy code

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/select.h>

#include "proxyMsgs.h"

#define _ALLOC
#include "proxyStim.h"
#undef _ALLOC

#include "proxyStimProto.h"
#include "simplProto.h"
#include "loggerProto.h"

/*--------------------------------------
	relayStim - entry point
--------------------------------------*/
int main(int argc, char **argv, char **envp)
{
static char *fn="proxyStim";
int x_it=0;
char line[80];

initialize(argc, argv);

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MARK,
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
		line[strlen(line)-1]=0;

		switch(line[0])
			{
			case '?':	// help
				printf("proxy stimulator commands:\n");
				printf("t <str> - test string\n");
				printf("q       - quit\n");

				printf("-> ");
				fflush(stdout);
				break;

			case 't':	//string
				{
				RELAY_TEST_MSG *outMsg;
				char str[80];

				sprintf(str,"%s",&line[2]);

				fcLogx(__FILE__, fn,
					globalMask,
					TRACE_MISC,
					"TEST str=<%s>",
					str
					);

				outMsg=(RELAY_TEST_MSG *)outArea;

				outMsg->token=RELAY_TEST;
				sprintf(outMsg->str,"%s",str);

				fcLogx(__FILE__, fn,
					globalMask,
					TRACE_MISC,
					"msg=<%s> -> relay at slot=%d",
					outMsg->str,
					proxyID
					);

				Send(proxyID, outArea, inArea, sizeof(RELAY_TEST_MSG), MAX_MSG_SIZE);

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
	TRACE_MISC,
	"done");

name_detach();

exit(0);

}// end proxyStim
