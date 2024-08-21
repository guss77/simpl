#===========================================
#
#	Send/Receive/Reply  Tcl extensions
#	for TCP/IP virtual circuits
#
# Description:
# This file contains the FC virtual circuit
# extensions to Tcl/Tk for TCP/IP sockets.
# It takes the form of a Tcl/Tk package library.
#
#-----------------------------------------------------------------------
#    Copyright (C) 1999, 2007 FCSoftware Inc. 
#
#    This library is free software; you can redistribute it and/or
#    modify it under the terms of the GNU Lesser General Public
#    License as published by the Free Software Foundation; either
#    version 2.1 of the License, or (at your option) any later version.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#    Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public
#    License along with this library; if not, write to the Free Software
#    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
#    If you discover a bug or add an enhancement contact us on the 
#    SIMPL project mailing list.
#-----------------------------------------------------------------------
#
#==========================================
# $Log: fcsocket.tcl,v $
# Revision 1.6  2011/03/23 18:04:43  bobfcsoft
# added readFromSocket
#
# Revision 1.5  2007/07/24 21:47:20  bobfcsoft
# new contact info
#
# Revision 1.4  2006/04/24 22:06:56  bobfcsoft
# enhanced logging
#
# Revision 1.3  2006/02/07 17:34:48  bobfcsoft
# Tcl/Tk enhancements
#
# Revision 1.2  2006/01/26 02:14:05  bobfcsoft
# more enhancements for Tcl to Windows
#
# Revision 1.1.1.1  2005/03/27 11:50:45  paul_c
# Initial import
#
# Revision 1.9  2002/06/12 18:26:25  root
# added vc_send_ack function
#
# Revision 1.8  2002/01/03 14:46:48  root
# use masks to suppress vc_logit message at tcl end of socket
#
# Revision 1.7  2001/12/05 15:36:52  root
# added homeHost to arg list of attachSocket
#
# Revision 1.6  2001/06/18 15:55:26  root
# enhanced logging
#
# Revision 1.5  2000/10/13 13:40:00  root
# added LGPL
#
# Revision 1.4  2000/04/17 14:59:26  root
# added SEND_NO_REPLY
#
# Revision 1.3  2000/01/24 21:52:40  root
# vc_logit is now non blocking message via socket
# ie. no reply expected
#
# Revision 1.2  1999/12/30 12:10:51  root
# made compatible with cleaned up message structures
#
# Revision 1.1  1999/11/04 15:38:52  root
# Initial revision
#
# Revision 1.2  1999/08/23 11:10:46  root
# fixed to make socket binary
#
# Revision 1.1  1999/06/29 17:33:20  root
# Initial revision
#
#==========================================
package provide fcsocket 1.0

set VC_NAME_ATTACH 	0
set VC_NAME_DETACH 	1
set VC_NAME_LOCATE	2
set VC_SEND_IT		3
set VC_REPLY_IT		4
set VC_RELAY_IT		5
set VC_IS_LOGGER_UP	6	
set VC_LOGIT		7
set VC_SEND_NO_REPLY	8
set VC_ACK              9

set traceflag -1
#set traceflag 1

#=========================================
#
# attachSocket - entry point
#
#=========================================
proc attachSocket {homeHost myPort} {
global traceflag

#set homeHost [getattr originSocketHost]

mytrace $traceflag [format "homeHost=%s port=%d" $homeHost $myPort]

# myPort is in network byte ordering
set thisSocket [socket $homeHost $myPort]
fconfigure $thisSocket -translation binary

#catch {puts stdout [format "homeHost=%s port=%d" $homeHost $myPort]}

return $thisSocket

};#end attachSocket

