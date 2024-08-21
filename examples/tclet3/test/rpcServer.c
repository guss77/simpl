/*======================================
	rpcServer.c

Description:
This module is used to receive a RPC message from GUI
in tclet3 example.

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
======================================*/
/*
 *$Log: rpcServer.c,v $
 *Revision 1.1  2007/07/26 16:09:43  bobfcsoft
 *new file
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/timeb.h>

#include "tclet3Msgs.h"
#include "rpcServerMsgs.h"

#define _ALLOC
#include "rpcServer.h"
#include "loggerVars.h"
#undef _ALLOC

#include "rpcServerProto.h"
#include "ipcProto.h"
#include "loggerProto.h"

/*--------------------------------------
	rpcServer - entry point
--------------------------------------*/
int main(int argc, char **argv, char **envp)
{
static char *fn="rpcServer";
UINT16 *token;
int fromWhom;
char *msg;
int nbytes;

printf("%s:starting\n",fn);

initialize(argc, argv);

token=(UINT16 *)inArea;
while(1)
	{
	fromWhom = receiveMsg(&msg, &nbytes);
	memcpy(inArea,msg,nbytes);

	switch(*token)
		{
		case RPC_CALL:
			{
			RPC_CALL_MSG *inMsg;
			RPC_CALL_MSG *outMsg;
			static int count;
			
			inMsg=(RPC_CALL_MSG *)inArea;
			fcLogx(__FILE__, fn,
				globalMask,
				RPC_SERVER_MISC,
				"RPC_CALL funcID=%d",
				inMsg->funcID);

			outMsg=(RPC_CALL_MSG *)outArea;
			outMsg->token=RPC_CALL;
			sprintf(outMsg->data,"%s", makeRPCcall(inMsg->funcID, inMsg->data));

			loadReply(fromWhom,outArea,sizeof(RPC_CALL_MSG));
			replyMsg(fromWhom);
			}
			break;

		default:
			fcLogx(__FILE__, fn,
				globalMask,
				RPC_SERVER_MISC,
				"unknown token=%d",
				*token);

			loadReply(fromWhom,NULL,0);
			replyMsg(fromWhom);
			break;
		}
	} // end while

printf("%s:done\n",fn);
detachName();

return(1);
}// end rpcServer

/*============================================
	RPC call - entry point
============================================*/
char *makeRPCcall(UINT16 funcID, char *data)
{
static char *fn="makeRPCcall";
static char outdata[80];	// return stuff goes here

fcLogx(__FILE__, fn,
	globalMask,
	RPC_SERVER_FUNC_IO,
	"ding"
	);

switch(funcID)
	{
	case RPC1:
		{
		RPC1_MSG *inparam;
		RPC1_MSG *outparam;
		inparam = (RPC1_MSG *)data;
		outparam = (RPC1_MSG *)outdata;

fcLogx(__FILE__, fn,
	globalMask,
	RPC_SERVER_MISC,
	"incoming color=<%s>",
	inparam->color
	);

		sprintf(outparam->color,"%.19s",rpc1(inparam->color));

fcLogx(__FILE__, fn,
	globalMask,
	RPC_SERVER_MISC,
	"returned color=<%s>",
	outparam->color
	);

		}
		break;
	}

return(outdata);

} // end makeRPCcall

/*============================================
	initialize - entry point
============================================*/
void initialize(int argc, char **argv)
{
static char *fn="initialize";
int i;                          /* loop variable */
char myName[20];
char loggerName[20];
int rc;

globalMask=0xff;
myName[0]=0;
loggerName[0]=0;
myMsg[0]=0;

sprintf(myMsg,"hello there");

/*===============================================
  process command args
===============================================*/
for(i=1; i<=argc; ++i)
        {
        char *p = argv[i];

        if(p == NULL) continue;

        if(*p == '-')
                {
                switch(*++p)
                        {
                        case 'n':
                                for(;*p != 0; p++);
				sprintf(myName,"%s",++p);
				rc=attachName(myName, 1024, NULL);
				if(rc == -1)
					{
					printf("%s: unable to attach as <%s>\n",
						fn,
						myName);
					exit(0);
					}
				else
					printf("attached as <%s> rc=%d\n",myName,rc);
                                break;

			case 'm':
                                for(;*p != 0; p++);
				sprintf(myMsg,"%s",++p);
				break;

			case 'l':
                                for(;*p != 0; p++);
				sprintf(loggerName,"%.19s",++p);
				break;

                        default:
				printf("%s:unknown arg %s\n",fn, p);
                                break;
                        }/*end switch*/
                } /* end if *p */
        }/*end for i*/

// if manditory name is not supplied show usage
if(myName[0] == 0)
	{
	myUsage();
	exit(0);
	}

logger_FCID = is_logger_upx(loggerName);

fcLogx(__FILE__, fn,
	globalMask,
	RPC_SERVER_MISC,
	"ding"
	);

} /* end initialize */

/*===================================================
	myUsage - entry point
===================================================*/
void myUsage()
{
printf("======================= usage =====================================\n");
printf(" usage for rpcServer:\n");
printf("     rpcServer -n <myName> <optionals>\n");
printf("     where optionals are:\n");
printf("        -l <loggerName> - connect to trace logger\n");
printf("===================================================================\n");
}// end myUsage
