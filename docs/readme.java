/***********************************************************************

FILE:			readme.java

DATE:			09 Mar 16

DESCRIPTION:	Description of how to use the SIMPL Java class.

NOTE:			tabs = 4 for this file.

REVISIONS:
$Log: readme.java,v $
Revision 1.1  2009/03/17 15:29:32  johnfcsoft
initial entry


***********************************************************************/

This file is intended as a brief description and background of SIMPL Java
methods. It is represented by a Java class called Jsimpl. This is contained in
a file called Jsimpl.class. Jsimpl.class refers to a shared JNI library called
libjsimpl.so which provides the actual C-based SIMPL calls.

The Jsimpl class essentially contains two types of methods:
1. those that refer to SIMPL functionality, and
2. those that refer to packing and unpacking the messages that are received and
sent via the SIMPL functions.

Below, we will look at these two types of methods in some detail.

NOTE: the following has been written with a Linux distribution in mind
(directory names and locations specifically) but the basic ideas are invariant
w.r.t. the OS being used.

=============
SIMPL Methods
=============

The source code for the Jsimpl.class is called naturally enough Jsimpl.java.
Looking at this file reveals that the class methods are grouped in a rough way.
The SIMPL methods appear at the beginning and they relate the C-based SIMPL
function calls to Java methods via JNI.

They appear as follows:

-----------------------------------------------------------------------
int nameAttach(String name)

nameAttach() attaches the unique SIMPL name "name". This has the effect of
setting up the calling process for SIMPL communications and allowing other
SIMPL-enabled programs to locate this process if necessary. This is always the
first method called.

Returns: 0 for success; -1 for failure

Example:
String name = "mySimplName";
int ret = Jsimpl.nameAttach(name);
-----------------------------------------------------------------------

-----------------------------------------------------------------------
int nameDetach()

nameDetach() releases all SIMPL functionality from a program. If a program is
finishing, this method should be called prior to the end or even if SIMPL
capability is no longer required within the program. nameDetach() isn't always
necessary to call because it is called by default internally upon program exit.

Returns: 0 for success; -1 for failure

Example:
String name = "mySimplName";
int ret = Jsimpl.nameAttach(name);
	.
	.
	.
ret = Jsimpl.nameDetach();
-----------------------------------------------------------------------

-----------------------------------------------------------------------
int surDetach(int fd)

surDetach() releases all SIMPL functionality relating to remote message
sending. (ie. from host to host). It should be be called when such capability
is no longer required within the program. Like nameDetach(), it also is called
by default internally upon program exit.

Returns: 0 for success; -1 for failure

Example:
int id = Jsimpl.nameLocate("remote program");
	.
	.
	.
int ret = Jsimpl.surDetach(id);
-----------------------------------------------------------------------

-----------------------------------------------------------------------
int nameLocate(String name)

nameLocate() locates a SIMPL-enabled program by "name" that the calling
program wishes to send a mesaage to. It is required prior to Send()'ing a
message.

Returns: >=0 for success; -1 for failure

Example:
int id = Jsimpl.nameLocate("program");
	.
	.
	.
int ret = Jsimpl.Send(id);
-----------------------------------------------------------------------

-----------------------------------------------------------------------
int Send(int id)

Send() sends a message to another program defined by a unique id.

Returns: >=0 for success which is the size (if any) of a replied message; -1
for failure.

Example:
int id = Jsimpl.nameLocate("program");
	.
// build the message to be sent
	.
int ret = Jsimpl.Send(id);
-----------------------------------------------------------------------

-----------------------------------------------------------------------
int Receive()

Receive() receives a message from another program.

Returns: >=0 for success which is the id of the sender; -1 for failure or
<-1 for a proxy.

Example:
int senderId = Jsimpl.Receive();
-----------------------------------------------------------------------

-----------------------------------------------------------------------
int Reply()

Reply() replies to a sender after a Receive().

Returns: >=0 for success; -1 for failure.

Example:
int ret = Jsimpl.Reply(senderId);
-----------------------------------------------------------------------

-----------------------------------------------------------------------
int Trigger(int id, int proxy)

Trigger() sends a proxy to another program defined by a unique id.

Returns: >=0 for success; -1 for failure.

Example:
int id = Jsimpl.nameLocate("program");
	.
int proxy = 42;
	.
int ret = Jsimpl.Trigger(id, proxy);
-----------------------------------------------------------------------

-----------------------------------------------------------------------
int whatsMyRecvfd()

whatsMyRecvfd() returns a receiver's file descriptor. This can be used when a
program is "selecting" on more than one file descriptor.

Returns: >=0 for success; -1 for failure.

Example:
int fd = Jsimpl.whatsMyRecvfd();
-----------------------------------------------------------------------

-----------------------------------------------------------------------
int returnProxy(int proxy)

returnProxy() returns the true value of the proxy value returned by a
Receive() as sent by a Trigger().

Returns: >=0

Example:
int ret = Jsimpl.Receive();
if (ret < -1)
	{
	int proxy = Jsimpl.returnProxy(ret);
	}
