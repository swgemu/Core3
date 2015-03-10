# Copyright (C) 2007 <SWGEmu>
 
# This File is part of Core3.
 
# This program is free software; you can redistribute 
# it and/or modify it under the terms of the GNU Lesser 
# General Public License as published by the Free Software
# Foundation; either version 2 of the License, 
# or (at your option) any later version.
 
# This program is distributed in the hope that it will be useful, 
# but WITHOUT ANY WARRANTY; without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
# See the GNU Lesser General Public License for
# more details.
 
# You should have received a copy of the GNU Lesser General 
# Public License along with this program; if not, write to
# the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
# Linking Engine3 statically or dynamically with other modules 
# is making a combined work based on Engine3. 
# Thus, the terms and conditions of the GNU Lesser General Public License 
# cover the whole combination.
 
# In addition, as a special exception, the copyright holders of Engine3 
# give you permission to combine Engine3 program with free software 
# programs or libraries that are released under the GNU LGPL and with 
# code included in the standard release of Core3 under the GNU LGPL 
# license (or modified versions of such code, with unchanged license). 
# You may copy and distribute such a system following the terms of the
# GNU LGPL for Engine3 and the licenses of the other code concerned, 
# provided that you include the source code of that other code when 
# and as the GNU LGPL requires distribution of source code.
 
# Note that people who make modified versions of Engine3 are not obligated 
# to grant this special exception for their modified versions; 
# it is their choice whether to do so. The GNU Lesser General Public License 
# gives permission to release a modified version without this exception; 
# this exception also makes it possible to release a modified version 
# which carries forward this exception.

IDLC = /usr/local/bin/idlc 
				
IDL_CLASSPATH = ../MMOEngine/include

IDL_DIRECTIVES = -noprelocks -makefile src/Makefile.am -outdir autogen -cp $(IDL_CLASSPATH)

UNITTEST_DIRECTIVES = 

all: #build
	#cd build/unix && cmake ../.. && make
	#cp build/unix/src/core3 bin

build: idl gtest
	cd build/unix && make -j4 UNITTEST_DIRECTIVES="$(UNITTEST_DIRECTIVES)" #CC=clang CXX=clang++
	cp build/unix/src/client/core3* bin
	cp build/unix/src/core3* bin
	#cd bin/conf && svnversion > rev.txt
	cd bin/conf && git log --pretty=format:'%h was %an, %ar, message: %s' -10 > rev.txt
	rm build/unix/src/core3
	#done
	
unittest: UNITTEST_DIRECTIVES = -fprofile-arcs -ftest-coverage
unittest: build

rebuild: clean build

idl:
	$(IDLC) $(IDL_DIRECTIVES) -sd src anyadEclipse
	#done
	
gtest:
	cd utils/gtest-1.6.0 && make all

config:
	aclocal
	automake --add-missing
	autoreconf --force --install
	cd build/unix && ../../configure
	#cd ../MMOEngine/external/ptmalloc3 && make
	#done

clean: cleanidl	
	cd build/unix && make clean
	cd utils/gtest-1.6.0 && make clean
	#cd build/unix/src && rm *
	#cd build/unix/src/.deps && rm *
	#done
		
cleanidl:
	$(IDLC) -rebuild $(IDL_DIRECTIVES) -sd src anyadEclipse

cleardb:
	cd bin/databases && rm -rf *.*
	#done

PLATFORM:=$(shell uname -s)

ifeq ($(PLATFORM),Linux)
	CPU_CORES:=$(shell grep -c processor /proc/cpuinfo)

	ENGINE3_DIR:=$(shell find /opt -name engine3* -print -quit)
else 
ifeq ($(PLATFORM),Darwin)
  	CPU_CORES:=$(sysctl hw.ncpu | awk '{print $2}')

	ENGINE3_DIR:=$(shell find /opt -name engine3* -depth 0)
endif
endif

build-cmake: idl-cmake
	cd build/unix && cmake -DCMAKE_INSTALL_PREFIX=`pwd`/../.. ../.. && make -j$(CPU_CORES)
	cd build/unix && make install

clean-cmake: cleanidl-cmake
	cd build/unix && make clean
	#done

IDLC_BIN:=$(ENGINE3_DIR)/bin/idlc

idl-cmake:
	$(IDLC_BIN) -cp $(ENGINE3_DIR)/include -sd src *.idl

cleanidl-cmake:
	$(IDLC_BIN) -rb -cp $(ENGINE3_DIR)/include -sd src *.idl
	#done
	
deleteidl:
	$(IDLC) -delete $(IDL_DIRECTIVES) -sd src anyadEclipse
	#done
	
