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


object_tangible_ship_crafted_capacitor_shared_advanced_capacitor_battery = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_advanced_capacitor_battery.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:advanced_capacitor_battery",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:advanced_capacitor_battery",
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

	clientObjectCRC = 3843288645,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_advanced_capacitor_battery, "object/tangible/ship/crafted/capacitor/shared_advanced_capacitor_battery.iff")

object_tangible_ship_crafted_capacitor_shared_advanced_recharge_module = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_advanced_recharge_module.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:advanced_recharge_module",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:advanced_recharge_module",
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

	clientObjectCRC = 4282694391,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_advanced_recharge_module, "object/tangible/ship/crafted/capacitor/shared_advanced_recharge_module.iff")

object_tangible_ship_crafted_capacitor_shared_base_capacitor = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_base_capacitor.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_music_red_ball_jet_organ.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@base_weapon_capacitor:base",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@base_weapon_capacitor:base",
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

	clientObjectCRC = 3064505654,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_base_capacitor, "object/tangible/ship/crafted/capacitor/shared_base_capacitor.iff")

object_tangible_ship_crafted_capacitor_shared_base_capacitor_subcomponent = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_capacitor_subcomponent",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_capacitor_subcomponent",
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

	clientObjectCRC = 4258529862,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_base_capacitor_subcomponent, "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff")

object_tangible_ship_crafted_capacitor_shared_base_capacitor_subcomponent_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_capacitor_subcomponent_mk1",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_capacitor_subcomponent_mk1",
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

	clientObjectCRC = 1484781854,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk3.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk2.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_base_capacitor_subcomponent_mk1, "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk1.iff")

object_tangible_ship_crafted_capacitor_shared_base_capacitor_subcomponent_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_capacitor_subcomponent_mk2",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_capacitor_subcomponent_mk2",
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

	clientObjectCRC = 2204651913,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk3.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_base_capacitor_subcomponent_mk2, "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk2.iff")

object_tangible_ship_crafted_capacitor_shared_base_capacitor_subcomponent_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_capacitor_subcomponent_mk3",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_capacitor_subcomponent_mk3",
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

	clientObjectCRC = 3395630596,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_base_capacitor_subcomponent_mk3, "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk3.iff")

object_tangible_ship_crafted_capacitor_shared_base_capacitor_subcomponent_mk4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_capacitor_subcomponent_mk4",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_capacitor_subcomponent_mk4",
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

	clientObjectCRC = 830872848,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_base_capacitor_subcomponent_mk4, "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff")

object_tangible_ship_crafted_capacitor_shared_base_capacitor_subcomponent_mk5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_capacitor_subcomponent_mk5",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_capacitor_subcomponent_mk5",
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

	clientObjectCRC = 2022406813,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_base_capacitor_subcomponent_mk5, "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff")

object_tangible_ship_crafted_capacitor_shared_basic_capacitor = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_basic_capacitor.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_n:base_capacitor",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_capacitor",
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

	clientObjectCRC = 1364868080,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_basic_capacitor, "object/tangible/ship/crafted/capacitor/shared_basic_capacitor.iff")

object_tangible_ship_crafted_capacitor_shared_capacitor_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_capacitor_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:capacitor_mk1",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:capacitor_mk1",
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

	clientObjectCRC = 277361603,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_capacitor_mk1, "object/tangible/ship/crafted/capacitor/shared_capacitor_mk1.iff")

object_tangible_ship_crafted_capacitor_shared_capacitor_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_capacitor_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:capacitor_mk2",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:capacitor_mk2",
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

	clientObjectCRC = 3416234836,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_capacitor_mk2, "object/tangible/ship/crafted/capacitor/shared_capacitor_mk2.iff")

object_tangible_ship_crafted_capacitor_shared_capacitor_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_capacitor_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:capacitor_mk3",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:capacitor_mk3",
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

	clientObjectCRC = 2190671065,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_capacitor_mk3, "object/tangible/ship/crafted/capacitor/shared_capacitor_mk3.iff")

object_tangible_ship_crafted_capacitor_shared_capacitor_mk4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_capacitor_mk4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:capacitor_mk4",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:capacitor_mk4",
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

	clientObjectCRC = 2037503949,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_capacitor_mk4, "object/tangible/ship/crafted/capacitor/shared_capacitor_mk4.iff")

