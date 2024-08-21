"""
This is a python simpl text-based example sender

Usage: python sender_txt.py receiverName tokenType
"""

#! /usr/bin/python

import sys
import struct
import simpl

# some variables
sName = "py_sender"
rName = sys.argv[1]

if sys.argv[2] == "10": 
	print "token = 10"	
	token = 10
	var1 = 99
	var2 = 999
	var3 = 9999
	outBuffer = struct.pack("iiii", token, var1, var2, var3)
elif sys.argv[2] == "20":
	print "token = 20"	
	token = 20
	var1 = 3.1415
	outBuffer = struct.pack("if", token, var1)
elif sys.argv[2] == "30":
	print "token = 30"	
	token = 30
	var2 = "this is the castle of my master..."
	var1 = len(var2)
	outBuffer = struct.pack("ii" + str(var1) + "s", token, var1, var2)
else:
	print "unknown message type"
	sys.exit(-1)
	
print repr(outBuffer)

# attach a simpl name
retVal = simpl.name_attach(sName)
if retVal == -1:
	print "%s: name attach error-%s" %(sName, simpl.whatsMyError()) 
	sys.exit(-1)

# name locate receiver
receiverId = simpl.name_locate(rName)
if receiverId == -1:
	print "%s: name locate error-%s" %(sName, simpl.whatsMyError()) 
	sys.exit(-1)

# send the message
retVal = simpl.Send(receiverId, outBuffer, None)
if retVal == -1:
	print "%s: send error-%s" %(sName, simpl.whatsMyError())
	sys.exit(-1)
