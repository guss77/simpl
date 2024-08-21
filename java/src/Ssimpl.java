/*
This class allows a java program to send/receive messages to/from remote
programs via the SIMPL protocol using the tclSurrogate.

This entails the usual SIMPL functionality like name locate, Send, Receive etc.
as well as message constructing/deconstructing methods which provide a
convenient layer between the programmer and the nitty-gritty of messages
themselves. These methods pack/unpack the traditional java primitives as well as
Strings and the various arrays of primitives available.

There are two constructors available. The first runs on a set of default values.
The second allows all defaults to be changed. The values that are changeable
are:
1. the processor architecture,
2. the byte order,
3. the incoming message buffer size, and
4. the outgoing message buffer size.

The processor architecture refers to whether a CPU be 32-bit or 64-bit. This
can make a difference in the memory sizes of primitive java variables,
particularly the long. It is 4 bytes in size on a 32-bit platform while it is 8
bytes on a 64-bit. This is important when trying to pack/unpack variables
in/out of byte buffers. These byte buffers serve as the holding tanks for the
various incoming and outgoing messages.

The byte order refers to how the java primitives are stored in memory. This may
vary between different computers. In order to have messages that are sensible
to everyone concerned, the byte order may need to be set to some agreed upon
configuration.

The incoming message buffer refers to a byte buffer that is used to receive
incoming messages. The size of this buffer should be at least the size of the
largest expected incoming message.

Ditto the outgoing buffer and its size.

The incoming messages are deconstructed with the use of the unpack*() methods.
The outgoing messages are constructed with the aid of the pack*() methods.
*/

import java.net.*;
import java.nio.*;
import java.io.*;
import java.nio.channels.*;

