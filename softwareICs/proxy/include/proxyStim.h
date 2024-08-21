/*************************************************************
FILE:	proxyStim.h	

DESCRIPTION:	
This file contains globals for proxyStim app.

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
$Log: proxyStim.h,v $
Revision 1.1  2006/06/21 21:05:44  bobfcsoft
new proxy code

=======================================================

*************************************************************/
#ifndef _PROXY_STIM_DEFS
#define _PROXY_STIM_DEFS

#include "simpl.h"
#include "loggerVars.h"

#define MAX_MSG_SIZE 	8192

// stuff to enable trace logger
_ALLOC unsigned int globalMask;
#define TRACE_MARK		0x00000001
#define TRACE_FUNC_IO	0x00000002
#define TRACE_MISC		0x00000010

_ALLOC int proxyID;

// for keyboard access
_ALLOC int fd;
_ALLOC int maxfd;
_ALLOC int my_fds[2];
_ALLOC fd_set watchset;
_ALLOC fd_set inset;

_ALLOC char inArea[MAX_MSG_SIZE];
_ALLOC char outArea[MAX_MSG_SIZE];

#endif
