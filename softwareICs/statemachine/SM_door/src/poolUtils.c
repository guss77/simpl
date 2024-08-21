/*************************************************************

FILE:		poolUtils.c

DESCRIPTION:	
This memory pool utilities for statemachine module. 

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
$Log: poolUtils.c,v $
Revision 1.1  2006/06/26 18:03:18  bobfcsoft
statemachine

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "statemachineMsgs.h"
#include "doorDefs.h"

#define _ALLOC extern
#include "door.h"
#include "statemachine.h"
#undef _ALLOC

//  Prototypes 
#include "doorProto.h"
#include "statemachineProto.h"
#include "loggerProto.h"
#include "simplProto.h"

/*=================================================
	pool_init - entry point
=================================================*/
int pool_init()
{
static char *fn="pool_init";
int i;
int j;
char *next;
int rc=0;

poolTable[P_LINK].bytes=sizeof(LINKED_LIST);
poolTable[P_DOOR].bytes=sizeof(DOOR_REC);

poolTable[P_LINK].pages=P_LINK_PAGES;
poolTable[P_DOOR].pages=P_DOOR_PAGES;

for(i=0; i<MAX_POOL_TYPES; i++)
	{
	rc+=poolTable[i].pages;

	poolTable[i].records=(poolTable[i].pages*4096)/poolTable[i].bytes;
	poolTable[i].index = (POOL_REC *)malloc(poolTable[i].records*sizeof(POOL_REC));

	if(poolTable[i].index == NULL)
		{
		return(-1);
		}

	poolTable[i].top = malloc(4096*poolTable[i].pages);
	if(poolTable[i].top == NULL)
		{
		return(-1);
		}

	for(j=0,next=poolTable[i].top; j<poolTable[i].records; j++, next+=poolTable[i].bytes)
		{
		poolTable[i].index[j].data=(char *)next;
		poolTable[i].index[j].flag=0;  // available
		} // end for records

	}// end for types

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"rc=%d",
	rc
	);

return(rc);

} // end pool_init

/*=================================================
	pool_malloc - entry point
=================================================*/
void *pool_malloc(int size)
{
static char *fn="pool_malloc";
int mypool;
int i;
void *rc=NULL;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"size=%d",
	size
	);

mypool=whichPool(size);
if(mypool != MAX_POOL_TYPES)
	{
	for(i=0; i<poolTable[mypool].records; i++)
		{
		if(poolTable[mypool].index[i].flag == 0)
			{
			poolTable[mypool].index[i].flag=1;
			rc=poolTable[mypool].index[i].data;
			break;
			}
		}
	}

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"rc=poolTable[%d].index[%d]=%X",
	mypool,
	i,
	rc
	);

return(rc);

} // end pool_malloc

/*=================================================
	pool_free - entry point
=================================================*/
void pool_free(void *ptr)
{
static char *fn="pool_free";
int i;
int j;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"ptr=%X",
	ptr
	);

for(i=0; i<MAX_POOL_TYPES; i++)
	{
	for(j=0; j<poolTable[i].records; j++)
		{
		if(poolTable[i].index[j].data == ptr)
			{
			poolTable[i].index[j].flag=0;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MARK,
	"freeing record %d",
	j
	);

			break;
			} //end if data
		}// end for j
	} // end for i

} // end pool_free

/*=================================================
	whichPool - entry point
=================================================*/
int whichPool(int size)
{
static char *fn="whichPool";
int i;
int rc=MAX_POOL_TYPES;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"size=%d",
	size
	);

for(i=0; i<MAX_POOL_TYPES; i++)
	{
	if(size == poolTable[i].bytes)
		{
		rc=i;
		break;
		}
	}

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"pool=%d",
	rc
	);

return(rc);

} // end whichPool

