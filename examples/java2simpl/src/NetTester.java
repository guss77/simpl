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

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.border.*;

public class NetTester extends JFrame
{

   private   static TClient tClient;


   JPanel contentPane;
   JMenuBar menuBar1 = new JMenuBar();
   JMenu menuFile = new JMenu();
   JMenuItem menuFileExit = new JMenuItem();
   JMenu menuHelp = new JMenu();
   JMenuItem menuHelpAbout = new JMenuItem();
   BorderLayout borderLayout1 = new BorderLayout();
   TitledBorder titledBorder1;
   JPanel jPanel1 = new JPanel();
   JPanel jPanel2 = new JPanel();
   JPanel jPanel3 = new JPanel();
   JLabel statusBar = new JLabel();
   JLabel statusWin2 = new JLabel();
   JLabel statusWin1 = new JLabel();
   BorderLayout borderLayout2 = new BorderLayout();
   JLabel toAddr = new JLabel();
   JLabel toPort = new JLabel();
   JTextField tfToAddr = new JTextField();
   JTextField tfToPort = new JTextField();
   JButton bCall = new JButton();
   JButton bListen = new JButton();
   JButton bClose = new JButton();
   BorderLayout borderLayout3 = new BorderLayout();
   JPanel jPanel4 = new JPanel();
   JPanel jPanel5 = new JPanel();
   ButtonGroup TextDisplay = new ButtonGroup();
   JRadioButton rbAsText = new JRadioButton();
   JRadioButton rbAsHex = new JRadioButton();
   JPanel jPanel6 = new JPanel();
   BorderLayout borderLayout4 = new BorderLayout();
   JTextField tfEntryWin = new JTextField();
   JButton bSend = new JButton();
   JScrollPane jScrollPane1 = new JScrollPane();
   JTextArea MsgWindow = new JTextArea();
   JButton bClear = new JButton();

   //Construct the frame
   public NetTester()
   {
      enableEvents(AWTEvent.WINDOW_EVENT_MASK);
      try
      {
         jbInit();
      }
      catch(Exception e)
      {
         e.printStackTrace();
      }
   }

