/*************************************************************
FILE:	agent.h	

DESCRIPTION:	
This file contains globals for agent app.

AUTHOR:			R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2000, 2002, 2007 FCSoftware Inc. 

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
Revision 1.1  2007/07/27 14:10:49  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 20:57:06  root
v2.0 compatible

Revision 1.1  2002/10/29 18:49:45  root
Initial revision

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
