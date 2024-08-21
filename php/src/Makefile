###############################################
#
# Makefile - for SIMPL php
#
#-----------------------------------------------------------------------
#    Copyright (C) 2011 FCSoftware Inc. 
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
#Revision 1.1  2011/09/08 13:14:53  bobfcsoft
#new file
#
#
###############################################

CC=cc
DE=

line1 = --------------------------------------------------------------------

LIB_DIR=../../lib
 
#========================
# Default targets
#========================
all:\
    title \
    $(LIB_DIR)/SIMPL.php
	@echo SIMPL-PHP all

title:
	@echo SIMPL-PHP build starting

description:
	@(\
	echo;\
	echo "$(line1)";\
	echo "Compiling module -> $<";\
	echo )

#===================
# Library 
#===================
$(LIB_DIR)/SIMPL.php: SIMPL.php
	cp SIMPL.php $(LIB_DIR)/SIMPL.php

#===================
# Compiles
#===================

#===================
#  install
#===================
install:\
    title \
    $(LIB_DIR)/SIMPL.php
	@echo SIMPL-PHP install

#===================
#  clean
#===================
clean:
	@-rm -f $(LIB_DIR)/SIMPL.php
	@echo SIMPL-PHP clean
