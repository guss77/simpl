"""
A module library for python-based SIMPL remotely connected to tclSurrogate.
Built with running one-sided SIMPL in mind for platforms like Windows.
"""

import socket
import struct

NAME_ATTACH = 0
NAME_DETACH = 1
NAME_LOCATE = 2
SEND_IT = 3
REPLY_IT = 4
RELAY_IT = 5
SEND_NO_REPLY = 8
ACK = 9
PORT = 8001

SCHAR = struct.calcsize("c")
SSHORT = struct.calcsize("h")
SINT = struct.calcsize("i")

global gatewaySocket

def getBinaryValue(msg, offset, size, type):
	if type == "s":
		format = str(size) + "s"
	else:
		format = type
	start = offset
	stop = start + size
	t = struct.unpack(format, msg[start:stop])
	return t[0]

#############################################################################
"""
nameAttach() creates a socket connection to tclSurrogate on a remote host
and registers its name with that host for SIMPL communication to ensue
"""
def nameAttach(destination):
	# get the port/oneSurrogate host/simpl name
	port, host, name = phn(destination)

	"""
	print "port=", port
	print "host=", host
	print "name=", name
	"""

	# check for error and possibly set port to default
	if port == -1:
		return -1
	elif port == 0:
		port = PORT
	
	# generate a socket
	global gatewaySocket
	gatewaySocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	
	# connect the socket to the appropriate port and host address
	gatewaySocket.connect((host, port))
	
	# calculate the size of the name attach message without header
	size = SINT + 20 * SCHAR + SINT
	
	# compose the name_attach message to be sent to tclSurrogate
	sMsg = struct.pack("HHi" + str(20) + "si", NAME_ATTACH, size, -1, name, -1)
	
	# send message to tclSurrogate
	gatewaySocket.send(sMsg)
	
	# calculate the size of the reply message from the tclSurrogate
	size = 2 * SSHORT + SINT + 20 * SCHAR + 2 * SINT
	
	# read the reply from tclSurrogate
	numRead, rMsg = readStream(size)

	"""
	print "expected size= ", size
	print "message size=", len(rMsg)
	print "numRead = ", numRead
	token = getBinaryValue(rMsg, 0, SSHORT, "H")
	print "token=", token
	bytes = getBinaryValue(rMsg, SSHORT, SSHORT, "H")
	print "bytes=", bytes
	towhom = getBinaryValue(rMsg, 2 * SSHORT, SINT, "i")
	print "towhom=", towhom
	name = getBinaryValue(rMsg, 2 * SSHORT + SINT, \
		20 * SCHAR, "s")
	print "name=", name
	"""

	# check number of bytes read
	if numRead != size:
		return -1
	
	# check incoming token
	token = getBinaryValue(rMsg, 0, SSHORT, "H")
	if token != REPLY_IT:
		return -1
	
	# calculate the offset to the return code within the message
	offset = 2 * SSHORT + SINT + 20 * SCHAR
	# retrieve the return code from the message
	rc = getBinaryValue(rMsg, offset, SINT, "i")

	return rc

#############################################################################

def nameDetach():
	# compose the name_detach message to be sent to tclSurrogate
	sMsg = struct.pack("HH", NAME_DETACH, 0)

	# send closure message
	gatewaySocket.send(sMsg)
	gatewaySocket.close()
	
	return 0

#############################################################################
"""
nameLocate() tells the surrogate on the remote host to locally connect to
the said host. The surrogate does so, and if successful, acts like a relay
between the sender and the receiver.
"""
def nameLocate(name):
	# calculate the size of the name locate message without header
	size = SINT + 20 * SCHAR + SINT
	
	# compose the name_locate message to be sent to tclSurrogate
	sMsg = struct.pack("HHi" + str(20) + "si", NAME_LOCATE, size, -1, name, -1)
	
	# send message to tclSurrogate
	gatewaySocket.send(sMsg)

	# calculate the size of the reply message from the tclSurrogate
	size = 2 * SSHORT + SINT + 20 * SCHAR + \
		SINT
		
	# read the response from tclSurrogate
	numRead, rMsg = readStream(size)
	
	"""
	print "size=", len(rMsg)
	print "numRead=", numRead
	token = getBinaryValue(rMsg, 0, SSHORT, "H")
	print "token=", token
	bytes = getBinaryValue(rMsg, SSHORT, SSHORT, "H")
	print "bytes=", bytes
	towhom = getBinaryValue(rMsg, 2 * SSHORT, SINT, "i")
	print "towhom=", towhom
	name = getBinaryValue(rMsg, 2 * SSHORT + SINT, \
		20 * SCHAR, "s")
	print "name=", name
	receiverID = getBinaryValue(rMsg, offset, SINT, "i")
	print "receiverID=", receiverID
	"""
	
	# check number of bytes read
	if numRead != size:
		return -1
	
	# check incoming token
	token = getBinaryValue(rMsg, 0, SSHORT, "H")
	if token != REPLY_IT:
		return -1
	
	# calculate the offset to the return code within the message
	offset = 2 * SSHORT + SINT + 20 * SCHAR
	# retrieve the return code from the message
	receiverID = getBinaryValue(rMsg, offset, SINT, "i")
	
	return receiverID
	
