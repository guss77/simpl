/*====================================================

FILE:	showThisInit.h	

DESCRIPTION:	
This file initialization code for showThis app.

AUTHOR:			R.D. Findlay

-------------------------
FCsoftware Inc. 1999,  2007
This code is released as open source.   We hope you find 
it useful.  If you discover a bug or add an enhancement 
contact us on the SIMPL project mailing list. 

-------------------------

Revision history:
=======================================================
$Log: showThisInit.c,v $
Revision 1.1  2007/07/26 15:51:49  bobfcsoft
new file

Revision 1.1  1999/09/16 18:16:42  root
Initial revision

=======================================================
====================================================*/
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "standardTypes.h"

#include "rtMsgs.h"
#include "rtDefs.h"
#define _ALLOC extern
#include "showThis.h"
#undef _ALLOC

/*  Prototypes  */
#include "ipcProto.h"
#include "loggerProto.h"
void initialize(int argc, char **argv);
int myExit();

/*=========================================================
	initialize
=========================================================*/
void initialize(int argc, char **argv)
{
static char *fn="initialize";
int i;
char myName[20];
char logger_name[20];

globalMask=0xffffffff;

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
			case 'n':   // set this process name
				if(*++p == 0) p++;
				sprintf(myName,"%.19s",p);

				if(attachName(myName, 1024, myExit) == -1)
					{
					printf("%s: Can't attach as %s\n",fn,myName);
					exit(0);
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

// connect to logger
logger_FCID = is_logger_upx(logger_name);

if ((my_fds[0] = open(RT_TO_SHOW_FIFO, O_RDONLY)) < 0) 
	{
	fprintf(stderr, "Error opening %s\n",RT_TO_SHOW_FIFO);
	exit(1);
	}

// arm the select routine
FD_ZERO(&watchset);
FD_SET(my_fds[0], &watchset);

fcLogx(__FILE__, fn,
	globalMask,
	DISPLAY_MARK,
	"done");

}// end initialize

/*==================================================
	myExit - entry point
==================================================*/
int myExit()
{
static char *fn="showThisExit";

printf("%s:goodbye\n",fn);

return(1);

} // end myExit
