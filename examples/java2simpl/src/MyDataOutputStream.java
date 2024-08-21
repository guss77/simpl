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

public class MyDataOutputStream extends DataOutputStream implements DataOutput 
{
   
   public MyDataOutputStream (OutputStream out)
   {
      super(out);
   }

   private void incCount (int value)
   {
      int temp = written + value;

      if (temp < 0)
      {
         temp = Integer.MAX_VALUE;
      }
      written = temp;

   }

   /**
    * Method : writeLowShort
    *
    * This method is used to allow Java to send a short with low order first
    * instead of high order first.
    */
   public final void writeLowShort (int v) throws IOException 
   {
	   OutputStream out = this.out;

	   out.write((v >>> 0) & 0xFF);
	   out.write((v >>> 8) & 0xFF);

	   incCount(2);
   }

   /**
    * Method : writeLowInt
    *
    * This method is used to allow Java to send a int with low order first
    * instead of high order first.
    */
   public final void writeLowInt (int v) throws IOException
   {
      OutputStream out = this.out;

      out.write((v >>>  0) & 0xFF);
      out.write((v >>>  8) & 0xFF);
      out.write((v >>> 16) & 0xFF);
      out.write((v >>> 24) & 0xFF);

      incCount(4);
   }

   /**
    * Method : writeLowLong
    *
    * This method is used to allow Java to send a long with low order first
    * instead of high order first.
    */
   public final void writeLowLong (long v) throws IOException
   {
      OutputStream out = this.out;

      out.write((int)(v >>>  0) & 0xFF);
      out.write((int)(v >>>  8) & 0xFF);
      out.write((int)(v >>> 16) & 0xFF);
      out.write((int)(v >>> 24) & 0xFF);
      out.write((int)(v >>> 32) & 0xFF);
      out.write((int)(v >>> 40) & 0xFF);
      out.write((int)(v >>> 48) & 0xFF);
      out.write((int)(v >>> 56) & 0xFF);

      incCount(8);
   }

}  // End of MyDataOutputStream Class
