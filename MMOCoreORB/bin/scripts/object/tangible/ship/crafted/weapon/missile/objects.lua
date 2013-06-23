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


object_tangible_ship_crafted_weapon_missile_shared_base_countermeasure = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_base_countermeasure.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_chaff.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741838,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "string_id_table",

	gameObjectType = 1073741838,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
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

	clientObjectCRC = 3245525817,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_base_countermeasure, "object/tangible/ship/crafted/weapon/missile/shared_base_countermeasure.iff")

object_tangible_ship_crafted_weapon_missile_shared_base_pack = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_base_pack.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_missile.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741837,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "string_id_table",

	gameObjectType = 1073741837,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
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

	clientObjectCRC = 1672702928,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_base_pack, "object/tangible/ship/crafted/weapon/missile/shared_base_pack.iff")

object_tangible_ship_crafted_weapon_missile_shared_countermeasure_chaff_launcher = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_chaff_launcher.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_chaff_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741840,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:weapon_chaff_launcher",

	gameObjectType = 1073741840,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:weapon_chaff_launcher",
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

	clientObjectCRC = 3047216132,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_countermeasure_chaff_launcher, "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_chaff_launcher.iff")

object_tangible_ship_crafted_weapon_missile_shared_countermeasure_chaff_pack = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_chaff_pack.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_chaff.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741838,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:weapon_chaff_pack",

	gameObjectType = 1073741838,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:weapon_chaff_pack",
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

	clientObjectCRC = 1564710260,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_countermeasure.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_countermeasure_chaff_pack, "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_chaff_pack.iff")

object_tangible_ship_crafted_weapon_missile_shared_countermeasure_confuser_launcher = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_confuser_launcher.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_chaff_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741840,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:weapon_confuser_launcher",

	gameObjectType = 1073741840,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:weapon_confuser_launcher",
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

	clientObjectCRC = 2635857595,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_countermeasure_confuser_launcher, "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_confuser_launcher.iff")

object_tangible_ship_crafted_weapon_missile_shared_countermeasure_confuser_pack = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_confuser_pack.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_chaff.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741838,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:weapon_confuser_pack",

	gameObjectType = 1073741838,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:weapon_confuser_pack",
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

	clientObjectCRC = 1375246682,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_countermeasure.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_countermeasure_confuser_pack, "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_confuser_pack.iff")

object_tangible_ship_crafted_weapon_missile_shared_countermeasure_decoy_launcher = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_decoy_launcher.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_chaff_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741840,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:weapon_decoy_launcher",

	gameObjectType = 1073741840,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:weapon_decoy_launcher",
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

	clientObjectCRC = 822727721,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_countermeasure_decoy_launcher, "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_decoy_launcher.iff")

object_tangible_ship_crafted_weapon_missile_shared_countermeasure_decoy_pack = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_decoy_pack.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_chaff.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741838,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:weapon_decoy_pack",

	gameObjectType = 1073741838,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:weapon_decoy_pack",
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

	clientObjectCRC = 17293110,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_countermeasure.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_countermeasure_decoy_pack, "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_decoy_pack.iff")

object_tangible_ship_crafted_weapon_missile_shared_countermeasure_em_launcher = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_em_launcher.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_chaff_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741840,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:weapon_em_launcher",

	gameObjectType = 1073741840,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:weapon_em_launcher",
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

	clientObjectCRC = 4142390620,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_countermeasure_em_launcher, "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_em_launcher.iff")

object_tangible_ship_crafted_weapon_missile_shared_countermeasure_em_pack = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_em_pack.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_chaff.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741838,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:weapon_em_pack",

	gameObjectType = 1073741838,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:weapon_em_pack",
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

	clientObjectCRC = 3439723072,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_countermeasure.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_countermeasure_em_pack, "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_em_pack.iff")

object_tangible_ship_crafted_weapon_missile_shared_countermeasure_microchaff_launcher = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_microchaff_launcher.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_chaff_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741840,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:weapon_microchaff_launcher",

	gameObjectType = 1073741840,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:weapon_microchaff_launcher",
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

	clientObjectCRC = 4217308443,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_countermeasure_microchaff_launcher, "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_microchaff_launcher.iff")

object_tangible_ship_crafted_weapon_missile_shared_countermeasure_microchaff_pack = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_microchaff_pack.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_chaff.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741838,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:weapon_microchaff_pack",

	gameObjectType = 1073741838,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:weapon_microchaff_pack",
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

	clientObjectCRC = 103083573,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_countermeasure.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_countermeasure_microchaff_pack, "object/tangible/ship/crafted/weapon/missile/shared_countermeasure_microchaff_pack.iff")

object_tangible_ship_crafted_weapon_missile_shared_weapon_basic_launcher = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_weapon_basic_launcher.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/xwing_weapon_neg_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:weapon_basic_launcher",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:weapon_basic_launcher",
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

	clientObjectCRC = 2943273728,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_weapon_basic_launcher, "object/tangible/ship/crafted/weapon/missile/shared_weapon_basic_launcher.iff")

