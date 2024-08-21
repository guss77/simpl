/*************************************************************
FILE:	agency.h	

DESCRIPTION:	
This file contains globals for agency app.

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
$Log: agency.h,v $
Revision 1.1  2007/07/27 14:10:48  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 20:56:04  root
v2.0 compatible

Revision 1.1  2002/10/29 18:23:27  root
Initial revision

=======================================================

*************************************************************/
#ifndef _AGENCY_DEF
#define _AGENCY_DEF

#include "simpl.h"
#include "loggerVars.h"
#include "agencyDefs.h"  // for linked list stuff

#define	MAX_MSG_BUFFER_SIZE		1024

_ALLOC unsigned int globalMask;
#define AGENCY_MARK	0x00000001
#define AGENCY_FUNC_IO	0x00000002
#define AGENCY_STRUCTS	0x00000004
#define AGENCY_MISC	0x00000010

_ALLOC char *agentPending;
_ALLOC int nextRequestor;

_ALLOC Q_LINKED_LIST topofList;
_ALLOC Q_LINKED_LIST *head;

_ALLOC char inArea[MAX_MSG_BUFFER_SIZE];
_ALLOC char outArea[MAX_MSG_BUFFER_SIZE];

#endif
