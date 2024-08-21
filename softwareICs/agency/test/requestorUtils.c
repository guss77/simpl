/*************************************************************

FILE:		requestorUtils.c

DESCRIPTION:	
This file contains utility code for requestor app.

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
$Log: requestorUtils.c,v $
Revision 1.2  2008/08/11 21:23:19  bobfcsoft
wrapped message from requestor

Revision 1.1  2007/07/27 14:10:49  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 21:02:35  root
v2.0 compatible

Revision 1.1  2002/10/29 18:48:15  root
Initial revision

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "agencyMsgs.h"

#define _ALLOC extern
#include "requestor.h"
#undef _ALLOC

#include "requestorProto.h"
#include "simplProto.h"
#include "loggerProto.h"
#include "simplmiscProto.h"

/*====================================================
	hndlReply - entry point
====================================================*/
void hndlReply(char *msgArea)
{
static char *fn="hndlReply";
UINT16 *token;

token = (UINT16 *)msgArea;

switch(*token)
	{
	case AGENT_TEST:
		{
		AGENT_TEST_MSG *inMsg;

		inMsg=(AGENT_TEST_MSG *)inArea;

		fcLogx(__FILE__, fn,
			globalMask,
			REQ_MISC,
			"TEST_REPLY str=<%s>",
			inMsg->str
			);

printf("%s:TEST_REPLY str=<%s>\n",
	fn,
	inMsg->str
	);
			
		}
		break;

	default:
		printf("%s:unknown token=%d\n",fn,*token);
		break;
	}
} // end hndlReply
