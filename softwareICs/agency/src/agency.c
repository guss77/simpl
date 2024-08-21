/*************************************************************

FILE:		agency.c

DESCRIPTION:	
This program is an example of a SIMPL enabled agency module. 

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
$Log: agency.c,v $
Revision 1.2  2008/08/11 21:21:40  bobfcsoft
wrapped message from requestor

Revision 1.1  2007/07/27 14:10:49  bobfcsoft
new cvs file

Revision 1.4  2003/04/03 16:22:12  root
more warning cleanup

Revision 1.3  2003/04/03 16:19:33  root
RedHat 7.x warning cleanup

Revision 1.2  2002/12/03 20:59:54  root
v2.0 compatible

Revision 1.1  2002/10/29 18:20:51  root
Initial revision

=======================================================

*************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "agencyMsgs.h"
#define _ALLOC
#include "agency.h"
#undef _ALLOC

#include "agencyProto.h"
#include "loggerProto.h"
#include "simplProto.h"

/*=========================================================
	main - entry point
=========================================================*/
int main(int argc, char **argv)
{
static char *fn="agency";
int x_it=0;
int nbytes;			
char *sender;
UINT16 *token;

// parse the command line args
initialize(argc, argv);

fcLogx(__FILE__, fn,
	globalMask,
	AGENCY_FUNC_IO,
	"ding");

token = (UINT16 *)inArea;

while(!x_it)
	{
	nbytes = Receive(&sender, inArea, MAX_MSG_BUFFER_SIZE);
		
	switch(*token)
		{
		case AGENCY_WHAT_YA_GOT:
			fcLogx(__FILE__, fn,
				globalMask,
				AGENCY_MISC,
				"WHAT_YA_GOT"
				);

			dequeueMsg(sender);
			break;

		case AGENCY_REPLY:
			{
			AGENCY_WRAP_MSG *inMsg;

			inMsg=(AGENCY_WRAP_MSG *)inArea;

			fcLogx(__FILE__, fn,
				globalMask,
				AGENCY_MISC,
				"REPLY of %d bytes for requestor %X",
				inMsg->nbytes,
				inMsg->sender
				);

			Reply(inMsg->sender, (char *)&inMsg->mark, inMsg->nbytes);

			dequeueMsg(sender);
			}
			break;

		case AGENCY_PROCESS_THIS:
			{
			AGENCY_WRAP_MSG *inMsg;
			void *msgArea;

			inMsg=(AGENCY_WRAP_MSG *)inArea;

			fcLogx(__FILE__, fn,
				globalMask,
				AGENCY_MISC,
				"AGENT_TEST agentPending=%X",
				agentPending
				);

			msgArea=createMsg(nbytes);
			if(msgArea != NULL)
				{
				memcpy(msgArea,inArea,nbytes);
					
				if(agentPending != NULL)
				 	{
					replyToAgent(agentPending,
						sender,
						nbytes,
						msgArea);							
					destroyMsg(msgArea);
					}
				else
					{
					queueMsg(sender,msgArea,nbytes);
					printf("message queued\n");
					}
				}
			else
				{
				fcLogx(__FILE__, fn,
					globalMask,
					AGENCY_MARK,
					"unable to process TEST message"
					);
				Reply(sender, NULL, 0);
				}
			}
			break;

		default:
			printf("%s:unknown token=%d\n",fn,*token);
// send back a NULL reply immediately

			Reply(sender, NULL, 0);
			break;
		} // end switch

	} // end while

name_detach();

exit(0);
} // end agency
