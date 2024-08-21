
/*************************************************************

FILE:	rt_process.h	

DESCRIPTION:	
This file contains globals for rt_process module.

AUTHOR:			R.D. Findlay

-------------------------
FCsoftware Inc. 1999, 2007
This code is released as open source.   We hope you find 
it useful.  If you discover a bug or add an enhancement 
contact us on the SIMPL project mailing list. 

-------------------------

Revision history:
=======================================================
$Log: rt_process.h,v $
Revision 1.1  2007/07/26 15:51:49  bobfcsoft
new file

Revision 1.1  1999/09/16 18:17:11  root
Initial revision

=======================================================
*************************************************************/

#ifndef _RTPROCESS_DEF
#define _RTPROCESS_DEF

#include "rtDefs.h"

_ALLOC unsigned counter;

_ALLOC RT_TASK myTask;
_ALLOC int myFrequency;
_ALLOC int cutPoint;

_ALLOC char   inArea[1024];
_ALLOC char   outArea[1024];
#endif
