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


object_building_corellia_shared_association_hall_civilian_corellia = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 35,
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

	detailedDescription = "@building_detail:association_hall_civilian_tatooine",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_association_hall_style_corellia.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:association_hall_civilian_tatooine",

	noBuildRadius = 0,

	objectName = "@building_name:association_hall_civilian_tatooine",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_corl_assoc_hall_civ_s01.pob",

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
	totalCellNumber = 17,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2742139830,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_association_hall.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_association_hall_civilian_corellia, "object/building/corellia/shared_association_hall_civilian_corellia.iff")

object_building_corellia_shared_bank_corellia = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/mun_corl_bank_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 43,
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

	detailedDescription = "@building_detail:bank_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:bank_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:bank_corellia",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 925292585,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_bank.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_bank_corellia, "object/building/corellia/shared_bank_corellia.iff")

object_building_corellia_shared_cantina_corellia = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 58,
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

	interiorLayoutFileName = "interiorlayout/shared_cantina_style_01.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:cantina_general",

	noBuildRadius = 0,

	objectName = "@building_name:cantina_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_corl_cantina.pob",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 2013728951,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cantina.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_cantina_corellia, "object/building/corellia/shared_cantina_corellia.iff")

object_building_corellia_shared_capitol_corellia = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 70,
	clientDataFile = "clientdata/building/shared_capitol.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:capitol_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_capitol_style_corellia.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:capitol_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:capitol_corellia",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_corl_capitol_s01.pob",

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
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2023346551,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_capitol.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_capitol_corellia, "object/building/corellia/shared_capitol_corellia.iff")

object_building_corellia_shared_cloning_corellia = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
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

	detailedDescription = "@building_detail:guild_combat_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_cloning_facility.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:guild_combat_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:guild_combat_corellia",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_corl_cloning_s01.pob",

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
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4160058931,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cloning_facility.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_cloning_corellia, "object/building/corellia/shared_cloning_corellia.iff")

object_building_corellia_shared_filler_block_corellia_32x16_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_imprv_building_block_32x16_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 19,
	clientDataFile = "clientdata/building/shared_corellia_filler_block_32x16.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:filler_block_corellia_32x16_s01",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_block_corellia_32x16_s01",

	noBuildRadius = 0,

	objectName = "@building_name:filler_block_corellia_32x16_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 3487204259,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_filler_block_corellia_32x16_s01, "object/building/corellia/shared_filler_block_corellia_32x16_s01.iff")

object_building_corellia_shared_filler_block_corellia_64x32_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_imprv_building_block_64x32_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_corellia_filler_block_64x32_style01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:filler_block_corellia_64x32_s01",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_block_corellia_64x32_s01",

	noBuildRadius = 0,

	objectName = "@building_name:filler_block_corellia_64x32_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 1480274759,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_filler_block_corellia_64x32_s01, "object/building/corellia/shared_filler_block_corellia_64x32_s01.iff")

object_building_corellia_shared_filler_block_corellia_64x32_s02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_imprv_building_block_64x32_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
	clientDataFile = "clientdata/building/shared_corellia_filler_block_64x32_style02.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:filler_block_corellia_64x32_s02",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_block_corellia_64x32_s02",

	noBuildRadius = 0,

	objectName = "@building_name:filler_block_corellia_64x32_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 2200738768,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_filler_block_corellia_64x32_s02, "object/building/corellia/shared_filler_block_corellia_64x32_s02.iff")

object_building_corellia_shared_filler_building_corellia_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_imprv_building_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 50,
	clientDataFile = "clientdata/building/shared_corellia_filler_building_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:filler_building_corellia_style_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_corellia_style_1",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_corellia_style_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 2891016021,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_filler_building_corellia_style_01, "object/building/corellia/shared_filler_building_corellia_style_01.iff")

object_building_corellia_shared_filler_building_corellia_style_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_imprv_building_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 40,
	clientDataFile = "clientdata/building/shared_corellia_filler_building_02.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:filler_building_corellia_style_2",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_corellia_style_2",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_corellia_style_2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 2001129410,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_filler_building_corellia_style_02, "object/building/corellia/shared_filler_building_corellia_style_02.iff")

object_building_corellia_shared_filler_building_corellia_style_03 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_imprv_building_s03.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 40,
	clientDataFile = "clientdata/building/shared_corellia_filler_building_03.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:filler_building_corellia_style_3",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_corellia_style_3",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_corellia_style_3",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 1045145679,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_filler_building_corellia_style_03, "object/building/corellia/shared_filler_building_corellia_style_03.iff")

