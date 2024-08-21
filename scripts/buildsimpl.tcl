#!/bin/bash
#=========================================================
#	buildsimpl.tcl
#
# Description:
# Master build script for SIMPL tree
#
#-----------------------------------------------------------------------
#    Copyright (C) 2006 SIMPL Open Source project. 
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
#    If you discover a bug or add an enhancement here's contact us on the
#    SIMPL project mailing list. 
#
#-----------------------------------------------------------------------
#
# $Log: buildsimpl.tcl,v $
# Revision 1.7  2009/03/25 14:07:42  bobfcsoft
# check for tcl.h
#
# Revision 1.6  2009/01/13 21:42:22  bobfcsoft
# cleanup
#
# Revision 1.5  2008/12/04 13:15:47  bobfcsoft
# added support for tclx.x subdir
#
# Revision 1.4  2008/11/17 20:27:49  bobfcsoft
# use -e for file check
#
# Revision 1.3  2008/11/17 19:30:08  bobfcsoft
# better Tcl/Tk source checking
#
# Revision 1.2  2008/11/13 22:40:44  bobfcsoft
# separate make.out files
#
# Revision 1.1  2006/08/14 18:33:02  bobfcsoft
# split out tcl and python stuff
#
#
#=========================================================

MYTCLVER=TCL83

if [ -z $FIFO_PATH ]
then
	echo "The SIMPL code uses an environment variable"
	echo "called FIFO_PATH to locate the directory"
	echo "into which all the fifos will be created."
	echo "Please export the FIFO_PATH environment variable"
	echo "before continuing."
	exit
else
if [ ! -d $FIFO_PATH ]
then
	echo "The $FIFO_PATH directory does not exist."
	echo "The SIMPL code build requires this directory to"
	echo "exist in order to setup a memory mapped file."
	echo "Please create $FIFO_PATH before continuing."
	exit
else
if [ -z $SIMPL_HOME ]
then
	echo "The SIMPL code uses an environment variable"
	echo "called SIMPL_HOME to locate the SIMPL code tree."
	echo "The SIMPL_HOME can point any place as long as the"
	echo "path it points to ends in \"/simpl\"."
	echo "Please export the SIMPL_HOME environment variable"
	echo "before continuing."
	exit
else
if [ ! -d $SIMPL_HOME ]
then
	echo "The $SIMPL_HOME directory does not exist."
	echo "This indicates that the SIMPL tar.gz was improperly"
	echo "installed."
	echo "Please reexamine the installation instructions and"
	echo "repeat the installation if necessary."
	exit
fi
fi
fi
fi

TCLVER=`$SIMPL_HOME/scripts/tclver | cut -c1`
if [ $TCLVER != "8" ]
then
	echo "Your Tcl version is $TCLVER.x"
	echo "The portion of the SIMPL code which depends on"
	echo "Tcl v8.x may not compile."
	echo "This is not critical provided you do not wish to use"
	echo "the Tcl/Tk SIMPL extensions. If you do please upgrade"
	echo "Tcl/Tk to version 8.x before continuing."
	echo -n "Continue [y/n] "
	read mykey
	if [ $mykey != "y" ]
	then
		exit
	fi
	MYTCLVER=80
fi
TCLSUBVER=`$SIMPL_HOME/scripts/tclver | cut -c3`
MYTCLVER=$TCLVER.$TCLSUBVER
MYTCLDEF=$TCLVER\_$TCLSUBVER

if [ $TCLSUBVER -lt "3" ]
then
	echo "Your Tcl version is $TCLVER.$TCLSUBVER"
	echo "The portion of the SIMPL code which depends on"
	echo "Tcl v8.3 or higher may not compile."
	echo "This is not critical provided you do not wish to use"
	echo "the Tcl/Tk SIMPL extensions. If you do please upgrade"
	echo "Tcl/Tk to version 8.3 or higher before continuing."
	echo -n "Continue [y/n] "
	read mykey
	if [ $mykey != "y" ]
	then
		exit
	fi
	MYTCLVER=8.0
	MYTCLDEF=8_0
fi

