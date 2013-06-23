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


object_tangible_deed_harvester_deed_shared_harvester_creature_deed = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/deed/harvester_deed/shared_harvester_creature_deed.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_datapad.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8388610,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@deed_detail:creature_harvester_deed_name",

	gameObjectType = 8388610,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@deed:creature_harvester_deed_name",
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

	clientObjectCRC = 3801540743,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/deed/base/shared_deed_base.iff", "object/tangible/deed/base/shared_deed_installation_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_deed_harvester_deed_shared_harvester_creature_deed, "object/tangible/deed/harvester_deed/shared_harvester_creature_deed.iff")

object_tangible_deed_harvester_deed_shared_harvester_flora_deed = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/deed/harvester_deed/shared_harvester_flora_deed.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_datapad.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8388610,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@deed_detail:flora_harvester_deed_name",

	gameObjectType = 8388610,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@deed:flora_harvester_deed_name",
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

	clientObjectCRC = 2840949012,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/deed/base/shared_deed_base.iff", "object/tangible/deed/base/shared_deed_installation_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_deed_harvester_deed_shared_harvester_flora_deed, "object/tangible/deed/harvester_deed/shared_harvester_flora_deed.iff")

object_tangible_deed_harvester_deed_shared_harvester_flora_deed_heavy = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/deed/harvester_deed/shared_harvester_flora_deed_heavy.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_datapad.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8388610,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@deed_detail:flora_harvester_heavy_deed_name",

	gameObjectType = 8388610,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@deed:flora_harvester_heavy_deed_name",
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

	clientObjectCRC = 4005897011,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/deed/base/shared_deed_base.iff", "object/tangible/deed/base/shared_deed_installation_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_deed_harvester_deed_shared_harvester_flora_deed_heavy, "object/tangible/deed/harvester_deed/shared_harvester_flora_deed_heavy.iff")

object_tangible_deed_harvester_deed_shared_harvester_flora_deed_medium = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/deed/harvester_deed/shared_harvester_flora_deed_medium.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_datapad.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8388610,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@deed_detail:flora_harvester_medium_deed_name",

	gameObjectType = 8388610,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@deed:flora_harvester_medium_deed_name",
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

	clientObjectCRC = 1378608973,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/deed/base/shared_deed_base.iff", "object/tangible/deed/base/shared_deed_installation_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_deed_harvester_deed_shared_harvester_flora_deed_medium, "object/tangible/deed/harvester_deed/shared_harvester_flora_deed_medium.iff")

object_tangible_deed_harvester_deed_shared_harvester_gas_deed = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/deed/harvester_deed/shared_harvester_gas_deed.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_datapad.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8388610,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@deed_detail:gas_harvester_deed_name",

	gameObjectType = 8388610,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@deed:gas_harvester_deed_name",
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

	clientObjectCRC = 2231503385,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/deed/base/shared_deed_base.iff", "object/tangible/deed/base/shared_deed_installation_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_deed_harvester_deed_shared_harvester_gas_deed, "object/tangible/deed/harvester_deed/shared_harvester_gas_deed.iff")

object_tangible_deed_harvester_deed_shared_harvester_gas_deed_heavy = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/deed/harvester_deed/shared_harvester_gas_deed_heavy.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_datapad.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8388610,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@deed_detail:gas_harvester_heavy_deed_name",

	gameObjectType = 8388610,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@deed:gas_harvester_heavy_deed_name",
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

	clientObjectCRC = 277903692,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/deed/base/shared_deed_base.iff", "object/tangible/deed/base/shared_deed_installation_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_deed_harvester_deed_shared_harvester_gas_deed_heavy, "object/tangible/deed/harvester_deed/shared_harvester_gas_deed_heavy.iff")

object_tangible_deed_harvester_deed_shared_harvester_gas_deed_medium = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/deed/harvester_deed/shared_harvester_gas_deed_medium.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_datapad.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8388610,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@deed_detail:gas_harvester_medium_deed_name",

	gameObjectType = 8388610,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@deed:gas_harvester_medium_deed_name",
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

	clientObjectCRC = 2991048014,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/deed/base/shared_deed_base.iff", "object/tangible/deed/base/shared_deed_installation_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_deed_harvester_deed_shared_harvester_gas_deed_medium, "object/tangible/deed/harvester_deed/shared_harvester_gas_deed_medium.iff")

object_tangible_deed_harvester_deed_shared_harvester_liquid_deed = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/deed/harvester_deed/shared_harvester_liquid_deed.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_datapad.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8388610,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@deed_detail:liquid_harvester_deed_name",

	gameObjectType = 8388610,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@deed:liquid_harvester_deed_name",
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

	clientObjectCRC = 3335458434,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/deed/base/shared_deed_base.iff", "object/tangible/deed/base/shared_deed_installation_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_deed_harvester_deed_shared_harvester_liquid_deed, "object/tangible/deed/harvester_deed/shared_harvester_liquid_deed.iff")

