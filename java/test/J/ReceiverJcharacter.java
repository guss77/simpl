/*
java JNI SIMPL receiver for text-based messages
*/

class ReceiverJcharacter
	{
	public static void main(String arg[])
		{
		int ret;
		int sender;

		// default constructor
		Jsimpl simpl = new Jsimpl();

		/*
		perform a SIMPL name attach which is always necessary
		prior to any SIMPL methods being used
		*/
		ret = simpl.nameAttach("RECEIVER");
		if (ret == -1)
			{
			System.out.println("name attach error");
			System.exit(-1);
			}

		while (true)
			{
			// receive any incoming SIMPL messages
			sender = simpl.Receive();
			if (sender == -1)
				{
				System.out.println("receive error");
				System.exit(-1);
				}

			// unpack the incoming message from a sender
			unpackInput(simpl);

			// build the outgoing reply to the sender
			packOutput(simpl);

			// reply to the sender
			ret = simpl.Reply(sender);
			if (ret == -1)
				{
				System.out.println("reply error");
				System.exit(-1);
				}
			}
		}


	// a method for extracting a known SIMPL message
	static void unpackInput(Jsimpl simpl)
		{
		System.out.println("\nJava Receiver: received message **************");

		short A = simpl.unpackShort(simpl.CHR);
		System.out.println("A=" + A);

		byte B = simpl.unpackByte(simpl.CHR);
		System.out.println("B=" + B);

		byte C = simpl.unpackByte(simpl.CHR);
		System.out.println("C=" + C);

		double D = simpl.unpackDouble(simpl.CHR);
		System.out.println("D=" + D);

		byte E = simpl.unpackByte(simpl.CHR);
		System.out.println("E=" + E);

		long F = simpl.unpackLong(simpl.CHR);
		System.out.println("F=" + F);

		byte G = simpl.unpackByte(simpl.CHR);
		System.out.println("G=" + G);

		char H = simpl.unpackChar(simpl.CHR);
		System.out.println("H=" + H);

		int len = 31;
		String Z = simpl.unpackString(len, simpl.CHR);
		System.out.println("Z=" + Z);

		short I = simpl.unpackShort(simpl.CHR);
		System.out.println("I=" + I);

		int J = simpl.unpackInt(simpl.CHR);
		System.out.println("J=" + J);

		long K = simpl.unpackLong(simpl.CHR);
		System.out.println("K=" + K);

		float L = simpl.unpackFloat(simpl.CHR);
		System.out.println("L=" + L);

		char M = simpl.unpackChar(simpl.CHR);
		System.out.println("M=" + M);

		long N = simpl.unpackLong(simpl.CHR);
		System.out.println("N=" + N);

		len = 2;
		String O = simpl.unpackString(len, simpl.CHR);
		System.out.println("O=" + O);

		byte[] P = {0,1,2,3,4,5,6,7,8,9};
		simpl.unpackByteArray(P, simpl.CHR);
		System.out.println("P=" +P[0]+"..."+P[9]);

		char[] Q = {88, 89, 90};
		simpl.unpackCharArray(Q, simpl.CHR);
		System.out.println("Q=" +Q[0]+","+Q[1]+","+Q[2]);
	
		short[] R = {0, 1, 2, 3, 4, 5, 6};
		simpl.unpackShortArray(R, simpl.CHR);
		System.out.println("R=" +R[0]+"..."+R[6]);

		int[] S = {21, 31, 41, 51, 61};
		simpl.unpackIntArray(S, simpl.CHR);
		System.out.println("S=" +S[0]+"..."+S[4]);

		long[] T = {-21, -31, -41, -51, -61};
		simpl.unpackLongArray(T, simpl.CHR);
		System.out.println("T=" +T[0]+"..."+T[4]);

		float[] U = {100F, 200F, 300F};
		simpl.unpackFloatArray(U, simpl.CHR);
		System.out.println("U=" +U[0]+","+U[1]+","+U[2]);

		double[] V = {0, 0, 0, 0, 0};
		simpl.unpackDoubleArray(V, simpl.CHR);
		System.out.println("V=" +V[0]+"..."+V[4]);

		System.out.println("**********************************************");
		}

	// a method for building the replied response
	static void packOutput(Jsimpl simpl)
		{
		int ret;

		System.out.println("\nJava Receiver: replied message **************");

		short a = 1;
		ret = simpl.packShort(a, simpl.CHR);
		if (ret == -1)
			{
			System.out.println("packing error");
			System.exit(-1);
			}
		else
			{
			System.out.println("a=" + a);
			}

		byte b = 80;
		ret = simpl.packByte(b, simpl.CHR);
		System.out.println("b=" + b);

		byte c = 81;
		ret = simpl.packByte(c, simpl.CHR);
		System.out.println("c=" + c);

		double d = 4;
		ret = simpl.packDouble(d, simpl.CHR);
		System.out.println("d=" + d);

		byte e = 82;
		ret = simpl.packByte(e, simpl.CHR);
		System.out.println("e=" + e);

		long f = 6;
		ret = simpl.packLong(f, simpl.CHR);
		System.out.println("f=" + f);

		byte g = 83;
		ret = simpl.packByte(g, simpl.CHR);
		System.out.println("g=" + g);

		char h = 66;
		ret = simpl.packChar(h, simpl.CHR);
		System.out.println("h=" + h);

		String z = "We are the knights who say nee!";
		ret = simpl.packString(z, simpl.CHR);
		System.out.println("z=" + z);

		short i = 8;
		ret = simpl.packShort(i, simpl.CHR);
		System.out.println("i=" + i);

		int j = 9;
		ret = simpl.packInt(j, simpl.CHR);
		System.out.println("j=" + j);

		long k = 10;
		ret = simpl.packLong(k, simpl.CHR);
		System.out.println("k=" + k);

		float l = 11F;
		ret = simpl.packFloat(l, simpl.CHR);
		System.out.println("l=" + l);

		char m = 77;
		ret = simpl.packChar(m, simpl.CHR);
		System.out.println("m=" + m);

		long n = 5;
		ret = simpl.packLong(n, simpl.CHR);
		System.out.println("n=" + n);

		String o = "We";
		ret = simpl.packString(o, simpl.CHR);
		System.out.println("o=" + o);

		//abcdefghij
		byte[] p = {97,98,99,100,101,102,103,104,105,106};
		ret = simpl.packByteArray(p, simpl.CHR);
		System.out.println("p=" +p[0]+"..."+p[9]);

		char[] q = {66, 67, 68};
		ret = simpl.packCharArray(q, simpl.CHR);
		System.out.println("q=" +q[0]+","+q[1]+","+q[2]);

		short[] r = {50, 51, 52, 53, 54, 55, 56};
		ret = simpl.packShortArray(r, simpl.CHR);
		System.out.println("r=" +r[0]+"..."+r[6]);

		int[] s = {201, 301, 401, 501, 601};
		ret = simpl.packIntArray(s, simpl.CHR);
		System.out.println("s=" +s[0]+"..."+s[4]);

		long[] t = {-201, -301, -401, -501, -601};
		ret = simpl.packLongArray(t, simpl.CHR);
		System.out.println("t=" +t[0]+"..."+t[4]);

		float[] u = {10000F, 20000F, 30000F};
		ret = simpl.packFloatArray(u, simpl.CHR);
		System.out.println("u=" +u[0]+","+u[1]+","+u[2]);

		double[] v = {-200, -100, 0, 100, 200};
		ret = simpl.packDoubleArray(v, simpl.CHR);
		System.out.println("v=" +v[0]+"..."+v[4]);

		System.out.println("*********************************************\n");
		}
	}