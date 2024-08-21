#===============================================================
#
# Makefile   - for tclet3/src  
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
###############################################
#
#$Log: Makefile,v $
#Revision 1.1  2007/07/26 16:09:43  bobfcsoft
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

TCLET_TCL_PARTS=\
	topPart.tcl\
	globalVars.tcl\
	guiHandlers.tcl\
	rpcUtils.tcl\
	bottomPart.tcl

#========================
# Default targets
#========================
all:\
     title \
     $(BIN_DIR)\
     $(BIN_DIR)/tclet3.html\
     $(BIN_DIR)/tclet3.tcl
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
$(BIN_DIR)/tclet3.tcl: $(TCLET_TCL_PARTS)
	cat $(TCLET_TCL_PARTS) > $(BIN_DIR)/tclet3.tcl
	chmod a+x $(BIN_DIR)/tclet3.tcl

$(BIN_DIR)/tclet3.html: tclet3.html
	cp tclet3.html $(BIN_DIR)/tclet3.html
	chmod a+w $(BIN_DIR)/tclet3.html

#========================
# cleanup
#========================
clobber:\
	title
	@-rm $(BIN_DIR)/tclet3.tcl
	@-rm $(BIN_DIR)/tclet3.html
	@echo tclet/src clobber

#========================
# install
#========================
install:\
     title \
     $(BIN_DIR)\
     $(BIN_DIR)/tclet3.html\
     $(BIN_DIR)/tclet3.tcl
	cp $(BIN_DIR)/tclet3.tcl $(INSTALL_BIN_DIR)/tclet3.tcl
	cp $(BIN_DIR)/tclet3.html $(INSTALL_BIN_DIR)/tclet3.html
	@echo tclet/src install done
