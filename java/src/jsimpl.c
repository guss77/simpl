	/*======================================================================

FILE:			Jsimpl.c

DESCRIPTION:	This file contains the source code for native methods
				allowing Java programs to run the native C SIMPL library.

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
$Log: jsimpl.c,v $
Revision 1.6  2010/01/27 19:01:43  johnfcsoft
reset() in place

Revision 1.5  2010/01/18 19:28:02  johnfcsoft
editing

Revision 1.4  2009/05/01 13:17:54  johnfcsoft
added character and offset capability

Revision 1.3  2009/03/26 19:02:13  johnfcsoft
32/64 bit memory offset repair

Revision 1.2  2009/03/25 17:53:36  johnfcsoft
cleanup and 64/32 bit corrections

Revision 1.1  2009/03/11 20:39:26  johnfcsoft
initial entry

====================================================================
======================================================================*/

// simpl headers
#include <stdlib.h>
#include <string.h>
#include <jni.h>
#include <jsimpl.h>
#include <jsimplExtra.h>
#include <simpl.h>
#define _ALLOC extern
#include <simplLibVars.h>
#undef _ALLOC

/*########################################################################

packing/unpacking utility functions

#########################################################################*/

/**********************************************************************
FUNCTION:	Java_Jsimpl_start(JNIEnv *, jobject, jint, jint)

PURPOSE:	Set the size of the in and out message buffers.
***********************************************************************/
JNIEXPORT jint JNICALL
Java_Jsimpl_start(JNIEnv *env, jobject obj, jint inSize, jint outSize)
{
register int i;

outCtr = 0;
inCtr = 0;
outBufSize = 0;
inBufSize = 0;
inBuffer = NULL;
outBuffer = NULL;
stringObject = NULL;

// check inputted values
if (inSize < 0)
	{
	return(-1);
	}
if (outSize < 0)
	{
	return(-1);
	}

// output buffer
if (outSize > 0)
	{
	outBuffer = (char *)malloc(outSize);
	if (outBuffer == NULL)
		{
		return(-1);
		}
	outBufSize = outSize;
	}

// input buffer
if (inSize > 0)
	{
	inBuffer = (char *)malloc(inSize);
	if (inBuffer == NULL)
		{
		_end();
		return(-1);
		}
	inBufSize = inSize;

	stringObject = (char *)malloc(inSize);
	if (stringObject == NULL)
		{
		_end();
		return(-1);
		}
	}

// sender table
for (i = 0; i < TABLE_SIZE; i++)
	{
	sends[i].ptr = NULL;
	sends[i].size = 0;
	}

return(0);
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_end(JNIEnv *, jobject)

PURPOSE:	Clean up dynamic memory etc.
***********************************************************************/
JNIEXPORT void JNICALL
Java_Jsimpl_end(JNIEnv *env, jobject obj)
{
_end();
}

/**********************************************************************
FUNCTION:	void _end(void)

PURPOSE:	Clean up dynamic memory etc.
***********************************************************************/

void _end()
{
if (inBuffer != NULL)
	{
	free(inBuffer);
	}

if (outBuffer != NULL)
	{
	free(outBuffer);
	}

if (stringObject != NULL)
	{
	free(stringObject);
	}
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_reset(JNIEnv *, jobject)

PURPOSE:	Reset inCtr and outCtr.
***********************************************************************/

JNIEXPORT void JNICALL
Java_Jsimpl_resetCtrs(JNIEnv *env, jobject obj)
{
inCtr = 0;
outCtr = 0;
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_sizeInBuf(JNIEnv *, jobject)

PURPOSE:	Return the size for the input buffer.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_sizeInBuf(JNIEnv *env, jobject obj)
{
return(inBufSize);
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_sizeOutBuf(JNIEnv *, jobject)

PURPOSE:	Return the available size for the output buffer.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_sizeOutBuf(JNIEnv *env, jobject obj)
{
return(outBufSize);
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_sizeOutFree(JNIEnv *, jobject)

PURPOSE:	Return the available size for the output buffer.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_sizeOutFree(JNIEnv *env, jobject obj)
{
return(outBufSize - outCtr);
}

/*########################################################################

packing functions

#########################################################################*/

/**********************************************************************
FUNCTION:	Java_Jsimpl_packB(JNIEnv *, jobject, jbyte, jint)

PURPOSE:	Write a byte to a character buffer.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_packB(JNIEnv *env, jobject obj, jbyte p, jint action)
{
signed char var = p;

return( packer(&var, sizeof(char), sizeof(char), action) );
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_packC(JNIEnv *, jobject, jchar, jint)

PURPOSE:	Write a char to a character buffer.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_packC(JNIEnv *env, jobject obj, jchar p, jint action)
{
int ret;
NEE var;

var.b = p;

ret = packer(&var.a[0], sizeof(char), sizeof(char), action);
if (ret == -1)
	{
	return(-1);
	}

return( packer(&var.a[1], sizeof(char), sizeof(char), CHARACTER) );
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_packS(JNIEnv *, jobject, jshort, jint)

PURPOSE:	Write a short to a character buffer.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_packS(JNIEnv *env, jobject obj, jshort p, jint action)
{
short int var = p;

return( packer(&var, sizeof(short), sizeof(short), action) );
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_packI(JNIEnv *, jobject, jint, jint)

PURPOSE:	Write an int to a character buffer.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_packI(JNIEnv *env, jobject obj, jint p, jint action)
{
int var = p;

return( packer(&var, sizeof(int), sizeof(int), action) );
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_packL(JNIEnv *, jobject, jlong, jint)

PURPOSE:	Write a long to a character buffer.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_packL(JNIEnv *env, jobject obj, jlong p, jint action)
{
signed long int var = p;

return( packer(&var, sizeof(long), sizeof(long), action) );
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_packF(JNIEnv *, jobject, jfloat, jint)

PURPOSE:	Write a float to a character buffer.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_packF(JNIEnv *env, jobject obj, jfloat p, jint action)
{
float var = p;

return( packer(&var, sizeof(float), sizeof(float), action) );
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_packD(JNIEnv *, jobject, jdouble, jint)

PURPOSE:	Write a double to a character buffer.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_packD(JNIEnv *env, jobject obj, jdouble p, jint action)
{
double var = p;

return( packer(&var, sizeof(double), sizeof(double), action) );
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_packStr(JNIEnv *, jobject, jstring, jint)

PURPOSE:	Write a string to a character buffer.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_packStr(JNIEnv *env, jobject obj, jstring p, jint action)
{
const char *str;
int len;
int ret;

str = (*env)->GetStringUTFChars(env, p, NULL);
if (str == NULL)
	{
	return(-1);
	}

len = strlen(str);
ret = packer((char *)str, len, sizeof(char), action);
(*env)->ReleaseStringUTFChars(env, p, str);

return(ret);
}

/**********************************************************************
FUNCTION:	packer(void *, int, int, int)

CALLED AS:	int ret = packer(&a, size, primSize, action)

PURPOSE:	Writes bytes to the global buffer.

NOTES:	1.action >= 0 ==> action = stated offset
		2. action = -1 ==> concatenate directly
		3. action = -2 ==> calculate structural offset
***********************************************************************/

int packer(void *ptr, int size, int primSize, int action)
{
char *bufPtr;

// buffer overshoot?
if (outBufSize < size)
	{
	return(-1);
	}

if (action == BINARY) // unpack automatically for C structure
	{
	int boundary = getBoundary(primSize);
	bufPtr = outBuffer + outCtr;
	for (; (unsigned long int)bufPtr % boundary; outCtr++, bufPtr++);
	// buffer overshoot?
	if ( outBufSize < (outCtr + size) )
		{
		return(-1);
		}
	}
else if (action == CHARACTER) // unpack it at current offset
	{
	bufPtr = outBuffer + outCtr;
	}
else // unpack at desired offset position
	{
	int offset = action;
	if (offset < 0)
		{
		return(-1);
		}
	// buffer overshoot?
	if (outBufSize < (size + offset) )
		{
		return(-1);
		}
	bufPtr = outBuffer + offset;
	outCtr = offset;
	}

memcpy(bufPtr, ptr, size);
outCtr += size;

return(0);
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_packArray(JNIEnv *, jobject, jobject, jint, jint)

PURPOSE:	Write an array to a character buffer.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_packArray(JNIEnv *env, jobject obj, jobject p, jint type,
jint action)
{
jsize length;
int size;
int primSize;
char *bufPtr;

// length of array
length = (*env)->GetArrayLength(env, p);
if (!length)
	{
	return(-1);
	}

// calculate the primitive and total array size in bytes
switch (type)
	{
	case BYTE:
		primSize = sizeof(char);
		size = length * sizeof(char);
		break;
	case CHAR:
		primSize = sizeof(char) * 2;
		size = length * sizeof(char) * 2;
		break;
	case SHORT:
		primSize = sizeof(short);
		size = length * sizeof(short);
		break;
	case INT:
		primSize = sizeof(int);
		size = length * sizeof(int);
		break;
	case LONG:
		primSize = sizeof(long);
		size = length * sizeof(long);
		break;
	case FLOAT:
		primSize = sizeof(float);
		size = length * sizeof(float);
		break;
	case DOUBLE:
		primSize = sizeof(double);
		size = length * sizeof(double);
	}

// unpack for C structure or at current offset (same for byte only)
if (action == BINARY)
	{
	int boundary = getBoundary(primSize);
	int ctr = 0;
	bufPtr = outBuffer + outCtr;
	for (; (unsigned long int)bufPtr % boundary; ctr++, bufPtr++);
	// buffer overshoot?
	if ( outBufSize < (outCtr + ctr + size) )
		{
		return(-1);
		}
	outCtr += ctr;
	}
else if (action == CHARACTER)
	{
	// buffer overshoot?
	if ( outBufSize < (outCtr + size) )
		{
		return(-1);
		}
	bufPtr = outBuffer + outCtr;
	}
// unpack at desired offset position
else
	{
	int offset = action;
	if (offset < 0)
		{
		return(-1);
		}
	// buffer overshoot?
	if (outBufSize < (size + offset) )
		{
		return(-1);
		}
	bufPtr = outBuffer + offset;
	outCtr = offset;
	}

// ascertain the correct procedure
switch (type)
	{
	case BYTE:
		(*env)->GetByteArrayRegion(env, p, 0, length, (jbyte *)bufPtr);
		break;
	case CHAR:
		(*env)->GetCharArrayRegion(env, p, 0, length, (jchar *)bufPtr);
		break;
	case SHORT:
		(*env)->GetShortArrayRegion(env, p, 0, length, (jshort *)bufPtr);
		break;
	case INT:
		(*env)->GetIntArrayRegion(env, p, 0, length, (jint *)bufPtr);
		break;
	case LONG:
		(*env)->GetLongArrayRegion(env, p, 0, length, (jlong *)bufPtr);
		break;
	case FLOAT:
		(*env)->GetFloatArrayRegion(env, p, 0, length, (jfloat *)bufPtr);
		break;
	case DOUBLE:
		(*env)->GetDoubleArrayRegion(env, p, 0, length, (jdouble *)bufPtr);
		break;
	}

// update the in buffer counter
outCtr += size;

return(0);
}

/*########################################################################

unpacking functions

#########################################################################*/

/**********************************************************************
FUNCTION:	Java_Jsimpl_unpackB(JNIEnv *, jobject, jint)

PURPOSE:	Read a byte from a character buffer.
***********************************************************************/

JNIEXPORT jbyte JNICALL
Java_Jsimpl_unpackB(JNIEnv *env, jobject obj, jint action)
{
signed char var;
int ret;

ret = unpacker(&var, sizeof(char), sizeof(char), action);

return( ret == -1 ? ret : var );
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_unpackC(JNIEnv *, jobject, jint)

PURPOSE:	Read a char from a character buffer.
***********************************************************************/

JNIEXPORT jchar JNICALL
Java_Jsimpl_unpackC(JNIEnv *env, jobject obj, jint action)
{
int ret;
NEE var;

ret = unpacker(&var.a[0], sizeof(char), sizeof(char), action);
if (ret == -1)
	{
	return(0);
	}
ret = unpacker(&var.a[1], sizeof(char), sizeof(char), CHARACTER);
if (ret == -1)
	{
	return(0);
	}

return(var.b);
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_unpackS(JNIEnv *, jobject, jint)

PURPOSE:	Read a short from a character buffer.
***********************************************************************/

JNIEXPORT jshort JNICALL
Java_Jsimpl_unpackS(JNIEnv *env, jobject obj, jint action)
{
short var;
int ret;

ret = unpacker(&var, sizeof(short), sizeof(short), action);

return( ret == -1 ? ret : var );
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_unpackI(JNIEnv *, jobject, jint)

PURPOSE:	Read an int from a character buffer.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_unpackI(JNIEnv *env, jobject obj, jint action)
{
int var;
int ret;

ret = unpacker(&var, sizeof(int), sizeof(int), action);

return( ret == -1 ? ret : var );
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_unpackL(JNIEnv *, jobject, jint)

PURPOSE:	Read a long from a character buffer.
***********************************************************************/

JNIEXPORT jlong JNICALL
Java_Jsimpl_unpackL(JNIEnv *env, jobject obj, jint action)
{
long var;
int ret;

ret = unpacker(&var, sizeof(long), sizeof(long), action);

return( ret == -1 ? ret : var );
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_unpackF(JNIEnv *, jobject, jint)

PURPOSE:	Read a float from a character buffer.
***********************************************************************/

JNIEXPORT jfloat JNICALL
Java_Jsimpl_unpackF(JNIEnv *env, jobject obj, jint action)
{
float var;
int ret;

ret = unpacker(&var, sizeof(float), sizeof(float), action);

return( ret == -1 ? ret : var );
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_unpackD(JNIEnv *, jobject, jint)

PURPOSE:	Read a double from a character buffer.
***********************************************************************/

JNIEXPORT jdouble JNICALL
Java_Jsimpl_unpackD(JNIEnv *env, jobject obj, jint action)
{
double var;
int ret;

ret = unpacker(&var, sizeof(double), sizeof(double), action);

return( ret == -1 ? ret : var );
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_unpackStr(JNIEnv *, jobject, jint, jint)

PURPOSE:	Read a string from a character buffer.
***********************************************************************/

JNIEXPORT jstring JNICALL
Java_Jsimpl_unpackStr(JNIEnv *env, jobject obj, jint len, jint action)
{
int ret;

memset(stringObject, 0, inBufSize);

ret = unpacker(stringObject, len, sizeof(char), action);
if (ret == -1)
	{
	return(NULL);
	}

return( (*env)->NewStringUTF(env, stringObject) );
}

/**********************************************************************
FUNCTION:	unpacker(void *, int, int, int)

CALLED AS:	int ret = unpacker(&a, size, primSize, action)

PURPOSE:	Reads bytes from the global buffer.

NOTES:	1.action >= 0 ==> action = stated offset
		2. action = -1 ==> concatenate directly
		3. action = -2 ==> calculate structural offset
***********************************************************************/

int unpacker(void *ptr, int size, int primSize, int action)
{
char *bufPtr;

// buffer overshoot?
if (inBufSize < size)
	{
	return(-1);
	}

if (action == BINARY) // unpack automatically for C structure
	{
	int boundary = getBoundary(primSize);
	int ctr = 0;
	bufPtr = inBuffer + inCtr;
	for (; (unsigned long int)bufPtr % boundary; ctr++, bufPtr++);
	// buffer overshoot?
	if ( inBufSize < (inCtr + ctr + size) )
		{
		return(-1);
		}
	inCtr += ctr;
	}
else if (action == CHARACTER) // unpack it at current offset
	{
	bufPtr = inBuffer + inCtr;
	}
else // unpack at desired offset position
	{
	int offset = action;
	if (offset < 0)
		{
		return(-1);
		}
	// buffer overshoot?
	if (inBufSize < (size + offset) )
		{
		return(-1);
		}
	bufPtr = inBuffer + offset;
	inCtr = offset;
	}

memcpy(ptr, bufPtr, size);
inCtr += size;

return(0);
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_unpackArray(JNIEnv *, jobject, jobject, jint, jint)

PURPOSE:	Read an array from a character buffer.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_unpackArray(JNIEnv *env, jobject obj, jobject p, jint type,
jint action)
{
jsize length;
int size;
int primSize;
char *bufPtr;

// length of array
length = (*env)->GetArrayLength(env, p);
if (!length)
	{
	return(-1);
	}

// calculate the primitive and total array size in bytes
switch (type)
	{
	case BYTE:
		primSize = sizeof(char);
		size = length * sizeof(char);
		break;
	case CHAR:
		primSize = sizeof(char) * 2;
		size = length * sizeof(char) * 2;
		break;
	case SHORT:
		primSize = sizeof(short);
		size = length * sizeof(short);
		break;
	case INT:
		primSize = sizeof(int);
		size = length * sizeof(int);
		break;
	case LONG:
		primSize = sizeof(long);
		size = length * sizeof(long);
		break;
	case FLOAT:
		primSize = sizeof(float);
		size = length * sizeof(float);
		break;
	case DOUBLE:
		primSize = sizeof(double);
		size = length * sizeof(double);
	}

// unpack for C structure or at current offset (same for byte only)
if (action == BINARY)
	{
	int boundary = getBoundary(primSize);
	int ctr = 0;
	bufPtr = inBuffer + inCtr;
	for (; (unsigned long int)bufPtr % boundary; ctr++, bufPtr++);
	// buffer overshoot?
	if ( inBufSize < (inCtr + ctr + size) )
		{
		return(-1);
		}
	inCtr += ctr;
	}
else if (action == CHARACTER)
	{
	// buffer overshoot?
	if ( inBufSize < (inCtr + size) )
		{
		return(-1);
		}
	bufPtr = inBuffer + inCtr;
	}
// unpack at desired offset position
else
	{
	int offset = action;
	if (offset < 0)
		{
		return(-1);
		}
	// buffer overshoot?
	if (inBufSize < (size + offset) )
		{
		return(-1);
		}
	bufPtr = inBuffer + offset;
	inCtr = offset;
	}

// ascertain the correct procedure
switch (type)
	{
	case BYTE:
		(*env)->SetByteArrayRegion(env, p, 0, length, (jbyte *)bufPtr);
		break;
	case CHAR:
		(*env)->SetCharArrayRegion(env, p, 0, length, (jchar *)bufPtr);
		break;
	case SHORT:
		(*env)->SetShortArrayRegion(env, p, 0, length, (jshort *)bufPtr);
		break;
	case INT:
		(*env)->SetIntArrayRegion(env, p, 0, length, (jint *)bufPtr);
		break;
	case LONG:
		(*env)->SetLongArrayRegion(env, p, 0, length, (jlong *)bufPtr);
		break;
	case FLOAT:
		(*env)->SetFloatArrayRegion(env, p, 0, length, (jfloat *)bufPtr);
		break;
	case DOUBLE:
		(*env)->SetDoubleArrayRegion(env, p, 0, length, (jdouble *)bufPtr);
		break;
	}

// update the in buffer counter
inCtr += size;

return(0);
}

/**********************************************************************
FUNCTION:	getBoundary(int)

CALLED AS:	int boundary = getBoundary(size)

PURPOSE:	Returns the structure placing for 32/64 bit architectures.
***********************************************************************/

int getBoundary(int size)
{
char *ptr;

return( (size > sizeof(ptr)) ? sizeof(ptr) : size);
}

/*########################################################################

test structure function

#########################################################################*/

/**********************************************************************
FUNCTION:	printTester(jint type)

CALLED AS:	printTester(type)

PURPOSE:	Writes the values of the TESTER struct to screen.
***********************************************************************/

JNIEXPORT void JNICALL
Java_Jsimpl_printTester(JNIEnv *env, jobject obj, jint type)
{
memcpy(inBuffer, outBuffer, inBufSize);

if (!type)
	{
	return;
	}

typedef struct
	{
	short a;
	char b;
	char c;
	double d;
	char e;
	long f;
	char g;
	char h[2];
	char z[31];
	short i;
	int j;
	long k;
	float l;
	char m[2];
	long n;
	char o[2];
	char p[10];
	NEE q[3];
	short r[7];
	int s[5];
	long t[5];
	float u[3];
	double v[5];
	} TESTER;

TESTER *out = (TESTER *)outBuffer;

printf("******************************************\n");
printf("C message structure starts here\n");
printf("******************************************\n");

printf("a=%p %d\n", &(out->a), out->a);
printf("b=%p %c\n", &(out->b), out->b);
printf("c=%p %c\n", &(out->c), out->c);
printf("d=%p %f\n", &(out->d), out->d);
printf("e=%p %c\n", &(out->e), out->e);
printf("f=%p %ld\n", &(out->f), out->f);
printf("g=%p %c\n", &(out->g), out->g);
printf("h=%p %c %c\n", &(out->h), out->h[0], out->h[1]);
printf("z=%p %.31s\n", &(out->z), out->z);
printf("i=%p %d\n", &(out->i), out->i);
printf("j=%p %d\n", &(out->j), out->j);
printf("k=%p %ld\n", &(out->k), out->k);
printf("l=%p %f\n", &(out->l), out->l);
printf("m=%p %c %c\n", &(out->m), out->m[0], out->m[1]);
printf("n=%p %ld\n", &(out->n), out->n);
printf("o=%p %.2s\n", &(out->o), out->o);
printf("p=%p %c %c %c %c %c %c %c %c %c %c\n", &(out->p), out->p[0],
	out->p[1], out->p[2], out->p[3], out->p[4], out->p[5], out->p[6], out->p[7],
	out->p[8], out->p[9]);
printf("q=%p %c%c %c%c %c%c\n", &(out->q), out->q[0].a[0], out->q[0].a[1],
	out->q[1].a[0], out->q[1].a[1], out->q[2].a[0], out->q[2].a[1]);
printf("r=%p %d,%d,%d,%d,%d,%d,%d\n", &(out->r), out->r[0], out->r[1],
	out->r[2], out->r[3], out->r[4], out->r[5], out->r[6]);
printf("s=%p %d,%d,%d,%d,%d\n", &(out->s), out->s[0], out->s[1],
	out->s[2], out->s[3], out->s[4]);
printf("t=%p %ld,%ld,%ld,%ld,%ld\n", &(out->t), out->t[0], out->t[1],
	out->t[2], out->t[3], out->t[4]);
printf("u=%p %f,%f,%f\n", &(out->u), out->u[0], out->u[1], out->u[2]);
printf("v=%p %f,%f,%f,%f,%f\n", &(out->v), out->v[0], out->v[1], out->v[2],
	out->v[3], out->v[4]);

printf("******************************************\n");
printf("C message structure ends here\n");
printf("******************************************\n");
}

/*########################################################################

SIMPL functions used in IPC

#########################################################################*/

/**********************************************************************
FUNCTION:	Java_Jsimpl_nameAttach(JNIEnv *, jobject, jstring)

CALLED AS:	int ret = Jsimpl.nameAttach(String simpl_name)

PURPOSE:	Perform a SIMPL name attach.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_nameAttach(JNIEnv *env, jobject obj, jstring p)
{
const char *str;
int ret = -1;

str = (*env)->GetStringUTFChars(env, p, NULL);
if (str == NULL)
	{
	return(ret);
	}

ret = name_attach(str, NULL);

(*env)->ReleaseStringUTFChars(env, p, str);

return(ret);
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_nameDetach(JNIEnv *, jobject)

CALLED AS:	int ret = Jsimpl.nameDetach()

PURPOSE:	Release all SIMPL functionality.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_nameDetach(JNIEnv *env, jobject obj)
{
return( name_detach() );
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_surDetach(JNIEnv *, jobject, jint)

CALLED AS:	int proxy = Jsimpl.surDetach(int surrogate_simpl_id)

PURPOSE:	Detach a surrogate.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_surDetach(JNIEnv *env, jobject obj, jint p)
{
int surrogateID = (int)p;

return( sur_detach(surrogateID) );
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_nameLocate(JNIEnv *, jobject, jstring)

CALLED AS:	int ret = Jsimpl.nameLocate(String simpl_name)

PURPOSE:	Perform a SIMPL name locate.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_nameLocate(JNIEnv *env, jobject obj, jstring p)
{
const char *str;
int ret = -1;

str = (*env)->GetStringUTFChars(env, p, NULL);
if (str == NULL)
	{
	return(ret);
	}

ret = name_locate(str);

(*env)->ReleaseStringUTFChars(env, p, str);

return(ret);
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_Send(JNIEnv *, jobject, jint)

CALLED AS:	int ret = Jsimpl.Send(int id)

PURPOSE:	Send a SIMPL message and retrieve reply.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_Send(JNIEnv *env, jobject obj, jint p)
{
int id = (int)p;
int iSize;
void *iPtr = (void *)inBuffer;
void *oPtr = (void *)outBuffer;

if (oPtr == NULL)
	{
	return(-1);
	}

if (outCtr > 0)
	{
	inCtr = 0;
	iSize = Send(id, oPtr, iPtr, outCtr, inBufSize);
	outCtr = 0;
	}
else
	{
	iSize = -1;
	}

return(iSize);
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_Receive(JNIEnv *, jobject)

CALLED AS:	int ret = Jsimpl.Receive()

PURPOSE:	Receive a SIMPL message.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_Receive(JNIEnv *env, jobject obj)
{
char *sender;
void *iPtr = (void *)inBuffer;
int iSize;
int ret;

if (iPtr == NULL)
	{
	return(-1);
	}

if (inBufSize == 0)
	{
	return(-1);
	}

inCtr = 0;

iSize = Receive(&sender, iPtr, inBufSize);

if (iSize > 0)
	{
	ret = setTable(sender, iSize);
	}
else
	{
	ret = iSize;
	}

return(ret);
}

/**********************************************************************
FUNCTION:	int setTable(char *, int)

CALLED AS:	int ret = setTable(char *sender, int)

PURPOSE:	Return an offset to a sender table.
***********************************************************************/

int setTable(char *sender, int iSize)
{
int i;
int ret = -1;

for (i = 0; i < TABLE_SIZE; i++)
	{
	if (sends[i].size == 0)
		{
		sends[i].size = iSize;
		sends[i].ptr = sender;
		ret = i;
		break;
		}
	}

return(ret);
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_getMsgSize(JNIEnv *, jobject, jint)

CALLED AS:	int size = Jsimpl.getMsgSize(int sender)

PURPOSE:	Return a received message size.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_getMsgSize(JNIEnv *env, jobject obj, jint sender)
{
int offset = sender;

return(sends[offset].size);
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_Reply(JNIEnv *, jobject, jint)

CALLED AS:	int ret = Jsimpl.Receive()

PURPOSE:	Receive a SIMPL message.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_Reply(JNIEnv *env, jobject obj, jint sender)
{
int offset = sender;
char *ptr;
int ret;

ptr = getPtr(offset);
ret = Reply(ptr, outBuffer, outCtr);
outCtr = 0;

return(ret);
}

/**********************************************************************
FUNCTION:	char *getPtr(int)

CALLED AS:	char *ptr = getPtr(int offset)

PURPOSE:	Return a sender pointer.
***********************************************************************/

char *getPtr(int offset)
{
char *ptr;

ptr = sends[offset].ptr;
sends[offset].ptr = NULL;
sends[offset].size = 0;

return(ptr);
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_Trigger(JNIEnv *, jobject, jint, jint)

CALLED AS:	int proxy = Jsimpl.Trigger(int id, int proxy)

PURPOSE:	Send a proxy to a SIMPL receiver.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_Trigger(JNIEnv *env, jobject obj, jint i, jint p)
{
int a = (int)i;
int b = (int)p;

return( Trigger(a, b) );
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_whatsMyRecvfd(JNIEnv *, jobject)

CALLED AS:	int fd = Jsimpl.whatsMyRecvfd()

PURPOSE:	Return the receive fd for a SIMPL receiver.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_whatsMyRecvfd(JNIEnv *env, jobject obj)
{
return( whatsMyRecvfd() );
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_returnProxy(JNIEnv *, jobject, jint)

CALLED AS:	int proxy = Jsimpl.returnProxy(int un_altered_proxy)

PURPOSE:	Return the true value of a proxy.
***********************************************************************/

JNIEXPORT jint JNICALL
Java_Jsimpl_returnProxy(JNIEnv *env, jobject obj, jint p)
{
int a = (int)p;

return( returnProxy(a) );
}

/**********************************************************************
FUNCTION:	Java_Jsimpl_whatsMyError(JNIEnv *, jobject)

CALLED AS:	string errStr = Jsimpl.whatsMyError()

PURPOSE:	Return the simpl error string based on the last value of
			_simpl_errno.
***********************************************************************/

JNIEXPORT jstring JNICALL
Java_Jsimpl_whatsMyError(JNIEnv *env, jobject obj)
{
return( (*env)->NewStringUTF(env, whatsMyError()) );
}
