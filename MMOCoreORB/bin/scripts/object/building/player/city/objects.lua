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


object_building_player_city_shared_bank_corellia = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_corl_bank_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_bank_player.cdf",
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

	detailedDescription = "@building_detail:bank",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:bank",

	noBuildRadius = 0,

	objectName = "@building_name:bank",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_bank.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1845141471,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_bank_corellia, "object/building/player/city/shared_bank_corellia.iff")

object_building_player_city_shared_bank_naboo = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_bank_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_bank_player.cdf",
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

	detailedDescription = "@building_detail:bank",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:bank",

	noBuildRadius = 0,

	objectName = "@building_name:bank",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_bank.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3868143603,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_bank_naboo, "object/building/player/city/shared_bank_naboo.iff")

object_building_player_city_shared_bank_tatooine = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_bank_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_bank_player.cdf",
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

	detailedDescription = "@building_detail:bank",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:bank",

	noBuildRadius = 0,

	objectName = "@building_name:bank",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_bank.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1371143744,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_bank_tatooine, "object/building/player/city/shared_bank_tatooine.iff")

object_building_player_city_shared_cantina_corellia = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_city_medium_building.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:cantina",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_housing",

	noBuildRadius = 0,

	objectName = "@building_name:cantina",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_cantina_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_city_cantina.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 2,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3739527551,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_player_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_cantina_corellia, "object/building/player/city/shared_cantina_corellia.iff")

object_building_player_city_shared_cantina_naboo = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_city_medium_building.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:cantina",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_housing",

	noBuildRadius = 0,

	objectName = "@building_name:cantina",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_nboo_cantina_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_city_cantina.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 2,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2025646266,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_player_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_cantina_naboo, "object/building/player/city/shared_cantina_naboo.iff")

object_building_player_city_shared_cantina_tatooine = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_city_medium_building.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:cantina",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_housing",

	noBuildRadius = 0,

	objectName = "@building_name:cantina",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_tato_cantina_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_city_cantina.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 2,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3802646752,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_player_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_cantina_tatooine, "object/building/player/city/shared_cantina_tatooine.iff")

object_building_player_city_shared_cityhall_corellia = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_city_cityhall.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:cityhall",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_housing",

	noBuildRadius = 0,

	objectName = "@building_name:cityhall",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_capitol_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_city_cityhall.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 5,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4031190701,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_player_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_cityhall_corellia, "object/building/player/city/shared_cityhall_corellia.iff")

object_building_player_city_shared_cityhall_naboo = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_city_cityhall.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:cityhall",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_housing",

	noBuildRadius = 0,

	objectName = "@building_name:cityhall",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_nboo_capitol_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_city_cityhall.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 5,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3442426219,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_player_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_cityhall_naboo, "object/building/player/city/shared_cityhall_naboo.iff")

object_building_player_city_shared_cityhall_tatooine = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_city_cityhall.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:cityhall",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_housing",

	noBuildRadius = 0,

	objectName = "@building_name:cityhall",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_tato_capitol_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_city_cityhall.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 5,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3422844722,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_player_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_cityhall_tatooine, "object/building/player/city/shared_cityhall_tatooine.iff")

object_building_player_city_shared_cloning_corellia = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_city_medium_building.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:cloning",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_housing",

	noBuildRadius = 0,

	objectName = "@building_name:cloning",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_cloning_facility_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_city_cloning.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 4,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1360449531,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_player_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_cloning_corellia, "object/building/player/city/shared_cloning_corellia.iff")

object_building_player_city_shared_cloning_naboo = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_city_medium_building.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:cloning",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_housing",

	noBuildRadius = 0,

	objectName = "@building_name:cloning",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_nboo_cloning_facility_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_city_cloning.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 4,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2221199199,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_player_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_cloning_naboo, "object/building/player/city/shared_cloning_naboo.iff")

object_building_player_city_shared_cloning_tatooine = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_city_medium_building.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:cloning",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_housing",

	noBuildRadius = 0,

	objectName = "@building_name:cloning",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_tato_cloning_facility_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_city_cloning.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 4,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1834331748,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_player_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_cloning_tatooine, "object/building/player/city/shared_cloning_tatooine.iff")

