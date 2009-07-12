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


object_tangible_wearables_base_shared_armor_base = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_armor",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_armor",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_armor_base, 1118410205)

object_tangible_wearables_base_shared_base_back = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"back"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:cape_s01",

	gameObjectType = 16777233,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:cape_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_back, 2810806644)

object_tangible_wearables_base_shared_base_backpack = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"back"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 50,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:backpack_s01",

	gameObjectType = 8213,

	locationReservationRadius = 0,
	lookAtText = "@container_lookat:base_container",

	noBuildRadius = 0,

	objectName = "@wearables_name:backpack_s01",
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

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_backpack, 3185007320)

object_tangible_wearables_base_shared_base_bandolier = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"back"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bandolier_s01",

	gameObjectType = 16777217,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:bandolier_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_bandolier, 3970091966)

object_tangible_wearables_base_shared_base_belt = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"utility_belt"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:belt_s01",

	gameObjectType = 16777218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:belt_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_belt, 1062557489)

object_tangible_wearables_base_shared_base_bicep_both = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"bicep_l", "bicep_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_bicep_both",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_bicep_both",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_bicep_both, 2712137924)

object_tangible_wearables_base_shared_base_bicep_l = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"bicep_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_bicep_l",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_bicep_l",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_bicep_l, 4008734029)

object_tangible_wearables_base_shared_base_bicep_r = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"bicep_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_bicep_r",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_bicep_r",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_bicep_r, 2653235422)

object_tangible_wearables_base_shared_base_bracer_both = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"bracer_upper_l", "bracer_lower_l", "bracer_upper_r", "bracer_lower_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bracer_s01",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:bracer_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_bracer_both, 837302752)

object_tangible_wearables_base_shared_base_bracer_l = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"bracer_upper_l", "bracer_lower_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bracer_s01",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:bracer_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_bracer_l, 2708618999)

object_tangible_wearables_base_shared_base_bracer_r = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"bracer_upper_r", "bracer_lower_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bracer_s01",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:bracer_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_bracer_r, 3517414244)

object_tangible_wearables_base_shared_base_bracer_upper_both = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"bracer_upper_l", "bracer_upper_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bracer_s01",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:bracer_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_bracer_upper_both, 2675265298)

object_tangible_wearables_base_shared_base_bracer_upper_l = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"bracer_upper_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bracer_s01",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:bracer_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_bracer_upper_l, 4140306303)

object_tangible_wearables_base_shared_base_bracer_upper_r = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"bracer_upper_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bracer_s01",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:bracer_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_bracer_upper_r, 2250066668)

object_tangible_wearables_base_shared_base_cape = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest3_l", "chest3_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:cape_s01",

	gameObjectType = 16777220,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:cape_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_cape, 2484521886)

object_tangible_wearables_base_shared_base_cloak = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest2", "bicep_l", "bicep_r", "bracer_upper_l", "bracer_upper_r", "bracer_lower_l", "bracer_lower_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:cloak_s01",

	gameObjectType = 16777221,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:cloak_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_cloak, 2056216974)

object_tangible_wearables_base_shared_base_cloak_hooded = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest2", "bicep_l", "bicep_r", "bracer_upper_l", "bracer_upper_r", "bracer_lower_l", "bracer_lower_r", "hat"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:cloak_s01",

	gameObjectType = 16777221,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:cloak_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_cloak_hooded, 31223610)

object_tangible_wearables_base_shared_base_cloak_noback = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest2", "back", "bicep_l", "bicep_r", "bracer_upper_l", "bracer_upper_r", "bracer_lower_l", "bracer_lower_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:cloak_s01",

	gameObjectType = 16777221,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:cloak_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_cloak_noback, 2091266362)

object_tangible_wearables_base_shared_base_costume_allow_jewelry = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest1", "hat", "eyes", "mouth", "back", "chest2", "chest3_l", "chest3_r", "bicep_l", "bicep_r", "bracer_upper_l", "bracer_lower_l", "bracer_upper_r", "bracer_lower_r", "gloves", "gloves", "utility_belt", "pants1", "pants2", "shoes"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_costume",

	gameObjectType = 16777233,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_costume",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_costume_allow_jewelry, 2707266953)

object_tangible_wearables_base_shared_base_costume_full = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest1", "hat", "eyes", "earring_l", "earring_r", "mouth", "neck", "back", "chest2", "chest3_l", "chest3_r", "bicep_l", "bicep_r", "bracer_upper_l", "bracer_lower_l", "bracer_upper_r", "bracer_lower_r", "wrist_l", "wrist_r", "gloves", "gloves", "ring_l", "ring_r", "utility_belt", "pants1", "pants2", "shoes"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_costume",

	gameObjectType = 16777233,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_costume",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_costume_full, 2269371502)

