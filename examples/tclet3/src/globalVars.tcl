#=============================================
#
#	globalVars.tcl
#
#=============================================
# $Log: globalVars.tcl,v $
# Revision 1.1  2007/07/26 16:09:43  bobfcsoft
# new file
#
#=============================================

set MASK_MISC		1
set MASK_IO		2

set VC_NAME_ATTACH 	0
set VC_NAME_DETACH 	1
set VC_NAME_LOCATE	2
set VC_SEND_IT		3
set VC_REPLY_IT		4
set VC_RELAY_IT		5
set VC_IS_LOGGER_UP	6
set VC_LOGIT		7

# Note: the ffff in front is needed because
# Tcl does not appear to handle 16 bit numbers
# > 0x8000 correctly in binary scan
#set MY_TEST		0xfffffc01

set FC_TESTING		99
set FC_QUIT		0
set FC_NAME_LOCATE	1	
set FC_HIT_ME		2

set RPC_CALL	0xfffffc01
set RPC1	0

set j 0
set pendingEventFrom	-1

