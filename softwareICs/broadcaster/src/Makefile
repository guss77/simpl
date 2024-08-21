#=======================================================
#
# DESCRIPTION:	
# Makefile for softwareICs/broadcaster/src tree.
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
# Revision history:
#=======================================================
# $Log: Makefile,v $
# Revision 1.3  2011/03/23 17:28:44  bobfcsoft
# removed space in -L option for Mac compatibility
#
# Revision 1.2  2009/04/14 15:51:30  bobfcsoft
# added i386 target
#
# Revision 1.1  2007/07/27 14:13:04  bobfcsoft
# new cvs file
#
# Revision 1.2  2002/12/03 21:12:09  root
# v2.0 compatible
#
# Revision 1.1  2002/10/30 15:58:45  root
# Initial revision
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

FC_MGR_OBJ=\
	$(OBJ_DIR)/fcMgr.o\
	$(OBJ_DIR)/fcMgrInit.o\
	$(OBJ_DIR)/fcMgrUtils.o

FC_BROADCASTER_OBJ=\
	$(OBJ_DIR)/fcBroadcaster.o\
	$(OBJ_DIR)/fcBroadInit.o\
	$(OBJ_DIR)/fcBroadUtils.o

CFLAGS=\
	-c\
	-g\
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
     $(BIN_DIR)/fcBroadcaster\
     $(BIN_DIR)/fcMgr
	@$(DO_END)

title:
	@echo "=============== broadcaster/src $(THIS_TARGET) ================"

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
$(BIN_DIR)/fcBroadcaster:	$(FC_BROADCASTER_OBJ)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) -o $(BIN_DIR)/fcBroadcaster $(FC_BROADCASTER_OBJ) $(LDFLAGS)

$(BIN_DIR)/fcMgr:	$(FC_MGR_OBJ)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) -o $(BIN_DIR)/fcMgr $(FC_MGR_OBJ) $(LDFLAGS)

#===================
# Compiles
#===================
$(OBJ_DIR)/fcBroadcaster.o: fcBroadcaster.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/fcBroadcaster.o fcBroadcaster.c

$(OBJ_DIR)/fcBroadInit.o: fcBroadInit.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/fcBroadInit.o fcBroadInit.c

$(OBJ_DIR)/fcBroadUtils.o: fcBroadUtils.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/fcBroadUtils.o fcBroadUtils.c

$(OBJ_DIR)/fcMgr.o: fcMgr.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/fcMgr.o fcMgr.c

$(OBJ_DIR)/fcMgrInit.o: fcMgrInit.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/fcMgrInit.o fcMgrInit.c

$(OBJ_DIR)/fcMgrUtils.o: fcMgrUtils.c
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(ARCHFLAGS) $(CFLAGS) -o $(OBJ_DIR)/fcMgrUtils.o fcMgrUtils.c

#===================
# Cleanup
#===================
clobber: clean
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(BIN_DIR)/fcBroadcaster
	@-rm -f $(BIN_DIR)/fcMgr
	@$(DO_END)

#===================
# Install
#===================
install:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(BIN_DIR)/fcBroadcaster\
     $(BIN_DIR)/fcMgr
	cp $(BIN_DIR)/fcBroadcaster $(INSTALL_BIN_DIR)/fcBroadcaster
	cp $(BIN_DIR)/fcMgr $(INSTALL_BIN_DIR)/fcMgr
	@$(DO_END)

#===================
#  i386
#===================
i386:
	make install ARCHFLAGS="-march=i386"
	@echo broadcaster i386

