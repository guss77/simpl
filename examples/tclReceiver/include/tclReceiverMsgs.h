
/*************************************************************

FILE:		tclReceiverMsgs.h

DESCRIPTION:	
This file contains message and token definitions

AUTHOR:		R.D. Findlay

-------------------------
FCsoftware Inc. 1999, 2007
This code is released as open source.   We hope you find 
it useful.  If you discover a bug or add an enhancement 
contact us on the SIMPL project mailing list. 

-------------------------

Revision history:
=======================================================
$Log: tclReceiverMsgs.h,v $
Revision 1.1  2007/07/24 21:09:29  bobfcsoft
new file

=======================================================

*************************************************************/

#ifndef _TCLRECEIVER_MSGS_DEF
#define _TCLRECEIVER_MSGS_DEF

#include "standardTypes.h"   // for UINT16 etc

typedef enum
	{
	FC_TESTING=0xa0,
	FC_QUIT,
	MAX_TCL_RECEIVER_TOKENS
	}TCL_RECEIVER_TOKEN;

typedef struct
	{
	UINT16 token;		// FC_TESTING
	char text[80];
	}FC_TESTING_MSG;

typedef struct
	{
	UINT16 token;		// FC_QUIT
	}FC_QUIT_MSG;

#endif
