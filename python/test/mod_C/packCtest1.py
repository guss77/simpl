#import required modules
from wcsimpl import *
from array import array
import time
import sys

ret = nameAttach("PACK_TEST_1", 1024)
if ret == -1:
	print "%s: name attach error-%s" %(whatsMyError())
	sys.exit(-1)

packChar("A", BIN)
packDouble(3.1415, BIN)
packShort(2, BIN)
packChar("B", BIN)
packLong(24.424242, BIN)
packChar("C", BIN)
packFloat(2.1718, BIN)
packInt(37, BIN)
packString("we are the knights who say nee!", BIN)
	
a = array("c", "012345678")
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

crossCopy()

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
		
print
print repr(returnInBuffer())
print "msg size =%d" %(len(returnOutBuffer()))

nameDetach()
