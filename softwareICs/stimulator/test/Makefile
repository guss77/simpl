#=======================================================
#
# DESCRIPTION:	
# Makefile for softwareICs/stimulator/test tree.
#
# AUTHOR:	R.D. Findlay
#
#-----------------------------------------------------------------------
#    Copyright (C) 2000, 2002, 2008 FCSoftware Inc. 
#
#    This software is in the public domain.
#    Permission to use, copy, modify, and distribute this software and its
#    documentation for any purpose and without fee is hereby granted, 
#    without any conditions or restrictions.
#    This software is provided "as is" without express or implied warranty.
#
#    If you discover a bug or add an enhancement contact us on the: 
#
#	SIMPL project mailing list
#-----------------------------------------------------------------------
# Revision history:
#=======================================================
# $Log: Makefile,v $
# Revision 1.3  2011/03/23 17:44:41  bobfcsoft
# removed space in -L option for Mac compatibility
#
# Revision 1.2  2009/04/14 19:04:18  bobfcsoft
# added i386 target
#
# Revision 1.1  2008/04/28 18:00:22  bobfcsoft
# new in CVS
#
# Revision 1.2  2002/12/03 21:24:37  root
# v2.0 compatible
#
# Revision 1.1  2002/12/03 20:22:45  root
# Initial revision
#
#=======================================================
#
#=======================================================

SOFT_IC_DIR=../..
SIMPL_DIR=$(SIMPL_HOME)

CC=cc

PROGRAM_NAME=
line1 = --------------------------------------------------------------------

OBJ_DIR=obj
BIN_DIR=../bin
LIB_DIR=../lib

INSTALL_BIN_DIR=$(SOFT_IC_DIR)/bin
INSTALL_LIB_DIR=$(SOFT_IC_DIR)/lib

LOCAL_INCL_DIR=../include
SIMPL_INCL_DIR=$(SIMPL_DIR)/include

RECEIVER_OBJ=\
	$(OBJ_DIR)/receiver.o\
	$(OBJ_DIR)/receiverInit.o

RECV_TESTER_OBJ=\
	$(OBJ_DIR)/recvTester.o\
	$(OBJ_DIR)/recvTesterInit.o\
	$(OBJ_DIR)/recvTesterUtils.o

CFLAGS=\
	-c\
	-g\
	-Wall\
        -I $(LOCAL_INCL_DIR)\
        -I $(SIMPL_INCL_DIR)

LDFLAGS=\
	-L$(SIMPL_DIR)/lib\
	-lsimplmisc\
	-lsimpllog\
	-lsimpl

THIS_TARGET="starting"
DO_END=make -s title THIS_TARGET="<$@> done"

#========================
# Default targets
#========================
all:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/recvTester\
     $(BIN_DIR)/receiver
	@$(DO_END)

title:
	@echo "=============== stimulator/test $(THIS_TARGET) ================"

description:
	@(\
	echo;\
	echo "$(line1)";\
	echo "Compiling $(PROGRAM_NAME) -> $(OBJ_NAME)";\
	echo )

$(OBJ_DIR):
	mkdir obj
	chmod a+w obj

$(BIN_DIR):
	mkdir ../bin
	chmod a+w ../bin

$(LIB_DIR):
	mkdir ../lib
	chmod a+w ../lib

#========================
# Link
#========================
$(BIN_DIR)/receiver:	$(RECEIVER_OBJ)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) -o $(BIN_DIR)/receiver $(RECEIVER_OBJ) $(LDFLAGS)

$(BIN_DIR)/recvTester:	$(RECV_TESTER_OBJ)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) -o $(BIN_DIR)/recvTester $(RECV_TESTER_OBJ) $(LDFLAGS)

#===================
# Compiles
#===================
$(OBJ_DIR)/receiver.o: receiver.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/receiver.o receiver.c

$(OBJ_DIR)/receiverInit.o: receiverInit.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/receiverInit.o receiverInit.c

$(OBJ_DIR)/recvTester.o: recvTester.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/recvTester.o recvTester.c

$(OBJ_DIR)/recvTesterInit.o: recvTesterInit.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/recvTesterInit.o recvTesterInit.c

$(OBJ_DIR)/recvTesterUtils.o: recvTesterUtils.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(CFLAGS) -o $(OBJ_DIR)/recvTesterUtils.o recvTesterUtils.c

#===================
# Cleanup
#===================
clobber: clean
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(LIB_DIR)/*.a
	@$(DO_END)

#===================
# Install
#===================
install:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/recvTester\
     $(BIN_DIR)/receiver
	cp $(BIN_DIR)/recvTester $(INSTALL_BIN_DIR)/recvTester
	cp $(BIN_DIR)/receiver $(INSTALL_BIN_DIR)/stim_receiver
	@$(DO_END)
