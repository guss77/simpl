/*=================================================
	Send/Receive/Reply  Tcl extensions

Description:
This file contains the FC ipc extensions to Tcl/Tk.

-----------------------------------------------------------------------
    Copyright (C) 1998, 2002, 2007 FCSoftware Inc. 

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
=================================================*/
/*
 * $Log: fctclx.c,v $
 * Revision 1.7  2011/03/23 18:07:21  bobfcsoft
 * added hooks for composite name attach name
 *
 * Revision 1.6  2008/07/28 16:21:49  bobfcsoft
 * fixed error stuff in name_attach
 *
 * Revision 1.5  2008/07/28 15:01:02  bobfcsoft
 * catch Send error
 *
 * Revision 1.4  2007/07/24 21:47:20  bobfcsoft
 * new contact info
 *
 * Revision 1.3  2006/08/17 00:11:34  bobfcsoft
 * added string.h
 *
 * Revision 1.2  2005/12/20 15:25:08  bobfcsoft
 * some header warnings cleanup
 *
 * Revision 1.1.1.1  2005/03/27 11:50:45  paul_c
 * Initial import
 *
 * Revision 1.17  2004/07/13 16:42:23  root
 * reply contains full msgBuf
 * ie. 2 integers on front end
 *
 * Revision 1.16  2004/07/11 07:31:18  root
 * fixed typo with previous SetByteArrayObj fix
 *
 * Revision 1.15  2004/07/11 07:27:18  root
 * replaced SetStringObj with SetByteArrayObj
 *
 * Revision 1.14  2002/12/02 16:02:55  root
 * v2.0 fixes
 *
 * Revision 1.13  2002/11/22 16:31:15  root
 * 2.0rc3
 *
 * Revision 1.12  2002/11/19 15:16:02  root
 * 2.0rc1
 *
 * Revision 1.11  2002/08/27 14:28:53  root
 * new SIMPL need a pid on FCID structure
 * name_locate now needs to return with 12 bytes not 8
 *
 * Revision 1.10  2002/06/12 18:27:10  root
 * fcipc merge completed
 *
 * Revision 1.9  2002/01/31 14:33:51  root
 * allow for older versions of Tcl/Tk
 *
 * Revision 1.8  2000/10/13 13:38:40  root
 * using SIMPL "x" functions to nameLocatex, sendMsgx etc
 *
 * Revision 1.6  1999/09/09 14:08:19  root
 * added name_detach stuff
 *
 * Revision 1.5  1999/05/19 16:24:40  root
 * new triggerProxy and
 * NULL user exit function
 *
 * Revision 1.4  1999/04/08 14:34:55  root
 * cleanup
 *
 * Revision 1.3  1999/02/04 15:34:12  root
 * cleanup
 *
 */
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <tcl.h>
#include <standardTypes.h>

#include "simpl.h"

#include "simplProto.h"

int name_attachObjCmd(ClientData clientData,
		Tcl_Interp *interp,
		int objc, 
		Tcl_Obj *CONST objv[]);

int name_detachObjCmd(ClientData clientData,
		Tcl_Interp *interp,
		int objc, 
		Tcl_Obj *CONST objv[]);

int name_locateObjCmd(ClientData clientData,
		Tcl_Interp *interp,
		int objc, 
		Tcl_Obj *CONST objv[]);

int sendObjCmd(ClientData clientData,
		Tcl_Interp *interp,
		int objc, 
		Tcl_Obj *CONST objv[]);

int trigger_proxyObjCmd(ClientData clientData,
		Tcl_Interp *interp,
		int objc, 
		Tcl_Obj *CONST objv[]);

int receiveObjCmd(ClientData clientData,
		Tcl_Interp *interp,
		int objc, 
		Tcl_Obj *CONST objv[]);

int replyObjCmd(ClientData clientData,
		Tcl_Interp *interp,
		int objc, 
		Tcl_Obj *CONST objv[]);

int logitObjCmd(ClientData clientData,
		Tcl_Interp *interp,
		int objc, 
		Tcl_Obj *CONST objv[]);

typedef struct
	{
	int slot;
	int nbytes;
	char data;
	}RECEIVE_REC;

static char msgBuf[8192];
static char *myslot[64];  // Tcl can't handle pointers 

#define LOG_BUF_SIZE 512

