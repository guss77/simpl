/*************************************************************

FILE:		doorParsers.c

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
$Log: doorParsers.c,v $
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


/*=================================================
	skipBlock - entry point
=================================================*/
void skipBlock(FILE *fp)
{
static char *fn="skipBlock";
char line[80];

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MARK,
	"ding"
	);

while(fgets(line,79,fp) != NULL)
	{
	if(line[0] == 'Z') break;
	}// end while

}// end skipBlock

/*=================================================
	parseRESET - entry point
=================================================*/
void parseRESET(FILE *fp)
{
static char *fn="parseRESET";
char line[80];
char *p;
int x_it=0;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MARK,
	"ding"
	);

while(fgets(line,79,fp) != NULL)
	{
     	line[strlen(line)-1]=0; /* get rid of CR */
      	p=skipOverWhiteSpace(line);

	switch(line[0])
		{
		case 'D':	// DOOR
			{
			LINKED_LIST *doorHead;
			LINKED_LIST *myRec;

			doorHead=listHead[DOOR_LIST];

			for(myRec=doorHead->next; myRec != doorHead; myRec=myRec->next)
				{
				deleteFromList(myRec);
				} // end for

			}
			break;
		
		case 'Z':
			x_it=1;
			break;

		default:
			break;
		} // end switch
	if(x_it == 1) break;
	} // end while


}// end parseRESET

/*=================================================
	parseDELETE - entry point
=================================================*/
void parseDELETE(FILE *fp)
{
static char *fn="parseDELETE";
char line[80];
char *p;
int x_it=0;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MARK,
	"ding"
	);

while(fgets(line,79,fp) != NULL)
	{
     	line[strlen(line)-1]=0; /* get rid of CR */
      	p=skipOverWhiteSpace(line);

	switch(line[0])
		{
		case 'D':	// DOOR
			{
			DOOR_REC *doorRec;

			parseDoor(fp);

			doorRec=(DOOR_REC *)dataArea;
			deleteDoor(doorRec->doorID);

			x_it=1;
			}
			break;

		default:
			skipBlock(fp);
			x_it=1;
			break;
		} // end switch
        if(x_it == 1) break;
	} // end while


}// end parseDELETE

/*=================================================
	parseADD - entry point
=================================================*/
void parseADD(FILE *fp)
{
static char *fn="parseADD";
char line[80];
char *p;
int x_it=0;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MARK,
	"ding"
	);

while(fgets(line,79,fp) != NULL)
	{
     	line[strlen(line)-1]=0; /* get rid of CR */
      	p=skipOverWhiteSpace(line);

	switch(line[0])
		{
		case 'D':	// DOOR
			{
			parseDoor(fp);

			addNewDoor(dataArea, sizeof(DOOR_REC));

			x_it=1;
			}
			break;

		default:
			skipBlock(fp);
			x_it=1;
			break;
		} // end switch
        if(x_it == 1) break;
	} // end while


}// end parseADD

/*=================================================
	parseOVERWRITE - entry point
=================================================*/
void parseOVERWRITE(FILE *fp)
{
static char *fn="parseOW";
char line[80];
char *p;
int x_it=0;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_MARK,
	"ding"
	);

while(fgets(line,79,fp) != NULL)
	{
     	line[strlen(line)-1]=0; /* get rid of CR */
      	p=skipOverWhiteSpace(line);

	switch(line[0])
		{
		case 'D':	// DOOR
			{
			parseDoor(fp);

			overwriteDoor(dataArea,sizeof(DOOR_REC));

			x_it=1;
			}
			break;

		default:
			skipBlock(fp);
			x_it=1;
			break;
		} // end switch
        if(x_it == 1) break;
	} // end while


}// end parseOVERWRITE

/*====================================================
	parseDoor - entry point
====================================================*/
int parseDoor(FILE *fp)
{
static char *fn="parseDoor";
char line[80];
char *p;
DOOR_REC *doorRec;
int x_it=0;
int rc=0;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"ding");

memset ( dataArea
       , 0x00
       , 8192
       );

doorRec=(DOOR_REC *)dataArea;

while(fgets(line,79,fp) != NULL)
	{
     	line[strlen(line)-1]=0; /* get rid of CR */
      	p=skipOverWhiteSpace(line);

	switch(line[0])
		{
		case 'I':	// ID
			doorRec->doorID = atoi(p);

			fcLogx(__FILE__, fn,
				globalMask,
				TRACE_MISC,
				"doorID: %d",
				doorRec->doorID);
			break;

		case 'o':	// opentime
			doorRec->opentime = atoi(p);

			fcLogx(__FILE__, fn,
				globalMask,
				TRACE_MISC,
				"opentime: %d sec",
				doorRec->opentime);
			break;

		case 'Z':
			x_it=1;
			break;

		default:
			break;
		}

	if(x_it == 1) break;
	} // end while

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"rc=%d",
	rc);

return(rc);

} // end parseDoor
