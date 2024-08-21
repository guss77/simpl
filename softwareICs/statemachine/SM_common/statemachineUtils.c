/*************************************************************

FILE:		statemachineUtils.c

DESCRIPTION:	
This file contains utilities for statemachine module. 

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
$Log: statemachineUtils.c,v $
Revision 1.1  2006/06/26 18:03:16  bobfcsoft
statemachine

=======================================================

*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "statemachineMsgs.h"

#define _ALLOC extern
#include "statemachine.h"
#undef _ALLOC

//  Prototypes
#include "statemachineProto.h"
#include "loggerProto.h"
#include "simplProto.h"

/*=================================================
	createLink - entry point
=================================================*/
LINKED_LIST *createLink()
{
static char *fn="createLink";
LINKED_LIST *new;

new = (LINKED_LIST *)pool_malloc(sizeof(LINKED_LIST));

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
        "New link Address = <%X>",
        new
	);

new->next = new;
new->prev = new;
new->data = NULL;

return(new);
}// end createLink

/*=================================================
	addToList - entry point
=================================================*/
LINKED_LIST *addToList(LINKED_LIST *head, void *mydata)
{
LINKED_LIST *new;
LINKED_LIST *tail;

new = createLink();

if(new != NULL)
	{
	new->data = mydata;

	tail=head->prev;

	new->prev=tail;
	new->next=head;
	tail->next=new;
	head->prev=new;
    	}

return(new);
} // end addToList

/*=================================================
	deleteFromList - entry point
=================================================*/
void deleteFromList(LINKED_LIST *thisOne)
{
static char *fn="deleteFromList";

deleteDataRec(thisOne->data);

(thisOne->prev)->next = thisOne->next;
(thisOne->next)->prev = thisOne->prev;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
        "free link Address = <%X>",
        thisOne
	);

pool_free(thisOne);

} // end deleteFromList

/*=================================================
	createDataRec - entry point
=================================================*/
void *createDataRec(int nbytes)
{
static char *fn="createDataRec";
void *new;

new = (void *)pool_malloc(nbytes);
if(new != NULL)
	{
	memset((void *)new, 0, nbytes);

	fcLogx(__FILE__, fn,
		globalMask,
		TRACE_MISC,
        	"new dataRec addr = <%X> size = %d bytes",
        	new,
		nbytes
		);
	}// end if new

return(new);
}// end createDataRec

/*=================================================
	deleteDataRec - entry point
=================================================*/
void deleteDataRec(void *dataRec)
{
static char *fn="deleteDataRec";

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MISC,
        "free dataRec Address = <%X>",
        dataRec
	);

pool_free(dataRec);

}// end deleteDataRec

/*=================================================
	loadData - entry point
=================================================*/
void loadData(char *filename)
{
static char *fn="loadData";
FILE *fp;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MISC,
	"file=<%s>",
	filename
	);

fp=fopen(filename,"r");
if(fp == NULL)
	{
	fcLogx(__FILE__, fn,
		TRACE_MISC,
		TRACE_MISC,
		"file <%s> does not exist",
		filename);
	}
else
	{
	char line[80];
	char *p;

	while(fgets(line,79,fp) != NULL)
		{
     		line[strlen(line)-1]=0; /* get rid of CR */
      		p=skipOverWhiteSpace(line);

		switch(line[0])
			{
			case 'R':  // RESET
				parseRESET(fp);
				break;

			case 'A':  // ADD
				parseADD(fp);
				break;

			case 'D':  // DELETE
				parseDELETE(fp);
				break;

			case 'O':  // OVERWRITE 
				parseOVERWRITE(fp);
				break;

			default:
				break;
			} // end switch
		} // end while

	fclose(fp);

	} // end else fp not NULL

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"done");

}// end loadData

/*=========================================
	skipOverWhiteSpace - entry point
=========================================*/
char *skipOverWhiteSpace(char *start)
{
char *p;

for(p=start; *p != 0 && *p != ' ' && *p != 0x09; p++);  // skip to whitespace
if(*p != 0)
	{
	for(; *p == ' ' || *p == 0x09; p++); // skip whitespace
	}

return(p);
}// end skipOverWhiteSpace
