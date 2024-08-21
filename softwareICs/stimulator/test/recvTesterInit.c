/*************************************************************

FILE:		recvTesterInit.c

DESCRIPTION:	
This file contains initialization code for recvTester app.

AUTHOR:			R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2000, 2002 FCSoftware Inc. 

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

    If you discover a bug or add an enhancement please contact us on 
    the SIMPL project mailing list.

-----------------------------------------------------------------------
Revision history:
=======================================================
$Log: recvTesterInit.c,v $
Revision 1.2  2011/09/08 16:56:23  bobfcsoft
more portable arg processing

Revision 1.1  2008/04/28 18:00:22  bobfcsoft
new in CVS

Revision 1.2  2002/12/03 21:25:46  root
v2.0 compatible

Revision 1.1  2002/12/03 20:23:28  root
Initial revision

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "stimulatorMsgs.h"

#define _ALLOC extern
#include "recvTester.h"
#undef _ALLOC

#include "recvTesterProto.h"
#include "simplProto.h"
#include "loggerProto.h"
#include "simplmiscProto.h"

/*============================================
	initialize - entry point
============================================*/
void initialize(int argc, char **argv)
{
static char *fn="initialize";
int i;                          /* loop variable */
char myName[20];
char loggerName[20];
char stim_name[20];
int myslot;

globalMask=0xff;
myName[0]=0;
stim_name[0]=0;
infile[0]=0;

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
#if 0
				else
					printf("attached as <%s> myslot=%d\n",myName,myslot);
#endif
                                break;

			case 'p':   //data path
                                for(;*p != 0; p++);
//				sprintf(datapath,"%s",++p);
				sprintf(datapath,"%s",argv[++i]);
				break;

			case 'f':   //input data file name
                                for(;*p != 0; p++);
//				sprintf(infile,"%s",++p);
				sprintf(infile,"%s",argv[++i]);
				break;

			case 's':  // stimulator name
				if(*++p == 0) p++;
//				sprintf(stim_name,"%.19s",p);
				sprintf(stim_name,"%.19s",argv[++i]);

				stimID=name_locate(stim_name);
				if(stimID == -1)
					{
					printf("%s: can't locate %s\n",
						fn,stim_name);
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

if(stim_name[0] == 0)
	{
	myUsage();
	name_detach();
	exit(0);
	}

if(infile[0] == 0)
	{
	myUsage();
	name_detach();
	exit(0);
	}

// try to connect to trace logger
logger_ID = is_logger_upx(loggerName);

// arm the select routine
my_fds[0] = STDIN_FILENO;   // keyboard
my_fds[1] = whatsMyRecvfd(); // receive fifo

FD_ZERO(&watchset);
FD_SET(my_fds[0], &watchset);
FD_SET(my_fds[1], &watchset);

maxfd=0;
for(i=0; i<2; i++)
	if(maxfd < my_fds[i]) maxfd=my_fds[i];

// open infile
sprintf(fullinfile,"%s/%s",datapath,infile);
printf("full infile=<%s>\n",fullinfile);

fcLogx(__FILE__, fn,
	0xff,
	TESTER_MARK,
	"myName=<%s> myslot=%d",
	myName,
	myslot
	);

fcLogx(__FILE__, fn,
	0xff,
	TESTER_MARK,
	"stim name=<%s> stimslot=%d",
	stim_name,
	stimID
	);

fcLogx(__FILE__, fn,
	0xff,
	TESTER_MARK,
	"full infile=<%s>",
	fullinfile);

fcLogx(__FILE__, fn,
	0xff,
	TESTER_MARK,
	"trace logger mask = 0x%04X",
	globalMask);

} /* end initialize */

/*===================================================
	myUsage - entry point
===================================================*/
void myUsage()
{
printf("====================== usage =============================\n");
printf(" usage for recvTester:\n");
printf("      recvTester -n <myName> -s <stim name> -f <infile> \n");
printf("                 <optionals>\n");
printf("      where optionals are:\n");
printf("        -m 0x<mask> - set trace log mask\n");
printf("        -l <loggerName> - connect to trace logger\n");
printf("==========================================================\n");
}// end myUsage
