/*************************************************************
FILE:	fcMgrProto.h	

DESCRIPTION:	
This file contains prototypes for fcMgr app.

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
$Log: fcMgrProto.h,v $
Revision 1.1  2007/07/27 14:13:04  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 21:10:59  root
v2.0 compatible

Revision 1.1  2002/10/30 15:56:56  root
Initial revision
=======================================================

*************************************************************/

#ifndef _FC_MGR_PROTO_DEF
#define _FC_MGR_PROTO_DEF

#include "fcMgrDefs.h"	//Q_LINKED_LIST stuff

void initialize(int, char **);
void myUsage();

int queueMsg(void *, int);
int dequeueMsg(char *);
void *createMsg(int);
Q_LINKED_LIST *createLink();
Q_LINKED_LIST *addToList();
void deleteFromList(Q_LINKED_LIST *);

#endif
