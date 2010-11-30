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


object_building_poi_shared_anywhere_fs_intro_camp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2150026524
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_anywhere_fs_intro_camp, "object/building/poi/shared_anywhere_fs_intro_camp.iff")

object_building_poi_shared_anywhere_imperial_base_large_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_anywhere_imperial_base_large_1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3181956427
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_anywhere_imperial_base_large_1, "object/building/poi/shared_anywhere_imperial_base_large_1.iff")

object_building_poi_shared_anywhere_imperial_base_small_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_anywhere_imperial_base_small_1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 990728646
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_anywhere_imperial_base_small_1, "object/building/poi/shared_anywhere_imperial_base_small_1.iff")

object_building_poi_shared_anywhere_misc_camp_small_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_anywhere_misc_camp_small_1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2012164314
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_anywhere_misc_camp_small_1, "object/building/poi/shared_anywhere_misc_camp_small_1.iff")

object_building_poi_shared_anywhere_rebel_base_large_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_anywhere_rebel_base_large_1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1530380993
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_anywhere_rebel_base_large_1, "object/building/poi/shared_anywhere_rebel_base_large_1.iff")

object_building_poi_shared_anywhere_rebel_camp_large_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_anywhere_rebel_camp_large_1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1267268082
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_anywhere_rebel_camp_large_1, "object/building/poi/shared_anywhere_rebel_camp_large_1.iff")

object_building_poi_shared_anywhere_rebel_camp_small_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_anywhere_rebel_camp_small_1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3442304383
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_anywhere_rebel_camp_small_1, "object/building/poi/shared_anywhere_rebel_camp_small_1.iff")

object_building_poi_shared_anywhere_rebel_camp_small_2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_anywhere_rebel_camp_small_2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 372952552
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_anywhere_rebel_camp_small_2, "object/building/poi/shared_anywhere_rebel_camp_small_2.iff")

object_building_poi_shared_anywhere_rebel_camp_small_3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_anywhere_rebel_camp_small_3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1597483621
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_anywhere_rebel_camp_small_3, "object/building/poi/shared_anywhere_rebel_camp_small_3.iff")

object_building_poi_shared_anywhere_uberlair_imperial_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_anywhere_uberlair_imperial_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 833924651
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_anywhere_uberlair_imperial_01, "object/building/poi/shared_anywhere_uberlair_imperial_01.iff")

object_building_poi_shared_corellia_afarathu_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_afarathu_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2141413884
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_afarathu_large1, "object/building/poi/shared_corellia_afarathu_large1.iff")

object_building_poi_shared_corellia_afarathu_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_afarathu_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2763311467
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_afarathu_large2, "object/building/poi/shared_corellia_afarathu_large2.iff")

object_building_poi_shared_corellia_afarathu_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_afarathu_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3988369126
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_afarathu_large3, "object/building/poi/shared_corellia_afarathu_large3.iff")

object_building_poi_shared_corellia_afarathu_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_afarathu_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2880031369
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_afarathu_medium2, "object/building/poi/shared_corellia_afarathu_medium2.iff")

object_building_poi_shared_corellia_afarathu_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_afarathu_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2734773168
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_afarathu_small1, "object/building/poi/shared_corellia_afarathu_small1.iff")

object_building_poi_shared_corellia_afarathu_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_afarathu_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2014772007
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_afarathu_small2, "object/building/poi/shared_corellia_afarathu_small2.iff")

object_building_poi_shared_corellia_afarathu_small3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_afarathu_small3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 823893162
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_afarathu_small3, "object/building/poi/shared_corellia_afarathu_small3.iff")

object_building_poi_shared_corellia_beldonna_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_beldonna_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4189497836
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_beldonna_large1, "object/building/poi/shared_corellia_beldonna_large1.iff")

object_building_poi_shared_corellia_beldonna_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_beldonna_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 580977019
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_beldonna_large2, "object/building/poi/shared_corellia_beldonna_large2.iff")

object_building_poi_shared_corellia_beldonna_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_beldonna_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1806460662
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_beldonna_large3, "object/building/poi/shared_corellia_beldonna_large3.iff")

object_building_poi_shared_corellia_corellia_times_investigator_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_corellia_times_investigator_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3495558430
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_corellia_times_investigator_large1, "object/building/poi/shared_corellia_corellia_times_investigator_large1.iff")

object_building_poi_shared_corellia_corellia_times_investigator_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_corellia_times_investigator_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 189683081
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_corellia_times_investigator_large2, "object/building/poi/shared_corellia_corellia_times_investigator_large2.iff")

object_building_poi_shared_corellia_corellia_times_investigators_camp_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_corellia_times_investigators_camp_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3864145072
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_corellia_times_investigators_camp_small1, "object/building/poi/shared_corellia_corellia_times_investigators_camp_small1.iff")

object_building_poi_shared_corellia_corellia_times_investigators_camp_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_corellia_times_investigators_camp_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1027965991
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_corellia_times_investigators_camp_small2, "object/building/poi/shared_corellia_corellia_times_investigators_camp_small2.iff")

object_building_poi_shared_corellia_corsec_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_corsec_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2110974936
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_corsec_large1, "object/building/poi/shared_corellia_corsec_large1.iff")

object_building_poi_shared_corellia_corsec_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_corsec_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2797945679
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_corsec_large2, "object/building/poi/shared_corellia_corsec_large2.iff")

object_building_poi_shared_corellia_corsec_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_corsec_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4022871234
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_corsec_large3, "object/building/poi/shared_corellia_corsec_large3.iff")

object_building_poi_shared_corellia_drall_abbot_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_drall_abbot_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1754860044
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_drall_abbot_large1, "object/building/poi/shared_corellia_drall_abbot_large1.iff")

object_building_poi_shared_corellia_drall_abbot_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_drall_abbot_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3012469403
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_drall_abbot_large2, "object/building/poi/shared_corellia_drall_abbot_large2.iff")

object_building_poi_shared_corellia_drall_abbot_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_drall_abbot_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4202939670
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_drall_abbot_large3, "object/building/poi/shared_corellia_drall_abbot_large3.iff")

object_building_poi_shared_corellia_drall_abbot_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_drall_abbot_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3281302012
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_drall_abbot_medium2, "object/building/poi/shared_corellia_drall_abbot_medium2.iff")

object_building_poi_shared_corellia_drall_abbot_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_drall_abbot_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3023779904
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_drall_abbot_small1, "object/building/poi/shared_corellia_drall_abbot_small1.iff")

object_building_poi_shared_corellia_drall_abbot_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_drall_abbot_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1865191639
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_drall_abbot_small2, "object/building/poi/shared_corellia_drall_abbot_small2.iff")

object_building_poi_shared_corellia_drall_abbots_camp_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_drall_abbots_camp_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 657822368
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_drall_abbots_camp_small1, "object/building/poi/shared_corellia_drall_abbots_camp_small1.iff")

object_building_poi_shared_corellia_drall_patriot_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_drall_patriot_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2646384537
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_drall_patriot_large1, "object/building/poi/shared_corellia_drall_patriot_large1.iff")

object_building_poi_shared_corellia_drall_patriot_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_drall_patriot_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1185625870
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_drall_patriot_large2, "object/building/poi/shared_corellia_drall_patriot_large2.iff")

object_building_poi_shared_corellia_drall_patriot_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_drall_patriot_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 262557827
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_drall_patriot_large3, "object/building/poi/shared_corellia_drall_patriot_large3.iff")

object_building_poi_shared_corellia_drall_patriot_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_drall_patriot_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2021438110
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_drall_patriot_medium2, "object/building/poi/shared_corellia_drall_patriot_medium2.iff")

object_building_poi_shared_corellia_drall_patriot_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_drall_patriot_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1092529621
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_drall_patriot_small1, "object/building/poi/shared_corellia_drall_patriot_small1.iff")

object_building_poi_shared_corellia_drall_patriot_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_drall_patriot_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2584282434
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_drall_patriot_small2, "object/building/poi/shared_corellia_drall_patriot_small2.iff")

object_building_poi_shared_corellia_flail_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_flail_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4128797230
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_flail_large1, "object/building/poi/shared_corellia_flail_large1.iff")

object_building_poi_shared_corellia_flail_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_flail_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 756013753
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_flail_large2, "object/building/poi/shared_corellia_flail_large2.iff")

object_building_poi_shared_corellia_greck_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_greck_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2415245494
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_greck_large1, "object/building/poi/shared_corellia_greck_large1.iff")

object_building_poi_shared_corellia_greck_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_greck_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1424101409
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_greck_large2, "object/building/poi/shared_corellia_greck_large2.iff")

object_building_poi_shared_corellia_hidden_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_hidden_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2767898088
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_hidden_large1, "object/building/poi/shared_corellia_hidden_large1.iff")

object_building_poi_shared_corellia_hidden_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_hidden_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2146266495
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_hidden_large2, "object/building/poi/shared_corellia_hidden_large2.iff")

object_building_poi_shared_corellia_meatlump_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_meatlump_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 804219570
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_meatlump_large1, "object/building/poi/shared_corellia_meatlump_large1.iff")

object_building_poi_shared_corellia_meatlump_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_meatlump_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4109943333
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_meatlump_large2, "object/building/poi/shared_corellia_meatlump_large2.iff")

object_building_poi_shared_corellia_meatlump_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_meatlump_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3186992552
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_meatlump_large3, "object/building/poi/shared_corellia_meatlump_large3.iff")

object_building_poi_shared_corellia_meatlump_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_meatlump_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4081932542
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_meatlump_small1, "object/building/poi/shared_corellia_meatlump_small1.iff")

object_building_poi_shared_corellia_meatlump_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_meatlump_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 677048425
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_meatlump_small2, "object/building/poi/shared_corellia_meatlump_small2.iff")

object_building_poi_shared_corellia_meatlump_small3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_meatlump_small3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1633130468
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_meatlump_small3, "object/building/poi/shared_corellia_meatlump_small3.iff")

object_building_poi_shared_corellia_monumenter_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_monumenter_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1922341284
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_monumenter_large1, "object/building/poi/shared_corellia_monumenter_large1.iff")

object_building_poi_shared_corellia_monumenter_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_monumenter_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2843947315
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_monumenter_large2, "object/building/poi/shared_corellia_monumenter_large2.iff")

object_building_poi_shared_corellia_monumenter_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_monumenter_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3767424702
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_monumenter_large3, "object/building/poi/shared_corellia_monumenter_large3.iff")

object_building_poi_shared_corellia_nyax_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_nyax_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1203547217
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_nyax_large1, "object/building/poi/shared_corellia_nyax_large1.iff")

object_building_poi_shared_corellia_nyax_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_nyax_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2628453574
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_nyax_large2, "object/building/poi/shared_corellia_nyax_large2.iff")

object_building_poi_shared_corellia_nyax_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_nyax_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3584451403
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_nyax_large3, "object/building/poi/shared_corellia_nyax_large3.iff")

