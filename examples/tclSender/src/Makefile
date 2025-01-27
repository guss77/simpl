###############################################
#
# Makefile - for Tcl tester 
#
# NOTE:
# This make requires that Tcl8.0.x is installed
#
#	FCsoftware Inc. 1998, 2007
#   	This code is released as open source.   We hope you find 
#	it useful.  If you discover a bug or add an enhancement 
#	contact us on the SIMPL project mailing list. 
#
#
#$Log: Makefile,v $
#Revision 1.1  2007/07/24 21:04:05  bobfcsoft
#new file
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

INSTALL_LIB_DIR=$(SIMPL_DIR)/lib
INSTALL_BIN_DIR=../../bin

LOCAL_INCL_DIR=../include
INCL_DIR=$(SIMPL_DIR)/include
TCL_INCL_DIR=$(TCL_HOME)/generic

TCLSIM_OBJ=\
	$(OBJ_DIR)/tclSim.o

TCLSEND_PARTS=\
	topPart.tcl \
	globalVars.tcl \
	bottomPart.tcl

CDFLAGS=-c\
	-g\
	-Wall \
	-I $(LOCAL_INCL_DIR)\
	-I $(INCL_DIR)

LDFLAGS=\
	-L $(SIMPL_DIR)/lib\
	-lsimpllog\
	-lsimpl


#========================
# Default targets
#========================
all:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(LIB_DIR) \
     $(BIN_DIR)/tclSender.tcl \
     $(BIN_DIR)/tclSim
	@echo tclstuff all

title:
	@echo tclstuff build starting

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

$(LIB_DIR):
	mkdir ../lib
	chmod a+w ../lib

#========================
# Link
#========================
$(BIN_DIR)/tclSim:	$(TCLSIM_OBJ)
	$(CC) -o $(BIN_DIR)/tclSim $(TCLSIM_OBJ) $(LDFLAGS)

$(BIN_DIR)/tclSender.tcl: $(TCLSEND_PARTS)
	cat $(TCLSEND_PARTS) > $(BIN_DIR)/tclSender.tcl
	chmod a+x $(BIN_DIR)/tclSender.tcl

#========================
# Compiles
#========================
$(OBJ_DIR)/tclSim.o: tclSim.c
	$(CC) $(CDFLAGS) -o $(OBJ_DIR)/tclSim.o tclSim.c

#========================
# cleanup
#========================
clobber:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm $(BIN_DIR)/*
	@-rm -f $(LIB_DIR)/*
	@echo tclstuff clobber

#========================
# install
#========================
install:\
     title \
     $(OBJ_DIR) \
     $(BIN_DIR) \
     $(LIB_DIR) \
     $(BIN_DIR)/tclSender.tcl \
     $(BIN_DIR)/tclSim
	cp $(BIN_DIR)/tclSim $(INSTALL_BIN_DIR)/tclSim
	cp $(BIN_DIR)/tclSender.tcl $(INSTALL_BIN_DIR)/tclSender.tcl
	@echo tclstuff install
