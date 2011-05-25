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


object_tangible_ship_crafted_shields_shared_adv_deflector_shields = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:adv_deflector_shields",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:adv_deflector_shields",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 512254018,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_adv_deflector_shields, "object/tangible/ship/crafted/shields/shared_adv_deflector_shields.iff")

object_tangible_ship_crafted_shields_shared_advanced_projector_unit = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:advanced_projector_unit",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:advanced_projector_unit",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3156847701,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_advanced_projector_unit, "object/tangible/ship/crafted/shields/shared_advanced_projector_unit.iff")

object_tangible_ship_crafted_shields_shared_base_shields = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ins_all_pow_fusion_ion_u0.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@base_shield_generator:base",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@base_shield_generator:base",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1334075435,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_base_shields, "object/tangible/ship/crafted/shields/shared_base_shields.iff")

object_tangible_ship_crafted_shields_shared_base_shields_subcomponent = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_shields_subcomponent",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_shields_subcomponent",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 501625805,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_base_shields_subcomponent, "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff")

object_tangible_ship_crafted_shields_shared_base_shields_subcomponent_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_shields_subcomponent_mk1",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_shields_subcomponent_mk1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1088509023,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk3.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk2.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_base_shields_subcomponent_mk1, "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk1.iff")

object_tangible_ship_crafted_shields_shared_base_shields_subcomponent_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_shields_subcomponent_mk2",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_shields_subcomponent_mk2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2616655048,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk3.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_base_shields_subcomponent_mk2, "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk2.iff")

object_tangible_ship_crafted_shields_shared_base_shields_subcomponent_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_shields_subcomponent_mk3",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_shields_subcomponent_mk3",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3539704645,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_base_shields_subcomponent_mk3, "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk3.iff")

object_tangible_ship_crafted_shields_shared_base_shields_subcomponent_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_shields_subcomponent_mk4",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_shields_subcomponent_mk4",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 689483857,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_base_shields_subcomponent_mk4, "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff")

object_tangible_ship_crafted_shields_shared_base_shields_subcomponent_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_shields_subcomponent_mk5",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_shields_subcomponent_mk5",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1612044252,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_base_shields_subcomponent_mk5, "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff")

object_tangible_ship_crafted_shields_shared_basic_shields = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ins_all_pow_fusion_ion_u0.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_n:base_shields",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_shields",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2199672090,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_basic_shields, "object/tangible/ship/crafted/shields/shared_basic_shields.iff")

object_tangible_ship_crafted_shields_shared_deflector_shields = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:deflector_shields",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:deflector_shields",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2014890702,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_deflector_shields, "object/tangible/ship/crafted/shields/shared_deflector_shields.iff")

object_tangible_ship_crafted_shields_shared_exp_deflector_shields = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:exp_deflector_shields",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:exp_deflector_shields",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2951736677,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_exp_deflector_shields, "object/tangible/ship/crafted/shields/shared_exp_deflector_shields.iff")

object_tangible_ship_crafted_shields_shared_heavy_deflector_shields = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:heavy_deflector_shields",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:heavy_deflector_shields",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3437680347,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_heavy_deflector_shields, "object/tangible/ship/crafted/shields/shared_heavy_deflector_shields.iff")

object_tangible_ship_crafted_shields_shared_light_deflector_shields = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:light_deflector_shields",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:light_deflector_shields",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2970588716,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_light_deflector_shields, "object/tangible/ship/crafted/shields/shared_light_deflector_shields.iff")

object_tangible_ship_crafted_shields_shared_shield_energy_saver_kit_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_energy_saver_kit_mk1",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_energy_saver_kit_mk1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1931620288,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk3.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk2.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk1.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_energy_saver_kit_mk1, "object/tangible/ship/crafted/shields/shared_shield_energy_saver_kit_mk1.iff")

object_tangible_ship_crafted_shields_shared_shield_energy_saver_kit_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_energy_saver_kit_mk2",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_energy_saver_kit_mk2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2822080343,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk3.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk2.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_energy_saver_kit_mk2, "object/tangible/ship/crafted/shields/shared_shield_energy_saver_kit_mk2.iff")

object_tangible_ship_crafted_shields_shared_shield_energy_saver_kit_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_energy_saver_kit_mk3",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_energy_saver_kit_mk3",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3778601178,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk3.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_energy_saver_kit_mk3, "object/tangible/ship/crafted/shields/shared_shield_energy_saver_kit_mk3.iff")

object_tangible_ship_crafted_shields_shared_shield_energy_saver_kit_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_energy_saver_kit_mk4",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_energy_saver_kit_mk4",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 450612174,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_energy_saver_kit_mk4, "object/tangible/ship/crafted/shields/shared_shield_energy_saver_kit_mk4.iff")

