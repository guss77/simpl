#=======================================================
#
# DESCRIPTION:	
# Makefile for softwareICs/broadcaster/test tree.
#
# AUTHOR:	R.D. Findlay
#
#-----------------------------------------------------------------------
#    Copyright (C) 2000, 2002, 2007 FCSoftware Inc. 
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
# Revision history:
#=======================================================
# $Log: Makefile,v $
# Revision 1.3  2011/03/23 17:30:49  bobfcsoft
# removed space in -L option for Mac compatibility
#
# Revision 1.2  2009/04/14 15:54:31  bobfcsoft
# added i386 target
#
# Revision 1.1  2007/07/27 14:13:04  bobfcsoft
# new cvs file
#
# Revision 1.2  2002/12/03 21:05:13  root
# v2.0 compatible
#
# Revision 1.1  2002/10/30 15:59:41  root
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

INSTALL_LIB_DIR=$(SOFT_IC_DIR)/lib
INSTALL_BIN_DIR=$(SOFT_IC_DIR)/bin

LOCAL_INCL_DIR=../include
SIMPL_INCL_DIR=$(SIMPL_DIR)/include
SIMPL_INCL_DIR2=$(SIMPL_DIR)/qnx/include

RECV_SIM_OBJ=\
	$(OBJ_DIR)/receiverSim.o\
	$(OBJ_DIR)/recvSimInit.o\
	$(OBJ_DIR)/recvSimUtils.o

SENDER_STIM_OBJ=\
	$(OBJ_DIR)/senderStim.o\
	$(OBJ_DIR)/sendStimInit.o

CFLAGS=\
	-c\
	-g\
	-Wall\
        -I $(LOCAL_INCL_DIR)\
        -I $(SIMPL_INCL_DIR)\
        -I $(SIMPL_INCL_DIR2)

LDFLAGS=\
	-L$(SIMPL_DIR)/lib\
	-lsimpllog\
	-lsimpl\
	-lsimplmisc

ARCHFLAGS =

THIS_TARGET="starting"
DO_END=make -s title THIS_TARGET="<$@> done"

#========================
# Default targets
#========================
all:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/receiverSim\
     $(BIN_DIR)/senderStim
	@$(DO_END)

title:
	@echo "=============== broadcaster/test $(THIS_TARGET) ================"

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

#========================
# Link
#========================
$(BIN_DIR)/receiverSim:	$(RECV_SIM_OBJ)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) -o $(BIN_DIR)/receiverSim $(RECV_SIM_OBJ) $(LDFLAGS)
	
$(BIN_DIR)/senderStim:	$(SENDER_STIM_OBJ)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) -o $(BIN_DIR)/senderStim $(SENDER_STIM_OBJ) $(LDFLAGS)
	
#========================
# Compiles
#========================
$(OBJ_DIR)/senderStim.o: senderStim.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/senderStim.o senderStim.c

$(OBJ_DIR)/sendStimInit.o: sendStimInit.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/sendStimInit.o sendStimInit.c

$(OBJ_DIR)/sendStimUtils.o: sendStimUtils.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/sendStimUtils.o sendStimUtils.c

$(OBJ_DIR)/receiverSim.o: receiverSim.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/receiverSim.o receiverSim.c

$(OBJ_DIR)/recvSimInit.o: recvSimInit.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/recvSimInit.o recvSimInit.c

$(OBJ_DIR)/recvSimUtils.o: recvSimUtils.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/recvSimUtils.o recvSimUtils.c

#========================
# Cleanup
#========================
clobber: clean
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/receiverSim
	@-rm -f $(BIN_DIR)/senderStim
	@$(DO_END)

#========================
# Install
#========================
install:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/receiverSim\
     $(BIN_DIR)/senderStim
	cp $(BIN_DIR)/receiverSim $(INSTALL_BIN_DIR)/receiverSim
	cp $(BIN_DIR)/senderStim $(INSTALL_BIN_DIR)/senderStim
	@$(DO_END)

#===================
#  i386
#===================
i386:
	make install ARCHFLAGS="-march=i386"
	@echo broadcaster/test i386

