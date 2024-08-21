#=============================================
#
#	msgHandlers.tcl
#
#=============================================
# $Log: msgHandlers.tcl,v $
# Revision 1.1  2007/07/24 21:09:29  bobfcsoft
# new file
#
#=============================================

#=============================================
# 	hndlMsg - entry point
#=============================================
proc hndlMsg {fromWhom msg} {
global forever
global reply
global FC_QUIT
global FC_TESTING
global this
global logger
global MASK_MISC
global logMask
set fn hndlMsg

catch {puts stdout [format "%s:ding" $fn]}

binary scan $msg s1 token

logit $logger $this $fn $MASK_MISC $logMask [format "token=0x%X fromWhom=%d" $token $fromWhom]

set reply [binary format "s1" $FC_TESTING]
Reply $fromWhom $reply 2

if { $token == $FC_QUIT } {
	catch {puts stdout [format "token=FC_QUIT(0x%X)" $token]}
	logit $logger $this $fn $MASK_MISC $logMask [format "token=FC_QUIT(0x%X)" $token]
	set forever 1
} else {
if { $token == $FC_TESTING } {
	binary scan $msg s1a80 token mytext
	catch {puts stdout [format "token=FC_TESTING(0x%X) text=<%s>" $token $mytext]}
	logit $logger $this $fn $MASK_MISC $logMask [format "token=FC_TESTING(0x%X) text=<%s>" $token $mytext]

} else {
	puts stdout [format "token=0x%X unsupported" $token]
}
}
catch {puts stdout [format "%s:done" $fn]}
};#end hndlMsg
#
#======================== end msgHandlers =====================
#
