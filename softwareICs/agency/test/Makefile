#=======================================================
#
# DESCRIPTION:	
# Makefile for softwareICs/agency/test tree.
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
#
#-----------------------------------------------------------------------
#
# Revision history:
#=======================================================
# $Log: Makefile,v $
# Revision 1.3  2011/03/23 17:27:43  bobfcsoft
# removed space in -L option for Mac compatibility
#
# Revision 1.2  2009/04/14 15:43:34  bobfcsoft
# added i386 target
#
# Revision 1.1  2007/07/27 14:10:49  bobfcsoft
# new cvs file
#
# Revision 1.2  2002/12/03 21:00:51  root
# v2.0 compatible
#
# Revision 1.1  2002/10/29 18:47:15  root
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
INSTALL_BIN_DIR=$(SOFT_IC_DIR)/bin
INSTALL_LIB_DIR=$(SOFT_IC_DIR)/lib

LOCAL_INCL_DIR=../include
SIMPL_INCL_DIR=$(SIMPL_DIR)/include

AGENT_OBJ=\
	$(OBJ_DIR)/agent.o\
	$(OBJ_DIR)/agentInit.o\
	$(OBJ_DIR)/agentUtils.o

REQUESTOR_OBJ=\
	$(OBJ_DIR)/requestor.o\
	$(OBJ_DIR)/requestorInit.o\
	$(OBJ_DIR)/requestorUtils.o

CFLAGS=\
	-c \
	-Wall \
	-D $(DE) \
	-I $(LOCAL_INCL_DIR) \
	-I $(SIMPL_INCL_DIR)

LDFLAGS=\
	-L$(SIMPL_DIR)/lib\
	-lsimplmisc\
	-lsimpllog\
	-lsimpl

ARCHFLAGS =

HEADERS=

THIS_TARGET="starting"
DO_END=make -s title THIS_TARGET="<$@> done"

#========================
# Default targets
#========================
all:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/agent\
     $(BIN_DIR)/requestor
	@$(DO_END)

title:
	@echo "=============== agency/test $(THIS_TARGET) ================"

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
$(BIN_DIR)/agent:	$(AGENT_OBJ)
	$(CC) -o $(BIN_DIR)/agent $(AGENT_OBJ) $(LDFLAGS)
	
$(BIN_DIR)/requestor:	$(REQUESTOR_OBJ)
	$(CC) -o $(BIN_DIR)/requestor $(REQUESTOR_OBJ) $(LDFLAGS)
	
#===================
# Compiles
#===================
$(OBJ_DIR)/agent.o: agent.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/agent.o agent.c

$(OBJ_DIR)/agentInit.o: agentInit.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/agentInit.o agentInit.c

$(OBJ_DIR)/agentUtils.o: agentUtils.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/agentUtils.o agentUtils.c

$(OBJ_DIR)/requestor.o: requestor.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/requestor.o requestor.c

$(OBJ_DIR)/requestorInit.o: requestorInit.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/requestorInit.o requestorInit.c

$(OBJ_DIR)/requestorUtils.o: requestorUtils.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/requestorUtils.o requestorUtils.c

#========================
# Cleanup
#========================
clobber: clean
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/agent
	@-rm -f $(BIN_DIR)/requestor
	@$(DO_END)

#========================
# Install
#========================
install:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/agent\
     $(BIN_DIR)/requestor
	cp $(BIN_DIR)/agent $(INSTALL_BIN_DIR)/agent
	cp $(BIN_DIR)/requestor $(INSTALL_BIN_DIR)/requestor
	@$(DO_END)

#===================
#  i386
#===================
i386:
	make install ARCHFLAGS="-march=i386"
	@echo agency i386

