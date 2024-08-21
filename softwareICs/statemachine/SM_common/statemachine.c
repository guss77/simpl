/*************************************************************

FILE:		statemachine.c

DESCRIPTION:	
This program is an example of a SIMPL enabled statemachine module. 

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
$Log: statemachine.c,v $
Revision 1.2  2011/09/08 16:49:59  bobfcsoft
explicit select header

Revision 1.1  2006/06/26 18:03:16  bobfcsoft
statemachine

=======================================================

*************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/time.h>   // for select stuff

#include "statemachineMsgs.h"

#define _ALLOC
#include "statemachine.h"
#undef _ALLOC

#include "statemachineProto.h"
#include "loggerProto.h"
#include "simplProto.h"

/*=========================================================
	main - entry point
=========================================================*/
int main(int argc, char **argv)
{
static char *fn="statemachine";
int x_it=0;
int retval;

initialize(argc, argv);

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"starting");

while(!x_it)
	{
	inset=watchset;
	retval = select(maxfd+1, &inset, NULL, NULL, NULL);

	if (retval > 0) 
		{
		if (FD_ISSET(my_fds[0], &inset))  // from world
			{
			int nbytes;			
            		char *sender;
			int *token;
			int maskedToken;

			nbytes = Receive(&sender, inArea, MAX_MSG_BUFFER_SIZE);

			token = (int *)inArea;
			maskedToken = *token & 0xfffffff0;

fcLogx(__FILE__, fn,
	globalMask,
	TRACE_FUNC_IO,
	"token=0x%X",*token);

			switch(maskedToken)
				{
				case 0x0:	// common messages
					hndlCommonMsgs(sender, *token);
					break;

				case 0x100:	// events
					hndlEvents(sender, *token);
					break;

				default:
					fcLogx(__FILE__, fn,
						globalMask,
						TRACE_MARK,
						"unknown token %d",
						*token);

					Reply(sender,NULL,0);
					break;
				} // end switch

			} // end if FD

		} // end if retval

	} // end while

name_detach();

exit(1);

} // end statemachine
