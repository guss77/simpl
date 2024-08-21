/*************************************************************

FILE:		emitterUtils.c

DESCRIPTION:	
This file contains utility code for polling emitter app.

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
$Log: emitterUtils.c,v $
Revision 1.1  2006/06/19 22:32:44  bobfcsoft
new files

=======================================================

*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>

#include "emitterMsgs.h"
#define _ALLOC extern
#include "emitter.h"
#undef _ALLOC

#include "emitterProto.h"
#include "loggerProto.h"
#include "simplProto.h"

/*=======================================================
	registerShm
=======================================================*/
int registerShm()
{
static char *fn="registerShm";
EMITTER_REGISTER_MSG *outMsg;

fcLogx(__FILE__, fn,
	globalMask,
	EMITTER_FUNC_IO,
	"ding"
         );

outMsg = (EMITTER_REGISTER_MSG *)outArea;
outMsg->token=EMITTER_REGISTER;
outMsg->shmid=myshmid;

Send(queueID, outArea, inArea, sizeof(EMITTER_REGISTER_MSG), MAX_MSG_BUFFER_SIZE);
				

return(0);

} // end registerShm

/*=======================================================
	checkFlags
=======================================================*/
int checkFlags()
{
static char *fn="checkFlags";
EMITTER_CALL_HOME_MSG *outMsg;
EMITTER_DATA_MSG *inMsg;
UINT32 *flags;

fcLogx(__FILE__, fn,
	globalMask,
	EMITTER_FUNC_IO,
	"ding"
         );

flags=(UINT32 *)myshmPtr;

if(*flags > 0 )
	{
	outMsg = (EMITTER_CALL_HOME_MSG *)outArea;
	outMsg->token=EMITTER_CALL_HOME;

	Send(queueID, 
		outArea, 
		inArea, 
		sizeof(EMITTER_CALL_HOME_MSG), 
		MAX_MSG_BUFFER_SIZE);
	
	inMsg = (EMITTER_DATA_MSG *)inArea;

	fcLogx(__FILE__, fn,
		globalMask,
		EMITTER_FUNC_IO,
		"incoming data str =<%s>",
		inMsg->msg
         	);
	}
				

return(0);

} // end registerShm

/*=================================================
	checkFile - entry point
=================================================*/
int checkFile(char *filename)
{
static char *fn="checkFile";
struct stat buf;
static time_t myTime=0;
time_t fileTime;
FILE *fp;
char line[81];
int rc=0;

stat(filename,&buf);
fileTime=buf.st_mtime;

fcLogx(__FILE__, fn,
	globalMask,
	EMITTER_FUNC_IO,
	"myTime=%ld fileTime=%ld",
         myTime,
         fileTime);

if(myTime == 0)
	{
	myTime = fileTime;
	}
else
if(fileTime > myTime)
	{
fcLogx(__FILE__, fn,
	globalMask,
	EMITTER_FUNC_IO,
	"newer"
         );

	myTime = fileTime;

	fp = fopen(filename, "r");
	if(fp != NULL)
		{
		fgets(line,79,fp);

		if(memcmp(line,"SEND",4) == 0)
			{
			parseSEND(fp);
			}
		}// end if fp
	}// end if fileTime

return(rc);

} // end checkFile


/*=======================================================
	SEND parser
=======================================================*/
int parseSEND(FILE *fp)
{
static char *fn="parseSEND";
EMITTER_DATA_MSG *outMsg;
char line[81];

fcLogx(__FILE__, fn,
	globalMask,
	EMITTER_FUNC_IO,
	"ding"
         );

outMsg = (EMITTER_DATA_MSG *)outArea;
outMsg->token=EMITTER_DATA;

fgets(line,79,fp);
line[strlen(line)-1]=0; /* get rid of CR */
memcpy(outMsg->msg,line,79);

Send(queueID, outArea, inArea, sizeof(EMITTER_DATA_MSG), MAX_MSG_BUFFER_SIZE);
				
return(0);

} // end parseSEND

