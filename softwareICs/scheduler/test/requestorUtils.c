/*************************************************************

FILE:		requestorUtils.c

DESCRIPTION:	
This file contains utility code for requestor app.

AUTHOR:			R.D. Findlay

-------------------------
iCanProgram Inc.  2006

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
Revision 1.1  2006/06/19 22:32:45  bobfcsoft
new files

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "schedulerMsgs.h"

#define _ALLOC extern
#include "requestor.h"
#undef _ALLOC

#include "requestorProto.h"
#include "simplProto.h"
#include "loggerProto.h"
#include "simplmiscProto.h"

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

