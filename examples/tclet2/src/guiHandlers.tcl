#=============================================
#
#	guiHandlers.tcl
#
#=============================================
# $Log: guiHandlers.tcl,v $
# Revision 1.1  2007/07/26 16:01:52  bobfcsoft
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

label $m.for -text "This is an example of a sender type tclet."

label $m.by -text "by FCsoftware Inc."

entry $m.towhom -relief sunken -background red
button $m.locate -text "locate" -command locateRecv -state normal

entry $m.outgoing -text "outgoing message goes here" -relief sunken -background red
button $m.hitme -text "sendMe" -command hitMe -state disabled

label $m.reply -relief sunken -background yellow

place $m.for -x 10 -y 50
place $m.by -x 10 -y 80
place $m.towhom -x 10 -y 110
place $m.locate -x 170 -y 105
place $m.outgoing -x 10 -y 140
place $m.hitme -x 170 -y 135
place $m.reply -x 10 -y 170

pack $m -fill both -expand true

putInfo [format "%s: done" $fn]

} ;# end renderMain

#=========================================
#	showMsg - entry point
#=========================================
proc showMsg { msgText } {
global m
set fn "showMsg"

$m.reply config -text $msgText -background green
$m.hitme config -state normal

}; #end showMsg


#=========================================
#	locateRecv - entry point
#=========================================
proc locateRecv { } {
global MY_TEST
global m
global VC_NAME_LOCATE
global VC_REPLY_IT
global mySocket
global logger
global this
global MASK_MISC
global logMask
global pendingEventFrom
global toWhom

set fn "locate"

catch {puts stdout [format "%s: ding" $fn]}

set toName [ $m.towhom get ]

putInfo [format "%s: locating receiver %s" $fn $toName]

set toWhom [vc_name_locate $mySocket $toName]

putInfo [format "%s: found receiver <%s> at id=%d" $fn $toName $toWhom]
vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "toName=%s id=%d" $toName $toWhom]

$m.locate config -state disabled
$m.hitme config -state normal

};# end locateRecv

#=========================================
#	hitMe - entry point
#=========================================
proc hitMe { } {
global MY_TEST
global m
global VC_REPLY_IT
global VC_SEND_IT
global mySocket
global logger
global this
global MASK_MISC
global logMask
global pendingEventFrom
global toWhom

set fn "hitMe"

catch {puts stdout [format "%s: ding" $fn]}

set mymsg [ $m.outgoing get ]
#$m.reply delete 0 end

vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "toWhom=%d msg=<%s>" $toWhom $mymsg ]

set stoken $VC_SEND_IT
set sbytes [expr 4 + 2 + [string length $mymsg]]
set smsg [ binary format "s1s1i1s1a*" $stoken $sbytes $toWhom $MY_TEST $mymsg]
set replyMsg [sendToSocket $mySocket $smsg]

binary scan $replyMsg x4s1a* mytoken myreply

putInfo [format "reply message <%s>" $myreply]
vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "token=%d msg=<%s>" $mytoken $myreply ]

showMsg $myreply

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
