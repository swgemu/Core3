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


object_building_general_shared_aircar_general = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:aircar_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:aircar_general",

	noBuildRadius = 0,

	objectName = "@building_name:aircar_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 929068141,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_aircar.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_aircar_general, "object/building/general/shared_aircar_general.iff")

object_building_general_shared_arena_general = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:arena_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:arena_general",

	noBuildRadius = 0,

	objectName = "@building_name:arena_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3257125986,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_arena.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_arena_general, "object/building/general/shared_arena_general.iff")

object_building_general_shared_arena_large_general = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:arena_large_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:arena_large_general",

	noBuildRadius = 0,

	objectName = "@building_name:arena_large_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3322084706,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_arena_large.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_arena_large_general, "object/building/general/shared_arena_large_general.iff")

object_building_general_shared_association_hall_civilian_general = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:association_hall_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:association_hall_general",

	noBuildRadius = 0,

	objectName = "@building_name:association_hall_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_assoc_hall_civ_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 17,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3632219938,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_association_hall.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_association_hall_civilian_general, "object/building/general/shared_association_hall_civilian_general.iff")

object_building_general_shared_association_hall_general = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:association_hall_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:association_hall_general",

	noBuildRadius = 0,

	objectName = "@building_name:association_hall_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_assoc_hall_civ_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 17,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3960949370,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_association_hall.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_association_hall_general, "object/building/general/shared_association_hall_general.iff")

object_building_general_shared_bank_general = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:bank_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:bank_general",

	noBuildRadius = 0,

	objectName = "@building_name:bank_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2650754817,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_bank.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bank_general, "object/building/general/shared_bank_general.iff")

object_building_general_shared_bunker_allum_mine = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 50,
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

	interiorLayoutFileName = "interiorlayout/bunker_allum.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_bunker_allum_mine.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 65,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 599067335,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_allum_mine, "object/building/general/shared_bunker_allum_mine.iff")

object_building_general_shared_bunker_blacksun_outpost_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/bunker_blacksun_outpost.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_small_outpost_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 49,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1938342630,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_blacksun_outpost_01, "object/building/general/shared_bunker_blacksun_outpost_01.iff")

object_building_general_shared_bunker_crimelord_retreat_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	objectName = "@building_name:bunker_crimelord_retreat",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_crimelord_retreat_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 49,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3171223694,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_crimelord_retreat_01, "object/building/general/shared_bunker_crimelord_retreat_01.iff")

object_building_general_shared_bunker_imperial_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2982837298,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_imperial_01, "object/building/general/shared_bunker_imperial_01.iff")

object_building_general_shared_bunker_imperial_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1792922789,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_imperial_02, "object/building/general/shared_bunker_imperial_02.iff")

object_building_general_shared_bunker_imperial_03 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s03.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 600879912,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_imperial_03, "object/building/general/shared_bunker_imperial_03.iff")

object_building_general_shared_bunker_imperial_bunker_abandoned = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_abandoned_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 34,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 990897798,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_imperial_bunker_abandoned, "object/building/general/shared_bunker_imperial_bunker_abandoned.iff")

object_building_general_shared_bunker_imperial_deep_chasm = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_deep_chasm_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2935243152,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_imperial_deep_chasm, "object/building/general/shared_bunker_imperial_deep_chasm.iff")

object_building_general_shared_bunker_imperial_detainment_center_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/bunker_imperial_detainment_center.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:bunker_imperial_prison",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_imperial_prison_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 17,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1672354378,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_imperial_detainment_center_01, "object/building/general/shared_bunker_imperial_detainment_center_01.iff")

object_building_general_shared_bunker_imperial_prison_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	objectName = "@building_name:bunker_imperial_prison",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_imperial_prison_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 17,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1661550307,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_imperial_prison_01, "object/building/general/shared_bunker_imperial_prison_01.iff")

object_building_general_shared_bunker_imperial_weapons_research_facility_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/naboo_imperial_weapons_research_facility.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_research_facility_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 22,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 357299427,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_imperial_weapons_research_facility_01, "object/building/general/shared_bunker_imperial_weapons_research_facility_01.iff")

