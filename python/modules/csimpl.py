"""
csimpl.py

Contains wrapped calls to simpl2.so and simpl3.so, python versions
2 and 3 respectively, which are C simpl extension libraries.

Can be called as class methods via a Simpl class instantiation or as straight
functions.
"""

# import required module bits
from struct import pack, unpack
from sys import exit, version

# this file is to be imported as a module only
if __name__ == "__main__":
	print("csimpl.py is not to be run as a main program; it is a module only.")
	exit()

# which C extension library to import?
if version > '3':
	import simpl3 as simpl
else:
	import simpl2 as simpl

# global constants
SIMPL_BIN = -2
SIMPL_CHR = -1
SIMPL_NATIVE = 0
SIMPL_LITTLE_ENDIAN = 1
SIMPL_BIG_ENDIAN = 2
SIMPL_BIT_64 = 64
SIMPL_BIT_32 = 32

# for incoming messages
global _simplInBuf
global _simplInCtr
global _simplMaxIn

# for outgoing messages
global _simplOutBuf
global _simplOutCtr

# for 32/64-bit architectures involving incoming messages
global _simplIchar
global _simplIshort
global _simplIint
global _simplIlong
global _simplIfloat
global _simplIdouble

# for 32/64-bit architectures involving outgoing messages
global _simplOchar
global _simplOshort
global _simplOint
global _simplOlong
global _simplOfloat
global _simplOdouble

# byte order
global _simplInByteOrder
global _simplOutByteOrder

#############################################################################
#	Start of SIMPL class definition
#############################################################################
class Simpl(object):
	"""
	For a description of the Simpl class methods, see the descriptions with the
	accompanying functions below.
	"""

	# constructor
	def __init__(self, name, maxMemSize):
		# available constants for packing/unpacking
		self.BIN = SIMPL_BIN
		self.CHR = SIMPL_CHR

		# available constants for cpu architecture
		self.BIT_64 = SIMPL_BIT_64
		self.BIT_32 = SIMPL_BIT_32
		
		# available constants for byte ordering
		self.NATIVE = SIMPL_NATIVE
		self.LITTLE_ENDIAN = SIMPL_LITTLE_ENDIAN
		self.BIG_ENDIAN = SIMPL_BIG_ENDIAN

		# perform a simpl name attach
		if nameAttach(name, maxMemSize) == -1:
			print("name attach error-", whatsMyError())
			exit(-1)

	# destructor
	def __del__(self):
		# perform a simpl name detach and cleanup
		if nameDetach() == -1:
			print("name detach error-", whatsMyError())
			exit(-1)
		
	#==============================================================
	# SIMPL methods
	#==============================================================

	def surDetach(self, fd):
		return surDetach(fd)

	def nameLocate(self, phn):
		return nameLocate(phn)

	def send(self, receiverId):
		return send(receiverId)

	def trigger(self, receiverId, proxy):
		return trigger(receiverId, proxy)

	def receive(self):
		return receive()

	def reply(self, senderId):
		return reply(senderId)

	def whatsMyReceiveFd(self):
		return whatsMyReceiveFd()

	def whatsMyError(self):
		return whatsMyError()

	def returnProxy(self, value):
		return returnProxy(value)

	#==============================================================
	# packing methods
	#==============================================================

	def packMsg(self, action, form, *args):
		packMsg(action, form, *args)

	def packByte(self, p, action):
		packByte(p, action)
	
	def packChar(self, p, action):
		packChar(p, action)

	def packShort(self, p, action):
		packShort(p, action)

	def packInt(self, p, action):
		packInt(p, action)

	def packLong(self, p, action):
		packLong(p, action)

	def packFloat(self, p, action):
		packFloat(p, action)

	def packDouble(self, p, action):
		packDouble(p, action)

	def packString(self, p, action):
		packString(p, action)

	def packShortArray(self, p, action):
		packShortArray(p, action)

	def packIntArray(self, p, action):
		packIntArray(p, action)

	def packLongArray(self, p, action):
		packLongArray(p, action)

	def packFloatArray(self, p, action):
		packFloatArray(p, action)

	def packDoubleArray(self, p, action):
		packDoubleArray(p, action)

	#==============================================================
	# unpacking methods
	#==============================================================

	def unpackMsg(self, action, form):
		return unpackMsg(action, form)

	def unpackByte(self, action):
		return unpackByte(action)

	def unpackChar(self, action):
		return unpackChar(action)

	def unpackShort(self, action):
		return unpackShort(action)

	def unpackInt(self, action):
		return unpackInt(action)

	def unpackLong(self, action):
		return unpackLong(action)

	def unpackFloat(self, action):
		return unpackFloat(action)

	def unpackDouble(self, action):
		return unpackDouble(action)

	def unpackString(self, p, action):
		unpackString(p, action)

	def unpackShortArray(self, p, action):
		unpackShortArray(p, action)

	def unpackIntArray(self, p, action):
		unpackIntArray(p, action)

	def unpackLongArray(self, p, action):
		unpackLongArray(p, action)

	def unpackFloatArray(self, p, action):
		unpackFloatArray(p, action)

	def unpackDoubleArray(self, p, action):
		unpackDoubleArray(p, action)
		
	#==============================================================
	# other methods
	#==============================================================

	def reset(self):
		reset()

	def crossCopy(self):
		crossCopy()

	def returnInBuffer(self):
		return returnInBuffer()

	def returnOutBuffer(self):
		return returnOutBuffer()

	def setInByteOrder(self, order):
		setInByteOrder(order)

	def setOutByteOrder(self, order):
		setOutByteOrder(order)

	def setInArch(self, arch):
		setInArch(arch)

	def setOutArch(self, arch):
		setOutArch(arch)
