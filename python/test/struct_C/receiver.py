# receiver.py: This is a python simpl text-based receiver.
#! /usr/bin/python

# import required modules
import sys
import struct
import csimpl

# set this program's name
rName = "RECEIVER"

# enable this script to utilize simpl
retVal = csimpl.nameAttach(rName)
if retVal == -1:
	print "%s: name attach error-%s" %(rName, csimpl.whatsMyError())
	sys.exit(-1)

# receive a message
msgSize, senderId, msg = csimpl.receive()
if msgSize == -1:
	# error
	print "%s: receive error-%s" %(rName, csimpl.whatsMyError())
	sys.exit(-1)
elif msgSize < -1:
	# proxy
	proxy = csimpl.returnProxy(msgSize)
	print "%s: received=%d proxy=%d" %(rName, msgSize, proxy)
else:
	# message
	# extract the token from the message
	start = 0
	end = struct.calcsize("i")
	t = struct.unpack("i", msg[start:end])
	token = t[0]

	# react on token value
	if token == 10:
		start = end
		end = 2 * struct.calcsize("i")
		t = struct.unpack("i", msg[start:end])
		var1 = t[0]
		start = end
		end = 3 * struct.calcsize("i")
		t = struct.unpack("i", msg[start:end])
		var2 = t[0]
		start = end
		end = 4 * struct.calcsize("i")
		t = struct.unpack("i",msg[start:end])
		var3 = t[0]
		print "%s: token=%d var1=%d var2=%d var3=%d" %(rName, token, var1,
var2, var3)

	# reply to sending program
	var4 = 7
	out = struct.pack("i", var4)
	retVal = csimpl.reply(senderId, out)
	if retVal == -1:
		print "%s: reply error-%s" %(rName, csimpl.whatsMyError())
		sys.exit(-1)

csimpl.nameDetach()