object_tangible_ship_crafted_weapon_missile_shared_weapon_basic_pack = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_weapon_basic_pack.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/missile_proton_torpedo_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741837,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:weapon_basic_missile_pack",

	gameObjectType = 1073741837,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:weapon_basic_missile_pack",
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

	clientObjectCRC = 1453812677,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_weapon_basic_pack, "object/tangible/ship/crafted/weapon/missile/shared_weapon_basic_pack.iff")

object_tangible_ship_crafted_weapon_missile_shared_weapon_chaff_launcher = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_weapon_chaff_launcher.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_chaff_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:weapon_chaff_launcher",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:weapon_chaff_launcher",
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

	clientObjectCRC = 2657624858,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_weapon_chaff_launcher, "object/tangible/ship/crafted/weapon/missile/shared_weapon_chaff_launcher.iff")

object_tangible_ship_crafted_weapon_missile_shared_weapon_chaff_pack = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_weapon_chaff_pack.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_chaff.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741837,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:weapon_chaff_pack",

	gameObjectType = 1073741837,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:weapon_chaff_pack",
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

	clientObjectCRC = 1873034308,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_weapon_chaff_pack, "object/tangible/ship/crafted/weapon/missile/shared_weapon_chaff_pack.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_concussion_missile_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_concussion_missile_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_missile.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741837,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_concussion_missile",

	gameObjectType = 1073741837,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_concussion_missile_mk1",
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

	clientObjectCRC = 2871566567,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_pack.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_concussion_missile_mk1, "object/tangible/ship/crafted/weapon/missile/shared_wpn_concussion_missile_mk1.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_concussion_missile_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_concussion_missile_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_missile.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741837,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_concussion_missile",

	gameObjectType = 1073741837,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_concussion_missile_mk2",
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

	clientObjectCRC = 1883179120,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_pack.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_concussion_missile_mk2, "object/tangible/ship/crafted/weapon/missile/shared_wpn_concussion_missile_mk2.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_concussion_missile_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_concussion_missile_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_missile.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741837,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_concussion_missile",

	gameObjectType = 1073741837,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_concussion_missile_mk3",
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

	clientObjectCRC = 959606781,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_pack.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_concussion_missile_mk3, "object/tangible/ship/crafted/weapon/missile/shared_wpn_concussion_missile_mk3.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_imagerec_missile_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_imagerec_missile_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_missile.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741837,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_imagerec_missile",

	gameObjectType = 1073741837,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_imagerec_missile_mk1",
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

	clientObjectCRC = 190158470,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_pack.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_imagerec_missile_mk1, "object/tangible/ship/crafted/weapon/missile/shared_wpn_imagerec_missile_mk1.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_imagerec_missile_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_imagerec_missile_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_missile.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741837,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_imagerec_missile",

	gameObjectType = 1073741837,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_imagerec_missile_mk2",
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

	clientObjectCRC = 3494002193,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_pack.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_imagerec_missile_mk2, "object/tangible/ship/crafted/weapon/missile/shared_wpn_imagerec_missile_mk2.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_concussion_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_concussion_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_missile_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741839,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_launcher_concussion_mk1",

	gameObjectType = 1073741839,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_launcher_concussion_mk1",
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

	clientObjectCRC = 2721026212,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_concussion_mk1, "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_concussion_mk1.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_concussion_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_concussion_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_missile_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741839,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_launcher_concussion_mk2",

	gameObjectType = 1073741839,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_launcher_concussion_mk2",
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

	clientObjectCRC = 2033727539,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_concussion_mk2, "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_concussion_mk2.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_concussion_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_concussion_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_missile_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741839,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_launcher_concussion_mk3",

	gameObjectType = 1073741839,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_launcher_concussion_mk3",
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

	clientObjectCRC = 808804286,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_concussion_mk3, "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_concussion_mk3.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_imagerec_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_imagerec_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_missile_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741839,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_launcher_imagerec_mk1",

	gameObjectType = 1073741839,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_launcher_imagerec_mk1",
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

	clientObjectCRC = 1109435894,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_imagerec_mk1, "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_imagerec_mk1.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_imagerec_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_imagerec_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_missile_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741839,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_launcher_imagerec_mk2",

	gameObjectType = 1073741839,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_launcher_imagerec_mk2",
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

	clientObjectCRC = 2570521953,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_imagerec_mk2, "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_imagerec_mk2.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_proton_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_proton_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_missile_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741839,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_launcher_proton_mk1",

	gameObjectType = 1073741839,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_launcher_proton_mk1",
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

	clientObjectCRC = 2118814960,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_proton_mk1, "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_proton_mk1.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_proton_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_proton_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_missile_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741839,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_launcher_proton_mk2",

	gameObjectType = 1073741839,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_launcher_proton_mk2",
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

	clientObjectCRC = 2774344807,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_proton_mk2, "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_proton_mk2.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_proton_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_proton_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_missile_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741839,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_launcher_proton_mk3",

	gameObjectType = 1073741839,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_launcher_proton_mk3",
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

	clientObjectCRC = 3964683242,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_proton_mk3, "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_proton_mk3.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_proton_mk4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_proton_mk4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_missile_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741839,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_launcher_proton_mk4",

	gameObjectType = 1073741839,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_launcher_proton_mk4",
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

	clientObjectCRC = 397633790,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_proton_mk4, "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_proton_mk4.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_seismic_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_seismic_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_missile_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741839,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_launcher_seismic_mk1",

	gameObjectType = 1073741839,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_launcher_seismic_mk1",
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

	clientObjectCRC = 2922914559,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_seismic_mk1, "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_seismic_mk1.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_seismic_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_seismic_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_missile_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741839,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_launcher_seismic_mk2",

	gameObjectType = 1073741839,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_launcher_seismic_mk2",
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

	clientObjectCRC = 1966049896,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_seismic_mk2, "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_seismic_mk2.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_seismic_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_seismic_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_missile_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741839,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_launcher_seismic_mk3",

	gameObjectType = 1073741839,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_launcher_seismic_mk3",
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

	clientObjectCRC = 1008922085,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_seismic_mk3, "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_seismic_mk3.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_spacebomb_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_spacebomb_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_missile_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741839,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_launcher_spacebomb_mk1",

	gameObjectType = 1073741839,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_launcher_spacebomb_mk1",
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

	clientObjectCRC = 3027823737,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_spacebomb_mk1, "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_spacebomb_mk1.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_spacebomb_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_spacebomb_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_missile_launcher.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741839,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_launcher_spacebomb_mk2",

	gameObjectType = 1073741839,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_launcher_spacebomb_mk2",
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

	clientObjectCRC = 1869563118,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_launcher_spacebomb_mk2, "object/tangible/ship/crafted/weapon/missile/shared_wpn_launcher_spacebomb_mk2.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_proton_missile_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_proton_missile_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_missile.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741837,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_proton_missile",

	gameObjectType = 1073741837,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_proton_missile_mk1",
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

	clientObjectCRC = 1356357630,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_pack.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_proton_missile_mk1, "object/tangible/ship/crafted/weapon/missile/shared_wpn_proton_missile_mk1.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_proton_missile_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_proton_missile_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_missile.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741837,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_proton_missile",

	gameObjectType = 1073741837,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_proton_missile_mk2",
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

	clientObjectCRC = 2345662313,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_pack.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_proton_missile_mk2, "object/tangible/ship/crafted/weapon/missile/shared_wpn_proton_missile_mk2.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_proton_missile_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_proton_missile_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_missile.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741837,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_proton_missile",

	gameObjectType = 1073741837,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_proton_missile_mk3",
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

	clientObjectCRC = 3267530980,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_pack.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_proton_missile_mk3, "object/tangible/ship/crafted/weapon/missile/shared_wpn_proton_missile_mk3.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_proton_missile_mk4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_proton_missile_mk4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_missile.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741837,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_proton_missile",

	gameObjectType = 1073741837,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_proton_missile_mk4",
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

	clientObjectCRC = 958512112,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_pack.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_proton_missile_mk4, "object/tangible/ship/crafted/weapon/missile/shared_wpn_proton_missile_mk4.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_seismic_missile_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_seismic_missile_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_missile.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741837,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_seismic_missile",

	gameObjectType = 1073741837,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_seismic_missile_mk1",
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

	clientObjectCRC = 1794422147,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_pack.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_seismic_missile_mk1, "object/tangible/ship/crafted/weapon/missile/shared_wpn_seismic_missile_mk1.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_seismic_missile_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_seismic_missile_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_missile.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741837,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_seismic_missile",

	gameObjectType = 1073741837,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_seismic_missile_mk2",
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

	clientObjectCRC = 2984451348,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_pack.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_seismic_missile_mk2, "object/tangible/ship/crafted/weapon/missile/shared_wpn_seismic_missile_mk2.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_seismic_missile_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_seismic_missile_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_missile.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741837,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_seismic_missile",

	gameObjectType = 1073741837,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_seismic_missile_mk3",
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

	clientObjectCRC = 4176378521,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_pack.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_seismic_missile_mk3, "object/tangible/ship/crafted/weapon/missile/shared_wpn_seismic_missile_mk3.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_spacebomb_missile_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_spacebomb_missile_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_missile.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741837,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_spacebomb_missile_mk1",

	gameObjectType = 1073741837,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_spacebomb_missile_mk1",
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

	clientObjectCRC = 3906161899,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_pack.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_spacebomb_missile_mk1, "object/tangible/ship/crafted/weapon/missile/shared_wpn_spacebomb_missile_mk1.iff")

object_tangible_ship_crafted_weapon_missile_shared_wpn_spacebomb_missile_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/weapon/missile/shared_wpn_spacebomb_missile_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_ammo_missile.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741837,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:wpn_spacebomb_missile_mk1",

	gameObjectType = 1073741837,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:wpn_spacebomb_missile_mk2",
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

	clientObjectCRC = 868541564,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/crafted/weapon/missile/shared_base_pack.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_weapon_missile_shared_wpn_spacebomb_missile_mk2, "object/tangible/ship/crafted/weapon/missile/shared_wpn_spacebomb_missile_mk2.iff")
