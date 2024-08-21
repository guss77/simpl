/*************************************************************
FILE:	senderStim.h	

DESCRIPTION:	
This file contains globals for senderStim app.

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
$Log: senderStim.h,v $
Revision 1.1  2007/07/27 14:13:04  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 21:11:48  root
v2.0 compatible

Revision 1.1  2002/10/30 15:58:04  root
Initial revision

=======================================================

*************************************************************/
#ifndef _SENDER_STIM_DEFS
#define _SENDER_STIM_DEFS

#include "simpl.h"
#include "loggerVars.h"

#define MAX_MSG_SIZE 	8192

// stuff to enable trace logger
_ALLOC unsigned int globalMask;
#define SEND_STIM_MARK		0x00000001
#define SEND_STIM_FUNC_IO	0x00000002
#define SEND_STIM_MISC		0x00000010

_ALLOC int fcMgrID;

// for keyboard access
_ALLOC int fd;
_ALLOC int maxfd;
_ALLOC int my_fds[2];
_ALLOC fd_set watchset;
_ALLOC fd_set inset;

_ALLOC char inArea[MAX_MSG_SIZE];
_ALLOC char outArea[MAX_MSG_SIZE];

#endif
