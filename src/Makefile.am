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

ENGINE3_PATH=../../../../MMOEngine

INCLUDES =  $(SYSTEM_INCLUDES) \
	    -I$(USER_INCLUDES_PATH) -I$(USER_INCLUDES_PATH)/mysql \
	    -I$(ENGINE3_PATH)/include
			
LIBS =	$(SYSTEM_LIBS)  \
	-L../../../build/unix/src/client \
	-L$(USER_LIBS_PATH)/ -L$(USER_LIBS_PATH)/mysql -L$(USER_LIBS_PATH)/mysql5/mysql -L$(USER_LIBS_PATH)/lua -L$(ENGINE3_PATH)/lib/unix \
	-lmysqlclient -lz -lengine3 -llua

bin_PROGRAMS = core3

core3_IDLS =	server/zone/ZoneServer.cpp \
				server/zone/ZoneClientSession.cpp \
				server/zone/Zone.cpp \
				server/zone/objects/scene/SceneObject.cpp \
				server/zone/objects/intangible/IntangibleObject.cpp \
				server/zone/objects/tangible/TangibleObject.cpp \
				server/zone/objects/tangible/Container.cpp \
				server/zone/objects/creature/CreatureObject.cpp \
				server/zone/objects/player/PlayerObject.cpp \
				server/zone/objects/player/PlayerCreature.cpp \
				server/zone/managers/player/PlayerManager.cpp
				
core3_SOURCES =	$(core3_IDLS) \
		server/conf/ConfigManager.cpp \
		server/features/Features.cpp \
		server/db/ForumsDatabase.cpp \
		server/db/ServerDatabase.cpp \
		server/login/LoginMessageProcessorThread.cpp \
		server/login/LoginPacketHandler.cpp \
		server/login/LoginServer.cpp \
		server/ping/PingServer.cpp \
		server/proxy/LoginProxyServer.cpp \
		server/ServerCore.cpp \
		server/zone/ZoneServerImplementation.cpp \
		server/zone/ZoneClientSessionImplementation.cpp \
		server/zone/ZonePacketHandler.cpp \
		server/zone/ZoneMessageProcessorThread.cpp \
		server/zone/ZoneProcessServerImplementation.cpp \
		server/zone/ZoneImplementation.cpp \
		server/zone/managers/planet/HeightMap.cpp \
		server/zone/managers/object/ObjectManager.cpp \
		server/zone/managers/player/PlayerManagerImplementation.cpp \
		server/zone/managers/name/NameManager.cpp \
		server/zone/objects/scene/SceneObjectImplementation.cpp \
		server/zone/objects/intangible/IntangibleObjectImplementation.cpp \
		server/zone/objects/tangible/TangibleObjectImplementation.cpp \
		server/zone/objects/tangible/ContainerImplementation.cpp \
		server/zone/objects/creature/CreatureObjectImplementation.cpp \
		server/zone/objects/player/PlayerObjectImplementation.cpp \
		server/zone/objects/scene/variables/StringId.cpp \
		server/zone/objects/player/PlayerCreatureImplementation.cpp \
		server/zone/packets/charcreation/ClientCreateCharacter.cpp \
		main.cpp
		