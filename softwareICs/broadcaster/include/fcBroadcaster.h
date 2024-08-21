/*************************************************************
FILE:	fcBroadcaster.h	

DESCRIPTION:	
This file contains globals for fcBroadcaster app.

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
$Log: fcBroadcaster.h,v $
Revision 1.1  2007/07/27 14:13:04  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 21:10:13  root
v2.0 compatible

Revision 1.1  2002/10/30 15:56:19  root
Initial revision

=======================================================

*************************************************************/

#ifndef _FC_BROADCASTER_DEF
#define _FC_BROADCASTER_DEF

#include "simpl.h"
#include "fcBroadDefs.h"
#include "loggerVars.h"

#define	MAX_MSG_BUFFER_SIZE		1024

// some parameters for trace logger
// fclogger
_ALLOC unsigned int globalMask;
#define FCB_MARK	0x00000001
#define FCB_FUNC_IO	0x00000002
#define FCB_STRUCTS	0x00000004
#define FCB_MISC	0x00000010

// general globals
_ALLOC char myName[20];
_ALLOC int fcMgrID;
_ALLOC char fcMgr_name[20];

// for internal linked list
_ALLOC LINKED_LIST topofList;
_ALLOC LINKED_LIST *head;

_ALLOC char inArea[MAX_MSG_BUFFER_SIZE];
_ALLOC char outArea[MAX_MSG_BUFFER_SIZE];

#endif
