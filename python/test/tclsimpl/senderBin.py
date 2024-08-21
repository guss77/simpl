#import required modules
import tclsimpl
from array import array
import sys

def constructMsg(nee):
	# create arrays of all supported types for an outgoing message
	a = array("h", [0, 1, 2, 3, 4, 5, 6, 7, 8])
	b = array("i", [0, 1, 2, 3, 4, 5, 6, 7, 8])
	c = array("l", [0, 1, 2, 3, 4, 5, 6, 7, 8])
	d = array("f", [1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9])
	e = array("d", [.1, .02, .003, .0004, .00005, .000006, 0.0000007])

	# pack above arrays and other C data types into the outgoing message buffer
	nee.packMsg(nee.BIN, "cdhclcfisHILFD", "A", 3.1415, 2, "B", 42424242, "C",\
				2.1718, 37, "we are the knights who say nee!", a, b, c, d, e)

def deconstructMsg(nee):
	# extract the incoming message
	f,g,h,i,j,k,l,m,n,o,p,q,r,s = nee.unpackMsg(nee.BIN,\
										"cdhclcfi31s9H9I9L9F7D")

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

#***** main part of program ****************************************
	
# create a simpl instance
nee = tclsimpl.Simpl("50000:localhost:PACK_ALL")
	
# name locate receiver program
nid = nee.nameLocate("RECEIVER_B")
if nid == -1:
	print(myName, ": name locate error-", nee.whatsMyError())
	sys.exit(-1)

# build outgoing message
constructMsg(nee)

# send the message to the receiver program
ret = nee.send(nid)
if ret == -1:
	print(myName, ": send error-", nee.whatsMyError())
	sys.exit(-1)

	# examine the return message
deconstructMsg(nee)
