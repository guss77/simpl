/*************************************************************

FILE:		fcBroadUtils.c

DESCRIPTION:	
This file contains some utility functions for
broadcaster softwareIC.

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
$Log: fcBroadUtils.c,v $
Revision 1.1  2007/07/27 14:13:04  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 21:12:33  root
v2.0 compatible

Revision 1.1  2002/10/30 15:58:58  root
Initial revision

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h> // killZombies stuff

#include "fcMgrMsgs.h"

#define _ALLOC extern
#include "fcBroadcaster.h"
#undef _ALLOC

/*  Prototypes  */
#include "fcBroadProto.h"
#include "loggerProto.h"
#include "simplProto.h"
#include "simplmiscProto.h"

int vcNameLocate(char *);

/*=================================================
	createLink - entry point
=================================================*/
LINKED_LIST *createLink()
{
static char *fn="createLink";
LINKED_LIST *new;

new = (LINKED_LIST *)malloc(sizeof(LINKED_LIST));

fcLogx(__FILE__, fn,
	globalMask,
	FCB_FUNC_IO,
        "new link Address = <%X>",
        new
	);

memset(new,0,sizeof(LINKED_LIST));
new->next = new;
new->prev = new;
return(new);
}/* end createLink*/

/*=================================================
	addToList - entry point
=================================================*/
LINKED_LIST *addToList()
{
static char *fn="addToList";
LINKED_LIST *new;
LINKED_LIST *tail;

fcLogx(__FILE__, fn,
	globalMask,
	FCB_FUNC_IO,
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
void deleteFromList(LINKED_LIST *thisOne)
{
static char *fn="deleteFromList";

(thisOne->prev)->next = thisOne->next;
(thisOne->next)->prev = thisOne->prev;

fcLogx(__FILE__, fn,
	globalMask,
	FCB_FUNC_IO,
        "free link Address = <%X>",
        thisOne
	);

free(thisOne);

} // end deleteFromList

/*==================================================
	registerMe - entry point
==================================================*/
int registerMe(char *name, pid_t myPid)
{
static char *fn="registerMe";
int subscriberID;
LINKED_LIST *newRec=NULL;
int rc=-1;

fcLogx(__FILE__, fn,
	globalMask,
	FCB_FUNC_IO,
        "name=<%s> pid=%d",
	name,
        myPid
	);

subscriberID=name_locate(name);
if(subscriberID != -1)
	{
	newRec=addToList();
	if(newRec != NULL)
		{
		newRec->subscriberID = subscriberID;
		newRec->subscriber_pid = myPid;
		rc=1;
		}
	}

fcLogx(__FILE__, fn,
	globalMask,
	FCB_FUNC_IO,
        "name=<%s> rc=%d",
        name,
	rc
	);

return(rc);

} // end registerMe

/*==================================================
	deregisterMe - entry point
==================================================*/
int deregisterMe(pid_t myPid)
{
static char *fn="deregisterMe";
LINKED_LIST *thisOne=NULL;
int rc=-1;

fcLogx(__FILE__, fn,
	globalMask,
	FCB_FUNC_IO,
        "pid=%d",
        myPid
	);

for(thisOne=head->next; thisOne != head; thisOne=thisOne->next)
	{
	if(thisOne->subscriber_pid == myPid)
		{
		deleteFromList(thisOne);
		rc=1;
		break;
		}
	}

fcLogx(__FILE__, fn,
	globalMask,
	FCB_FUNC_IO,
        "pid=<%d> rc=%d",
        myPid,
	rc
	);

return(rc);

} // end deregisterMe

/*==================================================
	broadcastTo - entry point
==================================================*/
void broadcastTo(char *msg, int nbytes)
{
static char *fn="broadcastTo";
LINKED_LIST *thisOne=NULL;
LINKED_LIST *nextOne=NULL;

fcLogx(__FILE__, fn,
	globalMask,
	FCB_FUNC_IO,
        "nbytes=%d",
        nbytes
	);

for(thisOne=head->next; thisOne != head; thisOne=nextOne)
	{
	nextOne=thisOne->next;
#if 0
	loadSend(msg,nbytes);
	if(sendMsgx(thisOne->subscriberID) == -1)
#endif
	if(Send(thisOne->subscriberID, msg, NULL, nbytes, 0))
		{
		fcLogx(__FILE__, fn,
			globalMask,
			FCB_MISC,
        		"unable to send to pid=%d at slot=%d",
        		thisOne->subscriber_pid,
			thisOne->subscriberID
			);

		deleteFromList(thisOne);
		}
	}	
} // end broadcastTo
