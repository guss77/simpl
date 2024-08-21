/*************************************************************
FILE:	logmasker.h	

DESCRIPTION:	
This file contains globals for logmasker app.

AUTHOR:			R.D. Findlay

-------------------------
FCsoftware Inc. 1999, 2002, 2007

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

If you discover a bug or add an enhancement 
contact us on the SIMPL project mailing list. 

-------------------------

Revision history:
=======================================================
$Log: logmasker.h,v $
Revision 1.1  2007/07/24 20:57:54  bobfcsoft
new file

=======================================================

*************************************************************/
#ifndef _LOGMASKER_DEF
#define _LOGMASKER_DEF

#include "loggerVars.h"

#define	MAX_MSG_BUFFER_SIZE		1024
#define LOGMASKER_MARK	0x00000001

_ALLOC unsigned int globalMask;

_ALLOC char toName[20];
_ALLOC int toPid;

_ALLOC int my_fds[2];
_ALLOC fd_set watchset;
_ALLOC fd_set inset;

_ALLOC char data[1024];

_ALLOC char inArea[MAX_MSG_BUFFER_SIZE];
_ALLOC char outArea[MAX_MSG_BUFFER_SIZE];

#endif