#############################################################################
#	End of Simpl class definition
#############################################################################

#==============================================================
# SIMPL functions
#==============================================================

def nameAttach(name, maxMemSize):
	"""
	nameAttach() attaches a simpl name "name" and initializes all required
	aspects of simpl communications including message buffer sizes up to a
	maximum "maxMemSize".

	This function must be called prior to any simpl-based operations if simpl
	capabilities are going to be called directly as functions. If simpl
	capabilities are to be used via an instantiation of a Simpl class object,
	then nameAttach() is called as part of the constructor and is not to be
	called directly.

	This function/method must be called by any process (ie. senders and/or
	receivers) which desire to use	simpl.
	
	Returns success (>= 0) or failure (-1)
	"""
	global _simplMaxIn

	# set maximum incoming buffer size: needed for C extension, not for Python
	_simplMaxIn = maxMemSize

	# initialize incoming message buffer variables
	resetInBuffer()
	# initialize outgoing message buffer variables
	resetOutBuffer()

	# set incoming message  byte ordering - native by default
	setInByteOrder(SIMPL_NATIVE)
	# set outgoing message  byte ordering - native by default
	setOutByteOrder(SIMPL_NATIVE)

	# set incoming message C data types to reflect a 64-bit architecture
	setInArch(SIMPL_BIT_64)
	# set outgoing message C data types to reflect a 64-bit architecture
	setOutArch(SIMPL_BIT_64)

	# call C extension function
	return simpl.nameAttach(name)
	
def nameDetach():
	"""
	nameDetach() releases all required apects of simpl communications.
	This function is called when a program has no further use for simpl
	communications or at program termination. If simpl has been called as
	an instantiation of a Simpl class object, then nameDetach() will be called
	as part of the destructor and need not be called directly.

	Returns success (0) or failure (-1).
	"""
	return simpl.nameDetach()

def surDetach(fd):
	"""
	surDetach() releases any surrogate components of simpl communications.
	These will only arise when when communications are non-local and only under
	specific circumstances. For further information See the documentation under
	the C simpl library.

	Returns success (0) or failure (-1).
	"""
	return simpl.surDetach(fd)

def nameLocate(phn):
	"""
	nameLocate makes a communication connection with a another simpl based
	program using the "phn" argument. 'p'= port number, 'h'=host name or IP
	address, 'n'=the simpl name of the process with which communications are
	desired. The three possible fields are delimited by a colon ':'.

	This function/method is typically used by 'sender' processes to make a
	connection to a 'receiver' process for the purposes of exchanging data.
	
	Example: phn = "8000:concord:tim" where the port number is '8000', the
	computer host name is 'concord', and the process name is 'tim'.

	Example: phn = "50000:127.0.0.1:zut" where the port number is '50000', the
	computer host name is the 'local host' (loopback), and the program name is
	'zut' (just zut).

	Returns: the unique simpl Id of the receiver (>= 0) or failure (-1)
	"""
	return simpl.nameLocate(phn)

