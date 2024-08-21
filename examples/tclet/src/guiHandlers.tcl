#=============================================
#
#	guiHandlers.tcl
#
#=============================================
# $Log: guiHandlers.tcl,v $
# Revision 1.1  2007/07/26 15:59:29  bobfcsoft
# new file
#
#=============================================

#=============================================
#	renderMain - entry point
#=============================================
proc renderMain { } {

global m
global b_c
set fn "renderMain"

label $m.for -text "This application was created for TLUG presentation"

label $m.by -text "by FCsoftware Inc."

label $m.incoming -text "incoming message goes here" -relief sunken -background red
entry $m.reply -relief sunken -background yellow

place $m.for -x 10 -y 50
place $m.by -x 10 -y 80
place $m.incoming -x 10 -y 140
place $m.reply -x 10 -y 170

button $m.hitme -text "reply" -command hitMe -state disabled
place $m.hitme -x 170 -y 165

pack $m -fill both -expand true

putInfo [format "%s: done" $fn]

} ;# end renderMain

#=========================================
#	showMsg - entry point
#=========================================
proc showMsg { msgText } {
global m
set fn "showMsg"

$m.incoming config -text $msgText -background green
$m.hitme config -state normal

}; #end showMsg


#=========================================
#	hitMe - entry point
#=========================================
proc hitMe { } {
global MY_TEST
global m
global VC_REPLY_IT
global mySocket
global logger
global this
global MASK_MISC
global logMask
global pendingEventFrom

set fn "hitMe"

catch {puts stdout [format "%s: ding" $fn]}

set myreply [ $m.reply get ]
#$m.reply select range 0 end
$m.reply delete 0 end


vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "toWhom=%d reply=<%s>" $pendingEventFrom $myreply ]

if { $pendingEventFrom != -1 } {
	set rtoken $VC_REPLY_IT
	set rtoWhom $pendingEventFrom
	set rbytes [expr 4 + 2+ [string length $myreply]]
	set rmsg [ binary format "s1s1i1s1a*" $rtoken $rbytes $rtoWhom $MY_TEST $myreply]
	replyToSocket $mySocket $rmsg

#binary scan $rmsg c1c1c1c1c1c1c1c1 my1 my2 my3 my4 my5 my6 my7 my8
#vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "msg=%02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X" $my1 $my2 $my3 $my4 $my5 $my6 $my7 $my8 ]

	vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "sent ACK back to %d" $pendingEventFrom ]

	putInfo [format "message to %d ACK'd as <%s>" $pendingEventFrom $myreply]

	set pendingEventFrom -1
	$m.incoming config -text "incoming message goes here" -background red
	}

$m.hitme config -state disabled

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
