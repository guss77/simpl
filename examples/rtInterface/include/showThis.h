/*=========================================

FILE:	showThis.h	

DESCRIPTION:	
This file contains globals for showThis app.

AUTHOR:			R.D. Findlay

-------------------------
FCsoftware Inc. 1999, 2007
This code is released as open source.   We hope you find 
it useful.  If you discover a bug or add an enhancement 
contact us on the SIMPL project mailing list. 

-------------------------

Revision history:
=======================================================
$Log: showThis.h,v $
Revision 1.1  2007/07/26 15:51:49  bobfcsoft
new file

Revision 1.1  1999/09/16 18:17:18  root
Initial revision

=======================================================
=========================================*/
#ifndef _SHOWTHIS_DEF
#define _SHOWTHIS_DEF

#include "loggerVars.h"

#define	MAX_MSG_BUFFER_SIZE		1024
#define DISPLAY_MARK	0x00000001

_ALLOC unsigned int globalMask;

_ALLOC int my_fds[4];
_ALLOC fd_set watchset;
_ALLOC fd_set inset;

_ALLOC char inArea[MAX_MSG_BUFFER_SIZE];
_ALLOC char outArea[MAX_MSG_BUFFER_SIZE];

#endif