#############################################################################
"""
send() writes a message to the remote surrogate which then relays on the
message to the appropriate receiver.
"""
def send(receiverID, sMsg):
	# calculate the size of the  message to send without header
	size = SINT + len(sMsg)
	
	# compose the send message to be sent to tclSurrogate
	msg = struct.pack("HHi" + str(len(sMsg)) + "s", SEND_IT, size,\
		receiverID, sMsg)

	# send message to tclSurrogate
	gatewaySocket.send(msg)

	# calculate the size of the reply message front
	frontSize = 2 * SSHORT + SINT

	# read reply header
	numRead, hdr = readStream(frontSize)
	
	# check number of bytes read
	if numRead != frontSize:
		return -1, ""
		
	# extract the header values
	token, nbytes, toWhom = struct.unpack("HHi", hdr)
	if token != REPLY_IT:
		return -1, ""
	
	# is there any reply message?
	amount = nbytes - SINT
	if amount > 0:
		# read balance of reply - if any
		numRead, rMsg = readStream(amount)
		if numRead != amount:
			return -1, ""
	else:
		numRead = 0
		rMsg = ""
		
	return numRead, rMsg

#############################################################################
"""
not finished --- tclSurrogate cannot handle triggers at this time
"""
"""
def trigger(receiverID, proxy):
	# calculate the size of the  message to send without header
	size = SINT + psiml.SINT
	
	# compose the send message to be sent to tclSurrogate
	msg = struct.pack("HHii" + str(len(sMsg)) + "s", SEND_NO_REPLY, size,\
		receiverID, proxy)

	# send message to tclSurrogate
	gatewaySocket.send(msg)
		
	return proxy
"""

#############################################################################
"""
receive() reads messages from the remote sender via the remote surrogate.
"""
def receive():
	# calculate the size of the  message header
	hdrSize = 2 * SSHORT
	
	# messages are always preceded by a header
	numRead, hdr = readStream(hdrSize)
	
	# check number of bytes read
	if numRead != hdrSize:
		return -1, -1, ""
		
	# extract the header values
	token, nbytes = struct.unpack("HH", hdr)
	if token != RELAY_IT:
		return -1, -1, ""
	
	if nbytes < -1:
		return nbytes, -1, ""
	
	# get the balance of the message
	numRead, rMsg = readStream(nbytes)
	if numRead != nbytes:
		return -1, -1, ""
	
	# extract the sender's id
	senderID = getBinaryValue(rMsg, 0, SINT, "i")
		
	# extract the actual message - if any
	if nbytes - SINT > 0:
		databytes = nbytes - SINT
		data = getBinaryValue(rMsg, SINT, databytes, "s")
	else:
		databytes = 0
		data = ""
				
	return databytes, senderID, data

#############################################################################
"""
reply() responds back to a sender's remote surrogate.
"""
def reply(senderID, rMsg):
	if len(rMsg) > 0:
		# calculate the size of the  message to send without header
		size = SINT + len(rMsg)
	
		# compose the send message to be sent to tclSurrogate
		msg = struct.pack("HHi" + str(len(rMsg)) + "s", REPLY_IT, size, \
			senderID, rMsg)
	else:
		# calculate the size of the  message to send without header
		size = SINT
	
		# compose the send message to be sent to tclSurrogate
		msg = struct.pack("HHi", REPLY_IT, size, senderID)

	# send reply message to tclSurrogate
	gatewaySocket.send(msg)
	#print "mesage size=", size
	return 0

#############################################################################
"""
for use with receiving proxies when the surrogate is able to handle them
"""
def returnProxy(value):
	return (value * -1) - 1

#############################################################################
"""
a lay over from the C library; needed for backward compatibility
may be used in future
"""
def whatsMyError():
	return "python SIMPL error"

#############################################################################
"""
for delineating nameAttach() strings.
"""
def phn(str):
	# str = port:host:name OR host:name
	# how many :'s are there in str?
	a = 0
	for i in range(0, len(str)):
		if str[i] == ":":
			a = a + 1
	
	if a == 1:
		for i in range(0, len(str)):
			if str[i] == ":":
				host = str[0:i]
				name = str[i+1:len(str)]
		return 0, host, name
	elif a == 2:
		for i in range(0, len(str)):
			if str[i] == ":":
				port = int(str[0:i])
				break
		for j in range(i+1, len(str)):
			if str[j] == ":":
				host = str[i+1:j]
				name = str[j+1:len(str)]
		return port, host, name
	else:
		return -1, "", ""

############################################################################
"""
for reading buffered streams from sockets
"""
def readStream(nBytes):
	total = 0
	numLeft = nBytes
	msg = ""
	
	while (numLeft > 0):
		rMsg = gatewaySocket.recv(numLeft)
		numRead = len(rMsg)
		if numRead != 0:
			numLeft -= numRead
			total += numRead
			s = msg
			msg = s + rMsg
			
	return total, msg
