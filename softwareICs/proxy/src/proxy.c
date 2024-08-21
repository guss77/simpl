/*************************************************************

FILE:		proxy.c

DESCRIPTION:	
This program is an example of a proxy softwareIC. 

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
$Log: proxy.c,v $
Revision 1.2  2011/09/08 16:41:45  bobfcsoft
explicit select header

Revision 1.1  2006/06/21 21:05:44  bobfcsoft
new proxy code

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/shm.h>
#include <sys/select.h>

#include "proxyMsgs.h"

#define _ALLOC
#include "proxy.h"
#undef _ALLOC

#include "proxyProto.h"
#include "simplProto.h"
#include "loggerProto.h"

/*===============================================
	proxy - entry point
===============================================*/
int main(int argc, char **argv, char **envp)
{
static char *fn="proxy";
int i;
int x_it=0;
char *sender;

initialize(argc, argv);

fcLogx(__FILE__, fn,
	globalMask,
	PROXY_MARK,
	"starting"
	);

while(!x_it)
	{
	inset = watchset;
	select(maxfd+1, &inset, NULL, NULL, NULL);

// Is this from special fifo
	if(FD_ISSET(my_fds[1], &inset))  //  special fifo is ready
		{
		int *theID;

		theID = (int *)inArea;

		read(ZFifoID,inArea,4);

		fcLogx(__FILE__, fn,
			globalMask,
			PROXY_MISC,
			"special fifo ready,  theID=%d",
			*theID
			);

		if(proxyTable[*theID].recvID == -1)
			{
			char fullrecvName[20];

			sprintf(fullrecvName,"%s_%02d", recv_name, *theID);
			proxyTable[*theID].recvID=name_locate(fullrecvName);

		fcLogx(__FILE__, fn,
			globalMask,
			PROXY_MISC,
			"recvName=<%s> proxyTable[%d].recvID=%d",
			fullrecvName,
			*theID,
			proxyTable[*theID].recvID
			);

			}

		proxyTable[*theID].status = 1;
		}
	else
// Is this from SIMPL fifo
	if(FD_ISSET(my_fds[0], &inset))  //  receive is ready
		{
		int *shmID;

		shmID = (int *)inArea;

		read(my_fds[0],inArea,4); // read in shmID
		
		fcLogx(__FILE__, fn,
			globalMask,
			PROXY_MISC,
			"SIMPL fifo ready,  sender shmID=%d",
			*shmID
			);

		for(i=0; i<64; i++)
			{
			if(proxyTable[i].status == 1)
				{
				write(proxyTable[i].recvID,inArea,4);
				proxyTable[i].status = 0;

		fcLogx(__FILE__, fn,
			globalMask,
			PROXY_MISC,
			"relay to recvID=%d at slot=%d",
			i,
			proxyTable[i].recvID
			);

				break;
				}
			} // for i

		if(i == 64) // ie. nothing available
			{
			RELAY_ERROR_MSG *outMsg;

			sender = shmat(*shmID, 0, 0); // connect to sender shm

			outMsg=(RELAY_ERROR_MSG *)outArea;
			outMsg->token = RELAY_ERROR;

			Reply(sender,outArea,sizeof(RELAY_ERROR_MSG));
			} // end if i

		} // end if
	} // end while

fcLogx(__FILE__, fn,
	globalMask,
	PROXY_FUNC_IO,
	"done");

name_detach();

exit(0);

}// end proxy
