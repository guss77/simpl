
/*************************************************************
FILE:		receiver.h

DESCRIPTION:	
This file contains

AUTHOR:		R.D. Findlay

-------------------------
FCsoftware Inc. 1999, 2007
This code is released as open source.   We hope you find 
it useful.  If you discover a bug or add an enhancement 
contact us on the SIMPL project mailing list. 

-------------------------

Revision history:
=======================================================
$Log: receiver.h,v $
Revision 1.1  2007/07/24 20:57:54  bobfcsoft
new file

=======================================================

*************************************************************/

#ifndef _RECEIVER_DEF
#define _RECEIVER_DEF

#include "loggerVars.h"

#define	MAX_MSG_BUFFER_SIZE		1024

#define RECV_MARK	0x00000001
#define RECV_FUNC_IO	0x00000002
#define RECV_STRUCTS	0x00000004
_ALLOC unsigned int globalMask;

_ALLOC char inArea[MAX_MSG_BUFFER_SIZE];
_ALLOC char outArea[MAX_MSG_BUFFER_SIZE];

#endif
