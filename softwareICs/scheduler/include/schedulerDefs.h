/*************************************************************
FILE:	schedulerDefs.h	

DESCRIPTION:	
This file contains some definitions for scheduler app.

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
$Log: schedulerDefs.h,v $
Revision 1.1  2006/06/19 22:32:45  bobfcsoft
new files

=======================================================

*************************************************************/

#ifndef _SCHEDULER_DEFS_DEF
#define _SCHEDULER_DEFS_DEF

#include "standardTypes.h"

typedef struct qLink
	{
	struct qLink *next;
	struct qLink *prev;
	int nbytes;
	void *msg;
	}Q_LINKED_LIST;

#endif
