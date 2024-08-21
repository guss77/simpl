#include <SPI.h>
#include <Ethernet.h>

#define PRIMARY
#include "Simpl.h"
#undef PRIMARY

/*******************************************************************************
FUNCTION:	int nameAttach(const char *, unsigned, EthernetClient *, char *)

PURPOSE:	SIMPL name attaches on remote host.

RETURNS:	success:  0
			failure: -1
*******************************************************************************/

int nameAttach(char *serverName, unsigned port, EthernetClient *client, char
*myName)
{
const char *func = "nameAttach";
int ret;
int i;
SG_NAME_ATTACH_MSG msg;

// check for a  name
if (!strlen(myName))
	{
	sprintf(simpl_errstr, "%s: a name is required", func);
	return(-1);
	}

// check that name length is within bounds
if (strlen(myName) > MAX_NAME_LEN)
	{
	sprintf(simpl_errstr, "%s: name must be <= %d", func, MAX_NAME_LEN);
	return(-1);
	}

// connect to server
for (i = 1; i <= CONNECT_TRY; i++)
  {
  ret = client->connect(serverName, port);
  if (ret == 1)
    {
    break;
    }
  }

// check connect return value
switch (ret)
    {
    case 1:
        // good socket connection
        break;
    case 0:
        sprintf(simpl_errstr, "%s: socket connect: failed", func);
        return(-1);
    case -1:
        sprintf(simpl_errstr, "%s: socket connect: no DNS server given", func);
        return(-1);
    case -2:
        sprintf(simpl_errstr, "%s: socket connect: no DNS records found", func);
        return(-1);
    case -3:
        sprintf(simpl_errstr, "%s: socket connect: timeout", func);
        return(-1);
    default:
        sprintf(simpl_errstr, "%s: socket connect: unknown error", func);
        return(-1);
    }

// create the name attach message to be sent to the tclSurrogate
msg.token = SG_NAME_ATTACH;
msg.nbytes = sizeof(SG_NAME_ATTACH_MSG) - sizeof(msg.whom);
msg.whom = -1;
strcpy(msg.myName, myName);
msg.myPid = -1;
msg.mySlot = -1;

// check to see that the client is connected
if (!client->connected())
	{
	sprintf(simpl_errstr, "%s: client not connected", func);
	return(-1);
	}

// write out the name attach message on the socket to the tclSurrogate
ret = client->write((uint8_t *)&msg, sizeof(SG_NAME_ATTACH_MSG));
if (ret != sizeof(SG_NAME_ATTACH_MSG))
	{
	sprintf(simpl_errstr, "%s: incorrect write on message", func);
	return(-1);
	}

// read reply from the tclSurrogate
ret = commDelay(client);
if (ret == -1)
	{
	sprintf(simpl_errstr, "%s: name %s already in use?", func, myName);
	return(-1);
	}

ret = client->read((uint8_t *)&msg, (sizeof(unsigned short) << 1));
if (ret != (sizeof(unsigned short) << 1))
	{
	sprintf(simpl_errstr, "%s: incorrect read on header", func);
	return(-1);
	}

// check the reply token
if (msg.token != SG_REPLY_IT)
	{
	sprintf(simpl_errstr, "%s: incorrect message token", func);
	return(-1);
	}

// check the incoming message for the number of bytes
ret = client->read((uint8_t *)&(msg.whom), msg.nbytes);
if (ret != msg.nbytes)
	{
	sprintf(simpl_errstr, "%s: incorrect read on message", func);
	return(-1);
	}

return(0);
}

/*******************************************************************************
FUNCTION:	int nameDetach(EthernetClient *)

PURPOSE:	SIMPL name detaches on remote host. (ie. removes SIMPL name)

RETURNS:	success:  0
			failure: -1
*******************************************************************************/

int nameDetach(EthernetClient *client)
{
const char *func = "nameDetach";
int ret;
SG_NAME_DETACH_MSG msg;

// compose name detach message to send to tclSurrogate
msg.token = SG_NAME_DETACH;
msg.nbytes = 0;

if (client->connected())
	{
	// write out the name detach message on the socket to the tclSurrogate
	ret = client->write((uint8_t *)&msg, sizeof(SG_NAME_DETACH_MSG));
	if (ret != sizeof(SG_NAME_DETACH_MSG))
		{
		sprintf(simpl_errstr, "%s: incorrect write on message", func);
		return(-1);
		}

	return(0);
	}

sprintf(simpl_errstr, "%s: client not connected", func);
return(-1);
}

