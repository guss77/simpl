#=============================================
#
#	bottomPart.tcl
#
#=============================================
# $Log: bottomPart.tcl,v $
# Revision 1.1  2007/07/24 21:09:29  bobfcsoft
# new file
#
#=============================================

#================================================
#	main - entry point
#================================================
set fn main
set logMask 0xff
set loggerName ""

set state flag
foreach arg $argv {
	switch -- $state {
		flag {
			switch -glob -- $arg {
				-N	{ set state name }
				-m	{ set state mask }
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

		logger {
			set loggerName $arg
			set state flag
		}
	};# end switch state
};# end foreach

set myslot [name_attach $myName 2048]
catch {puts stdout [format "myName=<%s> myslot=%d" $myName $myslot]}

if { $loggerName == "" } {
	set logger -1
} else {
	set logger [name_locate "LOGGER"]
}
catch {puts stdout [format "loggerName=<%s>" $loggerName]}

catch {puts stdout [format "logMask=%X" $logMask]}

set myFifo [ format "%s/%s" $env(FIFO_PATH) $myslot]
set recvid [ open $myFifo {RDWR}]
catch {puts stdout [ format "myFifo=%s fd=%d" $myFifo $recvid]}
catch {puts stdout "dropping into wait forever loop"}

logit $logger $this $fn $MASK_MISC $logMask [format "myName=<%s> myslot=%s" $myName $myslot]
logit $logger $this $fn $MASK_MISC $logMask [format "loggerName=<%s>" $loggerName]
logit $logger $this $fn $MASK_MISC $logMask [format "logMask=%X" $logMask]
logit $logger $this $fn $MASK_MISC $logMask [format "myFifo=<%s> fd=<%s>" $myFifo $recvid]

fileevent $recvid readable doReceive
vwait forever

name_detach

puts stdout {done}
#
#================ end bottomPart =======================
