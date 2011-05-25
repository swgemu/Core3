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


object_building_military_shared_military_abandoned_police_station_rebel = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/building/shared_military_police_station.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:military_abandoned_police_station_rebel",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_abandoned_police_station_rebel.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_abandoned_police_station_rebel",

	noBuildRadius = 0,

	objectName = "@building_name:military_abandoned_police_station_rebel",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_police_station_rebl_s01.pob",

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

	clientObjectCRC = 61695795,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_abandoned_police_station_rebel, "object/building/military/shared_military_abandoned_police_station_rebel.iff")

object_building_military_shared_military_base_gate_house_imperial = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/mun_all_military_base_gate_house_impl_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 12,
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

	detailedDescription = "@building_detail:military_gate_house",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_gate_house",

	noBuildRadius = 0,

	objectName = "@building_name:military_gate_house",
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
	surfaceType = 1,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3485179638,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_base_gate_house_imperial, "object/building/military/shared_military_base_gate_house_imperial.iff")

object_building_military_shared_military_base_gate_house_rebel = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/mun_all_military_base_gate_house_rebl_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 12,
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

	detailedDescription = "@building_detail:military_gate_house",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_gate_house",

	noBuildRadius = 0,

	objectName = "@building_name:military_gate_house",
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
	surfaceType = 1,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 301400937,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_base_gate_house_rebel, "object/building/military/shared_military_base_gate_house_rebel.iff")

object_building_military_shared_military_base_police_station_imperial_lok_otto = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_base_police_station_imperial_otto",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/police_station_imperial_otto.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_base_police_station_imperial_otto",

	noBuildRadius = 0,

	objectName = "@building_name:military_base_police_station_imperial_otto",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_police_station_impl_s01.pob",

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

	clientObjectCRC = 603572205,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_base_police_station_imperial_lok_otto, "object/building/military/shared_military_base_police_station_imperial_lok_otto.iff")

object_building_military_shared_military_base_police_station_imperial_style_01 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_base_police_station_imperial",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_base_police_station_imperial_style_01.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_base_police_station_imperial",

	noBuildRadius = 0,

	objectName = "@building_name:military_base_police_station_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_police_station_impl_s01.pob",

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

	clientObjectCRC = 3633066758,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_base_police_station_imperial_style_01, "object/building/military/shared_military_base_police_station_imperial_style_01.iff")

object_building_military_shared_military_base_police_station_rebel_style_01 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_police_station_rebl_s01.pob",

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

	clientObjectCRC = 2265285311,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_base_police_station_rebel_style_01, "object/building/military/shared_military_base_police_station_rebel_style_01.iff")

object_building_military_shared_military_base_shed_imperial_barracks_s01 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_base_shed_imperial_barracks_s01.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_impl_s01.pob",

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
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4255048531,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_base_shed_imperial_barracks_s01, "object/building/military/shared_military_base_shed_imperial_barracks_s01.iff")

object_building_military_shared_military_base_shed_imperial_style_01 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_base_shed_imperial_style_01.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_impl_s01.pob",

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
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 196947849,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_base_shed_imperial_style_01, "object/building/military/shared_military_base_shed_imperial_style_01.iff")

object_building_military_shared_military_base_shed_imperial_style_bank_s01 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_base_shed_imperial_style_bank_s01.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_impl_s01.pob",

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
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3577026459,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_base_shed_imperial_style_bank_s01, "object/building/military/shared_military_base_shed_imperial_style_bank_s01.iff")

object_building_military_shared_military_base_shed_imperial_style_cantina_s01 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_base_shed_imperial_style_cantina_s01.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_impl_s01.pob",

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
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4151796568,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_base_shed_imperial_style_cantina_s01, "object/building/military/shared_military_base_shed_imperial_style_cantina_s01.iff")

object_building_military_shared_military_base_shed_imperial_style_hospital_01 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:imperial_military_hospital_1",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_base_shed_imperial_style_hospital_01.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:imperial_military_hospital_1",

	noBuildRadius = 0,

	objectName = "@building_name:imperial_military_hospital_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_impl_s01.pob",

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
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3493400176,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_base_shed_imperial_style_hospital_01, "object/building/military/shared_military_base_shed_imperial_style_hospital_01.iff")

