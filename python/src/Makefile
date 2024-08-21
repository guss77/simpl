###############################################
#
# Makefile - for simpl python versions 2 and 3 C extended libraries
#
#-----------------------------------------------------------------------
#    Copyright (C) 1999, 2002, 2007 FCSoftware Inc. 
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
#$Log: Makefile,v $
#Revision 1.13  2014/05/30 20:09:48  bobfcsoft
#latest stuff
#
#
###############################################

# default command line defs
PYTHONVER=2.7
RELEASE=2

SIMPL_OBJS=../../simplipc/src/obj/simpl.o ../../simplipc/src/obj/simplUtils.o
MOD_DIR=../modules
OBJ_DIR=./obj
LIB_DIR=../lib
INCL_DIR1=/usr/include/python$(PYTHONVER)
INCL_DIR2=../include
INCL_DIR3=../../include
MY_LIBRARY=simpl$(RELEASE).so
MY_OBJECT=simpl$(RELEASE).o
MY_SOURCE=simpl$(RELEASE)module.c

CC=cc 
CFLAGS=-fPIC -Wall -I$(INCL_DIR1) -I$(INCL_DIR2) -I$(INCL_DIR3)
LFLAGS=-shared $(SIMPL_OBJS)

description:
	@(\
	echo;\
	echo Python SIMPL build starting; \
	echo "Compiling $(MY_SOURCE) --> $(MY_LIBRARY)";\
	echo;\
	echo "** Note that this library works only for Python $(RELEASE) **";\
	echo;\
	echo "To change Python Version and Release type (for example):";\
	echo "make all/install PYTHONVER=3.3m RELEASE=3";\
	echo;\
	echo "To find the Python versions available on your computer type:";\
	echo "find / -name Python.h";\
	echo "and examine the path results of the search.";\
	echo;\
	echo "RELEASE is usually the major number of the Python version.";\
	echo)

#========================
# Default targets
#========================
all:\
	description\
	$(LIB_DIR)/$(MY_LIBRARY)
	cp $(LIB_DIR)/$(MY_LIBRARY) $(MOD_DIR)
	@echo python simpl all

#===================
# Library 
#===================
$(LIB_DIR)/$(MY_LIBRARY): $(OBJ_DIR)/$(MY_OBJECT)
	$(CC) $(LFLAGS) $< -o $@

#===================
# Compiles
#===================
$(OBJ_DIR)/$(MY_OBJECT): $(MY_SOURCE)
	$(CC) -c $(CFLAGS) -o $@ $(MY_SOURCE)

#===================
#  install
#===================
install:\
	description\
	$(LIB_DIR)/$(MY_LIBRARY)
	cp $(LIB_DIR)/$(MY_LIBRARY) $(MOD_DIR)
	cp $(MOD_DIR)/$(MY_LIBRARY) $(SIMPL_HOME)/modules
	cp $(MOD_DIR)/csimpl.py $(SIMPL_HOME)/modules
	cp $(MOD_DIR)/tclsimpl.py $(SIMPL_HOME)/modules
	@echo python simpl install

#===================
#  clean
#===================
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(LIB_DIR)/$(MY_LIBRARY)
	@-rm -f $(MOD_DIR)/$(MY_LIBRARY)
	@-rm -f $(SIMPL_HOME)/modules/$(MY_LIBRARY)
	@echo python simpl clean 