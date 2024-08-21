/*
for testing the pack/upnpack procedures only in the Offset mode
*/

class PackStest3
	{
	public static void main(String arg[])
		{
		int ret = -1;

		System.out.println("\n******************************************");
		System.out.println("out buffer memory packing starts here");
		System.out.println("******************************************");

		// simpl object constructor
		Ssimpl simpl = new Ssimpl();
		//Ssimpl simpl = new Ssimpl(512, 512);

		ret = simpl.getInBufferSize();
		System.out.println("inSize=" + ret);
		ret = simpl.getOutBufferSize();
		System.out.println("outSize=" + ret);
		ret = simpl.getOutSizeAvailable();
		System.out.println("available=" + ret);

		// pack a chunk of memory in C structure mode
		short a = 1;
		ret = simpl.packShort(a, 5);
		if (ret == -1)
			{
			System.out.println("a error");
			System.exit(0);
			}
		System.out.println("a=" + a);

		byte b = 80;
		ret = simpl.packByte(b, 10);
		System.out.println("b=" + b);

		byte c = 81;
		ret = simpl.packByte(c, 15);
		System.out.println("c=" + c);

		double d = 4;
		ret = simpl.packDouble(d, 20);
		System.out.println("d=" + d);

		byte e = 82;
		ret = simpl.packByte(e, 30);
		System.out.println("e=" + e);

		long f = 6;
		ret = simpl.packLong(f, 35);
		System.out.println("f=" + f);

		byte g = 83;
		ret = simpl.packByte(g, 45);
		System.out.println("g=" + g);

		char h = 66;
		ret = simpl.packChar(h, 50);
		System.out.println("h=" + h);

		String z = "We are the knights who say nee!";
		ret = simpl.packString(z, 55);
		System.out.println("z=" + z);

		short i = 8;
		ret = simpl.packShort(i, 90);
		System.out.println("i=" + i);

		int j = 9;
		ret = simpl.packInt(j, 95);
		System.out.println("j=" + j);

		long k = 10;
		ret = simpl.packLong(k, 100);
		System.out.println("k=" + k);

		float l = 11F;
		ret = simpl.packFloat(l, 110);
		System.out.println("l=" + l);

		char m = 77;
		ret = simpl.packChar(m, 115);
		System.out.println("m=" + m);

		long n = 5;
		ret = simpl.packLong(n, 120);
		System.out.println("n=" + n);

		String o = "We";
		ret = simpl.packString(o, 130);
		System.out.println("o=" + o);

		//abcdefghij
		byte[] p = {97,98,99,100,101,102,103,104,105,106};
		ret = simpl.packByteArray(p, 135);
		System.out.println("p=" +p[0]+"..."+p[9]);

		char[] q = {66, 67, 68};
		ret = simpl.packCharArray(q, 150);
		System.out.println("q=" +q[0]+","+q[1]+","+q[2]);

		short[] r = {50, 51, 52, 53, 54, 55, 56};
		ret = simpl.packShortArray(r, 160);
		System.out.println("r=" +r[0]+"..."+r[6]);

		int[] s = {201, 301, 401, 501, 601};
		ret = simpl.packIntArray(s, 180);
		System.out.println("s=" +s[0]+"..."+s[4]);

		long[] t = {-201, -301, -401, -501, -601};
		ret = simpl.packLongArray(t, 200);
		System.out.println("t=" +t[0]+"..."+t[4]);

		float[] u = {10000F, 20000F, 30000F};
		ret = simpl.packFloatArray(u, 240);
		System.out.println("u=" +u[0]+","+u[1]+","+u[2]);

		double[] v = {-200, -100, 0, 100, 200};
		ret = simpl.packDoubleArray(v, 255);
		System.out.println("v=" +v[0]+"..."+v[4]);

		ret = simpl.getOutSizeAvailable();
		System.out.println("available=" + ret);

		System.out.println("******************************************");
		System.out.println("out buffer memory packing stops here");
		System.out.println("******************************************\n");

		// copy outBuffer contents to inBuffer for testing
		simpl.bufCpy();
	
		/************************************************************
		memcpy(inBuffer, outBuffer, 1024) is in printTester() so that
		the pack/unpack can be tested here. outBuffer is loaded
		according to the pack*() and inBuffer is unloaded according to
		the unpack*() calls.
		**************************************************************/

		System.out.println("\n******************************************");
		System.out.println("in buffer memory unpacking starts here");
		System.out.println("******************************************");

		// unpack a chunk of memory
		short A = simpl.unpackShort(5);
		System.out.println("A=" + A);

		byte B = simpl.unpackByte(10);
		System.out.println("B=" + B);

		byte C = simpl.unpackByte(15);
		System.out.println("C=" + C);

		double D = simpl.unpackDouble(20);
		System.out.println("D=" + D);

		byte E = simpl.unpackByte(30);
		System.out.println("E=" + E);

		long F = simpl.unpackLong(35);
		System.out.println("F=" + F);

		byte G = simpl.unpackByte(45);
		System.out.println("G=" + G);

		char H = simpl.unpackChar(50);
		System.out.println("H=" + H);

		int len = 31;
		String Z = simpl.unpackString(len, 55);
		System.out.println("Z=" + Z);

		short I = simpl.unpackShort(90);
		System.out.println("I=" + I);

		int J = simpl.unpackInt(95);
		System.out.println("J=" + J);

		long K = simpl.unpackLong(100);
		System.out.println("K=" + K);

		float L = simpl.unpackFloat(110);
		System.out.println("L=" + L);

		char M = simpl.unpackChar(115);
		System.out.println("M=" + M);

		long N = simpl.unpackLong(120);
		System.out.println("N=" + N);

		len = 2;
		String O = simpl.unpackString(len, 130);
		System.out.println("O=" + O);

		byte[] P = {0,1,2,3,4,5,6,7,8,9};
		ret = simpl.unpackByteArray(P, 135);
		System.out.println("P=" +P[0]+"..."+P[9]);

		char[] Q = {0, 1, 2};
		ret = simpl.unpackCharArray(Q, 150);
		System.out.println("Q=" +Q[0]+","+Q[1]+","+Q[2]);

		short[] R = {0, 1, 2, 3, 4, 5, 6};
		ret = simpl.unpackShortArray(R, 160);
		System.out.println("R=" +R[0]+"..."+R[6]);

		int[] S = {0, 1, 2, 3, 4};
		ret = simpl.unpackIntArray(S, 180);
		System.out.println("S=" +S[0]+"..."+S[4]);

		long[] T = {-1, -2, -3, -4, -5};
		ret = simpl.unpackLongArray(T, 200);
		System.out.println("T=" +T[0]+"..."+T[4]);

		float[] U = {1F, 2F, 3F};
		ret = simpl.unpackFloatArray(U, 240);
		System.out.println("U=" +U[0]+","+U[1]+","+U[2]);

		double[] V = {-2, -1, 0, 1, 2};
		ret = simpl.unpackDoubleArray(V, 255);
		System.out.println("V=" +V[0]+"..."+V[4]);

		System.out.println("******************************************");
		System.out.println("in buffer memory unpacking stops here");
		System.out.println("******************************************\n");
		}
	}