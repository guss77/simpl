/*************************************************************

FILE:		stimulatorInit.c

DESCRIPTION:	
This file contains initialization routines for stimulator app. 

AUTHOR:			R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2000, 2002 FCSoftware Inc. 

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
$Log: stimulatorInit.c,v $
Revision 1.2  2011/09/08 16:54:37  bobfcsoft
more portable arg processing

Revision 1.1  2008/04/28 17:59:06  bobfcsoft
new in CVS

Revision 1.2  2002/12/03 21:24:08  root
v2.0 compatible

Revision 1.1  2002/12/03 20:21:17  root
Initial revision

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "stimulatorMsgs.h"

#define _ALLOC extern
#include "stimulator.h"
#undef _ALLOC

#include "stimulatorProto.h"
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
char loggerName[20];
char recv_name[20];
int myslot;

globalMask=0xff;
myName[0]=0;
recv_name[0]=0;
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
					printf("attached as <%s> myslot=%d\n",
						myName,myslot);
#endif
                                break;

			case 'r':  // recv name
				if(*++p == 0) p++;
//				sprintf(recv_name,"%.19s",p);
				sprintf(recv_name,"%.19s",argv[++i]);

				recvID=name_locate(recv_name);
				if(recvID == -1)
					{
					printf("%s: can't locate %s\n",
						fn,recv_name);
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

if(recv_name[0] == 0)
	{
	myUsage();
	name_detach();
	exit(0);
	}

// try to connect to trace logger
logger_ID = is_logger_upx(loggerName);

// arm the select routine
my_fds[0] = whatsMyRecvfd(); // receive fifo

FD_ZERO(&watchset);
FD_SET(my_fds[0], &watchset);

maxfd=0;
if(backgroundMode)
	{
	maxfd=my_fds[0];
	}
else
	{
	my_fds[1] = STDIN_FILENO;   // keyboard
	FD_SET(my_fds[1], &watchset);

	for(i=0; i<2; i++)
		if(maxfd < my_fds[i]) maxfd=my_fds[i];
	}

fcLogx(__FILE__, fn,
	0xff,
	STIM_MARK,
	"myName=<%s> myslot=%d",
	myName,
	myslot
	);

fcLogx(__FILE__, fn,
	0xff,
	STIM_MARK,
	"trace logger mask = 0x%04X",
	globalMask);

} /* end initialize */

/*===================================================
	myUsage - entry point
===================================================*/
void myUsage()
{
printf("====================== usage =============================\n");
printf(" usage for stimulator:\n");
printf("      stimulator -n <myName> -r <recv name> <optionals>\n");
printf("      where optionals are:\n");
printf("        -m 0x<mask> - trace logger mask override\n");
printf("        -l <loggerName> - connect to trace logger\n");
printf("==========================================================\n");
}// end myUsage
