/*************************************************************

FILE:		doorInit.c

DESCRIPTION:	
This file contains initialization code for door module. 

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
$Log: doorInit.c,v $
Revision 1.2  2011/09/08 16:51:22  bobfcsoft
more portable arg processing

Revision 1.1  2006/06/26 18:03:18  bobfcsoft
statemachine

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#include "statemachineMsgs.h"

#define _ALLOC
#include "door.h"
#undef _ALLOC

#define _ALLOC extern
#include "statemachine.h"
#undef _ALLOC

//  Prototypes  
#include "doorProto.h"
#include "statemachineProto.h"
#include "loggerProto.h"
#include "simplProto.h"
#include "simplmiscProto.h"

/*=========================================================
	SM_init - entry point
=========================================================*/
void SM_init(int argc, char **argv)
{
static char *fn="SM_init";
int type;
int i;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"ding");


/*=========================================================
	process command line arguments
=========================================================*/
for (i=1; i<=argc; ++i) 
	{	
	char *p = argv[i];

	if (p == NULL) continue;

	if (*p == '-')
		{             
		switch (*++p)
			{
			case 'a':
				if(*++p == 0) p++;
//				sprintf(alarmName,"%.19s",p);
				sprintf(alarmName,"%.19s",argv[++i]);
				break;

			case 'f':
				if(*++p == 0) p++;
//				sprintf(infile,"%.127s",p);
				sprintf(infile,"%.127s",argv[++i]);
				break;

			default:
				break;
			}
		}
	}	

// locate the alarm process is delayed until needed
alarmID=-1;

for(type=0; type<MAX_LIST_TYPES; type++)
	{
switch(type)
	{
	case DOOR_LIST:
		doorInit(infile);
		break;

	default:
		break;
	}
	}// end for

fcLogx(__FILE__, fn,
	TRACE_MARK,
	TRACE_MARK,
	"infile=<%s>",
	infile);

fcLogx(__FILE__, fn,
	TRACE_MARK,
	TRACE_MARK,
	"alarmName=<%s>",
	alarmName);


}//end SM_init

/*=========================================================
	doorInit - entry point
=========================================================*/
void doorInit(char *infile)
{
static char *fn="doorInit";
int i;
int totalpages;

// align to topofList
for(i=0; i<MAX_LIST_TYPES; i++)
	{
	listHead[i] = &topofList[i];  // note this entry is wasted to simplify algorithm
	listHead[i]->data=NULL;
	listHead[i]->next=listHead[i];
	listHead[i]->prev=listHead[i];
	}

// setup memory pool
if((totalpages=pool_init()) == -1)
	{
	fcLogx(__FILE__, fn,
		TRACE_MARK,	// force it to log
		TRACE_MARK,
		"unable to allocate memory pools"
		);

	name_detach();
	exit(0);
	}
else
	{
	fcLogx(__FILE__, fn,
		TRACE_MARK,	// force it to log
		TRACE_MARK,
		"total memory in pools=%d pages (%d kbytes)",
		totalpages,
		totalpages*4	
		);
	}

// load in the default structures
loadData(infile);		// load data from infile

}// end doorInit

/*===================================================
	myUsage - entry point
===================================================*/
void myUsage()
{
printf("====================== usage =====================\n");
printf(" usage for statemachine:\n");
printf("      statemachine -n <myName> \n");
printf("         -f <file name>\n");
printf("         <optionals>\n");
printf("      where optionals are:\n");
printf("        -m <mask> - set log mask\n");
printf("        -l <loggerName> - connect to trace logger\n");
printf("==================================================\n");
}// end myUsage
