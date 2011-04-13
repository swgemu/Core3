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


object_building_faction_perk_hq_shared_hq_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s01",

	gameObjectType = 515,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4204337141
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s01, "object/building/faction_perk/hq/shared_hq_s01.iff")

object_building_faction_perk_hq_shared_hq_s01_fp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s01",

	gameObjectType = 515,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2419085158
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s01_fp, "object/building/faction_perk/hq/shared_hq_s01_fp.iff")

object_building_faction_perk_hq_shared_hq_s01_imp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s01_imp.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s01",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s01_imp.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_impl_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 554924775
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s01_imp, "object/building/faction_perk/hq/shared_hq_s01_imp.iff")

object_building_faction_perk_hq_shared_hq_s01_imp_pvp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s01_imp.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s01_imp_pvp",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s01_imp.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s01_imp_pvp",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_impl_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2016142793
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s01_imp_pvp, "object/building/faction_perk/hq/shared_hq_s01_imp_pvp.iff")

object_building_faction_perk_hq_shared_hq_s01_rebel = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s01_rebel.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s01",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s01_rebel.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1119051291
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s01_rebel, "object/building/faction_perk/hq/shared_hq_s01_rebel.iff")

object_building_faction_perk_hq_shared_hq_s01_rebel_pvp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s01_rebel.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s01_rebel_pvp",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s01_rebel.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s01_rebel_pvp",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 769008513
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s01_rebel_pvp, "object/building/faction_perk/hq/shared_hq_s01_rebel_pvp.iff")

object_building_faction_perk_hq_shared_hq_s02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s02",

	gameObjectType = 515,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 563003234
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s02, "object/building/faction_perk/hq/shared_hq_s02.iff")

object_building_faction_perk_hq_shared_hq_s02_fp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s02",

	gameObjectType = 515,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2094148152
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s02_fp, "object/building/faction_perk/hq/shared_hq_s02_fp.iff")

object_building_faction_perk_hq_shared_hq_s02_imp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s02_imp.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s02",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s02_imp.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 869505530
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s02_imp, "object/building/faction_perk/hq/shared_hq_s02_imp.iff")

object_building_faction_perk_hq_shared_hq_s02_imp_pvp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s02_imp.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s02_imp_pvp",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s02_imp.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s02_imp_pvp",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1158021745
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s02_imp_pvp, "object/building/faction_perk/hq/shared_hq_s02_imp_pvp.iff")

object_building_faction_perk_hq_shared_hq_s02_rebel = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s02_rebel.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s02",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s02_rebel.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1283967902
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s02_rebel, "object/building/faction_perk/hq/shared_hq_s02_rebel.iff")

object_building_faction_perk_hq_shared_hq_s02_rebel_pvp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s02_rebel.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s02_rebel_pvp",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s02_rebel.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s02_rebel_pvp",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1309089184
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s02_rebel_pvp, "object/building/faction_perk/hq/shared_hq_s02_rebel_pvp.iff")

object_building_faction_perk_hq_shared_hq_s03 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s03",

	gameObjectType = 515,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s03",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1753471215
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s03, "object/building/faction_perk/hq/shared_hq_s03.iff")

object_building_faction_perk_hq_shared_hq_s03_fp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s03",

	gameObjectType = 515,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s03",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 661911282
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s03_fp, "object/building/faction_perk/hq/shared_hq_s03_fp.iff")

object_building_faction_perk_hq_shared_hq_s03_imp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s03_imp.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s03",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s03_imp.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s03",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3251843996
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s03_imp, "object/building/faction_perk/hq/shared_hq_s03_imp.iff")

object_building_faction_perk_hq_shared_hq_s03_imp_pvp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s03_imp.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s03_imp_pvp",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s03_imp.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s03_imp_pvp",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2913096820
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s03_imp_pvp, "object/building/faction_perk/hq/shared_hq_s03_imp_pvp.iff")

object_building_faction_perk_hq_shared_hq_s03_rebel = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s03_rebel.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s03",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s03_rebel.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s03",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3039513712
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s03_rebel, "object/building/faction_perk/hq/shared_hq_s03_rebel.iff")

object_building_faction_perk_hq_shared_hq_s03_rebel_pvp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s03_rebel.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s03_rebel_pvp",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s03_rebel.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s03_rebel_pvp",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2466839762
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s03_rebel_pvp, "object/building/faction_perk/hq/shared_hq_s03_rebel_pvp.iff")