object_building_poi_shared_corellia_selonian_rebel_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_selonian_rebel_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3652494141
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_selonian_rebel_large1, "object/building/poi/shared_corellia_selonian_rebel_large1.iff")

object_building_poi_shared_corellia_selonian_rebel_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_selonian_rebel_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 44239786
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_selonian_rebel_large2, "object/building/poi/shared_corellia_selonian_rebel_large2.iff")

object_building_poi_shared_corellia_selonian_rebel_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_selonian_rebel_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 85365105
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_selonian_rebel_small1, "object/building/poi/shared_corellia_selonian_rebel_small1.iff")

object_building_poi_shared_corellia_selonian_rebel_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_selonian_rebel_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3724622310
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_selonian_rebel_small2, "object/building/poi/shared_corellia_selonian_rebel_small2.iff")

object_building_poi_shared_corellia_selonian_rebel_small3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_selonian_rebel_small3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2534170219
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_selonian_rebel_small3, "object/building/poi/shared_corellia_selonian_rebel_small3.iff")

object_building_poi_shared_corellia_selonian_separatists_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_selonian_separatists_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1047558952
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_selonian_separatists_large1, "object/building/poi/shared_corellia_selonian_separatists_large1.iff")

object_building_poi_shared_corellia_selonian_separatists_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_selonian_separatists_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3848786879
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_selonian_separatists_large2, "object/building/poi/shared_corellia_selonian_separatists_large2.iff")

object_building_poi_shared_corellia_selonian_separatists_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_selonian_separatists_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3805432164
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_selonian_separatists_small1, "object/building/poi/shared_corellia_selonian_separatists_small1.iff")

object_building_poi_shared_corellia_selonian_separatists_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_selonian_separatists_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 969269747
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_selonian_separatists_small2, "object/building/poi/shared_corellia_selonian_separatists_small2.iff")

object_building_poi_shared_corellia_smashball_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_smashball_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 23761660
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_smashball_large1, "object/building/poi/shared_corellia_smashball_large1.iff")

object_building_poi_shared_corellia_smashball_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_smashball_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3665640043
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_smashball_large2, "object/building/poi/shared_corellia_smashball_large2.iff")

object_building_poi_shared_corellia_smashball_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_smashball_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2473614822
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_smashball_large3, "object/building/poi/shared_corellia_smashball_large3.iff")

object_building_poi_shared_corellia_smashball_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_smashball_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3720913072
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_smashball_small1, "object/building/poi/shared_corellia_smashball_small1.iff")

object_building_poi_shared_corellia_smashball_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_smashball_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 115279911
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_smashball_small2, "object/building/poi/shared_corellia_smashball_small2.iff")

object_building_poi_shared_corellia_solitude_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_solitude_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3611608872
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_solitude_large1, "object/building/poi/shared_corellia_solitude_large1.iff")

object_building_poi_shared_corellia_solitude_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_solitude_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 206794687
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_solitude_large2, "object/building/poi/shared_corellia_solitude_large2.iff")

object_building_poi_shared_corellia_solitude_medium3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_solitude_medium3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3525690034
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_solitude_medium3, "object/building/poi/shared_corellia_solitude_medium3.iff")

object_building_poi_shared_corellia_solitude_small4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_solitude_small4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1646203242
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_solitude_small4, "object/building/poi/shared_corellia_solitude_small4.iff")

object_building_poi_shared_corellia_swoop_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_swoop_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1644662189
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_swoop_large1, "object/building/poi/shared_corellia_swoop_large1.iff")

object_building_poi_shared_corellia_swoop_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_swoop_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3104843066
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_swoop_large2, "object/building/poi/shared_corellia_swoop_large2.iff")

object_building_poi_shared_corellia_swoop_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_corellia_swoop_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4028449463
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_corellia_swoop_large3, "object/building/poi/shared_corellia_swoop_large3.iff")

object_building_poi_shared_creature_lair_baz_nitch = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_baz_nitch.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1132882531
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_baz_nitch, "object/building/poi/shared_creature_lair_baz_nitch.iff")

object_building_poi_shared_creature_lair_boar_wolf = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_boar_wolf.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2163254490
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_boar_wolf, "object/building/poi/shared_creature_lair_boar_wolf.iff")

object_building_poi_shared_creature_lair_bocat = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_bocat.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2699861572
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_bocat, "object/building/poi/shared_creature_lair_bocat.iff")

object_building_poi_shared_creature_lair_bolma = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_bolma.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1685804096
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_bolma, "object/building/poi/shared_creature_lair_bolma.iff")

object_building_poi_shared_creature_lair_brackaset = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_brackaset.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2511531434
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_brackaset, "object/building/poi/shared_creature_lair_brackaset.iff")

object_building_poi_shared_creature_lair_brokensandcrawler_herb_camp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_brokensandcrawler_herb_camp.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3260213168
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_brokensandcrawler_herb_camp, "object/building/poi/shared_creature_lair_brokensandcrawler_herb_camp.iff")

object_building_poi_shared_creature_lair_condor_dragon = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_condor_dragon.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 168468441
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_condor_dragon, "object/building/poi/shared_creature_lair_condor_dragon.iff")

object_building_poi_shared_creature_lair_deathstarruins_junktown = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_deathstarruins_junktown.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2536553904
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_deathstarruins_junktown, "object/building/poi/shared_creature_lair_deathstarruins_junktown.iff")

object_building_poi_shared_creature_lair_deathstarruinsoldcamp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_deathstarruinsoldcamp.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2155178725
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_deathstarruinsoldcamp, "object/building/poi/shared_creature_lair_deathstarruinsoldcamp.iff")

object_building_poi_shared_creature_lair_exploding_homestead = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_exploding_homestead.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2933459627
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_exploding_homestead, "object/building/poi/shared_creature_lair_exploding_homestead.iff")

object_building_poi_shared_creature_lair_forest_bloom_herbivore = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_forest_bloom_herbivore.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2864892154
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_forest_bloom_herbivore, "object/building/poi/shared_creature_lair_forest_bloom_herbivore.iff")

object_building_poi_shared_creature_lair_forest_camp_remains = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_forest_camp_remains.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 312069736
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_forest_camp_remains, "object/building/poi/shared_creature_lair_forest_camp_remains.iff")

object_building_poi_shared_creature_lair_forest_sacrifice_beast = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_forest_sacrifice_beast.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1499753343
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_forest_sacrifice_beast, "object/building/poi/shared_creature_lair_forest_sacrifice_beast.iff")

object_building_poi_shared_creature_lair_gaping_spider = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_gaping_spider.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3037282369
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_gaping_spider, "object/building/poi/shared_creature_lair_gaping_spider.iff")

object_building_poi_shared_creature_lair_graul = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_graul.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1500140860
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_graul, "object/building/poi/shared_creature_lair_graul.iff")

object_building_poi_shared_creature_lair_gronda = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_gronda.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3644562261
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_gronda, "object/building/poi/shared_creature_lair_gronda.iff")

object_building_poi_shared_creature_lair_guardian_rancor = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_guardian_rancor.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4133313486
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_guardian_rancor, "object/building/poi/shared_creature_lair_guardian_rancor.iff")

object_building_poi_shared_creature_lair_gubbur = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_gubbur.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1423458211
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_gubbur, "object/building/poi/shared_creature_lair_gubbur.iff")

object_building_poi_shared_creature_lair_imperial_destroy = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_imperial_destroy.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 833511658
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_imperial_destroy, "object/building/poi/shared_creature_lair_imperial_destroy.iff")

object_building_poi_shared_creature_lair_kusak = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_kusak.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3440583076
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_kusak, "object/building/poi/shared_creature_lair_kusak.iff")

object_building_poi_shared_creature_lair_kwi = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_kwi.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2439742199
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_kwi, "object/building/poi/shared_creature_lair_kwi.iff")

object_building_poi_shared_creature_lair_langlatch = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_langlatch.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2030330619
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_langlatch, "object/building/poi/shared_creature_lair_langlatch.iff")

object_building_poi_shared_creature_lair_malkloc = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_malkloc.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3137310203
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_malkloc, "object/building/poi/shared_creature_lair_malkloc.iff")

object_building_poi_shared_creature_lair_purbole = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_purbole.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2399203938
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_purbole, "object/building/poi/shared_creature_lair_purbole.iff")

object_building_poi_shared_creature_lair_remer = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_remer.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3508768381
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_remer, "object/building/poi/shared_creature_lair_remer.iff")

object_building_poi_shared_creature_lair_reptilian_flyer = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_reptilian_flyer.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4009911486
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_reptilian_flyer, "object/building/poi/shared_creature_lair_reptilian_flyer.iff")

object_building_poi_shared_creature_lair_sand_panther = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_sand_panther.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3588797301
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_sand_panther, "object/building/poi/shared_creature_lair_sand_panther.iff")

object_building_poi_shared_creature_lair_shear_mite = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_shear_mite.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4085921723
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_shear_mite, "object/building/poi/shared_creature_lair_shear_mite.iff")

object_building_poi_shared_creature_lair_swampy_lair = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_swampy_lair.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1454550642
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_swampy_lair, "object/building/poi/shared_creature_lair_swampy_lair.iff")

object_building_poi_shared_creature_lair_verne = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_creature_lair_verne.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3846558086
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_creature_lair_verne, "object/building/poi/shared_creature_lair_verne.iff")

object_building_poi_shared_dantooine_janta_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dantooine_janta_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2789761722
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dantooine_janta_large1, "object/building/poi/shared_dantooine_janta_large1.iff")

object_building_poi_shared_dantooine_janta_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dantooine_janta_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2103429677
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dantooine_janta_large2, "object/building/poi/shared_dantooine_janta_large2.iff")

object_building_poi_shared_dantooine_janta_medium1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dantooine_janta_medium1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2834276344
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dantooine_janta_medium1, "object/building/poi/shared_dantooine_janta_medium1.iff")

object_building_poi_shared_dantooine_janta_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dantooine_janta_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1945646959
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dantooine_janta_medium2, "object/building/poi/shared_dantooine_janta_medium2.iff")

object_building_poi_shared_dantooine_janta_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dantooine_janta_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2062176502
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dantooine_janta_small1, "object/building/poi/shared_dantooine_janta_small1.iff")

object_building_poi_shared_dantooine_janta_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dantooine_janta_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2717775969
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dantooine_janta_small2, "object/building/poi/shared_dantooine_janta_small2.iff")

object_building_poi_shared_dantooine_kunga_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dantooine_kunga_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2589378688
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dantooine_kunga_large1, "object/building/poi/shared_dantooine_kunga_large1.iff")

object_building_poi_shared_dantooine_kunga_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dantooine_kunga_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1094803479
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dantooine_kunga_large2, "object/building/poi/shared_dantooine_kunga_large2.iff")

