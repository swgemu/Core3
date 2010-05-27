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

AM_CXXFLAGS=-ggdb -Wall -Wextra -Wno-unused -Wno-sign-compare -Wno-multichar

ENGINE3_PATH=../../../../MMOEngine

INCLUDES =  $(SYSTEM_INCLUDES) \
	    -I$(USER_INCLUDES_PATH) -I$(USER_INCLUDES_PATH)/mysql \
	    -I$(ENGINE3_PATH)/include -I/usr/include/lua5.1 -I/usr/include/mysql \
	    -I/usr/local/BerkeleyDB.4.8/include
			
LIBS =	$(SYSTEM_LIBS)  \
	-L../../../build/unix/src/client \
	-L/usr/local/BerkeleyDB.4.8/lib \
	-L$(USER_LIBS_PATH)/ -L$(USER_LIBS_PATH)/mysql -L$(USER_LIBS_PATH)/mysql5/mysql -L$(USER_LIBS_PATH)/lua -L$(ENGINE3_PATH)/lib/unix \
	-lmysqlclient -lz -lengine3 -llua -ldb

bin_PROGRAMS = core3

core3_IDLS =	server/zone/ZoneServer.cpp \
				server/zone/ZoneClientSession.cpp \
				server/zone/Zone.cpp \
				server/zone/objects/scene/SceneObject.cpp \
				server/zone/objects/intangible/IntangibleObject.cpp \
				server/zone/objects/intangible/ControlDevice.cpp \
				server/zone/objects/staticobject/StaticObject.cpp \
				server/zone/objects/intangible/VehicleControlDevice.cpp \
				server/zone/objects/tangible/TangibleObject.cpp \
				server/zone/objects/tangible/Container.cpp \
				server/zone/objects/tangible/Instrument.cpp \
				server/zone/objects/tangible/Food.cpp \
				server/zone/objects/creature/CreatureObject.cpp \
				server/zone/objects/creature/trainer/TrainerCreature.cpp \
				server/zone/objects/creature/VehicleObject.cpp \
				server/zone/objects/player/PlayerObject.cpp \
				server/zone/objects/player/sui/SuiBox.cpp \
				server/zone/objects/player/sui/listbox/SuiListBox.cpp \
				server/zone/objects/player/sui/listbox/SuiListBoxMenuItem.cpp \
				server/zone/objects/player/sui/banktransferbox/SuiBankTransferBox.cpp \
				server/zone/objects/waypoint/WaypointObject.cpp \
				server/zone/objects/player/PlayerCreature.cpp \
				server/zone/objects/cell/CellObject.cpp \
				server/zone/objects/group/GroupObject.cpp \
				server/zone/objects/region/Region.cpp \
				server/zone/objects/building/BuildingObject.cpp \
				server/zone/objects/building/cloning/CloningBuildingObject.cpp \
				server/zone/objects/building/medical/MedicalBuildingObject.cpp \
				server/zone/objects/building/recreation/RecreationBuildingObject.cpp \
				server/zone/objects/building/travel/TravelBuildingObject.cpp \
				server/zone/objects/building/tutorial/TutorialBuildingObject.cpp \
				server/zone/managers/player/PlayerManager.cpp \
				server/chat/room/ChatRoom.cpp \
				server/chat/ChatManager.cpp \
				server/chat/PersistentMessage.cpp \
				server/zone/managers/objectcontroller/ObjectController.cpp \
				server/zone/objects/resource/ResourceSpawn.cpp \
				server/zone/objects/tangible/fishing/FishingPoleObject.cpp \
				server/zone/objects/tangible/fishing/FishingBaitObject.cpp \
				server/zone/objects/tangible/fishing/FishObject.cpp \
				server/zone/managers/minigames/FishingManager.cpp \
				server/zone/objects/tangible/weapon/WeaponObject.cpp \
				server/zone/objects/tangible/weapon/MeleeWeaponObject.cpp \
				server/zone/objects/tangible/weapon/RangedWeaponObject.cpp \
				server/zone/objects/tangible/weapon/PistolWeaponObject.cpp \
				server/zone/objects/tangible/weapon/RifleWeaponObject.cpp \
				server/zone/objects/tangible/weapon/OneHandMeleeWeapon.cpp \
				server/zone/objects/tangible/weapon/TwoHandMeleeWeapon.cpp \
				server/zone/objects/tangible/weapon/PolearmWeaponObject.cpp \
				server/zone/managers/structure/StructureManager.cpp \
				server/zone/managers/planet/PlanetManager.cpp \
				server/zone/managers/radial/RadialManager.cpp \
				server/zone/managers/resource/ResourceManager.cpp \
				server/zone/managers/creature/CreatureManager.cpp \
				server/zone/managers/bazaar/BazaarManager.cpp \
				server/zone/managers/bazaar/BazaarAuctionsMap.cpp \
				server/zone/objects/resource/ResourceContainer.cpp \
				server/zone/objects/tangible/tool/CraftingTool.cpp \
				server/zone/objects/tangible/tool/ToolTangibleObject.cpp \
				server/zone/objects/tangible/tool/SurveyTool.cpp \
				server/zone/objects/tangible/wearables/WearableObject.cpp \
				server/zone/objects/tangible/wearables/ClothingObject.cpp \
				server/zone/objects/tangible/wearables/ArmorObject.cpp \
				server/zone/objects/tangible/deed/Deed.cpp \
				server/zone/objects/tangible/deed/playerhouse/PlayerHouseDeed.cpp \
				server/zone/objects/tangible/terminal/Terminal.cpp \
				server/zone/objects/tangible/terminal/bank/BankTerminal.cpp \
				server/zone/objects/tangible/terminal/mission/MissionTerminal.cpp \
				server/zone/objects/tangible/terminal/bazaar/BazaarTerminal.cpp \
				server/zone/objects/tangible/terminal/bazaar/AuctionItem.cpp \
				server/zone/objects/mission/MissionObject.cpp \
				server/zone/objects/tangible/terminal/startinglocation/StartingLocationTerminal.cpp \
				server/zone/objects/tangible/terminal/characterbuilder/CharacterBuilderTerminal.cpp
				
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
		server/zone/managers/planet/PlanetManagerImplementation.cpp \
		server/zone/managers/player/PlayerManagerImplementation.cpp \
		server/zone/managers/name/NameManager.cpp \
		server/zone/managers/group/GroupManager.cpp \
		server/zone/managers/professions/ProfessionManager.cpp \
		server/zone/managers/sui/SuiManager.cpp \
		server/zone/managers/bazaar/BazaarManagerImplementation.cpp \
		server/zone/managers/minigames/FishingManagerImplementation.cpp \
		server/zone/managers/resource/resourcespawner/ResourceSpawner.cpp \
		server/zone/managers/resource/resourcespawner/resourcetree/ResourceTree.cpp \
		server/zone/managers/resource/resourcespawner/resourcetree/ResourceTreeNode.cpp \
		server/zone/managers/resource/resourcespawner/resourcemap/ResourceMap.cpp \
		server/zone/managers/resource/resourcespawner/resourcepool/MinimumPool.cpp \
		server/zone/managers/resource/resourcespawner/resourcepool/RandomPool.cpp \
		server/zone/managers/resource/resourcespawner/resourcepool/FixedPool.cpp \
		server/zone/managers/resource/resourcespawner/resourcepool/NativePool.cpp \
		server/zone/objects/scene/SceneObjectImplementation.cpp \
		server/zone/objects/region/RegionImplementation.cpp \
		server/zone/objects/terrain/ProceduralTerrainAppearance.cpp \
		server/zone/objects/terrain/TerrainGenerator.cpp \
		server/zone/objects/terrain/layer/Layer.cpp \
		server/zone/objects/intangible/IntangibleObjectImplementation.cpp \
		server/zone/objects/staticobject/StaticObjectImplementation.cpp \
		server/zone/objects/intangible/VehicleControlDeviceImplementation.cpp \
		server/zone/objects/tangible/fishing/FishingPoleObjectImplementation.cpp \
		server/zone/objects/tangible/fishing/FishingBaitObjectImplementation.cpp \
		server/zone/objects/tangible/fishing/FishObjectImplementation.cpp \
		server/zone/objects/tangible/TangibleObjectImplementation.cpp \
		server/zone/objects/tangible/ContainerImplementation.cpp \
		server/zone/objects/tangible/terminal/bazaar/BazaarTerminalImplementation.cpp \
		server/zone/objects/tangible/deed/playerhouse/PlayerHouseDeedImplementation.cpp \
		server/zone/objects/tangible/tool/SurveyToolImplementation.cpp \
		server/zone/objects/group/GroupObjectImplementation.cpp \
		server/zone/objects/creature/CreatureObjectImplementation.cpp \
		server/zone/objects/creature/trainer/TrainerCreatureImplementation.cpp \
		server/zone/objects/creature/variables/CommandQueueAction.cpp \
		server/zone/objects/creature/commands/QueueCommand.cpp \
		server/zone/objects/creature/LuaCreatureObject.cpp \
		server/zone/objects/creature/VehicleObjectImplementation.cpp \
		server/zone/objects/creature/variables/SkillBoxList.cpp \
		server/zone/objects/player/PlayerObjectImplementation.cpp \
		server/zone/objects/player/variables/SkillList.cpp \
		server/zone/objects/resource/ResourceSpawnImplementation.cpp \
		server/zone/objects/resource/simplexnoise/SimplexNoise.cpp \
		server/zone/objects/resource/ResourceContainerImplementation.cpp \
		server/zone/objects/scene/variables/StringId.cpp \
		server/zone/objects/scene/variables/StringIdParameter.cpp \
		server/zone/objects/scene/variables/ParameterizedStringId.cpp \
		server/zone/objects/scene/variables/CustomizationVariables.cpp \
		server/zone/objects/cell/CellObjectImplementation.cpp \
		server/zone/objects/building/BuildingObjectImplementation.cpp \
		server/zone/objects/building/tutorial/TutorialBuildingObjectImplementation.cpp \
		server/zone/objects/player/PlayerCreatureImplementation.cpp \
		server/zone/objects/player/sui/SuiBoxImplementation.cpp \
		server/zone/objects/player/sui/listbox/SuiListBoxImplementation.cpp \
		server/zone/objects/player/badges/Badge.cpp \
		server/zone/objects/player/sui/banktransferbox/SuiBankTransferBoxImplementation.cpp \
		server/zone/packets/charcreation/ClientCreateCharacterCallback.cpp \
		server/zone/packets/object/ObjectControllerMessageCallback.cpp \
		server/chat/room/ChatRoomImplementation.cpp \
		server/chat/ChatManagerImplementation.cpp \
		server/chat/PersistentMessageImplementation.cpp \
		server/zone/managers/objectcontroller/ObjectControllerImplementation.cpp \
		server/zone/managers/objectcontroller/command/CommandConfigManager.cpp \
		server/zone/managers/terrain/TerrainManager.cpp \
		server/zone/managers/template/TemplateManager.cpp \
		server/zone/objects/waypoint/WaypointObjectImplementation.cpp \
		server/zone/objects/tangible/weapon/WeaponObjectImplementation.cpp \
		server/zone/objects/tangible/weapon/MeleeWeaponObjectImplementation.cpp \
		server/zone/managers/structure/StructureManagerImplementation.cpp \
		server/zone/objects/tangible/wearables/WearableObjectImplementation.cpp \
		server/zone/objects/tangible/wearables/ArmorObjectImplementation.cpp \
		server/zone/objects/tangible/terminal/TerminalImplementation.cpp \
		server/zone/objects/tangible/terminal/startinglocation/StartingLocationTerminalImplementation.cpp \
		server/zone/objects/tangible/terminal/characterbuilder/CharacterBuilderTerminalImplementation.cpp \
		server/zone/objects/tangible/terminal/bazaar/AuctionItemImplementation.cpp \
		server/zone/managers/radial/RadialManagerImplementation.cpp \
		server/zone/managers/resource/ResourceManagerImplementation.cpp \
		server/zone/managers/creature/CreatureManagerImplementation.cpp \
		server/zone/managers/combat/CombatManager.cpp \
		server/zone/objects/mission/MissionObjectImplementation.cpp \
		server/zone/templates/SharedTangibleObjectTemplate.cpp \
		server/zone/templates/SharedObjectTemplate.cpp \
		server/zone/templates/tangible/SharedBuildingObjectTemplate.cpp \
		server/zone/templates/tangible/SharedCreatureObjectTemplate.cpp \
		server/zone/templates/tangible/SharedWeaponObjectTemplate.cpp \
		main.cpp