object_building_military_shared_military_base_shed_imperial_style_officer_s01 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_base_shed_imperial_style_officer_s01.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_impl_s01.pob",

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
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 279599580,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_base_shed_imperial_style_officer_s01, "object/building/military/shared_military_base_shed_imperial_style_officer_s01.iff")

object_building_military_shared_military_base_shed_imperial_style_prison_01 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:imperial_prison_shed",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_base_shed_imperial_style_prison_01.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:imperial_prison_shed",

	noBuildRadius = 0,

	objectName = "@building_name:imperial_prison_shed",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_impl_s01.pob",

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
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3201291643,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_base_shed_imperial_style_prison_01, "object/building/military/shared_military_base_shed_imperial_style_prison_01.iff")

object_building_military_shared_military_base_shed_rebel_abandoned_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/building/shared_military_base_shed.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:abandoned_rebel_shed",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_base_shed_rebel_abandoned_01.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:abandoned_rebel_shed",

	noBuildRadius = 0,

	objectName = "@building_name:abandoned_rebel_shed",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

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
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1836586352,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_base_shed_rebel_abandoned_01, "object/building/military/shared_military_base_shed_rebel_abandoned_01.iff")

object_building_military_shared_military_base_shed_rebel_style_01 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/building/shared_military_base_shed.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_base_shed_rebel_style_01.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

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
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3606723543,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_base_shed_rebel_style_01, "object/building/military/shared_military_base_shed_rebel_style_01.iff")

object_building_military_shared_military_imperial_detachment_hq = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_imperial_detachment",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_imperial_detachment_hq.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_imperial_detachment",

	noBuildRadius = 0,

	objectName = "@building_name:military_imperial_detachment",
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

	clientObjectCRC = 3881652814,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_imperial_detachment_hq, "object/building/military/shared_military_imperial_detachment_hq.iff")

object_building_military_shared_military_imperial_field_hospital = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_imperial_field_hospital",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_imperial_field_hospital.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_imperial_field_hospital",

	noBuildRadius = 0,

	objectName = "@building_name:military_imperial_field_hospital",
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

	clientObjectCRC = 1587777178,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_imperial_field_hospital, "object/building/military/shared_military_imperial_field_hospital.iff")

object_building_military_shared_military_imperial_forward_outpost = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_imperial_forward_outpost",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_imperial_forward_outpost.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_imperial_forward_outpost",

	noBuildRadius = 0,

	objectName = "@building_name:military_imperial_forward_outpost",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

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
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3707185089,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_imperial_forward_outpost, "object/building/military/shared_military_imperial_forward_outpost.iff")

object_building_military_shared_military_imperial_strategic_base = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_imperial_strategic_base",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_imperial_strategic_base.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_imperial_strategic_base",

	noBuildRadius = 0,

	objectName = "@building_name:military_imperial_strategic_base",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_police_station_impl_s01.pob",

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

	clientObjectCRC = 1767088646,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_imperial_strategic_base, "object/building/military/shared_military_imperial_strategic_base.iff")

object_building_military_shared_military_imperial_tactical_center = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_imperial_tactical_center",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_imperial_tactical_center.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_imperial_tactical_center",

	noBuildRadius = 0,

	objectName = "@building_name:military_imperial_tactical_center",
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

	clientObjectCRC = 3834889912,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_imperial_tactical_center, "object/building/military/shared_military_imperial_tactical_center.iff")

object_building_military_shared_military_outpost_guard_house_imperial = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 12,
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_guard_house_impl_s01.pob",

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
	totalCellNumber = 2,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1294596356,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_outpost_guard_house_imperial, "object/building/military/shared_military_outpost_guard_house_imperial.iff")

object_building_military_shared_military_outpost_guard_house_rebel = SharedBuildingObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 12,
	clientDataFile = "clientdata/building/shared_military_outpost_guard_house.cdf",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_rebel_guard_house.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_guard_house_rebl_s01.pob",

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
	totalCellNumber = 2,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4257226961,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_outpost_guard_house_rebel, "object/building/military/shared_military_outpost_guard_house_rebel.iff")