object_building_poi_shared_dantooine_kunga_medium1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dantooine_kunga_medium1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1467699980
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dantooine_kunga_medium1, "object/building/poi/shared_dantooine_kunga_medium1.iff")

object_building_poi_shared_dantooine_kunga_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dantooine_kunga_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2355952539
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dantooine_kunga_medium2, "object/building/poi/shared_dantooine_kunga_medium2.iff")

object_building_poi_shared_dantooine_kunga_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dantooine_kunga_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1190460108
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dantooine_kunga_small1, "object/building/poi/shared_dantooine_kunga_small1.iff")

object_building_poi_shared_dantooine_kunga_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dantooine_kunga_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2648920667
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dantooine_kunga_small2, "object/building/poi/shared_dantooine_kunga_small2.iff")

object_building_poi_shared_dantooine_mokk_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dantooine_mokk_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 175414071
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dantooine_mokk_large1, "object/building/poi/shared_dantooine_mokk_large1.iff")

object_building_poi_shared_dantooine_mokk_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dantooine_mokk_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3512939424
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dantooine_mokk_large2, "object/building/poi/shared_dantooine_mokk_large2.iff")

object_building_poi_shared_dantooine_mokk_medium1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dantooine_mokk_medium1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1345707922
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dantooine_mokk_medium1, "object/building/poi/shared_dantooine_mokk_medium1.iff")

object_building_poi_shared_dantooine_mokk_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dantooine_mokk_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2334291717
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dantooine_mokk_medium2, "object/building/poi/shared_dantooine_mokk_medium2.iff")

object_building_poi_shared_dantooine_mokk_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dantooine_mokk_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3604392315
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dantooine_mokk_small1, "object/building/poi/shared_dantooine_mokk_small1.iff")

object_building_poi_shared_dantooine_mokk_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dantooine_mokk_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 230752748
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dantooine_mokk_small2, "object/building/poi/shared_dantooine_mokk_small2.iff")

object_building_poi_shared_dathomir_freedprisonercamp_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_freedprisonercamp_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1611276352
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_freedprisonercamp_small1, "object/building/poi/shared_dathomir_freedprisonercamp_small1.iff")

object_building_poi_shared_dathomir_freedprisonercamp_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_freedprisonercamp_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3139274967
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_freedprisonercamp_small2, "object/building/poi/shared_dathomir_freedprisonercamp_small2.iff")

object_building_poi_shared_dathomir_freedprisonerscamp_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_freedprisonerscamp_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3067701329
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_freedprisonerscamp_large1, "object/building/poi/shared_dathomir_freedprisonerscamp_large1.iff")

object_building_poi_shared_dathomir_freedprisonerscamp_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_freedprisonerscamp_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1842266310
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_freedprisonerscamp_large2, "object/building/poi/shared_dathomir_freedprisonerscamp_large2.iff")

object_building_poi_shared_dathomir_freedprisonerscamp_medium1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_freedprisonerscamp_medium1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1978969992
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_freedprisonerscamp_medium1, "object/building/poi/shared_dathomir_freedprisonerscamp_medium1.iff")

object_building_poi_shared_dathomir_freedprisonerscamp_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_freedprisonerscamp_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2934114079
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_freedprisonerscamp_medium2, "object/building/poi/shared_dathomir_freedprisonerscamp_medium2.iff")

object_building_poi_shared_dathomir_imperialprisonpatrol_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_imperialprisonpatrol_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2603789484
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_imperialprisonpatrol_large1, "object/building/poi/shared_dathomir_imperialprisonpatrol_large1.iff")

object_building_poi_shared_dathomir_imperialprisonpatrol_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_imperialprisonpatrol_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1076167739
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_imperialprisonpatrol_large2, "object/building/poi/shared_dathomir_imperialprisonpatrol_large2.iff")

object_building_poi_shared_dathomir_imperialprisonpatrol_medium1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_imperialprisonpatrol_medium1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 937321147
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_imperialprisonpatrol_medium1, "object/building/poi/shared_dathomir_imperialprisonpatrol_medium1.iff")

object_building_poi_shared_dathomir_imperialprisonscout_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_imperialprisonscout_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1927414722
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_imperialprisonscout_small1, "object/building/poi/shared_dathomir_imperialprisonscout_small1.iff")

object_building_poi_shared_dathomir_imperialprisonscout_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_imperialprisonscout_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2851449685
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_imperialprisonscout_small2, "object/building/poi/shared_dathomir_imperialprisonscout_small2.iff")

object_building_poi_shared_dathomir_nightsister_medium3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_nightsister_medium3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 255101489
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_nightsister_medium3, "object/building/poi/shared_dathomir_nightsister_medium3.iff")

object_building_poi_shared_dathomir_nightsister_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_nightsister_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2012109994
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_nightsister_small1, "object/building/poi/shared_dathomir_nightsister_small1.iff")

object_building_poi_shared_dathomir_nightsister_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_nightsister_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2902062141
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_nightsister_small2, "object/building/poi/shared_dathomir_nightsister_small2.iff")

object_building_poi_shared_dathomir_nightsister_small3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_nightsister_small3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3858011056
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_nightsister_small3, "object/building/poi/shared_dathomir_nightsister_small3.iff")

object_building_poi_shared_dathomir_nightsister_small4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_nightsister_small4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 504871076
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_nightsister_small4, "object/building/poi/shared_dathomir_nightsister_small4.iff")

object_building_poi_shared_dathomir_nightsister_small5 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_nightsister_small5.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1461378857
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_nightsister_small5, "object/building/poi/shared_dathomir_nightsister_small5.iff")

object_building_poi_shared_dathomir_nightsister_small6 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_nightsister_small6.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2349692862
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_nightsister_small6, "object/building/poi/shared_dathomir_nightsister_small6.iff")

object_building_poi_shared_dathomir_nightsisterpatrol_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_nightsisterpatrol_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3485566354
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_nightsisterpatrol_large1, "object/building/poi/shared_dathomir_nightsisterpatrol_large1.iff")

object_building_poi_shared_dathomir_nightsisterpatrol_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_nightsisterpatrol_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 349580549
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_nightsisterpatrol_large2, "object/building/poi/shared_dathomir_nightsisterpatrol_large2.iff")

object_building_poi_shared_dathomir_nightsisterpatrol_medium1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_nightsisterpatrol_medium1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2942599520
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_nightsisterpatrol_medium1, "object/building/poi/shared_dathomir_nightsisterpatrol_medium1.iff")

object_building_poi_shared_dathomir_singingmtnclan_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_singingmtnclan_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3095836244
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_singingmtnclan_small1, "object/building/poi/shared_dathomir_singingmtnclan_small1.iff")

object_building_poi_shared_dathomir_singingmtnclan_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_singingmtnclan_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1670454979
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_singingmtnclan_small2, "object/building/poi/shared_dathomir_singingmtnclan_small2.iff")

object_building_poi_shared_dathomir_singingmtnclanpatrol_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_singingmtnclanpatrol_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 139005500
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_singingmtnclanpatrol_large1, "object/building/poi/shared_dathomir_singingmtnclanpatrol_large1.iff")

object_building_poi_shared_dathomir_singingmtnclanpatrol_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_singingmtnclanpatrol_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3546195627
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_singingmtnclanpatrol_large2, "object/building/poi/shared_dathomir_singingmtnclanpatrol_large2.iff")

object_building_poi_shared_dathomir_singingmtnclanpatrol_medium1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_dathomir_singingmtnclanpatrol_medium1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1680011260
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_dathomir_singingmtnclanpatrol_medium1, "object/building/poi/shared_dathomir_singingmtnclanpatrol_medium1.iff")

object_building_poi_shared_destroyed_moisture_farm_theater = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_destroyed_moisture_farm_theater.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4201619574
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_destroyed_moisture_farm_theater, "object/building/poi/shared_destroyed_moisture_farm_theater.iff")

object_building_poi_shared_destroyed_sandcrawler_theater = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_destroyed_sandcrawler_theater.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3909453160
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_destroyed_sandcrawler_theater, "object/building/poi/shared_destroyed_sandcrawler_theater.iff")

object_building_poi_shared_endor_dulok_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_dulok_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1489412304
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_dulok_large1, "object/building/poi/shared_endor_dulok_large1.iff")

object_building_poi_shared_endor_dulok_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_dulok_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2211514439
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_dulok_large2, "object/building/poi/shared_endor_dulok_large2.iff")

object_building_poi_shared_endor_dulok_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_dulok_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3403444170
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_dulok_large3, "object/building/poi/shared_endor_dulok_large3.iff")

object_building_poi_shared_endor_dulok_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_dulok_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3951405793
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_dulok_medium, "object/building/poi/shared_endor_dulok_medium.iff")

object_building_poi_shared_endor_dulok_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_dulok_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1208746092
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_dulok_medium2, "object/building/poi/shared_endor_dulok_medium2.iff")

object_building_poi_shared_endor_dulok_medium7 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_dulok_medium7.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 569762914
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_dulok_medium7, "object/building/poi/shared_endor_dulok_medium7.iff")

object_building_poi_shared_endor_dulok_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_dulok_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2221183644
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_dulok_small1, "object/building/poi/shared_endor_dulok_small1.iff")

object_building_poi_shared_endor_dulok_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_dulok_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1601387019
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_dulok_small2, "object/building/poi/shared_endor_dulok_small2.iff")

object_building_poi_shared_endor_dulok_small3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_dulok_small3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 377380230
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_dulok_small3, "object/building/poi/shared_endor_dulok_small3.iff")

object_building_poi_shared_endor_dulok_small5 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_dulok_small5.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2760904991
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_dulok_small5, "object/building/poi/shared_endor_dulok_small5.iff")

object_building_poi_shared_endor_dulok_small6 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_dulok_small6.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2139601288
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_dulok_small6, "object/building/poi/shared_endor_dulok_small6.iff")

object_building_poi_shared_endor_dulok_small7 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_dulok_small7.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 915070469
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_dulok_small7, "object/building/poi/shared_endor_dulok_small7.iff")

object_building_poi_shared_endor_ewok_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_ewok_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1525456539
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_ewok_large1, "object/building/poi/shared_endor_ewok_large1.iff")

object_building_poi_shared_endor_ewok_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_ewok_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2180724236
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_ewok_large2, "object/building/poi/shared_endor_ewok_large2.iff")

object_building_poi_shared_endor_ewok_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_ewok_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3371585921
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_ewok_large3, "object/building/poi/shared_endor_ewok_large3.iff")

object_building_poi_shared_endor_ewok_large4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_ewok_large4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 857045653
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_ewok_large4, "object/building/poi/shared_endor_ewok_large4.iff")

object_building_poi_shared_endor_ewok_large5 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_ewok_large5.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2048400664
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_ewok_large5, "object/building/poi/shared_endor_ewok_large5.iff")

object_building_poi_shared_endor_ewok_large6 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_ewok_large6.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2702161295
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_ewok_large6, "object/building/poi/shared_endor_ewok_large6.iff")

