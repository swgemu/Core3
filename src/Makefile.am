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

AM_CXXFLAGS=-ggdb -Wall -Wextra -Wno-unused -Wno-sign-compare -march=i686

ENGINE3_PATH=../../../../MMOEngine

INCLUDES =  $(SYSTEM_INCLUDES) \
	    -I$(USER_INCLUDES_PATH) -I$(USER_INCLUDES_PATH)/mysql \
	    -I$(ENGINE3_PATH)/include
			
LIBS =	$(SYSTEM_LIBS)  \
	-L../../../build/unix/src/client \
	-L$(USER_LIBS_PATH)/ -L$(USER_LIBS_PATH)/mysql -L$(USER_LIBS_PATH)/lua -L$(ENGINE3_PATH)/lib/unix \
	-lmysqlclient -lz -lengine3 -llua

bin_PROGRAMS = core3

core3_IDLS =	server/chat/ChatManager.cpp \
		server/chat/GameCommandHandler.cpp \
		server/chat/room/ChatRoom.cpp \
		server/zone/managers/bank/BankManager.cpp \
		server/zone/managers/bazaar/BazaarManager.cpp \
		server/zone/managers/bazaar/BazaarPlanetManager.cpp \
		server/zone/managers/crafting/CraftingManager.cpp \
		server/zone/managers/creature/CreatureManager.cpp \
		server/zone/managers/guild/GuildManager.cpp \
		server/zone/managers/guild/GuildMap.cpp \
		server/zone/managers/item/ItemManager.cpp \
		server/zone/managers/item/ItemConfigManager.cpp \
		server/zone/managers/loot/LootManager.cpp \
		server/zone/managers/loot/LootTableManager.cpp \
		server/zone/managers/mission/MissionManager.cpp \
		server/zone/managers/planet/PlanetManager.cpp \
		server/zone/managers/player/PlayerManager.cpp \
		server/zone/managers/player/PlayerMap.cpp \
		server/zone/managers/resource/ResourceManager.cpp \
		server/zone/managers/resource/ResourceList.cpp \
		server/zone/managers/resource/ResourceItem.cpp \
		server/zone/managers/structure/StructureManager.cpp \
		server/zone/managers/user/UserManager.cpp \
		server/zone/objects/area/Area.cpp \
		server/zone/objects/area/ActiveArea.cpp \
		server/zone/objects/area/ActiveAreaTrigger.cpp \
		server/zone/objects/area/BadgeActiveArea.cpp \
		server/zone/objects/area/CampActiveArea.cpp \
		server/zone/objects/area/TestActiveArea.cpp \
		server/zone/objects/attackable/AttackableObject.cpp \
		server/zone/objects/auction/AuctionItem.cpp \
		server/zone/objects/building/BuildingObject.cpp \
		server/zone/objects/building/cell/CellObject.cpp \
		server/zone/objects/building/cloningfacility/CloningFacility.cpp \
		server/zone/objects/creature/action/Action.cpp \
		server/zone/objects/creature/action/ActionCreature.cpp \
		server/zone/objects/creature/bluefrog/BlueFrogCreature.cpp \
		server/zone/objects/creature/bluefrog/BlueFrogVector.cpp \
		server/zone/objects/creature/Creature.cpp \
		server/zone/objects/creature/CreatureGroup.cpp \
		server/zone/objects/creature/CreatureObject.cpp \
		server/zone/objects/creature/mount/MountCreature.cpp \
		server/zone/objects/creature/recruiter/imperial/ImperialRecruiterCreature.cpp \
		server/zone/objects/creature/recruiter/rebel/RebelRecruiterCreature.cpp \
		server/zone/objects/creature/recruiter/RecruiterCreature.cpp \
		server/zone/objects/creature/shuttle/ShuttleCreature.cpp \
		server/zone/objects/creature/trainer/TrainerCreature.cpp \
		server/zone/objects/draftschematic/DraftSchematicAttribute.cpp \
		server/zone/objects/draftschematic/DraftSchematic.cpp \
		server/zone/objects/draftschematic/DraftSchematicExpPropGroup.cpp \
		server/zone/objects/draftschematic/DraftSchematicGroup.cpp \
		server/zone/objects/draftschematic/DraftSchematicIngredient.cpp \
		server/zone/objects/draftschematic/DraftSchematicValues.cpp \
		server/zone/objects/group/GroupObject.cpp \
		server/zone/objects/guild/Guild.cpp \
		server/zone/objects/installation/factory/FactoryObject.cpp \
		server/zone/objects/installation/generator/GeneratorObject.cpp \
		server/zone/objects/installation/harvester/HarvesterObject.cpp \
		server/zone/objects/installation/InstallationObject.cpp \
		server/zone/objects/intangible/IntangibleObject.cpp \
		server/zone/objects/manufacture/ManufactureSchematic.cpp \
		server/zone/objects/mission/MissionObject.cpp \
		server/zone/objects/player/faction/FactionPointList.cpp \
		server/zone/objects/player/FriendsList.cpp \
		server/zone/objects/player/IgnoreList.cpp \
		server/zone/objects/player/Player.cpp \
		server/zone/objects/player/PlayerObject.cpp \
		server/zone/objects/player/sui/slicingbox/SuiSlicingBox.cpp \
		server/zone/objects/player/sui/banktransferbox/SuiBankTransferBox.cpp \
		server/zone/objects/player/sui/banktransferbox/SuiBankTipConfirmBox.cpp \
		server/zone/objects/player/sui/colorpicker/SuiColorPicker.cpp \
		server/zone/objects/player/sui/inputbox/SuiInputBox.cpp \
		server/zone/objects/player/sui/listbox/SuiListBox.cpp \
		server/zone/objects/player/sui/listbox/SuiListBoxVector.cpp \
		server/zone/objects/player/sui/messagebox/SuiMessageBox.cpp \
		server/zone/objects/player/sui/SuiBox.cpp \
		server/zone/objects/player/sui/transferbox/SuiTransferBox.cpp \
		server/zone/objects/player/badges/Badges.cpp \
		server/zone/objects/scene/SceneObject.cpp \
		server/zone/objects/ship/ShipObject.cpp \
		server/zone/objects/static/firework/FireworkWorld.cpp \
		server/zone/objects/static/StaticObject.cpp \
		server/zone/objects/tangible/appearance/HairObject.cpp \
		server/zone/objects/tangible/attachment/Attachment.cpp \
		server/zone/objects/tangible/terminal/bank/BankTerminal.cpp \
 		server/zone/objects/tangible/camokits/CamoKit.cpp \
		server/zone/objects/tangible/campkit/CampKit.cpp \
		server/zone/objects/tangible/campkit/campsite/CampSite.cpp \
		server/zone/objects/tangible/campkit/campsite/BasicCampSite.cpp \
		server/zone/objects/tangible/campkit/campsite/MultipersonCampSite.cpp \
		server/zone/objects/tangible/campkit/campsite/ImprovedCampSite.cpp \
		server/zone/objects/tangible/campkit/campsite/HQCampSite.cpp \
		server/zone/objects/tangible/campkit/campsite/FBCampSite.cpp \
		server/zone/objects/tangible/campkit/campsite/HTFBCampSite.cpp \
		server/zone/objects/tangible/component/ShipComponent.cpp \
		server/zone/objects/tangible/consumable/Consumable.cpp \
		server/zone/objects/tangible/consumable/food/Food.cpp \
		server/zone/objects/tangible/consumable/drink/Drink.cpp \
		server/zone/objects/tangible/Container.cpp \
		server/zone/objects/tangible/crafting/component/Component.cpp \
		server/zone/objects/tangible/crafting/component/armorcomponent/ArmorComponent.cpp \
		server/zone/objects/tangible/crafting/CraftingStation.cpp \
		server/zone/objects/tangible/crafting/CraftingTool.cpp \
		server/zone/objects/tangible/crafting/factorycrate/FactoryCrate.cpp \
		server/zone/objects/tangible/Datapad.cpp \
		server/zone/objects/tangible/deed/DeedObject.cpp \
		server/zone/objects/tangible/deed/factorydeed/FactoryDeed.cpp \
		server/zone/objects/tangible/deed/generatordeed/GeneratorDeed.cpp \
		server/zone/objects/tangible/deed/harvesterdeed/HarvesterDeed.cpp \
		server/zone/objects/tangible/deed/playerhousedeed/PlayerHouseDeed.cpp \
		server/zone/objects/tangible/deed/vehicledeed/VehicleDeed.cpp \
		server/zone/objects/tangible/deed/resourcedeed/ResourceDeed.cpp \
		server/zone/objects/tangible/firework/Firework.cpp \
        server/zone/objects/tangible/generic/GenericItem.cpp \
        server/zone/objects/tangible/generic/Dice.cpp \
		server/zone/objects/tangible/holocron/Holocron.cpp \
		server/zone/objects/tangible/instrument/Instrument.cpp \
		server/zone/objects/tangible/Inventory.cpp \
		server/zone/objects/tangible/inventory/CreatureInventory.cpp \
		server/zone/objects/tangible/inventory/BankInventory.cpp \
		server/zone/objects/tangible/lair/LairObject.cpp \
		server/zone/objects/tangible/MissionBag.cpp \
		server/zone/objects/tangible/pharmaceutical/CurePack.cpp \
		server/zone/objects/tangible/pharmaceutical/EnhancePack.cpp \
		server/zone/objects/tangible/pharmaceutical/Pharmaceutical.cpp \
		server/zone/objects/tangible/pharmaceutical/RevivePack.cpp \
		server/zone/objects/tangible/pharmaceutical/StatePack.cpp \
		server/zone/objects/tangible/pharmaceutical/StimPack.cpp \
		server/zone/objects/tangible/pharmaceutical/RangedStimPack.cpp \
		server/zone/objects/tangible/pharmaceutical/WoundPack.cpp \
		server/zone/objects/tangible/pharmaceutical/DotPack.cpp \
		server/zone/objects/tangible/tools/Tool.cpp \
		server/zone/objects/tangible/tools/smuggler/PrecisionLaserKnife.cpp \
		server/zone/objects/tangible/tools/smuggler/FlowAnalyzerNode.cpp \
		server/zone/objects/tangible/tools/smuggler/MolecularClamp.cpp \
		server/zone/objects/tangible/tools/smuggler/UpgradeKit.cpp \
		server/zone/objects/tangible/tools/repairtool/RepairTool.cpp \
		server/zone/objects/tangible/powerup/Powerup.cpp \
		server/zone/objects/tangible/resource/ResourceContainer.cpp \
		server/zone/objects/tangible/surveytool/SurveyTool.cpp \
		server/zone/objects/tangible/TangibleObject.cpp \
		server/zone/objects/tangible/terminal/bazaar/RegionBazaar.cpp \
		server/zone/objects/tangible/terminal/guild/GuildTerminal.cpp \
		server/zone/objects/tangible/terminal/cloning/CloningTerminal.cpp \
		server/zone/objects/tangible/terminal/cloning/InsuranceTerminal.cpp \
		server/zone/objects/tangible/terminal/mission/MissionTerminal.cpp \
		server/zone/objects/tangible/terminal/Terminal.cpp \
		server/zone/objects/tangible/terminal/travel/TravelTerminal.cpp \
		server/zone/objects/tangible/terminal/startinglocation/StartingLocationTerminal.cpp \
		server/zone/objects/tangible/terminal/vendor/VendorTerminal.cpp \
		server/zone/objects/tangible/terminal/camp/CampTerminal.cpp \
		server/zone/objects/tangible/gambling/LugjackMachine.cpp \
		server/zone/objects/tangible/gambling/JubileeWheel.cpp \
		server/zone/objects/tangible/ticketcollector/TicketCollector.cpp \
		server/zone/objects/tangible/ticket/Ticket.cpp \
		server/zone/objects/tangible/weapons/jedi/OneHandedJediWeapon.cpp \
		server/zone/objects/tangible/weapons/jedi/PolearmJediWeapon.cpp \
		server/zone/objects/tangible/weapons/jedi/TwoHandedJediWeapon.cpp \
		server/zone/objects/tangible/weapons/JediWeapon.cpp \
		server/zone/objects/tangible/weapons/melee/OneHandedMeleeWeapon.cpp \
		server/zone/objects/tangible/weapons/melee/PolearmMeleeWeapon.cpp \
		server/zone/objects/tangible/weapons/melee/TwoHandedMeleeWeapon.cpp \
		server/zone/objects/tangible/weapons/melee/UnarmedMeleeWeapon.cpp \
		server/zone/objects/tangible/weapons/MeleeWeapon.cpp \
		server/zone/objects/tangible/weapons/ranged/CarbineRangedWeapon.cpp \
		server/zone/objects/tangible/weapons/ranged/HeavyRangedWeapon.cpp \
		server/zone/objects/tangible/weapons/ranged/PistolRangedWeapon.cpp \
		server/zone/objects/tangible/weapons/ranged/RifleRangedWeapon.cpp \
		server/zone/objects/tangible/weapons/ranged/SpecialHeavyRangedWeapon.cpp \
		server/zone/objects/tangible/weapons/RangedWeapon.cpp \
		server/zone/objects/tangible/weapons/Weapon.cpp \
		server/zone/objects/tangible/weapons/ThrowableWeapon.cpp \
		server/zone/objects/tangible/weapons/throwable/TrapThrowableWeapon.cpp \
		server/zone/objects/tangible/weapons/throwable/GrenadeThrowableWeapon.cpp \
		server/zone/objects/tangible/wearables/Armor.cpp \
		server/zone/objects/tangible/wearables/Wearable.cpp \
		server/zone/objects/waypoint/WaypointObject.cpp \
		server/zone/ZoneClientSession.cpp \
		server/zone/Zone.cpp \
		server/zone/ZoneServer.cpp 
