#import required modules
import wssimpl
from array import array
import sys

def constructMsg(nee):
	nee.packChar("A", nee.CHR)
	nee.packDouble(3.1415, nee.CHR)
	nee.packShort(2, nee.CHR)
	nee.packChar("B", nee.CHR)
	nee.packLong(24, nee.CHR)
	nee.packChar("C", nee.CHR)
	nee.packFloat(2.1718, nee.CHR)
	nee.packInt(37, nee.CHR)
	nee.packString("we are the knights who say nee!", nee.CHR)

	a = array("c", "ZZZZZZZZZ")
	b = array("h", [0, 1, 2, 3, 4, 5, 6, 7, 8])
	c = array("i", [0, 1, 2, 3, 4, 5, 6, 7, 8])
	d = array("l", [0, 1, 2, 3, 4, 5, 6, 7, 8])
	e = array("f", [1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9])
	f = array("d", [.1, .02, .003, .0004, .00005, .000006, 0.0000007])

	nee.packCharArray(a, nee.CHR)
	nee.packShortArray(b, nee.CHR)
	nee.packIntArray(c, nee.CHR)
	nee.packLongArray(d, nee.CHR)
	nee.packFloatArray(e, nee.CHR)
	nee.packDoubleArray(f, nee.CHR)

def deconstructMsg(nee):
	print "receiver incoming message"
	print nee.unpackChar(nee.CHR)
	print nee.unpackDouble(nee.CHR)
	print nee.unpackShort(nee.CHR)
	print nee.unpackChar(nee.CHR)
	print nee.unpackLong(nee.CHR)
	print nee.unpackChar(nee.CHR)
	print nee.unpackFloat(nee.CHR)
	print nee.unpackInt(nee.CHR)
	print nee.unpackString(31, nee.CHR)

	var1 = " " * 9
	g = array("c", var1)
	nee.unpackCharArray(g, nee.CHR)
	print g

	var2 = [0] * 9
	h = array("h", var2)
	nee.unpackShortArray(h, nee.CHR)
	print h
	
	var3 = [0] * 9
	i = array("i", var3)
	nee.unpackIntArray(i, nee.CHR)
	print i
	
	var4 = [0] * 9
	j = array("l", var4)
	nee.unpackLongArray(j, nee.CHR)
	print j

	var5 = [0] * 9
	k = array("f", var5)
	nee.unpackFloatArray(k, nee.CHR)
	print k
	
	var6 = [0] * 7
	l = array("d", var6)
	nee.unpackDoubleArray(l, nee.CHR)
	print l

#***** main part of program ****************************************

nee = wssimpl.Simpl()

# name attach
myName = "RECEIVER_C"
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
