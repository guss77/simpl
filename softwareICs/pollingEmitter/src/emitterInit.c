/*************************************************************

FILE:		emitterInit.c

DESCRIPTION:	
This file contains initialization code for polling emitter. 

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
$Log: emitterInit.c,v $
Revision 1.2  2011/09/08 16:38:57  bobfcsoft
more portable arg processing

Revision 1.1  2006/06/19 22:32:44  bobfcsoft
new files

=======================================================

*************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/shm.h>

#include "emitterMsgs.h"

#define _ALLOC extern
#include "emitter.h"
#undef _ALLOC

/*  Prototypes  */
#include "emitterProto.h"
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
char queuename[20];

// set defaults
globalMask=0xff;
myName[0]=0;
logger_name[0]=0;

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

				myslot=name_attach(myName, NULL);
				if (myslot == -1)
					{
					printf("%s: Can't attach as %s\n",fn,myName);
					exit(0);
					}
				break;

			case 'f':
				if(*++p == 0) p++;
//				sprintf(fullfilename,"%.127s",p);
				sprintf(fullfilename,"%.127s",argv[++i]);
				break;

			case 'q':
				{
				int j;

				if(*++p == 0) p++;
//				sprintf(queuename,"%.19s",p);
				sprintf(queuename,"%.19s",argv[++i]);
					
				for(j=0; j<2; j++)  // try 3 times
					{
					queueID=name_locate(queuename);
					if(queueID != -1) break;
					sleep(1);
					}
				
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
logger_ID = is_logger_upx(logger_name);

// create a shared memory area
myshmid = shmget(IPC_PRIVATE, 4096, 0777 | IPC_CREAT);
if (myshmid == -1)
	{
fcLogx(__FILE__, fn,
	0xff,
	EMITTER_MARK,
	"unable to create page of shared memory - %s",strerror(errno));
	}
else
	{

// attach the shmem for messages to this process
	myshmPtr = shmat(myshmid, 0, 0);
	registerShm();
	}

fcLogx(__FILE__, fn,
	0xff,
	EMITTER_MARK,
	"myName=<%s> myslot=%d",
	myName,
	myslot
	);

fcLogx(__FILE__, fn,
	0xff,
	EMITTER_MARK,
	"filename=<%s>",
	fullfilename
	);

fcLogx(__FILE__, fn,
	0xff,
	EMITTER_MARK,
	"queuename=<%s> queueID=%d",
	queuename,
	queueID
	);

fcLogx(__FILE__, fn,
	0xff,
	EMITTER_MARK,
	"trace logger mask = 0x%04X",
	globalMask);

}// end initialize

/*===================================================
	myUsage - entry point
===================================================*/
void myUsage()
{
printf("====================== usage =====================\n");
printf(" usage for emitter:\n");
printf("      emitter -n <myName> <optionals>\n");
printf("      where optionals are:\n");
printf("        -f filename - file which is being polled\n");
printf("        -q queuename - name of queue receiver\n");
printf("        -m 0x<mask> - override default log mask\n");
printf("        -l <loggerName> - connect to trace logger\n");
printf("==================================================\n");
}// end myUsage
