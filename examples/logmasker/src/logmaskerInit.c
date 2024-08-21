/*************************************************************

FILE:		logmaskerInit.c

DESCRIPTION:	
This file contains initialization code for logmasker app.

AUTHOR:			R.D. Findlay

-------------------------
FCsoftware Inc. 1999, 2002, 2007

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
$Log: logmaskerInit.c,v $
Revision 1.1  2007/07/24 20:57:54  bobfcsoft
new file

=======================================================

*************************************************************/
#include <stdio.h>
#include <stdlib.h>  // atoi
#include <unistd.h>
#include <sys/time.h> // select stuff

#include "receiverMsgs.h"
#define _ALLOC extern
#include "logmasker.h"
#undef _ALLOC

/*  Prototypes  */
#include "logmaskerProto.h"
#include "simplProto.h"
#include "loggerProto.h"
#include "simplmiscProto.h"

/*=========================================================
	initialize
=========================================================*/
void initialize(int argc, char **argv)
{
static char *fn="initialize";
int i;
char myName[20];
char logger_name[20];
int myslot;

globalMask=0xffffffff;
toName[0]=0;
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
				sprintf(myName,"%.19s",p);

				myslot=name_attach(myName, NULL);
				if (myslot == -1)
					{
					printf("%s: Can't attach as %s\n",fn,myName);
					exit(0);
					}
				break;

			case 'r':
				{
				if(*++p == 0) p++;
				sprintf(toName,"%.19s",p);

				toPid=name_locate(toName);
				}
				break;

			case 'l':
				if(*++p == 0) p++;
				sprintf(logger_name,"%.19s",p);
				break;

			default:
				printf("Bad command line switch `%c'\n", *p);
			}
		}
	}	

if(toName[0] == 0 || myName[0] == 0)
	{
	printf("================= error ============================\n");
	printf(" please rerun as:\n");
	printf("          logmasker -n <myName> -r <recipent>\n");
	printf("=====================================================\n");
	exit(0);
	}

// connect to error logger
logger_ID = is_logger_upx(logger_name);

// arm the select routine
my_fds[0] = STDIN_FILENO;  	// keyboard
FD_ZERO(&watchset);
FD_SET(my_fds[0], &watchset);

fcLogx(__FILE__, fn,
	globalMask,
	LOGMASKER_MARK,
	"recipient <%s> id=%d",
	toName,
	toPid);

fcLogx(__FILE__, fn,
	globalMask,
	LOGMASKER_MARK,
	"done");

}// end initialize