object_building_general_shared_bunker_mad_bio = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 43,
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

	interiorLayoutFileName = "interiorlayout/geonosian_bio_dungeon.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_bunker_mad_bio_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 44,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3223964695,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_mad_bio, "object/building/general/shared_bunker_mad_bio.iff")

object_building_general_shared_bunker_rebel_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_rebl_bunker_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 18,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 102885585,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_rebel_01, "object/building/general/shared_bunker_rebel_01.iff")

object_building_general_shared_bunker_rebel_deep_chasm = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_rebl_bunker_deep_chasm_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3695355168,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_rebel_deep_chasm, "object/building/general/shared_bunker_rebel_deep_chasm.iff")

object_building_general_shared_bunker_rebel_spynet = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/bunker_rebel_spynet.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_abandoned_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 34,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4133162154,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_rebel_spynet, "object/building/general/shared_bunker_rebel_spynet.iff")

object_building_general_shared_bunker_rebel_weapons_depot = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/bunker_rebel_weapons_depot.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_small_outpost_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 49,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2551461683,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_rebel_weapons_depot, "object/building/general/shared_bunker_rebel_weapons_depot.iff")

object_building_general_shared_bunker_research_facility_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	objectName = "@building_name:bunker_imperial_research_facility",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_research_facility_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 22,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2046272201,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_research_facility_01, "object/building/general/shared_bunker_research_facility_01.iff")

object_building_general_shared_bunker_small_outpost_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_small_outpost_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 49,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1060967532,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_small_outpost_01, "object/building/general/shared_bunker_small_outpost_01.iff")

object_building_general_shared_bunker_small_outpost_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_small_outpost_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3828006139,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_small_outpost_02, "object/building/general/shared_bunker_small_outpost_02.iff")

object_building_general_shared_bunker_talus_chunker_bunker = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/chunker_bunker_interior.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_small_outpost_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2130756010,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_talus_chunker_bunker, "object/building/general/shared_bunker_talus_chunker_bunker.iff")

object_building_general_shared_bunker_tok_retreat_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/tok_retreat.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:bunker_crimelord_retreat",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_crimelord_retreat_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 49,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2032341079,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_tok_retreat_01, "object/building/general/shared_bunker_tok_retreat_01.iff")

object_building_general_shared_bunker_warren_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/warren.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_warren_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 87,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2436238099,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_bunker_warren_01, "object/building/general/shared_bunker_warren_01.iff")

object_building_general_shared_cantina_general = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:base_cantina",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cantina",

	noBuildRadius = 0,

	objectName = "@building_name:cantina_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4015930050,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cantina.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cantina_general, "object/building/general/shared_cantina_general.iff")

object_building_general_shared_capitol_general = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:base_palace",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_palace",

	noBuildRadius = 0,

	objectName = "@building_name:capitol_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_capitol_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2926502766,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_palace.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_capitol_general, "object/building/general/shared_capitol_general.iff")

object_building_general_shared_cave_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3160184163,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_01, "object/building/general/shared_cave_01.iff")

object_building_general_shared_cave_01_damprock = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:A Cave",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:Cave",

	noBuildRadius = 0,

	objectName = "@building_name:Cave Style 02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s01_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 952315499,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_01_damprock, "object/building/general/shared_cave_01_damprock.iff")

object_building_general_shared_cave_01_damprock_mirror = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:A Cave",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:Cave",

	noBuildRadius = 0,

	objectName = "@building_name:Cave Style 02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s01_damprock_mirror.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2530583699,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_01_damprock_mirror, "object/building/general/shared_cave_01_damprock_mirror.iff")

object_building_general_shared_cave_01_ice = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s01_ice.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3629542620,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_01_ice, "object/building/general/shared_cave_01_ice.iff")

