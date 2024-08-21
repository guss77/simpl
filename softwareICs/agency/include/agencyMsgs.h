
/*************************************************************
FILE:	agencyMsgs.h	

DESCRIPTION:	
This file contains message definitions for agency app.

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
$Log: agencyMsgs.h,v $
Revision 1.2  2008/08/11 21:22:29  bobfcsoft
wrapped message from requestor

Revision 1.1  2007/07/27 14:10:48  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 20:56:32  root
v2.0 compatible

Revision 1.1  2002/10/29 18:29:27  root
Initial revision

=======================================================

*************************************************************/
#ifndef _AGENCY_MSGS_DEF
#define _AGENCY_MSGS_DEF

#include "standardTypes.h"
#include "simpl.h"

typedef enum
	{
	AGENCY_WHAT_YA_GOT,
	AGENCY_GOT_ONE,
	AGENCY_REPLY,
	AGENCY_PROCESS_THIS,
	MAX_AGENCY_TOKENS
	}AGENCY_TOKEN;

typedef struct
	{
	UINT16 token; 	//AGENCY_WHAT_YA_GOT
	}AGENCY_WHAT_YA_GOT_MSG;

typedef struct
	{
	UINT16 token; 	//AGENCY_GOT_ONE, AGENCY_REPLY, AGENCY_PROCESS_THIS
	UINT16 nbytes;	//nbytes after mark
	char *sender;
	char mark;	//marks start of actual message
	}AGENCY_WRAP_MSG;

typedef enum
	{
	AGENT_TEST=0xa00,
	MAX_AGENT_TOKENS
	}AGENT_TOKEN;

typedef struct
	{
	UINT16 token; 	//AGENT_TEST
	char str[80];
	}AGENT_TEST_MSG;

#endif
