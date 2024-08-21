/*************************************************************
FILE:	proxyMsgs.h	

DESCRIPTION:	
This file contains globals for relay SIMPL software IC. 

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
$Log: proxyMsgs.h,v $
Revision 1.1  2006/06/21 21:05:44  bobfcsoft
new proxy code

=======================================================

*************************************************************/

#ifndef _PROXY_MSGS_DEF
#define _PROXY_MSGS_DEF

#include "standardTypes.h"

typedef enum
	{
	RELAY_TEST,
	RELAY_ERROR,
	MAX_RELAY_TOKENS
	}RELAY_TOKEN;

typedef struct
	{
	UINT16 token; 	//RELAY_TEST
	char str[80];
	}RELAY_TEST_MSG;

typedef struct
	{
	UINT16 token; 	//RELAY_ERROR
	int code;
	}RELAY_ERROR_MSG;
#endif