def send(receiverId):
	"""
	send() delivers a message that has been preformed via the use of packMsg()
	method/function	to the simpl receiver program with simpl identification
	number 'receiverId' and then blocks awaiting a reply.

	Returns: the number of bytes replied (>= 0) or failure (-1)
	"""
	resetInBuffer()
	ret = simpl.send(receiverId, _simplOutBuf, _simplInBuf)
	resetOutBuffer()
	return ret

def trigger(receiverId, proxy):
	"""
	trigger() delivers a proxy 'proxy' (>= 0) to the simpl receiver	program with
	simpl identification number 'receiverId'. It does not block awaiting a
	reply.

	Returns: success (0) or failure (-1)
	"""

	return simpl.trigger(receiverId, proxy)

def receive():
	"""
	receive() receives the messages sent by send() or trigger(). It blocks
	awaiting an incoming message/trigger.

	Returns: success (messageSize >= 0) and senderId (>=0), or failure
	(messageSize = -1).
	"""
	global _simplInBuf
	resetInBuffer()
	if version > '3':
		messageSize, senderId = simpl.receive(_simplInBuf)
	else:
		messageSize, senderId, _simplInBuf = simpl.receive()
	return messageSize, senderId

def reply(senderId):
	"""
	reply() replies a message or a null message received by send(). Upon
	receiving the reply, send() unblocks.

	Returns: success (reply msg size in bytes >= 0) or failure (-1).
	"""
	ret = simpl.reply(senderId, _simplOutBuf)
	resetOutBuffer()
	return ret

def whatsMyReceiveFd():
	"""
	Returns: success (receive fd >= 3) or failure (-1).
	"""
	return simpl.whatsMyReceiveFd()

def whatsMyError():
	"""
	Returns: an error string similar to strerror(errno) or None.
	"""
	return simpl.whatsMyError()

def returnProxy(value):
	"""
	When a proxy is received (receive()) via a trigger(), its value is <=-2. In
	order to regain the true value of the proxy, this 'value' is passed into
	returnProxy().

	Returns: the true value of the proxy (>= 0)
	"""
	return simpl.returnProxy(value)

#==============================================================
# packing functions
#==============================================================

def packMsg(action, form, *args):
	"""
	packMsg() is currently concerned with C data types. Python types etc. are
	not considered per say.
	
	packMsg() is a general packing routine used for constructing simpl messages
	that are bound to be forwarded to a receiver program via a simpl send()
	call. It is modeled after and uses the module struct.

	Message data may be packed in a binary or a character format. The 'action'
	defines the type of packing to occur: binary or character based.

	The 'form' defines a format string which defines the type, size and order of
	the data to be found in the outgoing message. The 'args' are the data type
	values to be placed in the outgoing message buffer. The target is the
	receiver program in question which will receive the message format and
	disassemble it accordingly.

	The format string can be quantified as follows:
	'b': a single unsigned character (1 byte)
	'c': a single character string (1 byte)
	's': a character string (length of string in bytes)
	'h': a signed short integer (2 bytes)
	'i': a signed integer (4 bytes)
	'l': a signed long integer (4 bytes/32-bit or 8 bytes/64-bit)
	'f': a signed float (4 bytes)
	'd': a signed double (4 bytes/32-bit or 8 bytes/64-bit)
	'H': a signed short integer array (size * 2 bytes)
	'I': a signed integer array (size * 4 bytes)
	'L': a signed long integer array(size * 4 bytes/32-bit or 8 bytes/64-bit)
	'F': a signed float array (size * 4 bytes)
	'D': a signed double array (size * 4 bytes/32-bit or 8 bytes/64-bit)

	A general format can be seen as follows:
	"chilfd#s#H#I#L#F#D"
	where '#' is the size/number of data types in the string or array.

	The above format defines a message that is as follows: (recall C types)
	1. one single character (1 byte, not unicode)
	2. one signed short integer
	3. one signed integer
	4. one signed long integer
	5. one floating point number
	6. one double precision floating point number
	7. one string # bytes long
	8. one signed short array of numbers # long
	9. one signed integer array of numbers # long
	10. one signed long array of numbers # long
	11. one floating point array of numbers # long
	12. one double precision floating point array of numbers # long
	
	The way the message is packed depends on:
	a) is it binary or character based?
	b) is the receiving architecture 32 or 64 bit?

	The outgoing message buffer is looked after internally to the module and
	the calling program (and programmer) need not be concerned, unlike the C
	version of simpl.
	
	Returns: nothing.
	"""
	global _simplOutBuf
	global _simplOutCtr

	# check inputted command line
	if len(form) != len(args):
		print("Number of format types is not equal to the number of arg types.")
		exit(-1)
	if not form.isalpha():
		print("Format string contains non-alphabetical character(s).")
		exit(-1)

	# delineate the form(at) string and process each variable type in args
	for (offset, item) in enumerate(form):
		# handle differences in python versions 2 and 3
		if item == 'c' or item == 's' and version > '3':
			arg = args[offset].encode('utf-8')
		else:
			arg = args[offset]

		if item.isupper() or item == 's':
			# an array or string
			amount = len(arg)
		else:
			# a single value
			amount = 1

		# single unsigned byte character
		if item == 'b':
			atomicSize = _simplOchar
			kind = "B"
		# single character string
		elif item == 'c':
			atomicSize = _simplOchar
			kind = "c"
		# string of single byte characters
		elif item == 's':
			atomicSize = _simplOchar
			kind = str(len(arg)) + "s"
		# single short integer or an array of same
		elif item == 'h' or item == 'H':
			atomicSize = _simplOshort
			kind = _simplOutByteOrder + "h"
		# single integer or an array of same
		elif item == 'i' or item == 'I':
			atomicSize = _simplOint
			kind = _simplOutByteOrder + "i"
		# single long integer or an array of same
		elif item == 'l' or item == 'L':
			atomicSize = _simplOlong
			kind = _simplOutByteOrder + "l"
		# single floating point number or an array of same
		elif item == 'f' or item == 'F':
			atomicSize = _simplOfloat
			kind = _simplOutByteOrder + "f"
		# single double precision floating point number or an array of same
		elif item == 'd' or item == 'D':
			atomicSize = _simplOdouble
			kind = _simplOutByteOrder + "d"
		# unknown C variable type
		else:
			print("Incorrect argument type =", item)
			exit(-1)

		# set counters and pack the out message buffer
		setOutBuf(atomicSize, action)
		if item.isupper(): # an array
			for i in range(amount):
				_simplOutBuf += pack(kind, arg[i])
		else: # a single value or a string of byte characters
			_simplOutBuf += pack(kind, arg)
		_simplOutCtr += amount * atomicSize 

