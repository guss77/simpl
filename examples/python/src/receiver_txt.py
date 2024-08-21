"""
This is a python simpl text-based example receiver
"""

"""
you will need to either
1. export PYTHONPATH=/home/simpl/simpl.2.0.3/python/modules
OR
2. copy psimpl.py to /usr/lib/python1.5/lib-dynload
for importing psimpl
"""

#! /usr/bin/python

import sys
import struct
from psimpl import getBinaryValue, SINT, SFLOAT, SLONG
from simpl import name_attach, Receive, Reply, whatsMyError

# set this program's name
rName = "py_receiver"

# attach a simpl name
retVal = name_attach(rName)
if retVal == -1:
	print "%s: name attach error-%s" %(rName, whatsMyError())
	sys.exit(-1)

# receive and process a message
while 1:
	# receive a message
	messageSize, senderId, message = Receive()

	# check for error
	if messageSize == -1:
		print "%s: receive error-%s" %(rName, whatsMyError())
		sys.exit(-1)
	# is it a non-null message?
	elif messageSize > 0:
		# extract the token from the message
		token = getBinaryValue(message, 0, SINT, "i")

		# react on token
		if token == 10:
			var1 = getBinaryValue(message, SINT, SINT, "i")
			var2 = getBinaryValue(message, 2 * SINT, SINT, "i")
			var3 = getBinaryValue(message, 3 * SINT, SINT, "i")
			print "%s: token=%d var1=%d var2=%d var3=%d" %(rName, token, var1, var2, var3)

		elif token == 20:
			var1 = getBinaryValue(message, SINT, SFLOAT, "f")
			print "%s: token=%d var1=%f" %(rName, token, var1)

		elif token == 30:
			length = getBinaryValue(message, SINT, SFLOAT, "i")
			var1 = getBinaryValue(message, 2 * SINT, length, "s")
			print "%s: token=%d var1=%s" %(rName, token, var1)

		else:
			print "%s: unknown token type=%d" %(rName, token)

	retVal = Reply(senderId, None)
	if retVal == -1:
		print "%s: reply error-%s" %(rName, whatsMyError())
		sys.exit(-1)