object_building_poi_shared_endor_ewok_large7 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_ewok_large7.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3892498946
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_ewok_large7, "object/building/poi/shared_endor_ewok_large7.iff")

object_building_poi_shared_endor_ewok_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_ewok_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3920598186
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_ewok_medium, "object/building/poi/shared_endor_ewok_medium.iff")

object_building_poi_shared_endor_ewok_medium3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_ewok_medium3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 582817679
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_ewok_medium3, "object/building/poi/shared_endor_ewok_medium3.iff")

object_building_poi_shared_endor_ewok_medium4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_ewok_medium4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3646831771
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_ewok_medium4, "object/building/poi/shared_endor_ewok_medium4.iff")

object_building_poi_shared_endor_ewok_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_ewok_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2253302999
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_ewok_small1, "object/building/poi/shared_endor_ewok_small1.iff")

object_building_poi_shared_endor_ewok_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_ewok_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1566114880
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_ewok_small2, "object/building/poi/shared_endor_ewok_small2.iff")

object_building_poi_shared_endor_ewok_small3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_ewok_small3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 341074893
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_ewok_small3, "object/building/poi/shared_endor_ewok_small3.iff")

object_building_poi_shared_endor_marauder_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_marauder_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2271972307
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_marauder_large1, "object/building/poi/shared_endor_marauder_large1.iff")

object_building_poi_shared_endor_marauder_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_marauder_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1551639364
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_marauder_large2, "object/building/poi/shared_endor_marauder_large2.iff")

object_building_poi_shared_endor_marauder_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_marauder_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 359744713
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_marauder_large3, "object/building/poi/shared_endor_marauder_large3.iff")

object_building_poi_shared_endor_marauder_large4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_marauder_large4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4002574301
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_marauder_large4, "object/building/poi/shared_endor_marauder_large4.iff")

object_building_poi_shared_endor_marauder_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_marauder_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 875069922
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_marauder_medium, "object/building/poi/shared_endor_marauder_medium.iff")

object_building_poi_shared_endor_marauder_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_marauder_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3438540088
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_marauder_medium2, "object/building/poi/shared_endor_marauder_medium2.iff")

object_building_poi_shared_endor_marauder_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_marauder_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1539946911
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_marauder_small1, "object/building/poi/shared_endor_marauder_small1.iff")

object_building_poi_shared_endor_marauder_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_marauder_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2162037000
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_marauder_small2, "object/building/poi/shared_endor_marauder_small2.iff")

object_building_poi_shared_endor_marauder_small3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_marauder_small3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3386078853
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_marauder_small3, "object/building/poi/shared_endor_marauder_small3.iff")

object_building_poi_shared_endor_marauder_small4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_endor_marauder_small4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 842030481
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_endor_marauder_small4, "object/building/poi/shared_endor_marauder_small4.iff")

object_building_poi_shared_imperial_listening_post = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_imperial_listening_post.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3267290153
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_imperial_listening_post, "object/building/poi/shared_imperial_listening_post.iff")

object_building_poi_shared_lincbarnes_testcamp_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lincbarnes_testcamp_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2644566900
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lincbarnes_testcamp_medium, "object/building/poi/shared_lincbarnes_testcamp_medium.iff")

object_building_poi_shared_lok_imperial_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_imperial_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1325908803
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_imperial_large1, "object/building/poi/shared_lok_imperial_large1.iff")

object_building_poi_shared_lok_imperial_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_imperial_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2484104148
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_imperial_large2, "object/building/poi/shared_lok_imperial_large2.iff")

object_building_poi_shared_lok_imperial_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_imperial_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3709668441
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_imperial_large3, "object/building/poi/shared_lok_imperial_large3.iff")

object_building_poi_shared_lok_imperial_large4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_imperial_large4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 654190413
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_imperial_large4, "object/building/poi/shared_lok_imperial_large4.iff")

object_building_poi_shared_lok_imperial_large5 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_imperial_large5.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1878212800
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_imperial_large5, "object/building/poi/shared_lok_imperial_large5.iff")

object_building_poi_shared_lok_imperial_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_imperial_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4232366450
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_imperial_medium, "object/building/poi/shared_lok_imperial_medium.iff")

object_building_poi_shared_lok_imperial_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_imperial_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3677952025
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_imperial_medium2, "object/building/poi/shared_lok_imperial_medium2.iff")

object_building_poi_shared_lok_imperial_medium4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_imperial_medium4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1775719552
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_imperial_medium4, "object/building/poi/shared_lok_imperial_medium4.iff")

object_building_poi_shared_lok_imperial_medium5 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_imperial_medium5.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 551170829
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_imperial_medium5, "object/building/poi/shared_lok_imperial_medium5.iff")

object_building_poi_shared_lok_imperial_medium6 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_imperial_medium6.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4224555930
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_imperial_medium6, "object/building/poi/shared_lok_imperial_medium6.iff")

object_building_poi_shared_lok_imperial_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_imperial_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2477125903
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_imperial_small1, "object/building/poi/shared_lok_imperial_small1.iff")

object_building_poi_shared_lok_imperial_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_imperial_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1219647896
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_imperial_small2, "object/building/poi/shared_lok_imperial_small2.iff")

object_building_poi_shared_lok_nymshenchman_large = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_nymshenchman_large.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2468275837
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_nymshenchman_large, "object/building/poi/shared_lok_nymshenchman_large.iff")

object_building_poi_shared_lok_nymshenchman_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_nymshenchman_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 368864307
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_nymshenchman_large2, "object/building/poi/shared_lok_nymshenchman_large2.iff")

object_building_poi_shared_lok_nymshenchman_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_nymshenchman_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1559301054
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_nymshenchman_large3, "object/building/poi/shared_lok_nymshenchman_large3.iff")

object_building_poi_shared_lok_nymshenchman_large4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_nymshenchman_large4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2802983082
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_nymshenchman_large4, "object/building/poi/shared_lok_nymshenchman_large4.iff")

object_building_poi_shared_lok_nymshenchman_large5 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_nymshenchman_large5.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3995027239
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_nymshenchman_large5, "object/building/poi/shared_lok_nymshenchman_large5.iff")

object_building_poi_shared_lok_nymshenchman_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_nymshenchman_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2108214933
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_nymshenchman_medium, "object/building/poi/shared_lok_nymshenchman_medium.iff")

object_building_poi_shared_lok_nymshenchman_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_nymshenchman_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1525875264
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_nymshenchman_medium2, "object/building/poi/shared_lok_nymshenchman_medium2.iff")

object_building_poi_shared_lok_nymshenchman_medium3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_nymshenchman_medium3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 335439309
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_nymshenchman_medium3, "object/building/poi/shared_lok_nymshenchman_medium3.iff")

object_building_poi_shared_lok_nymshenchman_medium4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_nymshenchman_medium4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3894234841
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_nymshenchman_medium4, "object/building/poi/shared_lok_nymshenchman_medium4.iff")

object_building_poi_shared_lok_nymshenchman_small3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_nymshenchman_small3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2152937970
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_nymshenchman_small3, "object/building/poi/shared_lok_nymshenchman_small3.iff")

object_building_poi_shared_lok_nymshenchman_small4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_lok_nymshenchman_small4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2075136742
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_lok_nymshenchman_small4, "object/building/poi/shared_lok_nymshenchman_small4.iff")

object_building_poi_shared_naboo_abbots_camp_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_abbots_camp_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 616378301
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_abbots_camp_large1, "object/building/poi/shared_naboo_abbots_camp_large1.iff")

object_building_poi_shared_naboo_afcitexplor_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_afcitexplor_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 591257863
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_afcitexplor_large1, "object/building/poi/shared_naboo_afcitexplor_large1.iff")

object_building_poi_shared_naboo_afcitexplor_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_afcitexplor_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4163520912
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_afcitexplor_large2, "object/building/poi/shared_naboo_afcitexplor_large2.iff")

object_building_poi_shared_naboo_afcitexplor_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_afcitexplor_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2424236854
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_afcitexplor_medium, "object/building/poi/shared_naboo_afcitexplor_medium.iff")

object_building_poi_shared_naboo_borvos_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_borvos_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 568758617
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_borvos_large1, "object/building/poi/shared_naboo_borvos_large1.iff")

object_building_poi_shared_naboo_borvos_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_borvos_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4210112974
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_borvos_large2, "object/building/poi/shared_naboo_borvos_large2.iff")

object_building_poi_shared_naboo_borvos_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_borvos_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3019660867
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_borvos_large3, "object/building/poi/shared_naboo_borvos_large3.iff")

object_building_poi_shared_naboo_borvos_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_borvos_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2460326760
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_borvos_medium, "object/building/poi/shared_naboo_borvos_medium.iff")

object_building_poi_shared_naboo_farm_medium_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_farm_medium_1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4283975782
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_farm_medium_1, "object/building/poi/shared_naboo_farm_medium_1.iff")

object_building_poi_shared_naboo_farm_medium_2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_farm_medium_2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 609214705
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_farm_medium_2, "object/building/poi/shared_naboo_farm_medium_2.iff")

object_building_poi_shared_naboo_gungawar_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_gungawar_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3123585066
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_gungawar_large1, "object/building/poi/shared_naboo_gungawar_large1.iff")

object_building_poi_shared_naboo_gungawar_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_gungawar_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1631160509
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_gungawar_large2, "object/building/poi/shared_naboo_gungawar_large2.iff")

object_building_poi_shared_naboo_gungtrad_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_gungtrad_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3437191612
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_gungtrad_large1, "object/building/poi/shared_naboo_gungtrad_large1.iff")

object_building_poi_shared_naboo_gungtrad_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_gungtrad_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 399034667
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_gungtrad_large2, "object/building/poi/shared_naboo_gungtrad_large2.iff")

object_building_poi_shared_naboo_gungtrad_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_gungtrad_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2140957581
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_gungtrad_medium, "object/building/poi/shared_naboo_gungtrad_medium.iff")

object_building_poi_shared_naboo_gungtrad_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_gungtrad_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1741955374
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_gungtrad_medium2, "object/building/poi/shared_naboo_gungtrad_medium2.iff")

object_building_poi_shared_naboo_gungwar_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_gungwar_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2104254608
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_gungwar_large1, "object/building/poi/shared_naboo_gungwar_large1.iff")

object_building_poi_shared_naboo_gungwar_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_gungwar_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2793129991
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_gungwar_large2, "object/building/poi/shared_naboo_gungwar_large2.iff")

object_building_poi_shared_naboo_gungwar_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_gungwar_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3459213985
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_gungwar_medium, "object/building/poi/shared_naboo_gungwar_medium.iff")

object_building_poi_shared_naboo_gunrunners_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_gunrunners_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2566973772
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_gunrunners_large1, "object/building/poi/shared_naboo_gunrunners_large1.iff")

