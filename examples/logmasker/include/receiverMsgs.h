
/*************************************************************

FILE:		receiverMsgs.h

DESCRIPTION:	
This file contains

AUTHOR:		R.D. Findlay

-------------------------
FCsoftware Inc. 1999, 2007
This code is released as open source.   We hope you find 
it useful.  If you discover a bug or add an enhancement 
contact us on the SIMPL project mailing list. 

-------------------------

Revision history:
=======================================================
$Log: receiverMsgs.h,v $
Revision 1.1  2007/07/24 20:57:54  bobfcsoft
new file

=======================================================

*************************************************************/

#ifndef _RECEIVER_MSGS_DEF
#define _RECEIVER_MSGS_DEF

typedef enum
	{
	FC_SET_LOG_MASK=0xfc00,
	MAX_RECEIVER_TOKENS
	}RECEIVER_TOKEN;

typedef struct
	{
	RECEIVER_TOKEN token;	// FC_SET_LOG_MASK
	unsigned int logMask;	// new log mask
	}FC_SET_LOG_MASK_MSG;

#endif
