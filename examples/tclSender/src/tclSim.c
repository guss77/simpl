/*=======================================================
FILE:	tclStim.c

DESCRIPTION:
This module is used to simulate a SIMPL receiver
for the tclSender.tcl script.

-------------------------
FCsoftware Inc. 2000, 2002, 2007

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

If you discover a bug or add an enhancement 
contact us on the SIMPL project mailing list. 

-------------------------
Revision history:
$Log: tclSim.c,v $
Revision 1.1  2007/07/24 21:04:05  bobfcsoft
new file

========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "tclSimMsgs.h"
#define _ALLOC
#include "tclSim.h"
#undef _ALLOC

#include "tclSimProto.h"
#include "simplProto.h"
#include "loggerProto.h"

/*--------------------------------------
	tclSim - entry point
--------------------------------------*/
void main(int argc, char **argv, char **envp)
{
static char *fn="tclSim";
char *p;
int x_it=0;
int n;
char *sender;

// for keyboard input
p=data;

initialize(argc,argv);


while(!x_it)
	{
	printf("Enter command: ");
	fflush(stdout);
	
	inset = watchset;
	select(maxfd+1, &inset, NULL, NULL, NULL);

// check which file descriptors are ready to be read from

// Is this from keyboard
	if(FD_ISSET(my_fds[0], &inset))  // keyboard is ready
		{
		n=read(my_fds[0],p,80);
		p[n-1]=0;

		fcLogx(__FILE__, fn,
			globalMask,
			TCLSIM_MARK,
			"%d bytes recd str=<%s>",n,p);

		switch(data[0])
			{
			case '?':  // help
				showUsage();
				break;

			case 'q':  // quit
				{
				FC_TESTING_MSG *outMsg;

				x_it=1;
				
				if(sender != NULL)
					{
					fcLogx(__FILE__, fn,
						globalMask,
						TCLSIM_MARK,
						"replying FC_TESTING -> id=%X with text=<%s>",
						sender,
						&p[2]);

#if 0
				printf("\nreplying <%s> to %X\n",
					&p[2],sender);
#endif

					outMsg=(FC_TESTING_MSG *)outArea;
					outMsg->token = FC_TESTING;
					sprintf(outMsg->text,"quit");
					Reply(sender,outArea,sizeof(FC_TESTING_MSG));
					sender=NULL;
					}
				}
				break;

			case 'r':  // text
				{
				FC_TESTING_MSG *outMsg;

				if(sender != NULL)
					{
					fcLogx(__FILE__, fn,
						globalMask,
						TCLSIM_MARK,
						"replying FC_TESTING -> id=%X with text=<%s>",
						sender,
						&p[2]);

#if 0
				printf("\nreplying <%s> to %X\n",
					&p[2],sender);
#endif

					outMsg=(FC_TESTING_MSG *)outArea;
					outMsg->token = FC_TESTING;
					sprintf(outMsg->text,"%.79s",&p[2]);
					Reply(sender,outArea,sizeof(FC_TESTING_MSG));
					sender=NULL;
					}
				}
				break;

			default:
				printf("\nunknown command <%s>\n",p);
				break;
			} // end switch
		} // end if keyboard
	else
// Is this from receive fifo
	if(FD_ISSET(my_fds[1], &inset))  //  receive is ready
		{
		int nbytes;			
		UINT16 *token;

		token=(UINT16 *)inArea;

		nbytes = Receive(&sender, inArea, MAX_MSG_BUFFER_SIZE);

		fcLogx(__FILE__, fn,
			globalMask,
			TCLSIM_MARK,
			"token=%X",
			*token);
		
		switch(*token)
			{
			case FC_TESTING:
				{
				FC_TESTING_MSG *inMsg;
				
				inMsg=(FC_TESTING_MSG *)inArea;
				
				fcLogx(__FILE__, fn,
					globalMask,
					TCLSIM_MARK,
					"recvd FC_TESTING with text=<%s>",
					inMsg->text);
				printf("\nincoming text <%s>\n",
					inMsg->text);
				}			
				break;
				
			default:
				fcLogx(__FILE__, fn,
					globalMask,
					TCLSIM_MARK,
					"unknown token=%X",
					*token);

				Reply(sender,NULL,0);
				sender = NULL;
				break;
			} //end switch
		} // end if message
	}// end while

name_detach();

}// end tclStim

/*============================================
	initialize - entry point
============================================*/
void initialize(int argc, char **argv)
{
static char *fn="initialize";
int i;                          /* loop variable */
char myName[20];
char toName[20];
char logger_name[20];
int myslot;

globalMask=0xffffffff;
myName[0]=0;
toName[0]=0;
logger_name[0]=0;

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
                        case 'n':   // attach myName
				if(*++p == 0) p++;
				sprintf(myName,"%.19s",p);

				myslot=name_attach(myName, NULL);
				if (myslot == -1)
					{
					printf("%s: Can't attach as %s\n",fn,myName);
					exit(0);
					}
				break;

			case 'l':
				if(*++p == 0) p++;
				sprintf(logger_name,"%.19s",p);
				break;

			default:
				printf("Bad command line switch `%c'\n", *p);
				break;
                        }/*end switch*/
                } /* end if *p */
        }/*end for i*/

// connect to error logger
logger_ID = is_logger_upx(logger_name);

// arm the select routine
my_fds[0] = STDIN_FILENO;   // keyboard
my_fds[1] = whatsMyRecvfd(); // receive fifo

FD_ZERO(&watchset);
FD_SET(my_fds[0], &watchset);
FD_SET(my_fds[1], &watchset);

maxfd=0;
for(i=0; i<2; i++)
	if(maxfd < my_fds[i]) maxfd=my_fds[i];

fcLogx(__FILE__, fn,
	0xff,	// force it to log
	TCLSIM_MARK,
	"my name: <%s> slot=%d",
	myName,
	myslot
	);

fcLogx(__FILE__, fn,
	0xff,	// force it to log
	TCLSIM_MARK,
	"myrecvfd = %d",
	my_fds[1]
	);

} /* end initialize */

/*==================================================
	showUsage - entry point
==================================================*/
void showUsage()
{
printf("r <text> - send this text to tclSender\n");
printf("q(uit)  - exit\n");
} // end showUsage
