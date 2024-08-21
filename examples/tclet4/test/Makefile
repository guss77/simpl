###############################################
#
# Makefile - for  tclet4/test
#
# NOTE:
# This make requires that Tcl8.0.x is installed
#
#-----------------------------------------------------------------------
#    Copyright (C) 2000, 2007 FCSoftware Inc. 
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
#    If you discover a bug or add an enhancement contact us on the  
#    SIMPL project mailing list.
#-----------------------------------------------------------------------
#
#$Log: Makefile,v $
#Revision 1.1  2007/07/27 14:16:01  bobfcsoft
#new cvs file
#
#
###############################################

TCL_HOME=/home/tcl/tcl8.0.3

CC=cc
DE=NODEBUG

PROGRAM_NAME=
line1 = --------------------------------------------------------------------
line2 = ====================================================================

DEST_DIR=.

OBJ_DIR=obj
LIB_DIR=../lib
BIN_DIR=../bin
SIMPL_DIR=$(SIMPL_HOME)

INSTALL_LIB_DIR=$(SIMPL_DIR)/examples/lib
INSTALL_BIN_DIR=$(SIMPL_DIR)/examples/bin

LOCAL_INCL_DIR=../include
INCL_DIR=$(SIMPL_DIR)/include
TCL_INCL_DIR=$(TCL_HOME)/generic

CB_SERVER_OBJECT =\
	$(OBJ_DIR)/cbServer.o\
	$(OBJ_DIR)/cbUtils.o

CDFLAGS=-c\
	-g\
	-Wall \
	-I $(LOCAL_INCL_DIR)\
	-I $(INCL_DIR)

LDFLAGS=\
	-L $(SIMPL_DIR)/lib\
	-lfclog\
	-lfcipc

#========================
# Default targets
#========================
all:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/cbServer
	@echo tclstuff all

title:
	@echo tclet4/test build starting

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

$(LIB_DIR):
	mkdir ../lib
	chmod a+w ../lib

#========================
# Link
#========================
$(BIN_DIR)/cbServer: $(CB_SERVER_OBJECT)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) -o $(BIN_DIR)/cbServer $(CB_SERVER_OBJECT) $(LDFLAGS)

#========================
# Compiles
#========================
$(OBJ_DIR)/cbServer.o : cbServer.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(CDFLAGS) -o $(OBJ_DIR)/cbServer.o cbServer.c

$(OBJ_DIR)/cbUtils.o : cbUtils.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(CDFLAGS) -o $(OBJ_DIR)/cbUtils.o cbUtils.c

#========================
# cleanup
#========================
clobber:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/*
	@echo tclet4/test clobber

#========================
# install
#========================
install:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/cbServer
	cp $(BIN_DIR)/cbServer $(INSTALL_BIN_DIR)/cbServer
	@echo tclet4/test install
