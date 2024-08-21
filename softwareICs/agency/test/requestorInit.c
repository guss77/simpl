/*************************************************************

FILE:		requestorInit.c

DESCRIPTION:	
This file contains initialization code for requestor.

AUTHOR:			R.D. Findlay

-------------------------
FCsoftware Inc. 2000, 2002, 2007

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

If you discover a bug or add an enhancement 
contact us on the SIMPL project mailing list. 

-------------------------

Revision history:
=======================================================
$Log: requestorInit.c,v $
Revision 1.2  2011/09/08 16:33:25  bobfcsoft
more portable arg processing

Revision 1.1  2007/07/27 14:10:49  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 21:02:22  root
v2.0 compatible

Revision 1.1  2002/10/29 18:48:05  root
Initial revision

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "agencyMsgs.h"

#define _ALLOC extern
#include "requestor.h"
#undef _ALLOC

#include "requestorProto.h"
#include "simplProto.h"
#include "loggerProto.h"
#include "simplmiscProto.h" // atoh

/*============================================
	initialize - entry point
============================================*/
void initialize(int argc, char **argv)
{
static char *fn="initialize";
int i;                          /* loop variable */
char myName[20];
char loggerName[20];
char agency_name[20];
int myslot;

globalMask=0xff;
myName[0]=0;
agency_name[0]=0;

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
                                break;

			case 'a':  // agency name
				{
				int j;

				if(*++p == 0) p++;
//				sprintf(agency_name,"%.19s",p);
				sprintf(agency_name,"%.19s",argv[++i]);

				for(j=0; j<2; j++)  // try 3 times
					{
#if 0
					agencyID=nameLocatex(agency_name);
#endif
					agencyID=name_locate(agency_name);
					if(agencyID != -1) break;
					printf("retrying nameLocate after 1sec sleep\n");
					sleep(1);
					}

				if(agencyID == -1)
					{
					printf("%s: can't locate %s\n",
						fn,agency_name);
					exit(0);
					}
				}
				break;

			case 'l':
                                for(;*p != 0; p++);
//				sprintf(loggerName,"%.19s",++p);
				sprintf(loggerName,"%.19s",argv[++i]);
				break;

			case 'm':
//				if(*++p == 0) p++;
				p=argv[++i];
				globalMask=atoh(&p[2]);  // skip 0x
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

if(agency_name[0] == 0)
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
	REQ_MARK,
	"myName=<%s> myslot=%d",
	myName,
	myslot
	);

fcLogx(__FILE__, fn,
	0xff,
	REQ_MARK,
	"agency name=<%s>",
	agency_name
	);

fcLogx(__FILE__, fn,
	0xff,
	REQ_MARK,
	"trace logger mask = 0x%04X",
	globalMask);

} /* end initialize */

/*===================================================
	myUsage - entry point
===================================================*/
void myUsage()
{
printf("====================== usage =============================\n");
printf(" usage for requestor:\n");
printf("      requestor -n <myName> -a <agency name> <optionals>\n");
printf("      where optionals are:\n");
printf("        -m 0x<mask> - trace logger mask override\n");
printf("        -l <loggerName> - connect to trace logger\n");
printf("==========================================================\n");
}// end myUsage
