/*************************************************************

FILE:		fcMgr.c

DESCRIPTION:	
This program is an example of a broadcaster softwareIC. 
This program is closely connected with the fcBroadcaster app.

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
$Log: fcMgr.c,v $
Revision 1.2  2009/04/14 15:51:07  bobfcsoft
cleanup

Revision 1.1  2007/07/27 14:13:04  bobfcsoft
new cvs file

Revision 1.3  2003/04/03 16:34:23  root
fixed RedHat 7.x warnings

Revision 1.2  2002/12/03 21:12:55  root
v2.0 compatible

Revision 1.1  2002/10/30 15:59:12  root
Initial revision
=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "fcMgrMsgs.h"

#define _ALLOC
#include "fcMgr.h"
#undef _ALLOC

#include "fcMgrProto.h"
#include "simplProto.h"
#include "loggerProto.h"

/*===============================================
	fcMgr - entry point
===============================================*/
int main(int argc, char **argv, char **envp)
{
static char *fn="fcMgr";
int x_it=0;
int nbytes;			
char *sender;
UINT16 *token;

initialize(argc, argv);

fcLogx(__FILE__, fn,
	globalMask,
	FC_MGR_MARK,
	"starting"
	);

while(!x_it)
	{
	token=(UINT16 *)inArea;

	nbytes = Receive(&sender, inArea, MAX_MSG_SIZE);

	switch(*token)
		{
		case FCM_REGISTER:
			{
			FCM_REGISTER_MSG *inMsg;
			FCM_REGISTER_MSG *outMsg;
			void *msgArea;

			inMsg=(FCM_REGISTER_MSG *)inArea;

			fcLogx(__FILE__, fn,
				globalMask,
				FC_MGR_MISC,
				"REGISTER name=<%s> pid=%d",
				inMsg->name,
				inMsg->myPid
				);

if(!backgroundMode)
	{
printf("%s: REGISTER name=<%s> pid=%d\n",
	fn,
	inMsg->name,
	inMsg->myPid);

	fflush(stdout);
	}

			msgArea=createMsg(sizeof(FCM_REGISTER_MSG));
			if(msgArea != NULL)
				{
				outMsg=(FCM_REGISTER_MSG *)msgArea;

				outMsg->token = FCM_REGISTER;
				sprintf(outMsg->name,
					"%.19s",
					inMsg->name);
				outMsg->myPid=inMsg->myPid;
					
				if(broadcasterPending != NULL)
				 	{
					Reply(broadcasterPending, (char *)msgArea, sizeof(FCM_REGISTER_MSG));
					broadcasterPending=NULL;

					free(msgArea);
					}
				else
					{
					queueMsg(msgArea,
					   sizeof(FCM_REGISTER_MSG));
					}
				}
			else
				{
				fcLogx(__FILE__, fn,
					globalMask,
					FC_MGR_MARK,
					"unable to process REGISTRATION for <%s> pid=%d",
					inMsg->name,
					inMsg->myPid
					);
				}

			Reply(sender, NULL, 0);
			}
			break;

		case FCM_DEREGISTER:
			{
			FCM_REGISTER_MSG *inMsg;
			FCM_REGISTER_MSG *outMsg;
			void *msgArea;

			inMsg=(FCM_REGISTER_MSG *)inArea;

			fcLogx(__FILE__, fn,
				globalMask,
				FC_MGR_MISC,
				"DEREGISTER pid=%d",
				inMsg->myPid
				);

if(!backgroundMode)
	{
printf("%s: DEREGISTER pid=%d\n",
	fn,
	inMsg->myPid);

	fflush(stdout);
	}

			msgArea=createMsg(sizeof(FCM_REGISTER_MSG));
			if(msgArea != NULL)
				{
				outMsg=(FCM_REGISTER_MSG *)msgArea;

				outMsg->token = FCM_DEREGISTER;
				outMsg->myPid=inMsg->myPid;
					
				if(broadcasterPending != NULL)
				 	{
					Reply(broadcasterPending, (char *)msgArea, sizeof(FCM_REGISTER_MSG));
					broadcasterPending=NULL;
					free(msgArea);
					}
				else
					{
					queueMsg(msgArea,
					   sizeof(FCM_REGISTER_MSG));
					}
				}
			else
				{
				fcLogx(__FILE__, fn,
					globalMask,
					FC_MGR_MARK,
					"unable to process DEREGISTRATION for pid=%d",
					inMsg->myPid
					);
				}

			Reply(sender, NULL, 0);	
			}
			break;

		case FCM_TEST:
			{
			FCM_TEST_MSG *inMsg;
			FCM_TEST_MSG *outMsg;
			void *msgArea;

			inMsg=(FCM_TEST_MSG *)inArea;

			fcLogx(__FILE__, fn,
				globalMask,
				FC_MGR_MISC,
				"TEST str=<%s>",
				inMsg->str
				);

if(!backgroundMode)
	{
printf("%s:TEST str=<%s>\n",
	fn,
	inMsg->str
	);

	fflush(stdout);
	}
			msgArea=createMsg(sizeof(FCM_TEST_MSG));
			if(msgArea != NULL)
				{
				outMsg=(FCM_TEST_MSG *)msgArea;

				outMsg->token = FCM_TEST;
				sprintf(outMsg->str,"%s",inMsg->str);
					
				if(broadcasterPending != NULL)
				 	{
					Reply(broadcasterPending, (char *)msgArea, sizeof(FCM_TEST_MSG));
					broadcasterPending=NULL;
					free(msgArea);
					}
				else
					{
					queueMsg(msgArea,
					   sizeof(FCM_TEST_MSG));
					}
				}
			else
				{
				fcLogx(__FILE__, fn,
					globalMask,
					FC_MGR_MARK,
					"unable to process TEST message"
					);
				}
			Reply(sender, NULL, 0);
			}
			break;

		case FCM_WHAT_YA_GOT:
			fcLogx(__FILE__, fn,
				globalMask,
				FC_MGR_MARK,
				"WHAT_YA_GOT"
				);

if(!backgroundMode)
	{
printf("%s: WHAT_YA_GOT\n",fn);

	fflush(stdout);
	}

			if(dequeueMsg(sender) != -1)
				{
				broadcasterPending=NULL;
				}
			else
				{
				broadcasterPending=sender;
				}
			break;

		default:
			Reply(sender, NULL, 0);
			fcLogx(__FILE__, fn,
				globalMask,
				FC_MGR_MARK,
				"unknown token=%d",
				*token
				);
if(!backgroundMode)
	{
	printf("%s:unknown token=%d\n",fn,*token);

	fflush(stdout);
	}
			break;
		}

	} // end while

fcLogx(__FILE__, fn,
	globalMask,
	FC_MGR_FUNC_IO,
	"done");

name_detach();

exit(0);

}// end fcMgr
