/*************************************************************

FILE:		statemachine.h

DESCRIPTION:	
This file contains global variables for statemachine module. 

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
$Log: statemachine.h,v $
Revision 1.1  2006/06/26 18:03:19  bobfcsoft
statemachine

=======================================================

*************************************************************/

#ifndef _STATEMACHINE_DEF
#define _STATEMACHINE_DEF

#include "statemachineDefs.h"
#include "loggerVars.h"

#define	MAX_MSG_BUFFER_SIZE		8192

#define TRACE_MARK	0x00000001
#define TRACE_FUNC_IO	0x00000002
#define TRACE_STRUCTS	0x00000004
#define TRACE_MISC	0x00000008
_ALLOC unsigned int globalMask;

_ALLOC int fd;
_ALLOC int maxfd;
_ALLOC int my_fds[2];
_ALLOC fd_set watchset;
_ALLOC fd_set inset;

_ALLOC char dataArea[MAX_MSG_BUFFER_SIZE];
_ALLOC char inArea[MAX_MSG_BUFFER_SIZE];
_ALLOC char outArea[MAX_MSG_BUFFER_SIZE];

#endif