object_tangible_wearables_base_shared_base_dress = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest1", "chest2", "pants1", "pants2"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:dress_s02",

	gameObjectType = 16777223,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:dress_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_dress, 2799882789)

object_tangible_wearables_base_shared_base_dress_formal = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest1", "chest2", "eyes", "mouth", "chest2", "chest3_l", "chest3_r", "bicep_l", "bicep_r", "bracer_upper_l", "bracer_upper_r", "utility_belt", "pants1", "pants2"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:dress_s02",

	gameObjectType = 16777223,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:dress_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_dress_formal, 3251571586)

object_tangible_wearables_base_shared_base_dress_formal_gloved = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest1", "chest2", "eyes", "mouth", "chest2", "chest3_l", "chest3_r", "bicep_l", "bicep_r", "bracer_upper_l", "bracer_upper_r", "bracer_lower_l", "bracer_lower_r", "gloves", "utility_belt", "pants1", "pants2"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:dress_s02",

	gameObjectType = 16777223,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:dress_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_dress_formal_gloved, 3497114818)

object_tangible_wearables_base_shared_base_dress_formal_hooded = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest1", "chest2", "hat", "eyes", "mouth", "chest2", "chest3_l", "chest3_r", "bicep_l", "bicep_r", "bracer_upper_l", "bracer_upper_r", "bracer_lower_l", "bracer_lower_r", "utility_belt", "pants1", "pants2"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:dress_s02",

	gameObjectType = 16777223,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:dress_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_dress_formal_hooded, 593250873)

object_tangible_wearables_base_shared_base_dress_poofysleeve_allow_gauntlets = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest1", "chest2", "pants1", "pants2", "bracer_upper_l", "bracer_lower_l", "bracer_upper_r", "bracer_lower_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:dress_s02",

	gameObjectType = 16777223,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:dress_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_dress_poofysleeve_allow_gauntlets, 4147701623)

object_tangible_wearables_base_shared_base_dress_poofysleeve_full = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest1", "chest2", "pants1", "pants2", "bicep_l", "bicep_r", "bracer_upper_l", "bracer_lower_l", "bracer_upper_r", "bracer_lower_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:dress_s02",

	gameObjectType = 16777223,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:dress_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_dress_poofysleeve_full, 470480709)

object_tangible_wearables_base_shared_base_dress_poofysleeve_lower = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest1", "chest2", "pants1", "pants2", "bracer_upper_l", "bracer_lower_l", "bracer_upper_r", "bracer_lower_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:dress_s02",

	gameObjectType = 16777223,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:dress_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_dress_poofysleeve_lower, 1881919920)

object_tangible_wearables_base_shared_base_dress_poofysleeve_upper = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest1", "chest2", "pants1", "pants2", "bicep_l", "bicep_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:dress_s02",

	gameObjectType = 16777223,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:dress_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_dress_poofysleeve_upper, 62461898)

object_tangible_wearables_base_shared_base_ear_both = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"earring_l", "earring_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s01",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_ear_both, 169169891)

object_tangible_wearables_base_shared_base_ear_either = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"earring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s01",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_ear_either, 1514339438)

object_tangible_wearables_base_shared_base_ear_l = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"earring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s01",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_ear_l, 4290100541)

object_tangible_wearables_base_shared_base_ear_r = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"earring_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s01",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_ear_r, 2405497006)

object_tangible_wearables_base_shared_base_eyes = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"eyes"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:eyewear_s01",

	gameObjectType = 16777225,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:eyewear_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_eyes, 749543557)

object_tangible_wearables_base_shared_base_gauntlets = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"gloves"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_gauntlets",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_gauntlets",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_gauntlets, 3961745252)

object_tangible_wearables_base_shared_base_gauntlets_long = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"gloves", "bracer_lower_l", "bracer_lower_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_gauntlets",

	gameObjectType = 16777233,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_gauntlets",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_gauntlets_long, 199720665)

object_tangible_wearables_base_shared_base_gloves = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"gloves"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:gloves_s01",

	gameObjectType = 16777224,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:gloves_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_gloves, 2864390584)

object_tangible_wearables_base_shared_base_gloves_long = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"gloves", "bracer_lower_l", "bracer_lower_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:gloves_s01",

	gameObjectType = 16777224,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:gloves_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_gloves_long, 1997625980)

object_tangible_wearables_base_shared_base_hat = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"hat"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:hat_s01",

	gameObjectType = 16777226,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:hat_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_hat, 2527263770)

object_tangible_wearables_base_shared_base_held_both = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"hold_r", "hold_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_held",

	gameObjectType = 16777233,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_held",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_held_both, 4046540417)

object_tangible_wearables_base_shared_base_held_l = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"hold_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_held",

	gameObjectType = 16777233,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_held",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_held_l, 3544049811)

