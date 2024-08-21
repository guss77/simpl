#=============================================
#
#	bottomPart.tcl
#
#=============================================
# $Log: bottomPart.tcl,v $
# Revision 1.1.1.1  2005/03/27 11:50:48  paul_c
# Initial import
#
# Revision 1.1  1999/04/08 14:36:23  root
# Initial revision
#
#

#================================================
#	main - entry point
#================================================
set fn main

set state flag
foreach arg $argv {
	switch -- $state {
		flag {
			switch -glob -- $arg {
				-m	{ set state mask }
				default { error "unknown flag $arg"}
			}
		}
		
		mask {
			set logMask $arg
			set state flag
		}
	};# end switch state
};# end foreach

puts stdout [format "myslot=%d" $myslot]
puts stdout [format "logMask=%X" $logMask]
puts stdout {dropping into wait forever loop}
logit $logger $this $fn $MASK_MISC $logMask [format "myslot=%d" $myslot]

vwait forever

puts stdout {done}
