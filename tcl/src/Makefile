###############################################
#
# Makefile - for Tcl extension 
#
# NOTE:
# This make requires that Tcl8.0.x is installed
#
#-----------------------------------------------------------------------
#    Copyright (C) 1998-2009  FCSoftware Inc. 
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
# $Log: Makefile,v $
# Revision 1.12  2013/05/29 20:16:04  bobfcsoft
# changed to Wl link paramater
#
# Revision 1.11  2009/04/13 17:26:37  bobfcsoft
# CVS issues
#
# Revision 1.10  2009/04/13 17:22:42  bobfcsoft
# added i386 target
#
# Revision 1.9  2009/01/19 20:27:28  bobfcsoft
# relocate tclSurrogate
#
# Revision 1.8  2009/01/13 21:51:38  bobfcsoft
# cleanup
#
# Revision 1.7  2009/01/12 19:51:32  johnfcsoft
# CVS thinks there was a change
#
# Revision 1.6  2008/11/26 17:31:49  bobfcsoft
# cleanup
#
# Revision 1.5  2007/07/24 21:47:20  bobfcsoft
# new contact info
#
# Revision 1.4  2006/08/08 14:43:16  bobfcsoft
# eliminated symbolic links in make
#
# Revision 1.3  2006/01/26 02:14:04  bobfcsoft
# more enhancements for Tcl to Windows
#
# Revision 1.2  2005/11/12 12:22:57  bobfcsoft
# cleanup
#
# Revision 1.1.1.1  2005/03/27 11:50:45  paul_c
# Initial import
#
# Revision 1.13  2003/09/11 15:42:25  root
# fixed DE define
#
# Revision 1.12  2002/11/22 16:31:00  root
# 2.0rc3
#
# Revision 1.11  2002/06/12 18:25:57  root
# fcipc merge completed
#
# Revision 1.10  2002/01/31 14:33:27  root
# allow for older versions of Tcl/Tk
#
# Revision 1.9  2001/12/15 12:25:13  root
# fixed -g option with DE and debug target
#
# Revision 1.8  2001/07/05 14:44:11  root
# added debug target
#
# Revision 1.7  2001/01/27 14:19:47  root
# using new simplmisc library instead of qnx library
#
# Revision 1.6  2000/10/13 13:39:35  root
# convert to SIMPL_HOME
#
# Revision 1.5  1999/11/04 15:39:22  root
# added tclSurrogate stuff
#
# Revision 1.4  1999/09/02 12:18:38  root
# fixed dependancy on /root to $(FC_DIR)
#
# Revision 1.3  1999/04/08 14:34:29  root
# force links
#
# Revision 1.2  1999/02/04 15:32:49  root
# cleanup
#
# Revision 1.1  1999/01/30 15:10:19  root
# Initial revision
#
#
###############################################

CC=cc
DE=NODEBUG
TCLVER=8.3
TCLDEF=8_3

PROGRAM_NAME=
line1 = --------------------------------------------------------------------
line2 = ====================================================================

DEST_DIR=.

OBJ_DIR=obj
LIB_DIR=../lib
BIN_DIR=../bin
SIMPL_DIR=../..

INSTALL_LIB_DIR=$(SIMPL_DIR)/lib
INSTALL_BIN_DIR=$(SIMPL_DIR)/bin

SIMPL_SRC_DIR=$(SIMPL_DIR)/simplipc/src

LOCAL_INCL_DIR=../include
INCL_DIR=$(SIMPL_DIR)/include
TCL_INCL_DIR=/usr/include/tcl$(TCLVER)
TCL_INCL_DIR2=/usr/local/include

FCTCLX_OBJ=\
	$(OBJ_DIR)/fctclx.o\
	$(OBJ_DIR)/simpl.o\
	$(OBJ_DIR)/simplUtils.o

MY_LIBRARY=libfctclx.so
SONAME=libfctclx.so.1

CFLAGS=\
	-D$(DE)\
	-Wall\
	-I $(LOCAL_INCL_DIR)\
	-I $(INCL_DIR)

LDFLAGS=\
	-L $(SIMPL_DIR)/lib\
	-lsimplmisc\
	-lsimpllog\
	-lsimpl\
	-L $(LIB_DIR)\
	-lfcsocket

