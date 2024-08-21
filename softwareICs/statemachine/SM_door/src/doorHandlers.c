/*************************************************************

FILE:		doorHandlers.c

DESCRIPTION:	
This file contains event handlers for door statemachine. 

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
$Log: doorHandlers.c,v $
Revision 1.1  2006/06/26 18:03:18  bobfcsoft
statemachine

=======================================================
*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "doorDefs.h"
#include "doorMsgs.h"

#define _ALLOC extern
#include "door.h"
#include "statemachine.h"
#undef _ALLOC

#include "doorProto.h"
#include "statemachineProto.h"
#include "simplProto.h"
#include "simplmiscProto.h"
#include "loggerProto.h"


/*===============================================
	hndlEvents - entry point
===============================================*/
void hndlEvents(char *sender, int token)
{
static char *fn="hndlEvents";

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"token=%d(0x%X)",
	token,
	token);

switch(token)
	{
	case DOOR_CLOSE:
		{
		DOOR_EVENT_MSG *inMsg;
		void *doorRec;

		Reply(sender,NULL,0);

		inMsg=(DOOR_EVENT_MSG *)inArea;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"CLOSE ID=%d",
	inMsg->doorID
	);
		doorRec=findDoor(inMsg->doorID);
	
		hndlCLOSE(doorRec);
		}
		break;

	case DOOR_OPEN:
		{
		DOOR_EVENT_MSG *inMsg;
		void *doorRec;

		Reply(sender,NULL,0);

		inMsg=(DOOR_EVENT_MSG *)inArea;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"OPEN ID=%d",
	inMsg->doorID
	);
		doorRec=findDoor(inMsg->doorID);
	
		hndlOPEN(doorRec);
		}
		break;

	case DOOR_UNLOCK:
		{
		DOOR_EVENT_MSG *inMsg;
		void *doorRec;

		Reply(sender,NULL,0);

		inMsg=(DOOR_EVENT_MSG *)inArea;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"UNLOCK ID=%d",
	inMsg->doorID
	);
		doorRec=findDoor(inMsg->doorID);
	
		hndlUNLOCK(doorRec);
		}
		break;

	case DOOR_TIMER:
		{
		DOOR_TIMER_MSG *inMsg;
		void *doorRec;

		Reply(sender,NULL,0);

		inMsg=(DOOR_TIMER_MSG *)inArea;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"TIMER ID=%d session=%d",
	inMsg->doorID,
	inMsg->session
	);
		doorRec=findDoor(inMsg->doorID);
	
		hndlTIMER(doorRec, inMsg->session);
		}
		break;

	default:
		fcLogx(__FILE__, fn,
			TRACE_MARK,
			TRACE_MARK,
			"unknown token=%d",token);
		break;
	} // end switch

} // end hndlEvents

/*===============================================
	hndlCLOSE - entry point
===============================================*/
void hndlCLOSE(void *myRec)
{
static char *fn="hndlCLOSE";
DOOR_REC *doorRec;

doorRec=(DOOR_REC *)myRec;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"incoming state[%d]=%s",
	doorRec->doorID,
	stateToStr(doorRec->state)
	);

switch(doorRec->state)
	{
	case DOOR_CLOSED_LOCKED:
		fcLogx(__FILE__, fn,
			TRACE_MARK,
			TRACE_MARK,
			"door ID=%d already CLOSED and LOCKED",doorRec->doorID);
		break;
		
	case DOOR_CLOSED_UNLOCKED:
		fcLogx(__FILE__, fn,
			TRACE_MARK,
			TRACE_MARK,
			"door ID=%d already CLOSED now reLOCKED",doorRec->doorID);
		doorRec->state=DOOR_CLOSED_LOCKED;
		break;
		
	case DOOR_OPENED:
		doorRec->state=DOOR_CLOSED_LOCKED;
		break;
		
	case DOOR_HELD:
		doorRec->state=DOOR_CLOSED_LOCKED;
		break;
		
	default:
		fcLogx(__FILE__, fn,
			TRACE_MARK,
			TRACE_MARK,
			"unknown state=%d",doorRec->state);
		break;
	} // end switch

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"new state[%d]=%s",
	doorRec->doorID,
	stateToStr(doorRec->state)
	);


} // end hndlCLOSE

/*===============================================
	hndlOPEN - entry point
===============================================*/
void hndlOPEN(void *myRec)
{
static char *fn="hndlOPEN";
DOOR_REC *doorRec;

doorRec=(DOOR_REC *)myRec;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"incoming state[%d]=%s",
	doorRec->doorID,
	stateToStr(doorRec->state)
	);

