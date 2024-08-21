/*======================================
	fcTester.c
-----------------------------------------------------------------------
    Copyright (C) 1998, 2002, 2007 FCSoftware Inc. 

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

    If you discover a bug or add an enhancement contact us on the
    SIMPL project mailing list. 

-----------------------------------------------------------------------
======================================*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

#include "standardTypes.h"
#include "simpl.h"

int logger;
int receiver;
static char logBuf[512];

#define FC_TESTING 	99

typedef struct
	{
	UINT16 token;
	char data;
	}FC_CONTAINER_MSG;

#define DB_RESET	19
#define TEST_PROXY	20

typedef struct
	{
	UINT16 token; 				// DB RESET
	int node;
	}TO_DB_RESET_MSG;

typedef struct
	{
	UINT16 token; 				// TEST_PROXY
	UINT16 proxy;
	}TEST_PROXY_MSG;

FC_CONTAINER_MSG *outMsg;
char outArea[8192];

#include "simplProto.h"
void initialize(int, char **);
void fclog(char *);


/*--------------------------------------
	fcTester - entry point
--------------------------------------*/
int main(int argc, char **argv, char **envp)
{
static char *fn="fcTester";
int x_it=0;
char mybuf[80];

initialize(argc, argv);

sprintf(logBuf,"%s:starting",fn);
fclog(logBuf);

outMsg=(FC_CONTAINER_MSG *)outArea;
outMsg->token = FC_TESTING;

while(!x_it)
	{
	printf("What do you want to do? ");
	fgets(mybuf,80,stdin);

	switch(mybuf[0])
		{
		case 'q':
			x_it=1;
			break;

		case 'r': // reset
			{
			TO_DB_RESET_MSG *dbMsg;

printf("reset\n");
			dbMsg=(TO_DB_RESET_MSG *)&outMsg->data;
			dbMsg->token = DB_RESET;
			dbMsg->node = 1;
#if 0
			loadSend(outArea,sizeof(TO_DB_RESET_MSG)+2);
			sendMsgx(receiver);
#endif
			Send(receiver,outArea,NULL,sizeof(TO_DB_RESET_MSG)+2,0);
			}
			break;
				
		case 'p': // proxy
			{
			TEST_PROXY_MSG *proxyMsg;
			int myProxy=33;
			int rc;

printf("proxy=%d\n",myProxy);

			proxyMsg=(TEST_PROXY_MSG *)&outMsg->data;
			proxyMsg->token = TEST_PROXY;
			proxyMsg->proxy = myProxy;
printf("8 bytes out\n");

#if 0
			loadSend(outArea,8);
			sendMsgx(receiver);
			rc=receiveMsg(&msg,&nbytes);
#endif
			Send(receiver,outArea,NULL,8,0);

printf("rc=%X\n",rc);
			}
			break;
				
		default:
			printf("unknown command %s\n",mybuf);
			break;
		}
	}

name_detach();

return(1);

}// end fcTester

/*============================================
	initialize - entry point
============================================*/
void initialize(int argc, char **argv)
{
static char *fn="initialize";
int i;                          /* loop variable */

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
				name_attach(++p, NULL);
printf("myname: %s\n",p);
                                break;

			case 'l':
                                for(;*p != 0; p++);
				logger=name_locate(++p);
printf("Logger: %s\n",p);
				break;

			case 'r':
                                for(;*p != 0; p++);
				receiver=name_locate(++p);
printf("Receiver: %s\n",p);
				break;

                        default:
				printf("%s:unknown arg %s\n",fn, p);
                                break;
                        }/*end switch*/
                } /* end if *p */
        }/*end for i*/


} /* end initialize */

/*================================
	fclog
================================*/
void fclog(char *logMsg)
{
#if 0
static char *fn="fclog";
#endif
char *p;

p=outArea;
sprintf(p,"%.255s",logMsg);
#if 0
loadSend(p,strlen(p)+1);
sendMsgx(logger);
#endif
Send(logger,p,NULL,strlen(p)+1,0);
} // end fclog
