/*************************************************************

FILE:		emitter.c

DESCRIPTION:	
This program is an example of a SIMPL enabled polling emitter module. 

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
$Log: emitter.c,v $
Revision 1.1  2006/06/19 22:32:44  bobfcsoft
new files

=======================================================

*************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "emitterMsgs.h"
#define _ALLOC
#include "emitter.h"
#undef _ALLOC

#include "emitterProto.h"
#include "loggerProto.h"
#include "simplProto.h"

/*=========================================================
	main - entry point
=========================================================*/
int main(int argc, char **argv)
{
static char *fn="emitter";
int x_it=0;

// parse the command line args
initialize(argc, argv);

fcLogx(__FILE__, fn,
	globalMask,
	EMITTER_FUNC_IO,
	"ding");

while(!x_it)
	{
	sleep(1);

	checkFlags();
	checkFile(fullfilename);

	} // end while

name_detach();

exit(0);
} // end emitter
