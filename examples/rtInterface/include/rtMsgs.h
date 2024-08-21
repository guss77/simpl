/*======================================================

FILE:	rtMsgs.h	

DESCRIPTION:	
This file contains message formats for rtStim <-> rt_process.

AUTHOR:			R.D. Findlay

-------------------------
FCsoftware Inc. 1999, 2007
This code is released as open source.   We hope you find 
it useful.  If you discover a bug or add an enhancement 
contact us on the SIMPL project mailing list. 

-------------------------

Revision history:
=======================================================
$Log: rtMsgs.h,v $
Revision 1.1  2007/07/26 15:51:49  bobfcsoft
new file

Revision 1.1  1999/09/16 18:16:59  root
Initial revision

=======================================================
=======================================================*/
#ifndef _RT_MSGS_DEF
#define _RT_MSGS_DEF

/*==============================================
 these messages normally between RT<->STIM
==============================================*/
typedef enum
	{
	START_TASK,
	STOP_TASK,
	MAX_STIM_RT_TOKENS
	}STIM_RT_TOKEN;

typedef struct
	{
  	STIM_RT_TOKEN token;   	// START_TASK or STOP_TASK
	int period;		// in RTTicks
	int frequency;		// in Hz
	}START_STOP_TASK_MSG;

/*=================================================
 these messages normally go from RT -> SHOW
=================================================*/
typedef enum
	{
	TASK_STARTED=400,
	TASK_STOPPED,
	KICK_YOU,
	MAX_RT_SHOW_TOKENS
	}RT_SHOW_TOKEN;

typedef struct
	{
  	RT_SHOW_TOKEN token;   // KICK_YOU
	int counter;
	int frequency;
	}KICK_YOU_MSG;

#endif
