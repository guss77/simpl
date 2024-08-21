"""
wssimpl.py

wrapper-surrogate Simpl

contains wrapped calls to ssimpl in conjunction with convenient
packing/unpacking routines w.r.t. C type data items.
"""

#import required modules
import struct
import ssimpl

# global constants
BIN = -2
CHR = -1
NATIVE = 0
LITTLE_ENDIAN = 1
LENDIAN = 1
BIG_ENDIAN = 2
BENDIAN = 2
BIT_64 = 64
B64 = 64
BIT_32 = 32
B32 = 32

# for incoming messages
global inBuffer
global inCtr
global maxIn

# for outgoing messages
global outBuffer
global outCtr

# for 32/64-bit architectures
global iChar
global iShort
global iInt
global iLong
global iFloat
global iDouble

global oChar
global oShort
global oInt
global oLong
global oFloat
global oDouble

# byte order
global inByteOrder
global outByteOrder

class Simpl:
	# constructor
	def __init__(self):
		# available constants for packing/unpacking
		self.BIN = BIN
		self.CHR = CHR

		# available constants for cpu architecture
		self.BIT_64 = BIT_64
		self.B64 = BIT_64
		self.BIT_32 = BIT_32
		self.B32 = BIT_32

		# available constants for byte ordering
		self.NATIVE = NATIVE
		self.LITTLE_ENDIAN = LITTLE_ENDIAN
		self.LENDIAN = LITTLE_ENDIAN
		self.BIG_ENDIAN = BIG_ENDIAN
		self.BENDIAN = BIG_ENDIAN
	#==============================================================
	# packing methods
	#==============================================================
	
	# pack a char (single character string in Python)
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

	def packCharArray(self, p, action):
		packCharArray(p, action)

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

	def unpackString(self, i, action):
		return unpackString(i, action)

	def unpackCharArray(self, p, action):
		return unpackCharArray(p, action)

	def unpackShortArray(self, p, action):
		return unpackShortArray(p, action)

	def unpackIntArray(self, p, action):
		return unpackIntArray(p, action)

	def unpackLongArray(self, p, action):
		return unpackLongArray(p, action)

	def unpackFloatArray(self, p, action):
		return unpackFloatArray(p, action)

	def unpackDoubleArray(self, p, action):
		return unpackDoubleArray(p, action)
		
	#==============================================================
	# other methods
	#==============================================================

	def initialize(self, maxBufferSize):
		initialize(maxBufferSize)

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

	#==============================================================
	# SIMPL methods
	#==============================================================
	
	def nameAttach(self, phn, maxMemSize):
		return nameAttach(phn, maxMemSize)

	def nameDetach(self):
		return nameDetach()

	def nameLocate(self, name):
		return nameLocate(name)

	def send(self, receiverId):
		return send(receiverId)

	def receive(self):
		return receive()

	def reply(self, senderId):
		return reply(senderId)

	def whatsMyError(self):
		return whatsMyError()
		
	def returnProxy(self, value):
		return returnProxy(value)
#==============================================================
# packing methods
#==============================================================
	
# pack a char (single character string in Python)
def packChar(p, action):
	global outBuffer
	global outCtr
	setOutCtr(oChar, action)
	outBuffer += struct.pack("c", p)
	outCtr += oChar
		
def packShort(p, action):
	global outBuffer
	global outCtr
	setOutCtr(oShort, action)
	format = outByteOrder + "h"
	outBuffer += struct.pack(format, p)
	outCtr += oShort
		
def packInt(p, action):
	global outBuffer
	global outCtr
	setOutCtr(oInt, action)
	format = outByteOrder + "i"
	outBuffer += struct.pack(format, p)
	outCtr += oInt
			
def packLong(p, action):
	global outBuffer
	global outCtr
	setOutCtr(oLong, action)
	format = outByteOrder + "l"
	outBuffer += struct.pack(format, p)
	outCtr += oLong
			
def packFloat(p, action):
	global outBuffer
	global outCtr
	setOutCtr(oFloat, action)
	format = outByteOrder + "f"
	outBuffer += struct.pack(format, p)
	outCtr += oFloat
				
def packDouble(p, action):
	global outBuffer
	global outCtr
	setOutCtr(oDouble, action)
	format = outByteOrder + "d"
	outBuffer += struct.pack(format, p)
	outCtr += oDouble
				
def packString(p, action):
	global outBuffer
	global outCtr
	setOutCtr(oChar, action)
	outBuffer += struct.pack(str(len(p)) + "s", p)
	outCtr += len(p)

def packCharArray(p, action):
	global outBuffer
	global outCtr
	setOutCtr(oChar, action)
	for i in range(len(p)):
		outBuffer += struct.pack("c", p[i])
	outCtr += (len(p) * oChar)

