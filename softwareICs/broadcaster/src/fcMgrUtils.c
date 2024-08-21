/*************************************************************

FILE:		fcMgrUtils.c

DESCRIPTION:	
This file contains some utility code for
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
$Log: fcMgrUtils.c,v $
Revision 1.2  2009/04/14 15:51:07  bobfcsoft
cleanup

Revision 1.1  2007/07/27 14:13:04  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 21:13:18  root
v2.0 compatible

Revision 1.1  2002/10/30 15:59:28  root
Initial revision
=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "fcMgrMsgs.h"

#define _ALLOC extern
#include "fcMgr.h"
#undef _ALLOC

#include "fcMgrProto.h"
#include "simplProto.h"
#include "loggerProto.h"
#include "simplmiscProto.h"  // for atoh

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
	FC_MGR_FUNC_IO,
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

/*=================================================
	dequeueMsg - entry point
=================================================*/
int dequeueMsg(char *replyToMe)
{
static char *fn="dequeueMsg";
Q_LINKED_LIST *thisOne;
int rc=-1;

fcLogx(__FILE__, fn,
	globalMask,
	FC_MGR_FUNC_IO,
       	"replyToMe=%X",
	replyToMe
	);

if(replyToMe != NULL)
	{
	thisOne=head->next;
	if(thisOne != head)
		{
		fcLogx(__FILE__, fn,
			globalMask,
			FC_MGR_MISC,
        		"replying %d nbytes => %X",
        		thisOne->nbytes,
			replyToMe
			);

		Reply(replyToMe, thisOne->msg, thisOne->nbytes);
		deleteFromList(thisOne);
		rc=1;
		}
	}

return(rc);

}// end dequeueMsg

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
	FC_MGR_FUNC_IO,
        "new msg Address = <%X>",
        new
	);

return(new);
}/* end createMsg*/

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
	FC_MGR_FUNC_IO,
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
	FC_MGR_FUNC_IO,
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

fcLogx(__FILE__, fn,
	globalMask,
	FC_MGR_FUNC_IO,
        "free msg = <%X>",
        thisOne->msg
	);

free(thisOne->msg);

fcLogx(__FILE__, fn,
	globalMask,
	FC_MGR_FUNC_IO,
        "free link Address = <%X>",
        thisOne
	);

free(thisOne);

} // end deleteFromList
