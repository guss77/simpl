/*************************************************************
FILE:		tclet3Msgs.h

DESCRIPTION:	
This file contains test message templates for tclet3 SIMPL
example.

AUTHOR:		R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2000, 2007 FCSoftware Inc. 

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    If you discover a bug or add an enhancement contact us on the
    SIMPL project mailing list. 

-----------------------------------------------------------------------
Revision history:
=======================================================
$Log: tclet3Msgs.h,v $
Revision 1.1  2007/07/26 16:09:43  bobfcsoft
new file

=======================================================

*************************************************************/

#ifndef _TCLET3_MSGS_DEF
#define _TCLET3_MSGS_DEF

#include "standardTypes.h"

/*=======================================
	 message tokens
=======================================*/
typedef enum
	{
	RPC_CALL=0xfc01,
	CALL_BACK_REQUEST,
	CALL_BACK_RESPONSE,
	MAX_NUM_TCLET3_TOKENS
	}TCLET3_TOKEN;

/*============================================
	message templates
============================================*/
typedef struct 
	{
	UINT16 token;		// for RPC_CALL
	UINT16 funcID;		// which function to call
	char data[80];
	}RPC_CALL_MSG;
	
typedef struct  
	{
	UINT16 token;		// for CALL_BACK_REQUEST
	UINT16 funcID;		// which type of function to load
	char callBackFunction[20];  // tcl call back command name
	char data[80];
	}CALL_BACK_REQUEST_MSG;
	
typedef struct  
	{
	UINT16 token;		// for CALL_BACK_RESPONSE
	UINT16 funcID;		// which type of function to load
	char callBackFunction[20];  // tcl call back command name
	char data[80];
	}CALL_BACK_RESPONSE_MSG;
	
#endif
