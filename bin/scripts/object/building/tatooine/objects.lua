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


object_building_tatooine_shared_association_hall_civilian_tatooine = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:association_hall_civilian_tatooine",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:association_hall_civilian_tatooine",

	noBuildRadius = 0,

	objectName = "@building_name:association_hall_civilian_tatooine",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_assoc_hall_civ_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 17,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3483054122
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_association_hall_civilian_tatooine, "object/building/tatooine/shared_association_hall_civilian_tatooine.iff")

object_building_tatooine_shared_association_hall_civilian_tatooine_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:association_hall_civilian_tatooine2",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:association_hall_civilian_tatooine2",

	noBuildRadius = 0,

	objectName = "@building_name:association_hall_civilian_tatooine2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_assoc_hall_civ_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 21,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3781643094
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_association_hall_civilian_tatooine_02, "object/building/tatooine/shared_association_hall_civilian_tatooine_02.iff")

object_building_tatooine_shared_bank_tatooine = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/mun_tato_bank_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/building/shared_bank.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:bank",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:bank",

	noBuildRadius = 0,

	objectName = "@building_name:bank",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 533531985
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_bank_tatooine, "object/building/tatooine/shared_bank_tatooine.iff")

object_building_tatooine_shared_cantina_tatooine = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/building/shared_tatooine_cantina.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:cantina_general",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_cantina_mos_eisley_tatooine.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:cantina_general",

	noBuildRadius = 0,

	objectName = "@building_name:cantina_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_cantina.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 15,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1072782602
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_cantina_tatooine, "object/building/tatooine/shared_cantina_tatooine.iff")

object_building_tatooine_shared_capitol_tatooine = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:capitol_tatooine",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:capitol_tatooine",

	noBuildRadius = 0,

	objectName = "@building_name:capitol_tatooine",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_tato_capitol_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1064279242
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_capitol_tatooine, "object/building/tatooine/shared_capitol_tatooine.iff")

object_building_tatooine_shared_cave_tatooine_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:base_cave",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/cave01.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_cave_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 20,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3062222401
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_cave_tatooine_style_01, "object/building/tatooine/shared_cave_tatooine_style_01.iff")

object_building_tatooine_shared_cave_tatooine_style_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:base_cave",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/cave02.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_cave_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 17,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1838311126
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_cave_tatooine_style_02, "object/building/tatooine/shared_cave_tatooine_style_02.iff")

object_building_tatooine_shared_cloning_facility_tatooine = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/building/shared_cloning.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:cloning_facility_tatooine",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_cloning_facility.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cloning_facility",

	noBuildRadius = 0,

	objectName = "@building_name:cloning_facility_tatooine",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_tato_cloning_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 749651154
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_cloning_facility_tatooine, "object/building/tatooine/shared_cloning_facility_tatooine.iff")

object_building_tatooine_shared_cloning_facility_tatooine_small = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/building/shared_cloning.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:cloning_facility_tatooine",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:cloning_facility_tatooine",

	noBuildRadius = 0,

	objectName = "@building_name:cloning_facility_tatooine",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_house_sml_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1267595977
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_cloning_facility_tatooine_small, "object/building/tatooine/shared_cloning_facility_tatooine_small.iff")

object_building_tatooine_shared_filler_building_block_64x16_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_tato_block_bldg_64x16_s01.apt",
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

	detailedDescription = "@building_detail:filler_building_tatt_style01_10",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_tatt_style01_10",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_tatt_style01_10",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1977133003
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_filler_building_block_64x16_style_01, "object/building/tatooine/shared_filler_building_block_64x16_style_01.iff")

object_building_tatooine_shared_filler_building_block_64x16_style_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_tato_block_bldg_64x16_s02.apt",
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

	detailedDescription = "@building_detail:filler_building_tatt_style01_10",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_tatt_style01_10",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_tatt_style01_10",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2932805468
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_filler_building_block_64x16_style_02, "object/building/tatooine/shared_filler_building_block_64x16_style_02.iff")

