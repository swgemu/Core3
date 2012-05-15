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


object_tangible_crafting_station_shared_armor_repair = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_armor_repair.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_repair_armor.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 32771,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:armor_repair_name",

	gameObjectType = 32771,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:armor_repair_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3769226262,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_repair.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_armor_repair, "object/tangible/crafting/station/shared_armor_repair.iff")

object_tangible_crafting_station_shared_clothing_repair = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_clothing_repair.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_repair_clothing_plain.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 32771,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:clothing_repair_name",

	gameObjectType = 32771,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:clothing_repair_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4032677980,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_repair.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_clothing_repair, "object/tangible/crafting/station/shared_clothing_repair.iff")

object_tangible_crafting_station_shared_clothing_station = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_clothing_station.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_clothing_mfg_station_m_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/installation/client_shared_manufacture_clothing_station.cdf",
	clientGameObjectType = 8198,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:clothing_station_name",

	gameObjectType = 8198,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:clothing_station_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/crafting_station.iff",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 737990049,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_station.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_clothing_station, "object/tangible/crafting/station/shared_clothing_station.iff")

object_tangible_crafting_station_shared_clothing_tool = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_clothing_tool.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_hairdressing_hair_dye_kit.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 32769,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:clothing_tool_name",

	gameObjectType = 32769,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:clothing_tool_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/crafting_tool.iff",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 753735496,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_tool.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_clothing_tool, "object/tangible/crafting/station/shared_clothing_tool.iff")

object_tangible_crafting_station_shared_droid_repair = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_droid_repair.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_repair_droids.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 32771,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:droid_repair_name",

	gameObjectType = 32771,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:droid_repair_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3945578306,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_repair.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_droid_repair, "object/tangible/crafting/station/shared_droid_repair.iff")

object_tangible_crafting_station_shared_food_station = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_food_station.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_food_mfg_station_m_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/installation/client_shared_manufacture_food_factory.cdf",
	clientGameObjectType = 8198,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:food_station_name",

	gameObjectType = 8198,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:food_station_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/crafting_station.iff",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3133859016,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_station.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_food_station, "object/tangible/crafting/station/shared_food_station.iff")

object_tangible_crafting_station_shared_food_tool = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_food_tool.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_cook_portable_stove_lg_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 32769,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:food_tool_name",

	gameObjectType = 32769,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:food_tool_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/crafting_tool.iff",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2849609519,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_tool.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_food_tool, "object/tangible/crafting/station/shared_food_tool.iff")

object_tangible_crafting_station_shared_generic_tool = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_generic_tool.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_computer_toolkit.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 32769,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:generic_tool_name",

	gameObjectType = 32769,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:generic_tool_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/crafting_tool.iff",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1055200365,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_tool.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_generic_tool, "object/tangible/crafting/station/shared_generic_tool.iff")

object_tangible_crafting_station_shared_jedi_tool = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_jedi_tool.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_lightsaber_crafting_kit.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 32769,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:jedi_tool_name",

	gameObjectType = 32769,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:jedi_tool_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/crafting_tool.iff",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 754074226,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_tool.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_jedi_tool, "object/tangible/crafting/station/shared_jedi_tool.iff")

object_tangible_crafting_station_shared_public_clothing_station = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_public_clothing_station.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_clothing_mfg_station_m_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/installation/client_shared_manufacture_clothing_station.cdf",
	clientGameObjectType = 8198,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:clothing_public_station_name",

	gameObjectType = 8198,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:clothing_public_station_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2936644592,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_public_station.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_public_clothing_station, "object/tangible/crafting/station/shared_public_clothing_station.iff")

object_tangible_crafting_station_shared_public_food_station = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_public_food_station.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_food_mfg_station_m_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/installation/client_shared_manufacture_food_factory.cdf",
	clientGameObjectType = 8198,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:food_public_station_name",

	gameObjectType = 8198,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:food_public_station_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 804779915,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_public_station.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_public_food_station, "object/tangible/crafting/station/shared_public_food_station.iff")