object_tangible_ship_crafted_shields_shared_shield_energy_saver_kit_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_energy_saver_kit_mk5",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_energy_saver_kit_mk5",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1406577731,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_energy_saver_kit_mk5, "object/tangible/ship/crafted/shields/shared_shield_energy_saver_kit_mk5.iff")

object_tangible_ship_crafted_shields_shared_shield_intensifier_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_intensifier_mk1",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_intensifier_mk1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 46751920,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk3.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk2.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk1.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_intensifier_mk1, "object/tangible/ship/crafted/shields/shared_shield_intensifier_mk1.iff")

object_tangible_ship_crafted_shields_shared_shield_intensifier_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_intensifier_mk2",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_intensifier_mk2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3655256103,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk3.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk2.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_intensifier_mk2, "object/tangible/ship/crafted/shields/shared_shield_intensifier_mk2.iff")

object_tangible_ship_crafted_shields_shared_shield_intensifier_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_intensifier_mk3",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_intensifier_mk3",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2429792170,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk3.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_intensifier_mk3, "object/tangible/ship/crafted/shields/shared_shield_intensifier_mk3.iff")

object_tangible_ship_crafted_shields_shared_shield_intensifier_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_intensifier_mk4",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_intensifier_mk4",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1798341822,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_intensifier_mk4, "object/tangible/ship/crafted/shields/shared_shield_intensifier_mk4.iff")

object_tangible_ship_crafted_shields_shared_shield_intensifier_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_intensifier_mk5",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_intensifier_mk5",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 574481203,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_intensifier_mk5, "object/tangible/ship/crafted/shields/shared_shield_intensifier_mk5.iff")

object_tangible_ship_crafted_shields_shared_shield_limiter_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_limiter_mk1",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_limiter_mk1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3366846680,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk3.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk2.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk1.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_limiter_mk1, "object/tangible/ship/crafted/shields/shared_shield_limiter_mk1.iff")

object_tangible_ship_crafted_shields_shared_shield_limiter_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_limiter_mk2",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_limiter_mk2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 330934351,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk3.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk2.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_limiter_mk2, "object/tangible/ship/crafted/shields/shared_shield_limiter_mk2.iff")

object_tangible_ship_crafted_shields_shared_shield_limiter_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_limiter_mk3",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_limiter_mk3",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1521799106,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk3.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_limiter_mk3, "object/tangible/ship/crafted/shields/shared_shield_limiter_mk3.iff")

object_tangible_ship_crafted_shields_shared_shield_limiter_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_limiter_mk4",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_limiter_mk4",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2706891990,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_limiter_mk4, "object/tangible/ship/crafted/shields/shared_shield_limiter_mk4.iff")

object_tangible_ship_crafted_shields_shared_shield_limiter_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_limiter_mk5",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_limiter_mk5",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3898245979,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_limiter_mk5, "object/tangible/ship/crafted/shields/shared_shield_limiter_mk5.iff")

object_tangible_ship_crafted_shields_shared_shield_overcharger_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_overcharger_mk1",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_overcharger_mk1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1951222314,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk3.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk2.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk1.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_overcharger_mk1, "object/tangible/ship/crafted/shields/shared_shield_overcharger_mk1.iff")

object_tangible_ship_crafted_shields_shared_shield_overcharger_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_overcharger_mk2",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_overcharger_mk2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2941969085,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk3.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk2.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_overcharger_mk2, "object/tangible/ship/crafted/shields/shared_shield_overcharger_mk2.iff")

object_tangible_ship_crafted_shields_shared_shield_overcharger_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_overcharger_mk3",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_overcharger_mk3",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3864495408,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk3.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_overcharger_mk3, "object/tangible/ship/crafted/shields/shared_shield_overcharger_mk3.iff")

object_tangible_ship_crafted_shields_shared_shield_overcharger_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_overcharger_mk4",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_overcharger_mk4",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 498380324,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk4.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_overcharger_mk4, "object/tangible/ship/crafted/shields/shared_shield_overcharger_mk4.iff")

object_tangible_ship_crafted_shields_shared_shield_overcharger_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:shield_overcharger_mk5",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:shield_overcharger_mk5",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1421461929,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent.iff", "object/tangible/ship/crafted/shields/shared_base_shields_subcomponent_mk5.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_shield_overcharger_mk5, "object/tangible/ship/crafted/shields/shared_shield_overcharger_mk5.iff")

object_tangible_ship_crafted_shields_shared_standard_projector_unit = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:standard_projector_unit",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:standard_projector_unit",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 129931938,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_shields_shared_standard_projector_unit, "object/tangible/ship/crafted/shields/shared_standard_projector_unit.iff")
