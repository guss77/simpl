#import required modules
from wssimpl import *
from array import array
import sys

def constructMsg():
	packChar("A", BIN)
	packDouble(3.1415, BIN)
	packShort(2, BIN)
	packChar("B", BIN)
	packLong(24, BIN)
	packChar("C", BIN)
	packFloat(2.1718, BIN)
	packInt(37, BIN)
	packString("we are the knights who say nee!", BIN)

	a = array("c", "ZZZZZZZZZ")
	b = array("h", [0, 1, 2, 3, 4, 5, 6, 7, 8])
	c = array("i", [0, 1, 2, 3, 4, 5, 6, 7, 8])
	d = array("l", [0, 1, 2, 3, 4, 5, 6, 7, 8])
	e = array("f", [1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9])
	f = array("d", [.1, .02, .003, .0004, .00005, .000006, 0.0000007])

	packCharArray(a, BIN)
	packShortArray(b, BIN)
	packIntArray(c, BIN)
	packLongArray(d, BIN)
	packFloatArray(e, BIN)
	packDoubleArray(f, BIN)

def deconstructMsg():
	print unpackChar(BIN)
	print unpackDouble(BIN)
	print unpackShort(BIN)
	print unpackChar(BIN)
	print unpackLong(BIN)
	print unpackChar(BIN)
	print unpackFloat(BIN)
	print unpackInt(BIN)
	print unpackString(31, BIN)

	var1 = " " * 9
	g = array("c", var1)
	unpackCharArray(g, BIN)
	print g

	var2 = [0] * 9
	h = array("h", var2)
	unpackShortArray(h, BIN)
	print h
	
	var3 = [0] * 9
	i = array("i", var3)
	unpackIntArray(i, BIN)
	print i
	
	var4 = [0] * 9
	j = array("l", var4)
	unpackLongArray(j, BIN)
	print j

	var5 = [0] * 9
	k = array("f", var5)
	unpackFloatArray(k, BIN)
	print k
	
	var6 = [0] * 7
	l = array("d", var6)
	unpackDoubleArray(l, BIN)
	print l

#***** main part of program ****************************************

# name attach
myName = "SENDER"
name = "50000:localhost:" + myName
ret = nameAttach(name, 1024)
if ret == -1:
	print "%s: name attach error-%s" %(myName, whatsMyError())
	sys.exit(-1)

# name locate receiver program
id = nameLocate("RECEIVER_B")
if id == -1:
	print "%s: name locate error-%s" %(myName, whatsMyError())
	sys.exit(-1)

# build outgoing message
constructMsg()

# send the message to the receiver program
ret = send(id)
if ret == -1:
	print "%s: send error-%s" %(myName, whatsMyError())
	sys.exit(-1)

# examine the return message
deconstructMsg()

# exit gracefully
nameDetach()
