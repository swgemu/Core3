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


object_tangible_ship_crafted_booster_shared_base_booster = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_base_booster.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/xwing_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@base_booster:base",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@base_booster:s01",
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

	clientObjectCRC = 1020427901,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_base_booster, "object/tangible/ship/crafted/booster/shared_base_booster.iff")

object_tangible_ship_crafted_booster_shared_base_booster_subcomponent = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_booster_subcomponent",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_booster_subcomponent",
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

	clientObjectCRC = 1262367016,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_base_booster_subcomponent, "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff")

object_tangible_ship_crafted_booster_shared_base_booster_subcomponent_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_booster_subcomponent_mk1",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_booster_subcomponent_mk1",
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

	clientObjectCRC = 1571131488,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk3.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk2.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_base_booster_subcomponent_mk1, "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk1.iff")

object_tangible_ship_crafted_booster_shared_base_booster_subcomponent_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_booster_subcomponent_mk2",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_booster_subcomponent_mk2",
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

	clientObjectCRC = 2259826935,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk3.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_base_booster_subcomponent_mk2, "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk2.iff")

object_tangible_ship_crafted_booster_shared_base_booster_subcomponent_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_booster_subcomponent_mk3",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_booster_subcomponent_mk3",
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

	clientObjectCRC = 3485425530,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_base_booster_subcomponent_mk3, "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk3.iff")

object_tangible_ship_crafted_booster_shared_base_booster_subcomponent_mk4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_booster_subcomponent_mk4",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_booster_subcomponent_mk4",
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

	clientObjectCRC = 878474350,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_base_booster_subcomponent_mk4, "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff")

object_tangible_ship_crafted_booster_shared_base_booster_subcomponent_mk5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:base_booster_subcomponent_mk5",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_booster_subcomponent_mk5",
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

	clientObjectCRC = 2102465507,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_base_booster_subcomponent_mk5, "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff")

object_tangible_ship_crafted_booster_shared_basic_booster = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_basic_booster.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/xwing_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_n:base_booster",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_booster",
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

	clientObjectCRC = 4241371436,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_basic_booster, "object/tangible/ship/crafted/booster/shared_basic_booster.iff")

object_tangible_ship_crafted_booster_shared_booster_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_booster_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:booster_mk1",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:booster_mk1",
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

	clientObjectCRC = 1453813442,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_booster_mk1, "object/tangible/ship/crafted/booster/shared_booster_mk1.iff")

object_tangible_ship_crafted_booster_shared_booster_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_booster_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:booster_mk2",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:booster_mk2",
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

	clientObjectCRC = 2377172565,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_booster_mk2, "object/tangible/ship/crafted/booster/shared_booster_mk2.iff")

object_tangible_ship_crafted_booster_shared_booster_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_booster_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:booster_mk3",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:booster_mk3",
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

	clientObjectCRC = 3300762072,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_booster_mk3, "object/tangible/ship/crafted/booster/shared_booster_mk3.iff")

object_tangible_ship_crafted_booster_shared_booster_mk4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_booster_mk4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:booster_mk4",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:booster_mk4",
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

	clientObjectCRC = 1063160524,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_booster_mk4, "object/tangible/ship/crafted/booster/shared_booster_mk4.iff")

object_tangible_ship_crafted_booster_shared_booster_mk5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_booster_mk5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:booster_mk5",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:booster_mk5",
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

	clientObjectCRC = 1985211713,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_booster_mk5, "object/tangible/ship/crafted/booster/shared_booster_mk5.iff")

object_tangible_ship_crafted_booster_shared_booster_overdriver_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_booster_overdriver_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:booster_overdriver_mk1",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:booster_overdriver_mk1",
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

	clientObjectCRC = 364252825,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk3.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk2.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk1.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_booster_overdriver_mk1, "object/tangible/ship/crafted/booster/shared_booster_overdriver_mk1.iff")

object_tangible_ship_crafted_booster_shared_booster_overdriver_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_booster_overdriver_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:booster_overdriver_mk2",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:booster_overdriver_mk2",
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

	clientObjectCRC = 3466700302,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk3.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk2.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_booster_overdriver_mk2, "object/tangible/ship/crafted/booster/shared_booster_overdriver_mk2.iff")

