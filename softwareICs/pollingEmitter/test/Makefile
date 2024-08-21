#=======================================================
#
# DESCRIPTION:	
# Makefile for softwareICs/pollingEmitter/test tree.
#
# AUTHOR:	R.D. Findlay
#
#-----------------------------------------------------------------------
#    Copyright (C) 2006, 2008 iCanProgram Inc. 
#
#    This software is in the public domain.
#    Permission to use, copy, modify, and distribute this software and its
#    documentation for any purpose and without fee is hereby granted, 
#    without any conditions or restrictions.
#    This software is provided "as is" without express or implied warranty.
#
#    If you discover a bug or add an enhancement contact us on the
#    SIMPL project mailing list. 
#
#-----------------------------------------------------------------------
#
# Revision history:
#=======================================================
# $Log: Makefile,v $
# Revision 1.3  2011/03/23 17:34:23  bobfcsoft
# removed space in -L option for Mac compatibility
#
# Revision 1.2  2009/04/14 16:08:19  bobfcsoft
# added i386 target
#
# Revision 1.1  2006/06/19 22:32:44  bobfcsoft
# new files
#
#=======================================================

SOFT_IC_DIR=../..
SIMPL_DIR=$(SIMPL_HOME)

CC=cc
DE=DEBUG

PROGRAM_NAME=
line1 = --------------------------------------------------------------------
line2 = ====================================================================

OBJ_DIR=obj
LIB_DIR=../lib
BIN_DIR=../bin
INSTALL_BIN_DIR=$(SOFT_IC_DIR)/bin
INSTALL_LIB_DIR=$(SOFT_IC_DIR)/lib

LOCAL_INCL_DIR=../include
SIMPL_INCL_DIR=$(SIMPL_DIR)/include

QUEUE_SIM_OBJ=\
	$(OBJ_DIR)/queueSim.o\
	$(OBJ_DIR)/queueSimInit.o\
	$(OBJ_DIR)/queueSimUtils.o

REQUESTOR_OBJ=\
	$(OBJ_DIR)/requestor.o\
	$(OBJ_DIR)/requestorInit.o\
	$(OBJ_DIR)/requestorUtils.o

CFLAGS=\
	-c \
	-Wall \
	-D $(DE) \
	-I $(LOCAL_INCL_DIR) \
	-I $(SIMPL_INCL_DIR)

LDFLAGS=\
	-L$(SIMPL_DIR)/lib\
	-lsimplmisc\
	-lsimpllog\
	-lsimpl

ARCHFLAGS =

HEADERS=

THIS_TARGET="starting"
DO_END=make -s title THIS_TARGET="<$@> done"

#========================
# Default targets
#========================
all:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/queueSim
	@$(DO_END)

title:
	@echo "=============== emitter/test $(THIS_TARGET) ================"

description:
	@(\
	echo;\
	echo "$(line1)";\
	echo "Compiling $(PROGRAM_NAME) module -> $(OBJ_NAME)";\
	echo )

$(OBJ_DIR):
	mkdir obj
	chmod a+w obj

$(LIB_DIR):
	mkdir ../lib
	chmod a+w ../lib

$(BIN_DIR):
	mkdir ../bin
	chmod a+w ../bin

#========================
# Link
#========================
$(BIN_DIR)/queueSim:	$(QUEUE_SIM_OBJ)
	$(CC) -o $(BIN_DIR)/queueSim $(QUEUE_SIM_OBJ) $(LDFLAGS)
	
$(BIN_DIR)/requestor:	$(REQUESTOR_OBJ)
	$(CC) -o $(BIN_DIR)/requestor $(REQUESTOR_OBJ) $(LDFLAGS)
	
#===================
# Compiles
#===================
$(OBJ_DIR)/queueSim.o: queueSim.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/queueSim.o queueSim.c

$(OBJ_DIR)/queueSimInit.o: queueSimInit.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/queueSimInit.o queueSimInit.c

$(OBJ_DIR)/queueSimUtils.o: queueSimUtils.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/queueSimUtils.o queueSimUtils.c

$(OBJ_DIR)/requestor.o: requestor.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/requestor.o requestor.c

$(OBJ_DIR)/requestorInit.o: requestorInit.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/requestorInit.o requestorInit.c

$(OBJ_DIR)/requestorUtils.o: requestorUtils.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/requestorUtils.o requestorUtils.c

#========================
# Cleanup
#========================
clobber: clean
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/queueSim
	@$(DO_END)

#========================
# Install
#========================
install:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/queueSim
	cp $(BIN_DIR)/queueSim $(INSTALL_BIN_DIR)/queueSim
	@$(DO_END)

#===================
#  i386
#===================
i386:
	make install ARCHFLAGS="-march=i386"
	@echo pollingEmitter/test i386

