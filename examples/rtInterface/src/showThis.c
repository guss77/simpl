/*====================================================

FILE:     showThis.c

DESCRIPTION:	
This module will display output from rt_process.

AUTHOR:			R.D. Findlay

-------------------------
FCsoftware Inc. 1999, 2007
This code is released as open source.   We hope you find 
it useful.  If you discover a bug or add an enhancement 
contact us on the SIMPL project mailing list. 

-------------------------

Revision history:
=======================================================
$Log: showThis.c,v $
Revision 1.1  2007/07/26 15:51:49  bobfcsoft
new file

Revision 1.1  1999/09/16 18:16:36  root
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
#define _ALLOC
#include "showThis.h"
#undef _ALLOC

/*  Prototypes  */
#include "ipcProto.h"
#include "loggerProto.h"
void processInput();
void initialize(int argc, char **argv);
int myExit();

/*==============================================
	main - entry point
==============================================*/
void main(int argc, char **argv)
{
static char *fn="showThis";
int n;
int retval;
int maxfd;
int x_it=0;
int i;

initialize(argc, argv);

maxfd=0;
for(i=0; i<3; i++)
	if(maxfd < my_fds[i]) maxfd=my_fds[i];

fcLogx(__FILE__, fn,
	globalMask,
	DISPLAY_MARK,
	"ding");

while(!x_it)
	{
	inset=watchset;
	retval = select(maxfd+1, &inset, NULL, NULL, NULL);


	if (retval > 0) 
		{
		if (FD_ISSET(my_fds[0], &inset))  // from rt_process
			{
			n = read(my_fds[0], inArea, 1024 - 1);
			processInput();
			}
		} // end if retval
	} // end while
} // end main


/*==============================================
	processInput - entry point
==============================================*/
void processInput()
{
static char *fn="processInput";
RT_SHOW_TOKEN *token;

token = (RT_SHOW_TOKEN *)inArea;
		
switch(*token)
	{
	case TASK_STARTED:
		{
		START_STOP_TASK_MSG *inMsg;

		inMsg=(START_STOP_TASK_MSG *)inArea;

printf("%s:RTtask started\n",fn);

		fcLogx(__FILE__, fn,
			globalMask,
			DISPLAY_MARK,
			"task started freq=%d Hz",
			inMsg->frequency
			);
		}
		break;

	case TASK_STOPPED:
printf("%s:RTtask stopped\n",fn);
		fcLogx(__FILE__, fn,
			globalMask,
			DISPLAY_MARK,
			"task stopped"
			);
		break;

	case KICK_YOU:
		{
		KICK_YOU_MSG *inMsg;

		inMsg=(KICK_YOU_MSG *)inArea;

		fcLogx(__FILE__, fn,
			globalMask,
			DISPLAY_MARK,
			"[%d] frequency=%d",
			inMsg->counter,
			inMsg->frequency);
		}
		break;

	default:
		printf("%s:unknown token=%d\n",fn,*token);
		break;
	} // end switch
} // end processInput
