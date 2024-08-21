#!/usr/bin/wish 
#=============================================
# 	tclet example
#		sender
#=============================================
set this "tclet4.tcl"

package require fcsocket

policy home

set f [frame .myArea -borderwidth 5 -width 400 -height 250]
set m [frame $f.main -width 400 -height 200]
set b [frame .bottomBar]

set mySocket [ attachSocket 16415 ]
catch {puts stdout [format "socket=%s" $mySocket]}

fileevent $mySocket readable { receiveFromSocket $mySocket }