/*******************************************************************************
FUNCTION:	long nameLocate(EthernetClient *, char *)

PURPOSE:	SIMPL name locates a receiver on remote host.

RETURNS:	success:  unique SIMPL receiver's id
			failure: -1
*******************************************************************************/

long nameLocate(EthernetClient *client, char *name)
{
const char *func = "nameLocate";
int ret;
SG_NAME_LOCATE_MSG msg;

// check for a  name
if (!strlen(name))
	{
	sprintf(simpl_errstr, "%s: a name is required", func);
	return(-1);
	}
	
// check that name length is within bounds
if (strlen(name) > MAX_NAME_LEN)
	{
	sprintf(simpl_errstr, "%s: name must be <= %d", func, MAX_NAME_LEN);
	return(-1);
	}

// create the name locate message to be sent to the tclSurrogate
msg.token = SG_NAME_LOCATE;
msg.nbytes = sizeof(SG_NAME_LOCATE_MSG) - sizeof(msg.whom);
msg.whom = -1;
strcpy(msg.thisName, name);
msg.rc = -1;

// check to see that the client is connected
if (!client->connected())
	{
	sprintf(simpl_errstr, "%s: client not connected", func);
	return(-1);
	}

// write out the name locate message on the socket to the tclSurrogate
ret = client->write((uint8_t *)&msg, sizeof(SG_NAME_LOCATE_MSG));
if (ret != sizeof(SG_NAME_LOCATE_MSG))
	{
	sprintf(simpl_errstr, "%s: incorrect write on name locate message", func);
	return(-1);
	}

// wait until response is ready to be read
ret = commDelay(client);
if (ret == -1)
	{
	sprintf(simpl_errstr, "%s: tclSurrogate unavailable for read", func);
	return(-1);
	}

// read reply from the tclSurrogate
ret = client->read((uint8_t *)&msg, sizeof(unsigned short) << 1);
if ( ret != (sizeof(unsigned short) << 1) )
	{
	sprintf(simpl_errstr, "%s: incorrect read on header", func);
	return(-1);
	}

// check the reply token
if (msg.token != SG_REPLY_IT)
	{
	sprintf(simpl_errstr, "%s: incorrect message token", func);
	return(-1);
	}

// check the incoming message for the number of bytes
ret = client->read((uint8_t *)&(msg.whom), msg.nbytes);
if (ret != msg.nbytes)
	{
	sprintf(simpl_errstr, "%s: incorrect read on message", func);
	return(-1);
	}
	
// return the tclSurrogate child's unique identifier
return(msg.rc);
}

/*******************************************************************************
FUNCTION:	int Send(EthernetClient *, long *, void *, void *, unsigned,
unsigned)

PURPOSE:	Sends message to and receives reply from a receiver.

RETURNS:	success:  size of replied message (if any).
			failure: -1
*******************************************************************************/

int Send(EthernetClient *client, long *receiverId, void *oMsg, void *iMsg,
unsigned oSize, unsigned iSize)
{
const char *func = "Send";
int ret;
SG_MSG msg;

// compose message header to tclSurrogate
msg.token = SG_SEND_IT;
// the sizeof(whom) will be taken off at the other end
msg.nbytes = oSize + sizeof(msg.whom);
msg.whom = *receiverId;

// check to see that the client is connected
if (!client->connected())
	{
	sprintf(simpl_errstr, "%s: client not connected", func);
	return(-1);
	}

// write out the send message 
ret = client->write((uint8_t *)&msg, sizeof(SG_MSG));
if (ret != sizeof(SG_MSG))
	{
	sprintf(simpl_errstr, "%s: incorrect write on header", func);
	return(-1);
	}

// write out the actual messsage
ret = client->write((uint8_t *)oMsg, oSize);
if (ret != oSize)
	{
	sprintf(simpl_errstr, "%s: incorrect write on message", func);
	return(-1);
	}
	
// read reply from the tclSurrogate
ret = commDelay(client);
if (ret == -1)
	{
	sprintf(simpl_errstr, "%s: tclSurrogate unavailable for read", func);
	return(-1);
	}

ret = client->read((uint8_t *)&msg, sizeof(SG_MSG));
if (ret != sizeof(SG_MSG))
	{
	sprintf(simpl_errstr, "%s: incorrect read on header", func);
	return(-1);
	}
	
// check the reply token
if (msg.token != SG_REPLY_IT)
	{
	sprintf(simpl_errstr, "%s: incorrect reply message token", func);
	return(-1);
	}

	// check the size of the incoming reply message
if ((msg.nbytes - sizeof(msg.whom)) > iSize)
	{
	sprintf(simpl_errstr, "%s: reply message too large", func);
	return(-1);
	}

// check the incoming message for the number of bytes
ret = client->read((uint8_t *)iMsg, msg.nbytes - sizeof(msg.whom));
if (ret != (msg.nbytes- sizeof(msg.whom)))
	{
	sprintf(simpl_errstr, "%s: incorrect read on message", func);
	return(-1);
	}

return(ret);
}

