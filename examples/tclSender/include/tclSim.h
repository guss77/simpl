/*=========================================
	tclSim.h

-------------------------
FCsoftware Inc. 2000, 2002, 2007

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

If you discover a bug or add an enhancement 
contact us on the SIMPL project mailing list. 

-------------------------
 $Log: tclSim.h,v $
 Revision 1.1  2007/07/24 21:04:05  bobfcsoft
 new file

=========================================*/

#ifndef _TCLSIM_DEF
#define _TCLSIM_DEF

#include "simpl.h"
#include "loggerVars.h"

#define	MAX_MSG_BUFFER_SIZE		1024
#define TCLSIM_MARK		0x00000001

_ALLOC unsigned int globalMask;

_ALLOC int toPid;

_ALLOC int maxfd;
_ALLOC int my_fds[2];
_ALLOC int ctl;
_ALLOC fd_set watchset;
_ALLOC fd_set inset;

_ALLOC char data[1024];

_ALLOC char inArea[MAX_MSG_BUFFER_SIZE];
_ALLOC char outArea[MAX_MSG_BUFFER_SIZE];

#endif