object_building_corellia_shared_filler_building_corellia_style_04 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_imprv_building_s04.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 52,
	clientDataFile = "clientdata/building/shared_corellia_filler_building_04.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:filler_building_corellia_style_4",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_corellia_style_4",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_corellia_style_4",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 3316155227,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_filler_building_corellia_style_04, "object/building/corellia/shared_filler_building_corellia_style_04.iff")

object_building_corellia_shared_filler_building_corellia_style_05 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_imprv_building_s05.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 34,
	clientDataFile = "clientdata/building/shared_corellia_filler_building_05.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:filler_building_corellia_style_5",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_corellia_style_5",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_corellia_style_5",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 2359682262,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_filler_building_corellia_style_05, "object/building/corellia/shared_filler_building_corellia_style_05.iff")

object_building_corellia_shared_filler_building_corellia_style_06 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_imprv_building_s06.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 68,
	clientDataFile = "clientdata/building/shared_corellia_filler_building_06.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:filler_building_corellia_style_6",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_corellia_style_6",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_corellia_style_6",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 1471302721,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_filler_building_corellia_style_06, "object/building/corellia/shared_filler_building_corellia_style_06.iff")

object_building_corellia_shared_filler_building_corellia_style_07 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_imprv_building_s07.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 50,
	clientDataFile = "clientdata/building/shared_corellia_filler_building_07.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:filler_building_corellia_style_7",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_building_corellia_style_7",

	noBuildRadius = 0,

	objectName = "@building_name:filler_building_corellia_style_7",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 515845068,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_filler_building_corellia_style_07, "object/building/corellia/shared_filler_building_corellia_style_07.iff")

object_building_corellia_shared_filler_historic_24x16_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_imprv_historic_24x16_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/building/shared_corellia_filler_slum_24x16_s01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:filler_historic_24x16_s01",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_historic_24x16_s01",

	noBuildRadius = 0,

	objectName = "@building_name:filler_historic_24x16_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 2616481902,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_filler_historic_24x16_s01, "object/building/corellia/shared_filler_historic_24x16_s01.iff")

object_building_corellia_shared_filler_historic_24x16_s02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_imprv_historic_24x16_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/building/shared_corellia_filler_slum_24x16_s02.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:filler_historic_24x16_s02",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_historic_24x16_s02",

	noBuildRadius = 0,

	objectName = "@building_name:filler_historic_24x16_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 1088680185,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_filler_historic_24x16_s02, "object/building/corellia/shared_filler_historic_24x16_s02.iff")

object_building_corellia_shared_filler_historic_32x16_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_imprv_historic_32x16_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 18,
	clientDataFile = "clientdata/building/shared_corellia_historic_filler_building_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:filler_historic_32x16_s01",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_historic_32x16_s01",

	noBuildRadius = 0,

	objectName = "@building_name:filler_historic_32x16_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 1667646591,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_filler_historic_32x16_s01, "object/building/corellia/shared_filler_historic_32x16_s01.iff")

object_building_corellia_shared_filler_historic_32x16_s02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_imprv_historic_32x16_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 18,
	clientDataFile = "clientdata/building/shared_corellia_historic_filler_building_02.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:filler_historic_32x16_s02",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_historic_32x16_s02",

	noBuildRadius = 0,

	objectName = "@building_name:filler_historic_32x16_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 3094473960,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_filler_historic_32x16_s02, "object/building/corellia/shared_filler_historic_32x16_s02.iff")

object_building_corellia_shared_filler_slum_16x16_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_imprv_slum_16x16_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 12,
	clientDataFile = "clientdata/building/shared_corellia_filler_slum_16x16_s01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:filler_slum_16x16_s01",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_slum_16x16_s01",

	noBuildRadius = 0,

	objectName = "@building_name:filler_slum_16x16_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 2757381075,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_filler_slum_16x16_s01, "object/building/corellia/shared_filler_slum_16x16_s01.iff")

object_building_corellia_shared_filler_slum_16x32_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_imprv_slum_16x32_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 18,
	clientDataFile = "clientdata/building/shared_corellia_filler_slum_16x32_s01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:filler_slum_16x32_s01",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_slum_16x32_s01",

	noBuildRadius = 0,

	objectName = "@building_name:filler_slum_16x32_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 1694210539,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_filler_slum_16x32_s01, "object/building/corellia/shared_filler_slum_16x32_s01.iff")

