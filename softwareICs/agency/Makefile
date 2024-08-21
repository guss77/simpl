#=======================================================
#
# DESCRIPTION:	
# Makefile for softwareICs/agency tree.
#
# AUTHOR:	R.D. Findlay
#
#-------------------------
# FCsoftware Inc. 2000, 2007,2008
# This code is released as open source.   You are free to
# use this code without restriction.  We hope you find 
# it useful.  If you discover a bug or add an enhancement 
# contact us on the SIMPL project mailing list. 
#
#-------------------------
#
# Revision history:
#=======================================================
# $Log: Makefile,v $
# Revision 1.2  2009/04/14 18:50:40  bobfcsoft
# using -C construct
#
# Revision 1.1  2007/07/27 14:10:47  bobfcsoft
# new cvs file
#
#=======================================================

PROJECT=SIMPL
TASK=agency

SRC_DIR=src
TEST_DIR=test

#===================================
# entry point for simple make
#===================================
all:
	@echo "$(PROJECT) $(TASK) build <all> starting"
	@echo `date`
	@make -C $(SRC_DIR)
	@make -C $(TEST_DIR)
	@echo "$(PROJECT) $(TASK) <all> done"
	@echo `date`

#===================================
# to force a total rebuild
#===================================
clobber: clean
clean:
	@echo "$(PROJECT) $(TASK) <clobber> starting"
	@make -C $(SRC_DIR) -s clobber
	@make -C $(TEST_DIR) -s clobber
	@echo "$(PROJECT) $(TASK) <clobber> done"

#===================================
# to move into master area
#===================================
install:
	@echo "$(PROJECT) $(TASK) build <install> starting"
	@echo `date`
	@make -C $(SRC_DIR) install
	@make -C $(TEST_DIR) install
	@echo "$(PROJECT) $(TASK) <install> done"
	@echo `date`