-----------------------------------------------------------------------

-----------------------------------------------------------------------
String whatsMyError()

whatsMyError() returns an error string similar to strerror(errno) in C.

Returns: a message string.

Example:
int ret = Jsimpl.Receive();
if (ret == -1)
	{
	System.out.println("receive problem: " + Jsimpl.whatsMyError());
	}

-----------------------------------------------------------------------

-----------------------------------------------------------------------
int getMsgSize(int id)

getMsgSize() returns the size of a received message.

Returns: >=0

Example:
int senderId = Jsimpl.Receive();
if (senderId != -1)
	{
	int size = getMsgSize(senderId);
	// size is the size of the message sent by senderId
	}

-----------------------------------------------------------------------

===============
Packing Methods
===============

The Java SIMPL methods were developed with the idea in mind that it might be
necessary to have Java programs communicate with C programs. SIMPL is currently
supported in C, Python, and Tcl as well. So, it is possible to have any
combination of Java, Tcl, Python and C programs communicate with each other via
SIMPL, either locally or remotely.

The usual mode of communication with a C program is simply to send it a number
of bytes with a predefined organization. Typically, a C program will read x
bytes into memory and then lay a structure template on this portion of memory
and pick out the pieces of interest. This sort of thing is not possible in Java
and the concept of a pointer is foreign. So, in order to build such a message
as a C program would desire, a series of "packing" routines have been written
which write the message.

For example, suppose that a Java program needs to send a message starting with
an int, followed by a float and then a short array and say that the  Java
program expects to get the same thing back in reply. Here is how we would do
it:

int sender;
int ret;
int i = 42;
float j = 3.1415F;
short[] k = {1, 2, 3};

// simpl name attach must come first
Jsimpl.nameAttach("sender")
// name locate the receiver process
sender = Jsimpl.nameLocate("receiver");
// allocate 100 bytes for the send and reply messages; more than enough
ret = Jsimpl.packStart(100, 100);
// build the message
ret = Jsimpl.packInt(i);
ret = Jsimpl.packFloat(j);
ret = Jsimpl.packShortArray(k);
// send the message
ret = Jsimpl.Send(sender);

A message will be sent to "receiver" starting with an int followed by a float
and then three shorts. Note that we have not checked the return values which
would normally be wise in case of problems.

The methods are in a one-to-one correspondence with the primitives available in
Java. Failures generally occur if there is not enough memory allocated for
the incoming and/or outgoing messages via packStart().

Many of these methods are candidates for function overloading in Java and
this was the original approach. Nevertheless, there are exceptions to the
rule and a sort asymmetry evolves between the packing and unpacking methods
which is unsightly, hence function overloading was not employed.

The packing methods are as follows:

-----------------------------------------------------------------------
int packByte(byte p)

packByte() packs a byte p (1 byte) into an outgoing message ie. one to be sent
via Send().

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int packChar(char p)

packChar() packs a char p (2 bytes) into an outgoing message ie. one to be sent
via Send().

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int packShort(short p)

packShort() packs a short integer p (2 bytes) into an outgoing message ie. one
to be sent via Send().

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int packInt(int p)

packInt() packs an int p (4 bytes) into an outgoing message ie. one to be sent
via Send().

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int packLong(long p)

packLong() packs a long integer p (8 bytes) into an outgoing message ie. one to
be sent via Send().

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int packFloat(float p)

packFloat() packs a float p (4 bytes) into an outgoing message ie. one to be
sent via Send().

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int packDouble(double p)

packDouble() packs a double p (8 bytes) into an outgoing message ie. one to be
sent via Send().

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int packString(String p)

packString() packs a String object into an outgoing message ie. one to be sent
via Send().

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int packByteArray(byte[] p)

packByteArray() packs an array of bytes p into an outgoing message ie. one to be
sent via Send().

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int packCharArray(char[] p)

packCharArray() packs an array of chars p into an outgoing message ie. one to be
sent via Send().

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int packShortArray(short[] p)

packShortArray() packs an array of short integers p into an outgoing message
ie. one to be sent via Send().

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int packIntArray(int[] p)

packIntArray() packs an array of integers p into an outgoing message
ie. one to be sent via Send().

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int packLongArray(long[] p)

packLongArray() packs an array of long integers p into an outgoing message
ie. one to be sent via Send().

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int packFloatArray(float[] p)

packFloatArray() packs an array of floating point numbers p into an outgoing
message ie. one to be sent via Send().

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int packDoubleArray(double[] p)

packDoubleArray() packs an array of double precision floating point numbers p
into an outgoing message ie. one to be sent via Send().

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

=================
Unpacking Methods
=================

Above, we discussed Packing Methods. These are used for building messages made
from Java primitives, strings, and arrays. These messages are those to be sent
out to a receiver program of some sort. This leaves the question: What to do
with messages that are received such as those from a Receive() or sent via a
Reply()?

These messages need to be unpacked from a buffer into Java types. In effect,
we need to deconstruct the message. This is accomplished with the unpack
methods.

