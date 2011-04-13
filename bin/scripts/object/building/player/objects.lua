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


object_building_player_shared_construction_structure = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/thm_tato_imprv_street_sign_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8203,
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

	gameObjectType = 8203,

	locationReservationRadius = 0,
	lookAtText = "@player_structure:temporary_structure",

	noBuildRadius = 0,

	objectName = "@player_structure:temporary_structure",
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

	clientObjectCRC = 4003827328
}

ObjectTemplates:addClientTemplate(object_building_player_shared_construction_structure, "object/building/player/shared_construction_structure.iff")

object_building_player_shared_player_garage_corellia_style_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_corl_garage_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_garage.cdf",
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

	detailedDescription = "@building_detail:ply_corellia_garage_s01",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:ply_corellia_garage_s01",

	noBuildRadius = 0,

	objectName = "@building_name:ply_corellia_garage_s01",
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
	structureFootprintFileName = "footprint/building/player/shared_player_garage_corellia_style_01.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3533693421
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_garage_corellia_style_01, "object/building/player/shared_player_garage_corellia_style_01.iff")

object_building_player_shared_player_garage_naboo_style_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garage_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_garage.cdf",
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

	detailedDescription = "@building_detail:ply_naboo_garage_s01",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:ply_naboo_garage_s01",

	noBuildRadius = 0,

	objectName = "@building_name:ply_naboo_garage_s01",
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
	structureFootprintFileName = "footprint/building/player/shared_player_garage_naboo_style_01.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2162635930
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_garage_naboo_style_01, "object/building/player/shared_player_garage_naboo_style_01.iff")

object_building_player_shared_player_garage_tatooine_style_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garage_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_garage.cdf",
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

	detailedDescription = "@building_detail:ply_tatooine_garage_s01",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:ply_tatooine_garage_s01",

	noBuildRadius = 0,

	objectName = "@building_name:ply_tatooine_garage_s01",
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
	structureFootprintFileName = "footprint/building/player/shared_player_garage_tatooine_style_01.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2075679353
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_garage_tatooine_style_01, "object/building/player/shared_player_garage_tatooine_style_01.iff")

object_building_player_shared_player_guildhall_corellia_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_association_hall.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_name:association_hall_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:association_hall_civilian_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:association_hall_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_assoc_hall_civ_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_guildhall_corellia_style_01.sfp",
	surfaceType = 1,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 17,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1038468412
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_guildhall_corellia_style_01, "object/building/player/shared_player_guildhall_corellia_style_01.iff")

object_building_player_shared_player_guildhall_generic_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_large_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_name:association_hall_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:association_hall_general",

	noBuildRadius = 0,

	objectName = "@building_name:association_hall_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_all_assoc_hall_civ_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_guildhall_corellia_style_01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 17,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1861851362
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_guildhall_generic_style_01, "object/building/player/shared_player_guildhall_generic_style_01.iff")

object_building_player_shared_player_guildhall_naboo_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_association_hall.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_name:association_hall_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:association_hall_civilian_naboo",

	noBuildRadius = 0,

	objectName = "@building_name:association_hall_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_nboo_assoc_hall_civ_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_guildhall_naboo_style_01.sfp",
	surfaceType = 3,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 17,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3197026082
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_guildhall_naboo_style_01, "object/building/player/shared_player_guildhall_naboo_style_01.iff")

object_building_player_shared_player_guildhall_tatooine_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
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

	detailedDescription = "@building_name:association_hall_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_housing",

	noBuildRadius = 0,

	objectName = "@building_name:association_hall_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_tato_assoc_hall_civ_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_guildhall_tatooine_style_01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 17,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2495774376
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_guildhall_tatooine_style_01, "object/building/player/shared_player_guildhall_tatooine_style_01.iff")

object_building_player_shared_player_guildhall_tatooine_style_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_large_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_name:association_hall_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_tatt_style01_guildhall",

	noBuildRadius = 0,

	objectName = "@building_name:association_hall_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_tato_assoc_hall_civ_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_guildhall_tatooine_style_02.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 21,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1339414079
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_guildhall_tatooine_style_02, "object/building/player/shared_player_guildhall_tatooine_style_02.iff")

object_building_player_shared_player_house_corellia_large_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_large_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_corellia_large_style_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_corellia_large_style_1",

	noBuildRadius = 0,

	objectName = "@building_name:housing_corellia_large_style_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_house_lg_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_corellia_large_style_01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 13,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2427663942
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_corellia_large_style_01, "object/building/player/shared_player_house_corellia_large_style_01.iff")

object_building_player_shared_player_house_corellia_large_style_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_large_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_corellia_large_style_2",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_corellia_large_style_2",

	noBuildRadius = 0,

	objectName = "@building_name:housing_corellia_large_style_2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_house_lg_s02_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_corellia_large_style_02.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1269079761
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_corellia_large_style_02, "object/building/player/shared_player_house_corellia_large_style_02.iff")