public class Ssimpl
	{
	// SIMPL message token constants
	private static final short NAME_ATTACH = 0;
	private static final short NAME_DETACH = 1;
	private static final short NAME_LOCATE = 2;
	private static final short SEND_IT = 3;
	private static final short REPLY_IT = 4;
	private static final short RELAY_IT = 5;

	// buffer constants
	private static final int DEFAULT_SIZE = 1024;
	private static final int DEFAULT_ARCH = 64;

	// globally scoped variables
	private SocketChannel sChannel;
	private int inSize;
	private int outSize;
	private int inCtr;
	private int outCtr;
	private ByteBuffer inBuffer;
	private ByteBuffer outBuffer;
	private int msgSize;
	private int msgSender;
	private int nameAttachResult;

	// primitive variable memory sizes in bytes
	private int bSize;
	private int cSize;
	private int sSize;
	private int iSize;
	private int lSize;
	private int fSize;
	private int dSize;
	private int arch;
	private int addSize;
	private String byteOrder;

	// pack/unpack padding type
	public final int BIN = -2;
	public final int CHR = -1;

	// constructor 1 - run on defaults
	Ssimpl()
		{
		arch = DEFAULT_ARCH;
		byteOrder = "NATIVE";
		inSize = DEFAULT_SIZE;
		outSize = DEFAULT_SIZE;
		commonCon();
		}

	// constructor 2 - no defaults
	Ssimpl(int a, String b, int iSize, int oSize)
		{
		arch = a;
		byteOrder = b;
		inSize = iSize;
		outSize = oSize;
		commonCon();
		}

	// common constructor bits
	private void commonCon()
		{
		// set variable memory sizes in bytes
		bSize = 1;
		cSize = 2;
		sSize = 2;
		iSize = 4;
		if (arch == 64)
			{
			addSize = 8;
			lSize = 8;
			}
		else
			{
			addSize = 4;
			lSize = 4;
			}
		fSize = 4;
		dSize = 8;

		// the buffer used for receiving messages
		inCtr = 0;
		if (inSize > 0)
			{
			inBuffer = ByteBuffer.allocate(inSize);
			setByteOrder(inBuffer);
			inBuffer.clear();
			}

		// the buffer used for sending messages
		outCtr = 0;
		if (outSize > 0)
			{
			outBuffer = ByteBuffer.allocate(outSize);
			setByteOrder(outBuffer);
			outBuffer.clear();
			}

		// no received messages yet
		msgSize = 0;
		msgSender = -1;

		// no name attach until method is actually run
		nameAttachResult = -1;
		
		// time gentlemen please ...
		Runtime.getRuntime().addShutdownHook(new Thread()
			{
			public void run()
				{
      			nameDetach();
				}
			});
		}

	// various utility methods
	public void reset()
		{
		inCtr = 0;
		outCtr = 0;
		}

	public int getInBufferSize()
		{
		return(inSize);
		}

	public int getOutBufferSize()
		{
		return(outSize);
		}

	public int getOutSizeAvailable()
		{
		return(outSize - outCtr);
		}

	/************************************************************************
	packing methods
	************************************************************************/

	// pack byte
	public int packByte(byte p, int offset)
		{
		// buffer overshoot?
		if (bSize > outSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setOutCtr(bSize, bSize, offset) == -1)
				{
				return(-1);
				}
			}

		outBuffer.put(outCtr, p);
		outCtr += bSize;
		return(0);
		}

	// pack char
	public int packChar(char p, int offset)
		{
		// buffer overshoot?
		if (cSize > outSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setOutCtr(cSize, bSize, offset) == -1)
				{
				return(-1);
				}
			}

		outBuffer.putChar(outCtr, p);
		outCtr += cSize;
		return(0);
		}

	// pack short
	public int packShort(short p, int offset)
		{
		// buffer overshoot?
		if (sSize > outSize)
			{
			return(-1);
			}

		if (offset != CHR)
			{
			if (setOutCtr(sSize, sSize, offset) == -1)
				{
				return(-1);
				}
			}

		outBuffer.putShort(outCtr, p);
		outCtr += sSize;
		return(0);
		}

	// pack int
	public int packInt(int p, int offset)
		{
		// buffer overshoot?
		if (iSize > outSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setOutCtr(iSize, iSize, offset) == -1)
				{
				return(-1);
				}
			}

		outBuffer.putInt(outCtr, p);
		outCtr += iSize;
		return(0);
		}

	// pack long
	public int packLong(long p, int offset)
		{
		// buffer overshoot?
		if (lSize > outSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setOutCtr(lSize, lSize, offset) == -1)
				{
				return(-1);
				}
			}

		outBuffer.putLong(outCtr, p);
		outCtr += lSize;
		return(0);
		}

	// pack float
	public int packFloat(float p, int offset)
		{
		// buffer overshoot?
		if (fSize > outSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setOutCtr(fSize, fSize, offset) == -1)
				{
				return(-1);
				}
			}

		outBuffer.putFloat(outCtr, p);
		outCtr += fSize;
		return(0);
		}

	// pack double
	public int packDouble(double p, int offset)
		{
		// buffer overshoot?
		if (dSize > outSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setOutCtr(dSize, dSize, offset) == -1)
				{
				return(-1);
				}
			}

		outBuffer.putDouble(outCtr, p);
		outCtr += dSize;
		return(0);
		}

	// pack String
	public int packString(String p, int offset)
		{
		// buffer overshoot?
		if (p.length() > outSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setOutCtr(p.length(), bSize, offset) == -1)
				{
				return(-1);
				}
			}

		byte[] q = p.getBytes();
		for (int i = 0; i < p.length(); i++, outCtr += bSize)
			{
			outBuffer.put(outCtr, q[i]);
			}
		return(0);
		}

	// pack byte array
	public int packByteArray(byte[] p, int offset)
		{
		// buffer overshoot?
		if (p.length > outSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setOutCtr(p.length, bSize, offset) == -1)
				{
				return(-1);
				}
			}

		for (int i = 0; i < p.length; i++, outCtr += bSize)
			{
			outBuffer.put(outCtr, p[i]);
			}

		return(0);
		}

	// pack char array
	public int packCharArray(char[] p, int offset)
		{
		// buffer overshoot?
		if (p.length > outSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setOutCtr(p.length, cSize, offset) == -1)
				{
				return(-1);
				}
			}

		for (int i = 0; i < p.length; i++, outCtr += cSize)
			{
			outBuffer.putChar(outCtr, p[i]);
			}

		return(0);
		}

	// pack short array
	public int packShortArray(short[] p, int offset)
		{
		// buffer overshoot?
		if (p.length > outSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setOutCtr(p.length, sSize, offset) == -1)
				{
				return(-1);
				}
			}

		for (int i = 0; i < p.length; i++, outCtr += sSize)
			{
			outBuffer.putShort(outCtr, p[i]);
			}

		return(0);
		}

	// pack int array
	public int packIntArray(int[] p, int offset)
		{
		// buffer overshoot?
		if (p.length > outSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setOutCtr(p.length, iSize, offset) == -1)
				{
				return(-1);
				}
			}

		for (int i = 0; i < p.length; i++, outCtr += iSize)
			{
			outBuffer.putInt(outCtr, p[i]);
			}

		return(0);
		}

	// pack long array
	public int packLongArray(long[] p, int offset)
		{
		// buffer overshoot?
		if (p.length > outSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setOutCtr(p.length, lSize, offset) == -1)
				{
				return(-1);
				}
			}

		for (int i = 0; i < p.length; i++, outCtr += lSize)
			{
			outBuffer.putLong(outCtr, p[i]);
			}

		return(0);
		}

	// pack float array
	public int packFloatArray(float[] p, int offset)
		{
		// buffer overshoot?
		if (p.length > outSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setOutCtr(p.length, fSize, offset) == -1)
				{
				return(-1);
				}
			}

		for (int i = 0; i < p.length; i++, outCtr += fSize)
			{
			outBuffer.putFloat(outCtr, p[i]);
			}

		return(0);
		}

	// pack double array
	public int packDoubleArray(double[] p, int offset)
		{
		// buffer overshoot?
		if (p.length > outSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setOutCtr(p.length, dSize, offset) == -1)
				{
				return(-1);
				}
			}

		for (int i = 0; i < p.length; i++, outCtr += dSize)
			{
			outBuffer.putDouble(outCtr, p[i]);
			}

		return(0);
		}

	private int setOutCtr(int size, int primSize, int action)
		{
		// action == BIN or action = offset >= 0 only
		if (action == BIN) // pack automatically for C structure
			{
			int boundary = (primSize > addSize) ? addSize : primSize;
			for(; (outCtr % boundary) != 0; outCtr++);
			// check again for buffer overshoot
			if ( (outCtr + size) > inSize )
				{
				return(-1);
				}
			}
		else // pack at desired offset position
			{
			// what if the action is -ve but not BIN/CHR
			if (action < BIN)
				{
				return(-1);
				}

			// buffer overshoot?
			if ( (size + action) > outSize )
				{
				return(-1);
				}

			outCtr = action;
			}

		return(0);
		}

	/*************************************************************************
	unpacking methods
	*************************************************************************/

	// unpack byte
	public byte unpackByte(int offset)
		{
		// buffer overshoot?
		if (bSize > inSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setInCtr(bSize, bSize, offset) == -1)
				{
				return(-1);
				}
			}

		byte p = inBuffer.get(inCtr);
		inCtr += bSize;
		return(p);
		}

	// unpack char
	public char unpackChar(int offset)
		{
		// buffer overshoot?
		if (cSize > inSize)
			{
			return(0);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setInCtr(cSize, bSize, offset) == -1)
				{
				return(0);
				}
			}

		char p = inBuffer.getChar(inCtr);
		inCtr += cSize;
		return(p);
		}

	// unpack short
	public short unpackShort(int offset)
		{
		// buffer overshoot?
		if (sSize > inSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setInCtr(sSize, sSize, offset) == -1)
				{
				return(-1);
				}
			}

		short p = inBuffer.getShort(inCtr);
		inCtr += sSize;
		return(p);
		}

	// unpack int
	public int unpackInt(int offset)
		{
		// buffer overshoot?
		if (iSize > inSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setInCtr(iSize, iSize, offset) == -1)
				{
				return(-1);
				}
			}

		int p = inBuffer.getInt(inCtr);
		inCtr += iSize;
		return(p);
		}

	// unpack long
	public long unpackLong(int offset)
		{
		// buffer overshoot?
		if (lSize > inSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setInCtr(lSize, lSize, offset) == -1)
				{
				return(-1);
				}
			}

		long p = inBuffer.getLong(inCtr);
		inCtr += lSize;
		return(p);
		}

	// unpack float
	public float unpackFloat(int offset)
		{
		// buffer overshoot?
		if (fSize > inSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setInCtr(fSize, fSize, offset) == -1)
				{
				return(-1);
				}
			}

		float p = inBuffer.getFloat(inCtr);
		inCtr += fSize;
		return(p);
		}

	// unpack double
	public double unpackDouble(int offset)
		{
		// buffer overshoot?
		if (dSize > inSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setInCtr(dSize, dSize, offset) == -1)
				{
				return(-1);
				}
			}

		double p = inBuffer.getDouble(inCtr);
		inCtr += dSize;
		return(p);
		}

	// unpack String
	public String unpackString(int len, int offset)
		{
		// buffer overshoot?
		if (len > inSize)
			{
			return("");
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setInCtr(len, bSize, offset) == -1)
				{
				return("");
				}
			}

		byte[] q = new byte[len];
		for (int i = 0; i < len; i++, inCtr += bSize)
			{
			q[i] = inBuffer.get(inCtr);
			}
		String p = new String(q);
		return(p);
		}

	// unpack byte array
	public int unpackByteArray(byte[] p, int offset)
		{
		// buffer overshoot?
		if (p.length > inSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setInCtr(p.length, bSize, offset) == -1)
				{
				return(-1);
				}
			}

		for (int i = 0; i < p.length; i++, inCtr += bSize)
			{
			p[i] = inBuffer.get(inCtr);
			}

		return(0);
		}

	// unpack char array
	public int unpackCharArray(char[] p, int offset)
		{
		// buffer overshoot?
		if (p.length > inSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setInCtr(p.length, cSize, offset) == -1)
				{
				return(-1);
				}
			}

		for (int i = 0; i < p.length; i++, inCtr += cSize)
			{
			p[i] = inBuffer.getChar(inCtr);
			}

		return(0);
		}

	// unpack short array
	public int unpackShortArray(short[] p, int offset)
		{
		// buffer overshoot?
		if (p.length > inSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setInCtr(p.length, sSize, offset) == -1)
				{
				return(-1);
				}
			}

		for (int i = 0; i < p.length; i++, inCtr += sSize)
			{
			p[i] = inBuffer.getShort(inCtr);
			}

		return(0);
		}

	// unpack int array
	public int unpackIntArray(int[] p, int offset)
		{
		// buffer overshoot?
		if (p.length > inSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setInCtr(p.length, iSize, offset) == -1)
				{
				return(-1);
				}
			}

		for (int i = 0; i < p.length; i++, inCtr += iSize)
			{
			p[i] = inBuffer.getInt(inCtr);
			}

		return(0);
		}

	// unpack long array
	public int unpackLongArray(long[] p, int offset)
		{
		// buffer overshoot?
		if (p.length > inSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setInCtr(p.length, lSize, offset) == -1)
				{
				return(-1);
				}
			}

		for (int i = 0; i < p.length; i++, inCtr += lSize)
			{
			p[i] = inBuffer.getLong(inCtr);
			}

		return(0);
		}

	// unpack float array
	public int unpackFloatArray(float[] p, int offset)
		{
		// buffer overshoot?
		if (p.length > inSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setInCtr(p.length, fSize, offset) == -1)
				{
				return(-1);
				}
			}

		for (int i = 0; i < p.length; i++, inCtr += fSize)
			{
			p[i] = inBuffer.getFloat(inCtr);
			}

		return(0);
		}

	// unpack double array
	public int unpackDoubleArray(double[] p, int offset)
		{
		// buffer overshoot?
		if (p.length > inSize)
			{
			return(-1);
			}

		// binary or offset, not character
		if (offset != CHR)
			{
			if (setInCtr(p.length, dSize, offset) == -1)
				{
				return(-1);
				}
			}

		for (int i = 0; i < p.length; i++, inCtr += dSize)
			{
			p[i] = inBuffer.getDouble(inCtr);
			}

		return(0);
		}

	private int setInCtr(int size, int primSize, int action)
		{
		// action == BIN or action = offset >= 0 only
		if (action == BIN) // unpack automatically for C structure
			{
			int boundary = (primSize > addSize) ? addSize : primSize;
			for(; (inCtr % boundary) != 0; inCtr++);
			// check again for buffer overshoot
			if ( (inCtr + size) > inSize )
				{
				return(-1);
				}
			}
		else // unpack at desired offset position
			{
			// what if the action is -ve but not BIN/CHR
			if (action < BIN)
				{
				return(-1);
				}

			// buffer overshoot?
			if ( (size + action) > inSize )
				{
				return(-1);
				}

			inCtr = action;
			}

		return(0);
		}

	public void bufCpy()
		{
		byte p;

		for (int i = 0; i < outCtr; i++)
			{
			p = outBuffer.get(i);
			inBuffer.put(i, p);
			}
		}

	/***********************************************************************
	SIMPL communication methods
	***********************************************************************/
	/*
	nameAttach() creates a socket connection to tclSurrogate on a remote host
	and registers its name with that host for SIMPL communication to ensue by
	sending a NAME_ATTACH message.
	*/

	public int nameAttach(int port, String host, String name)
		{
		try
			{
			// connect channel to the appropriate socket
			sChannel = SocketChannel.open();
			sChannel.connect( new InetSocketAddress(host, port) );
			}
		catch(IOException e)
			{
			System.out.println("nameAttach: " + e.getMessage());
			return(-1);
			}

		// size of outgoing message header
		short oMsgHdrSize = (short) (sSize << 1);
		// size of the outgoing message body
		short oMsgBodySize = (short)( (iSize << 1) + 20 * bSize );
		// the total message size
		int oMsgSize = oMsgHdrSize + oMsgBodySize;

		// allocate a byte buffer for the outgoing message
		ByteBuffer out = ByteBuffer.allocate(oMsgSize);

		// set the desired byte order
		setByteOrder(out);

		// compose the header of name attach message
		out.putShort(NAME_ATTACH);
		out.putShort(oMsgBodySize);

		// compose the body of name attach message
		out.putInt(-1);
		byte[] myName = name.getBytes();
		for (int i = 0; i < 20; i++)
			{
			if (i < name.length())
				{
				out.put(myName[i]);
				}
			else
				{
				out.put((byte)0);
				}
			}
		out.putInt(-1);

		// write the name attach message to the channel
		try
			{
			// write from the start of the message buffer
			out.position(0);
			// write out the message
			sChannel.write(out);
			}
		catch(IOException e)
			{
			System.out.println("nameAttach: " + e.getMessage());
			return(-1);
			}

		// calculate the size of the incoming message
		int iMsgSize = (sSize << 1) + (3 * iSize) + (20 * bSize);
		// allocate a byte buffer for the outgoing message
		ByteBuffer in = ByteBuffer.allocate(iMsgSize);

		// set the desired byte order
		setByteOrder(in);

		// read response from tclSurrogate
		try
			{
			// read into the start of the message buffer
			in.position(0);
			// read in the reply message
			sChannel.read(in);
			}
		catch(IOException e)
			{
			System.out.println("nameAttach: " + e.getMessage());
			return(-1);
			}

		// get and check the incoming token value
		short inToken = in.getShort(0);
		if (inToken != REPLY_IT)
			{
			System.out.println("nameAttach: Reply error");
			return(-1);
			}

		// calculate the offset to the return code within the message
		int offset = (sSize << 1) + iSize + (20 * bSize);

		// retrieve the return code from the message
		nameAttachResult = in.getInt(offset);

		return(nameAttachResult);
		}

	//#######################################################################

	/*
	nameDetach() composes the name detach message to be sent to tclSurrogate
	which concludes any further SIMPL communication
	*/
	public int nameDetach()
		{
		if (nameAttachResult == -1)
			{
			return(-1);
			}

		// the message size
		int oMsgSize = (sSize << 1);

		// allocate a byte buffer for the outgoing message
		ByteBuffer out = ByteBuffer.allocate(oMsgSize);

		// set the desired byte order
		setByteOrder(out);

		// compose the name detach message
		out.putShort(NAME_DETACH);
		out.putShort((short)0);

		// write the name attach message to the channel
		try
			{
			// start of message buffer
			out.position(0);
			// write out the message
			sChannel.write(out);
			// close the channel
			sChannel.close();
			}
		catch(IOException e)
			{
			System.out.println("nameDetach: " + e.getMessage());
			return(-1);
			}

		nameAttachResult = -1;

		return(0);
		}

	//#######################################################################

	/*
	nameLocate() composes the name locate message to be sent to tclSurrogate
	so that SIMPL communications can be set up between the calling program and
	the remotely "named" program
	*/
	public int nameLocate(String name)
		{
		// size of outgoing message header
		short oMsgHdrSize = (short) (sSize << 1);
		// size of the outgoing message body
		short oMsgBodySize = (short)( (iSize << 1) + 20 * bSize );
		// the total message size
		int oMsgSize = oMsgHdrSize + oMsgBodySize;

		// allocate a byte buffer for the outgoing message
		ByteBuffer out = ByteBuffer.allocate(oMsgSize);

		// set the desired byte order
		setByteOrder(out);

		// compose the header of name attach message
		out.putShort(NAME_LOCATE);
		out.putShort(oMsgBodySize);

		// compose the body of name attach message
		out.putInt(-1);
		byte[] thatName = name.getBytes();
		for (int i = 0; i < 20; i++)
			{
			if (i < name.length())
				{
				out.put(thatName[i]);
				}
			else
				{
				out.put((byte)0);
				}
			}
		out.putInt(-1);

		// write the name attach message to the channel
		try
			{
			// write from the start of the message buffer
			out.position(0);
			// write out the message
			sChannel.write(out);
			}
		catch(IOException e)
			{
			System.out.println("nameLocate: " + e.getMessage());
			return(-1);
			}

		// calculate the size of the incoming message
		int iMsgSize = (sSize << 1) + (iSize << 1) + (20 * bSize);
		// allocate a byte buffer for the outgoing message
		ByteBuffer in = ByteBuffer.allocate(iMsgSize);

		// set the desired byte order
		setByteOrder(in);

		// read response from tclSurrogate
		try
			{
			// read into the start of the message buffer
			in.position(0);
			// read in the reply message
			sChannel.read(in);
			}
		catch(IOException e)
			{
			System.out.println("nameLocate: " + e.getMessage());
			return(-1);
			}

		// get and check the incoming token value
		short inToken = in.getShort(0);
		if (inToken != REPLY_IT)
			{
			System.out.println("nameLocate: Reply error");
			return(-1);
			}

		//calculate the offset to the return code within the message
		int offset = (sSize << 1) + iSize + (20 * bSize);

		// retrieve the return code from the message
		return( in.getInt(offset) );
		}

	//#######################################################################

	/*
	Send() writes a message to the remote surrogate which then relays on the
	message to the appropriate remote receiver.
	*/
	public int Send(int id)
		{
		int numRead = 0;

		inCtr = 0;

		// size of first part of outgoing message
		short frontSize = (short) ( (sSize << 1) + iSize);

		// allocate a byte buffer for the outgoing message
		ByteBuffer front = ByteBuffer.allocate(frontSize);

		// set the desired byte order
		setByteOrder(front);

		// compose the front end of the message
		front.putShort(SEND_IT);
		front.putShort((short)(iSize + outCtr));
		front.putInt(id);

		// write the front end of the message to the channel
		try
			{
			// write from the start of the buffer
			front.position(0);
			// write out the front end of the message
			sChannel.write(front);
			// is there a message to send?
			if (outCtr > 0)
				{
				writeMsg();
				outCtr = 0;
				}
			}
		catch(IOException e)
			{
			System.out.println("Send: " + e.getMessage());
			return(-1);
			}

		// read response from tclSurrogate
		try
			{
			// read into the front buffer
			front.position(0);
			// read in the front part of the reply message
			sChannel.read(front);
			}
		catch(IOException e)
			{
			System.out.println("Send: " + e.getMessage());
			return(-1);
			}

		// get and check the incoming token value
		short inToken = front.getShort(0);
		if (inToken != REPLY_IT)
			{
			System.out.println("Send: reply token error");
			return(-1);
			}

		// what is the size of the actual reply
		short amount = front.getShort(sSize);
		amount -= iSize;

		// check for adequate memory
		if (amount > inSize)
			{
			System.out.println("Send: reply message too large for buffer");
			return(-1);
			}

		// if there is a message
		if (amount > 0)
			{
			try
				{
				// read balance of message into the reply buffer
				inBuffer.position(0);
				numRead = sChannel.read(inBuffer);
				}
			catch(IOException e)
				{
				System.out.println("Send: " + e.getMessage());
				return(-1);
				}
			}

		return(numRead);
		}

	//#######################################################################

	/*
	Receive() reads messages from a remote sender via the remote surrogate.
	*/
	public int Receive()
		{
		int senderId = -1;

		inCtr = 0;

		// size of first part of incoming message
		short frontSize = (short) ( (sSize << 1) + iSize);

		// allocate a byte buffer for the incoming message
		ByteBuffer front = ByteBuffer.allocate(frontSize);

		// set the desired byte order
		setByteOrder(front);

		// read the front part of the message
		try
			{
			// read front part of message
			front.position(0);
			sChannel.read(front);
			}
		catch(IOException e)
			{
			System.out.println("Receive: " + e.getMessage());
			return(-1);
			}

		// get and check the incoming token value
		short inToken = front.getShort(0);
		if (inToken == 0)
			{
			System.exit(0);
			}
		if (inToken != RELAY_IT)
			{
			System.out.println("Receive token incorrect");
			return(-1);
			}

		// what is the size of the actual message/trigger value?
		int value = (int)front.getShort(sSize);

		// is this a proxy value?
		if (value < -1)
			{
			// return the proxy value
			return(value);
			}

		// this is a message of some sort
		value -= iSize;

		// check for adequate memory
		if (value > inSize)
			{
			// return failure through sender id
			System.out.println("Receive: message too large for buffer");
			return(-1);
			}

		// if there is a message body
		if (value > 0)
			{
			// what is the sender id?
			senderId = front.getInt( (sSize << 1) );
			msgSender = senderId;

			try
				{
				// read balance of message into the receive buffer
				inBuffer.position(0);
				msgSize = sChannel.read(inBuffer);
				}
			catch(IOException e)
				{
				System.out.println("Receive: " + e.getMessage());
				return(-1);
				}
			}

		return(senderId);
		}

	//#######################################################################

	/*
	Reply() responds back to a sender's remote surrogate.
	*/
	public int Reply(int sender)
		{
		// size of first part of outgoing message
		short frontSize = (short)((sSize << 1) + iSize);

		// allocate a byte buffer for the outgoing message
		ByteBuffer front = ByteBuffer.allocate(frontSize);

		// set the desired byte order
		setByteOrder(front);

		// compose the front end of the message
		front.putShort(REPLY_IT);
		front.putShort((short)(iSize + outCtr));
		front.putInt(sender);

		// write the front end of the message to the channel
		try
			{
			// write from the start of the buffer
			front.position(0);
			// write out the front end of the message
			sChannel.write(front);
			// is there a reply
			if (outCtr > 0)
				{
				writeMsg();
				outCtr = 0;
				}
			}
		catch(IOException e)
			{
			System.out.println("Reply: " + e.getMessage());
			return(-1);
			}

		return(0);
		}

	//#######################################################################

	/*
	for use with receiving proxies when the surrogate is able to handle them
	*/
	public int returnProxy(int value)
		{
		return (value * -1) - 1;
		}

	//#######################################################################

	/*
	for use after receiving a message
	*/
	public int getMsgSize(int sender)
		{
		// must be the last message received
		if (sender == msgSender)
			{
			return(msgSize);
			}
		else
			{
			return(-1);
			}
		}

	//#######################################################################

	private void setByteOrder(ByteBuffer p)
		{
		if (byteOrder == "BIG_ENDIAN")
			{
			p.order(ByteOrder.BIG_ENDIAN);
			}
		else if (byteOrder == "LITTLE_ENDIAN")
			{
			p.order(ByteOrder.LITTLE_ENDIAN);
			}
		else
			{
			p.order(ByteOrder.nativeOrder());
			}
		//System.out.println("byte order=" + p.order());
		}

	//#######################################################################

	private int writeMsg()
		{
		// allocate a buffer based on the actual size of the outgoing message
		ByteBuffer buf = ByteBuffer.allocate(outCtr);
		setByteOrder(buf);
		buf.clear();

		// load the temporary buffer from the output buffer
		for (int i = 0; i < outCtr; i++)
			{
			buf.put(outBuffer.get(i));
			}

		try
			{
			// write from the start of the buffer
			buf.position(0);
			// write the message
			sChannel.write(buf);
			}
		catch(IOException e)
			{
			System.out.println("writeMsg: " + e.getMessage());
			return(-1);
			}

		return(0);
		}
	}