#=============================================
#
#	guiHandlers.tcl
#
#=============================================
# $Log: guiHandlers.tcl,v $
# Revision 1.1.1.1  2005/03/27 11:50:48  paul_c
# Initial import
#
# Revision 1.1  1999/04/08 14:37:16  root
# Initial revision
#
#

#=============================================
#  	hndlRefresh - entry point
#=============================================
proc hndlRefresh { msg } {
global this
global logger
global MASK_MISC
global logMask
set fn hndlRefresh

logit $logger $this $fn $MASK_MISC $logMask "ding"

binary scan $msg s1a100a100 token answerRec setupRec

logit $logger $this $fn $MASK_MISC $logMask [format "answerRec=<%s>" $answerRec]
logit $logger $this $fn $MASK_MISC $logMask [format "setupRec=<%s>" $setupRec]

#
# This is where the Tk code would display the output message
# in the output window
#

};#end hndlRefresh
