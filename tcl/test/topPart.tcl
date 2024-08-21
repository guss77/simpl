#!/usr/bin/tclsh 
#=============================================
# 	test script for Meterview messaging
#=============================================
set this "bob5.tcl"

package require Fctclx
set myslot [name_attach "BOBTCL" 2048]

set logger [name_locate "LOGGER"]
puts stdout [format "logger=%d" $logger]

set myFifo [ format "%s/%s" $env(FIFO_PATH) $myslot ]
puts stdout [ format "myFifo=%s" $myFifo ]

set recvid [ open $myFifo {RDWR}]
fileevent $recvid readable doReceive
