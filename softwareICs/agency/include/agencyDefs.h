/*************************************************************
FILE:	agencyDefs.h	

DESCRIPTION:	
This file contains some definitions for agency app.

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
$Log: agencyDefs.h,v $
Revision 1.1  2007/07/27 14:10:48  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 20:56:17  root
v2.0 compatible

Revision 1.1  2002/10/29 18:29:42  root
Initial revision

=======================================================

*************************************************************/

#ifndef _AGENCY_DEFS_DEF
#define _AGENCY_DEFS_DEF

#include "standardTypes.h"

typedef struct qLink
	{
	struct qLink *next;
	struct qLink *prev;
	char *sender;
	int nbytes;
	void *msg;
	}Q_LINKED_LIST;

#endif