object_tangible_wearables_base_shared_base_held_r = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"hold_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_held",

	gameObjectType = 16777233,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_held",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_held_r, 2749934848)

object_tangible_wearables_base_shared_base_helmet_closed_eyes = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"hat", "eyes"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:helmet_s01",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:helmet_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_helmet_closed_eyes, 2362107763)

object_tangible_wearables_base_shared_base_helmet_closed_full = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"hat", "eyes", "mouth"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:helmet_s01",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:helmet_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_helmet_closed_full, 3510435998)

object_tangible_wearables_base_shared_base_helmet_closed_full_ventilated = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"hat", "eyes", "mouth", "chest3_l", "chest3_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:helmet_s01",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:helmet_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_helmet_closed_full_ventilated, 2962747437)

object_tangible_wearables_base_shared_base_helmet_closed_mouth = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"hat", "mouth"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:helmet_s01",

	gameObjectType = 16777233,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:helmet_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_helmet_closed_mouth, 3128780769)

object_tangible_wearables_base_shared_base_helmet_open = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"hat"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:helmet_s01",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:helmet_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_helmet_open, 2025938864)

object_tangible_wearables_base_shared_base_jacket_halfsleeve = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest2", "bicep_l", "bicep_r", "bracer_upper_l", "bracer_upper_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:jacket_s02",

	gameObjectType = 16777227,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:jacket_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_jacket_halfsleeve, 2465585907)

object_tangible_wearables_base_shared_base_jacket_longsleeve = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest2", "bicep_l", "bicep_r", "bracer_upper_l", "bracer_upper_r", "bracer_lower_l", "bracer_lower_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:jacket_s02",

	gameObjectType = 16777227,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:jacket_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_jacket_longsleeve, 1586795263)

object_tangible_wearables_base_shared_base_jacket_shortsleeve = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest2", "bicep_l", "bicep_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:jacket_s02",

	gameObjectType = 16777227,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:jacket_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_jacket_shortsleeve, 1538565730)

object_tangible_wearables_base_shared_base_jewelry_set = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"neck", "earring_l", "earring_r", "ring_l", "ring_r", "wrist_l", "wrist_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_jewelry",

	gameObjectType = 16777233,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_jewelry",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_jewelry_set, 1811884613)

object_tangible_wearables_base_shared_base_jumpsuit = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest1", "pants1", "pants2"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_s01",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_jumpsuit, 3014962433)

object_tangible_wearables_base_shared_base_jumpsuit_gloved = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest1", "pants1", "pants2", "bicep_l", "bicep_r", "bracer_upper_r", "bracer_upper_l", "gloves"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_wearable",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_wearable",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_jumpsuit_gloved, 1949399047)

object_tangible_wearables_base_shared_base_jumpsuit_longsleeve = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest1", "pants1", "pants2", "bicep_l", "bicep_r", "bracer_upper_r", "bracer_upper_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_s01",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_jumpsuit_longsleeve, 2013984551)

object_tangible_wearables_base_shared_base_jumpsuit_shortsleeve = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest1", "pants1", "pants2", "bicep_l", "bicep_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_s01",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_jumpsuit_shortsleeve, 1198818608)

object_tangible_wearables_base_shared_base_mask_face = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"eyes", "mouth"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:mask_s01",

	gameObjectType = 16777233,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:mask_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_mask_face, 3305679722)

object_tangible_wearables_base_shared_base_mouth = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"mouth"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_mouth",

	gameObjectType = 16777233,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_mouth",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_mouth, 748013551)

object_tangible_wearables_base_shared_base_neck = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"neck"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_s01",

	gameObjectType = 16777233,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_neck, 551522086)

object_tangible_wearables_base_shared_base_pants = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"pants1"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:pants_s01",

	gameObjectType = 16777228,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:pants_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_pants, 3653526929)

object_tangible_wearables_base_shared_base_pauldron_both = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"bicep_l", "bicep_r", "chest3_l", "chest3_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_pauldrons",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_pauldrons",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_pauldron_both, 415713156)

object_tangible_wearables_base_shared_base_pauldron_l = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"bicep_l", "chest3_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_pauldron_r",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_pauldron_l",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_pauldron_l, 3883644082)

object_tangible_wearables_base_shared_base_pauldron_r = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"bicep_r", "chest3_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_pauldron_r",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_pauldron_r",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_pauldron_r, 2544824609)

object_tangible_wearables_base_shared_base_ring_both = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"ring_r", "ring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:ring_s01",

	gameObjectType = 2097153,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:ring_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_ring_both, 2610078742)

object_tangible_wearables_base_shared_base_ring_either = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"ring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:ring_s01",

	gameObjectType = 2097153,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:ring_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_ring_either, 2587414226)