object_tangible_crafting_station_shared_public_space_station = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_public_space_station.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_starship_mfg_station_m_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8198,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:space_public_station_name",

	gameObjectType = 8198,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:space_station_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 395482180,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_public_station.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_public_space_station, "object/tangible/crafting/station/shared_public_space_station.iff")

object_tangible_crafting_station_shared_public_structure_station = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_public_structure_station.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_structure_mfg_station_m_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/installation/client_shared_manufacture_structure_factory.cdf",
	clientGameObjectType = 8198,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:structure_public_station_name",

	gameObjectType = 8198,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:structure_public_station_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 464244555,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_public_station.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_public_structure_station, "object/tangible/crafting/station/shared_public_structure_station.iff")

object_tangible_crafting_station_shared_public_weapon_station = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_public_weapon_station.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_weapon_weapon_mfg_station_m_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/installation/client_shared_manufacture_weapon_factory.cdf",
	clientGameObjectType = 8198,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:weapon_public_station_name",

	gameObjectType = 8198,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:weapon_public_station_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1920049130,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_public_station.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_public_weapon_station, "object/tangible/crafting/station/shared_public_weapon_station.iff")

object_tangible_crafting_station_shared_space_station = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_space_station.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_starship_mfg_station_m_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8198,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:space_station_name",

	gameObjectType = 8198,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:space_station_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/crafting_station.iff",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 408520625,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_station.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_space_station, "object/tangible/crafting/station/shared_space_station.iff")

object_tangible_crafting_station_shared_space_tool = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_space_tool.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_starship_toolkit.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 32769,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:space_tool_name",

	gameObjectType = 32769,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:space_tool_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/crafting_tool.iff",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2903391664,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_tool.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_space_tool, "object/tangible/crafting/station/shared_space_tool.iff")

object_tangible_crafting_station_shared_structure_repair = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_structure_repair.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_repair_installations.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 32771,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:structure_repair_name",

	gameObjectType = 32771,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:structure_repair_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1513899009,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_repair.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_structure_repair, "object/tangible/crafting/station/shared_structure_repair.iff")

object_tangible_crafting_station_shared_structure_station = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_structure_station.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_structure_mfg_station_m_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/installation/client_shared_manufacture_structure_factory.cdf",
	clientGameObjectType = 8198,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:structure_station_name",

	gameObjectType = 8198,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:structure_station_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/crafting_station.iff",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2496989305,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_station.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_structure_station, "object/tangible/crafting/station/shared_structure_station.iff")

object_tangible_crafting_station_shared_structure_tool = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_structure_tool.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_instrument_calibrator.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 32769,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:structure_tool_name",

	gameObjectType = 32769,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:structure_tool_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/crafting_tool.iff",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4275700789,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_tool.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_structure_tool, "object/tangible/crafting/station/shared_structure_tool.iff")

object_tangible_crafting_station_shared_weapon_repair = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_weapon_repair.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_repair_ranged_weapons_other.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 32771,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:weapon_repair_name",

	gameObjectType = 32771,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:weapon_repair_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2607871827,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_repair.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_weapon_repair, "object/tangible/crafting/station/shared_weapon_repair.iff")

object_tangible_crafting_station_shared_weapon_station = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_weapon_station.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_weapon_weapon_mfg_station_m_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/installation/client_shared_manufacture_weapon_factory.cdf",
	clientGameObjectType = 8198,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:weapon_station_name",

	gameObjectType = 8198,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:weapon_station_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/crafting_station.iff",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2167265111,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_station.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_weapon_station, "object/tangible/crafting/station/shared_weapon_station.iff")

object_tangible_crafting_station_shared_weapon_tool = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/crafting/station/shared_weapon_tool.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_weapon_repair_kit_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 32769,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@crafting_detail:weapon_tool_name",

	gameObjectType = 32769,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@crafting:weapon_tool_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/crafting_tool.iff",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1693896753,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/crafting/base/shared_base_tool.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_crafting_station_shared_weapon_tool, "object/tangible/crafting/station/shared_weapon_tool.iff")