object_building_player_shared_player_house_corellia_medium_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_medium_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_corellia_medium_style_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_corellia_medium_style_1",

	noBuildRadius = 0,

	objectName = "@building_name:housing_corellia_medium_style_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_house_m_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_corellia_medium_style_01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 4,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4245590836
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_corellia_medium_style_01, "object/building/player/shared_player_house_corellia_medium_style_01.iff")

object_building_player_shared_player_house_corellia_medium_style_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_medium_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_corellia_medium_style_2",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_corellia_medium_style_2",

	noBuildRadius = 0,

	objectName = "@building_name:housing_corellia_medium_style_2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_house_m_s02_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_corellia_medium_style_02.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 3,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 639187875
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_corellia_medium_style_02, "object/building/player/shared_player_house_corellia_medium_style_02.iff")

object_building_player_shared_player_house_corellia_small_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_small_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_corellia_small_style_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_corellia_small_style_1",

	noBuildRadius = 0,

	objectName = "@building_name:housing_corellia_small_style_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_house_sm_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_corellia_small_style_01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 4,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2963259888
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_corellia_small_style_01, "object/building/player/shared_player_house_corellia_small_style_01.iff")

object_building_player_shared_player_house_corellia_small_style_01_floorplan_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_small_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_corellia_small_style_1_floorplan_2",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_corellia_small_style_1_floorplan_2",

	noBuildRadius = 0,

	objectName = "@building_name:housing_corellia_small_style_1_floorplan_2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_house_sm_s01_fp2.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_corellia_small_style_01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 4,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4102677864
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_corellia_small_style_01_floorplan_02, "object/building/player/shared_player_house_corellia_small_style_01_floorplan_02.iff")

object_building_player_shared_player_house_corellia_small_style_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_small_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_corellia_small_style_2",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_corellia_small_style_2",

	noBuildRadius = 0,

	objectName = "@building_name:housing_corellia_small_style_2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_house_sm_s02_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_corellia_small_style_02.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 3,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1804101991
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_corellia_small_style_02, "object/building/player/shared_player_house_corellia_small_style_02.iff")

object_building_player_shared_player_house_corellia_small_style_02_floorplan_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_small_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_corellia_small_style_2_floorplan_2",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_corellia_small_style_2_floorplan_2",

	noBuildRadius = 0,

	objectName = "@building_name:housing_corellia_small_style_2_floorplan_2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_house_sm_s02_fp2.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_corellia_small_style_02.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 2,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1944093248
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_corellia_small_style_02_floorplan_02, "object/building/player/shared_player_house_corellia_small_style_02_floorplan_02.iff")

object_building_player_shared_player_house_generic_large_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_large_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_general_large_style_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_general_large_style_1",

	noBuildRadius = 0,

	objectName = "@building_name:housing_general_large_style_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_all_house_lg_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_generic_large_style_01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 13,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2966981875
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_generic_large_style_01, "object/building/player/shared_player_house_generic_large_style_01.iff")

object_building_player_shared_player_house_generic_large_style_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_large_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_general_large_style_2",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_general_large_style_2",

	noBuildRadius = 0,

	objectName = "@building_name:housing_general_large_style_2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_all_house_lg_s02_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_generic_large_style_02.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1808737380
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_generic_large_style_02, "object/building/player/shared_player_house_generic_large_style_02.iff")

object_building_player_shared_player_house_generic_medium_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_medium_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_general_medium_style_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_general_medium_style_1",

	noBuildRadius = 0,

	objectName = "@building_name:housing_general_medium_style_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_all_house_m_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_generic_medium_style_01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 4,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 244814036
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_generic_medium_style_01, "object/building/player/shared_player_house_generic_medium_style_01.iff")

object_building_player_shared_player_house_generic_medium_style_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_medium_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_general_medium_style_2",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_general_medium_style_2",

	noBuildRadius = 0,

	objectName = "@building_name:housing_general_medium_style_2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_all_house_m_s02_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_generic_medium_style_01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 3,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3581950019
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_generic_medium_style_02, "object/building/player/shared_player_house_generic_medium_style_02.iff")

object_building_player_shared_player_house_generic_small_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_small_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_general_small_style_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_general_small_style_1",

	noBuildRadius = 0,

	objectName = "@building_name:housing_general_small_style_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_all_house_sm_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_generic_small_style_01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 4,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2431941445
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_generic_small_style_01, "object/building/player/shared_player_house_generic_small_style_01.iff")

object_building_player_shared_player_house_generic_small_style_01_floorplan_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_small_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_general_small_style_1_floorplan_2",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_general_small_style_1_floorplan_2",

	noBuildRadius = 0,

	objectName = "@building_name:housing_general_small_style_1_floorplan_2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_all_house_sm_s01_fp2.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_generic_small_style_01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 4,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4015966289
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_generic_small_style_01_floorplan_02, "object/building/player/shared_player_house_generic_small_style_01_floorplan_02.iff")

object_building_player_shared_player_house_generic_small_style_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_small_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_general_small_style_2",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_general_small_style_2",

	noBuildRadius = 0,

	objectName = "@building_name:housing_general_small_style_2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_all_house_sm_s02_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_generic_small_style_02.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 3,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1273222098
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_generic_small_style_02, "object/building/player/shared_player_house_generic_small_style_02.iff")

