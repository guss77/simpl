/*************************************************************
FILE:		cbServerMsgs.h

DESCRIPTION:	
This file contains test message templates for cbServer portion of
the tclet4 SIMPL example.

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
$Log: cbServerMsgs.h,v $
Revision 1.1  2007/07/27 14:16:01  bobfcsoft
new cvs file

=======================================================

*************************************************************/

#ifndef _CB_MSGS_DEF
#define _CB_MSGS_DEF

#include "standardTypes.h"

/*=======================================
	 rpc tokens
=======================================*/
typedef enum
	{
	CB1,
	MAX_NUM_CB_FUNC_IDS
	}CB_FUNC_ID;

/*============================================
	message templates
============================================*/
typedef struct 
	{
	char color[20];
	}CB1_MSG;
	
#endif
