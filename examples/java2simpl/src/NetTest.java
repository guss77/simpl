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

/**
 * Title:        Network TCP/IP Tester<p>
 * Description:  This application is used to test TCP/IP Socket
 * connections.  It will be able to send and receive
 * messages over an opened TCP/IP Connection.
 * <p>
 * Copyright:    Copyright (c) Donald Radke<p>
 * Company:      Computerific<p>
 * @author Donald Radke
 * @version 1.0
 */
//package nettest;

import javax.swing.UIManager;
import java.awt.*;

public class NetTest 
{
   boolean packFrame = false;

   //Construct the application
   public NetTest() 
   {
      NetTester frame = new NetTester();
      //Validate frames that have preset sizes
      //Pack frames that have useful preferred size info, e.g. from their layout
      if (packFrame) 
      {
         frame.pack();
      }
      else 
      {
         frame.validate();
      }
      //Center the window
      Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
      Dimension frameSize = frame.getSize();
      if (frameSize.height > screenSize.height) 
      {
         frameSize.height = screenSize.height;
      }
      if (frameSize.width > screenSize.width) 
      {
         frameSize.width = screenSize.width;
      }
      frame.setLocation((screenSize.width - frameSize.width) / 2, (screenSize.height - frameSize.height) / 2);
      frame.setVisible(true);
   }

   //Main method
   public static void main(String[] args) 
   {
      try 
      {
         UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
      }
      catch(Exception e) 
      {
         e.printStackTrace();
      }
      new NetTest();
   }
}