object_tangible_ship_crafted_capacitor_shared_capacitor_mk5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_capacitor_mk5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:capacitor_mk5",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:capacitor_mk5",
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

	clientObjectCRC = 813477952,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_capacitor_mk5, "object/tangible/ship/crafted/capacitor/shared_capacitor_mk5.iff")

object_tangible_ship_crafted_capacitor_shared_energy_saver_battery_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_energy_saver_battery_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:energy_saver_battery_mk1",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:energy_saver_battery_mk1",
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

	clientObjectCRC = 598079079,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk3.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk2.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk1.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_energy_saver_battery_mk1, "object/tangible/ship/crafted/capacitor/shared_energy_saver_battery_mk1.iff")

object_tangible_ship_crafted_capacitor_shared_energy_saver_battery_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_energy_saver_battery_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:energy_saver_battery_mk2",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:energy_saver_battery_mk2",
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

	clientObjectCRC = 4172439280,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk3.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk2.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_energy_saver_battery_mk2, "object/tangible/ship/crafted/capacitor/shared_energy_saver_battery_mk2.iff")

object_tangible_ship_crafted_capacitor_shared_energy_saver_battery_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_energy_saver_battery_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:energy_saver_battery_mk3",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:energy_saver_battery_mk3",
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

	clientObjectCRC = 2982099325,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk3.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_energy_saver_battery_mk3, "object/tangible/ship/crafted/capacitor/shared_energy_saver_battery_mk3.iff")

object_tangible_ship_crafted_capacitor_shared_energy_saver_battery_mk4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_energy_saver_battery_mk4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:energy_saver_battery_mk4",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:energy_saver_battery_mk4",
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

	clientObjectCRC = 1247548009,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_energy_saver_battery_mk4, "object/tangible/ship/crafted/capacitor/shared_energy_saver_battery_mk4.iff")

object_tangible_ship_crafted_capacitor_shared_energy_saver_battery_mk5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_energy_saver_battery_mk5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:energy_saver_battery_mk5",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:energy_saver_battery_mk5",
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

	clientObjectCRC = 55670244,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_energy_saver_battery_mk5, "object/tangible/ship/crafted/capacitor/shared_energy_saver_battery_mk5.iff")

object_tangible_ship_crafted_capacitor_shared_extended_life_battery_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_extended_life_battery_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:extended_life_battery_mk1",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:extended_life_battery_mk1",
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

	clientObjectCRC = 1281522685,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk3.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk2.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk1.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_extended_life_battery_mk1, "object/tangible/ship/crafted/capacitor/shared_extended_life_battery_mk1.iff")

object_tangible_ship_crafted_capacitor_shared_extended_life_battery_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_extended_life_battery_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:extended_life_battery_mk2",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:extended_life_battery_mk2",
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

	clientObjectCRC = 2541081450,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk3.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk2.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_extended_life_battery_mk2, "object/tangible/ship/crafted/capacitor/shared_extended_life_battery_mk2.iff")

object_tangible_ship_crafted_capacitor_shared_extended_life_battery_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_extended_life_battery_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:extended_life_battery_mk3",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:extended_life_battery_mk3",
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

	clientObjectCRC = 3732452583,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk3.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_extended_life_battery_mk3, "object/tangible/ship/crafted/capacitor/shared_extended_life_battery_mk3.iff")

object_tangible_ship_crafted_capacitor_shared_extended_life_battery_mk4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_extended_life_battery_mk4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:extended_life_battery_mk4",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:extended_life_battery_mk4",
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

	clientObjectCRC = 630956019,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_extended_life_battery_mk4, "object/tangible/ship/crafted/capacitor/shared_extended_life_battery_mk4.iff")

object_tangible_ship_crafted_capacitor_shared_extended_life_battery_mk5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_extended_life_battery_mk5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:extended_life_battery_mk5",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:extended_life_battery_mk5",
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

	clientObjectCRC = 1821833342,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_extended_life_battery_mk5, "object/tangible/ship/crafted/capacitor/shared_extended_life_battery_mk5.iff")

object_tangible_ship_crafted_capacitor_shared_heavy_battery_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_heavy_battery_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:heavy_battery_mk1",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:heavy_battery_mk1",
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

	clientObjectCRC = 1987626722,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk3.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk2.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk1.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_heavy_battery_mk1, "object/tangible/ship/crafted/capacitor/shared_heavy_battery_mk1.iff")

