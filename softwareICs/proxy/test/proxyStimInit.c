/*************************************************************

FILE:		proxyStimInit.c

DESCRIPTION:	
This file contains initialization code for proxyStim.

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
$Log: proxyStimInit.c,v $
Revision 1.2  2011/09/08 16:42:59  bobfcsoft
more portable arg processing

Revision 1.1  2006/06/21 21:05:45  bobfcsoft
new proxy code

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "proxyMsgs.h"

#define _ALLOC extern
#include "proxyStim.h"
#undef _ALLOC

#include "proxyStimProto.h"
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
char proxy_name[20];
int myslot;

globalMask=0xff;
myName[0]=0;
proxy_name[0]=0;

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

			case 'p':  // proxy name
				if(*++p == 0) p++;
//				sprintf(proxy_name,"%.19s",p);
				sprintf(proxy_name,"%.19s",argv[++i]);

				proxyID=name_locate(proxy_name);
				if(proxyID == -1)
					{
					printf("%s: can't locate %s\n",
						fn,proxy_name);
					exit(0);
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

if(proxy_name[0] == 0)

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
	TRACE_MARK,
	"myName=<%s> myslot=%d",
	myName,
	myslot
	);

fcLogx(__FILE__, fn,
	0xff,
	TRACE_MARK,
	"proxy name=<%s>",
	proxy_name
	);

fcLogx(__FILE__, fn,
	0xff,
	TRACE_MARK,
	"trace logger mask = 0x%04X",
	globalMask);

} /* end initialize */

/*===================================================
	myUsage - entry point
===================================================*/
void myUsage()
{
printf("====================== usage =============================\n");
printf(" usage for proxyStim:\n");
printf("      proxyStim -n <myName> -p <proxy name> <optionals>\n");
printf("      where optionals are:\n");
printf("        -m 0x<mask> - trace logger mask override\n");
printf("        -l <loggerName> - connect to trace logger\n");
printf("==========================================================\n");
}// end myUsage
