#=======================================================
#
# DESCRIPTION:	
# Makefile for softwareICs/relay/src tree.
#
# AUTHOR:	R.D. Findlay
#
#-----------------------------------------------------------------------
#    Copyright (C) 2006 iCanProgram Inc. 
#
#    This software is in the public domain.
#    Permission to use, copy, modify, and distribute this software and its
#    documentation for any purpose and without fee is hereby granted, 
#    without any conditions or restrictions.
#    This software is provided "as is" without express or implied warranty.
#
#    If you discover a bug or add an enhancement contact us on
#    the SIMPL project mailing list. 
#
#-----------------------------------------------------------------------
# Revision history:
#=======================================================
# $Log: Makefile,v $
# Revision 1.3  2011/03/23 17:35:30  bobfcsoft
# removed space in -L option for Mac compatibility
#
# Revision 1.2  2009/04/14 16:12:15  bobfcsoft
# added i386 target
#
# Revision 1.1  2006/06/21 21:05:44  bobfcsoft
# new proxy code
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
LIB_DIR=../lib

INSTALL_BIN_DIR=$(SOFT_IC_DIR)/bin
INSTALL_LIB_DIR=$(SOFT_IC_DIR)/lib

LOCAL_INCL_DIR=../include
SIMPL_INCL_DIR=$(SIMPL_DIR)/include

PROXY_OBJ=\
	$(OBJ_DIR)/proxy.o\
	$(OBJ_DIR)/proxyInit.o\
	$(OBJ_DIR)/proxyUtils.o

CDFLAGS=\
	-c\
	-Wall\
        -I $(LOCAL_INCL_DIR)\
        -I $(SIMPL_INCL_DIR)

LDFLAGS=\
	-L$(SIMPL_DIR)/lib\
	-lsimplmisc\
	-lsimpllog\
	-lsimpl

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
     $(BIN_DIR)/proxy
	@$(DO_END)

title:
	@echo "=============== proxy/src $(THIS_TARGET) ================"

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
$(BIN_DIR)/proxy:	$(PROXY_OBJ)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) -o $(BIN_DIR)/proxy $(PROXY_OBJ) $(LDFLAGS)

#===================
# Compiles
#===================
$(OBJ_DIR)/proxy.o: proxy.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CDFLAGS) -o $(OBJ_DIR)/proxy.o proxy.c

$(OBJ_DIR)/proxyInit.o: proxyInit.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CDFLAGS) -o $(OBJ_DIR)/proxyInit.o proxyInit.c

$(OBJ_DIR)/proxyUtils.o: proxyUtils.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CDFLAGS) -o $(OBJ_DIR)/proxyUtils.o proxyUtils.c

#===================
# Cleanup
#===================
clean: clobber
clobber:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/proxy
	@$(DO_END)

#===================
# Install
#===================
install:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/proxy
	cp $(BIN_DIR)/proxy $(INSTALL_BIN_DIR)/proxy
	@$(DO_END)

#===================
#  i386
#===================
i386:
	make install ARCHFLAGS="-march=i386"
	@echo proxy i386

