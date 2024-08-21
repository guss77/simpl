/*======================================
	rpcFuncs.c

Description:
This file contains the Remote Procedure Call functions
for the tclet3 example.

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
 *$Log: rpcFuncs.c,v $
 *Revision 1.1  2007/07/26 16:09:43  bobfcsoft
 *new file
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

#include "tclet3Msgs.h"

#define _ALLOC extern
#include "rpcServer.h"
#include "loggerVars.h"
#undef _ALLOC

#include "rpcServerProto.h"
#include "ipcProto.h"
#include "loggerProto.h"

/*============================================
	rpc1 - entry point
============================================*/
char *rpc1(char *oldColor)
{
static char *fn="rpc1";
static char newColor[20];

fcLogx(__FILE__, fn,
	globalMask,
	RPC_SERVER_FUNC_IO,
	"old color=<%s>",
	oldColor
	);

if(memcmp(oldColor,"blue",4) == 0)
	sprintf(newColor,"green");
else
	sprintf(newColor,"blue");

fcLogx(__FILE__, fn,
	globalMask,
	RPC_SERVER_FUNC_IO,
	"new color=<%s>",
	newColor
	);

sleep(10);

return(newColor);
} // end rpc1
