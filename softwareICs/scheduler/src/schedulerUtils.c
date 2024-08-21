/*************************************************************

FILE:		schedulerUtils.c

DESCRIPTION:	
This file contains utility code for scheduler app.

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
$Log: schedulerUtils.c,v $
Revision 1.1  2006/06/19 22:32:45  bobfcsoft
new files

=======================================================

*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

#include "schedulerMsgs.h"
#define _ALLOC extern
#include "scheduler.h"
#undef _ALLOC

#include "schedulerProto.h"
#include "loggerProto.h"
#include "simplProto.h"

/*==================================================
	fetchRecord - entry point
==================================================*/
int fetchRecord(int count)
{
static char *fn="fetchRecorD";
Q_LINKED_LIST *thisOne=NULL;
SCHEDULE_THIS_MSG *schedPtr;
VIEW_MSG *outMsg;
int i;
int rc=-1;

fcLogx(__FILE__, fn,
	globalMask,
	SCHEDULER_FUNC_IO,
        "ding"
	);


outMsg=(VIEW_MSG *)outArea;
outMsg->token=VIEW_NEXT;
outMsg->count=-1;

for(thisOne=head->next, i=0; thisOne != head; thisOne=thisOne->next, i++)
	{
	if(i == count)
		{
		schedPtr=(SCHEDULE_THIS_MSG *)thisOne->msg;

		outMsg->count=count;
		outMsg->stamp=schedPtr->stamp;
		outMsg->flags=schedPtr->flags;
		outMsg->nbytes=schedPtr->nbytes;

		rc=1;
		break;
		} // end if i

	} // end for

fcLogx(__FILE__, fn,
	globalMask,
	SCHEDULER_FUNC_IO,
        "rc=%d", rc
	);

return(rc);

} // end fetchRecord

/*==================================================
	checkForExpired - entry point
==================================================*/
int checkForExpired()
{
static char *fn="chk4expired";
Q_LINKED_LIST *thisOne=NULL;
SCHEDULE_THIS_MSG *schedPtr;
time_t now;
struct tm        *sched;
int i;
int rc=-1;

fcLogx(__FILE__, fn,
	globalMask,
	SCHEDULER_FUNC_IO,
        "ding"
	);

now=time(NULL);

for(thisOne=head->next, i=0; thisOne != head; thisOne=thisOne->next, i++)
	{
	schedPtr=(SCHEDULE_THIS_MSG *)thisOne->msg;

	if(schedPtr->stamp <  now )
		{
		schedPtr->flags |= SCHEDULER_EXPIRED;
		rc=1;
		}

	sched = localtime ((time_t *) &schedPtr->stamp);

	fcLogx(__FILE__, fn,
		globalMask,
		SCHEDULER_FUNC_IO,
        	"message %d scheduled at %s flags=0x%X",
		i,
		asctime(sched),
		schedPtr->flags
		);

	} // end for

return(rc);

} // end checkForExpired

/*==================================================
	newStamp - entry point
==================================================*/
time_t newStamp(int offset, UINT32 flags)
{
static char *fn="newStamp";
time_t now;
time_t new;
struct tm        *midnight;
int fulloffset;

fcLogx(__FILE__, fn,
	globalMask,
	SCHEDULER_FUNC_IO,
        "ding"
	);

if(flags & SCHEDULER_DAILY)
	fulloffset=86400+offset;
else
if(flags & SCHEDULER_WEEKLY)
	fulloffset=(86400*7)+offset;

now=time(NULL);
midnight = localtime (&now);
midnight->tm_hour=0;
midnight->tm_min=0;
midnight->tm_sec=0;

new=mktime(midnight)+fulloffset;  // next midnight + offset

fcLogx(__FILE__, fn,
	globalMask,
	SCHEDULER_FUNC_IO,
      	"new stamp %s",
	ctime(&new)
	);

return(new);

} // end newStamp

/*=================================================
	queueMsg - entry point
=================================================*/
int queueMsg(void *msg, int nbytes)
{
static char *fn="queueMsg";
Q_LINKED_LIST *newRec=NULL;
int rc=-1;

fcLogx(__FILE__, fn,
	globalMask,
	SCHEDULER_FUNC_IO,
       	"nbytes=%d",
	nbytes
	);

newRec=addToList();

if(newRec != NULL)
	{
	newRec->nbytes = nbytes;
	newRec->msg = msg;
	rc=1;
	}

return(rc);
}// end queueMsg

