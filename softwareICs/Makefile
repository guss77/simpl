#=======================================================
#
# DESCRIPTION:	
# Makefile for softwareICs tree.
#
# AUTHOR:	R.D. Findlay
#
#-------------------------
# iCanProgram Inc. 2006,2008
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
# Revision 1.4  2009/04/14 18:48:02  bobfcsoft
# added i386 target
#
# Revision 1.3  2009/01/12 19:51:56  johnfcsoft
# CVS thinks there was a change
#
# Revision 1.2  2008/11/27 02:08:13  bobfcsoft
# cleanup
#
# Revision 1.1  2006/06/26 18:03:15  bobfcsoft
# statemachine
#
#=======================================================

PROJECT=SIMPL
TASK=softwareICs

BROADCASTER_DIR=broadcaster
COURIER_DIR=courier
AGENCY_DIR=agency
RELAY_DIR=relay
STIMULATOR_DIR=stimulator
EMITTER_DIR=pollingEmitter
SCHEDULER_DIR=scheduler
PROXY_DIR=proxy
STATEMACHINE_DIR=statemachine

#===================================
# entry point for simple make
#===================================
all:
	@echo "$(PROJECT) $(TASK) build <all> starting"
	@echo `date`
	@make -C $(BROADCASTER_DIR)
	@make -C $(COURIER_DIR)
	@make -C $(AGENCY_DIR)
	@make -C $(RELAY_DIR)
	@make -C $(STIMULATOR_DIR)
	@make -C $(EMITTER_DIR)
	@make -C $(SCHEDULER_DIR)
	@make -C $(PROXY_DIR)
	@make -C $(STATEMACHINE_DIR)
	@echo "$(PROJECT) $(TASK) <all> done"
	@echo `date`

#=================================
# to force a total rebuild
#=================================
clean:
	@echo "$(PROJECT) $(TASK) build <clean> starting"
	@make -C $(BROADCASTER_DIR) clean
	@make -C $(COURIER_DIR) clean
	@make -C $(AGENCY_DIR) clean
	@make -C $(RELAY_DIR) clean
	@make -C $(STIMULATOR_DIR) clean
	@make -C $(EMITTER_DIR) clean
	@make -C $(SCHEDULER_DIR) clean
	@make -C $(PROXY_DIR) clean
	@make -C $(STATEMACHINE_DIR) clean
	@echo "$(PROJECT) $(TASK) <clean> done"

#========================
# to move into master area
#========================
install:
	@echo "$(PROJECT) $(TASK) build <install> starting"
	@echo `date`
	@make -C $(BROADCASTER_DIR) install
	@make -C $(COURIER_DIR) install
	@make -C $(AGENCY_DIR) install
	@make -C $(RELAY_DIR) install
	@make -C $(STIMULATOR_DIR) install
	@make -C $(EMITTER_DIR) install
	@make -C $(SCHEDULER_DIR) install
	@make -C $(PROXY_DIR) install
	@make -C $(STATEMACHINE_DIR) install
	@echo "$(PROJECT) $(TASK) <install> done"
	@echo `date`

#===================
#  i386
#===================
i386:
	make install ARCHFLAGS="-march=i386"
	@echo softwareICs i386