def packByte(p, action):
	packMsg(action, "b", p)

def packChar(p, action):
	packMsg(action, "c", p)

def packShort(p, action):
	packMsg(action, "h", p)
	
def packInt(p, action):
	packMsg(action, "i", p)
	
def packLong(p, action):
	packMsg(action, "l", p)
	
def packFloat(p, action):
	packMsg(action, "f", p)
	
def packDouble(p, action):
	packMsg(action, "d", p)
	
def packString(p, action):
	packMsg(action, "s", p)

def packShortArray(p, action):
	packMsg(action, "H", p)
	
def packIntArray(p, action):
	packMsg(action, "I", p)
	
def packLongArray(p, action):
	packMsg(action, "L", p)
	
def packFloatArray(p, action):
	packMsg(action, "F", p)
	
def packDoubleArray(p, action):
	packMsg(action, "D", p)

#==============================================================
# unpacking functions
#==============================================================
		
def unpackMsg(action, form):
	"""
	unpackMsg() is currently only concerned with C data types. Python types etc.
	are not considered per say.

	unpackMsg() is a general unpacking routine used for deconstructing simpl
	messages that have been received by a receiver program via a reply() to
	a send() call. It is modelled after and uses the module struct.

	The 'action' defines the type of packing to occur: binary or character
	based. The 'form' defines a format string which defines the type, size and
	order of the data to be found in the incoming message.

	The format string can be quantified as follows:
	'b': a single unsigned character (1 byte)
	'c': a single character string (1 byte)
	's': a character string (length of string in bytes)
	'h': a signed short integer (2 bytes)
	'i': a signed integer (4 bytes)
	'l': a signed long integer (4 bytes/32-bit or 8 bytes/64-bit)
	'f': a signed float (4 bytes)
	'd': a signed double (4 bytes/32-bit or 8 bytes/64-bit)
	'H': a signed short integer array (size * 2 bytes)
	'I': a signed integer array (size * 4 bytes)
	'L': a signed long integer array(size * 4 bytes/32-bit or 8 bytes/64-bit)
	'F': a signed float array (size * 4 bytes)
	'D': a signed double array (size * 4 bytes/32-bit or 8 bytes/64-bit)

	A general format can be seen as follows:
	"chilfd#s#H#I#L#F#D"
	where '#' is the size/number of data types in the string or array.

	Returns: a tuple which corresponds to the elements of the extracted message.
	"""
	global _simplInCtr
	
	# check inputted command line for aberrations
	if not len(form):
		print("Format string must not be null.")
		exit(-1)
	if not form.isalnum():
		print("Format string contains non-alphabetical/numerical character(s).")
		exit(-1)
		
	# determine the length of the working list based on the number of variables
	# and not the numerical values
	ctr = 0
	for ch in form:
		if ch.isalpha():
			ctr += 1
	
	# create a working list of values to be read into from inBuffer and
	# returned to the calling program
	args = [None] * ctr
	
	# string holding numerical values (string or array lengths) encountered
	length = ""

	# extract data based upon the variable type and size
	i = 0
	for item in form:
		# an alphabetic character in the format string
		if item.isalpha():
			# determine the size of the array or string
			if item.isupper() or item == 's':
				if not length: # a single valued string or array
					size = 1
				else:
					size = int(length)
			# a single value type
			else:
				size = 1
			# reset the length just in case it was used
			length = ""

			if item == 'b':
				atomicSize = _simplIchar
				kind = "B"
			elif item == 'c':
				atomicSize = _simplIchar
				kind = "c"
			elif item == 's':
				atomicSize = _simplIchar
				kind = str(size) + "s"
			elif item == 'h' or item == 'H':
				atomicSize = _simplIshort
				kind = _simplInByteOrder + "h"
			elif item == 'i' or item == 'I':
				atomicSize = _simplIint
				kind = _simplInByteOrder + "i"
			elif item == 'l' or item == 'L':
				atomicSize = _simplIlong
				kind = _simplInByteOrder + "l"
			elif item == 'f' or item == 'F':
				atomicSize = _simplIfloat
				kind = _simplInByteOrder + "f"
			elif item == 'd' or item == 'D':
				atomicSize = _simplIdouble
				kind = _simplInByteOrder + "d"
			else:
				print("Incorrect alphabetical type =", item)
				exit(-1)

			# set counters and unpack the in message buffer
			setInBuf(atomicSize, action)
			if item.isupper():
				args[i] = [None] * size
				for j in range(size):
					begin = _simplInCtr
					_simplInCtr = end = begin + atomicSize
					# recall, unpack returnr a tuple
					t = unpack(kind,_simplInBuf[begin:end])
					args[i][j] = t[0]
			else:
				begin = _simplInCtr
				_simplInCtr = end = begin + atomicSize * size
				# recall, unpack retunrs a tuple
				t = unpack(kind, _simplInBuf[begin:end])
				args[i] = t[0]
			i += 1 # only increment return value list now
		# a numeric value in the format string	
		else:
			length += item # build an array or string length value

	# return the required arguments to the calling program
	if i == 1:
		return args[0]
	else:
		return args

