/*************************************************************

FILE:		doorDefs.h

DESCRIPTION:	
This file contains structure definitions for statemachine object. 

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
$Log: doorDefs.h,v $
Revision 1.1  2006/06/26 18:03:17  bobfcsoft
statemachine

=======================================================

*************************************************************/

#ifndef _DOOR_DEFS_DEF
#define _DOOR_DEFS_DEF

#include "standardTypes.h"

typedef enum
	{
	DOOR_CLOSED_LOCKED,
	DOOR_CLOSED_UNLOCKED,
	DOOR_OPENED,
	DOOR_HELD,
	MAX_DOOR_STATES
	}DOOR_STATE;

typedef enum
	{
	DOOR_UNLOCK=0x100,
	DOOR_OPEN,
	DOOR_CLOSE,
	DOOR_TIMER,
	MAX_DOOR_EVENTS,
	DOOR_ALARM
	}DOOR_EVENT;

typedef struct
	{
	UINT32 doorID;
	int opentime;
	DOOR_STATE state;
	int session;
	}DOOR_REC;

// pool info
// 4k per page
#define P_LINK_PAGES	1
#define P_DOOR_PAGES	1

typedef enum
	{
	P_LINK,
	P_DOOR,
	MAX_POOL_TYPES
	}POOL_TYPE;

// linked list info
typedef enum
	{
	DOOR_LIST,
	MAX_LIST_TYPES
	}INFO_LIST_TYPE;

#endif