Following the example above in Pack Methods and using the same message:

// simpl name attach must come first
Jsimpl.nameAttach("receiver")
// allocate 100 bytes for the received and replied messages each
ret = Jsimpl.packStart(100, 100);
// receive messages
int senderId = Jsimpl.Receive();
// deconstruct the message
int i = Jsimpl.unpackInt();
float j = Jsimpl.unpackFloat();
short[] k = {0, 0, 0};
int ret = Jsimpl.unpackShortArray(k);

Note: the methods that return Java primitives such as byte, short etc. will
return a -1 on a failure. This may or may not indicate failure since Java
primitives are all signed values. ie. a returned short may indeed be the number
-1. In the case of unpacked arrays, a return value of -1 always indicates an
error.

The unpack methods are as follows:

-----------------------------------------------------------------------
byte unpackByte()

unpackByte() unpacks a byte (1 byte) from an incoming message ie. one that
has been Receive()'d or Reply()'d.

Returns: a byte value
----------------------------------------------------------------------

-----------------------------------------------------------------------
char unpackChar()

unpackChar() unpacks a char (2 bytes) from an incoming message ie. one that
has been Receive()'d or Reply()'d.

Returns: a char value
----------------------------------------------------------------------

-----------------------------------------------------------------------
short unpackShort()

unpackShort() unpacks a short integer (2 bytes) from an incoming message ie.
one that has been Receive()'d or Reply()'d.

Returns: a short value
----------------------------------------------------------------------

-----------------------------------------------------------------------
int unpackInt()

unpackInt() unpacks an integer (4 bytes) from an incoming message ie.
one that has been Receive()'d or Reply()'d.

Returns: an int value
----------------------------------------------------------------------

-----------------------------------------------------------------------
long unpackLong()

unpackLong() unpacks a long integer (8 bytes) from an incoming message ie.
one that has been Receive()'d or Reply()'d.

Returns: a long value
----------------------------------------------------------------------

-----------------------------------------------------------------------
float unpackFloat()

unpackFloat() unpacks a floating point number (4 bytes) from an incoming
message ie. one that has been Receive()'d or Reply()'d.

Returns: a float value
----------------------------------------------------------------------

-----------------------------------------------------------------------
double unpackDouble()

unpackDouble() unpacks a double precision floating point number (8 bytes) from
an incoming message ie. one that has been Receive()'d or Reply()'d.

Returns: a double value
----------------------------------------------------------------------

-----------------------------------------------------------------------
String unpackString(int len)

unpackString() unpacks a string object of length "len" from an incoming message
ie. one that has been Receive()'d or Reply()'d.

Returns: a String value
----------------------------------------------------------------------

-----------------------------------------------------------------------
int unpackByteArray(byte[] p)

unpackByteArray() unpacks an array of bytes p from an incoming message ie. one
that has been Receive()'d or Reply()'d.

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int unpackCharArray(char[] p)

unpackCharArray() unpacks an array of char p from an incoming message ie. one
that has been Receive()'d or Reply()'d.

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int unpackShortArray(short[] p)

unpackShortArray() unpacks an array of short integers p from an incoming
message ie. onethat has been Receive()'d or Reply()'d.

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int unpackIntArray(int[] p)

unpackIntArray() unpacks an array of integers p from an incoming message
ie. one that has been Receive()'d or Reply()'d.

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int unpackLongArray(long[] p)

unpackLongArray() unpacks an array of long integers p from an incoming message
ie. one that has been Receive()'d or Reply()'d.

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int unpackFloatArray(float[] p)

unpackFloatArray() unpacks an array of floating point numbers p from an
incoming message ie. one that has been Receive()'d or Reply()'d.

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
int unpackDoubleArray(double[] p)

unpackDoubleArray() unpacks an array of double precision floating point numbers
p from an incoming message ie. one that has been Receive()'d or Reply()'d.

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

=============
Other Methods
=============

There are a few other methods that are required or useful other than the
packing or unpacking types.

-----------------------------------------------------------------------
int packStart(int p, int q)

packStart() is required before any message packing/unpacking can occur. It
dynamically allocates memory to be used for incoming and outgoing messages
as well as performing a number of initializations required internally to this
class of JNI methods.

Returns: 0 for success; -1 for failure
----------------------------------------------------------------------

-----------------------------------------------------------------------
void packEnd()

packEnd() is used when a program has finished with any packing/unpacking
procedures.

Returns: nothing
----------------------------------------------------------------------

-----------------------------------------------------------------------
int packIfree()

packIfree() returns the amount of available memory at the point of calling for
an incoming message. The first argument in packStart() sets the maximum buffer
size for any incoming messages.

Returns: amount of input buffer available.
----------------------------------------------------------------------

-----------------------------------------------------------------------
int packOfree()

packOfree() returns the amount of available memory at the point of calling for
an outgoing message. The second argument in packStart() sets the maximum buffer
size for any outgoing messages. Each call to pack*() uses up more of the
available space and this method can be used as a check on that availability.

Returns: amount of output buffer available.
----------------------------------------------------------------------
