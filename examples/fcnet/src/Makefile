#=======================================================================
#
# FILE:			Makefile
#
# DESCRIPTION:	This make file produces the fcnet program.
#
# AUTHOR:		FC Software Inc.
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
# ======================================================================
# $Log: Makefile,v $
# Revision 1.2  2007/07/24 20:44:50  bobfcsoft
# new contact info
#
# Revision 1.1  2005/12/20 15:31:34  bobfcsoft
# initial commit
#
#=======================================================================

#====================================================================
# definitions
#====================================================================

CC = cc

OBJ_DIR = ./obj
BIN_DIR = ../bin
INC_DIR = ../include
#INSTALL_BIN_DIR=../../../bin

FCNET_OBJ =	\
			$(OBJ_DIR)/fcnet.o

CDFLAGS = -c -O -Wall -I$(INC_DIR) -o
LDFLAGS = 

#=====================================================================
# Default targets
#=====================================================================
all: \
    title \
    $(OBJ_DIR) \
    $(BIN_DIR) \
    $(BIN_DIR)/fcnet 
	@echo fcnet all

title:
	@echo fcnet starting

$(OBJ_DIR):
	mkdir ./obj
	chmod a+w ./obj

$(BIN_DIR):
	mkdir ../bin
	chmod a+w ../bin

#=====================================================================
# linking
#=====================================================================
$(BIN_DIR)/fcnet: $(FCNET_OBJ)
	$(CC) -o $@ $? $(LDFLAGS)
	
#=====================================================================
# compiling
#=====================================================================
$(OBJ_DIR)/fcnet.o: fcnet.c
	$(CC) $(CDFLAGS) $@ $<

#=====================================================================
#  cleanup
#=====================================================================
clobber: clean
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/*
	@echo fcnet clean/clobber

#=====================================================================
#  install 
#=====================================================================
install: \
    title \
    $(OBJ_DIR) \
    $(BIN_DIR) \
    $(BIN_DIR)/fcnet 
#	-cp $(BIN_DIR)/fcnet $(INSTALL_BIN_DIR)/fcnet
	@echo fcnet install

#===================
#  debug
#===================
debug:
	make install DE=-g
	@echo fcnet debug
