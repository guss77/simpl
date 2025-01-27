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

public class NetTester_AboutBox extends JDialog implements ActionListener 
{

   JPanel panel1 = new JPanel();
   JPanel panel2 = new JPanel();
   JPanel insetsPanel1 = new JPanel();
   JPanel insetsPanel2 = new JPanel();
   JPanel insetsPanel3 = new JPanel();
   JButton button1 = new JButton();
   JLabel imageControl1 = new JLabel();
   ImageIcon imageIcon;
   JLabel label1 = new JLabel();
   JLabel label2 = new JLabel();
   JLabel label3 = new JLabel();
   JLabel label4 = new JLabel();
   BorderLayout borderLayout1 = new BorderLayout();
   BorderLayout borderLayout2 = new BorderLayout();
   FlowLayout flowLayout1 = new FlowLayout();
   FlowLayout flowLayout2 = new FlowLayout();
   GridLayout gridLayout1 = new GridLayout();
   String product = "Network TCP/IP Tester";
   String version = "1.0";
   String copyright = "Copyright (c) Donald Radke";
   String comments = "Used to test TCP/IP Socket Connections.";

   public NetTester_AboutBox(Frame parent) 
   {
      super(parent);
      enableEvents(AWTEvent.WINDOW_EVENT_MASK);
      try 
      {
         jbInit();
      }
      catch(Exception e) 
      {
         e.printStackTrace();
      }
      //imageControl1.setIcon(imageIcon);
      pack();
   }

   private void jbInit() throws Exception  
   {
      //imageIcon = new ImageIcon(getClass().getResource("[Your Image]"));
      this.setTitle("About");
      setResizable(false);
      panel1.setLayout(borderLayout1);
      panel2.setLayout(borderLayout2);
      insetsPanel1.setLayout(flowLayout1);
      insetsPanel2.setLayout(flowLayout1);
      insetsPanel2.setBorder(new EmptyBorder(10, 10, 10, 10));
      gridLayout1.setRows(4);
      gridLayout1.setColumns(1);
      label1.setText(product);
      label2.setText(version);
      label3.setText(copyright);
      label4.setText(comments);
      insetsPanel3.setLayout(gridLayout1);
      insetsPanel3.setBorder(new EmptyBorder(10, 60, 10, 10));
      button1.setText("Ok");
      button1.addActionListener(this);
      insetsPanel2.add(imageControl1, null);
      panel2.add(insetsPanel2, BorderLayout.WEST);
      this.getContentPane().add(panel1, null);
      insetsPanel3.add(label1, null);
      insetsPanel3.add(label2, null);
      insetsPanel3.add(label3, null);
      insetsPanel3.add(label4, null);
      panel2.add(insetsPanel3, BorderLayout.CENTER);
      insetsPanel1.add(button1, null);
      panel1.add(insetsPanel1, BorderLayout.SOUTH);
      panel1.add(panel2, BorderLayout.NORTH);
   }

   protected void processWindowEvent(WindowEvent e) 
   {
      if (e.getID() == WindowEvent.WINDOW_CLOSING) 
      {
         cancel();
      }
      super.processWindowEvent(e);
   }

   void cancel() 
   {
      dispose();
   }

   public void actionPerformed(ActionEvent e) 
   {
      if (e.getSource() == button1) {
         cancel();
      }
   }
}
