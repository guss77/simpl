"""
packAll2: this program tests the packing/unpacking methods attached to a class
instance of simpl. The C variable types are somewhat unorganized on purpose but
all are used at least once.

This program also serves as a good example of the pack and unpack a message.

Python 2 and 3 compatible.
"""

#import required modules
import tclsimpl
from array import array

nee = tclsimpl.Simpl("50001:localhost:PACK_ALL")

# create arrays of all supported types for an outgoing message
b = array("h", [0, 1, 2, 3, 4, 5, 6, 7, 8])
c = array("i", [0, 1, 2, 3, 4, 5, 6, 7, 8])
d = array("l", [0, 1, 2, 3, 4, 5, 6, 7, 8])
e = array("f", [1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9])
f = array("d", [.1, .02, .003, .0004, .00005, .000006, 0.0000007])

# pack the above arrays and other C data types into the outgoing message buffer
nee.packChar("A", nee.BIN)
nee.packDouble(3.1415, nee.BIN)
nee.packShort(2, nee.BIN)
nee.packChar("B", nee.BIN)
nee.packLong(42424242, nee.BIN)
nee.packByte(False, nee.BIN)
nee.packFloat(2.1718, nee.BIN)
nee.packInt(37, nee.BIN)
nee.packString("we are the knights who say nee!", nee.BIN)
nee.packShortArray(b, nee.BIN)
nee.packIntArray(c, nee.BIN)
nee.packLongArray(d, nee.BIN)
nee.packFloatArray(e, nee.BIN)
nee.packDoubleArray(f, nee.BIN)

# copy the outgoing msg buffer to the incoming msg  buffer for comparison
nee.crossCopy()

# extract and print the contents of the incoming message
print(nee.unpackChar(nee.BIN))
print(nee.unpackDouble(nee.BIN))
print(nee.unpackShort(nee.BIN))
print(nee.unpackChar(nee.BIN))
print(nee.unpackLong(nee.BIN))
print(nee.unpackByte(nee.BIN))
print(nee.unpackFloat(nee.BIN))
print(nee.unpackInt(nee.BIN))
print(nee.unpackString(31, nee.BIN))
	
var2 = [0] * 9
h = array("h", var2)
nee.unpackShortArray(h, nee.BIN)
print(h)
	
var3 = [0] * 9
i = array("i", var3)
nee.unpackIntArray(i, nee.BIN)
print(i)
	
var4 = [0] * 9
j = array("l", var4)
nee.unpackLongArray(j, nee.BIN)
print(j)

var5 = [0] * 9
k = array("f", var5)
nee.unpackFloatArray(k, nee.BIN)
print(k)
	
var6 = [0] * 7
l = array("d", var6)
nee.unpackDoubleArray(l, nee.BIN)
print(l)

print("\n")
print(repr(nee.returnInBuffer()))
print("msg size=", len(nee.returnOutBuffer()))
