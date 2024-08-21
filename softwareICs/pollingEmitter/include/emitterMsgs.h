/*************************************************************
FILE:	emitterMsgs.h	

DESCRIPTION:	
This file contains message definitions for polling emitter app.

AUTHOR:			R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2006 iCanProgram Inc. 

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

    If you discover a bug or add an enhancement contact us at the
    SIMPL project mailing list. 

-----------------------------------------------------------------------
Revision history:
=======================================================
$Log: emitterMsgs.h,v $
Revision 1.1  2006/06/19 22:32:44  bobfcsoft
new files

=======================================================

*************************************************************/
#ifndef _EMITTER_MSGS_DEF
#define _EMITTER_MSGS_DEF

#include "standardTypes.h"
#include "simpl.h"

typedef enum
	{
	EMITTER_REGISTER,
	EMITTER_CALL_HOME,
	EMITTER_DATA,
	MAX_EMITTER_TOKENS
	}EMITTER_TOKEN;

typedef struct
	{
	UINT16 token; 	//EMITTER_REGISTER
	int shmid;
	}EMITTER_REGISTER_MSG;

typedef struct
	{
	UINT16 token; 	//EMITTER_CALL_HOME
	}EMITTER_CALL_HOME_MSG;

typedef struct
	{
	UINT16 token; 	//EMITTER_DATA
	char msg[256];
	}EMITTER_DATA_MSG;

#endif