object_building_corellia_shared_filler_slum_16x32_s02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_imprv_slum_16x32_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 18,
	clientDataFile = "clientdata/building/shared_corellia_filler_slum_16x32_s02.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:filler_slum_16x32_s02",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:filler_slum_16x32_s02",

	noBuildRadius = 0,

	objectName = "@building_name:filler_slum_16x32_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 3219927420,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_filler_slum_16x32_s02, "object/building/corellia/shared_filler_slum_16x32_s02.iff")

object_building_corellia_shared_garage_corellia = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/mun_corl_garage_s01_u01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 24,
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

	detailedDescription = "@building_detail:shuttleport_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:shuttleport_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:shuttleport_corellia",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 1140644280,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_parking_garage.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_garage_corellia, "object/building/corellia/shared_garage_corellia.iff")

object_building_corellia_shared_guild_combat_corellia_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
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

	detailedDescription = "@building_detail:guild_combat_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_guild_combat_style_corellia.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:guild_combat_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:guild_combat_corellia",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_corl_guild_combat_s01.pob",

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
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1288802152,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_guild.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_guild_combat_corellia_style_01, "object/building/corellia/shared_guild_combat_corellia_style_01.iff")

object_building_corellia_shared_guild_commerce_corellia_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
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

	detailedDescription = "@building_detail:guild_commerce_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_guild_commerce_style_corellia.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:guild_commerce_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:guild_commerce_corellia",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_corl_guild_commerce_s01.pob",

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
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2920780919,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_guild.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_guild_commerce_corellia_style_01, "object/building/corellia/shared_guild_commerce_corellia_style_01.iff")

object_building_corellia_shared_guild_theater_corellia_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 25,
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

	interiorLayoutFileName = "interiorlayout/shared_guild_theatre_style_01.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:theater",

	noBuildRadius = 0,

	objectName = "@building_name:theater",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_corl_guild_theater_s01.pob",

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
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3431234640,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_theater.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_guild_theater_corellia_s01, "object/building/corellia/shared_guild_theater_corellia_s01.iff")

object_building_corellia_shared_guild_university_corellia_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 38,
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

	detailedDescription = "@building_detail:guild_university_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_guild_university_style_corellia.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:guild_university_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:guild_university_corellia",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_corl_guild_university_s01.pob",

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
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3226540131,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_guild.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_guild_university_corellia_style_01, "object/building/corellia/shared_guild_university_corellia_style_01.iff")

object_building_corellia_shared_hospital_corellia = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 62,
	clientDataFile = "clientdata/building/shared_hospital.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:hospital_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_hospital_style_corellia.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:hospital_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:hospital_corellia",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_corl_hospital_s01.pob",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 2966265050,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_hospital.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_hospital_corellia, "object/building/corellia/shared_hospital_corellia.iff")

object_building_corellia_shared_hospital_corellia_s02 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:hospital_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_hospital_style_02.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:hospital_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:hospital_corellia",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_corl_hospital_s02.pob",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 1414124568,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_palace.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_hospital_corellia_s02, "object/building/corellia/shared_hospital_corellia_s02.iff")

object_building_corellia_shared_hotel_corellia = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 40,
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

	detailedDescription = "@building_detail:guild_combat_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_hotel_style_corellia.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:guild_combat_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:guild_combat_corellia",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_corl_hotel_s01.pob",

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
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3326447330,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_hotel.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_hotel_corellia, "object/building/corellia/shared_hotel_corellia.iff")

object_building_corellia_shared_merchant_tent_corellia_s01 = SharedBuildingObjectTemplate:new {
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
	portalLayoutFilename = "appearance/ply_corl_merchant_tent_s01.pob",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 2032858770,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_housing.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_merchant_tent_corellia_s01, "object/building/corellia/shared_merchant_tent_corellia_s01.iff")

object_building_corellia_shared_ply_corl_house_lg_s01_fp1 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:guild_combat_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:guild_combat_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:guild_combat_corellia",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_house_lg_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

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
	totalCellNumber = 13,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2468987350,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_housing.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_ply_corl_house_lg_s01_fp1, "object/building/corellia/shared_ply_corl_house_lg_s01_fp1.iff")

object_building_corellia_shared_ply_corl_house_m_s01_fp1 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:guild_combat_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:guild_combat_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:guild_combat_corellia",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_house_m_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

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
	totalCellNumber = 4,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1777902906,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_housing.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_ply_corl_house_m_s01_fp1, "object/building/corellia/shared_ply_corl_house_m_s01_fp1.iff")

