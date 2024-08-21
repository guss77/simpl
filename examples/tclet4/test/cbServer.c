/*======================================
	cbServer.c

Description:
This module is used to receive a callback message from GUI
in tclet4 example.

-----------------------------------------------------------------------
    Copyright (C) 2000,2007 FCSoftware Inc. 

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
 *$Log: cbServer.c,v $
 *Revision 1.1  2007/07/27 14:16:01  bobfcsoft
 *new cvs file
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/timeb.h>

#include "tclet4Msgs.h"
#include "cbServerMsgs.h"

#define _ALLOC
#include "cbServer.h"
#include "loggerVars.h"
#undef _ALLOC

#include "cbServerProto.h"
#include "ipcProto.h"
#include "loggerProto.h"

/*--------------------------------------
	cbServer - entry point
--------------------------------------*/
int main(int argc, char **argv, char **envp)
{
static char *fn="cbServer";
UINT16 *token;
int nbytes;
CALL_BACK_WHAT_YA_GOT_MSG *outMsg;

printf("%s:starting\n",fn);

initialize(argc, argv);

outMsg = (CALL_BACK_WHAT_YA_GOT_MSG *)outArea;
outMsg->token = CALL_BACK_WHAT_YA_GOT;
nbytes=sizeof(CALL_BACK_WHAT_YA_GOT_MSG);

fcLogx(__FILE__, fn,
	globalMask,
	CB_SERVER_MISC,
	"sending WHAT_YA_GOT to <%s>",
	toName);


token=(UINT16 *)inArea;
while(1)
	{
	loadSend(outArea,nbytes);
	sendMsg(toPid);
	retrieveReply(inArea);

	switch(*token)
		{
		case CALL_BACK_REQUEST:
			{
			CALL_BACK_REQUEST_MSG *inMsg;
			CALL_BACK_RESPONSE_MSG *outMsg;
			
			inMsg=(CALL_BACK_REQUEST_MSG *)inArea;
			fcLogx(__FILE__, fn,
				globalMask,
				CB_SERVER_MISC,
				"CALL funcID=%d callback=<%s>",
				inMsg->funcID,
				inMsg->callBackFunction);

			outMsg=(CALL_BACK_RESPONSE_MSG *)outArea;
			outMsg->token=CALL_BACK_RESPONSE;
			outMsg->funcID=inMsg->funcID;
			sprintf(outMsg->callBackFunction,"%.19s", inMsg->callBackFunction);
			
			sprintf(outMsg->data,"%s", cb1(inMsg->data));
			nbytes=sizeof(CALL_BACK_RESPONSE_MSG);

fcLogx(__FILE__, fn,
	globalMask,
	CB_SERVER_MISC,
	"sending %d bytes as RESPONSE",
	nbytes);


			}
			break;

		default:
			fcLogx(__FILE__, fn,
				globalMask,
				CB_SERVER_MISC,
				"unknown token=%d",
				*token);

			nbytes=0;
			break;
		}
	} // end while

printf("%s:done\n",fn);
detachName();

return(1);
}// end cbServer

/*============================================
	initialize - entry point
============================================*/
void initialize(int argc, char **argv)
{
static char *fn="initialize";
int i;                          /* loop variable */
int j;
char myName[20];
char loggerName[20];
int rc;
FCID who;

globalMask=0xff;
myName[0]=0;
toName[0]=0;
loggerName[0]=0;


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

			case 't':
                                for(;*p != 0; p++);
				sprintf(toName,"%s",++p);

				for(j=0; j<3; j++)  // try 4 times
					{
					who=nameLocatex(toName);
					if(who.slot != -1) break;

printf("Unable to locate tclet named <%s>\n", toName);
printf("Make sure this applet is running then\n");
printf("hit any key to try nameLocate again");
fgetc(stdin);

					}

				if(who.slot == -1)
					{
					printf("%s: unable to locate <%s>\n",
						fn,
						toName);
					detachName();
					exit(0);
					}
				else
					{
					toPid = who.fd;
					printf("located <%s> pid=%d\n",toName,toPid);
					}
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

if(toName[0] == 0)
	{
	myUsage();
	exit(0);
	}

logger_FCID = is_logger_upx(loggerName);

fcLogx(__FILE__, fn,
	globalMask,
	CB_SERVER_MISC,
	"ding toName=<%s>"
	);

} /* end initialize */

/*===================================================
	myUsage - entry point
===================================================*/
void myUsage()
{
printf("======================= usage =====================================\n");
printf(" usage for cbServer:\n");
printf("     cbServer -n <myName> -t <tcletName> <optionals>\n");
printf("     where optionals are:\n");
printf("        -l <loggerName> - connect to trace logger\n");
printf("===================================================================\n");
}// end myUsage
