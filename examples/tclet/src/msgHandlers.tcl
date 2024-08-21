#=============================================
#
#	msgHandlers.tcl
#
#=============================================
# $Log: msgHandlers.tcl,v $
# Revision 1.1  2007/07/26 15:59:29  bobfcsoft
# new file
#
#=============================================


#=============================================
# 	hndlSocketMsg - entry point
#
#	Note: can only use logit AFTER the 
#	replyToSocket as they use the same
#	port.
#=============================================
proc hndlSocketMsg {fromSocket thisToken msg} {
global MY_TEST
global VC_REPLY_IT
global VC_RELAY_IT
global mySocket
global this
global logger
global MASK_MISC
global logMask
global pendingEventFrom
set fn "hndlSocketMsg"

catch {puts stdout [format "%s: ding" $fn]}

if { $thisToken == $VC_RELAY_IT } {
	binary scan $msg i1s1a* fromWhom token text
} else {
	putInfo [format "unknown token=%d (0x%X)" $thisToken $thisToken]
}

if { $token == $MY_TEST } {
	set pendingEventFrom $fromWhom

	catch {puts stdout [format "token=MY_TEST(%d) msg=<%s> from %d" $token $text $fromWhom ]}
	vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "token=MY_TEST msg=<%s> from %d" $text $fromWhom ]

	showMsg $text
} else {
	putInfo [format "unknown subtoken=%d (0x%X)" $token $token]
	vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "unknown token=%d" $token]
}

};#end hndlSocketMsg

