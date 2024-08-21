/*************************************************************

FILE:		statemachineHandlers.c

DESCRIPTION:	
This contains the generic handlers for the statemachine module. 

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
$Log: statemachineHandlers.c,v $
Revision 1.1  2006/06/26 18:03:16  bobfcsoft
statemachine

=======================================================

*************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>     // for memcpy

#include "statemachineDefs.h"
#include "statemachineMsgs.h"

#define _ALLOC extern
#include "statemachine.h"
#undef _ALLOC

#include "statemachineProto.h"
#include "loggerProto.h"
#include "simplProto.h"

/*==============================================
	hndlCommonMsgs - entry point
==============================================*/
void hndlCommonMsgs(char *sender, int token)
{
static char *fn="hndlCommonMsgs";

switch(token)
	{
	case SM_DELETE_REC:
		{
		SM_DELETE_MSG *inMsg;

		inMsg=(SM_DELETE_MSG *)inArea;

		fcLogx(__FILE__, fn,
			globalMask,
			TRACE_MARK,
			"DELETE list=%d ID=%d",
			inMsg->list,
			inMsg->ID
			);
		
		Reply(sender,NULL,0);
		
		deleteRec(inMsg->list, inMsg->ID);
		}
		break;

	case SM_ADD_REC:
		{
		SM_REC_MSG *inMsg;

		inMsg=(SM_REC_MSG *)inArea;

		fcLogx(__FILE__, fn,
			globalMask,
			TRACE_MARK,
			"ADD_REC list=%d nbytes=%d",
			inMsg->list,
			inMsg->nbytes
			);
		
		Reply(sender,NULL,0);
		
		addNewRec(inMsg->list, &inMsg->mydata, inMsg->nbytes);
		}
		break;

	case SM_OVERWRITE_REC:
		{
		SM_REC_MSG *inMsg;

		inMsg=(SM_REC_MSG *)inArea;

		fcLogx(__FILE__, fn,
			globalMask,
			TRACE_MARK,
			"OVERWRITE_REC list=%d nbytes=%d",
			inMsg->list,
			inMsg->nbytes
			);
		
		Reply(sender,NULL,0);
		
		overwriteRec(inMsg->list, &inMsg->mydata, inMsg->nbytes);
		}
		break;

	case SM_RESYNC:
		{
		SM_RESYNC_MSG *inMsg;

		inMsg=(SM_RESYNC_MSG *)inArea;
		
		fcLogx(__FILE__, fn,
			globalMask,
			TRACE_MARK,
			"RESYNC: file=<%s>",
			inMsg->filename);
		
		Reply(sender,NULL,0);
		
		loadData(inMsg->filename); 
		}
		break;

	case SM_DUMP:
		{
		fcLogx(__FILE__, fn,
			globalMask,
			TRACE_MARK,
			"DUMP"
			);
		
		Reply(sender,NULL,0);
		
		dumpTable();
		}
		break;

	default:
		fcLogx(__FILE__, fn,
			TRACE_MARK,
			TRACE_MARK,
			"unknown token=%d",token);

		Reply(sender,NULL,0);
		break;
	} // end switch

} // end hndlCommonMsgs

