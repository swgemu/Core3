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


object_tangible_ship_crafted_armor_shared_adv_durasteel_plating = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:adv_durasteel_plating",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:adv_durasteel_plating",
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

	clientObjectCRC = 3119994654,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_adv_durasteel_plating, "object/tangible/ship/crafted/armor/shared_adv_durasteel_plating.iff")

object_tangible_ship_crafted_armor_shared_armor_reinforcement_panel_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:armor_reinforcement_panel_mk1",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:armor_reinforcement_panel_mk1",
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

	clientObjectCRC = 2997247202,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk5.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk4.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk3.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk2.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk1.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_armor_reinforcement_panel_mk1, "object/tangible/ship/crafted/armor/shared_armor_reinforcement_panel_mk1.iff")

object_tangible_ship_crafted_armor_shared_armor_reinforcement_panel_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:armor_reinforcement_panel_mk2",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:armor_reinforcement_panel_mk2",
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

	clientObjectCRC = 1773270133,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk5.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk4.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk3.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk2.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_armor_reinforcement_panel_mk2, "object/tangible/ship/crafted/armor/shared_armor_reinforcement_panel_mk2.iff")

object_tangible_ship_crafted_armor_shared_armor_reinforcement_panel_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:armor_reinforcement_panel_mk3",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:armor_reinforcement_panel_mk3",
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

	clientObjectCRC = 549229560,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk5.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk4.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk3.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_armor_reinforcement_panel_mk3, "object/tangible/ship/crafted/armor/shared_armor_reinforcement_panel_mk3.iff")

object_tangible_ship_crafted_armor_shared_armor_reinforcement_panel_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:armor_reinforcement_panel_mk4",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:armor_reinforcement_panel_mk4",
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

	clientObjectCRC = 3680483564,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk5.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk4.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_armor_reinforcement_panel_mk4, "object/tangible/ship/crafted/armor/shared_armor_reinforcement_panel_mk4.iff")

object_tangible_ship_crafted_armor_shared_armor_reinforcement_panel_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:armor_reinforcement_panel_mk5",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:armor_reinforcement_panel_mk5",
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

	clientObjectCRC = 2454904673,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk5.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_armor_reinforcement_panel_mk5, "object/tangible/ship/crafted/armor/shared_armor_reinforcement_panel_mk5.iff")

object_tangible_ship_crafted_armor_shared_base_armor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/armor_bone_s01_chest_plate_f.sat",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@base_armor:base",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@base_armor:base",
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

	clientObjectCRC = 2002100175,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_base_armor, "object/tangible/ship/crafted/armor/shared_base_armor.iff")

object_tangible_ship_crafted_armor_shared_base_armor_subcomponent = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_armor_subcomponent",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_armor_subcomponent",
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

	clientObjectCRC = 773618140,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_base_armor_subcomponent, "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent.iff")

object_tangible_ship_crafted_armor_shared_base_armor_subcomponent_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_armor_subcomponent_mk1",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_armor_subcomponent_mk1",
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

	clientObjectCRC = 2949774675,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk5.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk4.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk3.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk2.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_base_armor_subcomponent_mk1, "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk1.iff")

object_tangible_ship_crafted_armor_shared_base_armor_subcomponent_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_armor_subcomponent_mk2",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_armor_subcomponent_mk2",
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

	clientObjectCRC = 1959155140,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk5.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk4.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk3.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_base_armor_subcomponent_mk2, "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk2.iff")

object_tangible_ship_crafted_armor_shared_base_armor_subcomponent_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_armor_subcomponent_mk3",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_armor_subcomponent_mk3",
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

	clientObjectCRC = 1036726857,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk5.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk4.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_base_armor_subcomponent_mk3, "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk3.iff")

object_tangible_ship_crafted_armor_shared_base_armor_subcomponent_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_armor_subcomponent_mk4",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_armor_subcomponent_mk4",
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

	clientObjectCRC = 3324516701,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk5.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_base_armor_subcomponent_mk4, "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk4.iff")

object_tangible_ship_crafted_armor_shared_base_armor_subcomponent_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_armor_subcomponent_mk5",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_armor_subcomponent_mk5",
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

	clientObjectCRC = 2401599184,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_base_armor_subcomponent_mk5, "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk5.iff")

object_tangible_ship_crafted_armor_shared_durasteel_plating = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:durasteel_plating",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:durasteel_plating",
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

	clientObjectCRC = 1660462348,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_durasteel_plating, "object/tangible/ship/crafted/armor/shared_durasteel_plating.iff")

object_tangible_ship_crafted_armor_shared_experimental_armor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:exp_durasteel_plating",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:exp_durasteel_plating",
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

	clientObjectCRC = 2006663885,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_experimental_armor, "object/tangible/ship/crafted/armor/shared_experimental_armor.iff")

object_tangible_ship_crafted_armor_shared_heavy_durasteel_plating = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:hvy_durasteel_plating",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:hvy_durasteel_plating",
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

	clientObjectCRC = 3716397337,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_heavy_durasteel_plating, "object/tangible/ship/crafted/armor/shared_heavy_durasteel_plating.iff")

object_tangible_ship_crafted_armor_shared_light_durasteel_plating = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:lgt_durasteel_plating",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:lgt_durasteel_plating",
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

	clientObjectCRC = 2691365358,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_light_durasteel_plating, "object/tangible/ship/crafted/armor/shared_light_durasteel_plating.iff")

object_tangible_ship_crafted_armor_shared_mass_reduction_kit_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:mass_reduction_kit_mk1",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:mass_reduction_kit_mk1",
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

	clientObjectCRC = 3987898855,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk5.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk4.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk3.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk2.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk1.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_mass_reduction_kit_mk1, "object/tangible/ship/crafted/armor/shared_mass_reduction_kit_mk1.iff")

object_tangible_ship_crafted_armor_shared_mass_reduction_kit_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:mass_reduction_kit_mk2",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:mass_reduction_kit_mk2",
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

	clientObjectCRC = 916793712,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk5.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk4.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk3.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk2.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_mass_reduction_kit_mk2, "object/tangible/ship/crafted/armor/shared_mass_reduction_kit_mk2.iff")

object_tangible_ship_crafted_armor_shared_mass_reduction_kit_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:mass_reduction_kit_mk3",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:mass_reduction_kit_mk3",
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

	clientObjectCRC = 2141736701,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk5.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk4.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk3.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_mass_reduction_kit_mk3, "object/tangible/ship/crafted/armor/shared_mass_reduction_kit_mk3.iff")

object_tangible_ship_crafted_armor_shared_mass_reduction_kit_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:mass_reduction_kit_mk4",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:mass_reduction_kit_mk4",
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

	clientObjectCRC = 2219533801,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk5.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk4.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_mass_reduction_kit_mk4, "object/tangible/ship/crafted/armor/shared_mass_reduction_kit_mk4.iff")

object_tangible_ship_crafted_armor_shared_mass_reduction_kit_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:mass_reduction_kit_mk5",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:mass_reduction_kit_mk5",
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

	clientObjectCRC = 3443917412,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent.iff", "object/tangible/ship/crafted/armor/shared_base_armor_subcomponent_mk5.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_armor_shared_mass_reduction_kit_mk5, "object/tangible/ship/crafted/armor/shared_mass_reduction_kit_mk5.iff")