object_building_general_shared_cave_01_mirror = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:A Cave",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:Cave",

	noBuildRadius = 0,

	objectName = "@building_name:Cave Style 02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s01_mirror.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3887886541,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_01_mirror, "object/building/general/shared_cave_01_mirror.iff")

object_building_general_shared_cave_02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1732984308,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_02, "object/building/general/shared_cave_02.iff")

object_building_general_shared_cave_02_damprock = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:A Cave",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:Cave",

	noBuildRadius = 0,

	objectName = "@building_name:Cave Style 02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s02_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4040916264,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_02_damprock, "object/building/general/shared_cave_02_damprock.iff")

object_building_general_shared_cave_02_damprock_mirror = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:A Cave",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:Cave",

	noBuildRadius = 0,

	objectName = "@building_name:Cave Style 02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s02_damprock_mirror.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3705597680,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_02_damprock_mirror, "object/building/general/shared_cave_02_damprock_mirror.iff")

object_building_general_shared_cave_02_ice = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s02_ice.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3398864833,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_02_ice, "object/building/general/shared_cave_02_ice.iff")

object_building_general_shared_cave_02_mirror = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:A Cave",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:Cave",

	noBuildRadius = 0,

	objectName = "@building_name:Cave Style 02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s02_mirror.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4020721095,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_02_mirror, "object/building/general/shared_cave_02_mirror.iff")

object_building_general_shared_cave_03 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s03.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 29,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 776362617,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_03, "object/building/general/shared_cave_03.iff")

object_building_general_shared_cave_03_damprock = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:A Cave",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:Cave",

	noBuildRadius = 0,

	objectName = "@building_name:Cave Style 02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s03_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 29,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3073160169,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_03_damprock, "object/building/general/shared_cave_03_damprock.iff")

object_building_general_shared_cave_03_damprock_mirror = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:A Cave",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:Cave",

	noBuildRadius = 0,

	objectName = "@building_name:Cave Style 02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s03_damprock_mirror.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 29,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 426189756,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_03_damprock_mirror, "object/building/general/shared_cave_03_damprock_mirror.iff")

object_building_general_shared_cave_03_ice = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s03_ice.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 29,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 949364135,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_03_ice, "object/building/general/shared_cave_03_ice.iff")

object_building_general_shared_cave_03_mirror = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:A Cave",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:Cave",

	noBuildRadius = 0,

	objectName = "@building_name:Cave Style 02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s03_mirror.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 29,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3897669313,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_03_mirror, "object/building/general/shared_cave_03_mirror.iff")

object_building_general_shared_cave_04_ice_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s01_ice.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 519460091,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_04_ice_s01, "object/building/general/shared_cave_04_ice_s01.iff")

object_building_general_shared_cave_05_ice_s02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s02_ice.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 759540329,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_05_ice_s02, "object/building/general/shared_cave_05_ice_s02.iff")

object_building_general_shared_cave_06_flatland_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_flatland_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 736190789,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_06_flatland_s01, "object/building/general/shared_cave_06_flatland_s01.iff")

object_building_general_shared_cave_06_flatland_s01_damprock = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_flatland_s01_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3352052197,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_06_flatland_s01_damprock, "object/building/general/shared_cave_06_flatland_s01_damprock.iff")

object_building_general_shared_cave_06_flatland_s01_ice = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_flatland_s01_ice.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1663639712,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_06_flatland_s01_ice, "object/building/general/shared_cave_06_flatland_s01_ice.iff")

object_building_general_shared_cave_07_flatland_s02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_flatland_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1905336231,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_07_flatland_s02, "object/building/general/shared_cave_07_flatland_s02.iff")

object_building_general_shared_cave_07_flatland_s02_damprock = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_flatland_s02_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3655237343,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_07_flatland_s02_damprock, "object/building/general/shared_cave_07_flatland_s02_damprock.iff")

object_building_general_shared_cave_07_flatland_s02_ice = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_flatland_s02_ice.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2188080207,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_07_flatland_s02_ice, "object/building/general/shared_cave_07_flatland_s02_ice.iff")

