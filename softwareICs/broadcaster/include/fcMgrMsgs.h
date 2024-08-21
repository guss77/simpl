/*************************************************************
FILE:	fcMgrMsgs.h	

DESCRIPTION:	
This file contains globals for fcMgr app.

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
$Log: fcMgrMsgs.h,v $
Revision 1.1  2007/07/27 14:13:04  bobfcsoft
new cvs file

Revision 1.2  2002/12/03 21:10:48  root
v2.0 compatible

Revision 1.1  2002/10/30 15:56:46  root
Initial revision

=======================================================

*************************************************************/

#ifndef _FC_MGR_MSGS_DEF
#define _FC_MGR_MSGS_DEF

#include "standardTypes.h"

typedef enum
	{
	FCM_REGISTER,
	FCM_DEREGISTER,
	FCM_WHAT_YA_GOT,
	FCM_TEST,
	MAX_FC_MGR_TOKENS
	}FC_MGR_TOKEN;

typedef struct
	{
	UINT16 token;	//FCM_REGISTER, FCM_DEREGISTER
	char name[20];
	pid_t myPid;
	}FCM_REGISTER_MSG;

typedef struct
	{
	UINT16 token; 	//FCM_WHAT_YA_GOT
	}FCM_WHAT_YA_GOT_MSG;

typedef struct
	{
	UINT16 token; 	//FCM_TEST
	char str[80];
	}FCM_TEST_MSG;

#endif
