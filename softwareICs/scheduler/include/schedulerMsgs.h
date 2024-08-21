
/*************************************************************
FILE:	schedulerMsgs.h	

DESCRIPTION:	
This file contains message definitions for scheduler app.

AUTHOR:			R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2006 iCanProgam Inc. 

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
$Log: schedulerMsgs.h,v $
Revision 1.1  2006/06/19 22:32:45  bobfcsoft
new files

=======================================================

*************************************************************/
#ifndef _SCHEDULER_MSGS_DEF
#define _SCHEDULER_MSGS_DEF

#include "standardTypes.h"
#include "simpl.h"

typedef enum
	{
	AGENT_WHAT_YA_GOT,
	AGENT_TEST,
	SCHEDULE_THIS,
	VIEW_NEXT,
	MAX_AGENCY_TOKENS
	}AGENCY_TOKEN;


typedef struct
	{
	UINT16 token; 	//AGENT_WHAT_YA_GOT
	}AGENT_WHAT_YA_GOT_MSG;

typedef struct
	{
	UINT16 token; 	//AGENT_TEST
	char str[80];
	}AGENT_TEST_MSG;

// bits in the flags field
#define SCHEDULER_EXPIRED 0x00000001
#define SCHEDULER_DAILY   0x00000002
#define SCHEDULER_WEEKLY  0x00000004

typedef struct
	{
	UINT16 token; 	//SCHEDULE_THIS
	time_t stamp;
	UINT32 flags;
	int offset;     // for daily or weekly offsets
	UINT16 nbytes;
	char mark;     // marks the actual message
	}SCHEDULE_THIS_MSG;

typedef struct
	{
	UINT16 token; 	//VIEW_NEXT
	int count;
	time_t stamp;
	UINT32 flags;
	UINT16 nbytes;
	}VIEW_MSG;

#endif
