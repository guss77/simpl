###############################################
#
# Makefile - for C++ example code 
#
#-----------------------------------------------------------------------
#    Copyright (C) 2002, 2007 Computerific - Donald Radke
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
#Revision 1.1  2007/07/27 14:24:14  bobfcsoft
#new cvs file
#
#
#
###############################################
CC=g++
OS=_THISIS_LINUX
VER=_SIMPLIPC

PROGRAM_NAME=
line1 = --------------------------------------------------------------------
line2 = ====================================================================

SIMPL_DIR=$(SIMPL_HOME)
OBJ_DIR=obj
BIN_DIR=../bin

LOCAL_INCL_DIR=../include
INCL_DIR=$(SIMPL_DIR)/include
DEST_BIN_DIR=$(SIMPL_DIR)/bin

SENDER_OBJ=\
	$(OBJ_DIR)/Sender.o

RECEIVER_OBJ=\
	$(OBJ_DIR)/Receiver.o

CDFLAGS=-c \
	-Wall \
        -I $(LOCAL_INCL_DIR)\
        -I $(INCL_DIR)\
	-D$(OS)\
	-D$(VER)

LDFLAGS=\
	-L $(SIMPL_DIR)/lib\
	-lsimpl\
	-lsimplmisc

#========================
# Default targets
#========================
all:\
     title \
     whichOS \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/Sender \
     $(BIN_DIR)/Receiver
	@echo benchmark all

whichOS:
	@echo whichOS = $(OS)

title:
	@echo benchmark build starting

description:
	@(\
	echo;\
	echo "$(line1)";\
	echo "Compiling $(PROGRAM_NAME) module -> $<";\
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
$(BIN_DIR)/Sender:	$(SENDER_OBJ)
	$(CC) -o $(BIN_DIR)/Sender $(SENDER_OBJ) $(LDFLAGS)
	
$(BIN_DIR)/Receiver:	$(RECEIVER_OBJ)
	$(CC) -o $(BIN_DIR)/Receiver $(RECEIVER_OBJ) $(LDFLAGS)
	
#===================
# Compiles
#===================
$(OBJ_DIR)/Receiver.o: Receiver.cpp
	$(CC) $(CDFLAGS) -o $(OBJ_DIR)/Receiver.o Receiver.cpp

$(OBJ_DIR)/Sender.o: Sender.cpp
	$(CC) $(CDFLAGS) -o $(OBJ_DIR)/Sender.o Sender.cpp

#===================
#  clobber 
#===================
clobber:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/*.a
	@echo benchmark clobber

#===================
#  install 
#===================
install:\
     title \
     whichOS \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/sender \
     $(BIN_DIR)/receiver
	-cp $(BIN_DIR)/sender $(DEST_BIN_DIR)/sender
	-cp $(BIN_DIR)/receiver $(DEST_BIN_DIR)/receiver
	@echo benchmark install
