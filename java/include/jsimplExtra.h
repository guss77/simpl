/*======================================================================

FILE:			jsimplExtra.h

DESCRIPTION:	This file contains more definitions used by jsimpl.c.

AUTHOR:			FC Software Inc.

-----------------------------------------------------------------------
    Copyright (C) 2009 FCSoftware Inc. 

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

Revision history:
====================================================================
$Log: jsimplExtra.h,v $
Revision 1.4  2009/05/01 13:15:38  johnfcsoft
added character and offset capability

Revision 1.3  2009/03/26 19:02:50  johnfcsoft
cleanup

Revision 1.2  2009/03/25 17:51:43  johnfcsoft
added size definitions

Revision 1.1  2009/03/11 20:35:58  johnfcsoft
initial entry

====================================================================
======================================================================*/

#include <jni.h>

typedef struct
	{
	char *ptr;
	int size;
	} SENDER_TABLE;

typedef union
	{
	char a[2];
	jchar b;
	} NEE;

typedef enum
	{
	BYTE,
	CHAR,
	SHORT,
	INT,
	LONG,
	FLOAT,
	DOUBLE
	} ARRAY;

#define TABLE_SIZE	128
#define BINARY		-2
#define CHARACTER	-1

int setTable(char *, int);
char *getPtr(int);
void _end(void);
int packer(void *, int, int, int);
int unpacker(void *, int, int, int);
int getBoundary(int);

char *inBuffer = NULL;
char *outBuffer = NULL;
int inBufSize = 0;
int outBufSize = 0;
int inCtr = 0;
int outCtr = 0;
char *stringObject = NULL;
SENDER_TABLE sends[TABLE_SIZE];
