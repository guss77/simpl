/*======================================================================

FILE:			csimpl.h

DESCRIPTION:	This header file contains definitions used by simpl2module.c
				and simpl3module.c

AUTHOR:			FC Software Inc.

-----------------------------------------------------------------------
    Copyright (C) 2000 FCSoftware Inc.

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

-------------------------------------------------------------------------

Revision history:
====================================================================
$Log: csimpl.h,v $
Revision 1.4  2013/06/18 14:36:32  bobfcsoft
changes for Python3.x


====================================================================
======================================================================*/

#ifndef _C_SIMPL_H
#define _C_SIMPL_H

// should always be first
#include <Python.h>

// simpl headers
#include <simpl.h>
#include <simplLibProto.h>
#define _ALLOC extern
#include <simplErrors.h>
#include <simplLibVars.h>
#undef _ALLOC

#define SENDER_LIMIT 128

static char *senderArray[SENDER_LIMIT];
static void iniSenderArray(void);
static int setSenderArray(char *);
static char *getSenderArray(int);

#endif