object_tangible_ship_crafted_booster_shared_booster_overdriver_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_booster_overdriver_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:booster_overdriver_mk3",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:booster_overdriver_mk3",
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

	clientObjectCRC = 2276245891,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk3.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_booster_overdriver_mk3, "object/tangible/ship/crafted/booster/shared_booster_overdriver_mk3.iff")

object_tangible_ship_crafted_booster_shared_booster_overdriver_mk4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_booster_overdriver_mk4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:booster_overdriver_mk4",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:booster_overdriver_mk4",
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

	clientObjectCRC = 2085612183,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_booster_overdriver_mk4, "object/tangible/ship/crafted/booster/shared_booster_overdriver_mk4.iff")

object_tangible_ship_crafted_booster_shared_booster_overdriver_mk5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_booster_overdriver_mk5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:booster_overdriver_mk5",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:booster_overdriver_mk5",
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

	clientObjectCRC = 893553946,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_booster_overdriver_mk5, "object/tangible/ship/crafted/booster/shared_booster_overdriver_mk5.iff")

object_tangible_ship_crafted_booster_shared_extended_life_fuel_cell_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_extended_life_fuel_cell_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:extended_life_fuel_cell_mk1",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:extended_life_fuel_cell_mk1",
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

	clientObjectCRC = 675357004,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk3.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk2.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk1.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_extended_life_fuel_cell_mk1, "object/tangible/ship/crafted/booster/shared_extended_life_fuel_cell_mk1.iff")

object_tangible_ship_crafted_booster_shared_extended_life_fuel_cell_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_extended_life_fuel_cell_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:extended_life_fuel_cell_mk2",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:extended_life_fuel_cell_mk2",
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

	clientObjectCRC = 4082534875,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk3.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk2.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_extended_life_fuel_cell_mk2, "object/tangible/ship/crafted/booster/shared_extended_life_fuel_cell_mk2.iff")

object_tangible_ship_crafted_booster_shared_extended_life_fuel_cell_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_extended_life_fuel_cell_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:extended_life_fuel_cell_mk3",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:extended_life_fuel_cell_mk3",
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

	clientObjectCRC = 3126586966,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk3.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_extended_life_fuel_cell_mk3, "object/tangible/ship/crafted/booster/shared_extended_life_fuel_cell_mk3.iff")

object_tangible_ship_crafted_booster_shared_extended_life_fuel_cell_mk4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_extended_life_fuel_cell_mk4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:extended_life_fuel_cell_mk4",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:extended_life_fuel_cell_mk4",
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

	clientObjectCRC = 1102628162,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_extended_life_fuel_cell_mk4, "object/tangible/ship/crafted/booster/shared_extended_life_fuel_cell_mk4.iff")

object_tangible_ship_crafted_booster_shared_extended_life_fuel_cell_mk5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_extended_life_fuel_cell_mk5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:extended_life_fuel_cell_mk5",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:extended_life_fuel_cell_mk5",
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

	clientObjectCRC = 146121423,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_extended_life_fuel_cell_mk5, "object/tangible/ship/crafted/booster/shared_extended_life_fuel_cell_mk5.iff")

object_tangible_ship_crafted_booster_shared_fast_charge_fuel_cell_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_fast_charge_fuel_cell_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:fast_charge_fuel_cell_mk1",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:fast_charge_fuel_cell_mk1",
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

	clientObjectCRC = 943059743,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk3.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk2.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk1.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_fast_charge_fuel_cell_mk1, "object/tangible/ship/crafted/booster/shared_fast_charge_fuel_cell_mk1.iff")

object_tangible_ship_crafted_booster_shared_fast_charge_fuel_cell_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_fast_charge_fuel_cell_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:fast_charge_fuel_cell_mk2",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:fast_charge_fuel_cell_mk2",
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

	clientObjectCRC = 3810679688,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk3.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk2.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_fast_charge_fuel_cell_mk2, "object/tangible/ship/crafted/booster/shared_fast_charge_fuel_cell_mk2.iff")

