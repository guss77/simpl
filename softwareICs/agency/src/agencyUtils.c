/*************************************************************

FILE:		agencyUtils.c

DESCRIPTION:	
This file contains utility code for agency app.

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
$Log: agencyUtils.c,v $
Revision 1.2  2008/08/11 21:21:40  bobfcsoft
wrapped message from requestor

Revision 1.1  2007/07/27 14:10:49  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 21:00:17  root
v2.0 compatible

Revision 1.1  2002/10/29 18:28:09  root
Initial revision

=======================================================

*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "agencyMsgs.h"
#define _ALLOC extern
#include "agency.h"
#undef _ALLOC

#include "agencyProto.h"
#include "loggerProto.h"
#include "simplProto.h"

/*=================================================
	queueMsg - entry point
=================================================*/
int queueMsg(char *sender, void *msg, int nbytes)
{
static char *fn="queueMsg";
Q_LINKED_LIST *newRec=NULL;
int rc=-1;

fcLogx(__FILE__, fn,
	globalMask,
	AGENCY_FUNC_IO,
       	"sender=%X nbytes=%d",
	sender,
	nbytes
	);

newRec=addToList();

if(newRec != NULL)
	{
	newRec->sender = sender;
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
int rc=-1;

fcLogx(__FILE__, fn,
	globalMask,
	AGENCY_FUNC_IO,
        "ding"
	);

thisOne=head->next;
if(thisOne != head)
	{
	replyToAgent(agent,
		thisOne->sender,
		thisOne->nbytes, 
		(char *)thisOne->msg);

	deleteFromList(thisOne);
	rc=1;
	}
else
	{
	fcLogx(__FILE__, fn,
		globalMask,
		AGENCY_FUNC_IO,
        	"no messages to dequeue"
		);
	agentPending = agent;
	}

fcLogx(__FILE__, fn,
	globalMask,
	AGENCY_FUNC_IO,
        "agentPending=%X rc=%d",
	agentPending,
	rc
	);

return(rc);

} // end dequeueMsg

/*=================================================
	replyToAgent - entry point
=================================================*/
int replyToAgent(char *agent, char *sender, int nbytes, char *msg)
{
static char *fn="replyToAgent";
int rc=-1;
AGENCY_WRAP_MSG *outMsg;

fcLogx(__FILE__, fn,
	globalMask,
	AGENCY_FUNC_IO,
       	"agent=%X",
	agent
	);

if(agent != NULL)
	{
	fcLogx(__FILE__, fn,
		globalMask,
		AGENCY_MISC,
        	"replying %d nbytes => agent=%X",
        	nbytes,
		agent
		);

	outMsg=(AGENCY_WRAP_MSG *)msg;
	outMsg->token = AGENCY_GOT_ONE;
//outMsg->nbytes = nbytes;
	outMsg->sender = sender;
//memcpy(&outMsg->mark,msg,nbytes);

	Reply(agent, msg, 8+nbytes);
	agentPending = NULL;
	rc=1;
	}

return(rc);

}// end replyToAgent

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
	AGENCY_FUNC_IO,
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
	AGENCY_FUNC_IO,
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
	AGENCY_FUNC_IO,
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
	AGENCY_FUNC_IO,
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
	AGENCY_FUNC_IO,
        "free link Address = <%X>",
        thisOne
	);

free(thisOne);

} // end deleteFromList