   //Component initialization
   private void jbInit() throws Exception
   {
      contentPane = (JPanel) this.getContentPane();
      titledBorder1 = new TitledBorder("");
      contentPane.setLayout(borderLayout1);
      this.setSize(new Dimension(631, 408));
      this.setTitle("Network TCP/IP Tester");
      menuFile.setText("File");
      menuFileExit.setText("Exit");
      menuHelp.setText("Help");
      menuHelpAbout.setText("About");
      jPanel1.setMinimumSize(new Dimension(10, 100));
      jPanel1.setPreferredSize(new Dimension(10, 100));
      jPanel1.setLayout(null);
      jPanel3.setMinimumSize(new Dimension(10, 30));
      jPanel3.setPreferredSize(new Dimension(10, 30));
      jPanel3.setLayout(borderLayout2);
      statusBar.setBorder(BorderFactory.createLoweredBevelBorder());
      statusBar.setMaximumSize(new Dimension(60, 21));
      statusBar.setMinimumSize(new Dimension(60, 21));
      statusBar.setPreferredSize(new Dimension(60, 21));
      statusBar.setText(" Status :");
      statusWin2.setBorder(BorderFactory.createLoweredBevelBorder());
      statusWin2.setMaximumSize(new Dimension(60, 21));
      statusWin2.setMinimumSize(new Dimension(60, 21));
      statusWin2.setPreferredSize(new Dimension(60, 21));
      statusWin1.setBorder(BorderFactory.createLoweredBevelBorder());
      toAddr.setText("Server :");
      toAddr.setBounds(new Rectangle(25, 19, 75, 23));
      toPort.setBounds(new Rectangle(25, 59, 75, 23));
      toPort.setText("Port :");
      tfToAddr.setBackground(Color.white);
      tfToAddr.setNextFocusableComponent(tfToPort);
      tfToAddr.setBounds(new Rectangle(90, 19, 151, 23));
      tfToAddr.setText("localhost");
      tfToPort.setBounds(new Rectangle(90, 59, 80, 23));
      tfToPort.setBackground(Color.white);
      tfToPort.setNextFocusableComponent(tfToAddr);
      tfToPort.setText("16415");
      bCall.setText("Call");
      bCall.setBounds(new Rectangle(320, 11, 69, 30));
      bListen.setText("Listen");
      bListen.setBounds(new Rectangle(395, 11, 69, 30));
      bClose.setText("Close");
      bClose.setBounds(new Rectangle(470, 11, 69, 30));
      bClose.setEnabled(false);
      jPanel2.setLayout(borderLayout3);
      jPanel4.setMinimumSize(new Dimension(10, 50));
      jPanel4.setPreferredSize(new Dimension(10, 50));
      jPanel4.setLayout(null);
      jPanel5.setMinimumSize(new Dimension(10, 30));
      jPanel5.setPreferredSize(new Dimension(10, 30));
      jPanel5.setLayout(null);
      rbAsText.setText("As Text");
      rbAsText.setBounds(new Rectangle(67, 1, 107, 29));
      rbAsText.setMnemonic(KeyEvent.VK_T);
      rbAsHex.setText("As Hex");
      rbAsHex.setBounds(new Rectangle(182, 0, 107, 29));
      rbAsHex.setMnemonic(KeyEvent.VK_H);
      rbAsHex.setSelected(true);
      jPanel6.setLayout(borderLayout4);
      tfEntryWin.setBackground(Color.white);
      tfEntryWin.setBounds(new Rectangle(90, 17, 527, 21));
      bSend.setText("Send");
      bSend.setBounds(new Rectangle(13, 12, 69, 30));
      bSend.setEnabled(false);

//*****************************************************************************

      menuFileExit.addActionListener(new ActionListener()
      {
         public void actionPerformed(ActionEvent e)
         {
            fileExit_actionPerformed(e);
         }
      });

      menuHelpAbout.addActionListener(new ActionListener()
      {
         public void actionPerformed(ActionEvent e)
         {
            helpAbout_actionPerformed(e);
         }
      });

      bCall.addActionListener(new java.awt.event.ActionListener()
      {

         public void actionPerformed(ActionEvent e)
         {
            bCall_actionPerformed(e);
         }
      });

      bClose.addActionListener(new java.awt.event.ActionListener()
      {
         public void actionPerformed(ActionEvent e)
         {
            bClose_actionPerformed(e);
         }
      });

      bSend.addActionListener(new java.awt.event.ActionListener()
      {
         public void actionPerformed(ActionEvent e)
         {
            bSend_actionPerformed(e);
         }
      });
      bListen.addActionListener(new java.awt.event.ActionListener()
      {
         public void actionPerformed(ActionEvent e)
         {
            bListen_actionPerformed(e);
         }
      });

//*****************************************************************************

      MsgWindow.setBackground(Color.white);
      bClear.addActionListener(new java.awt.event.ActionListener()
      {

         public void actionPerformed(ActionEvent e)
         {
            bClear_actionPerformed(e);
         }
      });
      bClear.setBounds(new Rectangle(513, 0, 69, 30));
      bClear.setText("Clear");
      menuFile.add(menuFileExit);
      menuHelp.add(menuHelpAbout);
      menuBar1.add(menuFile);
      menuBar1.add(menuHelp);
      contentPane.add(jPanel1, BorderLayout.NORTH);
      jPanel1.add(toPort, null);
      jPanel1.add(toAddr, null);
      jPanel1.add(tfToPort, null);
      jPanel1.add(tfToAddr, null);
      jPanel1.add(bCall, null);
      jPanel1.add(bListen, null);
      jPanel1.add(bClose, null);
      contentPane.add(jPanel2, BorderLayout.CENTER);
      jPanel2.add(jPanel4, BorderLayout.NORTH);
      jPanel4.add(tfEntryWin, null);
      jPanel4.add(bSend, null);
      jPanel2.add(jPanel5, BorderLayout.SOUTH);
      jPanel5.add(rbAsHex, null);
      jPanel5.add(rbAsText, null);
      jPanel5.add(bClear, null);
      TextDisplay.add(rbAsText);
      TextDisplay.add(rbAsHex);
      jPanel2.add(jPanel6, BorderLayout.CENTER);
      jPanel6.add(jScrollPane1, BorderLayout.CENTER);
      jScrollPane1.getViewport().add(MsgWindow, null);
      contentPane.add(jPanel3, BorderLayout.SOUTH);
      jPanel3.add(statusBar, BorderLayout.WEST);
      jPanel3.add(statusWin2, BorderLayout.EAST);
      jPanel3.add(statusWin1, BorderLayout.CENTER);

      this.setJMenuBar(menuBar1);
   }

   //File | Exit action performed
   public void fileExit_actionPerformed(ActionEvent e)
   {
      try
      {
         // Beep
         Toolkit.getDefaultToolkit().beep();
         // Show a confirmation dialog
         int reply = JOptionPane.showConfirmDialog(this,
                                                   "Do you really want to exit?",
                                                   "Network Tester - Exit" ,
                                                   JOptionPane.YES_NO_OPTION,
                                                   JOptionPane.QUESTION_MESSAGE);
         // If the confirmation was affirmative, handle exiting.
         if (reply == JOptionPane.YES_OPTION)
         {
            //tClient.sendToServer ( "END" );  // disconnect for server
            this.setVisible(false);          // hide the Frame
            this.dispose();                  // free the system resources
            System.exit(0);                  // close the application
         }
      }
      catch (Exception event)
      {
         this.setVisible(false);          // hide the Frame
         this.dispose();                  // free the system resources
         System.exit(0);                  // close the application
      }
   }

