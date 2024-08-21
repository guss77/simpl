#import required modules
import csimpl
import sys

#***** main part of program ****************************************
	
# constructor for simpl class object
nee = csimpl.Simpl("RECEIVER_C", 1024)

print("receiverFd=", nee.whatsMyReceiveFd())

while 1:
	# receive a message
	messageSize, senderId = nee.receive()
	if messageSize == -1:
		# error
		print("receive error-", nee.whatsMyError())
		sys.exit(-1)

	if messageSize < -1:
		# trigger
		print("proxy=",nee.returnProxy(messageSize))
		