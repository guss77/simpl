#=============================================
#
#	guiHandlers.tcl
#
#=============================================
# $Log: guiHandlers.tcl,v $
# Revision 1.1  2007/07/26 16:09:43  bobfcsoft
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

label $m.for -text "This is an example of an RPC call "

label $m.by -text "by FCsoftware Inc."

label $m.reply -relief sunken -background yellow
button $m.hitme -text "make RPC call" -command hitMe -state normal


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
$m.hitme config -state normal

}; #end showMsg

#=========================================
#	hitMe - entry point
#=========================================
proc hitMe { } {
global m
global mySocket
global logger
global this
global MASK_MISC
global logMask

set fn "hitMe"

catch {puts stdout [format "%s: ding" $fn]}

set oldcolor [ $m.reply cget -background ]

vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "oldcolor=<%s>" $oldcolor ]

#
# Make the RPC call itself
#
set newcolor [ rpc1 $oldcolor ]

putInfo [format "newcolor <%s>" $newcolor]
vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "newcolor=<%s>" $newcolor ]

showMsg $newcolor 

};# end hitMe

#========================================
#	testThis - entry point
#========================================
proc testThis { } {
global f
global b
global m
global mySocket
global logger
global this
global MASK_MISC
global logMask
global forever
set fn "testThis"

catch {puts stdout [format "%s: ding" $fn]}

vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask "ding"

showMsg "red" 

catch {puts stdout [format "%s: done" $fn]}

};# end testThis

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
