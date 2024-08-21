#=======================================================================
#
# FILE:		Makefile
#
# DESCRIPTION:	This is make file for a C simpl receiver.
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
#    SIMPL project mailing list
#-----------------------------------------------------------------------
#
# Revision history:
# ======================================================================
# $Log: Makefile,v $
# Revision 1.1  2013/07/05 14:08:49  bobfcsoft
# new
#
# Revision 1.1  2010/01/20 17:49:07  bobfcsoft
# new file
#
#
#=======================================================================

#====================================================================
# definitions
#====================================================================

OBJ_DIR = .
SIMPL_LIB_DIR = ../../../../../lib
INC_DIR = ../../../../../include
BIN_DIR = .

RECEIVER_OBJ = \
	$(OBJ_DIR)/receiver.o

CC = cc
CFLAGS = -O -Wall -I$(INC_DIR)
LDFLAGS = -L$(SIMPL_LIB_DIR) -lsimpl

#=====================================================================
# Default targets
#=====================================================================
all: \
	title \
	$(BIN_DIR)/receiver
	@echo arduino/simpl numTimesTwo all

title:
	@echo arduino/simpl numTimesTwo build starting

#========================
# link
#========================
$(BIN_DIR)/receiver: $(RECEIVER_OBJ)
	$(CC) -o $@ $? $(LDFLAGS)
	
#===================
# compiles
#===================
$(OBJ_DIR)/receiver.o: receiver.c
	$(CC) -c $(CFLAGS) -o $@ $<

#===================
#  clean
#===================
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/receiver
	@echo  arduino/simpl numTimesTwo clean
