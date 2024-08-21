/*=========================================

FILE:	rtStim.h	

DESCRIPTION:	
This file contains globals for rtStim app.

AUTHOR:			R.D. Findlay

-------------------------
FCsoftware Inc. 1999, 2007
This code is released as open source.   We hope you find 
it useful.  If you discover a bug or add an enhancement 
contact us on the SIMPL project mailing list. 

-------------------------

Revision history:
=======================================================
$Log: rtStim.h,v $
Revision 1.1  2007/07/26 15:51:49  bobfcsoft
new file

Revision 1.1  1999/09/16 18:17:04  root
Initial revision

=======================================================
=========================================*/
#ifndef _RTSTIM_DEF
#define _RTSTIM_DEF

#include "loggerVars.h"

#define	MAX_MSG_BUFFER_SIZE		1024
#define INPUT_MARK	0x00000001

_ALLOC unsigned int globalMask;

_ALLOC int toPid;

_ALLOC int my_fds[2];
_ALLOC int ctl;
_ALLOC fd_set watchset;
_ALLOC fd_set inset;
_ALLOC int myFrequency;

_ALLOC char keyArea[MAX_MSG_BUFFER_SIZE];
_ALLOC char inArea[MAX_MSG_BUFFER_SIZE];
_ALLOC char outArea[MAX_MSG_BUFFER_SIZE];

#endif