object_tangible_ship_crafted_booster_shared_fast_charge_fuel_cell_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_fast_charge_fuel_cell_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:fast_charge_fuel_cell_mk3",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:fast_charge_fuel_cell_mk3",
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

	clientObjectCRC = 2855222277,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk3.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_fast_charge_fuel_cell_mk3, "object/tangible/ship/crafted/booster/shared_fast_charge_fuel_cell_mk3.iff")

object_tangible_ship_crafted_booster_shared_fast_charge_fuel_cell_mk4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_fast_charge_fuel_cell_mk4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:fast_charge_fuel_cell_mk4",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:fast_charge_fuel_cell_mk4",
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

	clientObjectCRC = 1372329745,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_fast_charge_fuel_cell_mk4, "object/tangible/ship/crafted/booster/shared_fast_charge_fuel_cell_mk4.iff")

object_tangible_ship_crafted_booster_shared_fast_charge_fuel_cell_mk5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_fast_charge_fuel_cell_mk5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:fast_charge_fuel_cell_mk5",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:fast_charge_fuel_cell_mk5",
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

	clientObjectCRC = 415330460,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_fast_charge_fuel_cell_mk5, "object/tangible/ship/crafted/booster/shared_fast_charge_fuel_cell_mk5.iff")

object_tangible_ship_crafted_booster_shared_heavy_fuel_cell_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_heavy_fuel_cell_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:heavy_fuel_cell_mk1",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:heavy_fuel_cell_mk1",
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

	clientObjectCRC = 771601122,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk3.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk2.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk1.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_heavy_fuel_cell_mk1, "object/tangible/ship/crafted/booster/shared_heavy_fuel_cell_mk1.iff")

object_tangible_ship_crafted_booster_shared_heavy_fuel_cell_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_heavy_fuel_cell_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:heavy_fuel_cell_mk2",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:heavy_fuel_cell_mk2",
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

	clientObjectCRC = 4142537333,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk3.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk2.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_heavy_fuel_cell_mk2, "object/tangible/ship/crafted/booster/shared_heavy_fuel_cell_mk2.iff")

object_tangible_ship_crafted_booster_shared_heavy_fuel_cell_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_heavy_fuel_cell_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:heavy_fuel_cell_mk3",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:heavy_fuel_cell_mk3",
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

	clientObjectCRC = 3219619320,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk3.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_heavy_fuel_cell_mk3, "object/tangible/ship/crafted/booster/shared_heavy_fuel_cell_mk3.iff")

object_tangible_ship_crafted_booster_shared_heavy_fuel_cell_mk4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_heavy_fuel_cell_mk4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:heavy_fuel_cell_mk4",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:heavy_fuel_cell_mk4",
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

	clientObjectCRC = 1141135084,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk4.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_heavy_fuel_cell_mk4, "object/tangible/ship/crafted/booster/shared_heavy_fuel_cell_mk4.iff")

object_tangible_ship_crafted_booster_shared_heavy_fuel_cell_mk5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_heavy_fuel_cell_mk5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:heavy_fuel_cell_mk5",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:heavy_fuel_cell_mk5",
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

	clientObjectCRC = 218706273,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_subcomponent_base.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent.iff", "object/tangible/ship/crafted/booster/shared_base_booster_subcomponent_mk5.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_heavy_fuel_cell_mk5, "object/tangible/ship/crafted/booster/shared_heavy_fuel_cell_mk5.iff")

object_tangible_ship_crafted_booster_shared_xwing_booster_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_xwing_booster_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/xwing_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:xwing_booster_1",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:xwing_booster_1",
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

	clientObjectCRC = 1203730256,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_xwing_booster_mk1, "object/tangible/ship/crafted/booster/shared_xwing_booster_mk1.iff")

object_tangible_ship_crafted_booster_shared_xwing_booster_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/crafted/booster/shared_xwing_booster_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/xwing_booster_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_crafting_d:xwing_booster_2",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:xwing_booster_2",
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

	clientObjectCRC = 2628313031,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_booster_shared_xwing_booster_mk2, "object/tangible/ship/crafted/booster/shared_xwing_booster_mk2.iff")
