#import required modules
import wcsimpl
from array import array
import time
import sys

nee = wcsimpl.Simpl()

ret = nee.nameAttach("PACK_TEST_1", 1024)
if ret == -1:
	print "%s: name attach error-%s" %(whatsMyError())
	sys.exit(-1)

nee.packChar("A", nee.BIN)
nee.packDouble(3.1415, nee.BIN)
nee.packShort(2, nee.BIN)
nee.packChar("B", nee.BIN)
nee.packLong(24.424242, nee.BIN)
nee.packChar("C", nee.BIN)
nee.packFloat(2.1718, nee.BIN)
nee.packInt(37, nee.BIN)
nee.packString("we are the knights who say nee!", nee.BIN)
	
a = array("c", "012345678")
b = array("h", [0, 1, 2, 3, 4, 5, 6, 7, 8])
c = array("i", [0, 1, 2, 3, 4, 5, 6, 7, 8])
d = array("l", [0, 1, 2, 3, 4, 5, 6, 7, 8])
e = array("f", [1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9])
f = array("d", [.1, .02, .003, .0004, .00005, .000006, 0.0000007])

nee.packCharArray(a, nee.BIN)
nee.packShortArray(b, nee.BIN)
nee.packIntArray(c, nee.BIN)
nee.packLongArray(d, nee.BIN)
nee.packFloatArray(e, nee.BIN)
nee.packDoubleArray(f, nee.BIN)

nee.crossCopy()

print nee.unpackChar(nee.BIN)
print nee.unpackDouble(nee.BIN)
print nee.unpackShort(nee.BIN)
print nee.unpackChar(nee.BIN)
print nee.unpackLong(nee.BIN)
print nee.unpackChar(nee.BIN)
print nee.unpackFloat(nee.BIN)
print nee.unpackInt(nee.BIN)
print nee.unpackString(31, nee.BIN)
	
var1 = " " * 9
g = array("c", var1)
nee.unpackCharArray(g, nee.BIN)
print g
		
var2 = [0] * 9
h = array("h", var2)
nee.unpackShortArray(h, nee.BIN)
print h
	
var3 = [0] * 9
i = array("i", var3)
nee.unpackIntArray(i, nee.BIN)
print i
	
var4 = [0] * 9
j = array("l", var4)
nee.unpackLongArray(j, nee.BIN)
print j

var5 = [0] * 9
k = array("f", var5)
nee.unpackFloatArray(k, nee.BIN)
print k
	
var6 = [0] * 7
l = array("d", var6)
nee.unpackDoubleArray(l, nee.BIN)
print l
		
print
print repr(nee.returnInBuffer())
print "msg size =%d" %(len(nee.returnOutBuffer()))

nee.nameDetach()
