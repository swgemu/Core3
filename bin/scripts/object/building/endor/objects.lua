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


object_building_endor_shared_endor_catwalk = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_village_tree_catwlk_s01.apt",
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

	detailedDescription = "@building_detail:base_filler_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_filler_building",

	noBuildRadius = 0,

	objectName = "@building_name:base_filler_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 3,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1092202767
}

ObjectTemplates:addClientTemplate(object_building_endor_shared_endor_catwalk, "object/building/endor/shared_endor_catwalk.iff")

object_building_endor_shared_endor_catwalk_cap = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_village_tree_catwlk_cap_s01.apt",
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

	detailedDescription = "@building_detail:base_filler_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_filler_building",

	noBuildRadius = 0,

	objectName = "@building_name:base_filler_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 3,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1451215471
}

ObjectTemplates:addClientTemplate(object_building_endor_shared_endor_catwalk_cap, "object/building/endor/shared_endor_catwalk_cap.iff")

object_building_endor_shared_endor_forest_hut = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_forest_hut_s01.apt",
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

	detailedDescription = "@building_detail:endor_lake_hut",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:endor_lake_hut",

	noBuildRadius = 0,

	objectName = "@building_name:endor_lake_hut",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 3,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2759537117
}

ObjectTemplates:addClientTemplate(object_building_endor_shared_endor_forest_hut, "object/building/endor/shared_endor_forest_hut.iff")

object_building_endor_shared_endor_giant_catwalk = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_village_tree_catwlk_64m_s01.apt",
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

	detailedDescription = "@building_detail:base_filler_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_filler_building",

	noBuildRadius = 0,

	objectName = "@building_name:base_filler_building",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 3,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2543574892
}

ObjectTemplates:addClientTemplate(object_building_endor_shared_endor_giant_catwalk, "object/building/endor/shared_endor_giant_catwalk.iff")

object_building_endor_shared_endor_giant_village_tree_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_village_tree_s01.apt",
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

	detailedDescription = "@building_detail:endor_lake_hut",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:endor_lake_hut",

	noBuildRadius = 0,

	objectName = "@building_name:endor_lake_hut",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 3,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3384806373
}

ObjectTemplates:addClientTemplate(object_building_endor_shared_endor_giant_village_tree_s01, "object/building/endor/shared_endor_giant_village_tree_s01.iff")

object_building_endor_shared_endor_lake_hut = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_lakevillage_lake_hut.apt",
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

	detailedDescription = "@building_detail:endor_lake_hut",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:endor_lake_hut",

	noBuildRadius = 0,

	objectName = "@building_name:endor_lake_hut",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 3,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 790353916
}

ObjectTemplates:addClientTemplate(object_building_endor_shared_endor_lake_hut, "object/building/endor/shared_endor_lake_hut.iff")

object_building_endor_shared_endor_lake_hut_s02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_lake_hut_s02.apt",
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

	detailedDescription = "@building_detail:endor_lake_hut",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:endor_lake_hut",

	noBuildRadius = 0,

	objectName = "@building_name:endor_lake_hut",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 3,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1488414842
}

ObjectTemplates:addClientTemplate(object_building_endor_shared_endor_lake_hut_s02, "object/building/endor/shared_endor_lake_hut_s02.iff")

object_building_endor_shared_endor_lake_platform = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_lakevillage_lake_hut_pc1.apt",
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

	detailedDescription = "@building_detail:endor_lake_platform",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:endor_lake_platform",

	noBuildRadius = 0,

	objectName = "@building_name:endor_lake_platform",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 3,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2419475197
}

ObjectTemplates:addClientTemplate(object_building_endor_shared_endor_lake_platform, "object/building/endor/shared_endor_lake_platform.iff")

object_building_endor_shared_endor_lake_platform_cap = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_lake_platform_cap_s01.apt",
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

	detailedDescription = "@building_detail:endor_lake_platform",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:endor_lake_platform",

	noBuildRadius = 0,

	objectName = "@building_name:endor_lake_platform",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 3,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1002562347
}

