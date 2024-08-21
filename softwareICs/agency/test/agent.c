/*************************************************************

FILE:		agent.c

DESCRIPTION:	
It will be used to service the agency softwareIC. 

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
$Log: agent.c,v $
Revision 1.2  2008/08/11 21:23:19  bobfcsoft
wrapped message from requestor

Revision 1.1  2007/07/27 14:10:49  bobfcsoft
new cvs file

Revision 1.3  2003/04/03 16:55:27  root
fixes RedHat 7.x warnings

Revision 1.2  2002/12/03 21:01:04  root
v2.0 compatible

Revision 1.1  2002/10/29 18:47:21  root
Initial revision

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "agencyMsgs.h"

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
AGENCY_WHAT_YA_GOT_MSG *outMsg;
int sbytes;

initialize(argc, argv);

fcLogx(__FILE__, fn,
	globalMask,
	AGENT_MARK,
	"starting after delay of %d secs",
	startupDelay
	);

token=(UINT16 *)inArea;

outMsg=(AGENCY_WHAT_YA_GOT_MSG *)outArea;
outMsg->token = AGENCY_WHAT_YA_GOT;
sbytes=sizeof(AGENCY_WHAT_YA_GOT_MSG);

if(startupDelay != 0) sleep(startupDelay);

while(!x_it)
	{
	Send(agencyID, outArea, inArea, sbytes, MAX_MSG_SIZE);

	switch(*token)
		{
		case AGENCY_GOT_ONE:
			{
			AGENCY_WRAP_MSG *inMsg;
			UINT16 *msgToken;

			inMsg=(AGENCY_WRAP_MSG *)inArea;
			msgToken=(UINT16 *)&inMsg->mark;

			fcLogx(__FILE__, fn,
				globalMask,
				AGENT_MISC,
				"GOT_ONE sender=%X nbytes=%d token=%d",
				inMsg->sender,
				inMsg->nbytes,
				*msgToken
				);

			sbytes=hndlMsg(inMsg->sender, (char *)&inMsg->mark);
			}
			break;

		default:
			{
			AGENCY_WHAT_YA_GOT_MSG *outMsg;

			fcLogx(__FILE__, fn,
				globalMask,
				AGENT_MARK,
				"unknown token=%d",
				*token
				);
			printf("%s:unknown token=%d\n",fn,*token);

			outMsg=(AGENCY_WHAT_YA_GOT_MSG *)outArea;
			outMsg->token = AGENCY_WHAT_YA_GOT;
			sbytes=sizeof(AGENCY_WHAT_YA_GOT_MSG);
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
