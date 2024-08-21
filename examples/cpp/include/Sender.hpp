/*============================================
	Sender.hpp

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
 *$Log: Sender.hpp,v $
 *Revision 1.1  2007/07/27 14:24:14  bobfcsoft
 *new cvs file
 *
 *
 */
#include <iostream.h>
#include <string.h>

#include "simplmiscProto.h"
#if 0
#include "FCID.hpp"
#endif

extern "C" int name_attach(const char *, void (*myExit)());
extern "C" int name_detach(void);
extern "C" int name_locate(char *);
extern "C" int Send(int, void *, void *, unsigned, unsigned);

class Sender
{
   public:
      Sender();
      ~Sender();
      
      // Functions That Use SIMPL 'C' Functions
      int NameAttach ();
      int NameLocate ();
      int SendtoPID ( int toPid );
      int NameDetach ();
      
      // Accessor Methods
      const int getToPID ();
      const void setInMsgSize ( const int iValue );
      const void setOutMsgSize ( const int iValue );
      const void setMyName ( const char* acValue );
      const void setToName ( const char* acValue );
      const void setOutArea ( const char* acValue );
      const char* getInArea ();
      const char* getMyName ();
      const char* getToName ();
      const int getOutMsgSize ();

      
   private:
      char inArea[8192];
      char outArea[8192];
      int toPID;
      
      unsigned  inMsgSize;
      unsigned  outMsgSize;
      char myName[20];
      char toName[20];
   

};// end of Sender Class

Sender::Sender()
{
   // Default values for message size in/out
   inMsgSize  = 1024;
   outMsgSize = 1024;
}

Sender::~Sender()
{
   // Call name_detach in case developer forgets to name detach
   // upon exiting the program...
   name_detach ();
}

// Calls to 'C' SIMPL Functions
int Sender::NameAttach ()
{
   return ( name_attach ( myName,  NULL ) );
}

int Sender::NameLocate ()
{
   // This function will find the SIMPL name to send to and
   // assign the toPID.  So there is no need for a setToPID()
   // function.
   toPID = name_locate ( toName );
   
   return ( toPID );
}

int Sender::SendtoPID ( int toPid )
{
   
   memset ( inArea, 0x00, 8192 );
   return ( Send( toPid, outArea, inArea, outMsgSize, inMsgSize ));
   
}

int Sender::NameDetach ()
{
   return ( name_detach () );
}

// Set/Get Functions
const int Sender::getToPID ()
{
   return ( toPID );
}

const void Sender::setInMsgSize ( const int iValue )
{
   inMsgSize = iValue;
}

const void Sender::setOutMsgSize ( const int iValue )
{
   outMsgSize = iValue;
}

const void Sender::setMyName ( const char* acValue )
{
   memset ( myName, 0x00, 20 );
   strncpy ( myName, acValue, 19 );
}

const void Sender::setToName ( const char* acValue )
{
   memset ( toName, 0x00, 20 );
   strncpy ( toName, acValue, 19 );
}

const void Sender::setOutArea ( const char* acValue )
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

const char* Sender::getInArea ()
{
   return ( inArea );
}

const char* Sender::getMyName ()
{
   return ( myName );
}

const char* Sender::getToName ()
{
   return ( toName );
}

const int Sender::getOutMsgSize ()
{
   return ( outMsgSize );
}

