/*************************************************************

FILE:		doorMsgs.h

DESCRIPTION:	
This file contains message structures for door object. 

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
$Log: doorMsgs.h,v $
Revision 1.1  2006/06/26 18:03:17  bobfcsoft
statemachine

=======================================================

*************************************************************/

#ifndef _DOOR_MSGS_DEF
#define _DOOR_MSGS_DEF

#include "doorDefs.h"  // DOOR_EVENT defn

typedef struct
	{
	DOOR_EVENT token;	//UNLOCK, OPEN, CLOSE
	UINT32 doorID;
	}DOOR_EVENT_MSG;

typedef struct
	{
	DOOR_EVENT token;	//TIMER
	UINT32 doorID;
	int session;
	}DOOR_TIMER_MSG;

typedef struct
	{
	DOOR_EVENT token;	//ALARM
	UINT32 doorID;
	}DOOR_ALARM_MSG;

#endif
