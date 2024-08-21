/*************************************************************

FILE:		proxyStimUtils.c

DESCRIPTION:	
This file contains utility code for proxyStim app.

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
$Log: proxyStimUtils.c,v $
Revision 1.1  2006/06/21 21:05:45  bobfcsoft
new proxy code

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "proxyMsgs.h"

#define _ALLOC extern
#include "proxyStim.h"
#undef _ALLOC

#include "proxyStimProto.h"
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
	case RELAY_TEST:
		{
		RELAY_TEST_MSG *inMsg;

		inMsg=(RELAY_TEST_MSG *)inArea;

		fcLogx(__FILE__, fn,
			globalMask,
			TRACE_MISC,
			"TEST reply str=<%s>",
			inMsg->str
			);

printf("%s:TEST reply str=<%s>\n",
	fn,
	inMsg->str
	);
			
		}
		break;

	case RELAY_ERROR:
		fcLogx(__FILE__, fn,
			globalMask,
			TRACE_MISC,
			"RELAY_ERROR"
			);

printf("%s:RELAY_ERROR - no available receivers\n",
	fn
	);
			
		break;

	default:
		printf("%s:unknown token=%d\n",fn,*token);
		break;
	}
} // end hndlReply