object_tangible_ship_crafted_capacitor_shared_heavy_battery_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_heavy_battery_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:heavy_battery_mk2",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:heavy_battery_mk2",
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

	clientObjectCRC = 2909761141,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk3.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk2.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_heavy_battery_mk2, "object/tangible/ship/crafted/capacitor/shared_heavy_battery_mk2.iff")

object_tangible_ship_crafted_capacitor_shared_heavy_battery_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_heavy_battery_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:heavy_battery_mk3",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:heavy_battery_mk3",
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

	clientObjectCRC = 3831630328,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk3.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_heavy_battery_mk3, "object/tangible/ship/crafted/capacitor/shared_heavy_battery_mk3.iff")

object_tangible_ship_crafted_capacitor_shared_heavy_battery_mk4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_heavy_battery_mk4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:heavy_battery_mk4",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:heavy_battery_mk4",
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

	clientObjectCRC = 528556780,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_heavy_battery_mk4, "object/tangible/ship/crafted/capacitor/shared_heavy_battery_mk4.iff")

object_tangible_ship_crafted_capacitor_shared_heavy_battery_mk5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_heavy_battery_mk5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:heavy_battery_mk5",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:heavy_battery_mk5",
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

	clientObjectCRC = 1452033377,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_heavy_battery_mk5, "object/tangible/ship/crafted/capacitor/shared_heavy_battery_mk5.iff")

object_tangible_ship_crafted_capacitor_shared_quick_recharge_battery_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_quick_recharge_battery_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:quick_recharge_battery_mk1",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:quick_recharge_battery_mk1",
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

	clientObjectCRC = 1831490574,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk3.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk2.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk1.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_quick_recharge_battery_mk1, "object/tangible/ship/crafted/capacitor/shared_quick_recharge_battery_mk1.iff")

object_tangible_ship_crafted_capacitor_shared_quick_recharge_battery_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_quick_recharge_battery_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:quick_recharge_battery_mk2",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:quick_recharge_battery_mk2",
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

	clientObjectCRC = 3057515673,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk3.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk2.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_quick_recharge_battery_mk2, "object/tangible/ship/crafted/capacitor/shared_quick_recharge_battery_mk2.iff")

object_tangible_ship_crafted_capacitor_shared_quick_recharge_battery_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_quick_recharge_battery_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:quick_recharge_battery_mk3",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:quick_recharge_battery_mk3",
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

	clientObjectCRC = 4281375508,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk3.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_quick_recharge_battery_mk3, "object/tangible/ship/crafted/capacitor/shared_quick_recharge_battery_mk3.iff")

object_tangible_ship_crafted_capacitor_shared_quick_recharge_battery_mk4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_quick_recharge_battery_mk4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:quick_recharge_battery_mk4",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:quick_recharge_battery_mk4",
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

	clientObjectCRC = 80982016,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk4.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_quick_recharge_battery_mk4, "object/tangible/ship/crafted/capacitor/shared_quick_recharge_battery_mk4.iff")

object_tangible_ship_crafted_capacitor_shared_quick_recharge_battery_mk5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_quick_recharge_battery_mk5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:quick_recharge_battery_mk5",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:quick_recharge_battery_mk5",
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

	clientObjectCRC = 1306449805,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent.iff", "object/tangible/ship/crafted/capacitor/shared_base_capacitor_subcomponent_mk5.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_quick_recharge_battery_mk5, "object/tangible/ship/crafted/capacitor/shared_quick_recharge_battery_mk5.iff")

object_tangible_ship_crafted_capacitor_shared_standard_capacitor_battery = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_standard_capacitor_battery.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:standard_capacitor_battery",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:standard_capacitor_battery",
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

	clientObjectCRC = 3218110775,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_standard_capacitor_battery, "object/tangible/ship/crafted/capacitor/shared_standard_capacitor_battery.iff")

object_tangible_ship_crafted_capacitor_shared_standard_recharge_module = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/capacitor/shared_standard_recharge_module.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_capacitor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741830,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:standard_recharge_module",

	gameObjectType = 1073741830,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:standard_recharge_module",
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

	clientObjectCRC = 4261874664,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_capacitor_shared_standard_recharge_module, "object/tangible/ship/crafted/capacitor/shared_standard_recharge_module.iff")
