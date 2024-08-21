/***********************************************************************

FILE:			fcnet.h

DATE:			05 Dec 6

DESCRIPTION:	This file contains necessary headers, definitions
				and global variables for the fcnet program

-----------------------------------------------------------------------
    Copyright (C) 2000, 2002, 2007 FCSoftware Inc. 

    This software is in the public domain.
    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, 
    without any conditions or restrictions.
    This software is provided "as is" without express or implied warranty.

    If you discover a bug or add an enhancement contact us on the 
    SIMPL project mailing list. 

-----------------------------------------------------------------------
		
REVISIONS:
$Log: fcnet.h,v $
Revision 1.2  2007/07/24 20:44:50  bobfcsoft
new contact info

Revision 1.1  2005/12/20 15:31:34  bobfcsoft
initial commit

***********************************************************************/

#ifndef _FCNET_H
#define _FCNET_H

// standard headers
#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>

// definitions
#define TIME_LIMIT			30
#define	DATA_LEN			12
#define	MAXIP_LEN			60
#define	MAXICMP_LEN			76
#define	MAX_HOST_NAME_LEN	128
#define	MAX_SIZE			(65536 - 60 - 8)

// function prototypes
int initialize(int, char **, char *);
int procpack(char *, int, struct sockaddr_in *);
int sendMsg(int, struct sockaddr *);
int recvMsg(int);
int hndlTimeStampReply(struct icmp *, int);
int hndlError(struct icmp *);
void usage(void);
unsigned short getCksum(unsigned short *, int);
void sigAlrm(int);

// globals
const char *fn = "fcnet";
int tsorig;
int timeLimit;
int reportTime;

#endif
