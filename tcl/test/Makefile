###############################################
#
# Makefile - for Tcl tester 
#
# NOTE:
# This make requires that Tcl8.0.x is installed
#
#-----------------------------------------------------------------------
#    Copyright (C) 1998, 2002, 2007 FCSoftware Inc. 
#
#    This software is in the public domain.
#    Permission to use, copy, modify, and distribute this software and its
#    documentation for any purpose and without fee is hereby granted, 
#    without any conditions or restrictions.
#    This software is provided "as is" without express or implied warranty.
#
#    If you discover a bug or add an enhancement contact us on the
#    SIMPL project mailing list.
#-----------------------------------------------------------------------
#
#$Log: Makefile,v $
#Revision 1.7  2010/02/19 16:35:12  bobfcsoft
#added i386 stuff
#
#Revision 1.6  2009/03/17 14:22:59  bobfcsoft
#cleanup
#
#Revision 1.5  2009/01/19 20:30:46  bobfcsoft
#relocated tclSurrogate
#
#Revision 1.4  2009/01/13 21:53:06  bobfcsoft
#Debian cleanup
#
#Revision 1.3  2008/11/26 17:32:04  bobfcsoft
#cleanup
#
#Revision 1.2  2007/07/24 21:47:20  bobfcsoft
#new contact info
#
#Revision 1.1.1.1  2005/03/27 11:50:48  paul_c
#Initial import
#
#Revision 1.8  2003/04/23 20:44:15  root
#added support for dynamic SIMPL libraries
#
#Revision 1.7  2002/11/22 16:33:19  root
#2.0rc3
#
#Revision 1.6  2002/06/12 18:31:06  root
#fcipc merge completed
#
#Revision 1.5  2000/10/13 14:05:30  root
#LGPL
#using SIMPL_HOME
#
#Revision 1.4  1999/12/30 12:14:16  root
#added fifoReceiver
#
#Revision 1.3  1999/11/04 15:40:59  root
#added tclSurrogate test stuff
#
#Revision 1.2  1999/09/09 14:08:54  root
#*** empty log message ***
#
#Revision 1.1  1999/04/08 14:35:41  root
#Initial revision
#
#Revision 1.1  1999/02/01 13:26:54  root
#Initial revision
#
#Revision 1.1  1999/01/30 15:10:19  root
#Initial revision
#
#
###############################################

CC=cc
DE=NODEBUG

PROGRAM_NAME=
line1 = --------------------------------------------------------------------
line2 = ====================================================================

DEST_DIR=.

OBJ_DIR=obj
LIB_DIR=../lib
BIN_DIR=../bin
SIMPL_DIR=../..

INSTALL_LIB_DIR=$(SIMPL_DIR)/lib
INSTALL_BIN_DIR=$(SIMPL_DIR)/bin

LOCAL_INCL_DIR=../include
INCL_DIR=$(SIMPL_DIR)/include

FCTESTER_OBJ=\
	$(OBJ_DIR)/fcTester.o

BOB5_PARTS=\
	topPart.tcl \
	globalVars.tcl \
	guiHandlers.tcl \
	msgHandlers.tcl \
	receiveUtils.tcl \
	bottomPart.tcl

CFLAGS=\
	-g\
	-Wall \
	-I $(LOCAL_INCL_DIR)\
	-I $(INCL_DIR)

LDFLAGS=\
	-L $(SIMPL_DIR)/lib\
	-lsimpllog\
	-lsimpl\
	-L $(LIB_DIR)\
	-lfcsocket

LDFLAGS2=\
	-L $(SIMPL_DIR)/lib\
	-lsimpl

ARCHFLAGS = 


#========================
# Default targets
#========================
all:\
     title \
     $(BIN_DIR)/sender.tcl \
     $(BIN_DIR)/receiver.tcl \
     $(BIN_DIR)/bob5.tcl \
     $(BIN_DIR)/fcTester
	@echo tclstuff all

title:
	@echo tclstuff build starting

description:
	@(\
	echo;\
	echo "$(line1)";\
	echo "Compiling $(PROGRAM_NAME) -> $(OBJ_NAME)";\
	echo )

#========================
# Link
#========================
$(BIN_DIR)/sender.tcl:  sender.tcl
	cp sender.tcl $(BIN_DIR)/sender.tcl
	chmod a+x $(BIN_DIR)/sender.tcl

$(BIN_DIR)/receiver.tcl:  receiver.tcl
	cp receiver.tcl $(BIN_DIR)/receiver.tcl
	chmod a+x $(BIN_DIR)/receiver.tcl

$(BIN_DIR)/fcTester:	$(FCTESTER_OBJ)
	$(CC) -o $(BIN_DIR)/fcTester $(FCTESTER_OBJ) $(LDFLAGS2)

$(BIN_DIR)/bob5.tcl: $(BOB5_PARTS)
	cat $(BOB5_PARTS) > $(BIN_DIR)/bob5.tcl
	chmod a+x $(BIN_DIR)/bob5.tcl

$(BIN_DIR)/fifoReceiver: $(FIFO_RECEIVER_OBJECT)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) -o $(BIN_DIR)/fifoReceiver $(FIFO_RECEIVER_OBJECT) $(LDFLAGS)

$(BIN_DIR)/fifoSender: $(FIFO_SENDER_OBJECT)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) -o $(BIN_DIR)/fifoSender $(FIFO_SENDER_OBJECT) $(LDFLAGS)

$(BIN_DIR)/socketSender: $(SOCKET_SENDER_OBJECT)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) -o $(BIN_DIR)/socketSender $(SOCKET_SENDER_OBJECT) $(LDFLAGS)

#========================
# Compiles
#========================
$(OBJ_DIR)/fcTester.o: fcTester.c
	$(CC) -c $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/fcTester.o fcTester.c

$(OBJ_DIR)/fifoReceiver.o : fifoReceiver.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) -c $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/fifoReceiver.o fifoReceiver.c

$(OBJ_DIR)/fifoSender.o : fifoSender.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) -c $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/fifoSender.o fifoSender.c

$(OBJ_DIR)/socketSender.o : socketSender.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) -c $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/socketSender.o socketSender.c

#========================
# cleanup
#========================
clobber: clean
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/*
	@echo tclstuff clean

#========================
# install
#========================
install:\
     title \
     $(BIN_DIR)/sender.tcl \
     $(BIN_DIR)/receiver.tcl \
     $(BIN_DIR)/bob5.tcl \
     $(BIN_DIR)/fcTester
	@echo tclstuff install

#===================
#  i386
#===================
i386:
	make install ARCHFLAGS="-march=i386"
	@echo tclstuff i386

