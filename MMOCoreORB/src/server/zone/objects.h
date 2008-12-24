/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef ZONEOBJECTS_H_
#define ZONEOBJECTS_H_

#include "objects/player/Player.h"
#include "objects/player/PlayerImplementation.h"
#include "objects/player/PlayerObject.h"
#include "objects/player/PlayerObjectImplementation.h"
#include "objects/player/FriendsList.h"
#include "objects/player/FriendsListImplementation.h"
#include "objects/player/IgnoreList.h"
#include "objects/player/IgnoreListImplementation.h"

#include "objects/creature/Creature.h"
#include "objects/creature/CreatureImplementation.h"
#include "objects/creature/CreatureObject.h"
#include "objects/creature/CreatureObjectImplementation.h"
#include "objects/creature/action/ActionCreature.h"
#include "objects/creature/action/ActionCreatureImplementation.h"
#include "objects/creature/trainer/TrainerCreature.h"
#include "objects/creature/trainer/TrainerCreatureImplementation.h"
#include "objects/creature/bluefrog/BlueFrogCreature.h"
#include "objects/creature/bluefrog/BlueFrogCreatureImplementation.h"
#include "objects/creature/shuttle/ShuttleCreature.h"
#include "objects/creature/shuttle/ShuttleCreatureImplementation.h"
#include "objects/creature/recruiter/RecruiterCreature.h"
#include "objects/creature/recruiter/RecruiterCreatureImplementation.h"
#include "objects/creature/mount/MountCreature.h"
#include "objects/creature/mount/MountCreatureImplementation.h"

#include "objects/group/GroupObject.h"
#include "objects/group/GroupObjectImplementation.h"
#include "objects/guild/Guild.h"
#include "objects/guild/GuildImplementation.h"

#include "objects/tangible/TangibleObject.h"
#include "objects/tangible/TangibleObjectImplementation.h"
#include "objects/tangible/Container.h"
#include "objects/tangible/ContainerImplementation.h"
#include "objects/tangible/Bank.h"
#include "objects/tangible/BankImplementation.h"
#include "objects/tangible/Datapad.h"
#include "objects/tangible/DatapadImplementation.h"
#include "objects/tangible/Inventory.h"
#include "objects/tangible/InventoryImplementation.h"
#include "objects/tangible/MissionBag.h"
#include "objects/tangible/MissionBagImplementation.h"
#include "objects/tangible/component/ShipComponent.h"
#include "objects/tangible/component/ShipComponentImplementation.h"
#include "objects/tangible/wearables/Wearable.h"
#include "objects/tangible/wearables/WearableImplementation.h"
#include "objects/tangible/wearables/Armor.h"
#include "objects/tangible/wearables/ArmorImplementation.h"
#include "objects/tangible/appearance/HairObject.h"
#include "objects/tangible/appearance/HairObjectImplementation.h"
#include "objects/tangible/ticket/Ticket.h"
#include "objects/tangible/ticket/TicketImplementation.h"
#include "objects/tangible/terminal/Terminal.h"
#include "objects/tangible/terminal/TerminalImplementation.h"
#include "objects/tangible/terminal/travel/TravelTerminal.h"
#include "objects/tangible/terminal/travel/TravelTerminalImplementation.h"
#include "objects/tangible/terminal/mission/MissionTerminal.h"
#include "objects/tangible/terminal/mission/MissionTerminalImplementation.h"
#include "objects/tangible/terminal/guild/GuildTerminal.h"
#include "objects/tangible/terminal/guild/GuildTerminalImplementation.h"
#include "objects/tangible/terminal/vendor/VendorTerminal.h"
#include "objects/tangible/terminal/vendor/VendorTerminalImplementation.h"
#include "objects/tangible/ticketcollector/TicketCollector.h"
#include "objects/tangible/ticketcollector/TicketCollectorImplementation.h"
#include "objects/tangible/instrument/Instrument.h"
#include "objects/tangible/instrument/InstrumentImplementation.h"
#include "objects/attackable/lair/LairObject.h"
#include "objects/attackable/lair/LairObjectImplementation.h"

// Deeds
#include "objects/tangible/deed/DeedObject.h"
#include "objects/tangible/deed/DeedObjectImplementation.h"
#include "objects/tangible/deed/harvesterdeed/HarvesterDeed.h"
#include "objects/tangible/deed/harvesterdeed/HarvesterDeedImplementation.h"
#include "objects/tangible/deed/factorydeed/FactoryDeed.h"
#include "objects/tangible/deed/factorydeed/FactoryDeedImplementation.h"
#include "objects/tangible/deed/generatordeed/GeneratorDeed.h"
#include "objects/tangible/deed/generatordeed/GeneratorDeedImplementation.h"
#include "objects/tangible/deed/vehicledeed/VehicleDeed.h"
#include "objects/tangible/deed/vehicledeed/VehicleDeedImplementation.h"
#include "objects/tangible/deed/playerhousedeed/PlayerHouseDeed.h"
#include "objects/tangible/deed/playerhousedeed/PlayerHouseDeedImplementation.h"
#include "objects/tangible/deed/resourcedeed/ResourceDeed.h"
#include "objects/tangible/deed/resourcedeed/ResourceDeedImplementation.h"