object_building_player_shared_player_house_generic_small_style_02_floorplan_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_small_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_general_small_style_2_floorplan_2",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_general_small_style_2_floorplan_2",

	noBuildRadius = 0,

	objectName = "@building_name:housing_general_small_style_2_floorplan_2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_all_house_sm_s02_fp2.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_generic_small_style_02.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 2,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1748479865
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_generic_small_style_02_floorplan_02, "object/building/player/shared_player_house_generic_small_style_02_floorplan_02.iff")

object_building_player_shared_player_house_naboo_large_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 36,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_large_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_name:housing_naboo_large",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_naboo_style_1",

	noBuildRadius = 0,

	objectName = "@building_name:housing_naboo_large",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_nboo_house_lg_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_naboo_large_style_01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 14,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1926074883
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_naboo_large_style_01, "object/building/player/shared_player_house_naboo_large_style_01.iff")

object_building_player_shared_player_house_naboo_medium_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 36,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_medium_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_name:housing_naboo_medium",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_naboo_style_1",

	noBuildRadius = 0,

	objectName = "@building_name:housing_naboo_medium",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_nboo_house_m_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_naboo_medium_style_01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 7,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1333906211
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_naboo_medium_style_01, "object/building/player/shared_player_house_naboo_medium_style_01.iff")

object_building_player_shared_player_house_naboo_small_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 36,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_small_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_name:housing_naboo_small",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_naboo_style_1",

	noBuildRadius = 0,

	objectName = "@building_name:housing_naboo_small",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_nboo_house_sm_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_naboo_small_style_01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 3,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1390503349
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_naboo_small_style_01, "object/building/player/shared_player_house_naboo_small_style_01.iff")

object_building_player_shared_player_house_naboo_small_style_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 36,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_small_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_name:housing_naboo_small",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_naboo_style_1",

	noBuildRadius = 0,

	objectName = "@building_name:housing_naboo_small",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_nboo_house_sm_s02_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_naboo_small_style_02.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 4,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2314652962
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_naboo_small_style_02, "object/building/player/shared_player_house_naboo_small_style_02.iff")

object_building_player_shared_player_house_tatooine_large_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 36,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_large_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_tatt_style01_large",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_tatt_style01_large",

	noBuildRadius = 0,

	objectName = "@building_name:housing_tatt_style01_large",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_tato_house_lg_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_tatooine_large_style_01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3018624136
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_tatooine_large_style_01, "object/building/player/shared_player_house_tatooine_large_style_01.iff")

object_building_player_shared_player_house_tatooine_medium_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 36,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_medium_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_tatt_style01_med",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_tatt_style01_med",

	noBuildRadius = 0,

	objectName = "@building_name:housing_tatt_style01_med",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_tato_house_m_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_tatooine_medium_style_01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 8,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 936693005
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_tatooine_medium_style_01, "object/building/player/shared_player_house_tatooine_medium_style_01.iff")

object_building_player_shared_player_house_tatooine_small_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 36,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_small_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_tatt_style01_small",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_tatt_style01_small",

	noBuildRadius = 0,

	objectName = "@building_name:housing_tatt_style01_small",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_tato_house_sm_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_tatooine_small_style_01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 3,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2478865214
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_tatooine_small_style_01, "object/building/player/shared_player_house_tatooine_small_style_01.iff")

object_building_player_shared_player_house_tatooine_small_style_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 36,
	clientDataFile = "clientdata/building/shared_player_house_tatooine_small_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:housing_tatt_style01_small",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_tatt_style01_small",

	noBuildRadius = 0,

	objectName = "@building_name:housing_tatt_style01_small",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_tato_house_sm_s02_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_tatooine_small_style_02.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 3,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1222103977
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_house_tatooine_small_style_02, "object/building/player/shared_player_house_tatooine_small_style_02.iff")

object_building_player_shared_player_merchant_tent_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 36,
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

	detailedDescription = "@building_detail:merchant_tent",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:merchant_tent",

	noBuildRadius = 0,

	objectName = "@building_name:merchant_tent",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_tato_merchant_tent_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_merchant_tent.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 1,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2671747310
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_merchant_tent_style_01, "object/building/player/shared_player_merchant_tent_style_01.iff")

object_building_player_shared_player_merchant_tent_style_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 36,
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

	detailedDescription = "@building_detail:merchant_tent",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:merchant_tent",

	noBuildRadius = 0,

	objectName = "@building_name:merchant_tent",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_merchant_tent_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_merchant_tent.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 1,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1143474297
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_merchant_tent_style_02, "object/building/player/shared_player_merchant_tent_style_02.iff")

object_building_player_shared_player_merchant_tent_style_03 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 36,
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

	detailedDescription = "@building_detail:merchant_tent",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:merchant_tent",

	noBuildRadius = 0,

	objectName = "@building_name:merchant_tent",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_nboo_merchant_tent_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_merchant_tent.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 1,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 220557300
}

ObjectTemplates:addClientTemplate(object_building_player_shared_player_merchant_tent_style_03, "object/building/player/shared_player_merchant_tent_style_03.iff")
