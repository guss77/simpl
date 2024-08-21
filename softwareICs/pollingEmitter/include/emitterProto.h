/*************************************************************

FILE:		emitterProto.h

DESCRIPTION:	
This file contains prototypes for polling emitter example.

AUTHOR:		R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2006 iCanProgram Inc. 

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

    If you discover a bug or add an enhancement contact us on the 
    SIMPL mailing list. 

-----------------------------------------------------------------------
Revision history:
=======================================================
$Log: emitterProto.h,v $
Revision 1.1  2006/06/19 22:32:44  bobfcsoft
new files

=======================================================

*************************************************************/

#ifndef _EMITTER_PROTO_DEF
#define _EMITTER_PROTO_DEF

void initialize(int, char **);
void myUsage();

int registerShm();
int checkFlags();
int checkFile(char *);
int parseSEND(FILE *);

#endif
