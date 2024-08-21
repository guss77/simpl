/*************************************************************
FILE:	fcBroadDefs.h	

DESCRIPTION:	
This file contains definitions for fcBroadcaster app.

AUTHOR:			R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2000, 2002, 2007 FCSoftware Inc. 

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
$Log: fcBroadDefs.h,v $
Revision 1.1  2007/07/27 14:13:04  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 21:09:45  root
v2.0 compatible

Revision 1.1  2002/10/30 15:55:59  root
Initial revision

=======================================================

*************************************************************/

#ifndef _FC_BROAD_DEFS_DEF
#define _FC_BROAD_DEFS_DEF

#include "standardTypes.h"	// UINT32, UINT16 etc.
#include "simpl.h"              // public definitions

typedef struct myLink
	{
	struct myLink *next;
	struct myLink *prev;
	int subscriberID;
	pid_t subscriber_pid;
	}LINKED_LIST;

#endif
