/*************************************************************
FILE:	agent.h	

DESCRIPTION:	
This file contains globals for agent app.

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
$Log: agent.h,v $
Revision 1.1  2006/06/19 22:32:45  bobfcsoft
new files

=======================================================

*************************************************************/

#ifndef _AGENT_DEFS
#define _AGENT_DEFS

#define MAX_MSG_SIZE	8192

#include "simpl.h"
#include "loggerVars.h"

// some parameters to enable the trace logger
// fclogger
_ALLOC unsigned int globalMask;
#define AGENT_MARK		0x00000001
#define AGENT_FUNC_IO		0x00000002
#define AGENT_MISC		0x00000010

_ALLOC int replyCount;
_ALLOC int startupDelay;

_ALLOC int agencyID;

_ALLOC char inArea[MAX_MSG_SIZE];
_ALLOC char outArea[MAX_MSG_SIZE];

#endif
