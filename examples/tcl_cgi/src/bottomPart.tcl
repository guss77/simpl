#=============================================
#
#	bottomPart.tcl
#
#=============================================
# $Log: bottomPart.tcl,v $
# Revision 1.1  2007/07/26 15:56:32  bobfcsoft
# new file
#
#=============================================

#================================================
#	main - entry point
#================================================
set fn main

set logMask 0xff
set myName "TCLSEND"
set toName "TCLSIM"
set loggerName "LOGGER"

set myline [read stdin $env(CONTENT_LENGTH)]
foreach {name value} [split $myline &=] {
	lappend cgi($name) $value
	}

puts stdout [format "Content-type: text/html\n"]
puts stdout [format "<body>"]
puts stdout [format "<h3>"]
puts stdout [format "myline=%s<br>" $myline]
puts stdout [format "Message=%s<br>" $cgi(message)]

set myslot [name_attach $myName 2048]
catch {puts stdout [format "myName=%s myslot=%d<br>" $myName $myslot]}

if { $loggerName == "" } {
	set loggerID [binary format "i1i1" -1 -1]
} else {
	set loggerID [name_locate "LOGGER"]
}
binary scan $loggerID i1i1 loggerslot loggerfd
catch {puts stdout [format "loggerName=%s slot=%d<br>" $loggerName $loggerslot]}

catch {puts stdout [format "logMask=%X" $logMask]}

set toID [name_locate $toName]
binary scan $toID i1i1 toslot tofd

catch {puts stdout [format "toName=%s slot=%d fd=%d<br>" $toName $toslot $tofd]}

logit $loggerID $this $fn $MASK_MISC $logMask [format "myName=<%s> myslot=%d" $myName $myslot]
logit $loggerID $this $fn $MASK_MISC $logMask [format "loggerName=<%s> slot=%d" $loggerName $loggerslot]
logit $loggerID $this $fn $MASK_MISC $logMask [format "logMask=%X" $logMask]
logit $loggerID $this $fn $MASK_MISC $logMask [format "toName=<%s> slot=%d fd=%d" $toName $toslot $tofd]

# 
# Message loop
#
set myreply $cgi(message)
for {set i 0} {$i < 10} {incr i} {
	set smsg [binary format "s1a80" $FC_TESTING $myreply]
	set sbytes 24

	logit $loggerID $this $fn $MASK_MISC $logMask [format "sending <%s> to %s at slot=%d" $myreply $toName $toslot]

	catch {puts stdout [format "sending %s to %s at slot %d<br>" $myreply $toName $toslot]}

	set rmsg [Send $toID $smsg $sbytes]
	binary scan $rmsg s1a80 token myreply

	logit $loggerID $this $fn $MASK_MISC $logMask [format "token=%X reply=<%s>" $token $myreply]
	catch {puts stdout [format "myreply=%s<br>" $myreply]}

	if {$myreply == "quit"} {break}
	}

name_detach

puts stdout {done<br>}
puts stdout [format "</h3>"]
puts stdout [format "</body>"]
#
#================ end bottomPart =======================
