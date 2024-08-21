#===============================================================
#
#  Makefile for simpl/tcl tree
#
#-----------------------------------------------------------------------
#    Copyright (C) 1999, 2002, 2007, 2008 FCSoftware Inc. 
#
#    This software is in the public domain.
#    Permission to use, copy, modify, and distribute this software and its
#    documentation for any purpose and without fee is hereby granted, 
#    without any conditions or restrictions.
#    This software is provided "as is" without express or implied warranty.
#
#    If you discover a bug or add an enhancement contact us on the
#    SIMPL project mailing list.
#-----------------------------------------------------------------------
#
#===============================================================
#
#$Log: Makefile,v $
#Revision 1.4  2009/01/13 21:44:24  bobfcsoft
#cleanup
#
#Revision 1.3  2008/11/26 17:31:40  bobfcsoft
#cleanup
#
#Revision 1.2  2007/07/24 21:47:20  bobfcsoft
#new contact info
#
#Revision 1.1.1.1  2005/03/27 11:50:45  paul_c
#Initial import
#
#Revision 1.3  2002/12/02 16:01:56  root
#pass in TCLVER
#
#Revision 1.2  2000/10/13 14:05:01  root
#LGPL
#
#Revision 1.1  1999/11/04 15:38:10  root
#Initial revision
#
#Revision 1.1  1999/09/09 13:29:00  root
#Initial revision
#
#
#===============================================================

PROJECT=SIMPL

TCLVER=8.3
TCLDEF=8_3

SRC_DIR=src
TEST_DIR=test

#===================================
# entry point for simple make
#===================================
all:
	@echo "$(PROJECT) tcl build <all> starting"
	@echo `date`
	@make -C $(SRC_DIR) TCLVER=$(TCLVER) TCLDEF=$(TCLDEF)
	@make -C $(TEST_DIR) 
	@echo "$(PROJECT) tcl <all> done"
	@echo `date`

#===================================
# to force a total rebuild
#===================================
clobber: clean
clean:
	@echo "$(PROJECT) tcl <clean> starting"
	@make -C $(SRC_DIR) -s clean
	@make -C $(TEST_DIR) -s clean
	@echo "$(PROJECT) tcl <clean> done"

#===================================
# to move into master area
#===================================
install:
	@echo "$(PROJECT) tcl build <install> starting"
	@echo `date`
	@make -C $(SRC_DIR) install TCLVER=$(TCLVER) TCLDEF=$(TCLDEF)
	@make -C $(TEST_DIR) install
	@echo "$(PROJECT) tcl <install> done"
	@echo `date`
