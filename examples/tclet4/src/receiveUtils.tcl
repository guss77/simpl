#=============================================
#
#	receiveUtils.tcl
#
#=============================================
# $Log: receiveUtils.tcl,v $
# Revision 1.1  2007/07/27 14:16:01  bobfcsoft
# new cvs file
#
#=============================================

#=============================================
#	receiveFromSocket - entry point
#=============================================
proc receiveFromSocket {mySocket} {
global j
global this
global MASK_MISC
global logMask
global VC_REPLY_IT
set fn receiveFromSocket

set inMsg [ read $mySocket 4]
binary scan $inMsg s1s1 token nbytes 
set inMsg [ read $mySocket $nbytes]

putInfo [format "got socket message token=%d nbytes=%d" $token $nbytes]
#catch {puts stdout [format "got socket message token=%d nbytes=%d" $token $nbytes]}

hndlSocketMsg $mySocket $token $inMsg

};# end receiveFromSocket