def unpackByte(action):
	return unpackMsg(action, "b")

def unpackChar(action):
	return unpackMsg(action, "c")

def unpackShort(action):
	return unpackMsg(action, "h")

def unpackInt(action):
	return unpackMsg(action, "i")

def unpackLong(action):
	return unpackMsg(action, "l")

def unpackFloat(action):
	return unpackMsg(action, "f")

def unpackDouble(action):
	return unpackMsg(action, "d")

def unpackString(p, action):
	form = str(p) + "s"
	return unpackMsg(action, form)

def unpackShortArray(p, action):
	form = str(len(p)) + "H"
	p = unpackMsg(action, form)

def unpackIntArray(p, action):
	form = str(len(p)) + "I"
	p = unpackMsg(action, form)

def unpackLongArray(p, action):
	form = str(len(p)) + "L"
	p = unpackMsg(action, form)

def unpackFloatArray(p, action):
	form = str(len(p)) + "F"
	p = unpackMsg(action, form)

def unpackDoubleArray(p, action):
	form = str(len(p)) + "D"
	p = unpackMsg(action, form)

#==============================================================
# other useful functions
#==============================================================

def reset():
	"""
	reset() is a general call to set both the incoming and outgoing message
	buffers and their byte counters to a known state.
	"""
	# incoming message buffer variables
	resetInBuffer()
	# outgoing message buffer variables
	resetOutBuffer()

############################################################################

def resetInBuffer():
	"""
	resetInBuffer() re-initializes the incoming message buffer.
	"""
	global _simplInBuf
	global _simplInCtr

	if version > '3':
		_simplInBuf = b" " * _simplMaxIn
	else:
		_simplInBuf = " " * _simplMaxIn
	_simplInCtr = 0

