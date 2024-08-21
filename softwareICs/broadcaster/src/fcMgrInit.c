/*************************************************************

FILE:		fcMgrInit.c

DESCRIPTION:	
This file contains initialization code for 
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
$Log: fcMgrInit.c,v $
Revision 1.3  2011/09/08 16:34:47  bobfcsoft
more portable arg processing

Revision 1.2  2009/04/14 15:51:07  bobfcsoft
cleanup

Revision 1.1  2007/07/27 14:13:04  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 21:13:06  root
v2.0 compatible
.l

Revision 1.1  2002/10/30 15:59:19  root
Initial revision

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fcMgrMsgs.h"

#define _ALLOC extern
#include "fcMgr.h"
#undef _ALLOC

#include "fcMgrProto.h"
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
int myslot;

globalMask=0xff;
myName[0]=0;
broadcasterPending=NULL;
backgroundMode=0;

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
			case 'b':
				backgroundMode=1;
				break;

                        case 'n':
                                for(;*p != 0; p++);
//				sprintf(myName,"%s",++p);
				sprintf(myName,"%s",argv[++i]);
#if 0
				myslot=attachName(myName, 1024, NULL);
#endif
				myslot=name_attach(myName, NULL);
				if(myslot == -1)
					{
					printf("%s: unable to attach as <%s>\n",
						fn,
						myName);
					exit(0);
					}
#if 0
				else
					printf("attached as <%s> myslot=%d\n",myName,myslot);
#endif
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

// try to connect to trace logger
logger_ID = is_logger_upx(loggerName);

// align to topofList
head = &topofList;  // note this entry is wasted to simplify algorithm
head->next=head;
head->prev=head;

fcLogx(__FILE__, fn,
	0xff,
	FC_MGR_MARK,
	"myName=<%s> myslot=%d",
	myName,
	myslot
	);

} /* end initialize */

/*===================================================
	myUsage - entry point
===================================================*/
void myUsage()
{
printf("====================== usage =============================\n");
printf(" usage for fcMgr:\n");
printf("      fcMgr -n <myName> <optionals>\n");
printf("      where optionals are:\n");
printf("        -l <loggerName> - connect to trace logger\n");
printf("==========================================================\n");
}// end myUsage