#include "objects/tangible/holocron/Holocron.h"
#include "objects/tangible/holocron/HolocronImplementation.h"
#include "objects/tangible/firework/Firework.h"
#include "objects/tangible/firework/FireworkImplementation.h"
#include "objects/tangible/surveytool/SurveyTool.h"
#include "objects/tangible/surveytool/SurveyToolImplementation.h"
#include "objects/tangible/crafting/CraftingTool.h"
#include "objects/tangible/crafting/CraftingToolImplementation.h"
#include "objects/tangible/crafting/CraftingStation.h"
#include "objects/tangible/crafting/component/Component.h"
#include "objects/tangible/crafting/component/ComponentImplementation.h"
#include "objects/tangible/crafting/factorycrate/FactoryCrate.h"
#include "objects/tangible/crafting/factorycrate/FactoryCrateImplementation.h"
#include "objects/tangible/crafting/CraftingStationImplementation.h"
#include "objects/tangible/resource/ResourceContainer.h"
#include "objects/tangible/resource/ResourceContainerImplementation.h"
#include "objects/tangible/attachment/Attachment.h"
#include "objects/tangible/attachment/AttachmentImplementation.h"
#include "objects/tangible/powerup/Powerup.h"
#include "objects/tangible/powerup/PowerupImplementation.h"
#include "objects/tangible/inventory/CreatureInventory.h"
#include "objects/tangible/inventory/CreatureInventoryImplementation.h"

#include "objects/tangible/weapons/Weapon.h"
#include "objects/tangible/weapons/WeaponImplementation.h"
#include "objects/tangible/weapons/melee/PolearmMeleeWeapon.h"
#include "objects/tangible/weapons/melee/PolearmMeleeWeaponImplementation.h"
#include "objects/tangible/weapons/melee/OneHandedMeleeWeapon.h"
#include "objects/tangible/weapons/melee/OneHandedMeleeWeaponImplementation.h"
#include "objects/tangible/weapons/melee/TwoHandedMeleeWeapon.h"
#include "objects/tangible/weapons/melee/TwoHandedMeleeWeaponImplementation.h"
#include "objects/tangible/weapons/melee/UnarmedMeleeWeapon.h"
#include "objects/tangible/weapons/melee/UnarmedMeleeWeaponImplementation.h"
#include "objects/tangible/weapons/ranged/PistolRangedWeapon.h"
#include "objects/tangible/weapons/ranged/PistolRangedWeaponImplementation.h"
#include "objects/tangible/weapons/ranged/RifleRangedWeapon.h"
#include "objects/tangible/weapons/ranged/RifleRangedWeaponImplementation.h"
#include "objects/tangible/weapons/ranged/CarbineRangedWeapon.h"
#include "objects/tangible/weapons/ranged/CarbineRangedWeaponImplementation.h"
#include "objects/tangible/weapons/ranged/SpecialHeavyRangedWeapon.h"
#include "objects/tangible/weapons/ranged/SpecialHeavyRangedWeaponImplementation.h"
#include "objects/tangible/weapons/ranged/HeavyRangedWeapon.h"
#include "objects/tangible/weapons/ranged/HeavyRangedWeaponImplementation.h"
#include "objects/tangible/weapons/jedi/OneHandedJediWeapon.h"
#include "objects/tangible/weapons/jedi/OneHandedJediWeaponImplementation.h"
#include "objects/tangible/weapons/jedi/TwoHandedJediWeapon.h"
#include "objects/tangible/weapons/jedi/TwoHandedJediWeaponImplementation.h"
#include "objects/tangible/weapons/jedi/PolearmJediWeapon.h"
#include "objects/tangible/weapons/jedi/PolearmJediWeaponImplementation.h"

