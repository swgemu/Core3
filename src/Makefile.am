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

SVNDEF=-D'SVN_REV="$(shell svnversion -n .)"'
AM_CXXFLAGS=$(SVNDEF) -ggdb -Wall -Wextra -Wno-unused -Wno-sign-compare

ENGINE3_PATH=../../../../MMOEngine

INCLUDES =  $(SYSTEM_INCLUDES) \
	    -I$(USER_INCLUDES_PATH) -I$(USER_INCLUDES_PATH)/mysql \
	    -I$(ENGINE3_PATH)/include
			
LIBS =	$(SYSTEM_LIBS)  \
	-L../../../build/unix/src/client \
	-L$(USER_LIBS_PATH)/ -L$(USER_LIBS_PATH)/mysql -L$(USER_LIBS_PATH)/lua -L$(ENGINE3_PATH)/lib/unix \
	-lmysqlclient -lz -lengine3 -llua

bin_PROGRAMS = core3

core3_IDLS = server/chat/ChatManager.cpp \
		server/chat/GameCommandHandler.cpp \
		server/chat/room/ChatRoom.cpp \
		server/zone/managers/auction/AuctionManager.cpp \
		server/zone/managers/bank/BankManager.cpp \
		server/zone/managers/crafting/CraftingManager.cpp \
		server/zone/managers/creature/CreatureManager.cpp \
		server/zone/managers/guild/GuildManager.cpp \
		server/zone/managers/item/ItemManager.cpp \
		server/zone/managers/mission/MissionManager.cpp \
		server/zone/managers/planet/PlanetManager.cpp \
		server/zone/managers/player/PlayerManager.cpp \
		server/zone/managers/player/PlayerMap.cpp \
		server/zone/managers/structure/StructureManager.cpp \
		server/zone/managers/user/UserManager.cpp \
		server/zone/objects/SceneObject.cpp \
		server/zone/objects/cell/CellObject.cpp \
		server/zone/objects/intangible/IntangibleObject.cpp \
		server/zone/objects/intangible/player/PlayerObject.cpp \
		server/zone/objects/intangible/draftschematic/DraftSchematicObject.cpp \
		server/zone/objects/intangible/manufactureschematic/ManufactureSchematicObject.cpp \
		server/zone/objects/intangible/mission/MissionObject.cpp \
		server/zone/objects/intangible/waypoint/WaypointObject.cpp \
		server/zone/objects/tangible/TangibleObject.cpp \
		server/zone/objects/tangible/building/BuildingObject.cpp \
		server/zone/objects/tangible/building/camp/CampObject.cpp \
		server/zone/objects/tangible/component/ComponentObject.cpp \
		server/zone/objects/tangible/creature/CreatureObject.cpp \
		server/zone/objects/tangible/creature/npc/Creature.cpp \
		server/zone/objects/tangible/deed/DeedObject.cpp \
		server/zone/objects/tangible/instrument/InstrumentObject.cpp \
		server/zone/objects/tangible/installation/InstallationObject.cpp \
		server/zone/objects/tangible/inventory/InventoryObject.cpp \
		server/zone/objects/tangible/terminal/TerminalObject.cpp \
		server/zone/objects/tangible/terminal/bazaar/BazaarTerminalObject.cpp \
		server/zone/objects/tangible/powerup/PowerupObject.cpp \
		server/zone/objects/tangible/resourcecontainer/ResourceContainerObject.cpp \
		server/zone/objects/tangible/weapon/WeaponObject.cpp \
		server/zone/objects/tangible/wearable/WearableObject.cpp \
		server/zone/objects/tangible/wearable/armor/ArmorObject.cpp \
		server/zone/objects/universe/group/GroupObject.cpp \
		server/zone/objects/universe/guild/GuildObject.cpp \
		server/zone/ZoneClientSession.cpp \
		server/zone/Zone.cpp \
		server/zone/ZoneServer.cpp 
