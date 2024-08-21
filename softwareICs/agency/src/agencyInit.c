/*************************************************************

FILE:		agencyInit.c

DESCRIPTION:	
This file contains initialization code for agency. 

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
$Log: agencyInit.c,v $
Revision 1.2  2011/09/08 16:24:49  bobfcsoft
more portable arg processing

Revision 1.1  2007/07/27 14:10:49  bobfcsoft
new cvs file

Revision 1.3  2003/04/03 16:20:28  root
RedHat 7.x warning cleanup

Revision 1.2  2002/12/03 21:00:06  root
v2.0 compatible

Revision 1.1  2002/10/29 18:34:06  root
Initial revision

=======================================================

*************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "agencyMsgs.h"

#define _ALLOC extern
#include "agency.h"
#undef _ALLOC

/*  Prototypes  */
#include "agencyProto.h"
#include "loggerProto.h"
#include "simplProto.h"
#include "simplmiscProto.h" // for atoh

/*=========================================================
	initialize
=========================================================*/
void initialize(int argc, char **argv)
{
static char *fn="initialize";
int i;
int myslot;
char myName[20];
char logger_name[20];

// set defaults
globalMask=0xff;
myName[0]=0;
logger_name[0]=0;
agentPending=NULL;

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
			case 'n':
				if(*++p == 0) p++;
//				sprintf(myName,"%.19s",p);
				sprintf(myName,"%.19s",argv[++i]);

#if 0
				myslot=attachName(myName, 1024, NULL);
#endif
				myslot=name_attach(myName, NULL);
				if (myslot == -1)
					{
					printf("%s: Can't attach as %s\n",fn,myName);
					exit(0);
					}
				break;

			case 'l':
				if(*++p == 0) p++;
//				sprintf(logger_name,"%.19s",p);
				sprintf(logger_name,"%.19s",argv[++i]);
				break;

			case 'm':
//				if(*++p == 0) p++;
				p=argv[++i];
				globalMask=atoh(&p[2]);  // skip 0x
				break;

			default:
				printf("Bad command line switch `%c'\n", *p);
			} // end switch
		} // end if p
	} // end for i	

// if manditory name is not supplied show usage
if(myName[0] == 0)
	{
	myUsage();
	exit(0);
	}

// connect to logger
#if 0
logger_FCID = is_logger_upx(logger_name);
#endif
logger_ID = is_logger_upx(logger_name);

// align to topofList
head = &topofList;  // note this entry is wasted to simplify algorithm
head->next=head;
head->prev=head;

// defaults
agentPending=NULL;
nextRequestor=-1;

fcLogx(__FILE__, fn,
	0xff,
	AGENCY_MARK,
	"myName=<%s> myslot=%d",
	myName,
	myslot
	);

fcLogx(__FILE__, fn,
	0xff,
	AGENCY_MARK,
	"trace logger mask = 0x%04X",
	globalMask);

}// end initialize

/*===================================================
	myUsage - entry point
===================================================*/
void myUsage()
{
printf("====================== usage =====================\n");
printf(" usage for agency:\n");
printf("      agency -n <myName> <optionals>\n");
printf("      where optionals are:\n");
printf("        -m 0x<mask> - override default log mask\n");
printf("        -l <loggerName> - connect to trace logger\n");
printf("==================================================\n");
}// end myUsage