#include "objects/tangible/pharmaceutical/Pharmaceutical.h"
#include "objects/tangible/pharmaceutical/PharmaceuticalImplementation.h"
#include "objects/tangible/pharmaceutical/EnhancePack.h"
#include "objects/tangible/pharmaceutical/EnhancePackImplementation.h"
#include "objects/tangible/pharmaceutical/WoundPack.h"
#include "objects/tangible/pharmaceutical/WoundPackImplementation.h"
#include "objects/tangible/pharmaceutical/StimPack.h"
#include "objects/tangible/pharmaceutical/StimPackImplementation.h"
#include "objects/tangible/pharmaceutical/StatePack.h"
#include "objects/tangible/pharmaceutical/StatePackImplementation.h"
#include "objects/tangible/pharmaceutical/CurePack.h"
#include "objects/tangible/pharmaceutical/CurePackImplementation.h"
#include "objects/tangible/pharmaceutical/RevivePack.h"
#include "objects/tangible/pharmaceutical/RevivePackImplementation.h"
#include "objects/tangible/pharmaceutical/CureAreaPack.h"
#include "objects/tangible/pharmaceutical/CureAreaPackImplementation.h"

#include "objects/tangible/generic/GenericItem.h"
#include "objects/tangible/generic/GenericItemImplementation.h"
#include "objects/tangible/generic/Dice.h"
#include "objects/tangible/generic/DiceImplementation.h"

#include "objects/intangible/IntangibleObject.h"
#include "objects/intangible/IntangibleObjectImplementation.h"

#include "objects/draftschematic/DraftSchematic.h"
#include "objects/draftschematic/DraftSchematicImplementation.h"
#include "objects/draftschematic/DraftSchematicGroup.h"
#include "objects/draftschematic/DraftSchematicGroupImplementation.h"
#include "objects/draftschematic/DraftSchematicIngredient.h"
#include "objects/draftschematic/DraftSchematicIngredientImplementation.h"
#include "objects/draftschematic/DraftSchematicExpPropGroup.h"
#include "objects/draftschematic/DraftSchematicExpPropGroupImplementation.h"
#include "objects/draftschematic/DraftSchematicAttribute.h"
#include "objects/draftschematic/DraftSchematicAttributeImplementation.h"
#include "objects/draftschematic/DraftSchematicValues.h"
#include "objects/draftschematic/DraftSchematicValuesImplementation.h"

#include "objects/manufacture/ManufactureSchematic.h"
#include "objects/manufacture/ManufactureSchematicImplementation.h"

#include "objects/mission/MissionObject.h"
#include "objects/mission/MissionObjectImplementation.h"

#include "objects/waypoint/WaypointObject.h"
#include "objects/waypoint/WaypointObjectImplementation.h"

#include "objects/building/cell/CellObject.h"
#include "objects/building/cell/CellObjectImplementation.h"

#include "objects/building/BuildingObject.h"
#include "objects/building/BuildingObjectImplementation.h"

#include "objects/scene/SceneObject.h"
#include "objects/scene/SceneObjectImplementation.h"

// Installations
#include "objects/installation/InstallationObject.h"
#include "objects/installation/InstallationObjectImplementation.h"
#include "objects/installation/harvester/HarvesterObject.h"
#include "objects/installation/harvester/HarvesterObjectImplementation.h"
#include "objects/installation/factory/FactoryObject.h"
#include "objects/installation/factory/FactoryObjectImplementation.h"
#include "objects/installation/generator/GeneratorObject.h"
#include "objects/installation/generator/GeneratorObjectImplementation.h"

#include "objects/mission/MissionObject.h"
#include "objects/mission/MissionObjectImplementation.h"

#include "objects/ship/ShipObject.h"
#include "objects/ship/ShipObjectImplementation.h"

#include "objects/static/StaticObject.h"
#include "objects/static/StaticObjectImplementation.h"
#include "objects/static/firework/FireworkWorld.h"
#include "objects/static/firework/FireworkWorldImplementation.h"

#include "objects/auction/AuctionItem.h"

// SUI
#include "objects/player/sui/SuiBoxImplementation.h"
#include "objects/player/sui/SuiBox.h"
#include "objects/player/sui/inputbox/SuiInputBoxImplementation.h"
#include "objects/player/sui/inputbox/SuiInputBox.h"
#include "objects/player/sui/listbox/SuiListBoxImplementation.h"
#include "objects/player/sui/listbox/SuiListBox.h"
#include "objects/player/sui/listbox/SuiListBoxVector.h"
#include "objects/player/sui/messagebox/SuiMessageBoxImplementation.h"
#include "objects/player/sui/messagebox/SuiMessageBox.h"
#include "objects/player/sui/transferbox/SuiTransferBoxImplementation.h"
#include "objects/player/sui/transferbox/SuiTransferBox.h"

#include "objects/tangible/weapons/ThrowableWeapon.h"
#include "objects/tangible/weapons/ThrowableWeaponImplementation.h"
#include "objects/tangible/weapons/throwable/TrapThrowableWeapon.h"
#include "objects/tangible/weapons/throwable/TrapThrowableWeaponImplementation.h"
#include "objects/tangible/camokits/CamoKit.h"
#include "objects/tangible/camokits/CamoKitImplementation.h"
#endif /*ZONEOBJECTS_H_*/
