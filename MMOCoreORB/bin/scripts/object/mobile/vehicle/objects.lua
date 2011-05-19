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


object_mobile_vehicle_shared_jetpack = SharedCreatureObjectTemplate:new {
	acceleration = {8,3},
	animationMapFilename = "",
	appearanceFilename = "appearance/pv_jetpack_mandalorian.sat",
	arrangementDescriptors = {},

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 65537,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionHeight = 1.8,
	collisionLength = 6.8,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 2.7,
	containerType = 5,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@monster_detail:jetpack",

	gameObjectType = 65537,
	gender = 0,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@monster_name:jetpack",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.23,
	slotDescriptors = {"rider", "inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 90,
	speed = {13,7},
	stepHeight = 2,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 0,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {77,154},

	useStructureFootprintOutline = 0,

	warpTolerance = 20,
	waterModPercent = 0.75,

	clientObjectCRC = 1613040434,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/vehicle/shared_vehicle_base.iff", "object/mobile/vehicle/shared_landspeeder_base.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vehicle_shared_jetpack, "object/mobile/vehicle/shared_jetpack.iff")

object_mobile_vehicle_shared_landspeeder_av21 = SharedCreatureObjectTemplate:new {
	acceleration = {10,3},
	animationMapFilename = "",
	appearanceFilename = "appearance/pv_landspeeder_av21.sat",
	arrangementDescriptors = {},

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 65537,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionHeight = 1.8,
	collisionLength = 8.8,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 2.7,
	containerType = 5,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@monster_detail:landspeeder_av21",

	gameObjectType = 65537,
	gender = 0,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@monster_name:landspeeder_av21",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.23,
	slotDescriptors = {"rider", "inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 90,
	speed = {17,9},
	stepHeight = 2,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 0,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {77,154},

	useStructureFootprintOutline = 0,

	warpTolerance = 20,
	waterModPercent = 0.75,

	clientObjectCRC = 2842025402,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/vehicle/shared_vehicle_base.iff", "object/mobile/vehicle/shared_landspeeder_base.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vehicle_shared_landspeeder_av21, "object/mobile/vehicle/shared_landspeeder_av21.iff")

object_mobile_vehicle_shared_landspeeder_base = SharedCreatureObjectTemplate:new {
	acceleration = {2,2},
	animationMapFilename = "",
	appearanceFilename = "",
	arrangementDescriptors = {},

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 65537,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionHeight = 1.8,
	collisionLength = 1.5,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.5,
	containerType = 5,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 65537,
	gender = 0,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@obj_n:unknown_creature",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptors = {"rider", "inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 0,
	speed = {6,2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 0,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 634510067,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/vehicle/shared_vehicle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vehicle_shared_landspeeder_base, "object/mobile/vehicle/shared_landspeeder_base.iff")

object_mobile_vehicle_shared_landspeeder_x31 = SharedCreatureObjectTemplate:new {
	acceleration = {7,2},
	animationMapFilename = "",
	appearanceFilename = "appearance/pv_landspeeder_luke.sat",
	arrangementDescriptors = {},

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 65537,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionHeight = 1.8,
	collisionLength = 6.8,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 2.7,
	containerType = 5,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@monster_detail:landspeeder_x31",

	gameObjectType = 65537,
	gender = 0,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@monster_name:landspeeder_x31",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.23,
	slotDescriptors = {"rider", "inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 90,
	speed = {11,6},
	stepHeight = 2,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 0,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {77,154},

	useStructureFootprintOutline = 0,

	warpTolerance = 20,
	waterModPercent = 0.75,

	clientObjectCRC = 658152450,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/vehicle/shared_vehicle_base.iff", "object/mobile/vehicle/shared_landspeeder_base.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vehicle_shared_landspeeder_x31, "object/mobile/vehicle/shared_landspeeder_x31.iff")

object_mobile_vehicle_shared_landspeeder_x34 = SharedCreatureObjectTemplate:new {
	acceleration = {8,3},
	animationMapFilename = "",
	appearanceFilename = "appearance/pv_landspeeder_luke.sat",
	arrangementDescriptors = {},

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 65537,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionHeight = 1.8,
	collisionLength = 6.8,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 2.7,
	containerType = 5,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@monster_detail:landspeeder_x34",

	gameObjectType = 65537,
	gender = 0,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@monster_name:landspeeder_x34",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.23,
	slotDescriptors = {"rider", "inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 90,
	speed = {13,7},
	stepHeight = 2,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 0,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {77,154},

	useStructureFootprintOutline = 0,

	warpTolerance = 20,
	waterModPercent = 0.75,

	clientObjectCRC = 1321433100,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/vehicle/shared_vehicle_base.iff", "object/mobile/vehicle/shared_landspeeder_base.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vehicle_shared_landspeeder_x34, "object/mobile/vehicle/shared_landspeeder_x34.iff")

object_mobile_vehicle_shared_landspeeder_xp38 = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
	animationMapFilename = "",
	appearanceFilename = "appearance/monstrosity.sat",
	arrangementDescriptors = {},

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/creature/client_shared_cr_dewback.cdf",
	clientGameObjectType = 65537,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionHeight = 1.8,
	collisionLength = 6.8,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 2.7,
	containerType = 5,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@monster_detail:landspeeder_xp38",

	gameObjectType = 65537,
	gender = 0,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@monster_name:landspeeder_xp38",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptors = {"rider", "inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 90,
	speed = {9.75,0.95},
	stepHeight = 0.8,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 0,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 1064205223,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/vehicle/shared_vehicle_base.iff", "object/mobile/vehicle/shared_landspeeder_base.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vehicle_shared_landspeeder_xp38, "object/mobile/vehicle/shared_landspeeder_xp38.iff")

object_mobile_vehicle_shared_speederbike = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
	animationMapFilename = "",
	appearanceFilename = "appearance/pv_speeder_bike.sat",
	arrangementDescriptors = {},

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 65537,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionHeight = 1.8,
	collisionLength = 3.8,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 1.15,
	containerType = 5,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@monster_detail:speederbike",

	gameObjectType = 65537,
	gender = 0,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@monster_name:speederbike",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.126,
	slotDescriptors = {"rider", "inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 90,
	speed = {15,8},
	stepHeight = 0.8,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 0,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 1922373615,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/vehicle/shared_vehicle_base.iff", "object/mobile/vehicle/shared_landspeeder_base.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vehicle_shared_speederbike, "object/mobile/vehicle/shared_speederbike.iff")

object_mobile_vehicle_shared_speederbike_base = SharedCreatureObjectTemplate:new {
	acceleration = {2,2},
	animationMapFilename = "",
	appearanceFilename = "",
	arrangementDescriptors = {},

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 65537,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionHeight = 1.8,
	collisionLength = 1.5,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.5,
	containerType = 5,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 65537,
	gender = 0,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@obj_n:unknown_creature",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptors = {"rider", "inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 0,
	speed = {6,2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 0,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 2115869795,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/vehicle/shared_vehicle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vehicle_shared_speederbike_base, "object/mobile/vehicle/shared_speederbike_base.iff")

object_mobile_vehicle_shared_speederbike_flash = SharedCreatureObjectTemplate:new {
	acceleration = {10,3},
	animationMapFilename = "",
	appearanceFilename = "appearance/pv_flash_speeder.sat",
	arrangementDescriptors = {},

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 65537,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionHeight = 1.8,
	collisionLength = 2.8,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 1.17,
	containerType = 5,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@monster_detail:speederbike_flash",

	gameObjectType = 65537,
	gender = 0,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@monster_name:speederbike_flash",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.056,
	slotDescriptors = {"rider", "inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 90,
	speed = {17,9},
	stepHeight = 0.8,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 0,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {103,205},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 5125428,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/vehicle/shared_vehicle_base.iff", "object/mobile/vehicle/shared_landspeeder_base.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vehicle_shared_speederbike_flash, "object/mobile/vehicle/shared_speederbike_flash.iff")

object_mobile_vehicle_shared_speederbike_swoop = SharedCreatureObjectTemplate:new {
	acceleration = {10,3},
	animationMapFilename = "",
	appearanceFilename = "appearance/pv_swoop_bike.sat",
	arrangementDescriptors = {},

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 65537,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionHeight = 1.8,
	collisionLength = 2.8,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 1.17,
	containerType = 5,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@monster_detail:speederbike_swoop",

	gameObjectType = 65537,
	gender = 0,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@monster_name:speederbike_swoop",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.056,
	slotDescriptors = {"rider", "inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 90,
	speed = {17,9},
	stepHeight = 0.8,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 0,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {103,205},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 2943197007,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/vehicle/shared_vehicle_base.iff", "object/mobile/vehicle/shared_landspeeder_base.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vehicle_shared_speederbike_swoop, "object/mobile/vehicle/shared_speederbike_swoop.iff")

object_mobile_vehicle_shared_vehicle_base = SharedCreatureObjectTemplate:new {
	acceleration = {2,2},
	animationMapFilename = "",
	appearanceFilename = "",
	arrangementDescriptors = {},

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1024,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionHeight = 1.8,
	collisionLength = 1.5,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.5,
	containerType = 5,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 1024,
	gender = 0,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@obj_n:unknown_creature",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptors = {"rider", "inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 0,
	speed = {6,2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 0,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 1605130582,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vehicle_shared_vehicle_base, "object/mobile/vehicle/shared_vehicle_base.iff")
