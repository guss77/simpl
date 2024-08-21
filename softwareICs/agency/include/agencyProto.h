
/*************************************************************

FILE:		agencyProto.h

DESCRIPTION:	
This file contains prototypes for agency example.

AUTHOR:		R.D. Findlay

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
$Log: agencyProto.h,v $
Revision 1.1  2007/07/27 14:10:48  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 20:56:54  root
v2.0 compatible

Revision 1.1  2002/10/29 18:30:51  root
Initial revision

=======================================================

*************************************************************/

#ifndef _AGENCY_PROTO_DEF
#define _AGENCY_PROTO_DEF

void initialize(int, char **);
void myUsage();

void deleteFromList(Q_LINKED_LIST *thisOne);
Q_LINKED_LIST *addToList();
Q_LINKED_LIST *createLink();
void destroyMsg(void *msg);
void *createMsg(int nbytes);
int replyToAgent(char *, char *, int, char *);
int dequeueMsg(char *sender);
int queueMsg(char *sender, void *msg, int nbytes);

#endif
