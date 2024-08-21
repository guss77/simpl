# sender.py: This is a python simpl text-based sender.
# used for testing send() and trigger()
#! /usr/bin/python

# import required modules
import sys
import struct
import ssimpl

# initialize necessary variables
sName = "50000:localhost:SENDER"
rName = "RECEIVER"

# enable this script to utilize simpl
retVal = ssimpl.nameAttach(sName)
if retVal == -1:
	print "%s: name attach error-%s" %(sName, ssimpl.whatsMyError())
	sys.exit(-1)

# name locate the receiver program
receiverId = ssimpl.nameLocate(rName)
if receiverId == -1:
	print "%s: name locate error-%s" %(sName, ssimpl.whatsMyError())
	sys.exit(-1)

# send a message
# compose and send the message
token = 10
var1 = 99
var2 = 999
var3 = 9999
outBuffer = struct.pack("iiii", token, var1, var2, var3)

# compose reply
var4 = 1
inBuffer = struct.pack("i", var4)
	
retVal, inBuffer = ssimpl.send(receiverId, outBuffer)
if retVal == -1:
	print "%s: send error-%s" %(sName, ssimpl.whatsMyError())
	sys.exit(-1)

if (retVal > 0):
	t = struct.unpack("i", inBuffer[0:struct.calcsize("i")])
	var5 = t[0]
	print "%s: reply=%d" %(sName, var5)

ssimpl.nameDetach()