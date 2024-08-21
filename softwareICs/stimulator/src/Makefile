#=======================================================
#
# DESCRIPTION:	
# Makefile for softwareICs/stimulator/src tree.
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
# Revision 1.3  2011/03/23 17:43:48  bobfcsoft
# removed space in -L option for Mac compatibility
#
# Revision 1.2  2009/04/14 18:43:00  bobfcsoft
# added i386 target
#
# Revision 1.1  2008/04/28 17:59:07  bobfcsoft
# new in CVS
#
# Revision 1.2  2002/12/03 21:23:49  root
# v2.0 compatible
#
# Revision 1.1  2002/12/03 20:21:04  root
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

STIMULATOR_OBJ=\
	$(OBJ_DIR)/stimulator.o\
	$(OBJ_DIR)/stimulatorInit.o\
	$(OBJ_DIR)/stimulatorUtils.o

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
     $(BIN_DIR)/stimulator
	@$(DO_END)

title:
	@echo "=============== stimulator/src $(THIS_TARGET) ================"

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
$(BIN_DIR)/stimulator:	$(STIMULATOR_OBJ)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) -o $(BIN_DIR)/stimulator $(STIMULATOR_OBJ) $(LDFLAGS)
	
#========================
# Compiles
#========================
$(OBJ_DIR)/stimulator.o: stimulator.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/stimulator.o stimulator.c

$(OBJ_DIR)/stimulatorInit.o: stimulatorInit.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/stimulatorInit.o stimulatorInit.c

$(OBJ_DIR)/stimulatorUtils.o: stimulatorUtils.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/stimulatorUtils.o stimulatorUtils.c

#========================
# Cleanup
#========================
clobber: clean
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/stimulator
	@$(DO_END)

#========================
# Install
#========================
install:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/stimulator
	cp $(BIN_DIR)/stimulator $(INSTALL_BIN_DIR)/stimulator
	@$(DO_END)

#===================
#  i386
#===================
i386:
	make install ARCHFLAGS="-march=i386"
	@echo stimulator i386

