#===============================================================
#
# Makefile   - for tclet/src  
#
# NOTE:
# This example requires that Tcl8.0.x or better is installed.
# It also requires the TclPlugin v2.0 or better be installed.
#
#	FCsoftware Inc. 1999, 2007
#   	This code is released as open source.   We hope you find 
#	it useful.  If you discover a bug or add an enhancement 
#	contact us on the SIMPL project mailing list. 
#
#
###############################################
#
#$Log: Makefile,v $
#Revision 1.1  2007/07/26 15:59:29  bobfcsoft
#new file
#
#===============================================================

PROGRAM_NAME=
line1 = --------------------------------------------------------------------
line2 = ====================================================================

DEST_DIR=.

BIN_DIR=../bin
LIB_DIR=../lib
SIMPL_DIR=$(SIMPL_HOME)

INSTALL_BIN_DIR=../../bin

FC_TCL_PARTS=\
	topPart.tcl\
	globalVars.tcl\
	guiHandlers.tcl\
	receiveUtils.tcl\
	msgHandlers.tcl\
	bottomPart.tcl

#========================
# Default targets
#========================
all:\
     title \
     $(BIN_DIR)\
     $(BIN_DIR)/fc.html\
     $(BIN_DIR)/fc.tcl
	@echo tclet/src done

title:
	@echo Preparing Tcl/Tk GUI for examples/tclet ...

description:
	@(\
	echo;\
	echo "$(line1)";\
	echo "Compiling $(PROGRAM_NAME) module -> $<";\
	echo )

$(BIN_DIR):
	mkdir ../bin
	chmod a+w ../bin

$(LIB_DIR):
	mkdir ../lib
	chmod a+w ../lib

#========================
# Link
#========================
$(BIN_DIR)/fc.tcl: $(FC_TCL_PARTS)
	cat $(FC_TCL_PARTS) > $(BIN_DIR)/fc.tcl
	chmod a+x $(BIN_DIR)/fc.tcl

$(BIN_DIR)/fc.html: fc.html
	cp fc.html $(BIN_DIR)/fc.html
	chmod a+w $(BIN_DIR)/fc.html

#========================
# cleanup
#========================
clobber:\
	title
	@-rm $(BIN_DIR)/fc.tcl
	@-rm $(BIN_DIR)/fc.html
	@echo tclet/src clobber

#========================
# install
#========================
install:\
     title \
     $(BIN_DIR)\
     $(BIN_DIR)/fc.html\
     $(BIN_DIR)/fc.tcl
	cp $(BIN_DIR)/fc.tcl $(INSTALL_BIN_DIR)/fc.tcl
	cp $(BIN_DIR)/fc.html $(INSTALL_BIN_DIR)/fc.html
	@echo tclet/src install done
