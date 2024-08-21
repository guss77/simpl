/*************************************************************

FILE:		agent.c

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
$Log: agent.c,v $
Revision 1.1  2006/06/19 22:32:45  bobfcsoft
new files

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "schedulerMsgs.h"

#define _ALLOC
#include "agent.h"
#undef _ALLOC

#include "agentProto.h"
#include "simplProto.h"
#include "loggerProto.h"

/*===============================================
	agent - entry point
===============================================*/
int main(int argc, char **argv, char **envp)
{
static char *fn="agent";
int x_it=0;
UINT16 *token;
AGENT_WHAT_YA_GOT_MSG *outMsg;
int sbytes;

initialize(argc, argv);

fcLogx(__FILE__, fn,
	globalMask,
	AGENT_MARK,
	"starting after delay of %d secs",
	startupDelay
	);

token=(UINT16 *)inArea;

outMsg=(AGENT_WHAT_YA_GOT_MSG *)outArea;
outMsg->token = AGENT_WHAT_YA_GOT;
sbytes=sizeof(AGENT_WHAT_YA_GOT_MSG);

if(startupDelay != 0) sleep(startupDelay);

while(!x_it)
	{
	Send(agencyID, outArea, inArea, sbytes, MAX_MSG_SIZE);

	switch(*token)
		{
		case AGENT_TEST:
			{
			AGENT_TEST_MSG *inMsg;

			inMsg=(AGENT_TEST_MSG *)inArea;

			fcLogx(__FILE__, fn,
				globalMask,
				AGENT_MISC,
				"TEST str=<%s>",
				inMsg->str
				);

			outMsg=(AGENT_WHAT_YA_GOT_MSG *)outArea;
			outMsg->token = AGENT_WHAT_YA_GOT;
			sbytes=sizeof(AGENT_WHAT_YA_GOT_MSG);
			}
			break;


		default:
			{
			AGENT_WHAT_YA_GOT_MSG *outMsg;

			fcLogx(__FILE__, fn,
				globalMask,
				AGENT_MARK,
				"unknown token=%d",
				*token
				);
			printf("%s:unknown token=%d\n",fn,*token);

			outMsg=(AGENT_WHAT_YA_GOT_MSG *)outArea;
			outMsg->token = AGENT_WHAT_YA_GOT;
			sbytes=sizeof(AGENT_WHAT_YA_GOT_MSG);
			}
			break;
		}

	} // end while

fcLogx(__FILE__, fn,
	globalMask,
	AGENT_FUNC_IO,
	"done");

name_detach();

exit(0);

}// end agent
