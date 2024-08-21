#=======================================================
#
# DESCRIPTION:	
# Makefile for softwareICs/agency/src tree.
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
#
# Revision history:
#=======================================================
# $Log: Makefile,v $
# Revision 1.5  2011/09/08 16:23:43  bobfcsoft
# fixed typo on DO_END
#
# Revision 1.4  2011/03/23 17:25:58  bobfcsoft
# removed space in -L option for Mac compatibility
#
# Revision 1.3  2009/04/14 15:40:42  bobfcsoft
# fixed i386 stuff
#
# Revision 1.1  2007/07/27 14:10:49  bobfcsoft
# new cvs file
#
# Revision 1.1  2002/12/03 20:59:23  root
# Initial revision
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

AGENCY_OBJ=\
	$(OBJ_DIR)/agency.o\
	$(OBJ_DIR)/agencyInit.o\
	$(OBJ_DIR)/agencyUtils.o

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

HEADERS=$(LOCAL_INCL_DIR)/agency.h

THIS_TARGET="starting"
DO_END=make -s title THIS_TARGET="<$@> done"

#========================
# Default targets
#========================
all:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/agency
	@$(DO_END)

title:
	@echo "=============== agency/src $(THIS_TARGET) ================"

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
$(BIN_DIR)/agency:	$(AGENCY_OBJ)
	$(CC) -o $(BIN_DIR)/agency $(AGENCY_OBJ) $(LDFLAGS)
	
#===================
# Compiles
#===================
$(OBJ_DIR)/agency.o: agency.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/agency.o agency.c

$(OBJ_DIR)/agencyInit.o: agencyInit.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/agencyInit.o agencyInit.c

$(OBJ_DIR)/agencyUtils.o: agencyUtils.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/agencyUtils.o agencyUtils.c

#========================
# Cleanup
#========================
clobber: clean
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/agency
	@$(DO_END)

#========================
# Install
#========================
install:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/agency
	cp $(BIN_DIR)/agency $(INSTALL_BIN_DIR)/agency
	@$(DO_END)

#========================
#  i386
#========================
i386:
	make install ARCHFLAGS="-march=i386"
	@echo agency i386