object_tangible_deed_harvester_deed_shared_harvester_liquid_deed_heavy = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/deed/harvester_deed/shared_harvester_liquid_deed_heavy.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_datapad.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8388610,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@deed_detail:liquid_harvester_heavy_deed_name",

	gameObjectType = 8388610,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@deed:liquid_harvester_heavy_deed_name",
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

	clientObjectCRC = 1336331736,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/deed/base/shared_deed_base.iff", "object/tangible/deed/base/shared_deed_installation_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_deed_harvester_deed_shared_harvester_liquid_deed_heavy, "object/tangible/deed/harvester_deed/shared_harvester_liquid_deed_heavy.iff")

object_tangible_deed_harvester_deed_shared_harvester_liquid_deed_medium = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/deed/harvester_deed/shared_harvester_liquid_deed_medium.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_datapad.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8388610,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@deed_detail:liquid_harvester_medium_deed_name",

	gameObjectType = 8388610,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@deed:liquid_harvester_medium_deed_name",
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

	clientObjectCRC = 3291170804,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/deed/base/shared_deed_base.iff", "object/tangible/deed/base/shared_deed_installation_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_deed_harvester_deed_shared_harvester_liquid_deed_medium, "object/tangible/deed/harvester_deed/shared_harvester_liquid_deed_medium.iff")

object_tangible_deed_harvester_deed_shared_harvester_moisture_deed = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/deed/harvester_deed/shared_harvester_moisture_deed.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_datapad.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8388610,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@deed_detail:moisture_harvester_deed_name",

	gameObjectType = 8388610,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@deed:moisture_harvester_deed_name",
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

	clientObjectCRC = 1578846375,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/deed/base/shared_deed_base.iff", "object/tangible/deed/base/shared_deed_installation_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_deed_harvester_deed_shared_harvester_moisture_deed, "object/tangible/deed/harvester_deed/shared_harvester_moisture_deed.iff")

object_tangible_deed_harvester_deed_shared_harvester_moisture_deed_heavy = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/deed/harvester_deed/shared_harvester_moisture_deed_heavy.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_datapad.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8388610,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@deed_detail:moisture_harvester_heavy_deed_name",

	gameObjectType = 8388610,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@deed:moisture_harvester_heavy_deed_name",
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

	clientObjectCRC = 21472355,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/deed/base/shared_deed_base.iff", "object/tangible/deed/base/shared_deed_installation_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_deed_harvester_deed_shared_harvester_moisture_deed_heavy, "object/tangible/deed/harvester_deed/shared_harvester_moisture_deed_heavy.iff")

object_tangible_deed_harvester_deed_shared_harvester_moisture_deed_medium = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/deed/harvester_deed/shared_harvester_moisture_deed_medium.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_datapad.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8388610,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@deed_detail:moisture_harvester_medium_deed_name",

	gameObjectType = 8388610,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@deed:moisture_harvester_medium_deed_name",
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

	clientObjectCRC = 759835785,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/deed/base/shared_deed_base.iff", "object/tangible/deed/base/shared_deed_installation_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_deed_harvester_deed_shared_harvester_moisture_deed_medium, "object/tangible/deed/harvester_deed/shared_harvester_moisture_deed_medium.iff")

object_tangible_deed_harvester_deed_shared_harvester_ore_heavy_deed = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/deed/harvester_deed/shared_harvester_ore_heavy_deed.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_datapad.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8388610,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@deed_detail:ore_heavy_harvester_deed_name",

	gameObjectType = 8388610,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@deed:ore_heavy_harvester_deed_name",
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

	clientObjectCRC = 3224287923,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/deed/base/shared_deed_base.iff", "object/tangible/deed/base/shared_deed_installation_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_deed_harvester_deed_shared_harvester_ore_heavy_deed, "object/tangible/deed/harvester_deed/shared_harvester_ore_heavy_deed.iff")

object_tangible_deed_harvester_deed_shared_harvester_ore_s1_deed = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/deed/harvester_deed/shared_harvester_ore_s1_deed.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_datapad.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8388610,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@deed_detail:ore_s1_harvester_deed_name",

	gameObjectType = 8388610,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@deed:ore_s1_harvester_deed_name",
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

	clientObjectCRC = 2126009375,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/deed/base/shared_deed_base.iff", "object/tangible/deed/base/shared_deed_installation_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_deed_harvester_deed_shared_harvester_ore_s1_deed, "object/tangible/deed/harvester_deed/shared_harvester_ore_s1_deed.iff")

object_tangible_deed_harvester_deed_shared_harvester_ore_s2_deed = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/deed/harvester_deed/shared_harvester_ore_s2_deed.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_tool_datapad.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8388610,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@deed_detail:ore_s2_harvester_deed_name",

	gameObjectType = 8388610,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@deed:ore_s2_harvester_deed_name",
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

	clientObjectCRC = 4224231681,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/deed/base/shared_deed_base.iff", "object/tangible/deed/base/shared_deed_installation_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_deed_harvester_deed_shared_harvester_ore_s2_deed, "object/tangible/deed/harvester_deed/shared_harvester_ore_s2_deed.iff")
