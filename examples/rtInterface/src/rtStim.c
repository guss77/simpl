/*================================================
FILE:		rtStim.c

DESCRIPTION:	
This program is an example of a utility process 
used for sending messages from a SIMPL enable app
into an RTLinux module.

AUTHOR:			R.D. Findlay

-------------------------
FCsoftware Inc. 1999, 2007
This code is released as open source.   We hope you find 
it useful.  If you discover a bug or add an enhancement 
contact us on the SIMPL project mailing list. 

-------------------------

Revision history:
=======================================================
$Log: rtStim.c,v $
Revision 1.1  2007/07/26 15:51:49  bobfcsoft
new file

Revision 1.1  1999/09/16 18:16:23  root
Initial revision

=======================================================
================================================*/

#include <stdio.h>
#include <stdlib.h>  // atoi
#include <ctype.h> // isdigit
#include <errno.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <asm/rt_time.h>

#include "standardTypes.h"

#include "rtDefs.h"
#include "rtMsgs.h"
#define _ALLOC
#include "rtStim.h"
#undef _ALLOC

/*  Prototypes  */
#include "ipcProto.h"
#include "loggerProto.h"

void sendCtlMsg(char *, char *outbuf, int outlen);
void initialize(int argc, char **argv);
void showUsage();

/*==============================================
	main - entry point
==============================================*/
void main(int argc, char **argv)
{
static char *fn="rtStim";
int n;
int maxfd;
char *p;
int x_it=0;

p=keyArea;

initialize(argc,argv);
maxfd=my_fds[0];

while(!x_it)
	{
	printf("Enter command: ");
	fflush(stdout);

	inset = watchset;
	select(maxfd+1, &inset, NULL, NULL, NULL);

// check which file descriptors are ready to be read from

// Is this from keyboard
	if(FD_ISSET(my_fds[0], &inset))  // keyboard is ready
		{
		n=read(my_fds[0],p,80);
		p[n-1]=0;

		fcLogx(__FILE__, fn,
			globalMask,
			INPUT_MARK,
			"%d bytes recd str=<%s>",n,p);

		switch(keyArea[0])
			{
			case '?':  // help
				showUsage();
				break;

			case 'g':  // go
				{
				START_STOP_TASK_MSG *sMsg;

				fcLogx(__FILE__, fn,
					globalMask,
					INPUT_MARK,
					"START_TASK");

				sMsg = (START_STOP_TASK_MSG *)outArea;

				sMsg->token= START_TASK;
				sMsg->period = RT_TICKS_PER_SEC / myFrequency;
				sMsg->frequency = myFrequency;
				sendCtlMsg(STIM_TO_RT_FIFO,outArea,sizeof(START_STOP_TASK_MSG));
				fcLogx(__FILE__, fn,
					globalMask,
					INPUT_MARK,
					"frequency=%d Hz sMsg->period=%d ticks",
					myFrequency,
					sMsg->period);

				}
				break;

			case 'h':  // halt
				{
				START_STOP_TASK_MSG *sMsg;

				fcLogx(__FILE__, fn,
					globalMask,
					INPUT_MARK,
					"STOP_TASK");

				sMsg = (START_STOP_TASK_MSG *)outArea;

				sMsg->token= STOP_TASK;
				sendCtlMsg(STIM_TO_RT_FIFO,outArea,sizeof(START_STOP_TASK_MSG));
				}
				break;

			case 'q':	// quit
				x_it=1;
				break;

			default:
				break;
			} // end switch
		}
	} // end for

printf("%s:done\n",fn);
fcLogx(__FILE__, fn,
	globalMask,
	INPUT_MARK,
	"done");

detachName();

} // end main

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
myFrequency=1000;

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

				myslot=attachName(myName, 1024, NULL);
				if (myslot == -1)
					{
					printf("%s: Can't attach as %s\n",fn,myName);
					exit(0);
					}
				break;

			case 'f':  // frequency in Hz
				if(*++p == 0) p++;
				myFrequency = atoi(p);
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

// connect to error logger
logger_FCID = is_logger_upx(logger_name);

// arm the select routine
my_fds[0] = STDIN_FILENO;  	// keyboard
FD_ZERO(&watchset);
FD_SET(my_fds[0], &watchset);

fcLogx(__FILE__, fn,
	0xff,	// force it to log
	INPUT_MARK,
	"my name: <%s> slot=%d",
	myName,
	myslot
	);

fcLogx(__FILE__, fn,
	globalMask,
	INPUT_MARK,
	"frequency=%d Hz",
	myFrequency);

fcLogx(__FILE__, fn,
	globalMask,
	INPUT_MARK,
	"done");

}// end initialize

/*===================================================
	sendCtlMsg - entry point
===================================================*/
void sendCtlMsg(char *fifo, char *outbuf, int outlen)
{
static char *fn="sendCtlMsg";

if ((ctl = open(fifo, O_WRONLY)) < 0) 
	{
	fprintf(stderr, "Error opening command fifo <%s>\n",fifo);
	exit(1);
	}
write(ctl, outbuf, outlen);
close(ctl);

} // end sendCtlMsg

/*==================================================
	showUsage - entry point
==================================================*/
void showUsage()
{
printf("g(0)    - start the RTLinux module\n");
printf("h(alt)  - stop the RTLinux module\n");
printf("q(uit)  - exit the input process\n");
} // end showUsage