object_building_player_city_shared_garden_corellia_lrg_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_corl_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_corl_garden_lrg_01.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_large.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3782826017,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_corellia_lrg_01, "object/building/player/city/shared_garden_corellia_lrg_01.iff")

object_building_player_city_shared_garden_corellia_lrg_02 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_corl_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_corl_garden_lrg_02.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_large.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 980349110,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_corellia_lrg_02, "object/building/player/city/shared_garden_corellia_lrg_02.iff")

object_building_player_city_shared_garden_corellia_lrg_03 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_corl_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_corl_garden_lrg_03.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_large.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1935906619,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_corellia_lrg_03, "object/building/player/city/shared_garden_corellia_lrg_03.iff")

object_building_player_city_shared_garden_corellia_lrg_04 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_corl_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_corl_garden_lrg_04.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_large.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2290138159,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_corellia_lrg_04, "object/building/player/city/shared_garden_corellia_lrg_04.iff")

object_building_player_city_shared_garden_corellia_lrg_05 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_corl_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_corl_garden_lrg_05.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_large.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3247299490,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_corellia_lrg_05, "object/building/player/city/shared_garden_corellia_lrg_05.iff")

object_building_player_city_shared_garden_corellia_med_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_corl_garden_med_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_corl_garden_med_01.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_medium.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1120922265,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_corellia_med_01, "object/building/player/city/shared_garden_corellia_med_01.iff")

object_building_player_city_shared_garden_corellia_med_02 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_corl_garden_med_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_corl_garden_med_02.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_medium.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2581086734,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_corellia_med_02, "object/building/player/city/shared_garden_corellia_med_02.iff")

object_building_player_city_shared_garden_corellia_med_03 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_corl_garden_med_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_corl_garden_med_03.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_medium.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3503629699,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_corellia_med_03, "object/building/player/city/shared_garden_corellia_med_03.iff")

object_building_player_city_shared_garden_corellia_med_04 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_corl_garden_med_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_corl_garden_med_04.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_medium.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 724962967,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_corellia_med_04, "object/building/player/city/shared_garden_corellia_med_04.iff")

object_building_player_city_shared_garden_corellia_med_05 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_corl_garden_med_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_corl_garden_med_05.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_medium.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1648060698,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_corellia_med_05, "object/building/player/city/shared_garden_corellia_med_05.iff")

object_building_player_city_shared_garden_corellia_sml_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_corl_garden_sml_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_corl_garden_sml_01.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_small.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 782388533,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_corellia_sml_01, "object/building/player/city/shared_garden_corellia_sml_01.iff")

object_building_player_city_shared_garden_corellia_sml_02 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_corl_garden_sml_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_corl_garden_sml_02.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_small.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4122338722,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_corellia_sml_02, "object/building/player/city/shared_garden_corellia_sml_02.iff")

object_building_player_city_shared_garden_corellia_sml_03 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_corl_garden_sml_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_corl_garden_sml_03.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_small.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3166208559,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_corellia_sml_03, "object/building/player/city/shared_garden_corellia_sml_03.iff")

object_building_player_city_shared_garden_corellia_sml_04 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_corl_garden_sml_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_corl_garden_sml_04.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_small.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1197189435,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_corellia_sml_04, "object/building/player/city/shared_garden_corellia_sml_04.iff")

object_building_player_city_shared_garden_corellia_sml_05 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_corl_garden_sml_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_corl_garden_sml_05.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_small.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 240570038,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_corellia_sml_05, "object/building/player/city/shared_garden_corellia_sml_05.iff")

object_building_player_city_shared_garden_dantooine_lrg_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_dant_garden_lrg_01.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_large.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2412094562,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_dantooine_lrg_01, "object/building/player/city/shared_garden_dantooine_lrg_01.iff")

object_building_player_city_shared_garden_dantooine_med_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garden_med_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_dant_garden_med_01.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_medium.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 745739994,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_dantooine_med_01, "object/building/player/city/shared_garden_dantooine_med_01.iff")

