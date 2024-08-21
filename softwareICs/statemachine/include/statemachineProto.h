/*************************************************************

FILE:		statemachineProto.h

DESCRIPTION:	
This file contains the prototypes for the statemachine softwareIC. 

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
$Log: statemachineProto.h,v $
Revision 1.1  2006/06/26 18:03:19  bobfcsoft
statemachine

=======================================================

*************************************************************/

#ifndef _STATEMACHINE_PROTO_DEF
#define _STATEMACHINE_PROTO_DEF

#include "statemachineDefs.h"

// linked list stuff
void deleteFromList(LINKED_LIST *);
LINKED_LIST *addToList(LINKED_LIST *, void *);
LINKED_LIST *createLink();
void *createDataRec(int);
void deleteDataRec(void *);
void loadData(char *);

void initialize(int, char **);
void hndlCommonMsgs(char *, int);

// linked list stuff
char *skipOverWhiteSpace(char *);

/*=================================================
	statemachine API
	- to be created in SM_xxxx module
=================================================*/
//  initializations
void SM_init(int, char **);
void myUsage();

// main event handler
void hndlEvents(char *, int);

// data store stuff
int addNewRec(int, char *, int);
int overwriteRec(int, char *, int);
void deleteRec(int, int);
int showRec(int, void *);
int dumpTable();
int dumpRec(int);

// pool stuff
int pool_init();
void *pool_malloc(int);
void pool_free(void *);
int whichPool(int);

// data parsers
void parseRESET(FILE *);
void parseADD(FILE *);
void parseDELETE(FILE *);
void parseOVERWRITE(FILE *);

#endif