object_building_general_shared_cave_08_flatland_s03 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_flatland_s03.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 29,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2882713804,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_08_flatland_s03, "object/building/general/shared_cave_08_flatland_s03.iff")

object_building_general_shared_cave_08_flatland_s03_damprock = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_flatland_s03_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 29,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 524918885,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_08_flatland_s03_damprock, "object/building/general/shared_cave_08_flatland_s03_damprock.iff")

object_building_general_shared_cave_08_flatland_s03_ice = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_flatland_s03_ice.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 29,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 557190412,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_08_flatland_s03_ice, "object/building/general/shared_cave_08_flatland_s03_ice.iff")

object_building_general_shared_cave_lok_pirate_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/lok_pirate_cave_interior.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_flatland_s03.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 29,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 153465138,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_lok_pirate_cave, "object/building/general/shared_cave_lok_pirate_cave.iff")

object_building_general_shared_cave_morag = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/endor_cave_morag.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave_morag",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_endr_cave_morag.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1852639945,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cave_morag, "object/building/general/shared_cave_morag.iff")

object_building_general_shared_cloning_facility_general = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:base_cloning_facility",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cloning_facility",

	noBuildRadius = 0,

	objectName = "@building_name:cloning_facility_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 327514443,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cloning_facility.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_cloning_facility_general, "object/building/general/shared_cloning_facility_general.iff")

object_building_general_shared_corellia_afarathu_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/corellia_afarathu_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1102119105,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_corellia_afarathu_cave, "object/building/general/shared_corellia_afarathu_cave.iff")

object_building_general_shared_corellia_drall_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/corellia_drall_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s02_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 88228892,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_corellia_drall_cave, "object/building/general/shared_corellia_drall_cave.iff")

object_building_general_shared_corellia_nyax_bunker = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/corellia_nyax_bunker.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s03.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 780046145,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_corellia_nyax_bunker, "object/building/general/shared_corellia_nyax_bunker.iff")

object_building_general_shared_dantooine_force_crystal_hunter_sd_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/force_crystal_cave_v1.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1263547301,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_dantooine_force_crystal_hunter_sd_cave, "object/building/general/shared_dantooine_force_crystal_hunter_sd_cave.iff")

object_building_general_shared_dantooine_janta_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/dantooine_janta_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1976190033,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_dantooine_janta_cave, "object/building/general/shared_dantooine_janta_cave.iff")

object_building_general_shared_dantooine_kunga_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/dantooine_kunga_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s03_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 29,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2274845407,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_dantooine_kunga_cave, "object/building/general/shared_dantooine_kunga_cave.iff")

object_building_general_shared_dathomir_nsister_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/dathomir_nsister_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s01_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 711566567,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_dathomir_nsister_cave, "object/building/general/shared_dathomir_nsister_cave.iff")

object_building_general_shared_dathomir_nsister_rancor_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:A Cave",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/dathomir_nsister_rancor_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:Cave",

	noBuildRadius = 0,

	objectName = "@building_name:Cave Style 02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s01_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1702144691,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_dathomir_nsister_rancor_cave, "object/building/general/shared_dathomir_nsister_rancor_cave.iff")

object_building_general_shared_endor_jinda_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/endor_jinda_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_flatland_s03_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 29,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 709151424,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_endor_jinda_cave, "object/building/general/shared_endor_jinda_cave.iff")

object_building_general_shared_endor_korga_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/endor_korga_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s02_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1189018300,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_endor_korga_cave, "object/building/general/shared_endor_korga_cave.iff")

object_building_general_shared_endor_marauder_orphans_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/endor_marauder_orphans_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s02_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3233389758,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_endor_marauder_orphans_cave, "object/building/general/shared_endor_marauder_orphans_cave.iff")

object_building_general_shared_guild_combat_general_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:guild_combat_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:guild_combat_general",

	noBuildRadius = 0,

	objectName = "@building_name:guild_combat_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_guild_combat_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1394323186,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_guild.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_guild_combat_general_style_01, "object/building/general/shared_guild_combat_general_style_01.iff")

