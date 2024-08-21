/*************************************************************

FILE:		statemachineDefs.h

DESCRIPTION:	
This file contains some definitions for statemachine. 

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
$Log: statemachineDefs.h,v $
Revision 1.1  2006/06/26 18:03:19  bobfcsoft
statemachine

=======================================================

*************************************************************/

#ifndef _STATEMACHINE_DEFS_DEF
#define _STATEMACHINE_DEFS_DEF

#include "standardTypes.h"

typedef struct myLink
	{
	struct myLink *next;
	struct myLink *prev;
	void *data;
	}LINKED_LIST;

typedef struct
	{
	char *data;
	char flag;
	}POOL_REC;

typedef struct
	{
	int pages;
	int records;
	int bytes;
	void *top;
	POOL_REC *index;
	}POOL_TABLE;

#endif
