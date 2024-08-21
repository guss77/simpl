/*************************************************************
FILE:	recvSimProto.h	

DESCRIPTION:	
This file contains prototypes for receiverSim app.

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
$Log: recvSimProto.h,v $
Revision 1.1  2006/06/21 21:05:44  bobfcsoft
new proxy code

=======================================================

*************************************************************/

#ifndef _RECV_SIM_PROTO_DEF
#define _RECV_SIM_PROTO_DEF

void initialize(int, char **);
char *skipOverWhiteSpace(char *);
void myUsage();
int postmyID(int);

#endif
