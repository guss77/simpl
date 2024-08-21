/*************************************************************

FILE:		agentInit.c

DESCRIPTION:	
This file contains initialization code for agent.

AUTHOR:			R.D. Findlay

-------------------------
iCanProgram Inc. 2006

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
$Log: agentInit.c,v $
Revision 1.2  2011/09/08 16:48:35  bobfcsoft
more portable arg processing

Revision 1.1  2006/06/19 22:32:45  bobfcsoft
new files

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "schedulerMsgs.h"

#define _ALLOC extern
#include "agent.h"
#undef _ALLOC

#include "agentProto.h"
#include "simplProto.h"
#include "loggerProto.h"
#include "simplmiscProto.h"  // atoh

/*============================================
	initialize - entry point
============================================*/
void initialize(int argc, char **argv)
{
static char *fn="initialize";
int i;                          /* loop variable */
char myName[20];
char loggerName[20];
char agencyName[20];
int myslot;

globalMask=0xff;
myName[0]=0;
agencyName[0]=0;
replyCount=0;
startupDelay=0;

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
                                break;

			case 'a':
				{
				int j;

				if(*++p == 0) p++;
//				sprintf(agencyName,"%.19s",p);
				sprintf(agencyName,"%.19s",argv[++i]);

				for(j=0; j<2; j++)  // try 3 times
					{
					agencyID=name_locate(agencyName);
					
					if(agencyID != -1) break;
					printf("retrying nameLocate after 1sec sleep\n");
					sleep(1);
					}

				if(agencyID == -1)
					{
					printf("%s: can't locate %s\n",
						fn,agencyName);
					exit(0);
					}
				}
				break;

			case 'd':  // startup delay in sec
				if(*++p == 0) p++;
//				startupDelay=atoi(p);	
				startupDelay=atoi(argv[++i]);	
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

if(agencyName[0] == 0)
	{
	myUsage();
	name_detach();
	exit(0);
	}

// try to connect to trace logger
logger_ID = is_logger_upx(loggerName);

fcLogx(__FILE__, fn,
	0xff,
	AGENT_MARK,
	"myName=<%s> myslot=%d",
	myName,
	myslot
	);

fcLogx(__FILE__, fn,
	0xff,
	AGENT_MARK,
	"agencyName=<%s> agencyslot=%d",
	agencyName,
	agencyID
	);

fcLogx(__FILE__, fn,
	0xff,
	AGENT_MARK,
	"startup delay = %d secs",
	startupDelay
	);

fcLogx(__FILE__, fn,
	0xff,
	AGENT_MARK,
	"trace logger mask =0x%04X",
	globalMask
	);

} /* end initialize */

/*===================================================
	myUsage - entry point
===================================================*/
void myUsage()
{
printf("====================== usage =============================\n");
printf(" usage for agent:\n");
printf("      agent -n <myName> -a <agency name> <optionals>\n");
printf("      where optionals are:\n");
printf("        -d <delay>  - startup delay in secs\n");
printf("        -m 0x<mask> - trace logger mask override\n");
printf("        -l <loggerName> - connect to trace logger\n");
printf("==========================================================\n");
}// end myUsage
