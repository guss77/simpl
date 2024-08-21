#=======================================================
#
# DESCRIPTION:	
# Makefile for softwareICs/statemachine/SM_door/src tree.
#
# AUTHOR:	R.D. Findlay
#
#-----------------------------------------------------------------------
#    Copyright (C) 2006 iCanProgram Inc. 
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
# Revision 1.3  2011/03/23 17:41:57  bobfcsoft
# removed space in -L option for Mac compatibility
#
# Revision 1.2  2009/04/14 18:35:07  bobfcsoft
# added i386 target
#
# Revision 1.1  2006/06/26 18:03:17  bobfcsoft
# statemachine
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

COMMON_SRC_DIR=../../SM_common
COMMON_OBJ_DIR=$(COMMON_SRC_DIR)/obj

LOCAL_INCL_DIR=../include
INCL_DIR=../../include
SIMPL_INCL_DIR=$(SIMPL_DIR)/include

DOOR_OBJ=\
	$(OBJ_DIR)/doorInit.o\
	$(OBJ_DIR)/doorHandlers.o\
	$(OBJ_DIR)/doorParsers.o\
	$(OBJ_DIR)/doorUtils.o\
	$(OBJ_DIR)/poolUtils.o

STATEMACHINE_OBJ=\
	$(COMMON_OBJ_DIR)/statemachine.o\
	$(COMMON_OBJ_DIR)/statemachineInit.o\
	$(COMMON_OBJ_DIR)/statemachineUtils.o\
	$(COMMON_OBJ_DIR)/statemachineHandlers.o

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

HEADERS=$(LOCAL_INCL_DIR)/doorDefs.h

THIS_TARGET="starting"
DO_END=make -s title THIS_TARGET="<$@> done"

#========================
# Default targets
#========================
all:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/SM_door
	@$(DO_END)

title:
	@echo "=============== SM_door/src $(THIS_TARGET) ================"

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
$(BIN_DIR)/statemachine:	$(STATEMACHINE_OBJ)
	$(CC) -o $(BIN_DIR)/statemachine $(STATEMACHINE_OBJ) $(LDFLAGS)
	
$(BIN_DIR)/SM_door:	$(DOOR_OBJ) $(STATEMACHINE_OBJ)
	$(CC) -o $(BIN_DIR)/SM_door $(DOOR_OBJ) $(STATEMACHINE_OBJ) $(LDFLAGS)

#===================
# Compiles
#===================
$(OBJ_DIR)/doorInit.o: doorInit.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/doorInit.o doorInit.c

$(OBJ_DIR)/doorHandlers.o: doorHandlers.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/doorHandlers.o doorHandlers.c

$(OBJ_DIR)/doorParsers.o: doorParsers.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/doorParsers.o doorParsers.c

$(OBJ_DIR)/doorUtils.o: doorUtils.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/doorUtils.o doorUtils.c

$(OBJ_DIR)/poolUtils.o: poolUtils.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/poolUtils.o poolUtils.c

#===================
# Common Compiles
#===================
$(COMMON_OBJ_DIR)/statemachine.o: $(COMMON_SRC_DIR)/statemachine.c
	make -C $(COMMON_SRC_DIR) $(OBJ_DIR)/statemachine.o

$(COMMON_OBJ_DIR)/statemachineInit.o: $(COMMON_SRC_DIR)/statemachineInit.c
	make -C $(COMMON_SRC_DIR) $(OBJ_DIR)/statemachineInit.o

$(COMMON_OBJ_DIR)/statemachineUtils.o: $(COMMON_SRC_DIR)/statemachineUtils.c
	make -C $(COMMON_SRC_DIR) $(OBJ_DIR)/statemachineUtils.o

$(COMMON_OBJ_DIR)/statemachineHandlers.o: $(COMMON_SRC_DIR)/statemachineHandlers.c
	make -C $(COMMON_SRC_DIR) $(OBJ_DIR)/statemachineHandlers.o

#========================
# Cleanup
#========================
clobber: clean
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/SM_door
	cd $(COMMON_SRC_DIR); make clobber
	@$(DO_END)

#========================
# Install
#========================
install:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/SM_door
	cp $(BIN_DIR)/SM_door $(INSTALL_BIN_DIR)/SM_door
	@$(DO_END)

#===================
#  i386
#===================
i386:
	make install ARCHFLAGS="-march=i386"
	@echo SM_door i386

