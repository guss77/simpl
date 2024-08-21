#import required modules
import csimpl
import sys

#***** main part of program ****************************************
	
# constructor for simpl class object
nee = csimpl.Simpl("SENDER", 1024)

# name locate receiver program
id = nee.nameLocate("RECEIVER_C")
if id == -1:
	print("name locate error-", nee.whatsMyError())
	sys.exit(-1)

# send the message to the receiver program
ret = nee.trigger(id, 42)
if ret == -1:
	print("send error-", nee.whatsMyError())
	sys.exit(-1)
