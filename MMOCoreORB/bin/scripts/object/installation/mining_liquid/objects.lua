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


object_installation_mining_liquid_shared_mining_liquid_harvester_style_1 = SharedInstallationObjectTemplate:new {
	clientTemplateFileName = "object/installation/mining_liquid/shared_mining_liquid_harvester_style_1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ins_all_mobile_chem_refinery.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/installation/client_shared_mining_liquid_harvester_style_1.cdf",
	clientGameObjectType = 4099,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 4099,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@installation_n:liquid_mine",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/installation/mining_liquid/shared_mining_liquid_harvester_style_1.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2015682736,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/mining_liquid/base/shared_mining_liquid_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_installation_mining_liquid_shared_mining_liquid_harvester_style_1, "object/installation/mining_liquid/shared_mining_liquid_harvester_style_1.iff")

object_installation_mining_liquid_shared_mining_liquid_harvester_style_2 = SharedInstallationObjectTemplate:new {
	clientTemplateFileName = "object/installation/mining_liquid/shared_mining_liquid_harvester_style_2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ins_all_min_liquid_s01_u0.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/installation/client_shared_mining_liquid_harvester_style_2.cdf",
	clientGameObjectType = 4099,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 4099,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@installation_n:liquid_mine_medium",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/installation/mining_liquid/shared_mining_liquid_harvester_style_2.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2738047015,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/mining_liquid/base/shared_mining_liquid_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_installation_mining_liquid_shared_mining_liquid_harvester_style_2, "object/installation/mining_liquid/shared_mining_liquid_harvester_style_2.iff")

object_installation_mining_liquid_shared_mining_liquid_harvester_style_3 = SharedInstallationObjectTemplate:new {
	clientTemplateFileName = "object/installation/mining_liquid/shared_mining_liquid_harvester_style_3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ins_all_creature_farm_s01_u0.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/installation/client_shared_mining_organic_creature_farm.cdf",
	clientGameObjectType = 4099,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 4099,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@installation_n:liquid_mine_heavy",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/installation/mining_liquid/shared_mining_liquid_harvester_style_3.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3929943978,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/mining_liquid/base/shared_mining_liquid_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_installation_mining_liquid_shared_mining_liquid_harvester_style_3, "object/installation/mining_liquid/shared_mining_liquid_harvester_style_3.iff")

object_installation_mining_liquid_shared_mining_liquid_moisture_harvester = SharedInstallationObjectTemplate:new {
	clientTemplateFileName = "object/installation/mining_liquid/shared_mining_liquid_moisture_harvester.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ins_all_min_moisture_s01_u0.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/installation/client_shared_mining_moisture_harvester_style_1.cdf",
	clientGameObjectType = 4099,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 4099,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@installation_n:moisture_mine",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/installation/mining_liquid/shared_mining_liquid_moisture_harvester.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2235626870,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/mining_liquid/base/shared_mining_liquid_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_installation_mining_liquid_shared_mining_liquid_moisture_harvester, "object/installation/mining_liquid/shared_mining_liquid_moisture_harvester.iff")

object_installation_mining_liquid_shared_mining_liquid_moisture_harvester_heavy = SharedInstallationObjectTemplate:new {
	clientTemplateFileName = "object/installation/mining_liquid/shared_mining_liquid_moisture_harvester_heavy.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ins_all_moisture_lrg.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "",
	clientGameObjectType = 4099,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 4099,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@installation_n:moisture_mine_heavy",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/installation/mining_liquid/shared_mining_liquid_moisture_harvester_heavy.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1305511934,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/mining_liquid/base/shared_mining_liquid_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_installation_mining_liquid_shared_mining_liquid_moisture_harvester_heavy, "object/installation/mining_liquid/shared_mining_liquid_moisture_harvester_heavy.iff")

object_installation_mining_liquid_shared_mining_liquid_moisture_harvester_medium = SharedInstallationObjectTemplate:new {
	clientTemplateFileName = "object/installation/mining_liquid/shared_mining_liquid_moisture_harvester_medium.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ins_all_moisture_med.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "",
	clientGameObjectType = 4099,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 4099,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@installation_n:moisture_mine_medium",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/installation/mining_liquid/shared_mining_liquid_moisture_harvester_medium.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3152239258,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/mining_liquid/base/shared_mining_liquid_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_installation_mining_liquid_shared_mining_liquid_moisture_harvester_medium, "object/installation/mining_liquid/shared_mining_liquid_moisture_harvester_medium.iff")

object_installation_mining_liquid_shared_resource_harvester = SharedInstallationObjectTemplate:new {
	clientTemplateFileName = "object/installation/mining_liquid/shared_resource_harvester.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/tatt_ming_hydro_evaporator.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "",
	clientGameObjectType = 4096,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_n:default_craftable",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@string_table:Moisture Harvester",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/installation/base/shared_installation_base.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 860426391,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_installation_mining_liquid_shared_resource_harvester, "object/installation/mining_liquid/shared_resource_harvester.iff")