object_building_poi_shared_naboo_gunrunners_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_gunrunners_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1108820443
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_gunrunners_large2, "object/building/poi/shared_naboo_gunrunners_large2.iff")

object_building_poi_shared_naboo_gunrunners_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_gunrunners_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 709092221
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_gunrunners_medium, "object/building/poi/shared_naboo_gunrunners_medium.iff")

object_building_poi_shared_naboo_gunrunners_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_gunrunners_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1168300800
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_gunrunners_small1, "object/building/poi/shared_naboo_gunrunners_small1.iff")

object_building_poi_shared_naboo_gunrunners_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_gunrunners_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2662691735
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_gunrunners_small2, "object/building/poi/shared_naboo_gunrunners_small2.iff")

object_building_poi_shared_naboo_imperial_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_imperial_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 179496592
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_imperial_large1, "object/building/poi/shared_naboo_imperial_large1.iff")

object_building_poi_shared_naboo_imperial_scout_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_imperial_scout_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1761246693
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_imperial_scout_large1, "object/building/poi/shared_naboo_imperial_scout_large1.iff")

object_building_poi_shared_naboo_impext_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_impext_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3509571779
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_impext_large1, "object/building/poi/shared_naboo_impext_large1.iff")

object_building_poi_shared_naboo_impext_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_impext_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 171472980
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_impext_large2, "object/building/poi/shared_naboo_impext_large2.iff")

object_building_poi_shared_naboo_impext_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_impext_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1127555033
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_impext_large3, "object/building/poi/shared_naboo_impext_large3.iff")

object_building_poi_shared_naboo_impext_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_impext_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1651301106
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_impext_medium, "object/building/poi/shared_naboo_impext_medium.iff")

object_building_poi_shared_naboo_impswamp_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_impswamp_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 536910191
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_impswamp_large1, "object/building/poi/shared_naboo_impswamp_large1.iff")

object_building_poi_shared_naboo_impswamp_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_impswamp_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4212601336
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_impswamp_large2, "object/building/poi/shared_naboo_impswamp_large2.iff")

object_building_poi_shared_naboo_impswamp_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_impswamp_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2470679390
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_impswamp_medium, "object/building/poi/shared_naboo_impswamp_medium.iff")

object_building_poi_shared_naboo_mauler_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_mauler_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 647466583
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_mauler_large1, "object/building/poi/shared_naboo_mauler_large1.iff")

object_building_poi_shared_naboo_mauler_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_mauler_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4253034176
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_mauler_large2, "object/building/poi/shared_naboo_mauler_large2.iff")

object_building_poi_shared_naboo_mauler_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_mauler_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2513732710
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_mauler_medium, "object/building/poi/shared_naboo_mauler_medium.iff")

object_building_poi_shared_naboo_mvillager_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_mvillager_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1333273055
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_mvillager_large1, "object/building/poi/shared_naboo_mvillager_large1.iff")

object_building_poi_shared_naboo_mvillager_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_mvillager_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2490337608
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_mvillager_large2, "object/building/poi/shared_naboo_mvillager_large2.iff")

object_building_poi_shared_naboo_mvillager_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_mvillager_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4231736302
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_mvillager_medium, "object/building/poi/shared_naboo_mvillager_medium.iff")

object_building_poi_shared_naboo_police_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_police_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2977371865
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_police_large1, "object/building/poi/shared_naboo_police_large1.iff")

object_building_poi_shared_naboo_police_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_police_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1784725070
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_police_large2, "object/building/poi/shared_naboo_police_large2.iff")

object_building_poi_shared_naboo_police_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_police_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 36969704
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_police_medium, "object/building/poi/shared_naboo_police_medium.iff")

object_building_poi_shared_naboo_politic_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_politic_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2943429571
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_politic_large1, "object/building/poi/shared_naboo_politic_large1.iff")

object_building_poi_shared_naboo_politic_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_politic_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1952875348
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_politic_large2, "object/building/poi/shared_naboo_politic_large2.iff")

object_building_poi_shared_naboo_politic_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_politic_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 473047538
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_politic_medium, "object/building/poi/shared_naboo_politic_medium.iff")

object_building_poi_shared_naboo_ruins_large_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_ruins_large_1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1925640941
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_ruins_large_1, "object/building/poi/shared_naboo_ruins_large_1.iff")

object_building_poi_shared_naboo_ruins_medium_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_ruins_medium_1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2535903472
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_ruins_medium_1, "object/building/poi/shared_naboo_ruins_medium_1.iff")

object_building_poi_shared_naboo_ruins_medium_3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_ruins_medium_3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 87826410
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_ruins_medium_3, "object/building/poi/shared_naboo_ruins_medium_3.iff")

object_building_poi_shared_naboo_ruins_small_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_ruins_small_1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4100157024
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_ruins_small_1, "object/building/poi/shared_naboo_ruins_small_1.iff")

object_building_poi_shared_naboo_ruins_small_2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_ruins_small_2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 796182263
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_ruins_small_2, "object/building/poi/shared_naboo_ruins_small_2.iff")

object_building_poi_shared_naboo_ruins_small_3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_ruins_small_3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1719247226
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_ruins_small_3, "object/building/poi/shared_naboo_ruins_small_3.iff")

object_building_poi_shared_naboo_ruins_small_4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_ruins_small_4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2644150894
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_ruins_small_4, "object/building/poi/shared_naboo_ruins_small_4.iff")

object_building_poi_shared_naboo_ruins_small_5 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_ruins_small_5.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3566726627
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_ruins_small_5, "object/building/poi/shared_naboo_ruins_small_5.iff")

object_building_poi_shared_naboo_swamhunt_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_swamhunt_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3018898037
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_swamhunt_large1, "object/building/poi/shared_naboo_swamhunt_large1.iff")

object_building_poi_shared_naboo_swamhunt_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_swamhunt_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1759974114
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_swamhunt_large2, "object/building/poi/shared_naboo_swamhunt_large2.iff")

object_building_poi_shared_naboo_swamhunt_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_swamhunt_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 11776068
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_swamhunt_medium, "object/building/poi/shared_naboo_swamhunt_medium.iff")

object_building_poi_shared_naboo_swamp_rat_gang_camp_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_swamp_rat_gang_camp_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1168819895
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_swamp_rat_gang_camp_large1, "object/building/poi/shared_naboo_swamp_rat_gang_camp_large1.iff")

object_building_poi_shared_naboo_swamp_rat_gang_camp_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_swamp_rat_gang_camp_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2663214624
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_swamp_rat_gang_camp_large2, "object/building/poi/shared_naboo_swamp_rat_gang_camp_large2.iff")

object_building_poi_shared_naboo_swamp_rat_gang_camp_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_swamp_rat_gang_camp_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4142517382
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_swamp_rat_gang_camp_medium, "object/building/poi/shared_naboo_swamp_rat_gang_camp_medium.iff")

object_building_poi_shared_naboo_tradefederationloyalist_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_tradefederationloyalist_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 665275923
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_tradefederationloyalist_large1, "object/building/poi/shared_naboo_tradefederationloyalist_large1.iff")

object_building_poi_shared_naboo_tradefederationloyalist_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_tradefederationloyalist_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4239451780
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_tradefederationloyalist_large2, "object/building/poi/shared_naboo_tradefederationloyalist_large2.iff")

object_building_poi_shared_naboo_tradefederationloyalist_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_tradefederationloyalist_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2497987618
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_tradefederationloyalist_medium, "object/building/poi/shared_naboo_tradefederationloyalist_medium.iff")

object_building_poi_shared_naboo_tradefederationloyalist_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_tradefederationloyalist_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4211440735
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_tradefederationloyalist_small1, "object/building/poi/shared_naboo_tradefederationloyalist_small1.iff")

object_building_poi_shared_naboo_tradefederationloyalist_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_tradefederationloyalist_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 538105032
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_tradefederationloyalist_small2, "object/building/poi/shared_naboo_tradefederationloyalist_small2.iff")

object_building_poi_shared_naboo_tuskcattam_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_tuskcattam_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 609383494
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_tuskcattam_large1, "object/building/poi/shared_naboo_tuskcattam_large1.iff")

object_building_poi_shared_naboo_tuskcattam_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_tuskcattam_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4282768593
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_tuskcattam_large2, "object/building/poi/shared_naboo_tuskcattam_large2.iff")

object_building_poi_shared_naboo_tuskcattam_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_tuskcattam_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2534506103
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_tuskcattam_medium, "object/building/poi/shared_naboo_tuskcattam_medium.iff")

object_building_poi_shared_naboo_village_large_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_naboo_village_large_1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1100618175
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_naboo_village_large_1, "object/building/poi/shared_naboo_village_large_1.iff")

object_building_poi_shared_rebel_listening_post = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_rebel_listening_post.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2924073718
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_rebel_listening_post, "object/building/poi/shared_rebel_listening_post.iff")

object_building_poi_shared_rebel_scavenger_camp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_rebel_scavenger_camp.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1509267724
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_rebel_scavenger_camp, "object/building/poi/shared_rebel_scavenger_camp.iff")

object_building_poi_shared_scout_camp_s0 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_scout_camp_s0.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 144155712
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_scout_camp_s0, "object/building/poi/shared_scout_camp_s0.iff")

object_building_poi_shared_scout_camp_s1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_scout_camp_s1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1100661709
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_scout_camp_s1, "object/building/poi/shared_scout_camp_s1.iff")

object_building_poi_shared_scout_camp_s2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_scout_camp_s2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2592959322
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_scout_camp_s2, "object/building/poi/shared_scout_camp_s2.iff")

object_building_poi_shared_scout_camp_s3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_scout_camp_s3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3548384471
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_scout_camp_s3, "object/building/poi/shared_scout_camp_s3.iff")

object_building_poi_shared_scout_camp_s4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_scout_camp_s4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 677586883
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_scout_camp_s4, "object/building/poi/shared_scout_camp_s4.iff")

object_building_poi_shared_scout_camp_s5 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_scout_camp_s5.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1634615374
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_scout_camp_s5, "object/building/poi/shared_scout_camp_s5.iff")

object_building_poi_shared_slavegirl_medium_camp_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_slavegirl_medium_camp_1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 301257872
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_slavegirl_medium_camp_1, "object/building/poi/shared_slavegirl_medium_camp_1.iff")

object_building_poi_shared_slavegirl_medium_camp_2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_slavegirl_medium_camp_2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3403906055
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_slavegirl_medium_camp_2, "object/building/poi/shared_slavegirl_medium_camp_2.iff")

object_building_poi_shared_slavegirl_small_camp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_slavegirl_small_camp.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2704439988
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_slavegirl_small_camp, "object/building/poi/shared_slavegirl_small_camp.iff")

object_building_poi_shared_small_imperial_tie_bomber_base = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_small_imperial_tie_bomber_base.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2957252267
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_small_imperial_tie_bomber_base, "object/building/poi/shared_small_imperial_tie_bomber_base.iff")

