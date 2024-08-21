/*************************************************************

FILE:	rt_process.c	

DESCRIPTION:	
This file contains source for rt_process.

AUTHOR:			R.D. Findlay

-------------------------
FCsoftware Inc. 1999, 2007
This code is released as open source.   We hope you find 
it useful.  If you discover a bug or add an enhancement 
contact us on the SIMPL project mailing list. 

-------------------------

Revision history:
=======================================================
$Log: rt_process.c,v $
Revision 1.1  2007/07/26 15:51:49  bobfcsoft
new file

Revision 1.1  1999/09/16 18:16:30  root
Initial revision

=======================================================
*************************************************************/
#define MODULE

#include <stdio.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include <linux/errno.h>
#include <linux/cons.h>

#include <rtl_sched.h>
#include <rtl_fifo.h>
#include <asm/rt_irq.h>

#include "rtMsgs.h"
#include "rtDefs.h"

#define _ALLOC
#include "rt_process.h"
#undef _ALLOC

/*  Prototype  */

/*
 ********************************************************************
 *
 * Function: inputHandler
 *
 * Purpose : This function is used to start the process of sending
 *           and receiving data.
 *
 ********************************************************************
 */

int inputHandler ( unsigned int fifo )
{
static char *fn="inputHandler";
STIM_RT_TOKEN *token;
int nbytes;
int tbytes;
char *p;
RTIME now;
static firstTime=1;

token = (STIM_RT_TOKEN *)inArea;
p=inArea;

tbytes=rtf_get(fifo, p, sizeof(int));
p+=tbytes;

switch(*token)
	{
	case START_TASK:
		{
		START_STOP_TASK_MSG *inMsg;
		START_STOP_TASK_MSG *outMsg;

		inMsg=(START_STOP_TASK_MSG *)inArea;

		nbytes=rtf_get(fifo,
			p,
			sizeof(START_STOP_TASK_MSG)-tbytes);

		myFrequency = inMsg->frequency;
		cutPoint=myFrequency*5;

		outMsg=(START_STOP_TASK_MSG *)outArea;
		outMsg->token = TASK_STARTED;
		outMsg->frequency = myFrequency;
		rtf_put ( RT_TO_SHOW_FIFO_NUM, 
			outArea, 
			sizeof(START_STOP_TASK_MSG));   

		if(firstTime == 1)
			{
			now=rt_get_time();
			rt_task_make_periodic(&myTask,now,inMsg->period);
			firstTime=2;
			}
		else
			{
			rt_task_wakeup(&myTask);
			}
		}
		break;

	case STOP_TASK:
		{
		START_STOP_TASK_MSG *outMsg;

		nbytes=rtf_get(fifo,
			p,
			sizeof(START_STOP_TASK_MSG)-tbytes);

		outMsg=(START_STOP_TASK_MSG *)outArea;
		outMsg->token = TASK_STOPPED;
		rtf_put ( RT_TO_SHOW_FIFO_NUM, 
			outArea, 
			sizeof(START_STOP_TASK_MSG));   

		rt_task_suspend(&myTask);
		}
		break;
	
	default:
		printk("%s: unknown token=%d\n",fn,*token);
		break;
	} // end switch

return ( 0 );

}     /*  End Of inputHandler  */


/*============================================
	fun - entry point
	This module is run every period
============================================*/
void fun(int fifo)
{
#if 0
static char *fn="fun";
#endif

while(1)
	{
	counter++;
	if(counter%cutPoint == 0)
		{
		KICK_YOU_MSG *outMsg;

		outMsg = (KICK_YOU_MSG *)outArea;
		outMsg->token = KICK_YOU;
		outMsg->counter=counter;
		outMsg->frequency=myFrequency;
		rtf_put (RT_TO_SHOW_FIFO_NUM, 
			outArea, 
			sizeof(KICK_YOU_MSG));   
		}

	rt_task_wait();
	}
} // end fun

/*
 ********************************************************************
 *
 * Function: init_module
 *
 * Purpose : This function is used to initialize the RT-Linux
 *           module and create the FIFO's.
 *
 ********************************************************************
 */

int init_module ( void )
{
rtf_create ( STIM_TO_RT_FIFO_NUM , 4000); // incoming commands
rtf_create ( RT_TO_SHOW_FIFO_NUM , 4000 ); // outgoing results
rtf_create_handler ( STIM_TO_RT_FIFO_NUM , &inputHandler); 

rt_task_init(&myTask, fun, 1, 3000, 4);

printk("rt_process successfully loaded\n");

return ( 0 );

}     /*  End Of init_module  */

/*
 ********************************************************************
 *
 * Function: cleanup_module
 *
 * Purpose : This function is used to cleanup the FIFO's.
 *
 ********************************************************************
 */

void cleanup_module ( void )
{
rtf_destroy ( STIM_TO_RT_FIFO_NUM );
rtf_destroy ( RT_TO_SHOW_FIFO_NUM );

rt_task_delete(&myTask);

printk("rt_process unloaded\n");

return;
}     /*  End Of cleanup_module  */
