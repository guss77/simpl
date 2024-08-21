#=======================================================
#
# DESCRIPTION:	
# Makefile for softwareICs/courier/test tree.
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
# Revision 1.3  2011/03/23 17:32:22  bobfcsoft
# removed space in -L option for Mac compatibility
#
# Revision 1.2  2009/04/14 16:01:53  bobfcsoft
# added i386 target
#
# Revision 1.1  2008/11/26 16:52:05  bobfcsoft
# new file
#
# Revision 1.2  2002/12/03 21:16:11  root
# v2.0 compatible
#
# Revision 1.1  2002/12/03 19:14:24  root
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

RECV_SIM_OBJ=\
	$(OBJ_DIR)/receiverSim.o\
	$(OBJ_DIR)/recvSimInit.o\
	$(OBJ_DIR)/recvSimUtils.o

GUI_SIM_OBJ=\
	$(OBJ_DIR)/guiSim.o\
	$(OBJ_DIR)/guiSimInit.o

CFLAGS=\
	-c\
	-g\
	-Wall\
        -I $(LOCAL_INCL_DIR)\
        -I $(SIMPL_INCL_DIR)

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
     $(BIN_DIR)/guiSim
	@$(DO_END)

title:
	@echo "=============== courier/test $(THIS_TARGET) ================"

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
	
$(BIN_DIR)/guiSim:	$(GUI_SIM_OBJ)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) -o $(BIN_DIR)/guiSim $(GUI_SIM_OBJ) $(LDFLAGS)
	
#========================
# Compiles
#========================
$(OBJ_DIR)/guiSim.o: guiSim.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/guiSim.o guiSim.c

$(OBJ_DIR)/guiSimInit.o: guiSimInit.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/guiSimInit.o guiSimInit.c

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
	@-rm -f $(BIN_DIR)/guiSim
	@$(DO_END)

#========================
# Install
#========================
install:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/receiverSim\
     $(BIN_DIR)/guiSim
	cp $(BIN_DIR)/receiverSim $(INSTALL_BIN_DIR)/cr_receiverSim
	cp $(BIN_DIR)/guiSim $(INSTALL_BIN_DIR)/guiSim
	@$(DO_END)

#===================
#  i386
#===================
i386:
	make install ARCHFLAGS="-march=i386"
	@echo courier/test i386