object_building_general_shared_guild_commerce_general_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:guild_commerce_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:guild_commerce_general",

	noBuildRadius = 0,

	objectName = "@building_name:guild_commerce_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_guild_commerce_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 326541771,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_guild.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_guild_commerce_general_style_01, "object/building/general/shared_guild_commerce_general_style_01.iff")

object_building_general_shared_guild_university_general_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:guild_university_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:guild_university_general",

	noBuildRadius = 0,

	objectName = "@building_name:guild_university_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_guild_university_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3594966040,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_guild.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_guild_university_general_style_01, "object/building/general/shared_guild_university_general_style_01.iff")

object_building_general_shared_hotel_general_style_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:hotel_general_style_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:hotel_general_style_1",

	noBuildRadius = 0,

	objectName = "@building_name:hotel_general_style_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2957667026,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_hotel.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_hotel_general_style_1, "object/building/general/shared_hotel_general_style_1.iff")

object_building_general_shared_hotel_general_style_2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/mockup_hotelb.apt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:hotel_general_style_2",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:hotel_general_style_2",

	noBuildRadius = 0,

	objectName = "@building_name:hotel_general_style_2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1801306693,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_hotel.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_hotel_general_style_2, "object/building/general/shared_hotel_general_style_2.iff")

object_building_general_shared_housing_general_style_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:housing_general_style_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:housing_general_style_1",

	noBuildRadius = 0,

	objectName = "@building_name:housing_general_style_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1516155062,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_housing.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_housing_general_style_1, "object/building/general/shared_housing_general_style_1.iff")

object_building_general_shared_landing_pad_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:shuttleport_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:shuttleport_general",

	noBuildRadius = 0,

	objectName = "@building_name:shuttleport_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_landing_pad_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 1,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 1,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 766941896,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_filler_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_landing_pad_s01, "object/building/general/shared_landing_pad_s01.iff")

object_building_general_shared_lok_evil_droid_engineer_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/lok_evil_droid_engineer_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s03.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 29,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1736894341,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_lok_evil_droid_engineer_cave, "object/building/general/shared_lok_evil_droid_engineer_cave.iff")

object_building_general_shared_lok_kimogila_cult_bunker = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/lok_kimogila_cult_bunker.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_warren_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 87,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2736597128,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_lok_kimogila_cult_bunker, "object/building/general/shared_lok_kimogila_cult_bunker.iff")

object_building_general_shared_lok_mercenary_cave_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/lok_mercenary_cave_01.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s01_ice.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2476588024,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_lok_mercenary_cave_01, "object/building/general/shared_lok_mercenary_cave_01.iff")

object_building_general_shared_lok_nymstheme_mercenary_bunker = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/lok_nymstheme_mercenary_bunker.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:bunker_imperial_research_facility",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_research_facility_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 22,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 526484590,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_lok_nymstheme_mercenary_bunker, "object/building/general/shared_lok_nymstheme_mercenary_bunker.iff")

object_building_general_shared_lok_nymstheme_pirate_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/lok_nymstheme_pirate_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s03.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 29,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 18770566,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_lok_nymstheme_pirate_cave, "object/building/general/shared_lok_nymstheme_pirate_cave.iff")

object_building_general_shared_merchant_tent_all_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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
	portalLayoutFilename = "appearance/ply_all_merchant_tent_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 1,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3614150695,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_housing.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_merchant_tent_all_s01, "object/building/general/shared_merchant_tent_all_s01.iff")

object_building_general_shared_mun_all_capitol_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:capitol_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:capitol_general",

	noBuildRadius = 0,

	objectName = "@building_name:capitol_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_capitol_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1684189678,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_palace.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_mun_all_capitol_s01, "object/building/general/shared_mun_all_capitol_s01.iff")

object_building_general_shared_mun_all_cloning_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:cloning_facility_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:cloning_facility_general",

	noBuildRadius = 0,

	objectName = "@building_name:cloning_facility_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_cloning_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 432887298,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cloning_facility.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_mun_all_cloning_s01, "object/building/general/shared_mun_all_cloning_s01.iff")

