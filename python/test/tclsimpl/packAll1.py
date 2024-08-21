"""
packAll1: this program tests the packing/unpacking methods attached to a class
instance of simpl. The C variable types are somewhat unorganized on purpose but
all are used at least once.

This program also serves as a good example of the pack and unpack a message.

Python 2 and 3 compatible.
"""

#import required modules
import tclsimpl
from array import array

nee = tclsimpl.Simpl("50001:localhost:PACK_ALL")

# create an outgoing message
a = array("h", [0, 1, 2, 3, 4, 5, 6, 7, 8])
b = array("i", [0, 1, 2, 3, 4, 5, 6, 7, 8])
c = array("l", [0, 1, 2, 3, 4, 5, 6, 7, 8])
d = array("f", [1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9])
e = array("d", [.1, .02, .003, .0004, .00005, .000006, 0.0000007])

# pack the outgoing msg buffer
nee.packMsg(nee.BIN, "cdhclcfisHILFD", "A", 3.1415, 2, "B", 42424242, "C",
2.1718, 37, "we are the knights who say nee!", a, b, c, d, e)

# copy the contents of the out msg buffer to the in msg buffer for comparison
# simulates a send/receive/reply 
nee.crossCopy()

# unpack the incoming msg buffer
f,g,h,i,j,k,l,m,n,o,p,q,r,s = nee.unpackMsg(nee.BIN, "cdhclcfi31s9H9I9L9F7D")

# print the in msg contents: should be what was originally in the out msg
print(f)
print(g)
print(h)
print(i)
print(j)
print(k)
print(l)
print(m)
print(n)
print(o)
print(p)
print(q)
print(r)
print(s)
print("\n")
print(repr(nee.returnInBuffer()))
print("msg size=", len(nee.returnOutBuffer()))
