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

import java.lang.*;

public class toStr
{
    private static String lineSep = "\n";

    public static String toHexString (char[] data)
    {
        return (toHexString (null, data));
    }

    public static String toHexString (Integer start, char[] data)
    {
        String temp = new String (data);
        int dataLen = temp.length();
        byte[] out = temp.getBytes();
        return (toHexString (start, out, dataLen));
    }
    public static String toHexString (char[] data, int datalen)
    {
        byte[]  out = new String (data).getBytes();
        return (toHexString (out, datalen));
    }
    public static String toHexString (byte[] data, int datalen)
    {
        return (toHexString (null, data, datalen));
    }
    public static String toHexString (Integer startAddr, byte[] data, int datalen)
    {
        StringBuffer    finalOutput = new StringBuffer (datalen*4);
        StringBuffer    line = null;
        StringBuffer    ascii = null;
        int i;
        int     addr = 0;

        if (startAddr != null)
            addr = startAddr.intValue();
//        finalOutput.append(lineSep);
        for (i=0; i<datalen; ++i)
        {
            if ((i%16) == 0)
            {
                if (line != null)
                {
                    if (startAddr != null)
                    {
                        finalOutput.append(format (addr,4,4) + ": " + line.toString() + "  " + ascii.toString());
                        addr += 16;
                    }
                    else
                    {
                        finalOutput.append(line.toString() + "  " + ascii.toString());
                    }
                    finalOutput.append(lineSep);
                }
                line = new StringBuffer (64);
                ascii = new StringBuffer (20);
            }
            int     iValue = (int) (data[i] & 0xff);
            String tempStr = Integer.toHexString(iValue);
            if (tempStr.length() < 2)
                tempStr = new String ("0" + tempStr);
            line.append(tempStr + " ");


            char ch = '.';
            if (iValue <= 0x20 || iValue > 0x7f)
                ch = '.';
            else
                ch = (char) iValue;

            ascii.append(ch);
        }
        if ((i%16) == 0)    // Last line is full line
        {
            if (line != null)
            {
                if (startAddr != null)
                {
                    finalOutput.append(format (addr,4,4) + ": " + line.toString() + "  " + ascii.toString());
                }
                else
                    finalOutput.append(line.toString() + "  " + ascii.toString());
                finalOutput.append(lineSep);
            }
        }
        else                // Last line is partial line
        {
            for (int j=(i%16); j<16; ++j)
            {
                line.append("   ");
                ascii.append("_");
            }
            if (startAddr != null)
                finalOutput.append(format (addr,4,4) + ": " + line.toString() + "  " + ascii.toString());
            else
                finalOutput.append(line.toString() + "  " + ascii.toString());
            finalOutput.append(lineSep);
        }

        return (finalOutput.toString());
    }
    private static String format (int a, int b, int c)
    {
        String tempStr = Integer.toHexString(a);
        while (tempStr.length() < 4)
            tempStr = new String ("0" + tempStr);

        return (tempStr);
    }
}
