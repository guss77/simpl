#===============================================================
#
#  Makefile for tclet4 tree
#
#  FCsoftware Inc. 2000, 2007
#  This code is released as open source.   We hope you find 
#  it useful.  If you discover a bug or add an enhancement 
#  contact us on the SIMPL project mailing list. 
#
#===============================================================
#
#$Log: Makefile,v $
#Revision 1.1  2007/07/27 14:16:01  bobfcsoft
#new cvs file
#
#
#===============================================================

PROJECT=SIMPL

SRC_DIR=src
TEST_DIR=test

#===================================
# entry point for simple make
#===================================
all:
	@echo "$(PROJECT) tclet4 build <all> starting"
	@echo `date`
	@cd $(SRC_DIR); make -i 
	@cd $(TEST_DIR); make -i 
	@echo "$(PROJECT) tclet4 <all> done"
	@echo `date`

#===================================
# to force a total rebuild
#===================================
clobber:
	@echo "$(PROJECT) tclet4 <clobber> starting"
	@cd $(SRC_DIR); make -s clobber
	@cd $(TEST_DIR); make -s clobber
	@echo "$(PROJECT) tclet4 <clobber> done"

#===================================
# to move into master area
#===================================
install:
	@echo "$(PROJECT) tclet4 build <install> starting"
	@echo `date`
	@cd $(SRC_DIR); make -i install
	@cd $(TEST_DIR); make -i install
	@echo "$(PROJECT) tclet4 <install> done"
	@echo `date`
