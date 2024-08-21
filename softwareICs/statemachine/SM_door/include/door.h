/*************************************************************

FILE:		door.h

DESCRIPTION:	
This file contains global variables for door module. 

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
$Log: door.h,v $
Revision 1.1  2006/06/26 18:03:17  bobfcsoft
statemachine

=======================================================

*************************************************************/

#ifndef _DOOR_DEF
#define _DOOR_DEF

#include "doorDefs.h"
#include "statemachineDefs.h"
#include "loggerVars.h"

_ALLOC char infile[128];
_ALLOC char alarmName[20];
_ALLOC int alarmID;

// for list
_ALLOC LINKED_LIST topofList[MAX_LIST_TYPES];
_ALLOC LINKED_LIST *listHead[MAX_LIST_TYPES];

// for pools
_ALLOC POOL_TABLE poolTable[MAX_POOL_TYPES];

#endif
