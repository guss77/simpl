/*************************************************************
FILE:	recvTesterProto.h	

DESCRIPTION:	
This file contains prototypes for recvTester app.

AUTHOR:			R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2000, 2002 FCSoftware Inc. 

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

    If you discover a bug or add an enhancement here's how to reach us: 

	fcsoft@attcanada.ca
-----------------------------------------------------------------------
Revision history:
=======================================================
$Log: recvTesterProto.h,v $
Revision 1.1  2008/04/28 17:58:06  bobfcsoft
new in CVS

Revision 1.2  2002/12/03 21:22:58  root
v2.0 compatible

Revision 1.1  2002/12/03 20:22:09  root
Initial revision

=======================================================

*************************************************************/

#ifndef _RECV_TESTER_PROTO_DEF
#define _RECV_TESTER_PROTO_DEF

void initialize(int, char **);
void myUsage();

int runtest(char *);
char *skipOverWhiteSpace(char *start);

#endif
