/*============================================
	Sender.cpp

-----------------------------------------------------------------------
    Copyright (C) 2002, 2007 Computerific - Donald Radke

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

    If you discover a bug or add an enhancement contact us on the
    SIMPL project mailing list. 

-----------------------------------------------------------------------
============================================*/

//****************************************************************************
//**                                                                        **
//** This code is used to test a C++ program with the SIMPL Project, which  **
//** is written in 'C'.  SIMPL has been proven to work with Tcl/Tk and Java,**
//** now we attempt to prove SIMPL will work with C++.  Sender.hpp contains **
//** the Sender Class.                                                      **
//**                                                                        **
//****************************************************************************

/* 
 *$Log: Sender.cpp,v $
 *Revision 1.1  2007/07/27 14:24:14  bobfcsoft
 *new cvs file
 *
 *
 */
#include <iostream.h>
#include <time.h>
#include <sys/timeb.h>
#include "Sender.hpp"

int initialize ( int argc, char** argv, Sender* myTest );

int main ( int argc, char** argv)
{
   // Variable Listing
   static char *fn = "Sender";

   struct timeb before;
   struct timeb after;
   int msec;

   int iRepeats;

   Sender*  myTest = new Sender;
   int     toPID;
   
   // Start of Code
   cout <<  "Main...\n";
   iRepeats = initialize ( argc, argv, myTest );
   
   // Create a SIMPL named process for this app
   myTest->NameAttach();
   
   // Locate who to send a message to...
   toPID = myTest->NameLocate ();
   if ( toPID == -1 )
   {
      cout << "Can not find Receiver...\n";
   }
   else
   {
      // Record Start Time
      ftime ( &before );
      for ( int i = 0; i < iRepeats; i++)
	   {
         // Send a message
         myTest->SendtoPID ( toPID );
      }

      // Record Finish Time
      ftime ( &after );
      msec = (after.time - before.time)*1000 + (after.millitm - before.millitm);
      cout << fn << ":" << iRepeats << " messages took "<< msec << " ms\n";
   }

   // Detach SIMPL name process
   myTest->NameDetach ();
   
   // CleanUp
   delete ( myTest );
   
   return ( 0 );
}  //  End of main

//****************************************************************************
//**  Initalize Function                                                    **
//****************************************************************************
int initialize ( int argc, char** argv, Sender* myTest )
{
   // Variable Listing
   static char *fn="initialize";
   int  iRepeats = 100;

   // Start of Code
   for ( int i = 1; i <= argc; ++i )
   {
      char *p = argv[i];

      if ( p == NULL ) continue;

      if ( *p == '-' )
      {
         switch ( *++p )
         {
            case 'n':  // Retrieve myName (Sender)
            {
               for ( ; *p != 0; p++ );
               myTest->setMyName ( ++p );
               break;
            }

            case 'r':  // Retrieve toName (Receiver)
            {
               for ( ; *p != 0; p++ );
               myTest->setToName ( ++p );
               break;
            }

            case 't':  // Retrieve number of times to send
            {
               for ( ; *p != 0; p++ );
               iRepeats = atoi(++p);
               break;
            }

            case 's':  // Retrieve size of message to send
            {
               for ( ;*p != 0; p++ );
               myTest->setOutMsgSize ( atoi(++p) );
               myTest->setInMsgSize ( myTest->getOutMsgSize () );
               break;
            }

            default:
            {
               cout << fn << ": unknown arg " << p << "\n";
               break;
            }
         }/*end switch*/
      } /* end if *p */
   }/*end for i*/

   cout << "SIMPLipc version\n";
   cout << "Sender <" << myTest->getMyName () << "> sending " 
        << iRepeats << " messages of " << myTest->getOutMsgSize () 
        << " bytes to receiver <" << myTest->getToName () << ">\n"; 

   return ( iRepeats );
} //  End of initialize