def packShortArray(p, action):
	global outBuffer
	global outCtr
	setOutCtr(oShort, action)
	format = outByteOrder + "h"
	for i in range(len(p)):
		outBuffer += struct.pack(format, p[i])
	outCtr += (len(p) * oShort)

def packIntArray(p, action):
	global outBuffer
	global outCtr
	setOutCtr(oInt, action)
	format = outByteOrder + "i"
	for i in range(len(p)):
		outBuffer += struct.pack(format, p[i])
	outCtr += (len(p) * oInt)

def packLongArray(p, action):
	global outBuffer
	global outCtr
	setOutCtr(oLong, action)
	format = outByteOrder + "l"
	for i in range(len(p)):
		outBuffer += struct.pack(format, p[i])
	outCtr += (len(p) * oLong)

def packFloatArray(p, action):
	global outBuffer
	global outCtr
	setOutCtr(oFloat, action)
	format = outByteOrder + "f"
	for i in range(len(p)):
		outBuffer += struct.pack(format, p[i])
	outCtr += (len(p) * oFloat)

def packDoubleArray(p, action):
	global outBuffer
	global outCtr
	setOutCtr(oDouble, action)
	format = outByteOrder + "d"
	for i in range(len(p)):
		outBuffer += struct.pack(format, p[i])
	outCtr += (len(p) * oDouble)

#==============================================================
# unpacking methods
#==============================================================

def unpackChar(action):
	global inCtr
	setInCtr(iChar, action)
	end = inCtr + iChar
	t = struct.unpack("c", inBuffer[inCtr:end])
	inCtr += iChar
	return t[0]

def unpackShort(action):
	global inCtr
	setInCtr(iShort, action)
	format = inByteOrder + "h"
	end = inCtr + iShort
	t = struct.unpack(format, inBuffer[inCtr:end])
	inCtr += iShort
	return t[0]

def unpackInt(action):
	global inCtr
	setInCtr(iInt, action)
	format = inByteOrder + "i"
	end = inCtr + iInt
	t = struct.unpack(format, inBuffer[inCtr:end])
	inCtr += iInt
	return t[0]

def unpackLong(action):
	global inCtr
	setInCtr(iLong, action)
	format = inByteOrder + "l"
	end = inCtr + iLong
	t = struct.unpack(format, inBuffer[inCtr:end])
	inCtr += iLong
	return t[0]

def unpackFloat(action):
	global inCtr
	setInCtr(iFloat, action)
	format = inByteOrder + "f"
	end = inCtr + iFloat
	t = struct.unpack(format, inBuffer[inCtr:end])
	inCtr += iFloat
	return t[0]

def unpackDouble(action):
	global inCtr
	setInCtr(iDouble, action)
	format = inByteOrder + "d"
	end = inCtr + iDouble
	t = struct.unpack(format, inBuffer[inCtr:end])
	inCtr += iDouble
	return t[0]

def unpackString(i, action):
	global inCtr
	setInCtr(iChar, action)
	end = inCtr + i
	t = struct.unpack(str(i) + "s", inBuffer[inCtr:end])
	inCtr += i
	return t[0]

def unpackCharArray(p, action):
	global inCtr
	setInCtr(iChar, action)
	for i in range(len(p)):
		end = inCtr + iChar
		t = struct.unpack("c", inBuffer[inCtr:end])
		p[i] = t[0]
		inCtr += iChar

def unpackShortArray(p, action):
	global inCtr
	setInCtr(iShort, action)
	format = inByteOrder + "h"
	for i in range(len(p)):
		end = inCtr + iShort
		t = struct.unpack(format, inBuffer[inCtr:end])
		p[i] = t[0]
		inCtr += iShort

def unpackIntArray(p, action):
	global inCtr
	setInCtr(iInt, action)
	format = inByteOrder + "i"
	for i in range(len(p)):
		end = inCtr + iInt
		t = struct.unpack(format, inBuffer[inCtr:end])
		p[i] = t[0]
		inCtr += iInt

def unpackLongArray(p, action):
	global inCtr
	setInCtr(iLong, action)
	format = inByteOrder + "l"
	for i in range(len(p)):
		end = inCtr + iLong
		t = struct.unpack(format, inBuffer[inCtr:end])
		p[i] = t[0]
		inCtr += iLong

def unpackFloatArray(p, action):
	global inCtr
	setInCtr(iFloat, action)
	format = inByteOrder + "f"
	for i in range(len(p)):
		end = inCtr + iFloat
		t = struct.unpack(format, inBuffer[inCtr:end])
		p[i] = t[0]
		inCtr += iFloat

