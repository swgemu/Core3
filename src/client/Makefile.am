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

AM_CXXFLAGS=-ggdb -Wall -Wextra -Wno-unused -Wno-sign-compare

ENGINE3_PATH=../../../../../MMOEngine

INCLUDES =  $(SYSTEM_INCLUDES) \
	    -I$(USER_INCLUDES_PATH) -I$(USER_INCLUDES_PATH)/mysql \
	    -I$(ENGINE3_PATH)/include -I/usr/include/lua5.1 -I/usr/include/mysql \
	   	-I/usr/local/BerkeleyDB.5.0/include
			
LIBS =	$(SYSTEM_LIBS)  \
	-L../../../build/unix/src/client \
	-L/usr/local/BerkeleyDB.5.0/lib \
	-L$(USER_LIBS_PATH)/ -L$(USER_LIBS_PATH)/mysql -L$(USER_LIBS_PATH)/mysql5/mysql -L$(USER_LIBS_PATH)/lua -L$(ENGINE3_PATH)/lib/unix \
	-lengine3 -lmysqlclient -llua -lz -ldb

bin_PROGRAMS = core3client

core3client_SOURCES = \
		ClientCore.cpp \
		login/LoginClient.cpp \
		login/LoginSession.cpp \
		login/LoginPacketHandler.cpp \
		zone/Zone.cpp \
		zone/ZoneClient.cpp \
		zone/ZonePacketHandler.cpp \
		zone/ZoneClientThread.cpp \
		zone/managers/object/ObjectManager.cpp \
		zone/managers/objectcontroller/ObjectController.cpp \
		zone/objects/scene/SceneObject.cpp \
		zone/objects/scene/variables/StringId.cpp \
		zone/objects/creature/CreatureObject.cpp \
		zone/objects/tangible/TangibleObject.cpp \
		zone/objects/intangible/IntangibleObject.cpp \
		zone/objects/player/PlayerObject.cpp \
		zone/objects/player/PlayerCreature.cpp  