object_building_faction_perk_hq_shared_hq_s04 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s04",

	gameObjectType = 515,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s04",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s03.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2472604667
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s04, "object/building/faction_perk/hq/shared_hq_s04.iff")

object_building_faction_perk_hq_shared_hq_s04_fp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s04",

	gameObjectType = 515,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s04",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s03.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2715286835
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s04_fp, "object/building/faction_perk/hq/shared_hq_s04_fp.iff")

object_building_faction_perk_hq_shared_hq_s04_imp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s04_imp.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s04",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s04_imp.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s04",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s03.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 374497216
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s04_imp, "object/building/faction_perk/hq/shared_hq_s04_imp.iff")

object_building_faction_perk_hq_shared_hq_s04_imp_pvp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s04_imp.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s04_imp_pvp",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s04_imp.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s04_imp_pvp",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s03.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1063111937
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s04_imp_pvp, "object/building/faction_perk/hq/shared_hq_s04_imp_pvp.iff")

object_building_faction_perk_hq_shared_hq_s04_rebel = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s04_rebel.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s04",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s04_rebel.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s04",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s03.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1357832340
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s04_rebel, "object/building/faction_perk/hq/shared_hq_s04_rebel.iff")

object_building_faction_perk_hq_shared_hq_s04_rebel_pvp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s04_rebel.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s04_rebel_pvp",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s04_rebel.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 64,

	objectName = "@faction_perk_n:hq_s04_rebel_pvp",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s03.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2309317090
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s04_rebel_pvp, "object/building/faction_perk/hq/shared_hq_s04_rebel_pvp.iff")

object_building_faction_perk_hq_shared_hq_s05 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 64,
	clientDataFile = "",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s05",

	gameObjectType = 515,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 128,

	objectName = "@faction_perk_n:hq_s05",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_police_station_rebl_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s05.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 12,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3664614518
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s05, "object/building/faction_perk/hq/shared_hq_s05.iff")

object_building_faction_perk_hq_shared_hq_s05_fp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 64,
	clientDataFile = "",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s05",

	gameObjectType = 515,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 128,

	objectName = "@faction_perk_n:hq_s05",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_police_station_rebl_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s05.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 12,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4202045945
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s05_fp, "object/building/faction_perk/hq/shared_hq_s05_fp.iff")

object_building_faction_perk_hq_shared_hq_s05_imp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 64,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s05_imp.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s05",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s05_imp.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 128,

	objectName = "@faction_perk_n:hq_s05",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_police_station_impl_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s05.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 12,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3830642086
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s05_imp, "object/building/faction_perk/hq/shared_hq_s05_imp.iff")

object_building_faction_perk_hq_shared_hq_s05_imp_pvp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 64,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s05_imp.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s05_imp",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s05_imp.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 128,

	objectName = "@faction_perk_n:hq_s05_imp",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_police_station_impl_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s05.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 12,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3623459588
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s05_imp_pvp, "object/building/faction_perk/hq/shared_hq_s05_imp_pvp.iff")

object_building_faction_perk_hq_shared_hq_s05_rebel = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 64,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s05_rebel.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s05",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s05_rebel.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 128,

	objectName = "@faction_perk_n:hq_s05",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_police_station_rebl_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s05.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 12,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2839701370
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s05_rebel, "object/building/faction_perk/hq/shared_hq_s05_rebel.iff")

object_building_faction_perk_hq_shared_hq_s05_rebel_pvp = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 64,
	clientDataFile = "clientdata/faction_perk/hq/client_hq_s05_rebel.cdf",
	clientGameObjectType = 515,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@faction_perk_d:hq_s05_rebel_pvp",

	gameObjectType = 515,

	interiorLayoutFileName = "interiorlayout/faction_perk/hq/hq_s05_rebel.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_building",

	noBuildRadius = 128,

	objectName = "@faction_perk_n:hq_s05_rebel_pvp",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_police_station_rebl_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/faction_perk/hq/fp_s05.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/poi_large.lay",
	totalCellNumber = 12,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1420460176
}

ObjectTemplates:addClientTemplate(object_building_faction_perk_hq_shared_hq_s05_rebel_pvp, "object/building/faction_perk/hq/shared_hq_s05_rebel_pvp.iff")
