/*************************************************************

FILE:		recvTesterUtils.c

DESCRIPTION:	
This file contains utility code for recvTester app.

AUTHOR:			R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2000, 2002 FCSoftware Inc. 

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

    If you discover a bug or add an enhancement here's how to reach us: 

	fcsoft@attcanada.ca
-----------------------------------------------------------------------
Revision history:
=======================================================
$Log: recvTesterUtils.c,v $
Revision 1.1  2008/04/28 18:00:22  bobfcsoft
new in CVS

Revision 1.3  2003/04/03 16:57:12  root
fixed RedHat 7.x warnings

Revision 1.2  2002/12/03 21:26:00  root
v2.0 compatible

Revision 1.1  2002/12/03 20:23:36  root
Initial revision

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "stimulatorMsgs.h"

#define _ALLOC extern
#include "recvTester.h"
#undef _ALLOC

#include "recvTesterProto.h"
#include "simplProto.h"
#include "loggerProto.h"
#include "simplmiscProto.h"

/*====================================================
	runtest - entry point
====================================================*/
int runtest(char *filename)
{
static char *fn="runtest";
char line[80];
char *p;
int rc=-1;
int step=1;

fcLogx(__FILE__, fn,
	globalMask,
	TESTER_FUNC_IO,
	"filename=<%s>",
	filename);

in_fp=fopen(filename,"r");

while(fgets(line,79,in_fp) != NULL)
	{
     	line[strlen(line)-1]=0; /* get rid of CR */
      	p=skipOverWhiteSpace(line);

	switch(line[0])
		{
		case 0:
		case '#':  // comment
			break;

		case 'S':  // sleep
			{
			int nsecs;

			nsecs=atoi(p);
printf("[%3d]: sleep for %d secs\n",step++,nsecs);
			sleep(nsecs);
			}
			break;

		case 'T':  // test string
			{
			char str[80];
			STIM_TEST_MSG *outMsg;

			sprintf(str,"%.79s",p);

printf("[%3d]: TEST str=<%s>\n",step++,str);

			outMsg = (STIM_TEST_MSG *)outArea;
			outMsg->token = STIM_TEST;
			sprintf(outMsg->str,"%s",str);

			Send(stimID, outArea, NULL, sizeof(STIM_TEST_MSG), MAX_MSG_SIZE);
			}
			break;

		default:
			break;
		} // end switch

	} // end while

if(in_fp != NULL) fclose(in_fp);

fcLogx(__FILE__, fn,
	globalMask,
	TESTER_FUNC_IO,
	"rc=%d",
	rc);

return(rc);

} // end runtest

/*=========================================
	skipOverWhiteSpace - entry point
=========================================*/
char *skipOverWhiteSpace(char *start)
{
char *p;

for(p=start; *p != 0 && *p != ' ' && *p != 0x09; p++);  // skip to whitespace
if(*p != 0)
	{
	*p=0;	// null terminate
	p++;
	for(; *p == ' ' || *p == 0x09; p++); // skip whitespace
	}

return(p);
}// end skipOverWhiteSpace