object_building_general_shared_mun_all_guild_combat_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:guild_combat_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:guild_combat_general",

	noBuildRadius = 0,

	objectName = "@building_name:guild_combat_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_guild_combat_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3789605488,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_guild.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_mun_all_guild_combat_s01, "object/building/general/shared_mun_all_guild_combat_s01.iff")

object_building_general_shared_mun_all_guild_commerce_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:guild_commerce_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:guild_commerce_general",

	noBuildRadius = 0,

	objectName = "@building_name:guild_commerce_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_guild_commerce_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 49465033,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_guild.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_mun_all_guild_commerce_s01, "object/building/general/shared_mun_all_guild_commerce_s01.iff")

object_building_general_shared_mun_all_guild_theater_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:theater",

	noBuildRadius = 0,

	objectName = "@building_name:theater",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_guild_theater_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2335562190,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_theater.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_mun_all_guild_theater_s01, "object/building/general/shared_mun_all_guild_theater_s01.iff")

object_building_general_shared_mun_all_guild_university_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:guild_university_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:guild_university_general",

	noBuildRadius = 0,

	objectName = "@building_name:guild_university_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_guild_university_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1179256079,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_guild.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_mun_all_guild_university_s01, "object/building/general/shared_mun_all_guild_university_s01.iff")

object_building_general_shared_mun_all_hospital_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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
	portalLayoutFilename = "appearance/mun_all_hospital_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 14,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3942101786,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_palace.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_mun_all_hospital_s01, "object/building/general/shared_mun_all_hospital_s01.iff")

object_building_general_shared_mun_all_hospital_s02 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 30,
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
	portalLayoutFilename = "appearance/mun_all_hospital_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 3,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 836770701,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_palace.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_mun_all_hospital_s02, "object/building/general/shared_mun_all_hospital_s02.iff")

object_building_general_shared_mun_all_hotel_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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
	portalLayoutFilename = "appearance/mun_all_hotel_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 64245657,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_hotel.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_mun_all_hotel_s01, "object/building/general/shared_mun_all_hotel_s01.iff")

object_building_general_shared_mun_all_landing_pad_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 20,
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

	detailedDescription = "@building_detail:starport",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:starport",

	noBuildRadius = 0,

	objectName = "@building_name:starport",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_landing_pad_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 1,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2845231920,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_starport.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_mun_all_landing_pad_s01, "object/building/general/shared_mun_all_landing_pad_s01.iff")

object_building_general_shared_mun_all_starport_s01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:starport",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:starport",

	noBuildRadius = 0,

	objectName = "@building_name:starport",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_starport_s01_u01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 16,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1399192891,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_starport.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_mun_all_starport_s01, "object/building/general/shared_mun_all_starport_s01.iff")

object_building_general_shared_naboo_narglatch_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/naboo_narglatch_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s02_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1618666507,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_naboo_narglatch_cave, "object/building/general/shared_naboo_narglatch_cave.iff")

object_building_general_shared_naboo_pirate_bunker = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/naboo_pirate_bunker.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:bunker",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_small_outpost_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2696571862,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_naboo_pirate_bunker, "object/building/general/shared_naboo_pirate_bunker.iff")

object_building_general_shared_naboo_veermok_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/naboo_veermok_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s02_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1074091686,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_naboo_veermok_cave, "object/building/general/shared_naboo_veermok_cave.iff")

object_building_general_shared_newbie_hall = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 48,
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

	interiorLayoutFileName = "interiorlayout/newbie_hall.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:association_hall_civilian_tatooine",

	noBuildRadius = 0,

	objectName = "@building_name:association_hall_civilian_tatooine",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_newbie_hall.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 12,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3771444529,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_association_hall.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_newbie_hall, "object/building/general/shared_newbie_hall.iff")

