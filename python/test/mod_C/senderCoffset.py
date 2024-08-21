#import required modules
from wcsimpl import *
from array import array
import sys

def constructMsg():
	packChar("A", 0)
	packDouble(3.1415, 5)
	packShort(2, 15)
	packChar("B", 20)
	packLong(24, 25)
	packChar("C", 35)
	packFloat(2.1718, 45)
	packInt(37, 50)
	packString("we are the knights who say nee!", 55)

	a = array("c", "ZZZZZZZZZ")
	b = array("h", [0, 1, 2, 3, 4, 5, 6, 7, 8])
	c = array("i", [0, 1, 2, 3, 4, 5, 6, 7, 8])
	d = array("l", [0, 1, 2, 3, 4, 5, 6, 7, 8])
	e = array("f", [1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9])
	f = array("d", [.1, .02, .003, .0004, .00005, .000006, 0.0000007])

	packCharArray(a, 100)
	packShortArray(b, 200)
	packIntArray(c, 300)
	packLongArray(d, 400)
	packFloatArray(e, 500)
	packDoubleArray(f, 600)

def deconstructMsg():
	print "sender: replied message"
	print unpackChar(0)
	print unpackDouble(5)
	print unpackShort(15)
	print unpackChar(20)
	print unpackLong(25)
	print unpackChar(35)
	print unpackFloat(45)
	print unpackInt(50)
	print unpackString(31, 55)

	var1 = " " * 9
	g = array("c", var1)
	unpackCharArray(g, 100)
	print g

	var2 = [0] * 9
	h = array("h", var2)
	unpackShortArray(h, 200)
	print h
	
	var3 = [0] * 9
	i = array("i", var3)
	unpackIntArray(i, 300)
	print i
	
	var4 = [0] * 9
	j = array("l", var4)
	unpackLongArray(j, 400)
	print j

	var5 = [0] * 9
	k = array("f", var5)
	unpackFloatArray(k, 500)
	print k
	
	var6 = [0] * 7
	l = array("d", var6)
	unpackDoubleArray(l, 600)
	print l

#***** main part of program ****************************************
	
# name attach
myName = "SENDER"
ret = nameAttach(myName, 1024)
if ret == -1:
	print "%s: name attach error-%s" %(myName, whatsMyError())
	sys.exit(-1)

# name locate receiver program
id = nameLocate("RECEIVER_O")
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
