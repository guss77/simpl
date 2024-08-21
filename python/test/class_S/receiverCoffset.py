#import required modules
import wssimpl
from array import array
import sys

def constructMsg(nee):
	nee.packChar("A", 0)
	nee.packDouble(3.1415, 5)
	nee.packShort(2, 15)
	nee.packChar("B", 20)
	nee.packLong(24, 25)
	nee.packChar("C", 35)
	nee.packFloat(2.1718, 45)
	nee.packInt(37, 50)
	nee.packString("we are the knights who say nee!", 55)

	a = array("c", "ZZZZZZZZZ")
	b = array("h", [0, 1, 2, 3, 4, 5, 6, 7, 8])
	c = array("i", [0, 1, 2, 3, 4, 5, 6, 7, 8])
	d = array("l", [0, 1, 2, 3, 4, 5, 6, 7, 8])
	e = array("f", [1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9])
	f = array("d", [.1, .02, .003, .0004, .00005, .000006, 0.0000007])

	nee.packCharArray(a, 100)
	nee.packShortArray(b, 200)
	nee.packIntArray(c, 300)
	nee.packLongArray(d, 400)
	nee.packFloatArray(e, 500)
	nee.packDoubleArray(f, 600)

def deconstructMsg(nee):
	print "receiver incoming message"
	print nee.unpackChar(0)
	print nee.unpackDouble(5)
	print nee.unpackShort(15)
	print nee.unpackChar(20)
	print nee.unpackLong(25)
	print nee.unpackChar(35)
	print nee.unpackFloat(45)
	print nee.unpackInt(50)
	print nee.unpackString(31, 55)

	var1 = " " * 9
	g = array("c", var1)
	nee.unpackCharArray(g, 100)
	print g

	var2 = [0] * 9
	h = array("h", var2)
	nee.unpackShortArray(h, 200)
	print h
	
	var3 = [0] * 9
	i = array("i", var3)
	nee.unpackIntArray(i, 300)
	print i
	
	var4 = [0] * 9
	j = array("l", var4)
	nee.unpackLongArray(j, 400)
	print j

	var5 = [0] * 9
	k = array("f", var5)
	nee.unpackFloatArray(k, 500)
	print k
	
	var6 = [0] * 7
	l = array("d", var6)
	nee.unpackDoubleArray(l, 600)
	print l

#***** main part of program ****************************************

nee = wssimpl.Simpl()

# name attach

myName = "RECEIVER_O"
name = "50000:localhost:" + myName
ret = nee.nameAttach(name, 1024)
if ret == -1:
	print "%s: name attach error-%s" %(myName, nee.whatsMyError())
	sys.exit(-1)

while 1:
	# receive a message
	messageSize, senderId = nee.receive()
	if messageSize == -1:
		# error
		print "%s: receive error-%s" %(myName, nee.whatsMyError())
		sys.exit(-1)

	# examine the message
	deconstructMsg(nee)

	# build reply message
	constructMsg(nee)

	# reply to sending program
	retVal = nee.reply(senderId)
	if retVal == -1:
		print "%s: reply error-%s" %(myName, nee.whatsMyError())
		sys.exit(-1)