object_building_military_shared_military_outpost_guard_tower_1 = SharedBuildingObjectTemplate:new {
	appearanceFilename = "appearance/mun_all_military_base_lookout_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 8,
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
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
	surfaceType = 1,

	targetable = 0,
	terrainModificationFileName = "",
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3846575780,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_outpost_guard_tower_1, "object/building/military/shared_military_outpost_guard_tower_1.iff")

object_building_military_shared_military_rebel_detachment_hq = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_rebel_detachment",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_rebel_detachment_hq.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_rebel_detachment",

	noBuildRadius = 0,

	objectName = "@building_name:military_rebel_detachment",
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

	clientObjectCRC = 27534614,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_rebel_detachment_hq, "object/building/military/shared_military_rebel_detachment_hq.iff")

object_building_military_shared_military_rebel_field_hospital = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_rebel_field_hospital",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_rebel_field_hospital.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_rebel_field_hospital",

	noBuildRadius = 0,

	objectName = "@building_name:military_rebel_field_hospital",
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

	clientObjectCRC = 2029763921,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_rebel_field_hospital, "object/building/military/shared_military_rebel_field_hospital.iff")

object_building_military_shared_military_rebel_forward_outpost = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_rebel_forward_outpost",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_rebel_forward_outpost.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_rebel_forward_outpost",

	noBuildRadius = 0,

	objectName = "@building_name:military_rebel_forward_outpost",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

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
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 107026323,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_rebel_forward_outpost, "object/building/military/shared_military_rebel_forward_outpost.iff")

object_building_military_shared_military_rebel_strategic_base = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_rebel_strategic_base",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_rebel_strategic_base.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_rebel_strategic_base",

	noBuildRadius = 0,

	objectName = "@building_name:military_rebel_strategic_base",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_police_station_rebl_s01.pob",

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

	clientObjectCRC = 1326158285,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_rebel_strategic_base, "object/building/military/shared_military_rebel_strategic_base.iff")

object_building_military_shared_military_rebel_tactical_center = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_rebel_tactical_center",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/military_rebel_tactical_center.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_rebel_tactical_center",

	noBuildRadius = 0,

	objectName = "@building_name:military_rebel_tactical_center",
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

	clientObjectCRC = 1040578282,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cave.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_military_rebel_tactical_center, "object/building/military/shared_military_rebel_tactical_center.iff")

object_building_military_shared_mun_all_military_tower_impl_guard_s01 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_tower_impl_guard_s01.pob",

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

	clientObjectCRC = 4049657385,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_mun_all_military_tower_impl_guard_s01, "object/building/military/shared_mun_all_military_tower_impl_guard_s01.iff")

object_building_military_shared_outpost_cloning_facility = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:cloning_facility",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/outpost_cloning_facility.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:cloning_facility",

	noBuildRadius = 0,

	objectName = "@building_name:cloning_facility",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

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

	clientObjectCRC = 1152524774,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cloning_facility.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_outpost_cloning_facility, "object/building/military/shared_outpost_cloning_facility.iff")

object_building_military_shared_outpost_cloning_facility_s02 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:cloning_facility",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/outpost_cloning_facility_s02.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:cloning_facility",

	noBuildRadius = 0,

	objectName = "@building_name:cloning_facility",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

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

	clientObjectCRC = 1476076676,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cloning_facility.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_outpost_cloning_facility_s02, "object/building/military/shared_outpost_cloning_facility_s02.iff")

object_building_military_shared_outpost_cloning_facility_s03 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:cloning_facility",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/outpost_cloning_facility_s03.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:cloning_facility",

	noBuildRadius = 0,

	objectName = "@building_name:cloning_facility",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

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

	clientObjectCRC = 519455497,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cloning_facility.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_outpost_cloning_facility_s03, "object/building/military/shared_outpost_cloning_facility_s03.iff")

object_building_military_shared_outpost_shed = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/outpost_shed.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

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
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1037564192,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_outpost_shed, "object/building/military/shared_outpost_shed.iff")