object_building_tatooine_shared_filler_building_block_64x32_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_tato_block_bldg_64x32_s01.apt",
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

	detailedDescription = "@building_detail:filler_building_tatt_style01_10",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_tatt_style01_10",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_tatt_style01_10",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3491257899
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_filler_building_block_64x32_style_01, "object/building/tatooine/shared_filler_building_block_64x32_style_01.iff")

object_building_tatooine_shared_filler_building_block_64x32_style_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_tato_block_bldg_64x32_s02.apt",
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

	detailedDescription = "@building_detail:filler_building_tatt_style01_10",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_tatt_style01_10",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_tatt_style01_10",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 185595580
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_filler_building_block_64x32_style_02, "object/building/tatooine/shared_filler_building_block_64x32_style_02.iff")

object_building_tatooine_shared_filler_building_slave_quarters_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_tato_block_bldg_32x16_s03.apt",
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

	detailedDescription = "@building_detail:filler_building_tatt_style01_10",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_tatt_style01_10",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_tatt_style01_10",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3086665699
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_filler_building_slave_quarters_style_01, "object/building/tatooine/shared_filler_building_slave_quarters_style_01.iff")

object_building_tatooine_shared_filler_building_tatt_style01_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_tato_imprv_building_s01.apt",
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

	detailedDescription = "@building_detail:filler_building_tatt_style01_01",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_tatt_style01_01",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_tatt_style01_01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2338066597
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_filler_building_tatt_style01_01, "object/building/tatooine/shared_filler_building_tatt_style01_01.iff")

object_building_tatooine_shared_filler_building_tatt_style01_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_tato_imprv_building_s02.apt",
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

	detailedDescription = "@building_detail:filler_building_tatt_style01_02",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_tatt_style01_02",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_tatt_style01_02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1347139634
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_filler_building_tatt_style01_02, "object/building/tatooine/shared_filler_building_tatt_style01_02.iff")

object_building_tatooine_shared_filler_building_tatt_style01_03 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_tato_imprv_building_s03.apt",
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

	detailedDescription = "@building_detail:filler_building_tatt_style01_03",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_tatt_style01_03",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_tatt_style01_03",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 424075199
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_filler_building_tatt_style01_03, "object/building/tatooine/shared_filler_building_tatt_style01_03.iff")

object_building_tatooine_shared_filler_building_tatt_style01_04 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_tato_imprv_building_s04.apt",
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

	detailedDescription = "@building_detail:filler_building_tatt_style01_04",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_tatt_style01_04",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_tatt_style01_04",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3802526891
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_filler_building_tatt_style01_04, "object/building/tatooine/shared_filler_building_tatt_style01_04.iff")

object_building_tatooine_shared_filler_building_tatt_style01_05 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_tato_imprv_building_s05.apt",
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

	detailedDescription = "@building_detail:filler_building_tatt_style01_05",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_tatt_style01_05",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_tatt_style01_05",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2879951654
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_filler_building_tatt_style01_05, "object/building/tatooine/shared_filler_building_tatt_style01_05.iff")

object_building_tatooine_shared_filler_building_tatt_style01_06 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_tato_imprv_building_s06.apt",
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

	detailedDescription = "@building_detail:filler_building_tatt_style01_06",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_tatt_style01_06",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_tatt_style01_06",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1891580849
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_filler_building_tatt_style01_06, "object/building/tatooine/shared_filler_building_tatt_style01_06.iff")

object_building_tatooine_shared_filler_building_tatt_style01_07 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_tato_imprv_building_s07.apt",
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

	detailedDescription = "@building_detail:filler_building_tatt_style01_07",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_tatt_style01_07",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_tatt_style01_07",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 967990332
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_filler_building_tatt_style01_07, "object/building/tatooine/shared_filler_building_tatt_style01_07.iff")

object_building_tatooine_shared_filler_building_tatt_style01_08 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_tato_imprv_building_s08.apt",
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

	detailedDescription = "@building_detail:filler_building_tatt_style01_08",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_tatt_style01_08",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_tatt_style01_08",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2209902638
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_filler_building_tatt_style01_08, "object/building/tatooine/shared_filler_building_tatt_style01_08.iff")

