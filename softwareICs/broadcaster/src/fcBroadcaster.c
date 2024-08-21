/*************************************************************

FILE:		fcBroadcaster.c

DESCRIPTION:	
This program is an example of a broadcaster software IC. 
This program exists as a closely linked pair with the 
fcMgr receiver app.

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
$Log: fcBroadcaster.c,v $
Revision 1.1  2007/07/27 14:13:04  bobfcsoft
new cvs file

Revision 1.3  2003/04/03 16:32:54  root
fixed RedHat 7.x warnings

Revision 1.2  2002/12/03 21:12:46  root
v2.0 compatible

Revision 1.1  2002/10/30 15:59:05  root
Initial revision

=======================================================

*************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>   // for select stuff

#include "fcMgrMsgs.h"
#define _ALLOC
#include "fcBroadcaster.h"
#undef _ALLOC

#include "fcBroadProto.h"
#include "loggerProto.h"
#include "simplProto.h"

/*=========================================================
	main - entry point
=========================================================*/
int main(int argc, char **argv)
{
static char *fn="broadcaster";
int x_it=0;
UINT16 *token;
FCM_WHAT_YA_GOT_MSG *outMsg;

initialize(argc, argv);

fcLogx(__FILE__, fn,
	globalMask,
	FCB_FUNC_IO,
	"ding");

token=(UINT16 *)inArea;
outMsg=(FCM_WHAT_YA_GOT_MSG *)outArea;
while(!x_it)
	{
	outMsg->token = FCM_WHAT_YA_GOT;
#if 0
	loadSend(outArea,sizeof(FCM_WHAT_YA_GOT_MSG));
	sendMsgx(fcMgrID);
	retrieveReply(inArea);
#endif
	Send(fcMgrID, outArea, inArea, sizeof(FCM_WHAT_YA_GOT_MSG), MAX_MSG_BUFFER_SIZE);

	switch(*token)
		{
		case FCM_REGISTER:
			{
			FCM_REGISTER_MSG *inMsg;

			inMsg=(FCM_REGISTER_MSG *)inArea;

			fcLogx(__FILE__, fn,
				globalMask,
				FCB_MISC,
				"REGISTER name=<%s> pid=%d",
				inMsg->name,
				inMsg->myPid);

printf("%s:REGISTER name=<%s> pid=%d\n",
	fn,
	inMsg->name,
	inMsg->myPid);

			registerMe(inMsg->name, inMsg->myPid);
			}
			break;


		case FCM_DEREGISTER:
			{
			FCM_REGISTER_MSG *inMsg;

			inMsg=(FCM_REGISTER_MSG *)inArea;

			fcLogx(__FILE__, fn,
				globalMask,
				FCB_MISC,
				"DEREGISTER pid=%d",
				inMsg->myPid);

printf("%s: DEREGISTER pid=%d\n",
	fn,
	inMsg->myPid);

			deregisterMe(inMsg->myPid);
			}
			break;

		case FCM_TEST:
			{
			FCM_TEST_MSG *inMsg;

			inMsg=(FCM_TEST_MSG *)inArea;

			fcLogx(__FILE__, fn,
				globalMask,
				FCB_MISC,
				"TEST str=<%s>",
				inMsg->str);

printf("%s:UPDATE str=<%s>\n",
	fn,
	inMsg->str);

			broadcastTo(inArea, sizeof(FCM_TEST_MSG));
			}
			break;

		default:
			printf("%s:unknown token=%d\n",fn,*token);
			break;
		}
	} // end while

#if 0
detachName();
#endif
name_detach();

exit(0);

} // end fcBroadcaster
