/*************************************************************

FILE:		sendStimUtils.c

DESCRIPTION:	
This file contains utility code for senderStim app.

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
$Log: sendStimUtils.c,v $
Revision 1.1  2007/07/27 14:13:04  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 21:06:15  root
v2.0 compatible
.s

Revision 1.1  2002/10/30 16:00:41  root
Initial revision

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#if 0
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/timeb.h>
#include <sys/time.h>
#endif

#include "fcMgrMsgs.h"

#define _ALLOC extern
#include "senderStim.h"
#undef _ALLOC

#include "sendStimProto.h"
#include "simplProto.h"
#include "loggerProto.h"
#include "simplmiscProto.h"   // for atoh

