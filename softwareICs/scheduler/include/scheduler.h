/*************************************************************
FILE:	scheduler.h	

DESCRIPTION:	
This file contains globals for agency app.

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
$Log: scheduler.h,v $
Revision 1.1  2006/06/19 22:32:45  bobfcsoft
new files

=======================================================

*************************************************************/
#ifndef _SCHEDULER_DEF
#define _SCHEDULER_DEF

#include "simpl.h"
#include "loggerVars.h"
#include "schedulerDefs.h"  // for linked list stuff

#define	MAX_MSG_BUFFER_SIZE		1024

_ALLOC unsigned int globalMask;
#define SCHEDULER_MARK	0x00000001
#define SCHEDULER_FUNC_IO	0x00000002
#define SCHEDULER_STRUCTS	0x00000004
#define SCHEDULER_MISC	0x00000010

_ALLOC int fd;
_ALLOC int maxfd;
_ALLOC int my_fds[2];
_ALLOC fd_set watchset;
_ALLOC fd_set inset;

_ALLOC char *agentPending;
_ALLOC int nextRequestor;

_ALLOC Q_LINKED_LIST topofList;
_ALLOC Q_LINKED_LIST *head;

_ALLOC char inArea[MAX_MSG_BUFFER_SIZE];
_ALLOC char outArea[MAX_MSG_BUFFER_SIZE];

#endif
