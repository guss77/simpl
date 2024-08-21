/*************************************************************

FILE:		agentUtils.c

DESCRIPTION:	
This file contains utility code for agent.

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
$Log: agentUtils.c,v $
Revision 1.1  2006/06/19 22:32:45  bobfcsoft
new files

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "schedulerMsgs.h"

#define _ALLOC extern
#include "agent.h"
#undef _ALLOC

#include "agentProto.h"
#include "simplProto.h"
#include "loggerProto.h"

