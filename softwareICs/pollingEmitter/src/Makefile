#=======================================================
#
# DESCRIPTION:	
# Makefile for softwareICs/pollingEmitter/src tree.
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
# Revision 1.3  2011/03/23 17:33:31  bobfcsoft
# removed space in -L option for Mac compatibility
#
# Revision 1.2  2009/04/14 16:05:48  bobfcsoft
# added i386 target
#
# Revision 1.1  2006/06/19 22:32:44  bobfcsoft
# new files
#
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
INSTALL_BIN_DIR=../../bin
INSTALL_LIB_DIR=../../lib

LOCAL_INCL_DIR=../include
INCL_DIR=../../include
SIMPL_INCL_DIR=$(SIMPL_DIR)/include

EMITTER_OBJ=\
	$(OBJ_DIR)/emitter.o\
	$(OBJ_DIR)/emitterInit.o\
	$(OBJ_DIR)/emitterUtils.o

CFLAGS=\
	-c \
	-Wall \
	-D $(DE) \
	-I $(LOCAL_INCL_DIR) \
	-I $(INCL_DIR) \
	-I $(SIMPL_INCL_DIR)

LDFLAGS=\
	-L$(SIMPL_DIR)/lib\
	-lsimplmisc\
	-lsimpllog\
	-lsimpl

ARCHFLAGS =

HEADERS=$(LOCAL_INCL_DIR)/emitter.h

THIS_TARGET="starting"
DO_END=make -s title THIS_TARGET="<$@> done"

#========================
# Default targets
#========================
all:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/emitter
	@$(DO_END)

title:
	@echo "=============== emitter/src $(THIS_TARGET) ================"

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
$(BIN_DIR)/emitter:	$(EMITTER_OBJ)
	$(CC) -o $(BIN_DIR)/emitter $(EMITTER_OBJ) $(LDFLAGS)
	
#===================
# Compiles
#===================
$(OBJ_DIR)/emitter.o: emitter.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/emitter.o emitter.c

$(OBJ_DIR)/emitterInit.o: emitterInit.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/emitterInit.o emitterInit.c

$(OBJ_DIR)/emitterUtils.o: emitterUtils.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/emitterUtils.o emitterUtils.c

#========================
# Cleanup
#========================
clobber: clean
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/emitter
	@$(DO_END)

#========================
# Install
#========================
install:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/emitter
	cp $(BIN_DIR)/emitter $(INSTALL_BIN_DIR)/emitter
	@$(DO_END)

#===================
#  i386
#===================
i386:
	make install ARCHFLAGS="-march=i386"
	@echo pollingEmitter i386

