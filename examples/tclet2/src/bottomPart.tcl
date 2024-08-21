#================================================
#
#	bottomPart.tcl
#
#================================================
# $Log: bottomPart.tcl,v $
# Revision 1.1  2007/07/26 16:01:52  bobfcsoft
# new file
#
#================================================

#================================================
#	main - entry point
#================================================
set fn "main"

set myName ""  ;# we want to use the surrogate name
set loggerName "LOGGER"
set logMask 1
set state flag

# read the command line args
# NOTE: use lower case tags here but
#       use upper case tags in html file
catch {	set loggerName $embed_args(-l)}
catch {	set logMask $embed_args(-m)}

set attachReply [vc_name_attach $mySocket $myName 2048]
binary scan $attachReply x4a20i1i1 myName myPid myslot
catch {puts stdout [format "myName=%s myPid=%d slot=%d" $myName $myPid $myslot]}

set logger [find_logger $mySocket $loggerName]
catch {puts stdout [format "loggerName=<%s> logger_fd=%d" $loggerName $logger]}

vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "logger name=<%s> fd=%d mask=%d" $loggerName $logger $logMask]
vc_logit $mySocket $logger $this $fn $MASK_MISC $logMask [format "myName=<%s> myPid=%d myslot=%d" $myName $myPid $myslot]

button $b.quit -text "quit" -command quitThis
pack $b.quit -side right

label $b.info -width 50 -relief groove -borderwidth 5 -justify left
pack $b.info -side left

pack $b -side bottom -fill x

renderMain

pack $f -side top -expand true -fill both

putInfo [format "myName=<%s> myPid=%d myslot=%d" $myName $myPid $myslot]
catch {puts stdout "dropping into wait forever loop"}
vwait forever

catch {puts stdout [format "%s: done" $fn]}
exit
# end main
