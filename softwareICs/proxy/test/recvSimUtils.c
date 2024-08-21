/*************************************************************

FILE:		recvSimUtils.c

DESCRIPTION:	
This file contains some utility modules for receiverSim. 

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
$Log: recvSimUtils.c,v $
Revision 1.1  2006/06/21 21:05:45  bobfcsoft
new proxy code

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "proxyMsgs.h"

#define _ALLOC extern
#include "receiverSim.h"
#undef _ALLOC

#include "recvSimProto.h"
#include "simplProto.h"
#include "loggerProto.h"

/*=========================================
	 postmyID - entry point
=========================================*/
int postmyID(theID)
{
static char *fn="postmyID";
int rc=-1;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MARK,
	"theID=%d proxyID=%d",
	theID,
	proxyID
	);

write(proxyID, &theID, 4);

return(rc);

}// end postmyID

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
