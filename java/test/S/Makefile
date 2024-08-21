#=======================================================================
#
# FILE:			Makefile
#
# DESCRIPTION:	This is the local test make file.
#
# AUTHOR:		FC Software Inc.
#-----------------------------------------------------------------------
#    Copyright (C) 2000, 2008 FCSoftware Inc. 
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
#    If you discover a bug or add an enhancement contact us on the: 
#
#	SIMPL project mailing list
#-----------------------------------------------------------------------
#
# Revision history:
# ======================================================================
# $Log: Makefile,v $
# Revision 1.2  2009/05/10 15:52:54  johnfcsoft
# cleanup
#
# Revision 1.1  2009/05/01 14:09:10  johnfcsoft
# initial entry
#
#=======================================================================

#====================================================================
# definitions
#====================================================================

CLASS_DIR = ../../class

#=====================================================================
# Default targets
#=====================================================================
all: \
	title \
	javac
	@echo java simpl/test all

title:
	@echo java simpl/test build starting

javac:
	@echo running the java compiler ...
	javac -classpath $(CLASS_DIR) -d $(CLASS_DIR) PackStest1.java
	javac -classpath $(CLASS_DIR) -d $(CLASS_DIR) PackStest2.java
	javac -classpath $(CLASS_DIR) -d $(CLASS_DIR) PackStest3.java
	javac -classpath $(CLASS_DIR) -d $(CLASS_DIR) ReceiverSbinary.java
	javac -classpath $(CLASS_DIR) -d $(CLASS_DIR) ReceiverScharacter.java
	javac -classpath $(CLASS_DIR) -d $(CLASS_DIR) ReceiverSoffset.java
	javac -classpath $(CLASS_DIR) -d $(CLASS_DIR) SenderSbinary.java
	javac -classpath $(CLASS_DIR) -d $(CLASS_DIR) SenderScharacter.java
	javac -classpath $(CLASS_DIR) -d $(CLASS_DIR) SenderSoffset.java
#===================
#  clean
#===================
clean:
	@-rm -f $(CLASS_DIR)/PackStest*.class
	@-rm -f $(CLASS_DIR)/ReceiverS*.class
	@-rm -f $(CLASS_DIR)/SenderS*.class
	@echo java simplipc/test clean

install: all