if [ ! -e /usr/include/tcl.h ]
then
	if [ ! -e /usr/include/tcl$MYTCLVER/tcl.h ]
	then
		if [ ! -e /usr/local/include/tcl.h ]
		then
	echo "==============================================="
	echo "You don't have the Tcl/Tk sources installed."
	echo "The portion of the SIMPL code which depends on"
	echo "Tcl/Tk sources will not compile."
	echo ""
	echo "Please install both the Tcl/Tk runtime and the"
	echo "Tcl/Tk source packages and then"
	echo "rerun this script."
	echo "==============================================="
	exit
		fi
	fi
fi

OUT_FILE=$SIMPL_HOME/make.tcl.out

cd $SIMPL_HOME
if [ -a make.tcl.out.gz ]
then 
	rm make.tcl.out.gz
fi

date > $OUT_FILE
echo "==================================================" >> $OUT_FILE
echo "SIMPL_HOME = $SIMPL_HOME" >> $OUT_FILE
echo "FIFO_PATH = $FIFO_PATH" >> $OUT_FILE
echo "Tcl version = `$SIMPL_HOME/scripts/tclver`" >> $OUT_FILE
echo "SIMPL version:" >> $OUT_FILE
cat $SIMPL_HOME/version >> $OUT_FILE

echo "=================================================="
echo "SIMPL top level build script"
echo ""
echo "This script will run a top level Makefile"
echo "and route its output to a file:"
echo "     $OUT_FILE"
echo ""
echo "you can watch the process by"
echo "running tail -f $OUT_FILE on another console"
echo "if you wish"
echo "=================================================="
sleep 5 

echo "=================================================="
echo "Step 1:"
echo "running make clean ... please wait"
echo "NOTE: missing file errors here are quite normal"
echo "especially the first time you run this"
sleep 2
echo "==================================================" >> $OUT_FILE
echo "running make clean" >> $OUT_FILE
echo "==================================================" >> $OUT_FILE
cd $SIMPL_HOME/tcl
make clean 1>>$OUT_FILE 2>&1

echo "=================================================="
echo "Step 2:"
echo "running make install ... please wait"
echo "==================================================" >> $OUT_FILE
echo "running make install" >> $OUT_FILE
echo "==================================================" >> $OUT_FILE
make install TCLVER=$MYTCLVER TCLDEF=$MYTCLDEF 1>>$OUT_FILE 2>&1
echo "SIMPL/tcl make install done"

echo "=================================================="
echo "Step 3:"
echo "taking a snapshot of the $SIMPL_HOME/bin ... please wait"

cd $SIMPL_HOME/bin
echo "==================================================" >> $OUT_FILE
pwd >> $OUT_FILE
echo "==================================================" >> $OUT_FILE
echo "snapshot of $SIMPL_HOME/bin using \"ls -tl\"" >> $OUT_FILE
echo "==================================================" >> $OUT_FILE
ls -tl >>$OUT_FILE
echo "==================================================" >> $OUT_FILE
echo "snapshot of $SIMPL_HOME/bin using \"cksum *\"" >> $OUT_FILE
echo "==================================================" >> $OUT_FILE
cksum * >>$OUT_FILE

echo "=================================================="
echo "Step 4:"
echo "taking a snapshot of the $SIMPL_HOME/lib ... please wait"

cd $SIMPL_HOME/lib
echo "==================================================" >> $OUT_FILE
pwd >> $OUT_FILE
echo "==================================================" >> $OUT_FILE
echo "snapshot of $SIMPL_HOME/lib using \"ls -tl\"" >> $OUT_FILE
echo "==================================================" >> $OUT_FILE
ls -tl >>$OUT_FILE
echo "==================================================" >> $OUT_FILE
echo "snapshot of $SIMPL_HOME/lib using \"cksum *\"" >> $OUT_FILE
echo "==================================================" >> $OUT_FILE
cksum * >>$OUT_FILE

echo "=================================================="
echo "Step 5:"
echo "Please examine the output from the Makefile at:"
echo "	$OUT_FILE"
echo ""
echo "======================================================="
echo "If you encountered build problems that you cannot solve"
echo "Please email $OUT_FILE.gz to SIMPL project."
echo "======================================================="
echo "==================================================" >> $OUT_FILE
date >> $OUT_FILE
echo "==================================================" >> $OUT_FILE
