/*************************************************************

FILE:		stimulatorUtils.c

DESCRIPTION:	
This file contains some utility modules for receiverSim. 

AUTHOR:			R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2000, 2002 FCSoftware Inc. 

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

    If you discover a bug or add an enhancement here's how to reach us: 

	fcsoft@attcanada.ca
-----------------------------------------------------------------------
Revision history:
=======================================================
$Log: stimulatorUtils.c,v $
Revision 1.1  2008/04/28 17:59:06  bobfcsoft
new in CVS

Revision 1.2  2002/12/03 21:24:19  root
v2.0 compatible

Revision 1.1  2002/12/03 20:21:26  root
Initial revision

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#if 0
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/timeb.h>
#include <sys/time.h>
#endif

#include "stimulatorMsgs.h"
#include "receiverMsgs.h"

#define _ALLOC extern
#include "stimulator.h"
#undef _ALLOC

#include "stimulatorProto.h"
#include "simplProto.h"
#include "loggerProto.h"

/*=========================================
	skipOverWhiteSpace - entry point
=========================================*/
char *skipOverWhiteSpace(char *start)
{
char *p;

for(p=start; *p != 0 && *p != ' ' && *p != 0x09; p++);  // skip to whitespace
if(*p != 0)
	{
	for(; *p == ' ' || *p == 0x09; p++); // skip whitespace
	}

return(p);
}// end skipOverWhiteSpace

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
	case RECV_TEST:
		{
		RECV_TEST_MSG *inMsg;

		inMsg=(RECV_TEST_MSG *)inArea;

		fcLogx(__FILE__, fn,
			globalMask,
			STIM_MISC,
			"TEST reply str=<%s>",
			inMsg->str
			);

printf("%s:TEST reply str=<%s>\n",
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
