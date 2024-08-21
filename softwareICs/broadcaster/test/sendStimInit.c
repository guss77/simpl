/*************************************************************

FILE:		sendStimInit.c

DESCRIPTION:	
This file contains initialization code for senderStim.

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
$Log: sendStimInit.c,v $
Revision 1.2  2011/09/08 16:37:51  bobfcsoft
more portable arg processing

Revision 1.1  2007/07/27 14:13:04  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 21:06:03  root
v2.0 compatible

Revision 1.1  2002/10/30 16:00:35  root
Initial revision

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "fcMgrMsgs.h"

#define _ALLOC extern
#include "senderStim.h"
#undef _ALLOC

#include "sendStimProto.h"
#include "simplProto.h"
#include "loggerProto.h"

/*============================================
	initialize - entry point
============================================*/
void initialize(int argc, char **argv)
{
static char *fn="initialize";
int i;                          /* loop variable */
char myName[20];
char loggerName[20];
char fcMgr_name[20];
int myslot;

globalMask=0xff;
myName[0]=0;
fcMgr_name[0]=0;

/*===============================================
  process command args
===============================================*/
for(i=1; i<=argc; ++i)
        {
        char *p = argv[i];

        if(p == NULL) continue;

        if(*p == '-')
                {
                switch(*++p)
                        {
                        case 'n':
                                for(;*p != 0; p++);
//				sprintf(myName,"%s",++p);
				sprintf(myName,"%s",argv[++i]);
				myslot=name_attach(myName, NULL);
				if(myslot == -1)
					{
					printf("%s: unable to attach as <%s>\n",
						fn,
						myName);
					exit(0);
					}
				else
					printf("attached as <%s> myslot=%d\n",myName,myslot);
                                break;

			case 'f':   //fcMgr name
                                for(;*p != 0; p++);
//				sprintf(fcMgr_name,"%s",++p);
				sprintf(fcMgr_name,"%s",argv[++i]);

				fcMgrID=name_locate(fcMgr_name);
				if(fcMgrID == -1)
					{
					printf("%s: can't locate %s\n",
						fn,fcMgr_name);
					exit(0);
					}
				break;

			case 'l':
                                for(;*p != 0; p++);
//				sprintf(loggerName,"%.19s",++p);
				sprintf(loggerName,"%.19s",argv[++i]);
				break;

                        default:
				printf("%s:unknown arg %s\n",fn, p);
                                break;
                        }/*end switch*/
                } /* end if *p */
        }/*end for i*/

// check for compulsory args
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

// try to connect to trace logger
logger_ID = is_logger_upx(loggerName);

// arm the select routine
my_fds[0] = STDIN_FILENO;   // keyboard

FD_ZERO(&watchset);
FD_SET(my_fds[0], &watchset);

maxfd=my_fds[0];

fcLogx(__FILE__, fn,
	0xff,
	SEND_STIM_MARK,
	"myName=<%s> myslot=%d",
	myName,
	myslot
	);

fcLogx(__FILE__, fn,
	0xff,
	SEND_STIM_MARK,
	"fcMgrName=<%s> slot=%d",
	fcMgr_name,
	fcMgrID
	);

} /* end initialize */

/*===================================================
	myUsage - entry point
===================================================*/
void myUsage()
{
printf("====================== usage =============================\n");
printf(" usage for senderStim:\n");
printf("      senderStim -n <myName> -f <fcMgr name> <optionals>\n");
printf("      where optionals are:\n");
printf("        -l <loggerName> - connect to trace logger\n");
printf("==========================================================\n");
}// end myUsage