/*=====================================================
	Fctclx_Init - entry point
=====================================================*/
int Fctclx_Init(Tcl_Interp *interp)
{
Tcl_CreateObjCommand(interp, "name_attach", name_attachObjCmd,
	(ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
Tcl_CreateObjCommand(interp, "name_detach", name_detachObjCmd,
	(ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
Tcl_CreateObjCommand(interp, "name_locate", name_locateObjCmd,
	(ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
Tcl_CreateObjCommand(interp, "Send", sendObjCmd,
	(ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
Tcl_CreateObjCommand(interp, "triggerProxy", trigger_proxyObjCmd,
	(ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
Tcl_CreateObjCommand(interp, "Receive", receiveObjCmd,
	(ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
Tcl_CreateObjCommand(interp, "Reply", replyObjCmd,
	(ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
Tcl_CreateObjCommand(interp, "logit", logitObjCmd,
	(ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);

Tcl_PkgProvide(interp, "Fctclx", "1.1");
return TCL_OK;
} /* end fcTclX_Init */

/*===================================================
	name_attachObjCmd - entry point
===================================================*/
int name_attachObjCmd(ClientData clientData, 
	Tcl_Interp *interp,
	int objc, Tcl_Obj *CONST objv[])
{
static char *fn="name_attach";
Tcl_Obj *resultPtr;
int rc;
char *name;
int i;
char myname[64];
char *p;

#ifdef TCL80
name = objv[1]->bytes;
#else
name = Tcl_GetString(objv[1]);
#endif

// initialize the slot table
for(i=0; i<64; i++)
	myslot[i]=NULL;

//printf("go1 name=<%s> len=%d\n", name, strlen(name));

rc=name_attach(name, NULL);

if (rc != -1)
	{
	p=strrchr(name,':');

	if (p != NULL)
		sprintf(myname,"%s.%d", &p[1], getpid());
	else
		sprintf(myname,"%s.%d", name, getpid());
	}
else
	sprintf(myname,"NULL");

resultPtr = Tcl_GetObjResult(interp);
Tcl_SetStringObj(resultPtr, myname, strlen(myname));

return TCL_OK;
} /* end name_attachObjCmd */

/*===================================================
	name_detachObjCmd - entry point
===================================================*/
int name_detachObjCmd(ClientData clientData, 
	Tcl_Interp *interp,
	int objc, Tcl_Obj *CONST objv[])
{
static char *fn="name_detach";
Tcl_Obj *resultPtr;
int i;
int rc;

rc=name_detach();

// clear the slot table
for(i=0; i<64; i++)
	myslot[i]=NULL;

resultPtr = Tcl_GetObjResult(interp);
Tcl_SetIntObj(resultPtr, rc);

return TCL_OK;
} /* end name_detachObjCmd */

/*===================================================
	name_locateObjCmd - entry point
===================================================*/
int name_locateObjCmd(ClientData clientData, 
	Tcl_Interp *interp,
	int objc, Tcl_Obj *CONST objv[])
{
static char *fn="name_locate";
Tcl_Obj *resultPtr;
char *name;
int toWhom;

#ifdef TCL80
name = objv[1]->bytes;
#else
name = Tcl_GetString(objv[1]);
#endif

toWhom=name_locate(name);

resultPtr = Tcl_GetObjResult(interp);
Tcl_SetIntObj(resultPtr, toWhom);

return TCL_OK;
} /* end name_locateCmd */

/*===================================================
	sendObjCmd - entry point
===================================================*/
int sendObjCmd(ClientData clientData, 
	Tcl_Interp *interp,
	int objc, Tcl_Obj *CONST objv[])
{
static char *fn="Send";
Tcl_Obj *resultPtr;
int toWhom;
char *smsg;
int snbytes;
RECEIVE_REC *rmsg;
int tbytes;
char *dataPtr;
int nbytes;

// retrieve the arguments
Tcl_GetIntFromObj(interp, objv[1], &toWhom);

#ifdef TCL80
smsg = objv[2]->bytes;
#else
smsg = Tcl_GetByteArrayFromObj(objv[2],&nbytes);
#endif

Tcl_GetIntFromObj(interp, objv[3], &snbytes);

// setup the Reply record
rmsg = (RECEIVE_REC *)msgBuf;
dataPtr=(char *)&rmsg->data;

// compose and send the message
rmsg->nbytes=Send(toWhom, smsg, dataPtr, snbytes, 2048);

if(rmsg->nbytes == -1)
	{
	tbytes = (&rmsg->data - msgBuf)+1;
	}
else
	{
	tbytes = (&rmsg->data - msgBuf)+rmsg->nbytes+1;
	}
msgBuf[tbytes-1]=0;

resultPtr = Tcl_GetObjResult(interp);
Tcl_SetByteArrayObj(resultPtr, msgBuf, tbytes);

return TCL_OK;
} /* end sendCmd */

/*===================================================
	trigger_proxyObjCmd - entry point
===================================================*/
int trigger_proxyObjCmd(ClientData clientData, 
	Tcl_Interp *interp,
	int objc, Tcl_Obj *CONST objv[])
{
static char *fn="triggerProxy";
Tcl_Obj *resultPtr;
int toWhom;
int myProxy;
int rc=1;
int nbytes;

Tcl_GetIntFromObj(interp, objv[1], &toWhom);
Tcl_GetIntFromObj(interp, objv[2], &myProxy);

#if 0
printf("%s: toWhom=%d myProxy=%d\n",fn,toWhom,myProxy);
#endif

Trigger(toWhom, myProxy);

resultPtr = Tcl_GetObjResult(interp);
Tcl_SetIntObj(resultPtr, rc);

return TCL_OK;
} /* end trigger_proxyCmd */

/*===================================================
	receiveObjCmd - entry point
===================================================*/
int receiveObjCmd(ClientData clientData, 
	Tcl_Interp *interp,
	int objc, Tcl_Obj *CONST objv[])
{
static char *fn="Receive";
Tcl_Obj *resultPtr;
char *msgPtr;  // will be assigned by Receive()
int nbytes;
RECEIVE_REC *rmsg;
int tbytes;
int i;
#if 0
int nextReplyRec=-1;
#endif

// setup receive buffer   
rmsg = (RECEIVE_REC *)msgBuf;

nbytes=Receive(&msgPtr, &rmsg->data, 2048);

// find an empty slot
rmsg->slot = -1;
for(i=0; i<64; i++)
	{
	if(myslot[i] == NULL)
		{
		myslot[i] = msgPtr;
		rmsg->slot = i;
		break;
		}
	}

rmsg->nbytes = nbytes;
if(nbytes == -1)
	tbytes = (&rmsg->data - msgBuf)+1;
else
	tbytes = (&rmsg->data - msgBuf)+nbytes+1;
msgBuf[tbytes-1]=0;

#if 0
printf("fromWhom=%X nbytes=%d tbytes=%d\n", rmsg->slot, nbytes, tbytes);
#endif

resultPtr = Tcl_GetObjResult(interp);
Tcl_SetByteArrayObj(resultPtr, msgBuf, tbytes);

return TCL_OK;
} /* end receiveCmd */

/*===================================================
	replyCmd - entry point
===================================================*/
int replyObjCmd(ClientData clientData, 
	Tcl_Interp *interp,
	int objc, Tcl_Obj *CONST objv[])
{
static char *fn="Reply";
Tcl_Obj *resultPtr;
int toWhom;
char *msgPtr;
int nbytes;
int rc;
int i;

Tcl_GetIntFromObj(interp, objv[1], &toWhom);

#ifdef TCL80
msgPtr = objv[2]->bytes;
#else
msgPtr = Tcl_GetByteArrayFromObj(objv[2],&nbytes);
#endif
Tcl_GetIntFromObj(interp, objv[3], &nbytes);

#if 0
printf("nbytes=%d\n",nbytes);
printf("toWhom=%X\n",toWhom);
printf("msgPtr=%X-%X-%X-%X-%X\n",
	msgPtr[0],
	msgPtr[1],
	msgPtr[2],
	msgPtr[3],
	msgPtr[4]);
#endif


if(toWhom != -1)
	{
	rc=Reply(myslot[toWhom], msgPtr, nbytes);
	myslot[toWhom]=NULL;  // free up slot
	}
else
	rc=-1;

resultPtr = Tcl_GetObjResult(interp);
Tcl_SetIntObj(resultPtr, rc);

return TCL_OK;
} /* end replyCmd */


/*===================================================
	logitObjCmd - entry point
===================================================*/
int logitObjCmd(ClientData clientData, 
	Tcl_Interp *interp,
	int objc, Tcl_Obj *CONST objv[])
{
static char *fn="logit";
int logger;
char *fileName;
char *funcName;
char *msg;
int f;			// length of fileName
int w;			// length of who
int t;			// length of text
char *p;		// working pointer
int thisMask;		// log at this mask bit
int logMask;		// main log mask
int loggerID;
int nbytes;

p = msgBuf;
memset(msgBuf,0,512);

Tcl_GetIntFromObj(interp, objv[1], &loggerID);

#ifdef TCL80
fileName=objv[2]->bytes;
funcName=objv[3]->bytes;
#else
fileName=Tcl_GetString(objv[2]);
funcName=Tcl_GetString(objv[3]);
#endif

f=strlen(fileName);
w=strlen(funcName);

Tcl_GetIntFromObj(interp, objv[4], &thisMask);
Tcl_GetIntFromObj(interp, objv[5], &logMask);

#ifdef TCL80
msg=objv[6]->bytes;
#else
msg = Tcl_GetString(objv[6]);
#endif
t=strlen(msg);

if(f+w+t+1 > LOG_BUF_SIZE)
	{
	sprintf(p,"(%s) %s:",fileName, funcName);
	memcpy(&p[f+w+1],msg,LOG_BUF_SIZE-f-w-1);
	}
else
	{
	sprintf(p,"(%s) %s:%s",fileName, funcName, msg);
	}

if(thisMask & logMask)
	{
	if(logger != -1)
		{
		Send(loggerID, p, NULL, strlen(p)+1, 0);
		}
	}

return TCL_OK;
} // end logit