object_building_general_shared_newbie_hall_skipped = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 48,
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
	portalLayoutFilename = "appearance/thm_newbie_hall_skippedtutorial.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 1,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1011239275,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_association_hall.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_newbie_hall_skipped, "object/building/general/shared_newbie_hall_skipped.iff")

object_building_general_shared_nightsister_slave_mine_sd_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/nightsister_slave_mine_v2.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s02_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2054952898,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_nightsister_slave_mine_sd_cave, "object/building/general/shared_nightsister_slave_mine_sd_cave.iff")

object_building_general_shared_parking_garage_general = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:parking_garage_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:parking_garage_general",

	noBuildRadius = 0,

	objectName = "@building_name:parking_garage_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3151125,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_parking_garage.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_parking_garage_general, "object/building/general/shared_parking_garage_general.iff")

object_building_general_shared_ranchers_house_tatooine = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/building/shared_ranchers_house_tatooine.cdf",
	clientGameObjectType = 512,
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

	interiorLayoutFileName = "interiorlayout/rancher_house.ilf",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/building/player/shared_player_house_tatooine_medium_style_01.sfp",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 8,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2779359080,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_player_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_ranchers_house_tatooine, "object/building/general/shared_ranchers_house_tatooine.iff")

object_building_general_shared_rebel_fuel_depot = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/military_rebel_fuel_processing_depot.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_rebl_bunker_deep_chasm_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3374741880,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_rebel_fuel_depot, "object/building/general/shared_rebel_fuel_depot.iff")

object_building_general_shared_rori_bark_mite_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/rori_bark_mite_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s02_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2008111071,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_rori_bark_mite_cave, "object/building/general/shared_rori_bark_mite_cave.iff")

object_building_general_shared_rori_bat_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/bat_rori_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s01_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2510037668,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_rori_bat_cave, "object/building/general/shared_rori_bat_cave.iff")

object_building_general_shared_rori_cobral_bunker = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/rori_cobral_bunker.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2753493661,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_rori_cobral_bunker, "object/building/general/shared_rori_cobral_bunker.iff")

object_building_general_shared_rori_garyn_bunker = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/rori_garyn_bunker.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2144664039,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_rori_garyn_bunker, "object/building/general/shared_rori_garyn_bunker.iff")

object_building_general_shared_rori_hyperdrive_research_facility = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:Hyperdrive Research Facility",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/rori_hyperdrive_research_facility.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:Bunker",

	noBuildRadius = 0,

	objectName = "@building_name:Hyperdrive Research Facility",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_research_facility_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 22,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2711352465,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_rori_hyperdrive_research_facility, "object/building/general/shared_rori_hyperdrive_research_facility.iff")

object_building_general_shared_rori_kobola_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/rori_kobola_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s02_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 303008890,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_rori_kobola_cave, "object/building/general/shared_rori_kobola_cave.iff")

object_building_general_shared_rori_torton_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/rori_torton_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_flatland_s01_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1919200278,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_rori_torton_cave, "object/building/general/shared_rori_torton_cave.iff")

object_building_general_shared_shuttleport_general = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/mun_all_shuttleport_s01.apt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:shuttleport_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:shuttleport_general",

	noBuildRadius = 0,

	objectName = "@building_name:shuttleport_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3656969600,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_starport.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_shuttleport_general, "object/building/general/shared_shuttleport_general.iff")

object_building_general_shared_space_dungeon_corellian_corvette = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/corvette_base.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:base_cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_spc_corvette_dungeon.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2945204994,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_space_dungeon_corellian_corvette, "object/building/general/shared_space_dungeon_corellian_corvette.iff")

object_building_general_shared_space_dungeon_corellian_corvette_imperial = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/corvette_imperial.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:base_cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_spc_corvette_dungeon.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3935788511,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_space_dungeon_corellian_corvette_imperial, "object/building/general/shared_space_dungeon_corellian_corvette_imperial.iff")

object_building_general_shared_space_dungeon_corellian_corvette_rebel = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/corvette_rebel.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:base_cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_spc_corvette_dungeon.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1523571122,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_space_dungeon_corellian_corvette_rebel, "object/building/general/shared_space_dungeon_corellian_corvette_rebel.iff")

