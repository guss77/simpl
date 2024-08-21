#=======================================================
#
# DESCRIPTION:	
# Makefile for examples/rtInterface/src tree.
#
# AUTHOR:	R.D. Findlay
#
#-------------------------
# FCsoftware Inc. 1999, 2007
# This code is released as open source.   We hope you find 
# it useful.  If you discover a bug or add an enhancement 
# contact us on the SIMPL project mailing list. 
#
#-------------------------
#
# Revision history:
#=======================================================
# $Log: Makefile,v $
# Revision 1.1  2007/07/26 15:51:49  bobfcsoft
# new file
#
# Revision 1.1  1999/09/16 18:16:04  root
# Initial revision
#
#=======================================================
#=======================================================

SIMPL_DIR=$(SIMPL_HOME)
RTL_BASE_DIR=/usr/src/v1.1

CC=cc
DE=NODEBUG
#DE=DEBUG
LOGGER=ERRLOG

PROGRAM_NAME=
line1 = --------------------------------------------------------------------
line2 = ====================================================================

OBJ_DIR=obj
LIB_DIR=../lib
BIN_DIR=../bin
INSTALL_BIN_DIR=../../bin
INSTALL_MOD_DIR=../../modules
INSTALL_LIB_DIR=../../lib

LOCAL_INCL_DIR=../include
INCL_DIR=../../include
SIMPL_INCL_DIR=$(SIMPL_DIR)/include
RTL_INCL_DIR=$(RTL_BASE_DIR)/linux/include
RTL_INCL_DIR2=$(RTL_BASE_DIR)/rtl/include

RTSTIM_OBJ=\
	$(OBJ_DIR)/rtStim.o

SHOWTHIS_OBJ=\
	$(OBJ_DIR)/showThis.o\
	$(OBJ_DIR)/showThisInit.o

CDFLAGS_RT=\
	-c \
	-Wall \
	-O2 \
	-fomit-frame-pointer\
	-fno-strength-reduce\
	-I $(LOCAL_INCL_DIR) \
	-I $(INCL_DIR) \
	-I $(RTL_INCL_DIR) \
	-I $(RTL_INCL_DIR2) \
	-D__KERNEL__\
	-D__RT__\
	-D$(DE)

CDFLAGS=\
	-c \
	-Wall \
	-D $(LOGGER) \
	-I $(LOCAL_INCL_DIR) \
	-I $(INCL_DIR) \
	-I $(SIMPL_INCL_DIR) \
	-I $(RTL_INCL_DIR) \
	-I $(RTL_INCL_DIR2)

LDFLAGS=\
	-L $(SIMPL_DIR)/lib\
	-lqnx\
	-lfclog\
	-lfcipc

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
     $(BIN_DIR)/rtStim \
     $(BIN_DIR)/showThis \
     $(OBJ_DIR)/rt_process.o
	@$(DO_END)

title:
	@echo "=============== rtInterface/src $(THIS_TARGET) ================"

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
$(BIN_DIR)/rtStim:	$(RTSTIM_OBJ)
	$(CC) -o $(BIN_DIR)/rtStim $(RTSTIM_OBJ) $(LDFLAGS)
	
$(BIN_DIR)/showThis:	$(SHOWTHIS_OBJ)
	$(CC) -o $(BIN_DIR)/showThis $(SHOWTHIS_OBJ) $(LDFLAGS)
	
#===================
# Compiles
#===================
$(OBJ_DIR)/rtStim.o: rtStim.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(CDFLAGS) -o $(OBJ_DIR)/rtStim.o rtStim.c

$(OBJ_DIR)/showThis.o: showThis.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(CDFLAGS) -o $(OBJ_DIR)/showThis.o showThis.c

$(OBJ_DIR)/showThisInit.o: showThisInit.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(CDFLAGS) -o $(OBJ_DIR)/showThisInit.o showThisInit.c

$(OBJ_DIR)/rt_process.o: rt_process.c $(HEADERS)
	@make -s description PROGRAM_NAME="$<" OBJ_NAME="$@"
	$(CC) $(CDFLAGS_RT) -o $(OBJ_DIR)/rt_process.o rt_process.c

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
     $(BIN_DIR)/rtStim \
     $(BIN_DIR)/showThis \
     $(OBJ_DIR)/rt_process.o
	cp $(BIN_DIR)/rtStim $(INSTALL_BIN_DIR)/rtStim
	cp $(BIN_DIR)/showThis $(INSTALL_BIN_DIR)/showThis
	cp $(OBJ_DIR)/rt_process.o $(INSTALL_MOD_DIR)/rt_process.o
	cp go $(INSTALL_BIN_DIR)/go
	cp go1 $(INSTALL_BIN_DIR)/go1
	@$(DO_END)
