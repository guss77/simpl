/*************************************************************

FILE:		recvTester.c

DESCRIPTION:	
This program is an example of a utility process 
used for automating stimulator requests.

AUTHOR:			R.D. Findlay

-----------------------------------------------------------------------
    Copyright (C) 2000, 2002 FCSoftware Inc. 

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
$Log: recvTester.c,v $
Revision 1.2  2011/09/08 16:55:49  bobfcsoft
explicit select header

Revision 1.1  2008/04/28 18:00:22  bobfcsoft
new in CVS

Revision 1.3  2003/04/03 16:49:32  root
fixed RedHat 7.x warnings

Revision 1.2  2002/12/03 21:25:34  root
v2.0 compatible

Revision 1.1  2002/12/03 20:23:18  root
Initial revision

=======================================================

*************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/select.h>

#include "stimulatorMsgs.h"

#define _ALLOC
#include "recvTester.h"
#undef _ALLOC

#include "recvTesterProto.h"
#include "simplProto.h"
#include "loggerProto.h"

/*--------------------------------------
	recvTester - entry point
--------------------------------------*/
int main(int argc, char **argv, char **envp)
{
static char *fn="recvTester";
int x_it=0;
char line[80];

initialize(argc, argv);

fcLogx(__FILE__, fn,
	globalMask,
	TESTER_MARK,
	"starting"
	);

runtest(fullinfile);

printf("-> ");
fflush(stdout);
while(!x_it)
	{
	inset = watchset;
	select(maxfd+1, &inset, NULL, NULL, NULL);

// Is this from keyboard
	if(FD_ISSET(my_fds[0], &inset))  //  keyboard is ready
		{
		fgets(line, 79, stdin);

		switch(line[0])
			{
			case '?':
				printf("recvTester commands:\n");
				printf("q - quit\n");
				break;

			case 'q':
				x_it=1;
				break;

			default:
				printf("%s: unknown keypress <%c>\n",
					fn,
					line[0]);
				break;
			} // end switch

		printf("-> ");
		fflush(stdout);
		} // end if keyboard

	} // end while

fcLogx(__FILE__, fn,
	globalMask,
	TESTER_MISC,
	"done");

name_detach();

exit(0);

}// end recvTester
