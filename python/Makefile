#================================================
#
#    python top level build
#
#-----------------------------------------------------------------------
#    Copyright (C) 2003,2007 FCSoftware Inc. 
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
#
#-----------------------------------------------------------------------
#
#$Log: Makefile,v $
#Revision 1.6  2013/06/24 17:55:28  bobfcsoft
#cleanup
#
#Revision 1.4  2010/02/10 14:53:34  bobfcsoft
#call test makefile
#
#Revision 1.3  2008/11/26 17:25:19  bobfcsoft
#cleanup
#
#Revision 1.2  2007/09/12 16:36:08  bobfcsoft
#added fPIC flag for 64bit compile
#
#Revision 1.1.1.1  2005/03/27 11:51:04  paul_c
#Initial import
#
#Revision 1.3  2003/10/06 18:06:36  root
#fix to Python version hook
#
#Revision 1.2  2003/10/04 11:47:33  root
#added PYTHON_VERSION
#
#Revision 1.1  2003/06/24 14:21:44  root
#Initial revision
#
PROJECT=SIMPL
TASK=python

PYTHONVER=2.7
RELEASE=2

SRC_DIR=src
TEST_DIR=test

#===================================
# entry point for simple make
#===================================
all:
	@echo "$(PROJECT) $(TASK) build <all> starting"
	@echo `date`
	@make -C $(SRC_DIR) PYTHONVER=$(PYTHONVER) RELEASE=$(RELEASE)
	@make -C $(TEST_DIR)
	@echo "$(PROJECT) $(TASK) <all> done"
	@echo `date`

#=================================
# to force a total rebuild
#=================================
clean:
	@echo "$(PROJECT) $(TASK) <clean> starting"
	@make -C $(SRC_DIR) -s clean
	@make -C $(TEST_DIR) -s clean
	@echo "$(PROJECT) $(TASK) <clean> done"

#========================
# to move into master area
#========================
install:
	@echo "$(PROJECT) $(TASK) build <install> starting"
	@echo `date`
	@make -C $(SRC_DIR) install PYTHONVER=$(PYTHONVER) RELEASE=$(RELEASE)
	@make -C $(TEST_DIR) install
	@echo "$(PROJECT) $(TASK) <install> done"
	@echo `date`