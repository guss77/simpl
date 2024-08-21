###############################################
#
# Makefile - for java simpl
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
#Revision 1.8  2009/05/04 18:20:34  johnfcsoft
#cleanup
#
#Revision 1.7  2009/05/01 13:17:19  johnfcsoft
#added Ssimpl
#
#Revision 1.6  2009/03/25 18:38:45  johnfcsoft
#new make file
#
#Revision 1.4  2009/03/23 15:36:30  bobfcsoft
#installed to lib not modules
#
#Revision 1.3  2009/03/23 15:30:46  bobfcsoft
#fixes
#
#Revision 1.2  2009/03/23 15:24:07  bobfcsoft
#added i386 target
#
#Revision 1.1  2009/03/12 13:40:36  johnfcsoft
#initial entry
#

###############################################

CC=cc
DE=
OS_TYPE = _LINUX_OS

line1 = --------------------------------------------------------------------

SIMPL_DIR=../../simplipc/src
OBJ_DIR=./obj
LIB_DIR=../lib
INCL_DIR1=../include
INCL_DIR2=../../include
CLASS_DIR=../class

SIMPL_OBJS=\
	$(OBJ_DIR)/jsimpl.o\
	$(OBJ_DIR)/simpl.o\
	$(OBJ_DIR)/simplUtils.o

CFLAGS=\
	$(DE)\
	-D$(OS_TYPE)\
	-fPIC\
	-Wall\
	-I $(INCL_DIR1)\
	-I $(INCL_DIR2)

ARCHFLAGS=

LDFLAGS=-shared

MYLIBRARY=libjsimpl.so

#========================
# Default targets
#========================
all: \
	title \
	$(CLASS_DIR)/Ssimpl.class \
	$(CLASS_DIR)/Jsimpl.class \
	$(LIB_DIR)/$(MYLIBRARY)
	@echo java simpl all

title:
	@echo java simpl build starting

#===================
# Library
#===================
$(LIB_DIR)/$(MYLIBRARY): $(SIMPL_OBJS)
	$(CC) $(LDFLAGS) $? -o $@

#===================
# Compiles
#===================
$(OBJ_DIR)/jsimpl.o: jsimpl.c $(INCL_DIR1)/jsimpl.h
	$(CC) -c $(ARCHFLAGS) $(CFLAGS) -o $@ $<
			
$(OBJ_DIR)/simpl.o: $(SIMPL_DIR)/simpl.c
	$(CC) -c $(ARCHFLAGS) -O $(CFLAGS) -o $@ $<

$(OBJ_DIR)/simplUtils.o: $(SIMPL_DIR)/simplUtils.c
	$(CC) -c $(ARCHFLAGS) -O $(CFLAGS) -o $@ $<

$(CLASS_DIR)/Jsimpl.class: Jsimpl.java
	@echo running the java compiler ...
	javac -d $(CLASS_DIR) Jsimpl.java

$(INCL_DIR1)/jsimpl.h:
	@echo running the java header generator ...
	javah -jni -classpath $(CLASS_DIR) -o $(INCL_DIR1)/jsimpl.h Jsimpl

$(CLASS_DIR)/Ssimpl.class: Ssimpl.java
	@echo running the java compiler ...
	javac -d $(CLASS_DIR) Ssimpl.java

#===================
#  install
#===================
install: \
	title \
	$(CLASS_DIR)/Ssimpl.class \
	$(CLASS_DIR)/Jsimpl.class \
	$(LIB_DIR)/$(MYLIBRARY)
	cp $(LIB_DIR)/$(MYLIBRARY) $(SIMPL_HOME)/lib
	@echo java simpl install

#===================
#  clean
#===================
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(LIB_DIR)/$(MYLIBRARY)
	@-rm -f $(CLASS_DIR)/Jsimpl.class
	@-rm -f $(CLASS_DIR)/Ssimpl*.class
	@-rm -f $(INCL_DIR1)/jsimpl.h
	@echo java simpl clean