object_building_poi_shared_small_imperial_tie_bomber_base_v2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_small_imperial_tie_bomber_base_v2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1574028468
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_small_imperial_tie_bomber_base_v2, "object/building/poi/shared_small_imperial_tie_bomber_base_v2.iff")

object_building_poi_shared_tatooine_alkahara_bandits_camp_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_alkahara_bandits_camp_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 622598573
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_alkahara_bandits_camp_medium, "object/building/poi/shared_tatooine_alkahara_bandits_camp_medium.iff")

object_building_poi_shared_tatooine_alkahara_bandits_camp_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_alkahara_bandits_camp_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1258103248
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_alkahara_bandits_camp_small1, "object/building/poi/shared_tatooine_alkahara_bandits_camp_small1.iff")

object_building_poi_shared_tatooine_alkahara_bandits_camp_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_alkahara_bandits_camp_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2448066887
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_alkahara_bandits_camp_small2, "object/building/poi/shared_tatooine_alkahara_bandits_camp_small2.iff")

object_building_poi_shared_tatooine_alkahara_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_alkahara_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4289090146
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_alkahara_large1, "object/building/poi/shared_tatooine_alkahara_large1.iff")

object_building_poi_shared_tatooine_alkahara_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_alkahara_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 615643893
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_alkahara_large2, "object/building/poi/shared_tatooine_alkahara_large2.iff")

object_building_poi_shared_tatooine_burning_sandcrawler = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_burning_sandcrawler.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2841070881
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_burning_sandcrawler, "object/building/poi/shared_tatooine_burning_sandcrawler.iff")

object_building_poi_shared_tatooine_dervishcamp_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_dervishcamp_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2792167870
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_dervishcamp_large1, "object/building/poi/shared_tatooine_dervishcamp_large1.iff")

object_building_poi_shared_tatooine_dervishcamp_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_dervishcamp_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2105192745
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_dervishcamp_large2, "object/building/poi/shared_tatooine_dervishcamp_large2.iff")

object_building_poi_shared_tatooine_dervishcamp_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_dervishcamp_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 355341199
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_dervishcamp_medium, "object/building/poi/shared_tatooine_dervishcamp_medium.iff")

object_building_poi_shared_tatooine_dervishcamp_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_dervishcamp_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2060397554
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_dervishcamp_small1, "object/building/poi/shared_tatooine_dervishcamp_small1.iff")

object_building_poi_shared_tatooine_dervishcamp_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_dervishcamp_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2715321189
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_dervishcamp_small2, "object/building/poi/shared_tatooine_dervishcamp_small2.iff")

object_building_poi_shared_tatooine_desert_demons_camp_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_desert_demons_camp_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3587580084
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_desert_demons_camp_large1, "object/building/poi/shared_tatooine_desert_demons_camp_large1.iff")

object_building_poi_shared_tatooine_desert_demons_camp_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_desert_demons_camp_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 247564323
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_desert_demons_camp_large2, "object/building/poi/shared_tatooine_desert_demons_camp_large2.iff")

object_building_poi_shared_tatooine_desert_demons_camp_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_desert_demons_camp_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1721051781
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_desert_demons_camp_medium, "object/building/poi/shared_tatooine_desert_demons_camp_medium.iff")

object_building_poi_shared_tatooine_dim_u_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_dim_u_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3919443673
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_dim_u_large1, "object/building/poi/shared_tatooine_dim_u_large1.iff")

object_building_poi_shared_tatooine_dim_u_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_dim_u_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 847928910
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_dim_u_large2, "object/building/poi/shared_tatooine_dim_u_large2.iff")

object_building_poi_shared_tatooine_dim_u_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_dim_u_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1524563176
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_dim_u_medium, "object/building/poi/shared_tatooine_dim_u_medium.iff")

object_building_poi_shared_tatooine_dunestalkers_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_dunestalkers_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1602134381
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_dunestalkers_large1, "object/building/poi/shared_tatooine_dunestalkers_large1.iff")

object_building_poi_shared_tatooine_dunestalkers_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_dunestalkers_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2221476346
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_dunestalkers_large2, "object/building/poi/shared_tatooine_dunestalkers_large2.iff")

object_building_poi_shared_tatooine_dunestalkers_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_dunestalkers_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3963464540
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_dunestalkers_medium, "object/building/poi/shared_tatooine_dunestalkers_medium.iff")

object_building_poi_shared_tatooine_dunestalkers_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_dunestalkers_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2212270881
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_dunestalkers_small1, "object/building/poi/shared_tatooine_dunestalkers_small1.iff")

object_building_poi_shared_tatooine_dunestalkers_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_dunestalkers_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1489714102
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_dunestalkers_small2, "object/building/poi/shared_tatooine_dunestalkers_small2.iff")

object_building_poi_shared_tatooine_evil_hermit_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_hermit_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3440346918
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_hermit_large1, "object/building/poi/shared_tatooine_evil_hermit_large1.iff")

object_building_poi_shared_tatooine_evil_hermit_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_hermit_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 370683825
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_hermit_large2, "object/building/poi/shared_tatooine_evil_hermit_large2.iff")

object_building_poi_shared_tatooine_evil_hermit_medium1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_hermit_medium1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1759776270
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_hermit_medium1, "object/building/poi/shared_tatooine_evil_hermit_medium1.iff")

object_building_poi_shared_tatooine_evil_hermit_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_hermit_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3019089561
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_hermit_medium2, "object/building/poi/shared_tatooine_evil_hermit_medium2.iff")

object_building_poi_shared_tatooine_evil_hermit_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_hermit_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 296596842
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_hermit_small1, "object/building/poi/shared_tatooine_evil_hermit_small1.iff")

object_building_poi_shared_tatooine_evil_hermit_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_hermit_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3401195005
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_hermit_small2, "object/building/poi/shared_tatooine_evil_hermit_small2.iff")

object_building_poi_shared_tatooine_evil_nomad_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_nomad_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 577830484
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_nomad_large1, "object/building/poi/shared_tatooine_evil_nomad_large1.iff")

object_building_poi_shared_tatooine_evil_nomad_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_nomad_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4184299203
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_nomad_large2, "object/building/poi/shared_tatooine_evil_nomad_large2.iff")

object_building_poi_shared_tatooine_evil_nomad_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_nomad_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2959749454
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_nomad_large3, "object/building/poi/shared_tatooine_evil_nomad_large3.iff")

object_building_poi_shared_tatooine_evil_nomad_medium1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_nomad_medium1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3933988810
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_nomad_medium1, "object/building/poi/shared_tatooine_evil_nomad_medium1.iff")

object_building_poi_shared_tatooine_evil_nomad_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_nomad_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 829181789
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_nomad_medium2, "object/building/poi/shared_tatooine_evil_nomad_medium2.iff")

object_building_poi_shared_tatooine_evil_nomad_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_nomad_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4275227672
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_nomad_small1, "object/building/poi/shared_tatooine_evil_nomad_small1.iff")

object_building_poi_shared_tatooine_evil_nomad_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_nomad_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 633693327
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_nomad_small2, "object/building/poi/shared_tatooine_evil_nomad_small2.iff")

object_building_poi_shared_tatooine_evil_settlers_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_settlers_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 944821265
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_settlers_large1, "object/building/poi/shared_tatooine_evil_settlers_large1.iff")

object_building_poi_shared_tatooine_evil_settlers_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_settlers_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3813112966
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_settlers_large2, "object/building/poi/shared_tatooine_evil_settlers_large2.iff")

object_building_poi_shared_tatooine_evil_settlers_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_settlers_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2856983307
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_settlers_large3, "object/building/poi/shared_tatooine_evil_settlers_large3.iff")

object_building_poi_shared_tatooine_evil_settlers_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_settlers_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2333335072
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_settlers_medium, "object/building/poi/shared_tatooine_evil_settlers_medium.iff")

object_building_poi_shared_tatooine_evil_settlers_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_settlers_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1927088123
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_settlers_medium2, "object/building/poi/shared_tatooine_evil_settlers_medium2.iff")

object_building_poi_shared_tatooine_evil_settlers_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_settlers_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3841123933
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_settlers_small1, "object/building/poi/shared_tatooine_evil_settlers_small1.iff")

object_building_poi_shared_tatooine_evil_settlers_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_evil_settlers_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1071992522
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_evil_settlers_small2, "object/building/poi/shared_tatooine_evil_settlers_small2.iff")

object_building_poi_shared_tatooine_factory_liberation = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_factory_liberation.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3256091414
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_factory_liberation, "object/building/poi/shared_tatooine_factory_liberation.iff")

object_building_poi_shared_tatooine_farm_medium_2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_farm_medium_2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 589370670
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_farm_medium_2, "object/building/poi/shared_tatooine_farm_medium_2.iff")

object_building_poi_shared_tatooine_fugitive_camp_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_fugitive_camp_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2269855089
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_fugitive_camp_large1, "object/building/poi/shared_tatooine_fugitive_camp_large1.iff")

object_building_poi_shared_tatooine_fugitive_camp_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_fugitive_camp_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1549571558
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_fugitive_camp_large2, "object/building/poi/shared_tatooine_fugitive_camp_large2.iff")

object_building_poi_shared_tatooine_fugitive_camp_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_fugitive_camp_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 357692011
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_fugitive_camp_large3, "object/building/poi/shared_tatooine_fugitive_camp_large3.iff")

object_building_poi_shared_tatooine_fugitive_camp_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_fugitive_camp_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 872953664
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_fugitive_camp_medium, "object/building/poi/shared_tatooine_fugitive_camp_medium.iff")

object_building_poi_shared_tatooine_gunrunners_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_gunrunners_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2407212781
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_gunrunners_large1, "object/building/poi/shared_tatooine_gunrunners_large1.iff")

object_building_poi_shared_tatooine_gunrunners_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_gunrunners_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1416400506
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_gunrunners_large2, "object/building/poi/shared_tatooine_gunrunners_large2.iff")

object_building_poi_shared_tatooine_gunrunners_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_gunrunners_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1010314460
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_gunrunners_medium, "object/building/poi/shared_tatooine_gunrunners_medium.iff")

object_building_poi_shared_tatooine_hutt_assassin_camp_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_hutt_assassin_camp_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3403597906
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_hutt_assassin_camp_large1, "object/building/poi/shared_tatooine_hutt_assassin_camp_large1.iff")

object_building_poi_shared_tatooine_hutt_assassin_camp_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_hutt_assassin_camp_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 298410181
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_hutt_assassin_camp_large2, "object/building/poi/shared_tatooine_hutt_assassin_camp_large2.iff")

object_building_poi_shared_tatooine_hutt_assassin_camp_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_hutt_assassin_camp_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1489241928
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_hutt_assassin_camp_large3, "object/building/poi/shared_tatooine_hutt_assassin_camp_large3.iff")

