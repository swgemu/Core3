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

IDL_SOURCES = server/zone/Zone.idl \
				server/zone/ZoneClientSession.idl \
				server/zone/ZoneServer.idl \
				server/zone/objects/area/Area.idl \
				server/zone/objects/area/ActiveArea.idl \
				server/zone/objects/area/BaseArea.idl \
				server/zone/objects/area/NoBuildArea.idl \
				server/zone/objects/attackable/AttackableObject.idl \
				server/zone/objects/auction/AuctionItem.idl \
				server/zone/objects/scene/SceneObject.idl \
				server/zone/objects/creature/CreatureObject.idl \
				server/zone/objects/creature/Creature.idl \
				server/zone/objects/creature/CreatureGroup.idl \
				server/zone/objects/creature/shuttle/ShuttleCreature.idl \
				server/zone/objects/creature/action/ActionCreature.idl \
				server/zone/objects/creature/action/Action.idl \
				server/zone/objects/creature/trainer/TrainerCreature.idl \
				server/zone/objects/creature/bluefrog/BlueFrogCreature.idl \
				server/zone/objects/creature/bluefrog/BlueFrogVector.idl \
				server/zone/objects/creature/recruiter/RecruiterCreature.idl \
				server/zone/objects/creature/recruiter/imperial/ImperialRecruiterCreature.idl \
				server/zone/objects/creature/recruiter/rebel/RebelRecruiterCreature.idl \
				server/zone/objects/creature/mount/MountCreature.idl \
				server/zone/objects/player/Player.idl \
				server/zone/objects/player/FriendsList.idl \
				server/zone/objects/player/IgnoreList.idl \
				server/zone/objects/player/PlayerObject.idl \
				server/zone/objects/player/faction/FactionPointList.idl \
				server/zone/objects/player/sui/SuiBox.idl \
				server/zone/objects/player/sui/listbox/SuiListBox.idl \
				server/zone/objects/player/sui/messagebox/SuiMessageBox.idl \
				server/zone/objects/player/sui/transferbox/SuiTransferBox.idl \
				server/zone/objects/player/sui/banktransferbox/SuiBankTransferBox.idl \
				server/zone/objects/player/sui/inputbox/SuiInputBox.idl \
				server/zone/objects/player/sui/colorpicker/SuiColorPicker.idl \
				server/zone/objects/installation/factory/FactoryObject.idl \
				server/zone/objects/installation/generator/GeneratorObject.idl \
				server/zone/objects/installation/harvester/HarvesterObject.idl \
				server/zone/objects/installation/InstallationObject.idl \
				server/zone/objects/tangible/TangibleObject.idl \
				server/zone/objects/tangible/Container.idl \
				server/zone/objects/tangible/Inventory.idl \
				server/zone/objects/tangible/Datapad.idl \
				server/zone/objects/tangible/Bank.idl \
				server/zone/objects/tangible/MissionBag.idl \
				server/zone/objects/tangible/weapons/Weapon.idl \
				server/zone/objects/tangible/weapons/JediWeapon.idl \
				server/zone/objects/tangible/weapons/MeleeWeapon.idl \
				server/zone/objects/tangible/weapons/RangedWeapon.idl \
				server/zone/objects/tangible/appearance/HairObject.idl \
				server/zone/objects/tangible/wearables/Wearable.idl \
				server/zone/objects/tangible/wearables/Armor.idl \
				server/zone/objects/tangible/weapons/ranged/PistolRangedWeapon.idl \
				server/zone/objects/tangible/weapons/ranged/CarbineRangedWeapon.idl \
				server/zone/objects/tangible/weapons/ranged/RifleRangedWeapon.idl \
				server/zone/objects/tangible/weapons/ranged/SpecialHeavyRangedWeapon.idl \
				server/zone/objects/tangible/weapons/ranged/HeavyRangedWeapon.idl \
				server/zone/objects/tangible/weapons/melee/OneHandedMeleeWeapon.idl \
				server/zone/objects/tangible/weapons/melee/TwoHandedMeleeWeapon.idl \
				server/zone/objects/tangible/weapons/melee/PolearmMeleeWeapon.idl \
				server/zone/objects/tangible/weapons/melee/UnarmedMeleeWeapon.idl \
				server/zone/objects/tangible/weapons/jedi/OneHandedJediWeapon.idl \
				server/zone/objects/tangible/weapons/jedi/TwoHandedJediWeapon.idl \
				server/zone/objects/tangible/weapons/jedi/PolearmJediWeapon.idl \
				server/zone/objects/tangible/ticket/Ticket.idl \
				server/zone/objects/tangible/terminal/Terminal.idl \
				server/zone/objects/tangible/terminal/travel/TravelTerminal.idl \
				server/zone/objects/tangible/terminal/mission/MissionTerminal.idl \
				server/zone/objects/tangible/terminal/guild/GuildTerminal.idl \
				server/zone/objects/tangible/terminal/vendor/VendorTerminal.idl \
				server/zone/objects/tangible/terminal/bazaar/RegionBazaar.idl \
				server/zone/objects/tangible/ticketcollector/TicketCollector.idl \
				server/zone/objects/tangible/generic/GenericItem.idl \
				server/zone/objects/tangible/generic/Dice.idl \
				server/zone/objects/tangible/instrument/Instrument.idl \
				server/zone/objects/attackable/lair/LairObject.idl \
				server/zone/objects/tangible/surveytool/SurveyTool.idl \
				server/zone/objects/tangible/crafting/CraftingTool.idl \
				server/zone/objects/tangible/crafting/CraftingStation.idl \
				server/zone/objects/tangible/crafting/component/Component.idl \
				server/zone/objects/tangible/crafting/factorycrate/FactoryCrate.idl \
				server/zone/objects/tangible/resource/ResourceContainer.idl \
				server/zone/objects/tangible/pharmaceutical/Pharmaceutical.idl \
				server/zone/objects/tangible/pharmaceutical/EnhancePack.idl \
				server/zone/objects/tangible/pharmaceutical/WoundPack.idl \
				server/zone/objects/tangible/pharmaceutical/StimPack.idl \
				server/zone/objects/tangible/pharmaceutical/StatePack.idl \
				server/zone/objects/tangible/pharmaceutical/CurePack.idl \
				server/zone/objects/tangible/pharmaceutical/RevivePack.idl \
				server/zone/objects/tangible/attachment/Attachment.idl \
				server/zone/objects/tangible/powerup/Powerup.idl \
				server/zone/objects/tangible/holocron/Holocron.idl \
				server/zone/objects/tangible/firework/Firework.idl \
				server/zone/objects/tangible/deed/resourcedeed/ResourceDeed.idl \
				server/zone/objects/tangible/deed/factorydeed/FactoryDeed.idl \
				server/zone/objects/tangible/deed/generatordeed/GeneratorDeed.idl \
				server/zone/objects/tangible/deed/harvesterdeed/HarvesterDeed.idl \
				server/zone/objects/tangible/deed/vehicledeed/VehicleDeed.idl \
				server/zone/objects/tangible/deed/playerhousedeed/PlayerHouseDeed.idl \
				server/zone/objects/tangible/deed/DeedObject.idl \
				server/zone/objects/tangible/inventory/CreatureInventory.idl \
				server/zone/objects/static/firework/FireworkWorld.idl \
				server/zone/objects/static/StaticObject.idl \
				server/zone/objects/intangible/IntangibleObject.idl \
				server/zone/objects/group/GroupObject.idl \
				server/zone/objects/guild/Guild.idl \
				server/zone/objects/building/cell/CellObject.idl \
				server/zone/objects/building/BuildingObject.idl \
				server/zone/managers/crafting/CraftingManager.idl \
				server/zone/objects/draftschematic/DraftSchematic.idl \
				server/zone/objects/draftschematic/DraftSchematicGroup.idl \
				server/zone/objects/draftschematic/DraftSchematicIngredient.idl \
				server/zone/objects/draftschematic/DraftSchematicExpPropGroup.idl \
				server/zone/objects/draftschematic/DraftSchematicAttribute.idl \
				server/zone/objects/draftschematic/DraftSchematicValues.idl \
				server/zone/objects/manufacture/ManufactureSchematic.idl \
				server/zone/objects/mission/MissionObject.idl \
				server/zone/objects/waypoint/WaypointObject.idl \
				server/zone/objects/tangible/component/ShipComponent.idl \
				server/zone/objects/ship/ShipObject.idl \
				server/zone/managers/bazaar/BazaarManager.idl \
				server/zone/managers/bazaar/BazaarPlanetManager.idl \
				server/zone/managers/bank/BankManager.idl \
				server/zone/managers/mission/MissionManager.idl \
				server/zone/managers/guild/GuildMap.idl \
				server/zone/managers/guild/GuildManager.idl \
				server/zone/managers/player/PlayerManager.idl \
				server/zone/managers/player/PlayerMap.idl \
				server/zone/managers/item/ItemManager.idl \
				server/zone/managers/user/UserManager.idl \
				server/zone/managers/creature/CreatureManager.idl \
				server/zone/managers/planet/PlanetManager.idl \
				server/zone/managers/resource/ResourceManager.idl \
				server/zone/managers/resource/ResourceList.idl \
				server/zone/managers/resource/ResourceItem.idl \
				server/zone/managers/loot/LootTableManager.idl \
				server/chat/room/ChatRoom.idl \
				server/chat/ChatManager.idl

all:
	cd src && $(IDLC) $(IDL_SOURCES)
	cd build/unix && ../../configure && make
	cp build/unix/src/core3* bin
	#done

rebuild: clean all

config:
	autoreconf --force
	#done

clean: cleanidl
	cd build/unix && make clean
	#done

cleanidl:
	cd src && $(IDLC) -rebuild $(IDL_SOURCES)
