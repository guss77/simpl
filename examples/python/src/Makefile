#=======================================================================
#
# FILE:			Makefile
#
# DESCRIPTION:	This make file produces some test programs.
#
# AUTHOR:		FC Software Inc.
#-----------------------------------------------------------------------
#    Copyright (C) 2002, 2007 FCSoftware Inc. 
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
# ======================================================================
# $Log: Makefile,v $
# Revision 1.1  2007/07/26 15:44:13  bobfcsoft
# new file
#
#
#=======================================================================

#====================================================================
# definitions
#====================================================================
CC = cc

SIMPL_DIR=$(SIMPL_HOME)
OBJ_DIR = ./obj
BIN_DIR = ../bin
LIB_DIR = $(SIMPL_DIR)/lib
INC_DIR = $(SIMPL_DIR)/include

RECEIVER_OBJ =	\
			$(OBJ_DIR)/receiver_txt.o

SENDER_OBJ =	\
			$(OBJ_DIR)/sender_txt.o

# release flags
COMFLAGS = -O2 -pipe

CDFLAGS = $(COMFLAGS) -c -Wall -I$(INC_DIR) -o
LDFLAGS = $(COMFLAGS) -L$(LIB_DIR) -lsimpl -lsimplmisc

#=====================================================================
# Default target: all
#=====================================================================
all: install

install:\
    title \
    $(OBJ_DIR) \
    $(BIN_DIR) \
    $(BIN_DIR)/receiver_txt \
    $(BIN_DIR)/sender_txt
	@echo test all

title:
	@echo test starting

$(OBJ_DIR):
	mkdir ./obj
	chmod a+w ./obj

$(BIN_DIR):
	mkdir ../bin
	chmod a+w ../bin

#=====================================================================
# linking
#=====================================================================
$(BIN_DIR)/receiver_txt: $(RECEIVER_OBJ)
	$(CC) -o $@ $< $(LDFLAGS)

$(BIN_DIR)/sender_txt: $(SENDER_OBJ)
	$(CC) -o $@ $< $(LDFLAGS)
	
#=====================================================================
# compiling
#=====================================================================
$(OBJ_DIR)/receiver_txt.o: receiver_txt.c
	$(CC) $(CDFLAGS) $@ $<

$(OBJ_DIR)/sender_txt.o: sender_txt.c
	$(CC) $(CDFLAGS) $@ $<

#=====================================================================
#  cleanup
#=====================================================================
clobber: clean
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/receiver_txt
	@-rm -f $(BIN_DIR)/sender_txt
	@echo test clean/clobber
