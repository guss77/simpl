/*************************************************************

FILE:		proxyUtils.c

DESCRIPTION:	
This file contains utility code for proxy.

AUTHOR:			R.D. Findlay

-------------------------
iCanProgram Inc.  2006

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
$Log: proxyUtils.c,v $
Revision 1.1  2006/06/21 21:05:44  bobfcsoft
new proxy code

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "proxyMsgs.h"

#define _ALLOC extern
#include "proxy.h"
#undef _ALLOC

#include "proxyProto.h"
#include "simplProto.h"
#include "loggerProto.h"

