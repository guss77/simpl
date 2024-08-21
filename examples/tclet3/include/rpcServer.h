/*============================================
	rpcServer.h

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
============================================*/
/* 
 *$Log: rpcServer.h,v $
 *Revision 1.1  2007/07/26 16:09:43  bobfcsoft
 *new file
 *
 */
#ifndef _RPC_SERVER_DEFS
#define _RPC_SERVER_DEFS

#include "ipcDefs.h"

_ALLOC unsigned int globalMask;
#define RPC_SERVER_MARK		0x00000001
#define RPC_SERVER_FUNC_IO	0x00000002
#define RPC_SERVER_MISC		0x00000010

_ALLOC int toPid;
_ALLOC char toName[20];
_ALLOC char myMsg[80];

_ALLOC char inArea[8192];
_ALLOC char outArea[8192];

#endif
