#=============================================
#
#	receiveUtils.tcl
#
#=============================================
# $Log: receiveUtils.tcl,v $
# Revision 1.1.1.1  2005/03/27 11:50:48  paul_c
# Initial import
#
# Revision 1.1  1999/04/08 14:37:53  root
# Initial revision
#
#

#=============================================
#	doReceive - entry point
#=============================================
proc doReceive {} {
global j
global this
global logger
global MASK_MISC
global logMask
set fn doReceive

set buf [Receive]

puts stdout [format "got message #%d" $j]

binary scan $buf i1i1 fromWhom nbytes 
puts stdout [format "fromWhom=%d" $fromWhom]
puts stdout [format "nbytes=%d" $nbytes]
logit $logger $this $fn $MASK_MISC $logMask [format "received %d bytes from %d" $nbytes $fromWhom]
	
binary scan $buf x8a$nbytes msg 
hndlMsg $fromWhom $msg
incr j

};# end doReceive