############################################################################

def resetOutBuffer():
	"""
	resetOutBuffer() re-initializes the outgoing message buffer.
	"""
	global _simplOutBuf
	global _simplOutCtr

	if version > '3':
		_simplOutBuf = b""
	else:
		_simplOutBuf = ""
	_simplOutCtr = 0

#############################################################################

def crossCopy():
	"""
	crossCopy() copies the contents of the outgoing message buffer to the
	incoming message buffer for reasons of testing and verification.
	"""
	global _simplInBuf
	_simplInBuf = _simplOutBuf

#############################################################################

def returnInBuffer():
	"""
	returnInBuffer() returns the contents of the incoming message buffer.
	"""
	return _simplInBuf

#############################################################################

def returnOutBuffer():
	"""
	returnOutBuffer() returns the contents of the outgoing message buffer.
	"""
	return _simplOutBuf

#############################################################################

def setInByteOrder(order):
	"""
	setInByteOrder() sets the byte order on incoming messages.
	"""
	global _simplInByteOrder

	if order == SIMPL_NATIVE:
		_simplInByteOrder = ""
	elif order == SIMPL_LITTLE_ENDIAN:
		_simplInByteOrder = "<"
	else:
		_simplInByteOrder = ">"

#############################################################################

def setOutByteOrder(order):
	"""
	setOutByteOrder() sets the byte order on outgoing messages.
	"""
	global _simplOutByteOrder

	if order == SIMPL_NATIVE:
		_simplOutByteOrder = ""
	elif order == SIMPL_LITTLE_ENDIAN:
		_simplOutByteOrder = "<"
	else:
		_simplOutByteOrder = ">"

#############################################################################

def setInArch(arch):
	"""
	setInArch() sets the C variable sizes on incoming messages depending on
	32/64 bit architectures.
	"""
	global _simplIchar
	global _simplIshort
	global _simplIint
	global _simplIlong
	global _simplIfloat
	global _simplIdouble

	_simplIchar = 1
	_simplIshort = 2
	_simplIint = 4
	if arch == SIMPL_BIT_64:
		_simplIlong = 8
	else:
		_simplIlong = 4
	_simplIfloat = 4
	_simplIdouble = 8

#############################################################################

def setOutArch(arch):
	"""
	setOutArch() sets the C variable sizes on outgoing messages depending on
	32/64 bit architectures.
	"""
	global _simplOchar
	global _simplOshort
	global _simplOint
	global _simplOlong
	global _simplOfloat
	global _simplOdouble

	_simplOchar = 1
	_simplOshort = 2
	_simplOint = 4
	if arch == SIMPL_BIT_64:
		_simplOlong = 8
	else:
		_simplOlong = 4
	_simplOfloat = 4
	_simplOdouble = 8
	
#==============================================================
# Auxiliary functions needed by pack/unpack methods/functions
#==============================================================

def setInBuf(size, action):
	"""
	setInBuf() grows the incoming message buffer and increments the	incoming
	message buffer byte counter appropriately depending on the "action".

	Binary (_SIMPL_BIN) unpacks messages in a memory format C can understand.
	Character (_SIMPL_CHR) unpacks messages directly.
	Offset unpacks data at prescribed memory offsets.
	"""
	global _simplInCtr

	if action == SIMPL_BIN: # binary unpacking for the incoming message
		while _simplInCtr % size:
			_simplInCtr += 1
	elif action > 0: # offset unpacking for the incoming message
		while _simplInCtr < action:
			_simplInCtr += 1

#############################################################################

def setOutBuf(size, action):
	"""
	setOutBuf() grows the outgoing message buffer and increments the outgoing
	message buffer byte counter appropriately depending on the "action".

	Binary (_SIMPL_BIN) packs messages in a memory format C can understand.
	Character (_SIMPL_CHR) packs messages directly.
	Offset packs data at prescribed memory offsets.
	"""
	global _simplOutBuf
	global _simplOutCtr

	if action == SIMPL_BIN: # binary packing for the outgoing message
		while _simplOutCtr % size:
			if version > '3':
				_simplOutBuf += b"\000"
			else:
				_simplOutBuf += "\000"
			_simplOutCtr += 1
	elif action > 0: # offset packing for the outgoing message
		while _simplOutCtr < action:
			if version > '3':
				_simplOutBuf += b"\000"
			else:
				_simplOutBuf += "\000"
			_simplOutCtr += 1
	