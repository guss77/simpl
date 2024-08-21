"""
This is a python simpl gui-based example sender

Usage: python sender_gui.py receiverName
"""

#! /usr/bin/python

# import necessry modules
import sys
import struct
import simpl
from Tkinter import *

def hndlButton1(event):
	token = 10
	var1 = 99
	var2 = 999
	var3 = 9999
	out = struct.pack("iiii", token, var1, var2, var3)
	makeSend(out)

def hndlButton2(event):
	token = 20
	var1 = 3.1415
	out = struct.pack("if", token, var1)
	makeSend(out)

def hndlButton3(event):
	token = 30
	var2 = "this is the castle of my master..."
	var1 = len(var2)
	out = struct.pack("ii" + str(var1) + "s", token, var1, var2)
	makeSend(out)

def makeSend(out):
	retVal = simpl.Send(receiverId, out, None)
	if retVal == -1:
		print "%s: send error-%s" %(sName, simpl.whatsMyError())
		sys.exit(-1)

def die(event):
	sys.exit(0)

# initialize some variables
sName = "py_sender"
rName = sys.argv[1]

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

# initialize Tk
root = Tk()

# set up a button to initiate the sending of message token type 10
button = Button(root)
button["text"] = "send message token type 10"
button.bind("<Button-1>", hndlButton1);
button.pack()

# set up a button to initiate the sending of message token type 20
button = Button(root)
button["text"] = "send message token type 20"
button.bind("<Button-1>", hndlButton2);
button.pack()

# set up a button to initiate the sending of message token type 30
button = Button(root)
button["text"] = "send message token type 30"
button.bind("<Button-1>", hndlButton3);
button.pack()

# set up a button for program exit
button = Button(root)
button["text"] = "Exit"
button.bind("<Button-1>", die);
button.pack()

# handle user input forever
root.mainloop()
