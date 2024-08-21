#=============================================
#
#	globalVars.tcl
#
#=============================================
# $Log: globalVars.tcl,v $
# Revision 1.1  2007/07/27 14:16:01  bobfcsoft
# new cvs file
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

set FC_TESTING		99
set FC_QUIT		0
set FC_NAME_LOCATE	1	
set FC_HIT_ME		2

set RPC_CALL			0xfffffc01
set CALL_BACK_WHAT_YA_GOT	0xfffffc02
set CALL_BACK_REQUEST		0xfffffc03
set CALL_BACK_RESPONSE		0xfffffc04
set CB1	0

set j 0
set pendingEventFrom	-1

