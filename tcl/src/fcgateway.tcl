#===========================================
#
#	Send/Receive/Reply  Tcl extensions
#	for TCP/IP virtual circuits
#
# Description:
# This file contains the bridge library to allow
# Tcl/Tk Send/Receive/Reply API to work via the
# fcsocket library protocol
#
#-----------------------------------------------------------------------
#    Copyright (C) 2006 FCSoftware Inc. 
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
# $Log: fcgateway.tcl,v $
# Revision 1.5  2011/03/23 18:02:31  bobfcsoft
# added postMsg, readReply to allow split sender with event loop
#
# Revision 1.4  2009/07/15 11:46:34  bobfcsoft
# added SIMPL name to rc for name_attach
#
# Revision 1.3  2007/07/24 21:47:20  bobfcsoft
# new contact info
#
# Revision 1.2  2006/02/07 17:34:48  bobfcsoft
# Tcl/Tk enhancements
#
# Revision 1.1  2006/01/26 02:14:05  bobfcsoft
# more enhancements for Tcl to Windows
#
#
#==========================================
package provide fcgateway 1.0
package require fcsocket

set traceflag  -1
#set traceflag  1

global gatewayAddr
global gatewayPort
global gatewaySocket
global waitingForReply

#
# option to have this a separate channel
#
global senderSocket


#=========================================================
#  name_attach - entry point
#=========================================================
proc name_attach { myName } \
{
set fn name_attach
global gatewaySocket
global senderSocket
global gatewayAddr
global gatewayPort
global waitingForReply
global traceflag

mytrace $traceflag [format "%s:%s" $fn $myName]

set waitingForReply 0

set gatewaySocket [attachSocket $gatewayAddr $gatewayPort]
set senderSocket $gatewaySocket

mytrace $traceflag [format "%s:gatewaySocket=%s" $fn $gatewaySocket]

set rc [vc_name_attach $gatewaySocket $myName 0]

mytrace $traceflag [format "%s:rc=%d" $fn $rc]

return $myName.$rc

};# end name_attach

#=========================================================
#  attachSender - entry point
#=========================================================
proc attachSender { } \
{
set fn attachSender
global senderSocket
global gatewayAddr
global gatewayPort
global traceflag

mytrace $traceflag [format "%s:%s" $fn $myName]

set senderSocket [attachSocket $gatewayAddr $gatewayPort]

mytrace $traceflag [format "%s:senderSocket=%s" $fn $senderSocket]

mytrace $traceflag [format "%s:done" $fn]

return $senderSocket

};# end attachSender

#=========================================================
#  name_detach - entry point
#=========================================================
proc name_detach { } \
{
set fn name_detach
global gatewaySocket
global senderSocket
global traceflag

mytrace $traceflag [format "%s:gatewaySocket=%s senderSocket=%s" $fn $gatewaySocket $senderSocket]

if { $senderSocket != $gatewaySocket } {
	vc_name_detach $senderSocket
	close $senderSocket
	}

vc_name_detach $gatewaySocket

close $gatewaySocket

};# end name_detach

#=========================================================
#  name_locate - entry point
#=========================================================
proc name_locate { theName } \
{
set fn name_locate
global senderSocket
global traceflag

mytrace $traceflag [format "%s:%s" $fn $theName]

set rc [vc_name_locate $senderSocket $theName]

return $rc

};# end name_locate


#=========================================================
# Send - entry point
#=========================================================
proc Send { recvID msg sbytes } \
{
set fn Send
global senderSocket
global VC_SEND_IT
global traceflag

mytrace $traceflag [format "%s:Send->%d on socket=%s" $fn $recvID $senderSocket]

set token $VC_SEND_IT
set nbytes [expr 4 + $sbytes]
set toWhom $recvID
set sMsg [ binary format "s1s1i1a$sbytes" $token $nbytes $toWhom $msg]

set rMsg [sendToSocket $senderSocket $sMsg]

return $rMsg

};# end Send

#=========================================================
# postMsg - entry point
#=========================================================
proc postMsg { recvID msg sbytes } \
{
set fn postMsg
global senderSocket
global VC_SEND_IT
global waitingForReply
global traceflag

mytrace $traceflag [format "%s:post->%d on socket=%s" $fn $recvID $senderSocket]

if { $waitingForReply == 0 } {
	set token $VC_SEND_IT
	set nbytes [expr 4 + $sbytes]
	set toWhom $recvID
	set sMsg [ binary format "s1s1i1a$sbytes" $token $nbytes $toWhom $msg]

	relayToSocket $senderSocket $sMsg
	set rc 1
	set waitingForReply 1
} else {
	set rc -1
}

return $rc

};# end postMsg

#=========================================================
# readReply - entry point
#=========================================================
proc readReply { } \
{
set fn readReply
global senderSocket
global waitingForReply
global traceflag

if { $waitingForReply == 1 } {
	set rMsg [readFromSocket $senderSocket]
	set waitingForReply 0
} else {
	set rMsg ""
}

return $rMsg

};# end readReply



#=========================================================
# Receive - entry point
#=========================================================
proc Receive { } \
{
set fn Receive
global gatewaySocket
global VC_SEND_IT
global VC_RELAY_IT
global traceflag

mytrace $traceflag [format "%s:ding" $fn ]

set x_it 1
while { $x_it == 1 } {
	set recvHdr [ read $gatewaySocket 4 ]
	binary scan $recvHdr s1s1 token nbytes

mytrace $traceflag [format "%s:token=%d nbytes=%d" $fn $token $nbytes]

	if { $nbytes > 0 } {
		set restMsg [ read $gatewaySocket $nbytes] 

		if { $token == $VC_SEND_IT } {
			set rbytes [expr $nbytes -4]
			binary scan $restMsg i1a$rbytes fromWhom dataMsg
			set rMsg [binary format "i1i1a$rbytes" $fromWhom $rbytes $dataMsg]
			set x_it 0

		} else {
		if { $token == $VC_RELAY_IT } {
			set rbytes [expr $nbytes -4]
			binary scan $restMsg i1a$rbytes fromWhom dataMsg
			set rMsg [binary format "i1i1a$rbytes" $fromWhom $rbytes $dataMsg]
			set x_it 0

			};# end if token
		};# end else
		};# end if nbytes
	};# end while

return $rMsg

};# end Receive


#=========================================================
# Reply - entry point
#=========================================================
proc Reply { fromWhom msg rbytes } \
{
set fn Reply
global gatewaySocket
global VC_REPLY_IT
global traceflag

mytrace $traceflag [format "%s:Reply %d bytes->%d" $fn $rbytes $fromWhom]

set token $VC_REPLY_IT
set nbytes [expr 4 + $rbytes]
if { $rbytes > 0 } {
set rMsg [ binary format "s1s1i1a$rbytes" $token $nbytes $fromWhom $msg]
} else {
set rMsg [ binary format "s1s1i1" $token $nbytes $fromWhom]
}

replyToSocket $gatewaySocket $rMsg

};# end Reply




#=========================================================
#  logit - entry point
#=========================================================
proc logit { loggerID myFile myFn myMask logMask msg } \
{
set fn logit
global senderSocket

if { $loggerID != -1 } {

#	vc_logit $senderSocket $loggerID $myFile $myFn $myMask $logMask $msg

	set checkmask [ expr $myMask & $logMask ]
	if { $checkmask != 0 } {
		puts stdout [format "%s %s:%s" $myFile $myFn $msg]
		};# end if checkmask
	}

};# end logit