object_building_military_shared_outpost_shed_s02 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/outpost_shed_s02.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

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
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3955868475,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_outpost_shed_s02, "object/building/military/shared_outpost_shed_s02.iff")

object_building_military_shared_outpost_shed_s03 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/outpost_shed_s03.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

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
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2730796214,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_outpost_shed_s03, "object/building/military/shared_outpost_shed_s03.iff")

object_building_military_shared_outpost_shed_s04 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/outpost_shed_s04.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

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
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1495764898,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_outpost_shed_s04, "object/building/military/shared_outpost_shed_s04.iff")

object_building_military_shared_outpost_shed_s05 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:outpost_shed",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/outpost_shed_s05.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:outpost_shed",

	noBuildRadius = 0,

	objectName = "@building_name:outpost_shed",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

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
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 271247407,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_outpost_shed_s05, "object/building/military/shared_outpost_shed_s05.iff")

object_building_military_shared_outpost_starport = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:starport_corellia",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:starport_corellia",

	noBuildRadius = 0,

	objectName = "@building_name:starport_corellia",
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

	clientObjectCRC = 3035022053,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_starport.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_outpost_starport, "object/building/military/shared_outpost_starport.iff")

object_building_military_shared_pirate_outpost = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/shared_pirate_outpost.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

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
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2804382550,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_pirate_outpost, "object/building/military/shared_pirate_outpost.iff")

object_building_military_shared_pirate_warehouse = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/outpost_shed.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

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
	terrainModificationFileName = "terrain/mun_all_military_shed.lay",
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2437476511,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_pirate_warehouse, "object/building/military/shared_pirate_warehouse.iff")

object_building_military_shared_poi_all_alum_mine_s01 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_alum_mine_s01.pob",

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
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 568013580,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_poi_all_alum_mine_s01, "object/building/military/shared_poi_all_alum_mine_s01.iff")

object_building_military_shared_poi_all_impl_bunker_recon_outpost = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_impl_bunker_small_outpost_s01.pob",

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
	totalCellNumber = 49,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 339089158,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_poi_all_impl_bunker_recon_outpost, "object/building/military/shared_poi_all_impl_bunker_recon_outpost.iff")

object_building_military_shared_poi_all_jedi_temple_ruined = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_jedi_temple_ruined.pob",

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
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 149503406,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_poi_all_jedi_temple_ruined, "object/building/military/shared_poi_all_jedi_temple_ruined.iff")

object_building_military_shared_poi_all_mad_bio_mine_s01 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/poi_all_mad_bio_mine_s01.pob",

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
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2675557351,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_poi_all_mad_bio_mine_s01, "object/building/military/shared_poi_all_mad_bio_mine_s01.iff")

object_building_military_shared_rebel_hideout_themepark = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:military_guard_tower_1",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/rebel_hideout1.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:military_guard_tower_1",

	noBuildRadius = 0,

	objectName = "@building_name:military_guard_tower_1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_police_station_rebl_s01.pob",

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

	clientObjectCRC = 1446333372,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_rebel_hideout_themepark, "object/building/military/shared_rebel_hideout_themepark.iff")

object_building_military_shared_small_imperial_cloning_facility = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:cloning_facility",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/small_imperial_cloning_facility.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:cloning_facility",

	noBuildRadius = 0,

	objectName = "@building_name:cloning_facility",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_impl_s01.pob",

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

	clientObjectCRC = 2082976950,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cloning_facility.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_small_imperial_cloning_facility, "object/building/military/shared_small_imperial_cloning_facility.iff")

object_building_military_shared_small_imperial_cloning_facility_s02 = SharedBuildingObjectTemplate:new {
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

	detailedDescription = "@building_detail:cloning_facility",

	gameObjectType = 512,

	interiorLayoutFileName = "interiorlayout/small_imperial_cloning_facility_s02.ilf",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:cloning_facility",

	noBuildRadius = 0,

	objectName = "@building_name:cloning_facility",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_impl_s01.pob",

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

	clientObjectCRC = 972900942,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_cloning_facility.iff"}
}

ObjectTemplates:addClientTemplate(object_building_military_shared_small_imperial_cloning_facility_s02, "object/building/military/shared_small_imperial_cloning_facility_s02.iff")
