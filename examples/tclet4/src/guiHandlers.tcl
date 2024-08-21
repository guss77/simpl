#=============================================
#
#	guiHandlers.tcl
#
#=============================================
# $Log: guiHandlers.tcl,v $
# Revision 1.1  2007/07/27 14:16:01  bobfcsoft
# new cvs file
#
#=============================================

#=============================================
#	renderMain - entry point
#=============================================
proc renderMain { } {

global m
global b_c
set fn "renderMain"

label $m.for -text "This is an example of a call back"

label $m.by -text "by FCsoftware Inc."

label $m.reply -relief sunken -background yellow
button $m.hitme -text "make call back" -command hitMe -state disabled

place $m.for -x 10 -y 50
place $m.by -x 10 -y 80
place $m.reply -x 10 -y 140
place $m.hitme -x 170 -y 135

pack $m -fill both -expand true

putInfo [format "%s: done" $fn]

} ;# end renderMain

#=========================================
#	showMsg - entry point
#=========================================
proc showMsg { newcolor} {
global m
set fn "showMsg"

$m.reply config -text $newcolor -background $newcolor

}; #end showMsg

#=========================================
#	hitMe - entry point
#=========================================
proc hitMe { } {
global VC_REPLY_IT
global CB1
global pendingEventFrom
global CALL_BACK_REQUEST
global m
global mySocket
global logger
global this
global MASK_MISC
global logMask

set fn "hitMe"

catch {puts stdout [format "%s: ding" $fn]}

set oldcolor [ $m.reply cget -background ]
set replyMsg [ format "%s\0" $oldcolor ]

vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "fromWhom=%d oldcolor=<%s>" $pendingEventFrom $oldcolor ]

if { $pendingEventFrom != -1 } {
	set rtoken $VC_REPLY_IT
	set rtoWhom $pendingEventFrom
	set rbytes [expr 4 + 4 + 20 + [string length $replyMsg]]
	set rmsg [ binary format "s1s1i1s1s1a20a*" $rtoken $rbytes $rtoWhom $CALL_BACK_REQUEST $CB1 "cb1" $replyMsg]
	replyToSocket $mySocket $rmsg

	$m.hitme config -state disabled
	set pendingEventFrom -1

	vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "%d bytes to %d" $rbytes $rtoWhom ]
	}
};# end hitMe

#========================================
#	quitThis - entry point
#========================================
proc quitThis { } {
global f
global b
global m
global mySocket
global logger
global this
global MASK_MISC
global logMask
global forever
set fn "quitThis"

catch {puts stdout [format "%s: ding" $fn]}

vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask "closing down"

vc_name_detach $mySocket
close $mySocket

catch {puts stdout [format "%s: done" $fn]}

set forever 1

};# end quitThis

#========================================
#	putInfo - entry point
#========================================
proc putInfo { infoText } {
global b

$b.info config -justify left -text $infoText -background lightblue
catch {puts stdout $infoText}

}; #end putInfo