object_building_player_city_shared_garden_dantooine_sml_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garden_sml_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_dant_garden_sml_01.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_small.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1075753334,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_dantooine_sml_01, "object/building/player/city/shared_garden_dantooine_sml_01.iff")

object_building_player_city_shared_garden_dathomir_lrg_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_dath_garden_lrg_01.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_large.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 247337676,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_dathomir_lrg_01, "object/building/player/city/shared_garden_dathomir_lrg_01.iff")

object_building_player_city_shared_garden_dathomir_med_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_med_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_dath_garden_med_01.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_medium.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2903023732,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_dathomir_med_01, "object/building/player/city/shared_garden_dathomir_med_01.iff")

object_building_player_city_shared_garden_dathomir_sml_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_sml_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_dath_garden_sml_01.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_small.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3244623832,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_dathomir_sml_01, "object/building/player/city/shared_garden_dathomir_sml_01.iff")

object_building_player_city_shared_garden_endor_lrg_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_end_garden_lrg_01.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_large.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2039109063,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_endor_lrg_01, "object/building/player/city/shared_garden_endor_lrg_01.iff")

object_building_player_city_shared_garden_endor_med_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_med_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_end_garden_med_01.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_medium.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3661424511,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_endor_med_01, "object/building/player/city/shared_garden_endor_med_01.iff")

object_building_player_city_shared_garden_endor_sml_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_sml_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_end_garden_sml_01.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_small.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3058778323,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_endor_sml_01, "object/building/player/city/shared_garden_endor_sml_01.iff")

object_building_player_city_shared_garden_naboo_large = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_naboo_garden_02.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_bank.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2557845591,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_naboo_large, "object/building/player/city/shared_garden_naboo_large.iff")

object_building_player_city_shared_garden_naboo_lrg_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_nboo_garden_lrg_01.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_large.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1417631619,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_naboo_lrg_01, "object/building/player/city/shared_garden_naboo_lrg_01.iff")

object_building_player_city_shared_garden_naboo_lrg_02 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_nboo_garden_lrg_02.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_large.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2406022932,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_naboo_lrg_02, "object/building/player/city/shared_garden_naboo_lrg_02.iff")

object_building_player_city_shared_garden_naboo_lrg_03 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_nboo_garden_lrg_03.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_large.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3328546969,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_naboo_lrg_03, "object/building/player/city/shared_garden_naboo_lrg_03.iff")

object_building_player_city_shared_garden_naboo_lrg_04 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_nboo_garden_lrg_04.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_large.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1032237965,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_naboo_lrg_04, "object/building/player/city/shared_garden_naboo_lrg_04.iff")

object_building_player_city_shared_garden_naboo_lrg_05 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_nboo_garden_lrg_05.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_large.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1955320832,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_naboo_lrg_05, "object/building/player/city/shared_garden_naboo_lrg_05.iff")

object_building_player_city_shared_garden_naboo_med_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_med_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_nboo_garden_med_01.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_medium.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4157203771,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_naboo_med_01, "object/building/player/city/shared_garden_naboo_med_01.iff")

object_building_player_city_shared_garden_naboo_med_02 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_med_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_nboo_garden_med_02.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_medium.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 752766380,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_naboo_med_02, "object/building/player/city/shared_garden_naboo_med_02.iff")

object_building_player_city_shared_garden_naboo_med_03 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_med_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_nboo_garden_med_03.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_medium.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1708337697,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_naboo_med_03, "object/building/player/city/shared_garden_naboo_med_03.iff")

object_building_player_city_shared_garden_naboo_med_04 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_med_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_nboo_garden_med_04.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_medium.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2653946165,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_naboo_med_04, "object/building/player/city/shared_garden_naboo_med_04.iff")

object_building_player_city_shared_garden_naboo_med_05 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_med_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_nboo_garden_med_05.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_medium.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3611125432,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_naboo_med_05, "object/building/player/city/shared_garden_naboo_med_05.iff")

object_building_player_city_shared_garden_naboo_sml_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_sml_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_nboo_garden_sml_01.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_small.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2611233431,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_naboo_sml_01, "object/building/player/city/shared_garden_naboo_sml_01.iff")

