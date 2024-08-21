/*************************************************************
FILE:	agentProto.h	

DESCRIPTION:	
This file contains prototypes for courier app.

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
$Log: agentProto.h,v $
Revision 1.1  2007/07/27 14:10:49  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 20:57:18  root
v2.0 compatible

Revision 1.1  2002/10/29 18:49:53  root
Initial revision

=======================================================

*************************************************************/

#ifndef _AGENT_PROTO_DEF
#define _AGENT_PROTO_DEF

void initialize(int, char **);
void myUsage();

int hndlMsg(char *, char *);

#endif