#========================================
#
# sendToSocket - entry point
#
#========================================
proc sendToSocket {mySocket myMsg} {
set fn sendToSocket
global traceflag

mytrace $traceflag [format "%s: len myMsg=%d" $fn [string length $myMsg]]

puts -nonewline $mySocket $myMsg
flush $mySocket

#
# read the response header
#

set replyMsg [ read $mySocket 4 ]

mytrace $traceflag [ format "%s:got reply len=%d"  $fn [string length $replyMsg]]

binary scan $replyMsg s1s1 token nbytes 

if { $nbytes > 0 } {
	set restMsg [ read $mySocket $nbytes]

#
# Strip off routing field as well
#
	set rbytes [expr $nbytes - 4]
	binary scan $restMsg i1a$rbytes rt dataMsg

mytrace $traceflag [ format "%s: rt=%d rbytes=%d" $fn $rt $rbytes ]

	set replyMsg [binary format "x4i1a$rbytes" $rbytes $dataMsg]

	return $replyMsg
} else {
	return -1
}

};#end sendToSocket

#========================================
#
# replyToSocket - entry point
#
#========================================
proc replyToSocket {mySocket myMsg} {
set fn "replyToSocket"
global traceflag

#catch {puts stdout [format "%s: ding" $fn]}
mytrace $traceflag [format "%s: ding" $fn]

puts -nonewline $mySocket $myMsg
flush $mySocket

mytrace $traceflag [format "%s: done" $fn]
};#end replyToSocket

#========================================
#
# relayToSocket - entry point
#
#========================================
proc relayToSocket {mySocket myMsg} {
set fn relayToSocket

#catch {puts stdout [format "%s: ding" $fn]}

puts -nonewline $mySocket $myMsg
flush $mySocket

};#end relayToSocket

#========================================
#
# readFromSocket - entry point
#
#========================================
proc readFromSocket {mySocket} {
set fn readFromSocket
global traceflag

#
# read the response header
#

set replyMsg [ read $mySocket 4 ]

mytrace $traceflag [ format "%s:got reply len=%d"  $fn [string length $replyMsg]]

binary scan $replyMsg s1s1 token nbytes 

if { $nbytes > 0 } {
	set restMsg [ read $mySocket $nbytes]

#
# Strip off routing field as well
#
	set rbytes [expr $nbytes - 4]
	binary scan $restMsg i1a$rbytes rt dataMsg

mytrace $traceflag [ format "%s: rt=%d rbytes=%d" $fn $rt $rbytes ]

	set replyMsg [binary format "x4i1a$rbytes" $rbytes $dataMsg]

	return $replyMsg
} else {
	return -1
}

};#end readFromSocket

#========================================
#
# vc_name_attach - entry point
#
#========================================
proc vc_name_attach {mySocket myName bufSize} {
global VC_NAME_ATTACH
set fn vc_name_attach
global traceflag

#catch {puts stdout [format "%s: ding" $fn]}
mytrace $traceflag [format "%s: ding" $fn]

set token $VC_NAME_ATTACH
set nbytes [expr 4 + 20 + 4]
set toWhom -1
set myPid -1

set myMsg [binary format "s1s1i1a20i1" $token $nbytes $toWhom $myName $myPid]

set replyMsg [sendToSocket $mySocket $myMsg]
binary scan $replyMsg x8a20i1 myName rc 

#catch {puts stdout [format "%s: done" $fn]}
mytrace $traceflag [format "%s: rc=%d" $fn $rc]

return $rc

};#end vc_name_attach

#========================================
#
# vc_name_detach - entry point
#
#========================================
proc vc_name_detach {mySocket} {
global VC_NAME_DETACH
set fn vc_name_detach
global traceflag

#catch {puts stdout [format "%s: ding" $fn]}
mytrace $traceflag [format "%s: ding" $fn]

set token $VC_NAME_DETACH
set nbytes 0
set myMsg [binary format "s1s1" $token $nbytes ]

#sendToSocket $mySocket $myMsg
relayToSocket $mySocket $myMsg

#catch {puts stdout [format "%s: done" $fn]}
mytrace $traceflag [format "%s: done" $fn]

};#end vc_name_detach

