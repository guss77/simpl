/*************************************************************
FILE:	fcMgrDefs.h	

DESCRIPTION:	
This file contains some definitions for fcMgr app.

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
$Log: fcMgrDefs.h,v $
Revision 1.1  2007/07/27 14:13:04  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 21:10:38  root
v2.0 compatible

Revision 1.1  2002/10/30 15:56:34  root
Initial revision

=======================================================

*************************************************************/

#ifndef _FC_MGR_DEFS_DEF
#define _FC_MGR_DEFS_DEF

#include "standardTypes.h"

typedef struct qLink
	{
	struct qLink *next;
	struct qLink *prev;
	int nbytes;
	void *msg;
	}Q_LINKED_LIST;

#endif
