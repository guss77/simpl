#=============================================
#
#	bottomPart.tcl
#
#=============================================
# $Log: bottomPart.tcl,v $
# Revision 1.1  2007/07/24 21:04:05  bobfcsoft
# new file
#
#=============================================

#================================================
#	main - entry point
#================================================
set fn main
set logMask 0xff
set toName ""
set loggerName ""

set state flag
foreach arg $argv {
	switch -- $state {
		flag {
			switch -glob -- $arg {
				-N	{ set state name }
				-m	{ set state mask }
				-r      { set state receiver }
				-l	{ set state logger }
				default { error "unknown flag $arg"}
			}
		}
		
		name {
			set myName $arg
			set state flag
		}

		mask {
			set logMask $arg
			set state flag
		}

		receiver {
			set toName $arg
			set state flag
		}

		logger {
			set loggerName $arg
			set state flag
		}
	};# end switch state
};# end foreach

set myslot [name_attach $myName 2048]
catch {puts stdout [format "myName=<%s> myslot=%s" $myName $myslot]}

if { $loggerName == "" } {
	set loggerID -1
} else {
	set loggerID [name_locate "LOGGER"]
}
catch {puts stdout [format "loggerName=<%s>" $loggerName ] }

catch {puts stdout [format "logMask=%X" $logMask]}

set toID [name_locate $toName]

catch {puts stdout [format "toName=<%s> slot=%d" $toName $toID]}

logit $loggerID $this $fn $MASK_MISC $logMask [format "myName=<%s> myslot=%s" $myName $myslot]
logit $loggerID $this $fn $MASK_MISC $logMask [format "loggerName=<%s>" $loggerName ]
logit $loggerID $this $fn $MASK_MISC $logMask [format "logMask=%X" $logMask]
logit $loggerID $this $fn $MASK_MISC $logMask [format "toName=<%s> slot=%s" $toName $toID]

# 
# Message loop
#
set myreply "abc"
for {set i 0} {$i < 10} {incr i} {
	set smsg [binary format "s1a80" $FC_TESTING $myreply]
	set sbytes 24

	logit $loggerID $this $fn $MASK_MISC $logMask [format "sending <%s> to %s at slot=%d" $myreply $toName $toID]

	catch {puts stdout [format "sending <%s> to %s at slot %d" $myreply $toName $toslot]}

	set rmsg [Send $toID $smsg $sbytes]
	binary scan $rmsg s1a80 token myreply

	logit $loggerID $this $fn $MASK_MISC $logMask [format "token=%X reply=<%s>" $token $myreply]
	catch {puts stdout [format "myreply=<%s>" $myreply]}

	if {$myreply == "quit"} {break}
	}

name_detach

puts stdout {done}
#
#================ end bottomPart =======================
