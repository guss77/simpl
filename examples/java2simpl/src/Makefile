#===============================================================
#
#	This software was developed for
#	by
#	Computerific, Hamilton, Ontario, Canada
#
# Makefile   - for Java To SIMPL Example 
#
###############################################
#
#===============================================================

PROGRAM_NAME=NetTest
line1 = --------------------------------------------------------------------
line2 = ====================================================================

DEST_DIR=.

BIN_DIR=../bin
LIB_DIR=../lib
SIMPL_DIR=$(SIMPL_HOME)
CPLEX_DIR=$(CPLEX_HOME)

INSTALL_BIN_DIR=$(SIMPL_DIR)/examples/bin
INSTALL_LIB_DIR=$(SIMPL_DIR)/examples/lib


#========================
# Default targets
#========================
all:                          \
     title                    \
     description              \
     $(BIN_DIR)               \
     $(BIN_DIR)/*.class       \
     closing

title:
	@echo Preparing Java To SIMPL Example ...
  
description:
	@(                \
	echo;             \
	echo "$(line1)";  \
	echo "Compiling $(PROGRAM_NAME) module -> $(BIN_DIR)";\
	echo )

installing:
	@(                \
	echo;             \
	echo "$(line1)";  \
	echo "Installing $(PROGRAM_NAME) module -> $(INSTALL_BIN_DIR)";\
	echo )

closing:
	@(          \
	echo;       \
	echo "Java To SIMPL done";    \
	echo "$(line2)";              \
	echo )

ending:
	@(          \
	echo;       \
	echo "Java To SIMPL installed";    \
	echo "$(line2)";              \
	echo )

$(BIN_DIR):
	mkdir ../bin
	chmod a+w ../bin

#========================
# Link
#========================
$(BIN_DIR)/*.class: *.java
	javac *.java
	mv *.class $(BIN_DIR)/
	chmod a+x $(BIN_DIR)/*.class

#========================
# cleanup
#========================
clobber:\
	title
	@echo
	@echo $(line1)
	@-rm $(BIN_DIR)/*.class
	@-rm $(INSTALL_BIN_DIR)/*.class
	@echo Java To SIMPL clobber
	@echo $(line2)
	@echo

#========================
# install
#========================
install:\
     title \
     installing  \
     $(BIN_DIR)/*.class
	cp $(BIN_DIR)/*.class $(INSTALL_BIN_DIR)
	@echo
	@echo Java To SIMPL $(PROGRAM_NAME) installed at $(INSTALL_BIN_DIR) 
	@echo $(line2)
	@echo
