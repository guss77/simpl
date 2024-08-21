#=============================================
#
#	cbUtils.tcl
#
#=============================================
# $Log: cbUtils.tcl,v $
# Revision 1.1  2007/07/27 14:16:01  bobfcsoft
# new cvs file
#
#=============================================

#=========================================
#	cb1 - entry point
#=========================================
proc cb1 { newcolor } {
global mySocket
global logger
global this
global MASK_MISC
global logMask

set fn "cb1"

catch {puts stdout [format "%s: ding" $fn]}

vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "newcolor=<%s>" $newcolor ]

showMsg $newcolor

putInfo [format "%s: newcolor <%s>" $fn $newcolor]

};# end cb1

