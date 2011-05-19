--Copyright (C) 2009 <SWGEmu>

--This File is part of Core3.

--This program is free software; you can redistribute
--it and/or modify it under the terms of the GNU Lesser
--General Public License as published by the Free Software
--Foundation; either version 2 of the License,
--or (at your option) any later version.

--This program is distributed in the hope that it will be useful,
--but WITHOUT ANY WARRANTY; without even the implied warranty of
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
--See the GNU Lesser General Public License for
--more details.

--You should have received a copy of the GNU Lesser General
--Public License along with this program; if not, write to
--the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

--Linking Engine3 statically or dynamically with other modules
--is making a combined work based on Engine3.
--Thus, the terms and conditions of the GNU Lesser General Public License
--cover the whole combination.

--In addition, as a special exception, the copyright holders of Engine3
--give you permission to combine Engine3 program with free software
--programs or libraries that are released under the GNU LGPL and with
--code included in the standard release of Core3 under the GNU LGPL
--license (or modified versions of such code, with unchanged license).
--You may copy and distribute such a system following the terms of the
--GNU LGPL for Engine3 and the licenses of the other code concerned,
--provided that you include the source code of that other code when
--and as the GNU LGPL requires distribution of source code.

--Note that people who make modified versions of Engine3 are not obligated
--to grant this special exception for their modified versions;
--it is their choice whether to do so. The GNU Lesser General Public License
--gives permission to release a modified version without this exception;
--this exception also makes it possible to release a modified version
--which carries forward this exception.


object_tangible_loot_dungeon_geonosian_mad_bunker_shared_engineering_datapad = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_datapad_s2_inventory.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8211,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_d:biogenic_engineering_datapad",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@trophy_lookat:heirloom_bowl",

	noBuildRadius = 0,

	objectName = "@item_n:biogenic_engineering_datapad",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1212603957,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_loot_dungeon_geonosian_mad_bunker_shared_engineering_datapad, "object/tangible/loot/dungeon/geonosian_mad_bunker/shared_engineering_datapad.iff")

object_tangible_loot_dungeon_geonosian_mad_bunker_shared_engineering_key = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_ticket_inventory.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8211,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_d:biogenic_engineering_key",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@trophy_lookat:heirloom_bowl",

	noBuildRadius = 0,

	objectName = "@item_n:biogenic_engineering_key",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3779706256,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_loot_dungeon_geonosian_mad_bunker_shared_engineering_key, "object/tangible/loot/dungeon/geonosian_mad_bunker/shared_engineering_key.iff")

object_tangible_loot_dungeon_geonosian_mad_bunker_shared_passkey = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_ticket_inventory.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8211,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_d:biogenic_passkey",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@trophy_lookat:heirloom_bowl",

	noBuildRadius = 0,

	objectName = "@item_n:biogenic_passkey",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4110674252,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_loot_dungeon_geonosian_mad_bunker_shared_passkey, "object/tangible/loot/dungeon/geonosian_mad_bunker/shared_passkey.iff")

object_tangible_loot_dungeon_geonosian_mad_bunker_shared_relic_gbb_chemical_tab = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/thm_prp_bacta_ampules.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8211,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_d:relic_gbb_chemical_tab",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@trophy_lookat:relic_gbb_chemical_tab",

	noBuildRadius = 0,

	objectName = "@item_n:relic_gbb_chemical_tab",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1953839447,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_loot_dungeon_geonosian_mad_bunker_shared_relic_gbb_chemical_tab, "object/tangible/loot/dungeon/geonosian_mad_bunker/shared_relic_gbb_chemical_tab.iff")

object_tangible_loot_dungeon_geonosian_mad_bunker_shared_relic_gbb_data_tab = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/thm_prp_ledger.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8211,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_d:relic_gbb_data_tab",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@trophy_lookat:relic_gbb_data_tab",

	noBuildRadius = 0,

	objectName = "@item_n:relic_gbb_data_tab",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2836503277,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_loot_dungeon_geonosian_mad_bunker_shared_relic_gbb_data_tab, "object/tangible/loot/dungeon/geonosian_mad_bunker/shared_relic_gbb_data_tab.iff")

object_tangible_loot_dungeon_geonosian_mad_bunker_shared_relic_gbb_honey_carafe = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_tankard_full.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8211,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_d:relic_gbb_honey_carafe",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@trophy_lookat:relic_gbb_honey_carafe",

	noBuildRadius = 0,

	objectName = "@item_n:relic_gbb_honey_carafe",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1253190673,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_loot_dungeon_geonosian_mad_bunker_shared_relic_gbb_honey_carafe, "object/tangible/loot/dungeon/geonosian_mad_bunker/shared_relic_gbb_honey_carafe.iff")

object_tangible_loot_dungeon_geonosian_mad_bunker_shared_relic_gbb_ration_kit = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_ration_kit_lg.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8211,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_d:relic_gbb_ration_kit",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@trophy_lookat:relic_gbb_ration_kit",

	noBuildRadius = 0,

	objectName = "@item_n:relic_gbb_ration_kit",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 395732955,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_loot_dungeon_geonosian_mad_bunker_shared_relic_gbb_ration_kit, "object/tangible/loot/dungeon/geonosian_mad_bunker/shared_relic_gbb_ration_kit.iff")

object_tangible_loot_dungeon_geonosian_mad_bunker_shared_relic_gbb_small_ball = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/msc_toy_ball_m.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8211,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_d:relic_gbb_small_ball",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@trophy_lookat:relic_gbb_small_ball",

	noBuildRadius = 0,

	objectName = "@item_n:relic_gbb_small_ball",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3247484355,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_loot_dungeon_geonosian_mad_bunker_shared_relic_gbb_small_ball, "object/tangible/loot/dungeon/geonosian_mad_bunker/shared_relic_gbb_small_ball.iff")

object_tangible_loot_dungeon_geonosian_mad_bunker_shared_relic_gbb_spice_container = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_spice_container.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8211,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_d:relic_gbb_spice_container",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@trophy_lookat:relic_gbb_spice_container",

	noBuildRadius = 0,

	objectName = "@item_n:relic_gbb_spice_container",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2674127359,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_loot_dungeon_geonosian_mad_bunker_shared_relic_gbb_spice_container, "object/tangible/loot/dungeon/geonosian_mad_bunker/shared_relic_gbb_spice_container.iff")

object_tangible_loot_dungeon_geonosian_mad_bunker_shared_relic_gbb_tech_kit = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_ration_kit_m.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8211,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_d:relic_gbb_tech_kit",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@trophy_lookat:relic_gbb_tech_kit",

	noBuildRadius = 0,

	objectName = "@item_n:relic_gbb_tech_kit",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1965831716,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_loot_dungeon_geonosian_mad_bunker_shared_relic_gbb_tech_kit, "object/tangible/loot/dungeon/geonosian_mad_bunker/shared_relic_gbb_tech_kit.iff")