/*******************************************************************************
FUNCTION:	int Receive(EthernetClient *, long *, void *, unsigned)

PURPOSE:	Receives a message from a sender.

RETURNS:	success:  size of sent message.
			failure: -1
*******************************************************************************/

int Receive(EthernetClient *client, long *senderId, void *iMsg, unsigned iSize)
{
const char *func = "Receive";
int ret;
SG_MSG msg;

// check to see that the client is connected
if (!client->connected())
	{
	sprintf(simpl_errstr, "%s: client not connected", func);
	return(-1);
	}

// is there something to read? If not, return.
if (!client->available())
	{
	return(0);
	}

// read  the start of the message	
ret = client->read((uint8_t *)&msg, sizeof(SG_MSG));
if (ret != sizeof(SG_MSG))
	{
	sprintf(simpl_errstr, "%s: incorrect read on header", func);
	return(-1);
	}

// check the reply token
if (msg.token != SG_RELAY_IT)
	{
	sprintf(simpl_errstr, "%s: incorrect message token", func);
	return(-1);
	}

// check the size of the incoming message
if ((msg.nbytes - sizeof(msg.whom)) > iSize)
	{
	sprintf(simpl_errstr, "%s: incoming message too large", func);
	return(-1);
	}

// check the incoming message for the number of bytes
ret = client->read((uint8_t *)iMsg, msg.nbytes - sizeof(msg.whom));
if (ret != (msg.nbytes - sizeof(msg.whom)))
	{
	sprintf(simpl_errstr, "%s: incorrect read on message", func);
	return(-1);
	}

// got this far without apparent error, set the id of the sender
*senderId = msg.whom;
	
return(ret);
}

/*******************************************************************************
FUNCTION:	int Reply(EthernetClient *, long *, void *, unsigned)

PURPOSE:	Replies a message to a sender (if any).

RETURNS:	success:  0
			failure: -1
*******************************************************************************/

int Reply(EthernetClient *client, long *senderId, void *oMsg, unsigned oSize)
{
const char *func = "Reply";
SG_MSG msg;

// compose message header to tclSurrogate
msg.token = SG_REPLY_IT;
// the sizeof(whom) will be taken off at the other end
msg.nbytes = oSize + sizeof(msg.whom);
msg.whom = *senderId;

// check to see that the client is connected
if (!client->connected())
	{
	sprintf(simpl_errstr, "%s: client not connected", func);
	return(-1);
	}

// write out the send message
if (client->write((uint8_t *)&msg, sizeof(SG_MSG)) != sizeof(SG_MSG))
	{
	sprintf(simpl_errstr, "%s: incorrect write on header", func);
	return(-1);
	}

// write out the actual messsage
if (client->write((uint8_t *)oMsg, oSize) != oSize)
	{
	sprintf(simpl_errstr, "%s: incorrect write on message", func);
	return(-1);
	}

return(0);
}

/*******************************************************************************
FUNCTION:	char whatsMyError(void)

PURPOSE:	Returns the contents of the SIMPL library error/message string.

RETURNS:	char *
*******************************************************************************/

char *whatsMyError()
{
return(simpl_errstr);
}

/*******************************************************************************
FUNCTION:	int commDelay(EthernetClient *)

PURPOSE:	Sometimes found to be necessary when setting up a socket commection
			between an arduino and a remote host. Connections don't necessarily
			occur in the first pass and so this function tries to connect
			COMM_TRY times and waits COMM_TIMEOUT in between attempts.

RETURNS:	success:  0
			failure: -1
*******************************************************************************/

int commDelay(EthernetClient *client)
{
for (int i = 0; i <  COMM_TRY; i++)
	{
	if (client->available())
		{
		return(0);
		}
	delay(COMM_TIMEOUT);
	}

return(-1);
}