switch(doorRec->state)
	{
	case DOOR_CLOSED_LOCKED:
		fcLogx(__FILE__, fn,
			TRACE_MARK,
			TRACE_MARK,
			"door ID=%d forced OPEN",doorRec->doorID);
		doorRec->state=DOOR_OPENED;
		break;
		
	case DOOR_CLOSED_UNLOCKED:
		doorRec->state=DOOR_OPENED;
		break;
		
	case DOOR_OPENED:
		fcLogx(__FILE__, fn,
			TRACE_MARK,
			TRACE_MARK,
			"door ID=%d already OPEN",doorRec->doorID);
		doorRec->state=DOOR_OPENED;
		break;
		
	case DOOR_HELD:
		fcLogx(__FILE__, fn,
			TRACE_MARK,
			TRACE_MARK,
			"door ID=%d already HELD OPEN",doorRec->doorID);
		doorRec->state=DOOR_HELD;
		break;
		
	default:
		fcLogx(__FILE__, fn,
			TRACE_MARK,
			TRACE_MARK,
			"unknown state=%d",doorRec->state);
		break;
	} // end switch

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"new state[%d]=%s",
	doorRec->doorID,
	stateToStr(doorRec->state)
	);


} // end hndlOPEN

/*===============================================
	hndlUNLOCK - entry point
===============================================*/
void hndlUNLOCK(void *myRec)
{
static char *fn="hndlUNLOCK";
DOOR_REC *doorRec;

doorRec=(DOOR_REC *)myRec;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"incoming state[%d]=%s",
	doorRec->doorID,
	stateToStr(doorRec->state)
	);

switch(doorRec->state)
	{
	case DOOR_CLOSED_LOCKED:
		doorRec->state=DOOR_CLOSED_UNLOCKED;
		doorRec->session++;
		break;
		
	case DOOR_CLOSED_UNLOCKED:
		doorRec->state=DOOR_CLOSED_UNLOCKED;
		break;
		
	case DOOR_OPENED:
		fcLogx(__FILE__, fn,
			TRACE_MARK,
			TRACE_MARK,
			"UNLOCK occurred on an OPEN door ID=%d",doorRec->doorID);
		doorRec->state=DOOR_OPENED;
		break;
		
	case DOOR_HELD:
		fcLogx(__FILE__, fn,
			TRACE_MARK,
			TRACE_MARK,
			"UNLOCK occurred on an HELD door ID=%d",doorRec->doorID);
		break;
		
	default:
		fcLogx(__FILE__, fn,
			TRACE_MARK,
			TRACE_MARK,
			"unknown state=%d",doorRec->state);
		break;
	} // end switch

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"new state[%d]=%s",
	doorRec->doorID,
	stateToStr(doorRec->state)
	);

} // end hndlUNLOCK

/*===============================================
	hndlTIMER - entry point
===============================================*/
void hndlTIMER(void *myRec, int mysession)
{
static char *fn="hndlTIMER";
DOOR_REC *doorRec;

doorRec=(DOOR_REC *)myRec;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"incoming state[%d]=%s",
	doorRec->doorID,
	stateToStr(doorRec->state)
	);

switch(doorRec->state)
	{
	case DOOR_CLOSED_LOCKED:
		fcLogx(__FILE__, fn,
			TRACE_MARK,
			TRACE_MARK,
			"TIMER occurred on a CLOSED door ID=%d",doorRec->doorID);
		break;
		
	case DOOR_CLOSED_UNLOCKED:
		fcLogx(__FILE__, fn,
			TRACE_MARK,
			TRACE_MARK,
			"TIMER occurred on a CLOSED door ID=%d",doorRec->doorID);
		doorRec->state=DOOR_CLOSED_UNLOCKED;
		break;
		
	case DOOR_OPENED:
		if(mysession == doorRec->session)
			{
			doorRec->state=DOOR_HELD;
			raiseAlarm(doorRec->doorID);
			}
		else
			{
		fcLogx(__FILE__, fn,
			TRACE_MARK,
			TRACE_MARK,
			"TIMER occurred on an OPEN door ID=%d different session %d",doorRec->doorID, mysession);
		doorRec->state=DOOR_OPENED;
			}
		break;
		
	case DOOR_HELD:
		fcLogx(__FILE__, fn,
			TRACE_MARK,
			TRACE_MARK,
			"TIMER occurred on an HELD door ID=%d different session %d",doorRec->doorID, mysession);
		break;
		
	default:
		fcLogx(__FILE__, fn,
			TRACE_MARK,
			TRACE_MARK,
			"unknown state=%d",doorRec->state);
		break;
	} // end switch

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"new state[%d]=%s",
	doorRec->doorID,
	stateToStr(doorRec->state)
	);

} // end hndlTIMER

