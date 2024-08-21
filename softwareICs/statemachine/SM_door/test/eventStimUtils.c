/*************************************************************

FILE:		eventStimUtils.c

DESCRIPTION:	
This file contains utility functions for eventStim module. 

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
$Log: eventStimUtils.c,v $
Revision 1.1  2006/06/26 18:03:18  bobfcsoft
statemachine

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "statemachineMsgs.h"

#include "doorDefs.h"
#include "doorMsgs.h"

#define _ALLOC extern
#include "eventStim.h"
#undef _ALLOC

#include "eventStimProto.h"
#include "loggerProto.h"
#include "simplProto.h"


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

