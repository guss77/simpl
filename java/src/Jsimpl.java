public class Jsimpl
	{
	private static final int DEFAULT_SIZE = 1024;
	public final int BIN = -2;
	public final int CHR = -1;

	// sadly enums don't work too well for this app.
	private static final int BYTE = 0;
	private static final int CHAR = 1;
	private static final int SHORT = 2;
	private static final int INT = 3;
	private static final int LONG = 4;
	private static final int FLOAT = 5;
	private static final int DOUBLE = 6;

	// constructor 1 - run on defaults
	Jsimpl()
		{
		if (start(DEFAULT_SIZE, DEFAULT_SIZE) == -1)
			{
			System.out.println("start error");
			System.exit(-1);
			}
		}

	// constructor 2 - set everything needed
	Jsimpl(int iSize, int oSize)
		{
		if (start(iSize, oSize) == -1)
			{
			System.out.println("start error");
			System.exit(-1);
			}
		}

	// time gentlemen please ...
	protected void finalize()
		{
		nameDetach();
		end();
		}

	// various packing/unpacking utility methods
	public void reset()
		{
		resetCtrs();
		}

	public int getInBufferSize()
		{
		return( sizeInBuf() );
		}

	public int getOutBufferSize()
		{
		return( sizeOutBuf() );
		}

	public int getOutSizeAvailable()
		{
		return( sizeOutFree() );
		}

	/*
	packing methods
	*/

	// pack byte
	public int packByte(byte p, int offset)
		{
		return( packB(p, offset) );
		}

	// pack char
	public int packChar(char p, int offset)
		{
		return( packC(p, offset) );
		}

	// pack short
	public int packShort(short p, int offset)
		{
		return( packS(p, offset) );
		}

	// pack int
	public int packInt(int p, int offset)
		{
		return( packI(p, offset) );
		}

	// pack long
	public int packLong(long p, int offset)
		{
		return( packL(p, offset) );
		}

	// pack float
	public int packFloat(float p, int offset)
		{
		return( packF(p, offset) );
		}

	// pack double
	public int packDouble(double p, int offset)
		{
		return( packD(p, offset) );
		}

	// pack string
	public int packString(String p, int offset)
		{
		return( packStr(p, offset) );
		}

	// pack byte array
	public int packByteArray(byte[] p, int offset)
		{
		return( packArray(p, BYTE, offset) );
		}

	// pack char array
	public int packCharArray(char[] p, int offset)
		{
		return( packArray(p, CHAR, offset) );
		}

	// pack short array
	public int packShortArray(short[] p, int offset)
		{
		return( packArray(p, SHORT, offset) );
		}

	// pack int array
	public int packIntArray(int[] p, int offset)
		{
		return( packArray(p, INT, offset) );
		}

	// pack long array
	public int packLongArray(long[] p, int offset)
		{
		return( packArray(p, LONG, offset) );
		}

	// pack float array
	public int packFloatArray(float[] p, int offset)
		{
		return( packArray(p, FLOAT, offset) );
		}

	// pack double arrray
	public int packDoubleArray(double[] p, int offset)
		{
		return( packArray(p, DOUBLE, offset) );
		}

	/*
	unpacking methods
	*/

	// unpack byte
	public byte unpackByte(int offset)
		{
		return( unpackB(offset) );
		}

	// unpack char
	public char unpackChar(int offset)
		{
		return( unpackC(offset) );
		}

	// unpack short
	public short unpackShort(int offset)
		{
		return( unpackS(offset) );
		}

	// unpack int
	public int unpackInt(int offset)
		{
		return( unpackI(offset) );
		}

	// unpack long
	public long unpackLong(int offset)
		{
		return( unpackL(offset) );
		}
	
	// unpack float
	public float unpackFloat(int offset)
		{
		return( unpackF(offset) );
		}

	// unpack double
	public double unpackDouble(int offset)
		{
		return( unpackD(offset) );
		}

	// unpack string
	public String unpackString(int p, int offset)
		{
		return( unpackStr(p, offset) );
		}

	// unpack byte array
	public int unpackByteArray(byte[] p, int offset)
		{
		return( unpackArray(p, BYTE, offset) );
		}

	// unpack char array
	public int unpackCharArray(char[] p, int offset)
		{
		return( unpackArray(p, CHAR, offset) );
		}

	// unpack short array
	public int unpackShortArray(short[] p, int offset)
		{
		return( unpackArray(p, SHORT, offset) );
		}

	// unpack int array
	public int unpackIntArray(int[] p, int offset)
		{
		return( unpackArray(p, INT, offset) );
		}

	// unpack long array
	public int unpackLongArray(long[] p, int offset)
		{
		return( unpackArray(p, LONG, offset) );
		}

	// unpack float array
	public int unpackFloatArray(float[] p, int offset)
		{
		return( unpackArray(p, FLOAT, offset) );
		}

	// unpack double array
	public int unpackDoubleArray(double[] p, int offset)
		{
		return( unpackArray(p, DOUBLE, offset) );
		}

	// test for development of pack/unpack methods
	public static native void printTester(int type);

	// C functions underlying pack/unpack utility methods
	private native int start(int p, int q);
	private native void end();
	private native void resetCtrs();
	private native int sizeInBuf();
	private native int sizeOutBuf();
	private native int sizeOutFree();

	// C functions underlying pack methods
	private native int packB(byte p, int action);
	private native int packC(char p, int action);
	private native int packS(short p, int action);
	private native int packI(int p, int action);
	private native int packL(long p, int action);
	private native int packF(float p, int action);
	private native int packD(double p, int action);
	private native int packStr(String p, int action);
	private native int packArray(Object p, int type, int action);

	// C functions underlying unpack methods
	private native byte unpackB(int action);
	private native char unpackC(int action);
	private native short unpackS(int action);
	private native int unpackI(int action);
	private native long unpackL(int action);
	private native float unpackF(int action);
	private native double unpackD(int action);
	private native String unpackStr(int p, int action);
	private native int unpackArray(Object p, int type, int action);
	
	// SIMPL methods
	public native int nameAttach(String name);
	public native int nameDetach();
	public native int surDetach(int fd);
	public native int nameLocate(String name);
	public native int Send(int id);
	public native int Receive();
	public native int Reply(int sender);
	public native int Trigger(int id, int proxy);
	public native int whatsMyRecvfd();
	public native int returnProxy(int proxy);
	public native String whatsMyError();
	public native int getMsgSize(int sender);

	// get the SIMPL JNI library
	static
		{
		System.loadLibrary("jsimpl");
		}
	}
