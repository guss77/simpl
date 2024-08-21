/*============================================
	Receiver.hpp

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
/*
 *$Log: Receiver.hpp,v $
 *Revision 1.1  2007/07/27 14:24:14  bobfcsoft
 *new cvs file
 *
 *
 */
#include <iostream.h>
#include <string.h>
#if 0
#include "FCID.hpp"
#endif

extern "C" int name_attach(const char *, void (*myExit)());
extern "C" int name_detach(void);
extern "C" int Receive(char **, void *, int);
extern "C" int Reply(char *, void *, unsigned);
extern "C" int ReplyError(char *);

class Receiver
{
   public:
      Receiver();
      ~Receiver();
      
      // Functions That Use SIMPL 'C' Functions
      int NameAttach ();
      int ReplytoPID ( char *inValue );
      int ReceiveFrom (char **);
      int NameDetach ();
      
      // Set/Get Functions
      const char *getFromPID ();
      const void setMsgSize ( const int iValue );
      const void setMyName ( const char* acValue );
      const void setToName ( const char* acValue );
      const void setOutArea ( const char* acValue );
      const char* getInArea ();
      const char* getMyName ();
      
   private:
      char inArea[8192];
      char outArea[8192];
      char *fromPID;
      
      int  msgSize;
      char myName[20];

};// end of Receiver Class

Receiver::Receiver()
{
   // Default values for message size in/out
   msgSize = 1024;
}

Receiver::~Receiver()
{
   // Call name_detach in case developer forgets to name detach
   // upon exiting the program...
   name_detach ();
}

// Calls to 'C' SIMPL Functions
int Receiver::NameAttach ()
{
   return ( name_attach ( myName,  NULL ) );
}

int Receiver::ReceiveFrom (char **fromPID)
{
   msgSize = Receive ( fromPID, inArea, 8192 );
   
   return ( msgSize );
}

int Receiver::ReplytoPID ( char *inValue )
{
   return ( Reply ( inValue, outArea, msgSize ) );
}

int Receiver::NameDetach ()
{
   return ( name_detach () );
}

// Set/Get Functions
const char *Receiver::getFromPID ()
{
   return ( fromPID );
}

const void Receiver::setMsgSize ( const int iValue )
{
   msgSize = iValue;
}

const void Receiver::setMyName ( const char* acValue )
{
   memset ( myName, 0x00, 20 );
   strncpy ( myName, acValue, 19 );
}

const void Receiver::setOutArea ( const char* acValue )
{
   memset ( outArea, 0x00, 8192 );
   if ( strlen(acValue) > 8192 )
   {
      strncpy ( outArea, acValue, 8191 );
   }
   else
   {
      strcpy ( outArea, acValue );
   }
}

const char* Receiver::getInArea ()
{
   return ( inArea );
}

const char* Receiver::getMyName ()
{
   return ( myName );
}