object_building_player_city_shared_garden_naboo_sml_02 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_sml_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_nboo_garden_sml_02.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_small.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1085532672,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_naboo_sml_02, "object/building/player/city/shared_garden_naboo_sml_02.iff")

object_building_player_city_shared_garden_naboo_sml_03 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_sml_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_nboo_garden_sml_03.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_small.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 163483021,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_naboo_sml_03, "object/building/player/city/shared_garden_naboo_sml_03.iff")

object_building_player_city_shared_garden_naboo_sml_04 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_sml_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_nboo_garden_sml_04.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_small.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4066223769,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_naboo_sml_04, "object/building/player/city/shared_garden_naboo_sml_04.iff")

object_building_player_city_shared_garden_naboo_sml_05 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_garden_sml_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_nboo_garden_sml_05.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_small.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3142631700,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_naboo_sml_05, "object/building/player/city/shared_garden_naboo_sml_05.iff")

object_building_player_city_shared_garden_tatooine_lrg_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_tato_garden_lrg_01.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_large.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2152696910,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_tatooine_lrg_01, "object/building/player/city/shared_garden_tatooine_lrg_01.iff")

object_building_player_city_shared_garden_tatooine_lrg_02 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_tato_garden_lrg_02.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_large.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1532503257,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_tatooine_lrg_02, "object/building/player/city/shared_garden_tatooine_lrg_02.iff")

object_building_player_city_shared_garden_tatooine_lrg_03 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_tato_garden_lrg_03.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_large.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 307577684,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_tatooine_lrg_03, "object/building/player/city/shared_garden_tatooine_lrg_03.iff")

object_building_player_city_shared_garden_tatooine_lrg_04 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_tato_garden_lrg_04.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_large.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3921045568,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_tatooine_lrg_04, "object/building/player/city/shared_garden_tatooine_lrg_04.iff")

object_building_player_city_shared_garden_tatooine_lrg_05 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garden_lrg_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_tato_garden_lrg_05.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_large.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2696613837,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_tatooine_lrg_05, "object/building/player/city/shared_garden_tatooine_lrg_05.iff")

object_building_player_city_shared_garden_tatooine_med_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garden_med_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_tato_garden_med_01.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_medium.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 603537142,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_tatooine_med_01, "object/building/player/city/shared_garden_tatooine_med_01.iff")

object_building_player_city_shared_garden_tatooine_med_02 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garden_med_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_tato_garden_med_02.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_medium.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4176385633,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_tatooine_med_02, "object/building/player/city/shared_garden_tatooine_med_02.iff")

object_building_player_city_shared_garden_tatooine_med_03 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garden_med_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_tato_garden_med_03.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_medium.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2984505836,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_tatooine_med_03, "object/building/player/city/shared_garden_tatooine_med_03.iff")

object_building_player_city_shared_garden_tatooine_med_04 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garden_med_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_tato_garden_med_04.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_medium.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1241570040,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_tatooine_med_04, "object/building/player/city/shared_garden_tatooine_med_04.iff")

object_building_player_city_shared_garden_tatooine_med_05 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garden_med_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_tato_garden_med_05.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_medium.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 51232117,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_tatooine_med_05, "object/building/player/city/shared_garden_tatooine_med_05.iff")

object_building_player_city_shared_garden_tatooine_sml_01 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garden_sml_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_tato_garden_sml_01.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_small.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1335138650,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_tatooine_sml_01, "object/building/player/city/shared_garden_tatooine_sml_01.iff")

object_building_player_city_shared_garden_tatooine_sml_02 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garden_sml_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_tato_garden_sml_02.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_small.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2491625933,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_tatooine_sml_02, "object/building/player/city/shared_garden_tatooine_sml_02.iff")

object_building_player_city_shared_garden_tatooine_sml_03 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garden_sml_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_tato_garden_sml_03.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_small.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3717092928,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_tatooine_sml_03, "object/building/player/city/shared_garden_tatooine_sml_03.iff")