def unpackDoubleArray(p, action):
	global inCtr
	setInCtr(iDouble, action)
	format = inByteOrder + "d"
	for i in range(len(p)):
		end = inCtr + iDouble
		t = struct.unpack(format, inBuffer[inCtr:end])
		p[i] = t[0]
		inCtr += iDouble

#==============================================================
# other methods
#==============================================================

def initialize(maxBufferSize):
	# incoming message buffer variables
	global inCtr
	inCtr = 0
	global maxIn
	maxIn = maxBufferSize

	# outgoing message buffer variables
	global outCtr
	outCtr = 0
	global outBuffer
	outBuffer = ""

	# data sizes in bytes
	global iChar
	iChar = struct.calcsize("b")
	global iShort
	iShort = struct.calcsize("h")
	global iInt
	iInt = struct.calcsize("i")
	global iLong
	iLong = struct.calcsize("l")
	global iFloat
	iFloat = struct.calcsize("f")
	global iDouble
	iDouble = struct.calcsize("d")
		
	global oChar
	oChar = struct.calcsize("b")
	global oShort
	oShort = struct.calcsize("h")
	global oInt
	oInt = struct.calcsize("i")
	global oLong
	oLong = struct.calcsize("l")
	global oFloat
	oFloat = struct.calcsize("f")
	global oDouble
	oDouble = struct.calcsize("d")

	# byte ordering - native by default
	global inByteOrder
	inByteOrder = ""
	global outByteOrder
	outByteOrder = ""

def reset():
	# incoming message buffer variables
	global inBuffer
	inBuffer = ""
	global inCtr
	inCtr = 0
	global listCtr
	listCtr = 0
	# outgoing message buffer variables
	global outBuffer
	outBuffer = ""
	global outCtr
	outCtr = 0

def crossCopy():
	global inBuffer
	inBuffer = outBuffer

def returnInBuffer():
	return inBuffer

def returnOutBuffer():
	return outBuffer

def setInByteOrder(order):
	global inByteOrder
	if order == NATIVE:
		inByteOrder = ""
	elif order == LITTLE_ENDIAN:
		inByteOrder = "<"
	else:
		inByteOrder = ">"

def setOutByteOrder(order):
	global outByteOrder
	if order == NATIVE:
		outByteOrder = ""
	elif order == LITTLE_ENDIAN:
		outByteOrder = "<"
	else:
		outByteOrder = ">"

def setInArch(arch):
	global iChar
	iChar = 1
	global iShort
	iShort = 2
	global iInt
	iInt = 4
	global iLong
	if arch == BIT_64:
		iLong = 8
	else:
		iLong = 4
	global iFloat
	iFloat = 4
	global iDouble
	iDouble = 8
	
def setOutArch(arch):
	global oChar
	oChar = 1
	global oShort
	oShort = 2
	global oInt
	oInt = 4
	global oLong
	if arch == BIT_64:
		oLong = 8
	else:
		oLong = 4
	global oFloat
	oFloat = 4
	global oDouble
	oDouble = 8

#==============================================================
# SIMPL methods
#==============================================================

def nameAttach(phn, maxMemSize):
	initialize(maxMemSize)
	ret = ssimpl.nameAttach(phn)
	return ret

def nameDetach():
	ret = ssimpl.nameDetach()
	return ret

def nameLocate(name):
	ret = ssimpl.nameLocate(name)
	return ret

def send(receiverId):
	global inBuffer
	global inCtr
	global outBuffer
	global outCtr
	inBuf = "\000" * maxIn
	inCtr = 0
	ret, inBuffer = ssimpl.send(receiverId, outBuffer)
	outBuffer = ""
	outCtr = 0
	return ret

def receive():
	global inBuffer
	global inCtr
	inBuffer = ""
	inCtr = 0
	messageSize, senderId, inBuffer = ssimpl.receive()
	return messageSize, senderId
		
def reply(senderId):
	global outBuffer
	global outCtr
	ret = ssimpl.reply(senderId, outBuffer)
	outBuffer = ""
	outCtr = 0
	return ret

def whatsMyError():
	ret = ssimpl.whatsMyError()
	return ret
	
def returnProxy(value):
	ret = ssimpl.returnProxy(value)
	return ret

#==============================================================
# Auxiliary methods needed by pack/unpack
#==============================================================

def setOutCtr(size, action):
	global outBuffer
	global outCtr
	if action == BIN:
		while outCtr % size:
			outBuffer += "\000"
			outCtr += 1
	elif action > 0:
		while outCtr < action:
			outBuffer += "\000"
			outCtr += 1

def setInCtr(size, action):
	global inCtr
	if action == BIN:
		while inCtr % size:
			inCtr += 1
	elif action > 0:
		while inCtr < action:
			inCtr += 1