core3_SOURCES =	$(core3_IDLS) \
		server/ServerCore.cpp \
		server/chat/ChatManagerImplementation.cpp \
		server/chat/room/ChatRoomImplementation.cpp \
		server/conf/ConfigManager.cpp \
		server/db/ForumsDatabase.cpp \
		server/db/ServerDatabase.cpp \
		server/login/LoginMessageProcessorThread.cpp \
		server/login/LoginPacketHandler.cpp \
		server/login/LoginServer.cpp \
		server/ping/PingServer.cpp \
		server/proxy/LoginProxyServer.cpp \
		server/status/StatusServer.cpp \
		server/zone/Quaternion.cpp \
		server/zone/Vector3.cpp \
		server/zone/managers/auction/AuctionManagerImplementation.cpp \
		server/zone/managers/bank/BankManagerImplementation.cpp \
		server/zone/managers/combat/CombatManager.cpp \
		server/zone/managers/combat/CommandQueueAction.cpp \
		server/zone/managers/crafting/CraftingManagerImplementation.cpp \
		server/zone/managers/creature/CreatureManagerImplementation.cpp \
		server/zone/managers/group/GroupManager.cpp \
		server/zone/managers/guild/GuildManagerImplementation.cpp \
		server/zone/managers/item/ItemManagerImplementation.cpp \
		server/zone/managers/mission/MissionManagerImplementation.cpp \
		server/zone/managers/name/NameManager.cpp \
		server/zone/managers/object/ObjectManager.cpp \
		server/zone/managers/planet/HeightMap.cpp \
		server/zone/managers/planet/PlanetManagerImplementation.cpp \
		server/zone/managers/player/PlayerManagerImplementation.cpp \
		server/zone/managers/player/ProfessionManager.cpp \
		server/zone/managers/radial/RadialManager.cpp \
		server/zone/managers/skills/imagedesign/CustomizationManager.cpp \
		server/zone/managers/skills/imagedesign/ImageDesignCustomization.cpp \
		server/zone/managers/skills/ScriptAttacksManager.cpp \
		server/zone/managers/skills/SkillManager.cpp \
		server/zone/managers/structure/StructureManagerImplementation.cpp \
		server/zone/managers/user/UserManagerImplementation.cpp \
		server/zone/objects/SceneObjectImplementation.cpp \
		server/zone/objects/Container.cpp \
		server/zone/objects/cell/CellObjectImplementation.cpp \
		server/zone/objects/intangible/IntangibleObjectImplementation.cpp \
		server/zone/objects/intangible/player/PlayerObjectImplementation.cpp \
		server/zone/objects/intangible/draftschematic/DraftSchematicObjectImplementation.cpp \
		server/zone/objects/intangible/manufactureschematic/ManufactureSchematicObjectImplementation.cpp \
		server/zone/objects/intangible/mission/MissionObjectImplementation.cpp \
		server/zone/objects/intangible/waypoint/WaypointObjectImplementation.cpp \
		server/zone/objects/tangible/TangibleObjectImplementation.cpp \
		server/zone/objects/tangible/CustomizationVariables.cpp \
		server/zone/objects/tangible/building/BuildingObjectImplementation.cpp \
		server/zone/objects/tangible/building/camp/CampObjectImplementation.cpp \
		server/zone/objects/tangible/component/ComponentObjectImplementation.cpp \
		server/zone/objects/tangible/creature/CreatureObjectImplementation.cpp \
		server/zone/objects/tangible/creature/npc/CreatureImplementation.cpp \
		server/zone/objects/tangible/deed/DeedObjectImplementation.cpp \
		server/zone/objects/tangible/instrument/InstrumentObjectImplementation.cpp \
		server/zone/objects/tangible/installation/InstallationObjectImplementation.cpp \
		server/zone/objects/tangible/inventory/InventoryObjectImplementation.cpp \
		server/zone/objects/tangible/powerup/PowerupObjectImplementation.cpp \
		server/zone/objects/tangible/resourcecontainer/ResourceContainerObjectImplementation.cpp \
		server/zone/objects/tangible/structure/Structure.cpp \
		server/zone/objects/tangible/structure/StructurePermissionList.cpp \
		server/zone/objects/tangible/terminal/TerminalObjectImplementation.cpp \
		server/zone/objects/tangible/terminal/bazaar/BazaarTerminalObjectImplementation.cpp \
		server/zone/objects/tangible/weapon/WeaponObjectImplementation.cpp \
		server/zone/objects/tangible/wearable/WearableObjectImplementation.cpp \
		server/zone/objects/tangible/wearable/armor/ArmorObjectImplementation.cpp \
		server/zone/objects/universe/group/GroupObjectImplementation.cpp \
		server/zone/objects/universe/guild/GuildObjectImplementation.cpp \
		server/zone/packets/object/ObjectControllerMessage.cpp \
		server/zone/packets/charcreation/ClientCreateCharacter.cpp \
		server/zone/ZoneClientSessionImplementation.cpp \
		server/zone/ZoneImplementation.cpp \
		server/zone/ZoneMessageProcessorThread.cpp \
		server/zone/ZonePacketHandler.cpp \
		server/zone/ZoneProcessServerImplementation.cpp \
		server/zone/ZoneServerImplementation.cpp \
		main.cpp 
		