object_building_player_city_shared_garden_tatooine_sml_04 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garden_sml_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_tato_garden_sml_04.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_small.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 644709716,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_tatooine_sml_04, "object/building/player/city/shared_garden_tatooine_sml_04.iff")

object_building_player_city_shared_garden_tatooine_sml_05 = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_garden_sml_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_tato_garden_sml_05.cdf",
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

	detailedDescription = "@building_detail:garden",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:garden",

	noBuildRadius = 0,

	objectName = "@building_name:garden",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_garden_small.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1868569305,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_garden_tatooine_sml_05, "object/building/player/city/shared_garden_tatooine_sml_05.iff")

object_building_player_city_shared_hospital_corellia = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_hospital_player.cdf",
	clientGameObjectType = 512,
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
	portalLayoutFilename = "appearance/ply_corl_hospital_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_city_hospital.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 4,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3101511526,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_player_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_hospital_corellia, "object/building/player/city/shared_hospital_corellia.iff")

object_building_player_city_shared_hospital_naboo = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_hospital_player.cdf",
	clientGameObjectType = 512,
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
	portalLayoutFilename = "appearance/ply_nboo_hospital_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_city_hospital.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 4,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1387695986,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_player_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_hospital_naboo, "object/building/player/city/shared_hospital_naboo.iff")

object_building_player_city_shared_hospital_tatooine = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_hospital_player.cdf",
	clientGameObjectType = 512,
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
	portalLayoutFilename = "appearance/ply_tato_hospital_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_city_hospital.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 4,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2224959225,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_player_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_hospital_tatooine, "object/building/player/city/shared_hospital_tatooine.iff")

object_building_player_city_shared_shuttleport_corellia = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_corl_shuttleport_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/building/shared_shuttleport.cdf",
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

	detailedDescription = "@building_detail:shuttleport",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:shuttleport",

	noBuildRadius = 0,

	objectName = "@building_name:shuttleport",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_shuttleport.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3046076056,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_shuttleport_corellia, "object/building/player/city/shared_shuttleport_corellia.iff")

object_building_player_city_shared_shuttleport_naboo = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_nboo_shuttleport_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/building/shared_shuttleport.cdf",
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

	detailedDescription = "@building_detail:shuttleport",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:shuttleport",

	noBuildRadius = 0,

	objectName = "@building_name:shuttleport",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_shuttleport.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 893676466,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_shuttleport_naboo, "object/building/player/city/shared_shuttleport_naboo.iff")

object_building_player_city_shared_shuttleport_tatooine = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ply_tato_shuttleport_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/building/shared_shuttleport.cdf",
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

	detailedDescription = "@building_detail:shuttleport",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:shuttleport",

	noBuildRadius = 0,

	objectName = "@building_name:shuttleport",
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
	structureFootprintFileName = "footprint/building/player/shared_player_city_shuttleport.sfp",
	surfaceType = 1,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2311851783,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_shuttleport_tatooine, "object/building/player/city/shared_shuttleport_tatooine.iff")

object_building_player_city_shared_theater_corellia = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_city_medium_building.cdf",
	clientGameObjectType = 512,
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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:theater",

	noBuildRadius = 0,

	objectName = "@building_name:theater",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_theater_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_city_theater.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 1,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3302987664,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_player_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_theater_corellia, "object/building/player/city/shared_theater_corellia.iff")

object_building_player_city_shared_theater_naboo = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_city_medium_building.cdf",
	clientGameObjectType = 512,
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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:theater",

	noBuildRadius = 0,

	objectName = "@building_name:theater",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_nboo_theater_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_city_theater.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 1,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2697086195,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_player_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_theater_naboo, "object/building/player/city/shared_theater_naboo.iff")

object_building_player_city_shared_theater_tatooine = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 30,
	clientDataFile = "clientdata/building/shared_city_medium_building.cdf",
	clientGameObjectType = 512,
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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:theater",

	noBuildRadius = 0,

	objectName = "@building_name:theater",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_tato_theater_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_city_theater.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 1,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4171036175,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_player_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_player_city_shared_theater_tatooine, "object/building/player/city/shared_theater_tatooine.iff")
