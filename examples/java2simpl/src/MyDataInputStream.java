/*
 *******************************************************************
 * This code if free for anyone to use and play with.  It doesn't
 * matter to me what you do with it.  This was all used as a 
 * learning exercise.
 *
 * Donald Radke   -  Computerific    computerific@hotmail.com
 *
 *******************************************************************
 */

import java.io.*;

public class MyDataInputStream extends DataInputStream implements DataInput 
{

   public MyDataInputStream (InputStream in)
   {
      super(in);
   }

   public final short readLowShort() throws IOException
   {
      InputStream in = this.in;

      int ch1 = in.read();
      int ch2 = in.read();

      if ((ch1 | ch2) < 0)
      {
         throw new EOFException();
      }

      return (short)((ch2 << 8) + (ch1 << 0));

   }

   public final int readLowUnsignedShort () throws IOException
   {
      InputStream in = this.in;

      int ch1 = in.read();
      int ch2 = in.read();

      if ((ch1 | ch2) < 0)
      {
         throw new EOFException();
      }

      return (ch1 << 8) + (ch2 << 0);

   }

   public final int readLowInt () throws IOException
   {
      InputStream in = this.in;

      int ch1 = in.read();
      int ch2 = in.read();
      int ch3 = in.read();
      int ch4 = in.read();

      if ((ch1 | ch2 | ch3 | ch4) < 0)
      {
         throw new EOFException();
      }

      return ((ch4 << 24) + (ch3 << 16) + (ch2 << 8) + (ch1 << 0));

   }

   public final long readLowLong () throws IOException
   {
      InputStream in = this.in;

      return ((long)(readLowInt()) << 32) + (readLowInt() & 0xFFFFFFFFL);

   }


}  // End of MyDataInputStream Class