ObjectTemplates:addClientTemplate(object_building_endor_shared_endor_lake_platform_cap, "object/building/endor/shared_endor_lake_platform_cap.iff")

object_building_endor_shared_endor_lake_walkway_square = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_lake_platform_square_s01.apt",
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

	detailedDescription = "@building_detail:endor_lake_walkway_straight",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:endor_lake_walkway_straight",

	noBuildRadius = 0,

	objectName = "@building_name:endor_lake_walkway_straight",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 3,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1339123676
}

ObjectTemplates:addClientTemplate(object_building_endor_shared_endor_lake_walkway_square, "object/building/endor/shared_endor_lake_walkway_square.iff")

object_building_endor_shared_endor_lake_walkway_straight = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_lake_platform_rectangle_s01.apt",
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

	detailedDescription = "@building_detail:endor_lake_walkway_straight",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:endor_lake_walkway_straight",

	noBuildRadius = 0,

	objectName = "@building_name:endor_lake_walkway_straight",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 3,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3597287151
}

ObjectTemplates:addClientTemplate(object_building_endor_shared_endor_lake_walkway_straight, "object/building/endor/shared_endor_lake_walkway_straight.iff")

object_building_endor_shared_endor_tiki_torch = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_tiki_torch_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_endor_tiki_torch.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:endor_lake_hut",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:endor_lake_hut",

	noBuildRadius = 0,

	objectName = "@building_name:endor_lake_hut",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 3,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4148017771
}

ObjectTemplates:addClientTemplate(object_building_endor_shared_endor_tiki_torch, "object/building/endor/shared_endor_tiki_torch.iff")

object_building_endor_shared_endor_village_tree = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_village_tree_s01.apt",
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

	detailedDescription = "@building_detail:endor_lake_hut",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:endor_lake_hut",

	noBuildRadius = 0,

	objectName = "@building_name:endor_lake_hut",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 3,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1111623449
}

ObjectTemplates:addClientTemplate(object_building_endor_shared_endor_village_tree, "object/building/endor/shared_endor_village_tree.iff")

object_building_endor_shared_endor_village_tree_viewpoint = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_village_tree_viewpoint_s01.apt",
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

	detailedDescription = "@building_detail:endor_lake_hut",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:endor_lake_hut",

	noBuildRadius = 0,

	objectName = "@building_name:endor_lake_hut",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 3,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4074943330
}

ObjectTemplates:addClientTemplate(object_building_endor_shared_endor_village_tree_viewpoint, "object/building/endor/shared_endor_village_tree_viewpoint.iff")

object_building_endor_shared_endr_lake_rail16m = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_lake_rail16m.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 3,

	totalCellNumber = 0,

	clientObjectCRC = 2748322568
}

ObjectTemplates:addClientTemplate(object_building_endor_shared_endr_lake_rail16m, "object/building/endor/shared_endr_lake_rail16m.iff")

object_building_endor_shared_endr_lake_rail2m = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_lake_rail2m.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 3,

	totalCellNumber = 0,

	clientObjectCRC = 380245173
}

ObjectTemplates:addClientTemplate(object_building_endor_shared_endr_lake_rail2m, "object/building/endor/shared_endr_lake_rail2m.iff")

object_building_endor_shared_endr_lake_rail4m = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_lake_rail4m.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 3,

	totalCellNumber = 0,

	clientObjectCRC = 1280981925
}

ObjectTemplates:addClientTemplate(object_building_endor_shared_endr_lake_rail4m, "object/building/endor/shared_endr_lake_rail4m.iff")

object_building_endor_shared_endr_lake_rail8m = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_lake_rail8m.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 3,

	totalCellNumber = 0,

	clientObjectCRC = 4189742469
}

ObjectTemplates:addClientTemplate(object_building_endor_shared_endr_lake_rail8m, "object/building/endor/shared_endr_lake_rail8m.iff")
