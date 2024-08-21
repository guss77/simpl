/*************************************************************
FILE:	agency.h	

DESCRIPTION:	
This file contains globals for polling emitter app.

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
$Log: emitter.h,v $
Revision 1.1  2006/06/19 22:32:44  bobfcsoft
new files

=======================================================

*************************************************************/
#ifndef _EMITTER_DEF
#define _EMITTER_DEF

#include "simpl.h"
#include "loggerVars.h"

#define	MAX_MSG_BUFFER_SIZE		1024

_ALLOC unsigned int globalMask;
#define EMITTER_MARK	0x00000001
#define EMITTER_FUNC_IO	0x00000002
#define EMITTER_STRUCTS	0x00000004
#define EMITTER_MISC	0x00000010

_ALLOC int queueID;
_ALLOC int myshmid;
_ALLOC char *myshmPtr;
_ALLOC char fullfilename[128];

_ALLOC char inArea[MAX_MSG_BUFFER_SIZE];
_ALLOC char outArea[MAX_MSG_BUFFER_SIZE];

#endif