   //Help | About action performed
   public void helpAbout_actionPerformed(ActionEvent e)
   {
      NetTester_AboutBox dlg = new NetTester_AboutBox(this);
      Dimension dlgSize = dlg.getPreferredSize();
      Dimension frmSize = getSize();
      Point loc = getLocation();
      dlg.setLocation((frmSize.width - dlgSize.width) / 2 + loc.x, (frmSize.height - dlgSize.height) / 2 + loc.y);
      dlg.setModal(true);
      dlg.show();
   }

   //Overridden so we can exit when window is closed
   protected void processWindowEvent(WindowEvent e)
   {
      //super.processWindowEvent(e);
      if (e.getID() == WindowEvent.WINDOW_CLOSING)
      {
         fileExit_actionPerformed(null);
      }
   }

   void bCall_actionPerformed(ActionEvent e)
   {
      // Call Button was pressed.
      String   Server  = tfToAddr.getText();
      String   PortStr = tfToPort.getText();
      int      PortInt;

      try
      {
         PortInt = new Integer (PortStr).intValue();

         statusWin1.setText(" Connecting to " + Server + ": on Port " + PortInt + " ...");
         statusWin2.setText( " " + PortInt );

         tClient = new TClient ( Server, PortInt, this );

         bCall.setEnabled(false);
         bListen.setEnabled(false);
         bClose.setEnabled(true);
         bSend.setEnabled(true);

      }
      catch (NumberFormatException ex)
      {
         setNetButtons ();
         statusWin1.setText (" Invalid Port value \"" + PortStr + "\"");
         return;
      }
      catch (Exception ex)
      {
         setNetButtons ();
         statusWin1.setText(" Error Connecting: " + ex.getMessage());
         return;
      }
   }

   void bListen_actionPerformed(ActionEvent e)
   {
      // Listen Button was pressed.
      String   PortStr = tfToPort.getText();
      int      PortInt;

      try
      {

         PortInt = new Integer (PortStr).intValue();
         statusWin1.setText(" Waiting For Call on Port " + PortInt + " ...");
         statusWin2.setText( " " + PortInt );
         

         tClient = new TClient ( PortInt, this );

         bCall.setEnabled(false);
         bListen.setEnabled(false);
         bClose.setEnabled(true);
         bSend.setEnabled(true);

      }
      catch (NumberFormatException ex)
      {
         setNetButtons ();
         statusWin1.setText (" Invalid Port value \"" + PortStr + "\"");
         return;
      }
      catch (Exception ex)
      {
         setNetButtons ();
         statusWin1.setText(" Error Connecting: " + ex.getMessage());
         return;
      }
   }

   void bClose_actionPerformed(ActionEvent e)
   {
      // Close Button was pressed.
      tClient.socketClose();

      bCall.setEnabled(true);
      bListen.setEnabled(true);
      bClose.setEnabled(false);
      bSend.setEnabled(false);

      statusWin1.setText ( " Connection Closed..." );
      statusWin2.setText ( "" );
   }

   void bSend_actionPerformed(ActionEvent e)
   {
      // Send Button was pressed.
      String out = tfEntryWin.getText();

      if ( out.equals("") )
      {
         out = "SEND";
      }

      statusWin1.setText(" " + out.length() + " bytes of Data Sent");
      tClient.sendToServer ( out );
   }

   public void receiveData ( int iToken, String inValue )
   {
      switch (iToken)
      {
         // Messages to be displayed in Status Bar
         case 1:
         {
            statusWin1.setText( inValue );
            break;
         }

         // Messages to be displayed in Receive Window
         case 2:
         {
            String newLine   = "\n";
            String serverMsg = tClient.getServerMsg();

            statusWin1.setText(" " + serverMsg.length() + " bytes of Data Received");
            if ( rbAsText.isSelected() )
            {
               MsgWindow.append ( inValue + newLine );
            }
            else
            {
               MsgWindow.append ( toStr.toHexString ( new Integer (0x1000), inValue.toCharArray()));
            }
            break;
         }

         // Error Messages for Status Bar
         case 3:
         {
            statusWin1.setText( inValue );
            statusWin2.setText( "" );
         }
      }
   }
   
   public void setNetButtons ()
   {
//      tClient.socketClose();

      bCall.setEnabled(true);
      bListen.setEnabled(true);
      bClose.setEnabled(false);
      bSend.setEnabled(false);
   }

   void bClear_actionPerformed(ActionEvent e)
   {
      // Clear the Message Window
      MsgWindow.setText("");
   }


}