object_building_tatooine_shared_filler_building_tatt_style01_09 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_tato_imprv_building_s09.apt",
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

	detailedDescription = "@building_detail:filler_building_tatt_style01_09",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_tatt_style01_09",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_tatt_style01_09",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3400865699
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_filler_building_tatt_style01_09, "object/building/tatooine/shared_filler_building_tatt_style01_09.iff")

object_building_tatooine_shared_filler_building_tatt_style01_10 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_tato_imprv_building_s10.apt",
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

	detailedDescription = "@building_detail:filler_building_tatt_style01_10",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_tatt_style01_10",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_tatt_style01_10",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3648617040
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_filler_building_tatt_style01_10, "object/building/tatooine/shared_filler_building_tatt_style01_10.iff")

object_building_tatooine_shared_filler_building_tatt_style01_11 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_tato_imprv_building_s11.apt",
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

	detailedDescription = "@building_detail:filler_building_tatt_style01_10",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_tatt_style01_10",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_tatt_style01_10",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2423528925
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_filler_building_tatt_style01_11, "object/building/tatooine/shared_filler_building_tatt_style01_11.iff")

object_building_tatooine_shared_fort_tusken = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:fort_tusken",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/fort_tusken.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:fort_tusken",

	noBuildRadius = 0,

	objectName = "@building_name:fort_tusken",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_fort_tusken.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 23,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1194412824
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_fort_tusken, "object/building/tatooine/shared_fort_tusken.iff")

object_building_tatooine_shared_guild_combat_tatooine_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/building/shared_guild_combat.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_guild",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_guild_combat_style_tatooine.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_guild",

	noBuildRadius = 0,

	objectName = "@building_name:guild_combat",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_tato_guild_combat_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1273926318
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_guild_combat_tatooine_style_01, "object/building/tatooine/shared_guild_combat_tatooine_style_01.iff")

object_building_tatooine_shared_guild_commerce_tatooine_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/building/shared_guild_combat.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_guild",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_guild_commerce_style_tatooine.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_guild",

	noBuildRadius = 0,

	objectName = "@building_name:guild_commerce",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_tato_guild_commerce_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 113904481
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_guild_commerce_tatooine_style_01, "object/building/tatooine/shared_guild_commerce_tatooine_style_01.iff")

object_building_tatooine_shared_guild_theater_tatooine_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:theater",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_guild_theatre_style_tatooine.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:theater",

	noBuildRadius = 0,

	objectName = "@building_name:theater",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_tato_guild_theater_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3289028168
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_guild_theater_tatooine_style_01, "object/building/tatooine/shared_guild_theater_tatooine_style_01.iff")

object_building_tatooine_shared_guild_university_tatooine_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/building/shared_guild_combat.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_guild",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_guild_university_style_tatooine.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_guild",

	noBuildRadius = 0,

	objectName = "@building_name:guild_university",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_tato_guild_university_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 970934772
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_guild_university_tatooine_style_01, "object/building/tatooine/shared_guild_university_tatooine_style_01.iff")

object_building_tatooine_shared_guild_university_tatooine_style_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/building/shared_guild_combat.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_guild",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/mos_entha_police_station.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_guild",

	noBuildRadius = 0,

	objectName = "@building_name:guild_university",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_tato_guild_university_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3804815715
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_guild_university_tatooine_style_02, "object/building/tatooine/shared_guild_university_tatooine_style_02.iff")

object_building_tatooine_shared_hospital_tatooine = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:hospital",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:hospital",

	noBuildRadius = 0,

	objectName = "@building_name:hospital",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_tato_hospital_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 14,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4066183619
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_hospital_tatooine, "object/building/tatooine/shared_hospital_tatooine.iff")

object_building_tatooine_shared_hospital_tatooine_s02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_bank.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:hospital",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_hospital_style_02.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:hospital",

	noBuildRadius = 0,

	objectName = "@building_name:hospital",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_tato_hospital_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 3,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2745462757
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_hospital_tatooine_s02, "object/building/tatooine/shared_hospital_tatooine_s02.iff")

object_building_tatooine_shared_hotel_tatooine_general = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/building/shared_hotel.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:hotel_tatooine_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:hotel_tatooine_general",

	noBuildRadius = 0,

	objectName = "@building_name:hotel_tatooine_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_tato_hotel_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 776066139
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_hotel_tatooine_general, "object/building/tatooine/shared_hotel_tatooine_general.iff")

