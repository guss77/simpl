/*************************************************************
FILE:	recvTester.h	

DESCRIPTION:	
This file contains globals for recvTester app.

AUTHOR:			R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2000, 2002 FCSoftware Inc. 

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

    If you discover a bug or add an enhancement here's please contact us
    on the SIMPL project mailing list. 

-----------------------------------------------------------------------
Revision history:
=======================================================
$Log: recvTester.h,v $
Revision 1.1  2008/04/28 17:58:06  bobfcsoft
new in CVS

Revision 1.2  2002/12/03 21:22:43  root
v2.0 compatible

Revision 1.1  2002/12/03 20:22:02  root
Initial revision

=======================================================

*************************************************************/

#ifndef _RECV_TESTER_DEFS
#define _RECV_TESTER_DEFS

#include "simpl.h"
#include "loggerVars.h"

#define MAX_MSG_SIZE  8192

_ALLOC unsigned int globalMask;
#define TESTER_MARK	0x00000001
#define TESTER_FUNC_IO	0x00000002
#define TESTER_MISC	0x00000010

_ALLOC int toPid;
_ALLOC int stimID;

_ALLOC char datapath[80];
_ALLOC char infile[40];
_ALLOC FILE *in_fp;
_ALLOC char fullinfile[128];

_ALLOC int fd;
_ALLOC int maxfd;
_ALLOC int my_fds[2];
_ALLOC fd_set watchset;
_ALLOC fd_set inset;

_ALLOC char dataArea[8192];
_ALLOC char inArea[8192];
_ALLOC char outArea[8192];

#endif
