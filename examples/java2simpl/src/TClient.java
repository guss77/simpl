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


import java.util.*;
import java.net.*;
import java.io.*;

public class TClient extends Thread
{
   private static   Socket            theSocket   = null;
   private static   String            ServerMsg   = null;

   private static   MyDataInputStream   from_server = null;
   private static   MyDataOutputStream  to_server   = null;

   private static   NetTester         gNet1       = null;
   private static   TListener         tListener   = null;

   private static   ServerSocket      serSocket   = null;

   private static   int      toWhom = 0;
   private static   short    MY_TEST = 0xfffffc01;

   private static   boolean  LOCATE_FLAG  = false;

   public TClient ( String theAddress, int theLocalPort )
   {
      // connect to the server
      try
      {
         theSocket = new Socket( theAddress, theLocalPort );

         from_server = new MyDataInputStream ( theSocket.getInputStream());
         to_server   = new MyDataOutputStream ( theSocket.getOutputStream());

         start ();                          // Calls run method

      }
      catch (SocketException e )
      {
	      System.err.println ("Socket error : " + e);
      }
      catch (UnknownHostException e )
      {
	      System.err.println ("Invalid host!");
      }
      catch ( IOException e )
      {
         System.err.println ( "I/O Error : " + e.getMessage ());
      }

   }

   public TClient ( String theAddress, int theLocalPort, NetTester Net1 )
   {
      // connect to the server
      try
      {
         theSocket = new Socket( theAddress, theLocalPort );

         from_server = new MyDataInputStream ( theSocket.getInputStream());
         to_server   = new MyDataOutputStream ( theSocket.getOutputStream());

         start ();                          // Calls run method
         gNet1 = Net1;
         Net1.receiveData ( 1
                          , " Connected..."
                          );

      }
      catch (SocketException e )
      {
         Net1.receiveData ( 3
                          , " Socket Error : " + e.getMessage()
                          );
         Net1.setNetButtons ();
	      System.err.println ("Socket error : " + e.getMessage());
      }
      catch (UnknownHostException e )
      {
         Net1.receiveData ( 3
                          , " Invalid Host!"
                          );
         Net1.setNetButtons ();
	      System.err.println ("Invalid host!");
      }
      catch ( IOException e )
      {
         Net1.receiveData ( 3
                          , " Exception: " + e.getMessage()
                          );
         Net1.setNetButtons ();
         System.err.println ( "Exception: " + e.getMessage ());
      }

   }

   public TClient ( int theLocalPort, NetTester Net1 )
   {
      // Wait for a call
      gNet1 = Net1;
      tListener = new TListener ( theLocalPort );
   }

   public static void sendToServer ( String serverMessage )
   {
      byte[] myByte = new byte[4096];
      char[] myChar = new char[4096];

      // Send a binary mixed message...
      if ( serverMessage.equals ("ATTACH") )
      {
         short  sToken   = 0;
         short  sMsgLen  = 28;
         int    iPID     = -1;
         String strMsg   = "                    ";
         int    iWhat    = -1;
         
         try
         {
            //to_server.writeBoolean(true);
            to_server.writeLowShort(sToken);
            to_server.writeLowShort(sMsgLen);
            to_server.writeLowInt(iPID);
            to_server.writeBytes(strMsg);
            to_server.writeLowInt(iWhat);
            to_server.flush();

            gNet1.receiveData ( 1
                              , " " + to_server.size() + " bytes of Data Sent"
                              );
         }
         catch ( IOException eWrite )
         {
            gNet1.receiveData ( 3
                              , " Sending Binary Error : " + eWrite
                              );
         }

         return;
      }
      
      if ( serverMessage.equals ("DETACH") )
      {
         short  sToken   = 1;
         short  sMsgLen  = 0;
         
         try
         {
            to_server.writeLowShort (sToken);
            to_server.writeLowShort (sMsgLen);
            to_server.flush();

            gNet1.receiveData ( 1
                              , " " + to_server.size() + " bytes of Data Sent"
                              );
         }
         catch ( IOException eWrite )
         {
            gNet1.receiveData ( 3
                              , " Sending Binary Error : " + eWrite
                              );
         }

         return;
      }

      // Send a binary mixed message...
      if ( serverMessage.equals ("LOCATE") )
      {
         short  sToken   = 2;
         short  sMsgLen  = 28;
         int    iPID     = -1;
         String strMsg   = "BOBR                ";
         int    iWhat    = -1;
         
         try
         {
            //to_server.writeBoolean(true);
            to_server.writeLowShort(sToken);
            to_server.writeLowShort(sMsgLen);
            to_server.writeLowInt(iPID);
            to_server.writeBytes(strMsg);
            to_server.writeLowInt(iWhat);
            to_server.flush();

            gNet1.receiveData ( 1
                              , " " + to_server.size() + " bytes of Data Sent"
                              );
         }
         catch ( IOException eWrite )
         {
            gNet1.receiveData ( 3
                              , " Sending Binary Error : " + eWrite
                              );
         }

         LOCATE_FLAG = true;

         return;
      }


//      myChar = serverMessage.toCharArray();

//      for ( int i = 0; i < serverMessage.length(); i++)
//      {
//         myByte[i] =  (byte) myChar[i];
//      }

//      if ( serverMessage.equals ("END") )
//      {
//         socketClose();
//      }
//      else
//      {
//         gNet1.receiveData ( 1
//                           , " " + serverMessage.length() + " bytes of Data Sent"
//                           );

         try
         {
            int msgLen = serverMessage.length();
      
            msgLen += 6;

            to_server.writeLowShort ( 3 );
            to_server.writeLowShort ( msgLen );
            to_server.writeLowInt ( toWhom );
            to_server.writeLowShort ( MY_TEST );
            to_server.writeBytes ( serverMessage );
            to_server.flush();
         }
         catch ( IOException eWrite )
         {
            gNet1.receiveData ( 3
                              , " Sending Data Error : " + eWrite
                              );
         }

   }