object_building_general_shared_space_dungeon_hutt_asteroid = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:base_cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_spc_asteroid_bunker_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 692704019,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_space_dungeon_hutt_asteroid, "object/building/general/shared_space_dungeon_hutt_asteroid.iff")

object_building_general_shared_space_dungeon_star_destroyer = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:base_cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_spc_star_destroyer_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1431567153,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_space_dungeon_star_destroyer, "object/building/general/shared_space_dungeon_star_destroyer.iff")

object_building_general_shared_starport_general = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:starport_general",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:starport_general",

	noBuildRadius = 0,

	objectName = "@building_name:starport_general",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_starport_s01_u01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 16,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4229374013,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_starport.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_starport_general, "object/building/general/shared_starport_general.iff")

object_building_general_shared_starport_general_style_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:starport_general_style_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:starport_general_style_1",

	noBuildRadius = 0,

	objectName = "@building_name:starport_general_style_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2699737473,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_starport.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_starport_general_style_1, "object/building/general/shared_starport_general_style_1.iff")

object_building_general_shared_starport_general_style_2 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/mockup_starportb.apt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@building_detail:starport_general_style_2",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:starport_general_style_2",

	noBuildRadius = 0,

	objectName = "@building_name:starport_general_style_2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/starportb_circle.lay",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2080182550,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_starport.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_starport_general_style_2, "object/building/general/shared_starport_general_style_2.iff")

object_building_general_shared_talus_aakuan_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/aakuan_talus_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1823419741,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_talus_aakuan_cave, "object/building/general/shared_talus_aakuan_cave.iff")

object_building_general_shared_talus_aqualish_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/talus_aqualish_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s01_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3978592584,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_talus_aqualish_cave, "object/building/general/shared_talus_aqualish_cave.iff")

object_building_general_shared_talus_binyare_bunker = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/talus_binyare_bunker.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s03.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4022785523,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_talus_binyare_bunker, "object/building/general/shared_talus_binyare_bunker.iff")

object_building_general_shared_talus_giant_decay_mite_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/talus_decay_mite_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_flatland_s01_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2459804029,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_talus_giant_decay_mite_cave, "object/building/general/shared_talus_giant_decay_mite_cave.iff")

object_building_general_shared_talus_giant_fynock_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/talus_giant_fynock_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_flatland_s01_damprock.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1300216386,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_talus_giant_fynock_cave, "object/building/general/shared_talus_giant_fynock_cave.iff")

object_building_general_shared_talus_kahmurra_bunker = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/khmurra_talus_bunker.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1743913196,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_talus_kahmurra_bunker, "object/building/general/shared_talus_kahmurra_bunker.iff")

object_building_general_shared_talus_traitor_erran = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/talus_traitor_erran.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:bunker_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 9,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 330907884,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_talus_traitor_erran, "object/building/general/shared_talus_traitor_erran.iff")

object_building_general_shared_tatooine_beetle_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/tatooine_beetle_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1885974487,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_tatooine_beetle_cave, "object/building/general/shared_tatooine_beetle_cave.iff")

object_building_general_shared_tatooine_hutt_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/tatooine_hutt_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 11,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 434980665,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_tatooine_hutt_cave, "object/building/general/shared_tatooine_hutt_cave.iff")

object_building_general_shared_tatooine_squill_cave = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/tatooine_squill_cave.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/thm_all_cave_s03.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 29,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1109209534,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_tatooine_squill_cave, "object/building/general/shared_tatooine_squill_cave.iff")

object_building_general_shared_tatooine_tusken_bunker = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

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

	interiorLayoutFileName = "interiorlayout/tusken_tatooine_bunker.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_cave",

	noBuildRadius = 0,

	objectName = "@building_name:cave",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_s02.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2741312696,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_general_shared_tatooine_tusken_bunker, "object/building/general/shared_tatooine_tusken_bunker.iff")
