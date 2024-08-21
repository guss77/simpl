"""
This is a python simpl gui-based example receiver
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
from ScrolledText import *
from Tkinter import *
from psimpl import getBinaryValue, SINT, SFLOAT, SLONG
from simpl import name_attach, Receive, Reply, whatsMyRecvfd, whatsMyError

def hndlMessage(a, b):
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
		# react to the token
		tokenAction(token, message)

	# reply to the sender
	retVal = Reply(senderId, None)
	if retVal == -1:
		print "%s: reply error-%s" %(rName, whatsMyError())
		sys.exit(-1)

def tokenAction(token, message):
	if token == 10:
		var1 = getBinaryValue(message, SINT, SINT, "i")
		var2 = getBinaryValue(message, 2 * SINT, SINT, "i")
		var3 = getBinaryValue(message, 3 * SINT, SINT, "i")
		str = "token=%d var1=%d var2=%d var3=%d\n" %(token, var1, var2, var3)
		text.insert(END, str)
	elif token == 20:
		var1 = getBinaryValue(message, SINT, SFLOAT, "f")
		str = "token=%d var1=%f\n" %(token, var1)
		text.insert(END, str)
	elif token == 30:
		length = getBinaryValue(message, SINT, SFLOAT, "i")
		var1 = getBinaryValue(message, 2 * SINT, length, "s")
		str = "token=%d var1=%s\n" %(token, var1)
		text.insert(END, str)
	else:
		print "%s: unknown token type=%d\n" %(rName, token)

def finish(event):
	sys.exit(0)

# set this program's name
rName = "py_receiver"

# attach a simpl name
retVal = name_attach(rName)
if retVal == -1:
	print "%s: name attach error-%s" %(rName, whatsMyError())
	sys.exit(-1)

# get the receive fifo file dsecriptor
fd = whatsMyRecvfd()

# initialize graphics
root = Tk()

# attach a callback for incoming messages
root.tk.createfilehandler(fd, READABLE, hndlMessage)

button = Button(root)
button["text"] = "Exit"
button.bind("<Button-1>", finish)
button.pack()

text = ScrolledText(root, background="white")
text.pack() 

root.mainloop()