object_building_poi_shared_tatooine_hutt_assassin_camp_large4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_hutt_assassin_camp_large4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2737253468
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_hutt_assassin_camp_large4, "object/building/poi/shared_tatooine_hutt_assassin_camp_large4.iff")

object_building_poi_shared_tatooine_hutt_assassin_camp_medium1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_hutt_assassin_camp_medium1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2817272331
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_hutt_assassin_camp_medium1, "object/building/poi/shared_tatooine_hutt_assassin_camp_medium1.iff")

object_building_poi_shared_tatooine_hutt_assassin_camp_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_hutt_assassin_camp_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2096857756
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_hutt_assassin_camp_medium2, "object/building/poi/shared_tatooine_hutt_assassin_camp_medium2.iff")

object_building_poi_shared_tatooine_hutt_assassin_camp_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_hutt_assassin_camp_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 377289246
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_hutt_assassin_camp_small1, "object/building/poi/shared_tatooine_hutt_assassin_camp_small1.iff")

object_building_poi_shared_tatooine_hutt_assassin_camp_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_hutt_assassin_camp_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3446362761
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_hutt_assassin_camp_small2, "object/building/poi/shared_tatooine_hutt_assassin_camp_small2.iff")

object_building_poi_shared_tatooine_hutt_businessmen_camp_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_hutt_businessmen_camp_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2763131686
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_hutt_businessmen_camp_large1, "object/building/poi/shared_tatooine_hutt_businessmen_camp_large1.iff")

object_building_poi_shared_tatooine_hutt_businessmen_camp_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_hutt_businessmen_camp_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2141561777
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_hutt_businessmen_camp_large2, "object/building/poi/shared_tatooine_hutt_businessmen_camp_large2.iff")

object_building_poi_shared_tatooine_hutt_businessmen_camp_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_hutt_businessmen_camp_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 917029948
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_hutt_businessmen_camp_large3, "object/building/poi/shared_tatooine_hutt_businessmen_camp_large3.iff")

object_building_poi_shared_tatooine_hutt_businessmen_camp_large4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_hutt_businessmen_camp_large4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3444305704
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_hutt_businessmen_camp_large4, "object/building/poi/shared_tatooine_hutt_businessmen_camp_large4.iff")

object_building_poi_shared_tatooine_hutt_businessmen_camp_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_hutt_businessmen_camp_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 401670423
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_hutt_businessmen_camp_medium, "object/building/poi/shared_tatooine_hutt_businessmen_camp_medium.iff")

object_building_poi_shared_tatooine_hutt_businessmen_camp_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_hutt_businessmen_camp_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2148765697
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_hutt_businessmen_camp_medium2, "object/building/poi/shared_tatooine_hutt_businessmen_camp_medium2.iff")

object_building_poi_shared_tatooine_hutt_businessmen_camp_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_hutt_businessmen_camp_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2014329194
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_hutt_businessmen_camp_small1, "object/building/poi/shared_tatooine_hutt_businessmen_camp_small1.iff")

object_building_poi_shared_tatooine_hutt_businessmen_camp_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_hutt_businessmen_camp_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2735182333
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_hutt_businessmen_camp_small2, "object/building/poi/shared_tatooine_hutt_businessmen_camp_small2.iff")

object_building_poi_shared_tatooine_jawa_droid_thieves_camp_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_jawa_droid_thieves_camp_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1785735227
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_jawa_droid_thieves_camp_large1, "object/building/poi/shared_tatooine_jawa_droid_thieves_camp_large1.iff")

object_building_poi_shared_tatooine_jawa_droid_thieves_camp_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_jawa_droid_thieves_camp_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2976350380
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_jawa_droid_thieves_camp_large2, "object/building/poi/shared_tatooine_jawa_droid_thieves_camp_large2.iff")

object_building_poi_shared_tatooine_jawa_droid_thieves_camp_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_jawa_droid_thieves_camp_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4167755553
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_jawa_droid_thieves_camp_large3, "object/building/poi/shared_tatooine_jawa_droid_thieves_camp_large3.iff")

object_building_poi_shared_tatooine_jawa_droid_thieves_camp_medium1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_jawa_droid_thieves_camp_medium1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4163048709
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_jawa_droid_thieves_camp_medium1, "object/building/poi/shared_tatooine_jawa_droid_thieves_camp_medium1.iff")

object_building_poi_shared_tatooine_jawa_large_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_jawa_large_1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 780991958
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_jawa_large_1, "object/building/poi/shared_tatooine_jawa_large_1.iff")

object_building_poi_shared_tatooine_jawa_tradesmen_camp_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_jawa_tradesmen_camp_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 230353567
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_jawa_tradesmen_camp_large1, "object/building/poi/shared_tatooine_jawa_tradesmen_camp_large1.iff")

object_building_poi_shared_tatooine_jawa_tradesmen_camp_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_jawa_tradesmen_camp_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3601678856
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_jawa_tradesmen_camp_large2, "object/building/poi/shared_tatooine_jawa_tradesmen_camp_large2.iff")

object_building_poi_shared_tatooine_jawa_tradesmen_camp_medium1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_jawa_tradesmen_camp_medium1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2147690391
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_jawa_tradesmen_camp_medium1, "object/building/poi/shared_tatooine_jawa_tradesmen_camp_medium1.iff")

object_building_poi_shared_tatooine_mineral_farmer_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_mineral_farmer_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 886252581
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_mineral_farmer_large1, "object/building/poi/shared_tatooine_mineral_farmer_large1.iff")

object_building_poi_shared_tatooine_mineral_farmer_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_mineral_farmer_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4022635698
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_mineral_farmer_large2, "object/building/poi/shared_tatooine_mineral_farmer_large2.iff")

object_building_poi_shared_tatooine_mineral_farmer_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_mineral_farmer_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2798250815
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_mineral_farmer_large3, "object/building/poi/shared_tatooine_mineral_farmer_large3.iff")

object_building_poi_shared_tatooine_mineral_farmer_large4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_mineral_farmer_large4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1563082795
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_mineral_farmer_large4, "object/building/poi/shared_tatooine_mineral_farmer_large4.iff")

object_building_poi_shared_tatooine_mineral_farmer_medium1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_mineral_farmer_medium1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 523632648
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_mineral_farmer_medium1, "object/building/poi/shared_tatooine_mineral_farmer_medium1.iff")

object_building_poi_shared_tatooine_mineral_farmer_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_mineral_farmer_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3290540191
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_mineral_farmer_medium2, "object/building/poi/shared_tatooine_mineral_farmer_medium2.iff")

object_building_poi_shared_tatooine_moisture_farmer_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_moisture_farmer_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2815056351
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_moisture_farmer_large1, "object/building/poi/shared_tatooine_moisture_farmer_large1.iff")

object_building_poi_shared_tatooine_moisture_farmer_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_moisture_farmer_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2094920008
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_moisture_farmer_large2, "object/building/poi/shared_tatooine_moisture_farmer_large2.iff")

object_building_poi_shared_tatooine_moisture_farmer_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_moisture_farmer_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 902862533
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_moisture_farmer_large3, "object/building/poi/shared_tatooine_moisture_farmer_large3.iff")

object_building_poi_shared_tatooine_moisture_farmer_large4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_moisture_farmer_large4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3459497425
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_moisture_farmer_large4, "object/building/poi/shared_tatooine_moisture_farmer_large4.iff")

object_building_poi_shared_tatooine_moisture_farmer_medium1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_moisture_farmer_medium1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 773187407
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_moisture_farmer_medium1, "object/building/poi/shared_tatooine_moisture_farmer_medium1.iff")

object_building_poi_shared_tatooine_moisture_farmer_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_moisture_farmer_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4110569432
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_moisture_farmer_medium2, "object/building/poi/shared_tatooine_moisture_farmer_medium2.iff")

object_building_poi_shared_tatooine_nomad_squatter_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_nomad_squatter_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1135190096
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_nomad_squatter_large1, "object/building/poi/shared_tatooine_nomad_squatter_large1.iff")

object_building_poi_shared_tatooine_nomad_squatter_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_nomad_squatter_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2562590919
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_nomad_squatter_large2, "object/building/poi/shared_tatooine_nomad_squatter_large2.iff")

object_building_poi_shared_tatooine_nomad_squatter_medium1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_nomad_squatter_medium1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2604742890
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_nomad_squatter_medium1, "object/building/poi/shared_tatooine_nomad_squatter_medium1.iff")

object_building_poi_shared_tatooine_plaguevictim_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_plaguevictim_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 103376874
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_plaguevictim_large1, "object/building/poi/shared_tatooine_plaguevictim_large1.iff")

object_building_poi_shared_tatooine_plaguevictim_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_plaguevictim_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3711881085
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_plaguevictim_large2, "object/building/poi/shared_tatooine_plaguevictim_large2.iff")

object_building_poi_shared_tatooine_plaguevictim_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_plaguevictim_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3043651035
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_plaguevictim_medium, "object/building/poi/shared_tatooine_plaguevictim_medium.iff")

object_building_poi_shared_tatooine_prison_break = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_prison_break.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1155349866
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_prison_break, "object/building/poi/shared_tatooine_prison_break.iff")

object_building_poi_shared_tatooine_rodianhunter_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_rodianhunter_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3108734198
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_rodianhunter_large1, "object/building/poi/shared_tatooine_rodianhunter_large1.iff")

object_building_poi_shared_tatooine_rodianhunter_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_rodianhunter_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1650207841
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_rodianhunter_large2, "object/building/poi/shared_tatooine_rodianhunter_large2.iff")

object_building_poi_shared_tatooine_rodianhunter_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_rodianhunter_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 168332999
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_rodianhunter_medium, "object/building/poi/shared_tatooine_rodianhunter_medium.iff")

object_building_poi_shared_tatooine_slaver_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_slaver_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 864649654
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_slaver_large1, "object/building/poi/shared_tatooine_slaver_large1.iff")

object_building_poi_shared_tatooine_slaver_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_slaver_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3902679329
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_slaver_large2, "object/building/poi/shared_tatooine_slaver_large2.iff")

object_building_poi_shared_tatooine_slaver_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_slaver_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2710785708
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_slaver_large3, "object/building/poi/shared_tatooine_slaver_large3.iff")

object_building_poi_shared_tatooine_slaver_large4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_slaver_large4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1517315512
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_slaver_large4, "object/building/poi/shared_tatooine_slaver_large4.iff")

object_building_poi_shared_tatooine_slaver_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_slaver_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2160757639
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_slaver_medium, "object/building/poi/shared_tatooine_slaver_medium.iff")

object_building_poi_shared_tatooine_slaver_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_slaver_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2160290714
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_slaver_medium2, "object/building/poi/shared_tatooine_slaver_medium2.iff")

object_building_poi_shared_tatooine_spicefiend_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_spicefiend_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2850462148
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_spicefiend_large1, "object/building/poi/shared_tatooine_spicefiend_large1.iff")