object_building_tatooine_shared_hotel_tatooine_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/building/shared_hotel.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:hotel_tatooine_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:hotel_tatooine_general",

	noBuildRadius = 0,

	objectName = "@building_name:hotel_tatooine_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_tato_hotel_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4181798094
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_hotel_tatooine_style_01, "object/building/tatooine/shared_hotel_tatooine_style_01.iff")

object_building_tatooine_shared_housing_tatt_style01_large = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:housing_tatt_style01_large",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_tatt_style01_large",

	noBuildRadius = 0,

	objectName = "@building_name:housing_tatt_style01_large",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_assoc_hall_civ_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 21,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3970726045
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_housing_tatt_style01_large, "object/building/tatooine/shared_housing_tatt_style01_large.iff")

object_building_tatooine_shared_housing_tatt_style01_med = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:housing_tatt_style01_med",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_tatt_style01_med",

	noBuildRadius = 0,

	objectName = "@building_name:housing_tatt_style01_med",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_house_m_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 12,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2662523338
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_housing_tatt_style01_med, "object/building/tatooine/shared_housing_tatt_style01_med.iff")

object_building_tatooine_shared_housing_tatt_style01_small = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:housing_tatt_style01_small",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_tatt_style01_small",

	noBuildRadius = 0,

	objectName = "@building_name:housing_tatt_style01_small",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_house_sml_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3635932340
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_housing_tatt_style01_small, "object/building/tatooine/shared_housing_tatt_style01_small.iff")

object_building_tatooine_shared_housing_tatt_style02_large = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:housing_tatt_style01_large",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_tatt_style01_large",

	noBuildRadius = 0,

	objectName = "@building_name:housing_tatt_style01_large",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_assoc_hall_civ_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 21,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3801672984
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_housing_tatt_style02_large, "object/building/tatooine/shared_housing_tatt_style02_large.iff")

object_building_tatooine_shared_housing_tatt_style02_med = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:housing_tatt_style01_med",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_housing_tatt_wealthy_med.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_tatt_style01_med",

	noBuildRadius = 0,

	objectName = "@building_name:housing_tatt_style01_med",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_house_m_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 12,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2356282071
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_housing_tatt_style02_med, "object/building/tatooine/shared_housing_tatt_style02_med.iff")

object_building_tatooine_shared_housing_tatt_style02_small = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:housing_tatt_style01_small",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_tatt_style01_small",

	noBuildRadius = 0,

	objectName = "@building_name:housing_tatt_style01_small",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_house_sml_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3598940465
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_housing_tatt_style02_small, "object/building/tatooine/shared_housing_tatt_style02_small.iff")

object_building_tatooine_shared_housing_tatt_style03_large = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:housing_tatt_style01_large",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_tatt_style01_large",

	noBuildRadius = 0,

	objectName = "@building_name:housing_tatt_style01_large",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_assoc_hall_civ_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 21,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 456420086
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_housing_tatt_style03_large, "object/building/tatooine/shared_housing_tatt_style03_large.iff")

object_building_tatooine_shared_housing_tatt_style03_med = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:housing_tatt_style01_med",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_housing_tatt_wealthy_s01_med.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_tatt_style01_med",

	noBuildRadius = 0,

	objectName = "@building_name:housing_tatt_style01_med",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_house_m_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 12,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2121443505
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_housing_tatt_style03_med, "object/building/tatooine/shared_housing_tatt_style03_med.iff")

object_building_tatooine_shared_housing_tatt_style03_small = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:housing_tatt_style01_small",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_tatt_style01_small",

	noBuildRadius = 0,

	objectName = "@building_name:housing_tatt_style01_small",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_house_sml_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 791674591
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_housing_tatt_style03_small, "object/building/tatooine/shared_housing_tatt_style03_small.iff")

object_building_tatooine_shared_junkshop_watto = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:junkshop_watto",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:junkshop_watto",

	noBuildRadius = 0,

	objectName = "@building_name:junkshop_watto",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_watto_junkshop.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 3,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4014265599
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_junkshop_watto, "object/building/tatooine/shared_junkshop_watto.iff")

