/*************************************************************

FILE:		eventStimProto.c

DESCRIPTION:	
This file contains prototypes for the event stimulator. 

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
$Log: eventStimProto.h,v $
Revision 1.1  2006/06/26 18:03:17  bobfcsoft
statemachine

=======================================================

*************************************************************/

#ifndef _EVENT_STIM_PROTO_DEF
#define _EVENT_STIM_PROTO_DEF

#include "doorDefs.h"

void myUsage();
void initialize(int argc, char **argv);
void showHelp();
char *skipOverWhiteSpace(char *start);

#endif
