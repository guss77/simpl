/*====================================================

FILE:	receiverInit.c

DESCRIPTION:	
This file contains initialization code for receiver. 

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
$Log: receiverInit.c,v $
Revision 1.1  2007/07/24 20:57:54  bobfcsoft
new file

=======================================================
====================================================*/
#include <stdio.h>
#include <unistd.h>

#include "receiverMsgs.h"
#define _ALLOC extern
#include "receiver.h"
#undef _ALLOC

/*  Prototypes  */
#include "receiverProto.h"
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

// set defaults
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
				sprintf(myName,"%.19s",p);

				myslot=name_attach(myName, NULL);
				if (myslot == -1)
					{
					printf("%s: Can't attach as %s\n",fn,myName);
					exit(0);
					}
				break;

			case 'l':
				if(*++p == 0) p++;
				sprintf(logger_name,"%.19s",p);
				break;

			case 'm':
				if(*++p == 0) p++;
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

fcLogx(__FILE__, fn,
	globalMask,
	RECV_FUNC_IO,
	"done");

}// end initialize

/*===================================================
	myUsage - entry point
===================================================*/
void myUsage()
{
printf("====================== usage =====================\n");
printf(" usage for receiver:\n");
printf("      receiver -n <myName> <optionals>\n");
printf("      where optionals are:\n");
printf("        -m <mask> - override default log mask\n");
printf("        -l <loggerName> - connect to trace logger\n");
printf("==================================================\n");
}// end myUsage
