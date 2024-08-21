
/*************************************************************

FILE:		schedulerProto.h

DESCRIPTION:	
This file contains prototypes for scheduler example.

AUTHOR:		R.D. Findlay

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
$Log: schedulerProto.h,v $
Revision 1.1  2006/06/19 22:32:45  bobfcsoft
new files

=======================================================

*************************************************************/

#ifndef _SCHEDULER_PROTO_DEF
#define _SCHEDULER_PROTO_DEF

void initialize(int, char **);
void myUsage();

void deleteFromList(Q_LINKED_LIST *thisOne);
Q_LINKED_LIST *addToList();
Q_LINKED_LIST *createLink();
void destroyMsg(void *msg);
void *createMsg(int nbytes);
int dequeueMsg(char *sender);
int queueMsg(void *msg, int nbytes);
int checkForExpired();
time_t newStamp(int, UINT32);
int fetchRecord(int);

#endif