core3_SOURCES =	$(core3_IDLS) \
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
		server/ServerCore.cpp \
		server/status/StatusServer.cpp \
		server/zone/managers/bank/BankManagerImplementation.cpp \
		server/zone/managers/bazaar/BazaarManagerImplementation.cpp \
		server/zone/managers/bazaar/BazaarPlanetManagerImplementation.cpp \
		server/zone/managers/combat/CombatManager.cpp \
		server/zone/managers/combat/CommandQueueAction.cpp \
		server/zone/managers/crafting/CraftingManagerImplementation.cpp \
		server/zone/managers/creature/CreatureManagerImplementation.cpp \
		server/zone/managers/group/GroupManager.cpp \
		server/zone/managers/guild/GuildManagerImplementation.cpp \
		server/zone/managers/item/ItemManagerImplementation.cpp \
		server/zone/managers/item/ItemConfigManagerImplementation.cpp \
		server/zone/managers/loot/LootTableManagerImplementation.cpp \
		server/zone/managers/mission/MissionManagerImplementation.cpp \
		server/zone/managers/name/NameManager.cpp \
		server/zone/managers/object/ObjectManager.cpp \
		server/zone/managers/planet/HeightMap.cpp \
		server/zone/managers/planet/PlanetManagerImplementation.cpp \
		server/zone/managers/player/PlayerManagerImplementation.cpp \
		server/zone/managers/player/ProfessionManager.cpp \
		server/zone/managers/radial/RadialManager.cpp \
		server/zone/managers/resource/ResourceManagerImplementation.cpp \
		server/zone/managers/skills/imagedesign/CustomizationManager.cpp \
		server/zone/managers/skills/imagedesign/ImageDesignCustomization.cpp \
		server/zone/managers/skills/performance/PerformanceManager.cpp \
		server/zone/managers/skills/ScriptAttacksManager.cpp \
		server/zone/managers/skills/SkillManager.cpp \
		server/zone/managers/structure/StructureManagerImplementation.cpp \
		server/zone/managers/sui/SuiManager.cpp \
		server/zone/managers/user/UserManagerImplementation.cpp \
		server/zone/objects/attackable/AttackableObjectImplementation.cpp \
		server/zone/objects/tangible/lair/LairObjectImplementation.cpp \
		server/zone/objects/building/BuildingObjectImplementation.cpp \
		server/zone/objects/building/cell/CellObjectImplementation.cpp \
		server/zone/objects/building/StructurePermissionList.cpp \
		server/zone/objects/creature/action/ActionCreatureImplementation.cpp \
		server/zone/objects/creature/action/ActionImplementation.cpp \
		server/zone/objects/creature/bluefrog/BlueFrogCreatureImplementation.cpp \
		server/zone/objects/creature/buffs/Buff.cpp \
		server/zone/objects/creature/dots/DamageOverTime.cpp \
		server/zone/objects/creature/dots/DamageOverTimeList.cpp \
		server/zone/objects/creature/dots/DamageOverTimeMap.cpp \
		server/zone/objects/creature/CreatureImplementation.cpp \
		server/zone/objects/creature/CreatureObjectImplementation.cpp \
		server/zone/objects/creature/mount/MountCreatureImplementation.cpp \
		server/zone/objects/creature/recruiter/RecruiterCreatureImplementation.cpp \
		server/zone/objects/creature/shuttle/ShuttleCreatureImplementation.cpp \
		server/zone/objects/creature/trainer/TrainerCreatureImplementation.cpp \
		server/zone/objects/draftschematic/DraftSchematicExpPropGroupImplementation.cpp \
		server/zone/objects/draftschematic/DraftSchematicImplementation.cpp \
		server/zone/objects/draftschematic/DraftSchematicIngredientImplementation.cpp \
		server/zone/objects/draftschematic/DraftSchematicValuesImplementation.cpp \
		server/zone/objects/group/GroupObjectImplementation.cpp \
		server/zone/objects/guild/GuildImplementation.cpp \
		server/zone/objects/installation/factory/FactoryObjectImplementation.cpp \
		server/zone/objects/installation/generator/GeneratorObjectImplementation.cpp \
		server/zone/objects/installation/harvester/HarvesterObjectImplementation.cpp \
		server/zone/objects/installation/InstallationObjectImplementation.cpp \
		server/zone/objects/intangible/IntangibleObjectImplementation.cpp \
		server/zone/objects/mission/MissionObjectImplementation.cpp \
		server/zone/objects/player/FriendListImplementation.cpp \
		server/zone/objects/player/IgnoreListImplementation.cpp \
		server/zone/objects/player/PlayerImplementation.cpp \
		server/zone/objects/player/PlayerObjectImplementation.cpp \
		server/zone/objects/player/badges/Badge.cpp \
		server/zone/objects/player/sui/banktransferbox/SuiBankTransferBoxImplementation.cpp \
		server/zone/objects/player/sui/colorpicker/SuiColorPickerImplementation.cpp \
		server/zone/objects/player/sui/inputbox/SuiInputBoxImplementation.cpp \
		server/zone/objects/player/sui/listbox/SuiListBoxImplementation.cpp \
		server/zone/objects/player/sui/messagebox/SuiMessageBoxImplementation.cpp \
		server/zone/objects/player/sui/SuiBoxImplementation.cpp \
		server/zone/objects/player/sui/transferbox/SuiTransferBoxImplementation.cpp \
		server/zone/objects/scene/SceneObjectImplementation.cpp \
		server/zone/objects/scene/ContainerObject.cpp \
		server/zone/objects/ship/ShipObjectImplementation.cpp \
		server/zone/objects/static/StaticObjectImplementation.cpp \
		server/zone/objects/tangible/attachment/AttachmentImplementation.cpp \
		server/zone/objects/tangible/camokits/CamoKitImplementation.cpp \
		server/zone/objects/tangible/campkit/CampKitImplementation.cpp \
		server/zone/objects/tangible/campkit/campsite/CampSiteImplementation.cpp \
		server/zone/objects/tangible/campkit/campsite/BasicCampSiteImplementation.cpp \
		server/zone/objects/tangible/campkit/campsite/MultipersonCampSiteImplementation.cpp \
		server/zone/objects/tangible/campkit/campsite/ImprovedCampSiteImplementation.cpp \
		server/zone/objects/tangible/campkit/campsite/HQCampSiteImplementation.cpp \
		server/zone/objects/tangible/campkit/campsite/FBCampSiteImplementation.cpp \
		server/zone/objects/tangible/campkit/campsite/HTFBCampSiteImplementation.cpp \
		server/zone/objects/tangible/consumable/ConsumableImplementation.cpp \
		server/zone/objects/tangible/consumable/food/FoodImplementation.cpp \
		server/zone/objects/tangible/consumable/drink/DrinkImplementation.cpp \
		server/zone/objects/tangible/ContainerImplementation.cpp \
		server/zone/objects/tangible/InventoryImplementation.cpp \
		server/zone/objects/tangible/CustomizationVariables.cpp \
		server/zone/objects/tangible/crafting/component/ComponentImplementation.cpp \
		server/zone/objects/tangible/crafting/component/armorcomponent/ArmorComponentImplementation.cpp \
		server/zone/objects/tangible/crafting/CraftingStationImplementation.cpp \
		server/zone/objects/tangible/crafting/CraftingToolImplementation.cpp \
		server/zone/objects/tangible/crafting/factorycrate/FactoryCrateImplementation.cpp \
		server/zone/objects/tangible/deed/DeedObjectImplementation.cpp \
		server/zone/objects/tangible/deed/factorydeed/FactoryDeedImplementation.cpp \
		server/zone/objects/tangible/deed/generatordeed/GeneratorDeedImplementation.cpp \
		server/zone/objects/tangible/deed/harvesterdeed/HarvesterDeedImplementation.cpp \
		server/zone/objects/tangible/deed/playerhousedeed/PlayerHouseDeedImplementation.cpp \
		server/zone/objects/tangible/deed/vehicledeed/VehicleDeedImplementation.cpp \
		server/zone/objects/tangible/deed/resourcedeed/ResourceDeedImplementation.cpp \
		server/zone/objects/tangible/firework/FireworkImplementation.cpp \
        server/zone/objects/tangible/generic/GenericItemImplementation.cpp \
        server/zone/objects/tangible/generic/DiceImplementation.cpp \
		server/zone/objects/tangible/inventory/CreatureInventoryImplementation.cpp \
		server/zone/objects/tangible/inventory/BankInventoryImplementation.cpp \
		server/zone/objects/tangible/pharmaceutical/CurePackImplementation.cpp \
		server/zone/objects/tangible/pharmaceutical/EnhancePackImplementation.cpp \
		server/zone/objects/tangible/pharmaceutical/PharmaceuticalImplementation.cpp \
		server/zone/objects/tangible/pharmaceutical/RevivePackImplementation.cpp \
		server/zone/objects/tangible/pharmaceutical/StatePackImplementation.cpp \
		server/zone/objects/tangible/pharmaceutical/StimPackImplementation.cpp \
		server/zone/objects/tangible/pharmaceutical/RangedStimPackImplementation.cpp \
		server/zone/objects/tangible/pharmaceutical/WoundPackImplementation.cpp \
		server/zone/objects/tangible/pharmaceutical/DotPackImplementation.cpp \
		server/zone/objects/tangible/tools/ToolImplementation.cpp \
		server/zone/objects/tangible/tools/repairtool/RepairToolImplementation.cpp \
		server/zone/objects/tangible/powerup/PowerupImplementation.cpp \
		server/zone/objects/tangible/resource/ResourceContainerImplementation.cpp \
		server/zone/objects/tangible/surveytool/SurveyToolImplementation.cpp \
		server/zone/objects/tangible/TangibleObjectImplementation.cpp \
		server/zone/objects/tangible/ticketcollector/TicketCollectorImplementation.cpp \
		server/zone/objects/tangible/ticket/TicketImplementation.cpp \
		server/zone/objects/tangible/weapons/WeaponImplementation.cpp \
		server/zone/objects/tangible/weapons/ThrowableWeaponImplementation.cpp \
		server/zone/objects/tangible/weapons/throwable/TrapThrowableWeaponImplementation.cpp \
		server/zone/objects/tangible/weapons/throwable/GrenadeThrowableWeaponImplementation.cpp \
		server/zone/objects/tangible/wearables/WearableImplementation.cpp \
		server/zone/objects/tangible/wearables/ArmorImplementation.cpp \
		server/zone/packets/object/ObjectControllerMessage.cpp \
		server/zone/packets/charcreation/ClientCreateCharacter.cpp \
		server/zone/ZoneClientSessionImplementation.cpp \
		server/zone/ZoneImplementation.cpp \
		server/zone/ZoneMessageProcessorThread.cpp \
		server/zone/ZonePacketHandler.cpp \
		server/zone/ZoneProcessServerImplementation.cpp \
		server/zone/ZoneServerImplementation.cpp \
		main.cpp 
		