object_building_poi_shared_tatooine_spicefiend_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_spicefiend_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1928409427
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_spicefiend_large2, "object/building/poi/shared_tatooine_spicefiend_large2.iff")

object_building_poi_shared_tatooine_spicefiend_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_spicefiend_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1006393054
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_spicefiend_large3, "object/building/poi/shared_tatooine_spicefiend_large3.iff")

object_building_poi_shared_tatooine_spicefiend_large4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_spicefiend_large4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3223289290
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_spicefiend_large4, "object/building/poi/shared_tatooine_spicefiend_large4.iff")

object_building_poi_shared_tatooine_spicefiend_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_spicefiend_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 447058933
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_spicefiend_medium, "object/building/poi/shared_tatooine_spicefiend_medium.iff")

object_building_poi_shared_tatooine_spicefiend_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_spicefiend_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3847025874
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_spicefiend_medium2, "object/building/poi/shared_tatooine_spicefiend_medium2.iff")

object_building_poi_shared_tatooine_swoop_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_swoop_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1230309351
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_swoop_large1, "object/building/poi/shared_tatooine_swoop_large1.iff")

object_building_poi_shared_tatooine_swoop_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_swoop_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2453843824
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_swoop_large2, "object/building/poi/shared_tatooine_swoop_large2.iff")

object_building_poi_shared_tatooine_swoop_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_swoop_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3679439101
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_swoop_large3, "object/building/poi/shared_tatooine_swoop_large3.iff")

object_building_poi_shared_tatooine_swoop_large4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_swoop_large4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 548201449
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_swoop_large4, "object/building/poi/shared_tatooine_swoop_large4.iff")

object_building_poi_shared_tatooine_swoop_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_swoop_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4195749334
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_swoop_medium, "object/building/poi/shared_tatooine_swoop_medium.iff")

object_building_poi_shared_tatooine_swoop_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_swoop_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2474373547
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_swoop_medium2, "object/building/poi/shared_tatooine_swoop_medium2.iff")

object_building_poi_shared_tatooine_tuskenbantha_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_tuskenbantha_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 70977104
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_tuskenbantha_large1, "object/building/poi/shared_tatooine_tuskenbantha_large1.iff")

object_building_poi_shared_tatooine_tuskenbantha_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_tuskenbantha_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3744247495
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_tuskenbantha_large2, "object/building/poi/shared_tatooine_tuskenbantha_large2.iff")

object_building_poi_shared_tatooine_tuskenbantha_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_tuskenbantha_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3078098017
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_tuskenbantha_medium, "object/building/poi/shared_tatooine_tuskenbantha_medium.iff")

object_building_poi_shared_tatooine_tuskenwar_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_tuskenwar_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4071159081
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_tuskenwar_large1, "object/building/poi/shared_tatooine_tuskenwar_large1.iff")

object_building_poi_shared_tatooine_tuskenwar_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_tuskenwar_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 700407230
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_tuskenwar_large2, "object/building/poi/shared_tatooine_tuskenwar_large2.iff")

object_building_poi_shared_tatooine_tuskenwar_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_tuskenwar_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1622293043
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_tuskenwar_large3, "object/building/poi/shared_tatooine_tuskenwar_large3.iff")

object_building_poi_shared_tatooine_tuskenwar_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_tuskenwar_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1105985304
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_tuskenwar_medium, "object/building/poi/shared_tatooine_tuskenwar_medium.iff")

object_building_poi_shared_tatooine_valariangang_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_valariangang_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3919757322
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_valariangang_large1, "object/building/poi/shared_tatooine_valariangang_large1.iff")

object_building_poi_shared_tatooine_valariangang_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_valariangang_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 850749597
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_valariangang_large2, "object/building/poi/shared_tatooine_valariangang_large2.iff")

object_building_poi_shared_tatooine_valariangang_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_valariangang_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1524746811
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_valariangang_medium, "object/building/poi/shared_tatooine_valariangang_medium.iff")

object_building_poi_shared_tatooine_valariantrader_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_valariantrader_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2925334203
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_valariantrader_large1, "object/building/poi/shared_tatooine_valariantrader_large1.iff")

object_building_poi_shared_tatooine_valariantrader_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_valariantrader_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1967826476
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_valariantrader_large2, "object/building/poi/shared_tatooine_valariantrader_large2.iff")

object_building_poi_shared_tatooine_valariantrader_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_valariantrader_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 488506506
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_valariantrader_medium, "object/building/poi/shared_tatooine_valariantrader_medium.iff")

object_building_poi_shared_tatooine_village_medium_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_village_medium_1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1488043728
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_village_medium_1, "object/building/poi/shared_tatooine_village_medium_1.iff")

object_building_poi_shared_tatooine_village_medium_3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_village_medium_3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3400233418
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_village_medium_3, "object/building/poi/shared_tatooine_village_medium_3.iff")

object_building_poi_shared_tatooine_weequayzealots_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_weequayzealots_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 749133500
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_weequayzealots_large1, "object/building/poi/shared_tatooine_weequayzealots_large1.iff")

object_building_poi_shared_tatooine_weequayzealots_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_weequayzealots_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4155602475
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_weequayzealots_large2, "object/building/poi/shared_tatooine_weequayzealots_large2.iff")

object_building_poi_shared_tatooine_weequayzealots_medium = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_weequayzealots_medium.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2682639501
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_weequayzealots_medium, "object/building/poi/shared_tatooine_weequayzealots_medium.iff")

object_building_poi_shared_tatooine_weequayzealots_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_tatooine_weequayzealots_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3686926167
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_tatooine_weequayzealots_medium2, "object/building/poi/shared_tatooine_weequayzealots_medium2.iff")

object_building_poi_shared_yavin4_abandoned_rebel_camp_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_abandoned_rebel_camp_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3922111839
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_abandoned_rebel_camp_large1, "object/building/poi/shared_yavin4_abandoned_rebel_camp_large1.iff")

object_building_poi_shared_yavin4_abandoned_rebel_camp_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_abandoned_rebel_camp_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 852559304
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_abandoned_rebel_camp_large2, "object/building/poi/shared_yavin4_abandoned_rebel_camp_large2.iff")

object_building_poi_shared_yavin4_abandoned_rebel_camp_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_abandoned_rebel_camp_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2078040645
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_abandoned_rebel_camp_large3, "object/building/poi/shared_yavin4_abandoned_rebel_camp_large3.iff")

object_building_poi_shared_yavin4_abandoned_rebel_camp_medium1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_abandoned_rebel_camp_medium1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 719959858
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_abandoned_rebel_camp_medium1, "object/building/poi/shared_yavin4_abandoned_rebel_camp_medium1.iff")

object_building_poi_shared_yavin4_abandoned_rebel_camp_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_abandoned_rebel_camp_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4059963301
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_abandoned_rebel_camp_medium2, "object/building/poi/shared_yavin4_abandoned_rebel_camp_medium2.iff")

object_building_poi_shared_yavin4_abandoned_rebel_camp_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_abandoned_rebel_camp_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 895786771
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_abandoned_rebel_camp_small1, "object/building/poi/shared_yavin4_abandoned_rebel_camp_small1.iff")

object_building_poi_shared_yavin4_abandoned_rebel_camp_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_abandoned_rebel_camp_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4000528260
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_abandoned_rebel_camp_small2, "object/building/poi/shared_yavin4_abandoned_rebel_camp_small2.iff")

object_building_poi_shared_yavin4_hutt_scavenger_camp_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_hutt_scavenger_camp_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1405724823
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_hutt_scavenger_camp_large1, "object/building/poi/shared_yavin4_hutt_scavenger_camp_large1.iff")

object_building_poi_shared_yavin4_hutt_scavenger_camp_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_hutt_scavenger_camp_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2296250368
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_hutt_scavenger_camp_large2, "object/building/poi/shared_yavin4_hutt_scavenger_camp_large2.iff")

object_building_poi_shared_yavin4_hutt_scavenger_camp_medium1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_hutt_scavenger_camp_medium1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3076007066
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_hutt_scavenger_camp_medium1, "object/building/poi/shared_yavin4_hutt_scavenger_camp_medium1.iff")

object_building_poi_shared_yavin4_hutt_scavenger_camp_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_hutt_scavenger_camp_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1817152525
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_hutt_scavenger_camp_medium2, "object/building/poi/shared_yavin4_hutt_scavenger_camp_medium2.iff")

object_building_poi_shared_yavin4_hutt_scavenger_camp_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_hutt_scavenger_camp_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2406193883
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_hutt_scavenger_camp_small1, "object/building/poi/shared_yavin4_hutt_scavenger_camp_small1.iff")

object_building_poi_shared_yavin4_hutt_scavenger_camp_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_hutt_scavenger_camp_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1417425484
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_hutt_scavenger_camp_small2, "object/building/poi/shared_yavin4_hutt_scavenger_camp_small2.iff")

object_building_poi_shared_yavin4_imperial_patrol_camp_large1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_imperial_patrol_camp_large1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1421675238
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_imperial_patrol_camp_large1, "object/building/poi/shared_yavin4_imperial_patrol_camp_large1.iff")

object_building_poi_shared_yavin4_imperial_patrol_camp_large2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_imperial_patrol_camp_large2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2410324593
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_imperial_patrol_camp_large2, "object/building/poi/shared_yavin4_imperial_patrol_camp_large2.iff")

object_building_poi_shared_yavin4_imperial_patrol_camp_large3 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_imperial_patrol_camp_large3.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3332883964
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_imperial_patrol_camp_large3, "object/building/poi/shared_yavin4_imperial_patrol_camp_large3.iff")

object_building_poi_shared_yavin4_imperial_patrol_camp_large4 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_imperial_patrol_camp_large4.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1027927784
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_imperial_patrol_camp_large4, "object/building/poi/shared_yavin4_imperial_patrol_camp_large4.iff")

object_building_poi_shared_yavin4_imperial_patrol_medium1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_imperial_patrol_medium1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 989401762
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_imperial_patrol_medium1, "object/building/poi/shared_yavin4_imperial_patrol_medium1.iff")

object_building_poi_shared_yavin4_imperial_patrol_medium2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_imperial_patrol_medium2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_medium.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3790518837
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_imperial_patrol_medium2, "object/building/poi/shared_yavin4_imperial_patrol_medium2.iff")

object_building_poi_shared_yavin4_imperial_patrol_small1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_imperial_patrol_small1.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 94420443
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_imperial_patrol_small1, "object/building/poi/shared_yavin4_imperial_patrol_small1.iff")

object_building_poi_shared_yavin4_imperial_patrol_small2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/poi/shared_yavin4_imperial_patrol_small2.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:base_poi_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_small.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3736540492
}

ObjectTemplates:addClientTemplate(object_building_poi_shared_yavin4_imperial_patrol_small2, "object/building/poi/shared_yavin4_imperial_patrol_small2.iff")
