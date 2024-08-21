/*************************************************************

FILE:		statemachineInit.c

DESCRIPTION:	
This file contains initialization code for statemachine module. 

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
$Log: statemachineInit.c,v $
Revision 1.2  2011/09/08 16:50:31  bobfcsoft
more portable arg processing

Revision 1.1  2006/06/26 18:03:16  bobfcsoft
statemachine

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <string.h>

#include "statemachineMsgs.h"

#define _ALLOC extern
#include "statemachine.h"
#undef _ALLOC

//  Prototypes  
#include "statemachineProto.h"
#include "loggerProto.h"
#include "simplProto.h"
#include "simplmiscProto.h"

/*=========================================================
	initialize
=========================================================*/
void initialize(int argc, char **argv)
{
static char *fn="initialize";
char myName[20];
char logger_name[20];
int i;
int myslot;

globalMask=0xffffffff;
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
				break;
			}
		}
	}	

if(myName[0] == 0)
	{
	myUsage();
	exit(0);
	}

// connect to logger
logger_ID = is_logger_upx(logger_name);

// arm the select routine
my_fds[0] = whatsMyRecvfd();  // fifo

FD_ZERO(&watchset);
FD_SET(my_fds[0], &watchset);

maxfd=0;
for(i=0; i<1; i++)
	if(maxfd < my_fds[i]) maxfd=my_fds[i];

// trace log the startup info
fcLogx(__FILE__, fn,
	TRACE_MARK,	// force it to log
	TRACE_MARK,
	"executable: <%s> cksum=%lu",
	argv[0],
	cksum(argv[0])
	);

fcLogx(__FILE__, fn,
	TRACE_MARK,	// force it to log
	TRACE_MARK,
	"SIMPL name: <%s> slot=%d",
	myName,
	myslot
	);

fcLogx(__FILE__, fn,
	TRACE_MARK,  // force it to log
	TRACE_MARK,
	"trace logger mask = 0x%04X",
	globalMask);

// call the specific statemachine init routine
SM_init(argc, argv);

}// end initialize

