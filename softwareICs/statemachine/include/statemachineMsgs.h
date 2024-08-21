/*************************************************************

FILE:		statemachineMsgs.h

DESCRIPTION:	
This file contains tokenized message definitions for statemachine. 

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
$Log: statemachineMsgs.h,v $
Revision 1.1  2006/06/26 18:03:19  bobfcsoft
statemachine

=======================================================

*************************************************************/

#ifndef _STATEMACHINE_MSGS_DEF
#define _STATEMACHINE_MSGS_DEF

// general messages

typedef enum
	{
	SM_ADD_REC,
	SM_OVERWRITE_REC,
	SM_DELETE_REC,
	SM_RESYNC,
	SM_DUMP,
	MAX_SM_TOKENS
	}SM_TOKEN;

typedef struct
	{
	SM_TOKEN token;	//SM_ADD_REC, OVERWRITE_REC
	int list;	// which list
	int nbytes;     // number of bytes at mydata
	char mydata;
	}SM_REC_MSG;

typedef struct
	{
	SM_TOKEN token;	//INFO_DELETE_REC
	int list;	// which list
	int ID;         // which one
	}SM_DELETE_MSG;

typedef struct
	{
	SM_TOKEN token;	//SM_DUMP
	}SM_DUMP_MSG;

typedef struct
	{
	SM_TOKEN token;	//SM_RESYNC
	char filename[128];
	}SM_RESYNC_MSG;

#endif
