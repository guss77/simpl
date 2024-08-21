/*************************************************************

FILE:		doorUtils.c

DESCRIPTION:	
This file contains parsing logic for door records. 

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
$Log: doorUtils.c,v $
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

/*====================================================
	raiseAlarm - entry point
====================================================*/
int raiseAlarm(int mydoor)
{
static char *fn="raiseAlarm";
DOOR_ALARM_MSG *outMsg;
int sbytes;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MARK,
	"doorID=%d",mydoor);
		
if(alarmID == -1)
	alarmID=name_locate(alarmName);

outMsg=(DOOR_ALARM_MSG *)outArea;
outMsg->token=DOOR_ALARM;
outMsg->doorID=mydoor;
sbytes=sizeof(DOOR_ALARM_MSG);


fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MARK,
	"sending alarm to <%s> at %d",alarmName, alarmID);
		
Send(alarmID, outArea, inArea, sbytes, MAX_MSG_BUFFER_SIZE);

return(0);

}// end raiseAlarm

/*====================================================
	dumpTable - entry point
====================================================*/
int dumpTable()
{
static char *fn="dumpTable";
int i;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MARK,
	"ding");
		
for(i=0; i<MAX_LIST_TYPES; i++)
	{
	dumpRec(i);
	}

return(0);

}// end dumpTable

/*====================================================
	dumpRec - entry point
====================================================*/
int dumpRec(int thisList)
{
static char *fn="dumpRec";
LINKED_LIST *myRec;
LINKED_LIST *myHead=listHead[thisList];
int i;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MARK,
	"list type = %d",thisList);
		
for(myRec=myHead->next,i=1; myRec != myHead; myRec=myRec->next,i++)
	{
	showRec(thisList, myRec->data);
	}

return(0);

}// end dumpRec

/*====================================================
	deleteRec - entry point
====================================================*/
void deleteRec(int type, int myID)
{
static char *fn="deleteRec";

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"ding");

switch(type)
	{
	case DOOR_LIST:
		deleteDoor(myID);
		break;

	default:
		break;
	}
}// end deleteRec


/*====================================================
	deleteDoor - entry point
====================================================*/
int deleteDoor(int doorID)
{
static char *fn="deleteDoor";
LINKED_LIST *doorHead;
LINKED_LIST *myRec;
DOOR_REC *doorRec;
int rc=0;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MISC,
	"DELETE existing record");

doorHead=listHead[DOOR_LIST];

for(myRec=doorHead->next; myRec != doorHead; myRec=myRec->next)
	{
	doorRec=(DOOR_REC *)myRec->data;

	if(doorRec->doorID == doorID)
		{
		deleteFromList(myRec);
		break;
		}
	} // end for

return(rc);

} // end delete door


/*====================================================
	addNewRec - entry point
====================================================*/
int addNewRec(int type, char *data, int nbytes)
{
static char *fn="addNewRec";

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"ding");

switch(type)
	{
	case DOOR_LIST:
		addNewDoor(data, nbytes);
		break;

	default:
		break;
	}

return(0);

} // end addNewRec

/*====================================================
	addNewDoor - entry point
====================================================*/
int addNewDoor(char *data, int nbytes)
{
static char *fn="addNewDoor";
LINKED_LIST *doorHead;
LINKED_LIST *new;
void *rec;
int rc;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MARK,
	"ding"
	);
		
doorHead=listHead[DOOR_LIST];

rec=createDataRec(nbytes);

new=addToList(doorHead, rec);
memcpy(rec,(void *)data, nbytes);

showDoorRec(rec);

return(rc);

} // end addNewDoor

/*====================================================
	overwriteRec - entry point
====================================================*/
int overwriteRec(int type, char *data, int nbytes)
{
static char *fn="overwriteRec";

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"ding");

switch(type)
	{
	case DOOR_LIST:
		overwriteDoor(data, nbytes);
		break;

	default:
		break;
	}

return(0);

} // end overwriteRec

/*====================================================
	overwriteDoor - entry point
====================================================*/
int overwriteDoor(char *data, int nbytes)
{
static char *fn="overwriteDoor";
void *rec;
DOOR_REC *doorRec;
int rc;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MARK,
	"ding"
	);

doorRec=(DOOR_REC *)data;

rec = findDoor(doorRec->doorID);
if(rec != NULL)
	{
	DOOR_REC *newRec;

	newRec=(DOOR_REC *)rec;
	newRec->opentime=doorRec->opentime;
	}	

showDoorRec(rec);

return(rc);

} // end overwriteDoor

/*====================================================
	stateToStr - entry point
====================================================*/
char *stateToStr(int state)
{
//static char *fn="stateToStr";
static char rc[64];

rc[0]=0;
switch(state)
	{
	case DOOR_CLOSED_LOCKED:
		sprintf(rc,"CLOSED_LOCKED");
		break;

	case DOOR_CLOSED_UNLOCKED:
		sprintf(rc,"CLOSED_UNLOCKED");
		break;

	case DOOR_OPENED:
		sprintf(rc,"OPENED");
		break;

	case DOOR_HELD:
		sprintf(rc,"HELD");
		break;

	default:
		break; 
	}

return(rc);

} // end stateToStr

/*====================================================
	findDoor - entry point
====================================================*/
void *findDoor(int doorID)
{
static char *fn="findDoor";
LINKED_LIST *myRec;
LINKED_LIST *myHead=listHead[DOOR_LIST];
int i;
void *rc=NULL;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MARK,
	"list type = DOOR");
		
for(myRec=myHead->next,i=1; myRec != myHead; myRec=myRec->next,i++)
	{
	DOOR_REC *doorRec;

	doorRec=(DOOR_REC *)myRec->data;

	if(doorRec->doorID == doorID)
		{
		rc=myRec->data;
		break;
		}
	}

return(rc);

}// end findDoor

/*====================================================
	showRec - entry point
====================================================*/
int showRec(int thisList, void *dataBuf)
{
static char *fn="showRec";

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MARK,
	"list=%d",
	thisList);

switch(thisList)
	{
	case DOOR_LIST:
		showDoorRec(dataBuf);
		break;

	default:
		break;	
	} // end switch

return(0);
		
} // end showRec

/*====================================================
	showDoorRec - entry point
====================================================*/
int showDoorRec(void *myRec)
{
static char *fn="showDoor";
DOOR_REC *doorRec;

doorRec=(DOOR_REC *)myRec;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MARK,
	"ID=%d opentime=%d sec state=%s session=%d",
	doorRec->doorID,
	doorRec->opentime,
	stateToStr(doorRec->state),
	doorRec->session);

return(0);
		
} // end showDoorRec

