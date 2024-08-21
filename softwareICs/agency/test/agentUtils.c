/*************************************************************

FILE:		agentUtils.c

DESCRIPTION:	
This file contains utility code for agent.

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
$Log: agentUtils.c,v $
Revision 1.2  2008/08/11 21:23:19  bobfcsoft
wrapped message from requestor

Revision 1.1  2007/07/27 14:10:49  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 21:01:27  root
v2.0 compatible

Revision 1.1  2002/10/29 18:47:34  root
Initial revision

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "agencyMsgs.h"

#define _ALLOC extern
#include "agent.h"
#undef _ALLOC

#include "agentProto.h"
#include "simplProto.h"
#include "loggerProto.h"

/*===============================================
	hndlMsg - entry point
===============================================*/
int hndlMsg(char *sender, char *msgArea)
{
static char *fn="hndlMsg";
UINT16 *token;
int rc=0;

fcLogx(__FILE__, fn,
	globalMask,
	AGENT_FUNC_IO,
	"ding"
	);

token=(UINT16 *)msgArea;

switch(*token)
	{
	case AGENT_TEST:
		{
		AGENT_TEST_MSG *inMsg;
		AGENCY_WRAP_MSG *wrapMsg;
		AGENT_TEST_MSG *outMsg;

		inMsg=(AGENT_TEST_MSG *)msgArea;

		fcLogx(__FILE__, fn,
			globalMask,
			AGENT_MISC,
			"TEST str=<%s>",
			inMsg->str
			);

		wrapMsg=(AGENCY_WRAP_MSG *)outArea;
		wrapMsg->token = AGENCY_REPLY;
		wrapMsg->sender = sender;
		wrapMsg->nbytes = sizeof(AGENT_TEST_MSG);

		outMsg=(AGENT_TEST_MSG *)&wrapMsg->mark;
		outMsg->token = AGENT_TEST;
		sprintf(outMsg->str,"reply #%d",replyCount++);

		fcLogx(__FILE__, fn,
			globalMask,
			AGENT_MISC,
			"%d bytes reply to requestor=%X str=<%s>",
			wrapMsg->nbytes,
			wrapMsg->sender,
			outMsg->str
			);

		rc=8+sizeof(AGENT_TEST_MSG);
		}
		break;

	default:
		{
		AGENCY_WHAT_YA_GOT_MSG *outMsg;

		outMsg=(AGENCY_WHAT_YA_GOT_MSG *)outArea;
		outMsg->token = AGENCY_WHAT_YA_GOT;
		rc=sizeof(AGENCY_WHAT_YA_GOT_MSG);
		}
		break;
	} // end switch

return(rc);

} // end hndlMsg
