#import required modules
from wcsimpl import *
from array import array
import time
import sys

ret = nameAttach("PACK_TEST_2", 1024)
if ret == -1:
	print "%s: name attach error-%s" %(whatsMyError())
	sys.exit(-1)

packChar("A", CHR)
packDouble(3.1415, CHR)
packShort(2, CHR)
packChar("B", CHR)
packLong(24.424242, CHR)
packChar("C", CHR)
packFloat(2.1718, CHR)
packInt(37, CHR)
packString("we are the knights who say nee!", CHR)
	
a = array("c", "012345678")
b = array("h", [0, 1, 2, 3, 4, 5, 6, 7, 8])
c = array("i", [0, 1, 2, 3, 4, 5, 6, 7, 8])
d = array("l", [0, 1, 2, 3, 4, 5, 6, 7, 8])
e = array("f", [1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9])
f = array("d", [.1, .02, .003, .0004, .00005, .000006, 0.0000007])

packCharArray(a, CHR)
packShortArray(b, CHR)
packIntArray(c, CHR)
packLongArray(d, CHR)
packFloatArray(e, CHR)
packDoubleArray(f, CHR)

crossCopy()

print unpackChar(CHR)
print unpackDouble(CHR)
print unpackShort(CHR)
print unpackChar(CHR)
print unpackLong(CHR)
print unpackChar(CHR)
print unpackFloat(CHR)
print unpackInt(CHR)
print unpackString(31, CHR)
	
var1 = " " * 9
g = array("c", var1)
unpackCharArray(g, CHR)
print g
		
var2 = [0] * 9
h = array("h", var2)
unpackShortArray(h, CHR)
print h
	
var3 = [0] * 9
i = array("i", var3)
unpackIntArray(i, CHR)
print i
	
var4 = [0] * 9
j = array("l", var4)
unpackLongArray(j, CHR)
print j

var5 = [0] * 9
k = array("f", var5)
unpackFloatArray(k, CHR)
print k
	
var6 = [0] * 7
l = array("d", var6)
unpackDoubleArray(l, CHR)
print l
		
print
print repr(returnInBuffer())
print "msg size =%d" %(len(returnOutBuffer()))

nameDetach()
