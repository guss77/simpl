#=============================================
#
#	rpcUtils.tcl
#
#=============================================
# $Log: rpcUtils.tcl,v $
# Revision 1.1  2007/07/26 16:09:43  bobfcsoft
# new file
#
#=============================================

#=========================================
#	rpc1 - entry point
#=========================================
proc rpc1 { oldcolor } {
global RPC_CALL
global RPC1
global m
global VC_SEND_IT
global mySocket
global logger
global this
global MASK_MISC
global logMask
global toWhom

set fn "rpc1"

catch {puts stdout [format "%s: ding" $fn]}

set mymsg $oldcolor

vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "toWhom=%d msg=<%s>" $toWhom $mymsg ]

set stoken $VC_SEND_IT
set sbytes [expr 4 + 4 + [string length $mymsg]]
set smsg [ binary format "s1s1i1s1s1a*" $stoken $sbytes $toWhom $RPC_CALL $RPC1 $mymsg]
set replyMsg [sendToSocket $mySocket $smsg]

binary scan $replyMsg x4s1s1a* mytoken myfunc myreply

putInfo [format "reply message <%s>" $myreply]
vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "token=%d msg=<%s>" $mytoken $myreply ]

return $myreply

};# end rpc1