#========================================
#
# vc_name_locate - entry point
#
#========================================
proc vc_name_locate {mySocket thisName} {
global VC_NAME_LOCATE
set fn vc_name_locate
global traceflag

#catch {puts stdout [format "%s: ding thisName=<%s>" $fn $thisName]}
mytrace $traceflag [format "%s: ding thisName=<%s>" $fn $thisName]

set token $VC_NAME_LOCATE
set nbytes [expr 4 + 20 + 4]
set toWhom -1
set rc -1

#catch {puts stdout [format "%s:nbytes=%d" $fn $nbytes]}

set myMsg [binary format "s1s1i1a20i1" $token $nbytes $toWhom $thisName $rc]

#binary scan $myMsg c1c1c1c1c1c1c1c1 ch(0) ch(1) ch(2) ch(3) ch(4) ch(5) ch(6) ch(7)

#puts stdout [format "%s:0x%X-%X-%X-%X-%X-%X-%X-%X" $fn\
#	$ch(0) $ch(1) $ch(2) $ch(3) $ch(4) $ch(5) $ch(6) $ch(7) ]

set replyMsg [sendToSocket $mySocket $myMsg]
#binary scan $replyMsg x12x20i1 rc 
binary scan $replyMsg x28i1 rc 

#catch {puts stdout [format "%s: done rc=%d" $fn $rc]}
mytrace $traceflag [format "%s: done rc=%d" $fn $rc]

return $rc

};#end vc_name_locate

#========================================
#
# vc_send_ack - entry point
#
#========================================
proc vc_send_ack {mySocket} {
global VC_ACK
set fn vc_send_ack
global traceflag

#catch {puts stdout [format "%s: ding" $fn]}
mytrace $traceflag [format "%s: ding" $fn]

set token $VC_ACK
set nbytes 0

set myMsg [binary format "s1s1" $token $nbytes]

relayToSocket $mySocket $myMsg

#catch {puts stdout [format "%s: done" $fn]}
mytrace $traceflag [format "%s: done" $fn]

return 

};#end vc_send_ack

#========================================
#
# find_logger - entry point
#
#========================================
proc find_logger { mySocket loggerName} {
global VC_IS_LOGGER_UP
set fn find_logger
global traceflag

#catch {puts stdout [format "%s: loggerName=<%s>" $fn $loggerName]}
mytrace $traceflag [format "%s: loggerName=<%s>" $fn $loggerName]

set token $VC_IS_LOGGER_UP
set nbytes [expr 4 + 20 + 4]
set toWhom -1
set rc -1

set myMsg [binary format "s1s1i1a20i1" $token $nbytes $toWhom $loggerName $rc]

set rmsg [sendToSocket $mySocket $myMsg]
binary scan $rmsg x8x20i1 myLogger

#catch {puts stdout [ format "%s: myLogger=%d" $fn $myLogger ]} 
mytrace $traceflag [ format "%s: myLogger=%d" $fn $myLogger ]

return $myLogger

};#end find_logger

#========================================
#
# vc_logit - entry point
#
#========================================
proc vc_logit { mySocket myLogger myFile myFn myMask logMask msg } {
global VC_LOGIT
global traceflag

#catch {puts stdout [format "msg=<%s> len=%d" $msg [string length $msg]]}
mytrace $traceflag [format "msg=<%s> len=%d" $msg [string length $msg]]

set checkmask [ expr $myMask & $logMask ]
if { $checkmask != 0 } {

	set token $VC_LOGIT
	set outMsg [binary format "a20a20i1i1a*" $myFile $myFn $myMask $logMask $msg]
	set nbytes [expr 4 + [string length $outMsg]] 
	set myMsg [binary format "s1s1i1a*" $token $nbytes $myLogger $outMsg]

#catch {puts stdout [format "outMsg len=%d total len=%d" $nbytes [string length $myMsg]]}
	mytrace $traceflag [format "outMsg len=%d total len=%d" $nbytes [string length $myMsg]]

#sendToSocket $mySocket $myMsg

	puts -nonewline $mySocket $myMsg
	flush $mySocket
	}

};#end vc_logit

#========================================
#
# mytrace - entry point
#
#========================================
proc mytrace { traceflag msg } {

if { $traceflag != -1 } {

	catch {puts stdout $msg}
	}

};#end mytrace
