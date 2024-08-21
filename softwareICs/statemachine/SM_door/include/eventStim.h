/*************************************************************

FILE:		eventStim.h

DESCRIPTION:	
This file contains global definitions for eventStim. 

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
$Log: eventStim.h,v $
Revision 1.1  2006/06/26 18:03:17  bobfcsoft
statemachine

=======================================================

*************************************************************/

#ifndef _EVENT_STIM_DEFS
#define _EVENT_STIM_DEFS

#include "simpl.h"
#include "loggerVars.h"

#define MSG_SIZE			8192

_ALLOC unsigned int globalMask;
#define TRACE_MARK			0x00000001
#define TRACE_FUNC_IO		0x00000002
#define TRACE_MISC			0x00000010

_ALLOC int statemachineID;
_ALLOC int toPid;
_ALLOC char toName[20];
_ALLOC char myMsg[80];
_ALLOC char mypath[128];

_ALLOC int fd;
_ALLOC int maxfd;
_ALLOC int my_fds[2];
_ALLOC fd_set watchset;
_ALLOC fd_set inset;

_ALLOC char dataArea[MSG_SIZE];
_ALLOC char inArea[MSG_SIZE];
_ALLOC char outArea[MSG_SIZE];

#endif