   // run method used to read incoming messages from the server
   public void run ()
   {
      try
      {
            // wait for a message
         int    bufSize = 1024;
         byte   inbuf[] = new byte [bufSize];
         int    bytesRead;

         for (;;)
         {

            short myShort = from_server.readLowShort ();
            System.out.println ("First Short = <" + myShort + ">");

            myShort = from_server.readLowShort ();
            System.out.println ("Second Short = <" + myShort + ">");

            int myInt = from_server.readLowInt ();
            System.out.println ("First Int = <" + myInt + ">" );


            if ( LOCATE_FLAG )
	    {
               bytesRead = from_server.read (inbuf, 0, 20);
               toWhom = from_server.readLowInt ();
               System.out.println ("toWhom = <" + toWhom + ">" );
               LOCATE_FLAG = false;
	    }
	    else
	    {
               myShort = from_server.readLowShort ();
               System.out.println ("Second Short = <" + myShort + ">");

               bytesRead = from_server.read (inbuf, 0, bufSize);
	    }

	    if ( bytesRead < 0 )
            {
               gNet1.receiveData ( 3
                                 , " Connection Closed..."
                                 );
               gNet1.setNetButtons ();
               break;
            }
            else
            {
               // show the message to the user
               String theLine = new String (inbuf, 0, bytesRead);
               ServerMsg = theLine;
               gNet1.receiveData ( 2 
                                 , theLine
                                 );
               gNet1.receiveData ( 1
                                 , " " + bytesRead + " bytes of Data Received..."
                                 );
                                 
            }
            //bytesRead = from_server.read (inbuf);
         }  
      }
      catch ( IOException e ) 
      {
         gNet1.receiveData ( 3
                           , " Thread Error : " + e
                           );
      }
      
   } // End of run

   // Retrieve the server message
   String getServerMsg ()
   {
      return ( ServerMsg );
   }

   // The the socket connection
   public static void socketClose ()
   {
      try
      {
         gNet1.receiveData ( 3
                           , " Connection Closed..."
                           );
         theSocket.close();
      }
      catch (Exception e)
      {
         gNet1.receiveData ( 3
                           , " Closing Socket Error : " + e
                           );
      }
   }

// ****************************************************************************

   public class TListener extends Thread
   {
      public TListener ( int theLocalPort )
      {
         // Wait for a call
         try
         {
            serSocket = new ServerSocket( theLocalPort );
   
            start ();                          // Calls run method
         }
         catch (SocketException e )
         {
            gNet1.receiveData ( 3
                              , " Socket Error : " + e.getMessage()
                              );
            gNet1.setNetButtons ();
   	      System.err.println ("Socket error : " + e.getMessage());
         }
         catch ( IOException e )
         {
            gNet1.receiveData ( 3
                              , " Exception: " + e.getMessage()
                              );
            gNet1.setNetButtons ();
            System.err.println ( "Exception: " + e.getMessage ());
         }

      }

      // run method used to read incoming messages from the server
      public void run ()
      {
         try
         {
            // Wait for a Client to connect.
            theSocket = serSocket.accept ();

            gNet1.receiveData ( 1
                              , "Connection from : " 
                              + theSocket.getInetAddress().getHostAddress() 
                              + " : " + theSocket.getPort()
                              );
   
            from_server = new MyDataInputStream ( theSocket.getInputStream());
            to_server   = new MyDataOutputStream ( theSocket.getOutputStream());

            // wait for a message
            int    bufSize = 1024;
            byte   inbuf[] = new byte [bufSize];
            int    bytesRead;
   
            for (;;)
            {
               bytesRead = from_server.read (inbuf, 0, bufSize);
               
               if ( bytesRead < 0 )
               {
                  gNet1.receiveData ( 3
                                    , " Connection Closed..."
                                    );
                  gNet1.setNetButtons ();
                  break;
               }
               else
               {
                  // show the message to the user
                  int iTempVal = (int) inbuf[2];
                  String theLine = new String (inbuf, 0, bytesRead);
                  ServerMsg = theLine;
                  gNet1.receiveData ( 2
                                    , theLine
                                    );
               }
            }  
         }
         catch ( IOException e ) 
         {
            gNet1.receiveData ( 3
                              , " Thread Error : " + e
                              );
         }
      } // End of run

   }

// ****************************************************************************

   // Start of TClient
   public static void main ( String args[] ) 
   {
      // Variable Initialization
      String theAddress     = "";                // Server Address
      int    theLocalPort   = 0;                 // Server Port to connect to

      try
      {
         // check the command line for a host address
         if ( args.length != 2 )
         {
            System.out.println ( "Usage: java TClient <address> <port>" );
            System.exit (1);
         }
         else
         {
            theAddress    = args[0];
            theLocalPort  = Integer.parseInt ( args[1] );
         }

         new TClient ( theAddress, theLocalPort );

         // setup for user input
         BufferedReader userMessage =
            new BufferedReader ( new InputStreamReader ( System.in ));
         String userLine  = null;
         while ( true )
         {
            try
            {
               userLine = userMessage.readLine ();
               sendToServer ( userLine );
               if ( userLine.equals ("END") )
               {
                  break;
               }
            }
            catch ( IOException e ) {}

         }

      }
      finally
      {
         try
         {
            theSocket.close();
         }
         catch ( IOException e ) {}
      }

   }  // End of main

}  //  End of TClient Class
