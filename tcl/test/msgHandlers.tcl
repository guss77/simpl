#=============================================
#
#	msgHandlers.tcl
#
#=============================================
# $Log: msgHandlers.tcl,v $
# Revision 1.1.1.1  2005/03/27 11:50:48  paul_c
# Initial import
#
# Revision 1.2  1999/09/09 14:15:17  root
# *** empty log message ***
#
# Revision 1.1  1999/04/08 14:37:25  root
# Initial revision
#
#


#=============================================
# 	hndlMsg - entry point
#=============================================
proc hndlMsg {fromWhom msg} {
global reply
global DB_RESET
global TEST_PROXY
global FC_TESTING
global this
global logger
global MASK_MISC
global logMask
set fn hndlMsg

binary scan $msg s1 token

if { $token == $FC_TESTING } {
	set reply [binary format "s1" $FC_TESTING]
	Reply $fromWhom $reply 2
	hndlFCtesting $fromWhom $msg
	return
}

};#end hndlMsg

#=============================================
#  	hndlFCtesting - entry point
#=============================================
proc hndlFCtesting { fromWhom msg } {
global DB_RESET
global TEST_PROXY
global myreply
global this
global logger
global MASK_MISC
global logMask
set fn hndlFCtesting

logit $logger $this $fn $MASK_MISC $logMask "ding"

binary scan $msg s1s1 token subtoken

logit $logger $this $fn $MASK_MISC $logMask [format "subtoken=%d fromWhom=%d" $subtoken $fromWhom]

if { $subtoken == $DB_RESET } {
	puts stdout [format "token=DB_RESET(%d)" $subtoken]
	logit $logger $this $fn $MASK_MISC $logMask "token=DB_RESET"
} else {
if { $subtoken == $TEST_PROXY } {
	binary scan $msg s1s1s1 token subtoken myproxy
	puts stdout [format "token=TEST_PROXY(%d) myproxy=%d" $subtoken $myproxy]
	logit $logger $this $fn $MASK_MISC $logMask [format "token=TEST_PROXY myproxy=%d" $myproxy]

	set toTrigger [name_locate "FCTESTER"]
	triggerProxy $toTrigger $myproxy
} else {
	puts stdout [format "token=%d unsupported in test mode" $subtoken]
}
}

};#end hndlFCtesting