CFLAGS1=\
	-D$(DE)\
	-fPIC\
	-DTCL$(TCLDEF) \
        -I $(TCL_INCL_DIR)\
        -I $(TCL_INCL_DIR2)\
        -I $(LOCAL_INCL_DIR)\
        -I $(INCL_DIR)

LDFLAGS1=\
	-shared\
	-Wl,-soname,$(SONAME)\
	-lc\
	-L $(SIMPL_DIR)/lib\
	-lsimpl

ARCHFLAGS=


#========================
# Default targets
#========================
all:\
     title \
     $(LIB_DIR)/fcsocket.tcl\
     $(LIB_DIR)/fcgateway.tcl\
     $(LIB_DIR)/pkgIndex.tcl\
     $(LIB_DIR)/$(MY_LIBRARY)
	@echo tclstuff all

title:
	@echo tclstuff build starting

description:
	@(\
	echo;\
	echo "$(line1)";\
	echo "Compiling $(PROGRAM_NAME) -> $(OBJ_NAME)";\
	echo )

#========================
# Link
#========================
$(LIB_DIR)/fcgateway.tcl: fcgateway.tcl
	cp fcgateway.tcl $(LIB_DIR)/fcgateway.tcl
	chmod a+w $(LIB_DIR)/fcgateway.tcl

$(LIB_DIR)/fcsocket.tcl: fcsocket.tcl
	cp fcsocket.tcl $(LIB_DIR)/fcsocket.tcl
	chmod a+w $(LIB_DIR)/fcsocket.tcl

$(LIB_DIR)/pkgIndex.tcl: pkgIndex.tcl
	cp pkgIndex.tcl $(LIB_DIR)/pkgIndex.tcl
	chmod a+w $(LIB_DIR)/pkgIndex.tcl

$(LIB_DIR)/libfctclx.so: $(FCTCLX_OBJ) 
	gcc $(LDFLAGS1) -o $(LIB_DIR)/libfctclx.so $(FCTCLX_OBJ)

$(LIB_DIR)/i386/libfctclx.so: $(FCTCLX_OBJ) 
	gcc $(LDFLAGS1) -o $(LIB_DIR)/i386/libfctclx.so $(FCTCLX_OBJ)

#===================
# Compiles
#===================
$(OBJ_DIR)/fctclx.o: fctclx.c
	$(CC) -c $(CFLAGS1) $(ARCHFLAGS) -o $(OBJ_DIR)/fctclx.o fctclx.c

$(OBJ_DIR)/simpl.o: $(SIMPL_SRC_DIR)/simpl.c
	$(CC) -c $(CFLAGS1) $(ARCHFLAGS) -o $(OBJ_DIR)/simpl.o $(SIMPL_SRC_DIR)/simpl.c

$(OBJ_DIR)/simplUtils.o: $(SIMPL_SRC_DIR)/simplUtils.c
	$(CC) -c $(CFLAGS1) $(ARCHFLAGS) -o $(OBJ_DIR)/simplUtils.o $(SIMPL_SRC_DIR)/simplUtils.c

#===================
# Cleanup
#===================
clean:
	@-rm -f $(OBJ_DIR)/*.o
	@-rm -f $(LIB_DIR)/*.so
	@-rm -f $(LIB_DIR)/*.a
	@echo tclstuff clean

#===================
# Install
#===================
install:\
     title \
     $(LIB_DIR)/fcsocket.tcl\
     $(LIB_DIR)/fcgateway.tcl\
     $(LIB_DIR)/pkgIndex.tcl\
     $(LIB_DIR)/$(MY_LIBRARY)
	cp $(LIB_DIR)/fcgateway.tcl $(INSTALL_LIB_DIR)/fcgateway.tcl
	cp $(LIB_DIR)/fcsocket.tcl $(INSTALL_LIB_DIR)/fcsocket.tcl
	cp $(LIB_DIR)/pkgIndex.tcl $(INSTALL_LIB_DIR)/pkgIndex.tcl
	cp $(LIB_DIR)/$(MY_LIBRARY) $(INSTALL_LIB_DIR)
	@echo tclstuff install

#===================
#  i386
#===================
i386:
	make install MY_LIBRARY="i386/libfctclx.so" ARCHFLAGS="-march=i386"
	@echo tclstuff i386

#===================
#  debug
#===================
debug:
	make install DE=-g
	@echo tclstuff debug
