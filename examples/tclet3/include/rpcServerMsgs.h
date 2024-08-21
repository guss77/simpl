/*************************************************************
FILE:		rpcServerMsgs.h

DESCRIPTION:	
This file contains test message templates for rpcServer portion of
the tclet3 SIMPL example.

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
$Log: rpcServerMsgs.h,v $
Revision 1.1  2007/07/26 16:09:43  bobfcsoft
new file

=======================================================

*************************************************************/

#ifndef _RPC_MSGS_DEF
#define _RPC_MSGS_DEF

#include "standardTypes.h"

/*=======================================
	 rpc tokens
=======================================*/
typedef enum
	{
	RPC1,
	MAX_NUM_RPC_FUNC_IDS
	}RPC_FUNC_ID;

/*============================================
	message templates
============================================*/
typedef struct 
	{
	char color[20];
	}RPC1_MSG;
	
#endif
