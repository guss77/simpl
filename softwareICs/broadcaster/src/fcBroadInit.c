/*************************************************************

FILE:		fcBroadInit.c

DESCRIPTION:	
This file contains some initialization code for
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
$Log: fcBroadInit.c,v $
Revision 1.2  2011/09/08 16:34:47  bobfcsoft
more portable arg processing

Revision 1.1  2007/07/27 14:13:04  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 21:12:20  root
v2.0 compatible

Revision 1.1  2002/10/30 15:58:51  root
Initial revision
=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#if 0
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#endif

#include "fcMgrMsgs.h"
#define _ALLOC extern
#include "fcBroadcaster.h"
#undef _ALLOC

/*  Prototypes  */
#include "fcBroadProto.h"
#include "loggerProto.h"
#include "simplProto.h"
#include "simplmiscProto.h"  // for atoh etc

/*=========================================================
	initialize
=========================================================*/
void initialize(int argc, char **argv)
{
static char *fn="initialize";
int i;
char toName[20];
char logger_name[20];
int myslot;

globalMask=0xffffffff;
myName[0]=0;
toName[0]=0;
logger_name[0]=0;
fcMgr_name[0]=0;

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

			case 'f':
				{
				int j;

				if(*++p == 0) p++;
//				sprintf(fcMgr_name,"%.19s",p);
				sprintf(fcMgr_name,"%.19s",argv[++i]);

				for(j=0; j<2; j++)  // try 3 times
					{
					sleep(2);

#if 0
					fcMgrID=nameLocatex(fcMgr_name);
					if(fcMgrID.slot != -1) break;
#endif
					fcMgrID=name_locate(fcMgr_name);
					if(fcMgrID != -1) break;
					}

				if(fcMgrID == -1)
					{
					printf("%s: can't locate %s\n",
						fn,fcMgr_name);
					exit(0);
					}
				}
				break;

			case 'l':
				if(*++p == 0) p++;
//				sprintf(logger_name,"%.19s",p);
				sprintf(logger_name,"%.19s",argv[++i]);
				break;

			default:
				printf("Bad command line switch `%c'\n", *p);
			}
		}
	}	

if(myName[0] == 0)
	{
	myUsage();
	exit(0);
	}

if(fcMgr_name[0] == 0)
	{
	myUsage();
	name_detach();
	exit(0);
	}

// connect to logger
logger_ID = is_logger_upx(logger_name);

// align to topofList
head = &topofList;  // note this entry is wasted to simplify algorithm
head->next=head;
head->prev=head;

fcLogx(__FILE__, fn,
	0xff,	// force it to log
	FCB_MARK,
	"my name: <%s> slot=%d",
	myName,
	myslot
	);

fcLogx(__FILE__, fn,
	0xff,	// force it to log
	FCB_MARK,
	"fcMgr: <%s> slot=%d",
	fcMgr_name,
	fcMgrID
	);

}// end initialize

/*===================================================
	myUsage - entry point
===================================================*/
void myUsage()
{
printf("========================== usage ===============================\n");
printf(" usage for fcBroadcaster:\n");
printf("      fcBroadcaster -n <myName> -f <fcMgr name> <optionals>\n");
printf("      where optionals are:\n");
printf("        -l <loggerName> - connect to trace logger\n");
printf("=================================================================\n");
}// end myUsage
