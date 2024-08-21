/*======================================================================

FILE:			csimplmodule.c

DESCRIPTION:	This file contains the function calls (C wrappers)
				for the python simpl library used by python programs.

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

    If you discover a bug or add an enhancement here's how to reach us: 

	fcsoft@attcanada.ca
-----------------------------------------------------------------------

Revision history:
====================================================================
$Log: csimplmodule.c,v $
Revision 1.3  2011/12/31 20:36:57  johnfcsoft
METH_VARAGS -> METH_NOARGS

Revision 1.2  2010/02/11 15:00:38  johnfcsoft
added sender table

Revision 1.1  2010/02/04 16:48:30  johnfcsoft
initial entry

====================================================================
======================================================================*/

// simpl headers
#include <csimpl.h>

/**********************************************************************
FUNCTION:	simpl_nameAttach(PyObject *, PyObject *)

CALLED AS:	returnValue = simpl.nameAttach(programName)

PURPOSE:	Add simpl capability to a python program.

RETURNS:	success: 0 
			failure: -1
***********************************************************************/

static PyObject *simpl_nameAttach(PyObject *self, PyObject *args)
{
int ret = -1;
char *name;

initializeSenderArray();

// parse out the passed in arguments
if (PyArg_ParseTuple(args, "s", &name))
	{
	// call the actual simpl C library function
	ret = name_attach(name, NULL);
	}
else
	{
	_simpl_setErrorCode(COMMAND_LINE_ERROR);
	}

// convert C return value to python object for return
return( Py_BuildValue("i", ret) );
}

/**********************************************************************
FUNCTION:	simpl_nameDetach(PyObject *, PyObject *)

CALLED AS:	returnValue = simpl.nameDetach()

PURPOSE:	Remove simpl capability from a python program.

RETURNS:	success: 0 
			failure: -1
***********************************************************************/

static PyObject *simpl_nameDetach(PyObject *self, PyObject *args)
{
int ret;

// call the simpl C library function
ret = name_detach();

// convert C return value to python object for return
return( Py_BuildValue("i", ret) );
}

/**********************************************************************
FUNCTION:	simpl_surDetach(PyObject *, PyObject *)

CALLED AS:	returnValue = simpl.surDetach(surrogateId)

PURPOSE:	Remove a surrogate receiver and its remote partner.

RETURNS:	success: >= 0 
			failure: -1
***********************************************************************/

static PyObject *simpl_surDetach(PyObject *self, PyObject *args)
{
int ret = -1;
int fd;

// parse out the passed in arguments
if (PyArg_ParseTuple(args, "i", &fd))
	{
	// call the actual simpl C library function
	ret = sur_detach(fd);
	}
else
	{
	_simpl_setErrorCode(COMMAND_LINE_ERROR);
	}

// convert C return value to python object for return
return( Py_BuildValue("i", ret) );
}

/**********************************************************************
FUNCTION:	simpl_nameLocate(PyObject *, PyObject *)

CALLED AS:	receiverId = simpl.nameLocate(receiverName)

PURPOSE:	Get the id of a simpl receiver.

RETURNS:	success: >= 0 
			failure: -1
***********************************************************************/

static PyObject *simpl_nameLocate(PyObject *self, PyObject *args)
{
int ret = -1;
char *name;

// parse out the passed in arguments
if (PyArg_ParseTuple(args, "s", &name))
	{
	// call the actual simpl C library function
	ret = name_locate(name);
	}
else
	{
	_simpl_setErrorCode(COMMAND_LINE_ERROR);
	}

// convert C return value to python object for return
return( Py_BuildValue("i", ret) );
}
 
/**********************************************************************
FUNCTION:	simpl_receive(PyObject *, PyObject *)

CALLED AS:	msgSize, senderId, msg = simpl.receive()

PURPOSE:	Receive an incoming simpl message.

RETURNS:	success: message size >= 0 bytes 
			failure: message size = -1
			proxy: message size < -1
***********************************************************************/

static PyObject *simpl_receive(PyObject *self, PyObject *args)
{
int ret;
char *sender;
FCMSG_REC *msgPtr;
int senderOffset;

// call the actual simpl C library function
ret = Receive(&sender, NULL, 0);

// load the sender address into the sender table
senderOffset = setSenderArray(sender);

// what sort of message are we dealing with?
if (ret > 0) // message
	{
	msgPtr = (FCMSG_REC *)sender;
	return( Py_BuildValue("iiz#", ret, senderOffset, &msgPtr->data, ret) );
	}
else // null message/error/proxy
	{
	return( Py_BuildValue("iii", ret, senderOffset, NULL) );
	}
}

/**********************************************************************
FUNCTION:	simpl_send(PyObject *, PyObject *)

CALLED AS:	replyMsgSize = simpl.send(receiverId, outBuffer, inBuffer)

PURPOSE:	Sends a simpl message to a simpl receiver.

RETURNS:	success: reply message size in bytes >= 0 
			failure: -1
***********************************************************************/

static PyObject *simpl_send(PyObject *self, PyObject *args)
{
int ret = -1;
int fd;
char *outMem;
int outSize;
char *inMem;
int inSize;

// parse out the passed in arguments
if (PyArg_ParseTuple(args, "iz#z#", &fd, &outMem, &outSize, &inMem, &inSize))
	{
	// call the actual simpl C library function
	//ret = Send(fd, outMem, inMem, outSize, inSize);
	ret = Send(fd, outMem, inMem, outSize, inSize);
	}
else
	{
	_simpl_setErrorCode(COMMAND_LINE_ERROR);
	}

// convert C return value to python object for return
return( Py_BuildValue("i", ret) );
}

