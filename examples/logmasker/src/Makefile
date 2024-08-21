#=======================================================
#
# DESCRIPTION:	
# Makefile for examples/logmasker/src tree.
#
# AUTHOR:	R.D. Findlay
#
#-------------------------
# FCsoftware Inc. 1999, 2002
# This code is released as open source.   We hope you find 
# it useful.  If you discover a bug or add an enhancement 
# contact us on the SIMPL project mailing list. 
#
#-------------------------
#
# Revision history:
#=======================================================
# $Log: Makefile,v $
# Revision 1.1  2007/07/24 20:57:54  bobfcsoft
# new file
#
#=======================================================
#
#=======================================================

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

LOGMASKER_OBJ=\
	$(OBJ_DIR)/logmasker.o\
	$(OBJ_DIR)/logmaskerInit.o

RECEIVER_OBJ=\
	$(OBJ_DIR)/receiver.o\
	$(OBJ_DIR)/receiverInit.o

CDFLAGS=\
	-c \
	-Wall \
	-D $(DE) \
	-I $(LOCAL_INCL_DIR) \
	-I $(INCL_DIR) \
	-I $(SIMPL_INCL_DIR)

LDFLAGS=\
	-L $(SIMPL_DIR)/lib\
	-lsimplmisc\
	-lsimpllog\
	-lsimpl

HEADERS=$(LOCAL_INCL_DIR)/logmasker.h

THIS_TARGET="starting"
DO_END=make -s title THIS_TARGET="<$@> done"

#========================
# Default targets
#========================
all:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/logmasker\
     $(BIN_DIR)/receiver
	@$(DO_END)

title:
	@echo "=============== logmasker/src $(THIS_TARGET) ================"

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
$(BIN_DIR)/logmasker:	$(LOGMASKER_OBJ)
	$(CC) -o $(BIN_DIR)/logmasker $(LOGMASKER_OBJ) $(LDFLAGS)
	
$(BIN_DIR)/receiver:	$(RECEIVER_OBJ)
	$(CC) -o $(BIN_DIR)/receiver $(RECEIVER_OBJ) $(LDFLAGS)
	
#===================
# Compiles
#===================
$(OBJ_DIR)/logmasker.o: logmasker.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(CDFLAGS) -o $(OBJ_DIR)/logmasker.o logmasker.c

$(OBJ_DIR)/logmaskerInit.o: logmaskerInit.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(CDFLAGS) -o $(OBJ_DIR)/logmaskerInit.o logmaskerInit.c

$(OBJ_DIR)/receiver.o: receiver.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(CDFLAGS) -o $(OBJ_DIR)/receiver.o receiver.c

$(OBJ_DIR)/receiverInit.o: receiverInit.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(CDFLAGS) -o $(OBJ_DIR)/receiverInit.o receiverInit.c

#========================
# Cleanup
#========================
clobber:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/*
	@$(DO_END)

#========================
# Install
#========================
install:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/logmasker\
     $(BIN_DIR)/receiver
	cp $(BIN_DIR)/logmasker $(INSTALL_BIN_DIR)/logmasker
	cp $(BIN_DIR)/receiver $(INSTALL_BIN_DIR)/receiver
	@$(DO_END)