object_building_tatooine_shared_lair_environment_tatooine = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/defaultappearance.apt",
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

	detailedDescription = "@building_detail:filler_building_tatt_style01_10",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_tatt_style01_10",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_tatt_style01_10",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/lair_env_tatooine.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2616325223
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_lair_environment_tatooine, "object/building/tatooine/shared_lair_environment_tatooine.iff")

object_building_tatooine_shared_lucky_despot = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/building/shared_hotel.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:The Lucky Despot Hotel and Casino",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:Lucky Despot",

	noBuildRadius = 0,

	objectName = "@building_name:Lucky Despot Hotel and Casino",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_lucky_despot.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 1,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 32,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1100188829
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_lucky_despot, "object/building/tatooine/shared_lucky_despot.iff")

object_building_tatooine_shared_merchant_tent_tato_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:merchant_tent_tato_s01",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:merchant_tent_tato_s01",

	noBuildRadius = 0,

	objectName = "@building_name:merchant_tent_tato_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_tato_merchant_tent_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 1,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2745583203
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_merchant_tent_tato_s01, "object/building/tatooine/shared_merchant_tent_tato_s01.iff")

object_building_tatooine_shared_palace_tatooine_jabba = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:palace_tatooine_jabba",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/jabba_palace_interior.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:palace_tatooine_jabba",

	noBuildRadius = 0,

	objectName = "@building_name:palace_tatooine_jabba",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_tato_jabbas_palace.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 1,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 38,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4034000230
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_palace_tatooine_jabba, "object/building/tatooine/shared_palace_tatooine_jabba.iff")

object_building_tatooine_shared_parking_garage_tatooine_style_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/mun_tato_garage_s01_u01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/building/shared_garage.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:parking_garage_tatooine_style_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:parking_garage_tatooine_style_1",

	noBuildRadius = 0,

	objectName = "@building_name:parking_garage_tatooine_style_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2278884651
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_parking_garage_tatooine_style_1, "object/building/tatooine/shared_parking_garage_tatooine_style_1.iff")

object_building_tatooine_shared_poi_tato_farm_32x32_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/poi_tato_farm_32x32_s01.apt",
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

	detailedDescription = "@building_detail:poi_tato_farm_32x32_s01",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:poi_tato_farm_32x32_s01",

	noBuildRadius = 0,

	objectName = "@building_name:poi_tato_farm_32x32_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1014253665
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_poi_tato_farm_32x32_s01, "object/building/tatooine/shared_poi_tato_farm_32x32_s01.iff")

object_building_tatooine_shared_salon_tatooine = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 40,
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

	detailedDescription = "@building_detail:salon_tatooine",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_salon_style_tatooine.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:salon_tatooine",

	noBuildRadius = 0,

	objectName = "@building_name:salon_tatooine",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_tato_idesigner_tent_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 1,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 616531993
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_salon_tatooine, "object/building/tatooine/shared_salon_tatooine.iff")

object_building_tatooine_shared_shuttleport_tatooine = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/mun_tato_shuttleport_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/building/shared_shuttleport.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:shuttleport_tatooine",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:shuttleport_tatooine",

	noBuildRadius = 0,

	objectName = "@building_name:shuttleport_tatooine",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3505295527
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_shuttleport_tatooine, "object/building/tatooine/shared_shuttleport_tatooine.iff")

object_building_tatooine_shared_starport_tatooine = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
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

	detailedDescription = "@building_detail:starport_tatooine",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/starport_tatooine.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:starport_tatooine",

	noBuildRadius = 0,

	objectName = "@building_name:starport_tatooine",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_tato_starport_s01_u01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 16,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 351600928
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_starport_tatooine, "object/building/tatooine/shared_starport_tatooine.iff")

object_building_tatooine_shared_tower_jabbas_palace = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_tato_jabbas_palace_tower.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_bank.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:tower_jabbas_palace",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:tower_jabbas_palace",

	noBuildRadius = 0,

	objectName = "@building_name:tower_jabbas_palace",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2860552089
}

ObjectTemplates:addClientTemplate(object_building_tatooine_shared_tower_jabbas_palace, "object/building/tatooine/shared_tower_jabbas_palace.iff")
