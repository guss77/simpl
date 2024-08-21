/*============================================
	Sender.h

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
//** now we attempt to prove SIMPL will work with C++.  Receiver.hpp        **
//** contains the Receiver Class.                                           **
//**                                                                        **
//****************************************************************************

/*
 *$Log: Receiver.cpp,v $
 *Revision 1.1  2007/07/27 14:24:14  bobfcsoft
 *new cvs file
 *
 *
 */
 
#include <iostream.h>

#include "Receiver.hpp"
 
void initialize(int argc, char** argv, Receiver* myTest );

//********************************************
//** Receiver - entry point
//********************************************
int main ( int argc, char** argv, char** envp )
{
   // Variable Listing
   static char *fn = "Receiver";
   
   Receiver* myTest = new Receiver;
   char *fromWhom;
int rbytes;

   // Start of Code
   initialize ( argc, argv, myTest );

   cout << "Top of receive loop\n";
   myTest->NameAttach ();   
   while ( 1 )
   {
      rbytes = myTest->ReceiveFrom ( &fromWhom);
      myTest->ReplytoPID ( fromWhom );
   }

   cout << fn << ":done\n";

   myTest->NameDetach();

   return ( 1 );

} //  End of main

//********************************************
//** initialize - entry point
//********************************************
void initialize( int argc, char **argv, Receiver* myTest )
{
   // Variable Listing
   static char *fn = "initialize";
   char myName[20];

   // Start of Code
   for ( int i = 1; i <= argc; ++i )
   {
      char *p = argv[i];

      if ( p == NULL ) continue;

      if ( *p == '-' )
      {
         switch ( *++p )
         {
            case 'n':
            {
               for ( ; *p != 0; p++ );
               
               myTest->setMyName ( ++p );
               cout << "Receiver <" << myTest->getMyName () << "> starting\n";
               break;
            }

            default:
            {
               cout << fn << ":unknown arg "<< p << endl;
               break;
            }
         }/*end switch*/
      } /* end if *p */
   }/*end for i*/

   if ( !myName )
   {
      cout << "No name specified.\n";
      cout << "Usage: Receiver -n name\n";
      exit(0);
   }

   cout << "SIMPLIPC version\n";

} /* end initialize */
