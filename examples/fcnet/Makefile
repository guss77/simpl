#===============================================================
#
#  Makefile for fcnet tree
#
#-----------------------------------------------------------------------
#    Copyright (C) 2002, 2007 FCSoftware Inc. 
#
#    This library is free software; you can redistribute it and/or
#    modify it under the terms of the GNU Lesser General Public
#    License as published by the Free Software Foundation; either
#    version 2.1 of the License, or (at your option) any later version.
#
#    This library is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
#    Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public
#    License along with this library; if not, write to the Free Software
#    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#
#    If you discover a bug or add an enhancement contact us on the
#    SIMPL project mailing list.
#-----------------------------------------------------------------------
#===============================================================
#$Log: Makefile,v $
#Revision 1.2  2007/07/24 20:44:50  bobfcsoft
#new contact info
#
#Revision 1.1  2005/12/20 15:31:34  bobfcsoft
#initial commit
#
#===============================================================

PROJECT=FCNET

SRC_DIR=src

#===================================
# entry point for simple make
#===================================
all:
	@echo "$(PROJECT) build <all> starting"
	@echo `date`
	@cd $(SRC_DIR); make -i 
	@echo "$(PROJECT) <all> done"
	@echo `date`

#===================================
# to force a total rebuild
#===================================
clobber:
	@echo "$(PROJECT) <clobber> starting"
	@cd $(SRC_DIR); make -s clobber
	@echo "$(PROJECT) <clobber> done"

#===================================
# to move into master area
#===================================
install:
	@echo "$(PROJECT) build <install> starting"
	@echo `date`
	@cd $(SRC_DIR); make -i install
	@echo "$(PROJECT) <install> done"
	@echo `date`
