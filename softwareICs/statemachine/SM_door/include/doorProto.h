/*************************************************************

FILE:		doorProto.h

DESCRIPTION:	
This file contains the prototypes for the door statemachine. 

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
$Log: doorProto.h,v $
Revision 1.1  2006/06/26 18:03:17  bobfcsoft
statemachine

=======================================================

*************************************************************/

#ifndef _DOOR_PROTO_DEF
#define _DOOR_PROTO_DEF

#include "doorDefs.h"

void doorInit(char *);

// datastore stuff
int addNewDoor(char *, int);
int overwriteDoor(char *, int);
int deleteDoor(int);
int showDoorRec(void *);

void *findDoor(int);
char *stateToStr(int);

// statemachine core
void hndlCLOSE(void *);
void hndlOPEN(void *);
void hndlUNLOCK(void *);
void hndlTIMER(void *, int);
int raiseAlarm(int);

// data load parsers
int parseDoor(FILE *fp);
void skipBlock(FILE *);

#endif
