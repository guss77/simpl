#=============================================
#
#	msgHandlers.tcl
#
#=============================================
# $Log: msgHandlers.tcl,v $
# Revision 1.1  2007/07/27 14:16:01  bobfcsoft
# new cvs file
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
global CALL_BACK_WHAT_YA_GOT
global CALL_BACK_RESPONSE
global VC_REPLY_IT
global VC_RELAY_IT
global m
global mySocket
global this
global logger
global MASK_MISC
global logMask
global pendingEventFrom
set fn "hndlSocketMsg"

catch {puts stdout [format "%s: ding" $fn]}

if { $thisToken == $VC_RELAY_IT } {
	binary scan $msg i1s1a* fromWhom token restofmsg
} else {
	putInfo [format "unknown token=%d (0x%X)" $thisToken $thisToken]
	vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "unknown token=%d (0x%X)" $thisToken $thisToken ]
}

if { $token == $CALL_BACK_WHAT_YA_GOT } {
	set pendingEventFrom $fromWhom
	$m.hitme config -state normal

	catch {puts stdout [format "token=WHAT_YA_GOT(%d) from %d" $token $fromWhom ]}
	vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "token=WHAT_YA_GOT from %d" $fromWhom ]

} else {

if { $token == $CALL_BACK_RESPONSE } {
	set pendingEventFrom $fromWhom
	$m.hitme config -state normal

	binary scan $restofmsg s1a20a* funcID cbfunc newcolor

	catch {puts stdout [format "token=CALL_BACK(%d) msg=<%s> from %d" $token $text $fromWhom ]}
	vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "token=CALL_BACK_RESPONSE newcolor=<%s> cb=<%s> from %d" $newcolor $cbfunc $fromWhom ]

#	showMsg $newcolor
	$cbfunc $newcolor
} else {
	putInfo [format "unknown subtoken=%d (0x%X)" $token $token]
	vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "unknown token=%d" $token]
}
}

};#end hndlSocketMsg

