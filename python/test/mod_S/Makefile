#=======================================================================
#
# FILE:		Makefile
#
# DESCRIPTION:	This is the local test make file.
#
# AUTHOR:	FC Software Inc.
#-----------------------------------------------------------------------
#    Copyright (C) 2000, 2008 FCSoftware Inc. 
#
#    This library is free software; you can redistribute it and/or
#    modify it under the terms of the GNU Lesser General Public
#    License as published by the Free Software Foundation; either
#    version 2.1 of the License, or (at your option) any later version.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#    Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public
#    License along with this library; if not, write to the Free Software
#    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
#    If you discover a bug or add an enhancement contact us on the: 
#
#	SIMPL project mailing list
#-----------------------------------------------------------------------
#
# Revision history:
# ======================================================================
# $Log: Makefile,v $
# Revision 1.1  2010/02/04 15:40:03  johnfcsoft
# initial entry
#
# Revision 1.1  2010/01/20 17:52:43  bobfcsoft
# new file
#
#
#=======================================================================

#====================================================================
# definitions
#====================================================================

CC = cc

OBJ_DIR = ./obj
SIMPL_LIB_DIR = ../../../lib
INC_DIR = ../../../include
BIN_DIR = ../../bin

SENDER_OBJ = \
	$(OBJ_DIR)/sender.o

RECEIVER_OBJ = \
	$(OBJ_DIR)/receiver.o

CFLAGS = -O -Wall -I$(INC_DIR)
LDFLAGS = -L$(SIMPL_LIB_DIR) -lsimpl

#=====================================================================
# Default targets
#=====================================================================
all: \
	title \
	$(BIN_DIR)/sender \
	$(BIN_DIR)/receiver
	@echo python simpl/test all

title:
	@echo java simpl/test build starting

#========================
# Link
#========================
$(BIN_DIR)/sender: $(SENDER_OBJ)
	$(CC) -o $@ $? $(LDFLAGS)
	
$(BIN_DIR)/receiver: $(RECEIVER_OBJ)
	$(CC) -o $@ $? $(LDFLAGS)
	
#===================
# Compiles
#===================
$(OBJ_DIR)/receiver.o: receiver.c
	$(CC) -c $(CFLAGS) -o $@ $<

$(OBJ_DIR)/sender.o: sender.c
	$(CC) -c $(CFLAGS) -o $@ $<

#===================
#  clean
#===================
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/sender
	@-rm -f $(BIN_DIR)/receiver
	@echo python simplipc/test clean

install: all