object_tangible_wearables_base_shared_base_ring_l = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"ring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:ring_s01",

	gameObjectType = 2097153,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:ring_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_ring_l, 3286738453)

object_tangible_wearables_base_shared_base_ring_r = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"ring_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
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

	gameObjectType = 2097153,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_detail:ring_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_ring_r, 3006456710)

object_tangible_wearables_base_shared_base_robe_longsleeve = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest2", "chest3_l", "chest3_r", "bicep_l", "bicep_r", "bracer_upper_l", "bracer_upper_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_s01",

	gameObjectType = 16777229,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_robe_longsleeve, 3859006116)

object_tangible_wearables_base_shared_base_robe_longsleeve_hooded = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest2", "chest3_l", "chest3_r", "bicep_l", "bicep_r", "bracer_upper_l", "bracer_upper_r", "hat"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_s01",

	gameObjectType = 16777229,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_robe_longsleeve_hooded, 3926887891)

object_tangible_wearables_base_shared_base_robe_shortsleeve = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest2", "chest3_l", "chest3_r", "bicep_l", "bicep_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_s01",

	gameObjectType = 16777229,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_robe_shortsleeve, 1473420708)

object_tangible_wearables_base_shared_base_robe_shortsleeve_hooded = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest2", "chest3_l", "chest3_r", "bicep_l", "bicep_r", "hat"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_s01",

	gameObjectType = 16777229,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_robe_shortsleeve_hooded, 1105969450)

object_tangible_wearables_base_shared_base_shirt = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest1"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:shirt_s03",

	gameObjectType = 16777230,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:shirt_s03",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_shirt, 224364220)

object_tangible_wearables_base_shared_base_shirt_poofysleeve_full = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest1", "bicep_l", "bicep_r", "bracer_upper_l", "bracer_lower_l", "bracer_upper_r", "bracer_lower_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:shirt_s03",

	gameObjectType = 16777230,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:shirt_s03",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_shirt_poofysleeve_full, 3144684645)

object_tangible_wearables_base_shared_base_shirt_poofysleeve_lower = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest1", "bracer_upper_l", "bracer_lower_l", "bracer_upper_r", "bracer_lower_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:shirt_s03",

	gameObjectType = 16777230,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:shirt_s03",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_shirt_poofysleeve_lower, 3852531643)

object_tangible_wearables_base_shared_base_shirt_poofysleeve_upper = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest1", "bicep_l", "bicep_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:shirt_s03",

	gameObjectType = 16777230,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:shirt_s03",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_shirt_poofysleeve_upper, 2519871937)

object_tangible_wearables_base_shared_base_shoes = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"shoes"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:shoes_s01",

	gameObjectType = 16777222,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:shoes_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_shoes, 2786535462)

object_tangible_wearables_base_shared_base_skirt = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"pants1", "pants2"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:skirt_s03",

	gameObjectType = 16777234,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:skirt_s03",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_skirt, 3787318242)

object_tangible_wearables_base_shared_base_sleeve_both = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"bicep_l", "bicep_r", "bracer_upper_l", "bracer_upper_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_sleeves",

	gameObjectType = 16777233,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_sleeves",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_sleeve_both, 1904536543)

object_tangible_wearables_base_shared_base_sleeve_l = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"bicep_l", "bracer_upper_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_sleeve_l",

	gameObjectType = 16777233,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_sleeve_l",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_sleeve_l, 3578472162)

object_tangible_wearables_base_shared_base_sleeve_r = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"bicep_r", "bracer_upper_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_sleeve_r",

	gameObjectType = 16777233,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_sleeve_r",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_sleeve_r, 2778620785)

object_tangible_wearables_base_shared_base_vest = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"chest2"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:vest_s01",

	gameObjectType = 16777231,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:vest_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_vest, 3591511546)

object_tangible_wearables_base_shared_base_wrist_both = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"wrist_l", "wrist_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bracelet_s01",

	gameObjectType = 2097154,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:bracelet_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_wrist_both, 3301034284)

object_tangible_wearables_base_shared_base_wrist_either = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"wrist_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bracelet_s01",

	gameObjectType = 2097154,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:bracelet_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_wrist_either, 1850116475)

object_tangible_wearables_base_shared_base_wrist_l = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"wrist_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bracelet_s01",

	gameObjectType = 2097154,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:bracelet_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_wrist_l, 3290100944)

object_tangible_wearables_base_shared_base_wrist_r = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"wrist_r"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bracelet_s01",

	gameObjectType = 2097154,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:bracelet_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_base_wrist_r, 3033510211)

object_tangible_wearables_base_shared_wearables_base = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:default_wearable",

	gameObjectType = 16777233,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:default_wearable",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0
}

ObjectTemplates:addTemplate(object_tangible_wearables_base_shared_wearables_base, 3547164646)
