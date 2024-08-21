===============================================
readme.tcl
===============================================
$Log: readme.tcl,v $
Revision 1.3  2009/01/22 14:53:55  bobfcsoft
cleanup

===============================================
Here is a procedure to get  Tcl/Tk sources installed 
and to get the fctclx library installed and running.

1) Make a home for the downloads
mkdir /home/tcl
go to www.tcl.tk

find and download both tcl and tk sources.
	tcl8.x.x-src.tar.gz
	tk8.x.x-src.tar.gz
to this directory

2) Install the new version of tcl
cd /home/tcl
tar -zxvf tcl8.x.x-src.tar.gz
cd tcl8.x.x/unix
./configure
make
make install
cd /usr/bin
ln -fs /usr/local/bin/tclsh8.x tclsh
tclsh
%info tclversion
%exit

You should see 8.x as the version number.

3) Install the new version of Tk 
cd /home/tcl
tar -zxvf tk8.x.x-src.tar.gz
cd tk8.x.x/unix
./configure
make
make install
cd /usr/bin
ln -fs /usr/local/bin/wish8.x wish

4) Install the SIMPL package and the SIMPL-Tcl extension package
be sure that you have an enviroment variable defined
	SIMPL_HOME=/root/simpl   (or whatever)

cd $SIMPL_HOME
cd ..
<place your two SIMPL tarballs here>
tar -zxvf simpl-x.x.x.tar.gz
ln -s simpl-x.x.x simpl
buildsimpl

tar -zxvf simpltcl-x.x.tar.gz
cd simpl
ln -s tcl-x.x tcl
buildsimpl.tcl

5) Configure the simpl tcl library extension as a package
cd $SIMPL_HOME/lib
ln -s $SIMPL_HOME/tcl/lib/libfctclx.so.1 libfctclx.so
cd /usr/local/lib
mkdir simpl 
cd simpl
ln -s $SIMPL_HOME/lib/libfctclx.so .
tclsh
%pkg_mkIndex /usr/local/lib/simpl *.so
%exit


-------------------------
FCsoftware Inc. 1998,2009
This code is released as open source.   We hope you find 
it useful.  If you discover a bug or add an enhancement 
contact us on the SIMPL project mailing list. 

-------------------------
