/*************************************************************
FILE:	requestorProto.h	

DESCRIPTION:	
This file contains prototypes for requestor app.

AUTHOR:			R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2006 iCanProgram Inc. 

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

    If you discover a bug or add an enhancement contact us at
    the SIMPL project mailing list. 

-----------------------------------------------------------------------
Revision history:
=======================================================
$Log: requestorProto.h,v $
Revision 1.1  2006/06/19 22:32:45  bobfcsoft
new files

=======================================================

*************************************************************/
#ifndef _REQUESTOR_PROTO_DEF
#define _REQUESTOR_PROTO_DEF

void initialize(int, char **);
void myUsage();
char *skipOverWhiteSpace(char *);

#endif