/**********************************************************************
FUNCTION:	simpl_trigger(PyObject *, PyObject *)

CALLED AS:	simpl.trigger(i, i)

PURPOSE:	Send simpl proxy to a simpl receiver.

RETURNS:	success: 0 
			failure: -1
***********************************************************************/

static PyObject *simpl_trigger(PyObject *self, PyObject *args)
{
int ret = -1;
int fd;
int proxy;

// parse out the passed in arguments
if (PyArg_ParseTuple(args, "ii", &fd, &proxy))
	{
	// call the actual simpl C library function
	ret = Trigger(fd, proxy);
	}
else
	{
	_simpl_setErrorCode(COMMAND_LINE_ERROR);
	}

// convert C return value to python object for return
return( Py_BuildValue("i", ret) );
}

/**********************************************************************
FUNCTION:	simpl_reply(PyObject *, PyObject *)

CALLED AS:	replyMsgSize = simpl.reply(senderId, outBuffer)

PURPOSE:	Reply to sender.

RETURNS:	success: reply message size in bytes >= 0
			failure: -1
***********************************************************************/

static PyObject *simpl_reply(PyObject *self, PyObject *args)
{
int ret = -1;
char *sender;
char *mem;
int size;
int senderOffset;

// parse out the passed in arguments
if (PyArg_ParseTuple(args, "iz#", &senderOffset, &mem, &size))
	{
	// get the actual sender address
	sender = getSenderArray(senderOffset);
	// call the actual simpl C library function
	ret = Reply(sender, mem, size);
	}
else
	{
	_simpl_setErrorCode(COMMAND_LINE_ERROR);
	}

// convert C return value to python object for return
return( Py_BuildValue("i", ret) );
}

/**********************************************************************
FUNCTION:	simpl_whatsMyReceiveFd(PyObject *, PyObject *)

CALLED AS:	fd = simpl.whatsMyReceiveFd()

PURPOSE:	Return the receive fifo file descriptor.

RETURNS:	success: file descriptor >= 0
			failure: -1
***********************************************************************/

static PyObject *simpl_whatsMyReceiveFd(PyObject *self, PyObject *args)
{
int fd;

// call the actual simpl C library function
fd = whatsMyRecvfd();

// convert C return value to python object for return
return( Py_BuildValue("i", fd) );
}

/**********************************************************************
FUNCTION:	simpl_whatsMyError(PyObject *, PyObject *)

CALLED AS:	errStr = simpl.whatsMyError()

PURPOSE:	Return the simpl error string based on the last value of
			_simpl_errno.
***********************************************************************/

static PyObject *simpl_whatsMyError(PyObject *self, PyObject *args)
{
char *error;

// call the actual simpl C library function
error = whatsMyError();

// convert C return value to python object for return
return( Py_BuildValue("s", error) );
}

/**********************************************************************
FUNCTION:	simpl_returnProxy(PyObject *, PyObject *)

CALLED AS:	true proxy value = simpl.returnProxy(received proxy value)

PURPOSE:	Return the true value of a triggered proxy.
***********************************************************************/

static PyObject *simpl_returnProxy(PyObject *self, PyObject *args)
{
int incomingProxy;
int proxy = -1;

// parse out the passed in arguments
if (PyArg_ParseTuple(args, "i", &incomingProxy))
	{
	// call the actual simpl C library function
	proxy = returnProxy(incomingProxy);
	}
else
	{
	_simpl_setErrorCode(COMMAND_LINE_ERROR);
	}

// convert C return value to python object for return
return( Py_BuildValue("i", proxy) );
}

/******************** function name binding table *********************/

static PyMethodDef simplmethods[] =
	{
	{"nameAttach", simpl_nameAttach, METH_VARARGS},
	{"nameDetach", simpl_nameDetach, METH_NOARGS},
	{"surDetach", simpl_surDetach, METH_VARARGS},
	{"nameLocate", simpl_nameLocate, METH_VARARGS},
	{"receive", simpl_receive, METH_NOARGS},
	{"send", simpl_send, METH_VARARGS},
	{"trigger", simpl_trigger, METH_VARARGS},
	{"reply", simpl_reply, METH_VARARGS},
	{"whatsMyReceiveFd", simpl_whatsMyReceiveFd, METH_NOARGS},
	{"whatsMyError", simpl_whatsMyError, METH_NOARGS},
	{"returnProxy", simpl_returnProxy, METH_VARARGS},
	{NULL, NULL}
	};

/********************** module initialization *************************/

DL_EXPORT(void) initcsimpl()
{
Py_InitModule("csimpl", simplmethods);
}

/********************** sender table functions ***********************/

void initializeSenderArray()
{
register int i;

for (i = 0; i < SENDER_LIMIT; i++)
	{
	senderArray[i] = NULL;
	}
}

int setSenderArray(char *sender)
{
register int i;

for (i = 0; i < SENDER_LIMIT; i++)
	{
	if (senderArray[i] == NULL)
		{
		senderArray[i] = sender;
		break;
		}
	}

return (i == SENDER_LIMIT) ? -1 : i;
}

char *getSenderArray(int senderOffset)
{
char *sender;

sender = senderArray[senderOffset];
senderArray[senderOffset] = NULL;

return sender;
}