object_building_corellia_shared_ply_corl_house_s_s01_fp1 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:guild_combat_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:guild_combat_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:guild_combat_corellia",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_house_sm_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

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
	totalCellNumber = 4,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4262283837,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_housing.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_ply_corl_house_s_s01_fp1, "object/building/corellia/shared_ply_corl_house_s_s01_fp1.iff")

object_building_corellia_shared_ply_corl_house_s_s01_fp2 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:guild_combat_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:guild_combat_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:guild_combat_corellia",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_house_sm_s01_fp2.pob",

	rangedIntCustomizationVariables = {},

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
	totalCellNumber = 4,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 622518954,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_housing.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_ply_corl_house_s_s01_fp2, "object/building/corellia/shared_ply_corl_house_s_s01_fp2.iff")

object_building_corellia_shared_ply_corl_house_s_s02_fp1 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:guild_combat_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:guild_combat_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:guild_combat_corellia",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_house_sm_s02_fp1.pob",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 3972901152,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_housing.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_ply_corl_house_s_s02_fp1, "object/building/corellia/shared_ply_corl_house_s_s02_fp1.iff")

object_building_corellia_shared_salon_corellia = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:salon_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_salon_style_corellia.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:salon_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:salon_corellia",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_corl_idesigner_tent_s01.pob",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 4015891242,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_salon.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_salon_corellia, "object/building/corellia/shared_salon_corellia.iff")

object_building_corellia_shared_shuttleport_corellia = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/mun_corl_shuttleport_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 29,
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

	detailedDescription = "@building_detail:shuttleport_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:shuttleport_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:shuttleport_corellia",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 197393539,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_shuttleport.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_shuttleport_corellia, "object/building/corellia/shared_shuttleport_corellia.iff")

object_building_corellia_shared_skyscraper_corellia_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_skyskraper_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 42,
	clientDataFile = "clientdata/building/shared_skyscraper_corellia_style_01.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:skyscraper_corellia_style_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:skyscraper_corellia_style_1",

	noBuildRadius = 0,

	objectName = "@building_name:skyscraper_corellia_style_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 2284214156,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_skyscraper_corellia_style_01, "object/building/corellia/shared_skyscraper_corellia_style_01.iff")

object_building_corellia_shared_skyscraper_corellia_style_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_skyskraper_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 45,
	clientDataFile = "clientdata/building/shared_skyscraper_corellia_style_02.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:skyscraper_corellia_style_2",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:skyscraper_corellia_style_2",

	noBuildRadius = 0,

	objectName = "@building_name:skyscraper_corellia_style_2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 1395785499,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_skyscraper_corellia_style_02, "object/building/corellia/shared_skyscraper_corellia_style_02.iff")

object_building_corellia_shared_skyscraper_corellia_style_03 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_skyskraper_s03.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 55,
	clientDataFile = "clientdata/building/shared_skyscraper_corellia_style_03.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:skyscraper_corellia_style_3",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:skyscraper_corellia_style_3",

	noBuildRadius = 0,

	objectName = "@building_name:skyscraper_corellia_style_3",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 440178838,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_skyscraper_corellia_style_03, "object/building/corellia/shared_skyscraper_corellia_style_03.iff")

object_building_corellia_shared_skyscraper_corellia_style_04 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_skyskraper_s04.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 55,
	clientDataFile = "clientdata/building/shared_skyscraper_corellia_style_04.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:skyscraper_corellia_style_4",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:skyscraper_corellia_style_4",

	noBuildRadius = 0,

	objectName = "@building_name:skyscraper_corellia_style_4",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 3789534082,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_skyscraper_corellia_style_04, "object/building/corellia/shared_skyscraper_corellia_style_04.iff")

object_building_corellia_shared_skyscraper_corellia_style_05 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/thm_corl_skyskraper_s05.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 42,
	clientDataFile = "clientdata/building/shared_skyscraper_corellia_style_05.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:skyscraper_corellia_style_5",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:skyscraper_corellia_style_5",

	noBuildRadius = 0,

	objectName = "@building_name:skyscraper_corellia_style_5",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

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

	clientObjectCRC = 2832389135,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_skyscraper_corellia_style_05, "object/building/corellia/shared_skyscraper_corellia_style_05.iff")

object_building_corellia_shared_starport_corellia = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 96,
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

	detailedDescription = "@building_detail:starport_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/starport_corellia_interior.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:starport_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:starport_corellia",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_corl_starport_s01_u01.pob",

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
	totalCellNumber = 16,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1449497657,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_starport.iff"}
}

ObjectTemplates:addClientTemplate(object_building_corellia_shared_starport_corellia, "object/building/corellia/shared_starport_corellia.iff")
