/*************************************************************
FILE:	fcMgr.h	

DESCRIPTION:	
This file contains globals for fcMgr app.

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
$Log: fcMgr.h,v $
Revision 1.2  2009/04/14 18:56:50  bobfcsoft
added background mode

Revision 1.1  2007/07/27 14:13:04  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 21:10:26  root
v2.0 compatible

Revision 1.1  2002/10/30 15:56:26  root
Initial revision
=======================================================

*************************************************************/

#ifndef _FC_MGR_DEFS
#define _FC_MGR_DEFS

#define MAX_MSG_SIZE	8192

#include "fcMgrDefs.h"	// LINKED_LIST stuff
#include "simpl.h"
#include "loggerVars.h"

// some parameters to enable the trace logger
// fclogger
_ALLOC unsigned int globalMask;
#define FC_MGR_MARK		0x00000001
#define FC_MGR_FUNC_IO		0x00000002
#define FC_MGR_MISC		0x00000010

// general globals
_ALLOC int backgroundMode;
_ALLOC char *broadcasterPending;

_ALLOC Q_LINKED_LIST topofList;
_ALLOC Q_LINKED_LIST *head;

_ALLOC char inArea[MAX_MSG_SIZE];
_ALLOC char outArea[MAX_MSG_SIZE];

#endif
