/*************************************************************
FILE:	stimulator.h	

DESCRIPTION:	
This file contains globals for stimulator app.

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
$Log: stimulator.h,v $
Revision 1.1  2008/04/28 17:58:06  bobfcsoft
new in CVS

Revision 1.2  2002/12/03 21:23:12  root
v2.0 compatible

Revision 1.1  2002/12/03 20:22:15  root
Initial revision

=======================================================

*************************************************************/

#ifndef _STIMULATOR_DEFS
#define _STIMULATOR_DEFS

#include "simpl.h"
#include "loggerVars.h"

#define MAX_MSG_SIZE	8192

// some parameters for trace logger (fclogger)
_ALLOC unsigned int globalMask;
#define STIM_MARK		0x00000001
#define STIM_FUNC_IO		0x00000002
#define STIM_MISC		0x00000010

// general globals
_ALLOC char myName[20];

_ALLOC int recvID;

// to enable keyboard access
_ALLOC int backgroundMode;
_ALLOC int fd;
_ALLOC int maxfd;
_ALLOC int my_fds[2];
_ALLOC fd_set watchset;
_ALLOC fd_set inset;

_ALLOC char inArea[MAX_MSG_SIZE];
_ALLOC char outArea[MAX_MSG_SIZE];

#endif