/*==================================================
	dequeueMsg - entry point
==================================================*/
int dequeueMsg(char *agent)
{
static char *fn="dequeueMsg";
Q_LINKED_LIST *thisOne=NULL;
SCHEDULE_THIS_MSG *schedPtr;
int i;
int rc=-1;

fcLogx(__FILE__, fn,
	globalMask,
	SCHEDULER_FUNC_IO,
        "ding"
	);

for(thisOne=head->next, i=0; thisOne != head; thisOne=thisOne->next, i++)
	{
	schedPtr=(SCHEDULE_THIS_MSG *)thisOne->msg;

	if(schedPtr->flags & SCHEDULER_EXPIRED)
		{
		int rbytes;

		rbytes = schedPtr->nbytes;
		memcpy(outArea,&schedPtr->mark,rbytes);
		Reply(agent, outArea, rbytes);

fcLogx(__FILE__, fn,
	globalMask,
	SCHEDULER_FUNC_IO,
        "reply %d bytes to agent 0x%X",
	rbytes,
	agent
	);

fcLogx(__FILE__, fn,
	globalMask,
	SCHEDULER_FUNC_IO,
        "outArea 0x%X-%X-%X-%X",
	outArea[0],
	outArea[1],
	outArea[2],
	outArea[3]
	);

		agentPending=NULL;

		if(schedPtr->flags & SCHEDULER_DAILY || schedPtr->flags & SCHEDULER_WEEKLY)
			{
			schedPtr->stamp=newStamp(schedPtr->offset,schedPtr->flags);
			schedPtr->flags &= ~SCHEDULER_EXPIRED;
			}
		else
			{
			deleteFromList(thisOne);
			}
		rc=1;
		break;
		} // end if flags
	} // end for

if(rc == -1)
	{
	fcLogx(__FILE__, fn,
		globalMask,
		SCHEDULER_FUNC_IO,
        	"no messages to dequeue"
		);
	agentPending = agent;
	}

fcLogx(__FILE__, fn,
	globalMask,
	SCHEDULER_FUNC_IO,
        "agentPending=%X rc=%d",
	agentPending,
	rc
	);

return(rc);

} // end dequeueMsg


/*=================================================
	createMsg - entry point
=================================================*/
void *createMsg(int nbytes)
{
static char *fn="createMsg";
void *new;

new = (void *)malloc(nbytes);

fcLogx(__FILE__, fn,
	globalMask,
	SCHEDULER_FUNC_IO,
        "new msg Address = <%X>",
        new
	);

return(new);
}/* end createMsg*/

/*=================================================
	destroyMsg - entry point
=================================================*/
void destroyMsg(void *msg)
{
static char *fn="destroyMsg";

fcLogx(__FILE__, fn,
	globalMask,
	SCHEDULER_FUNC_IO,
        "freeing msg at <%X>",
        msg
	);

free(msg);

}/* end destroyMsg*/

/*=================================================
	createLink - entry point
=================================================*/
Q_LINKED_LIST *createLink()
{
static char *fn="createLink";
Q_LINKED_LIST *new;

new = (Q_LINKED_LIST *)malloc(sizeof(Q_LINKED_LIST));

fcLogx(__FILE__, fn,
	globalMask,
	SCHEDULER_FUNC_IO,
        "new link Address = <%X>",
        new
	);

memset(new,0,sizeof(Q_LINKED_LIST));
new->next = new;
new->prev = new;
return(new);
}/* end createLink*/

/*=================================================
	addToList - entry point
=================================================*/
Q_LINKED_LIST *addToList()
{
static char *fn="addToList";
Q_LINKED_LIST *new;
Q_LINKED_LIST *tail;

fcLogx(__FILE__, fn,
	globalMask,
	SCHEDULER_FUNC_IO,
       	"ding"
	);

new = createLink();

if(new != NULL)
	{
	tail=head->prev;

	new->prev=tail;
	new->next=head;
	tail->next=new;
	head->prev=new;
    	}

return(new);
} /* end addToList */

/*=================================================
	deleteFromList - entry point
=================================================*/
void deleteFromList(Q_LINKED_LIST *thisOne)
{
static char *fn="deleteFromList";

(thisOne->prev)->next = thisOne->next;
(thisOne->next)->prev = thisOne->prev;

destroyMsg(thisOne->msg);

fcLogx(__FILE__, fn,
	globalMask,
	SCHEDULER_FUNC_IO,
        "free link Address = <%X>",
        thisOne
	);

free(thisOne);

} // end deleteFromList
