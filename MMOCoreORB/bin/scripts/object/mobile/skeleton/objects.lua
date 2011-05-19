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


object_mobile_skeleton_shared_acklay = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 2.3,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.5,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 89,
	speed = {8.28,4.74},
	stepHeight = 3,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 3,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 3915581743,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_acklay, "object/mobile/skeleton/shared_acklay.iff")

object_mobile_skeleton_shared_astromech = SharedCreatureObjectTemplate:new {
	acceleration = {4,2},
	animationMapFilename = "",
	appearanceFilename = "",
	arrangementDescriptors = {"ship_droid"},

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1024,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionHeight = 0.5,
	collisionLength = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.45,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 204,
	speed = {7,2},
	stepHeight = 0.25,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 994908092,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_astromech, "object/mobile/skeleton/shared_astromech.iff")

object_mobile_skeleton_shared_base_insect_moth = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 0,
	speed = {5.5,2},
	stepHeight = 0.75,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 1820074321,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_base_insect_moth, "object/mobile/skeleton/shared_base_insect_moth.iff")

object_mobile_skeleton_shared_bat = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.5,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@monster_detail:base_monster",

	gameObjectType = 1024,
	gender = 0,

	locationReservationRadius = 0,
	lookAtText = "@monster_lookat:base_monster",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@monster_name:base_monster",
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 103,
	speed = {9.05,3.02},
	stepHeight = 0.9,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 2504466576,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_bat, "object/mobile/skeleton/shared_bat.iff")

object_mobile_skeleton_shared_bird_finch = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 0.3,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.1,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 155,
	speed = {9.9,3.07},
	stepHeight = 1.62,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 1000541852,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_bird_finch, "object/mobile/skeleton/shared_bird_finch.iff")

object_mobile_skeleton_shared_bird_giant = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 2,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 151,
	speed = {21.6,15},
	stepHeight = 1.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 519570189,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_bird_giant, "object/mobile/skeleton/shared_bird_giant.iff")

object_mobile_skeleton_shared_bird_turkey = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 0.55,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.3,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 93,
	speed = {6.13,0.61},
	stepHeight = 0.2,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 1413515142,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_bird_turkey, "object/mobile/skeleton/shared_bird_turkey.iff")

object_mobile_skeleton_shared_camel = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
	animationMapFilename = "",
	appearanceFilename = "",
	arrangementDescriptors = {},

	cameraHeight = 3.9,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1024,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionHeight = 1.8,
	collisionLength = 5.5,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0.5,
	collisionRadius = 1.5,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 94,
	speed = {8.5,1.69},
	stepHeight = 1.25,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 3,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 2223413436,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_camel, "object/mobile/skeleton/shared_camel.iff")

object_mobile_skeleton_shared_canine = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 1.3,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.5,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 85,
	speed = {9.03,0.84},
	stepHeight = 0.3,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 825801147,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_canine, "object/mobile/skeleton/shared_canine.iff")

object_mobile_skeleton_shared_cat_domestic = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.3,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 137,
	speed = {6,1.42},
	stepHeight = 0.25,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 1826010896,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_cat_domestic, "object/mobile/skeleton/shared_cat_domestic.iff")

object_mobile_skeleton_shared_cat_predatory = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 3.14,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.5,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 146,
	speed = {13.42,0.81},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 284042171,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_cat_predatory, "object/mobile/skeleton/shared_cat_predatory.iff")

object_mobile_skeleton_shared_cll8 = SharedCreatureObjectTemplate:new {
	acceleration = {4,2},
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
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 213,
	speed = {5,2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 3021854628,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_cll8, "object/mobile/skeleton/shared_cll8.iff")

object_mobile_skeleton_shared_dewback = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
	animationMapFilename = "",
	appearanceFilename = "",
	arrangementDescriptors = {},

	cameraHeight = 2.7,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1024,
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
	containerType = 1,
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
	postureAlignToTerrain = {1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 90,
	speed = {9.75,0.95},
	stepHeight = 0.8,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1.5,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 892528452,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_dewback, "object/mobile/skeleton/shared_dewback.iff")

object_mobile_skeleton_shared_droid_2 = SharedCreatureObjectTemplate:new {
	acceleration = {4,2},
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
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 224,
	speed = {7,2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 2856144413,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_droid_2, "object/mobile/skeleton/shared_droid_2.iff")

object_mobile_skeleton_shared_droideka = SharedCreatureObjectTemplate:new {
	acceleration = {4,2},
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
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 210,
	speed = {8,2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 4190971251,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_droideka, "object/mobile/skeleton/shared_droideka.iff")

object_mobile_skeleton_shared_dz70 = SharedCreatureObjectTemplate:new {
	acceleration = {4,2},
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
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 222,
	speed = {7,2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 2699879603,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_dz70, "object/mobile/skeleton/shared_dz70.iff")

object_mobile_skeleton_shared_eg6 = SharedCreatureObjectTemplate:new {
	acceleration = {4,2},
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
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 215,
	speed = {1.3,0.2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 3003303428,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_eg6, "object/mobile/skeleton/shared_eg6.iff")

object_mobile_skeleton_shared_elephant = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
	animationMapFilename = "",
	appearanceFilename = "",
	arrangementDescriptors = {},

	cameraHeight = 2.5,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1024,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionHeight = 1.8,
	collisionLength = 4.3,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 2.2,
	containerType = 1,
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
	postureAlignToTerrain = {1,1,1,1,1,1,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 62,
	speed = {6.98,0.78},
	stepHeight = 0.75,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 4284811148,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_elephant, "object/mobile/skeleton/shared_elephant.iff")

object_mobile_skeleton_shared_elephant_bantha = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
	animationMapFilename = "",
	appearanceFilename = "",
	arrangementDescriptors = {},

	cameraHeight = 2.75,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1024,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionHeight = 1.8,
	collisionLength = 4.3,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 2.2,
	containerType = 1,
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
	postureAlignToTerrain = {1,1,1,1,1,1,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 62,
	speed = {6.98,0.78},
	stepHeight = 0.75,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 2.38,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 1623233094,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_elephant_bantha, "object/mobile/skeleton/shared_elephant_bantha.iff")

object_mobile_skeleton_shared_fambaa = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 11.16,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 4.2,
	containerType = 1,
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
	postureAlignToTerrain = {1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 97,
	speed = {6.85,3},
	stepHeight = 2,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 1277611918,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_fambaa, "object/mobile/skeleton/shared_fambaa.iff")

object_mobile_skeleton_shared_frog = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 0.4,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.2,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 81,
	speed = {7.57,0.46},
	stepHeight = 0.15,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 2783556290,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_frog, "object/mobile/skeleton/shared_frog.iff")

object_mobile_skeleton_shared_giraffe = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 4.7,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 1.8,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 167,
	speed = {6.53,0.94},
	stepHeight = 1.2,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 2416872297,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_giraffe, "object/mobile/skeleton/shared_giraffe.iff")

object_mobile_skeleton_shared_goat = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 2.5,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 1.25,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 123,
	speed = {6.38,1.29},
	stepHeight = 0.75,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 3334329739,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_goat, "object/mobile/skeleton/shared_goat.iff")

object_mobile_skeleton_shared_griffon = SharedCreatureObjectTemplate:new {
	acceleration = {3.7,2},
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
	collisionLength = 4,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 2,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 113,
	speed = {6.7,3.75},
	stepHeight = 1.35,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 1997066566,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_griffon, "object/mobile/skeleton/shared_griffon.iff")

object_mobile_skeleton_shared_horse = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 3.2,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 1.2,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 110,
	speed = {7.75,1.33},
	stepHeight = 0.75,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 2297855719,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_horse, "object/mobile/skeleton/shared_horse.iff")

object_mobile_skeleton_shared_humanoid = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "",
	arrangementDescriptors = {},

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1025,
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
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 1025,
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
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 0,
	speed = {6,2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.5,

	clientObjectCRC = 1714909795,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_humanoid, "object/mobile/skeleton/shared_humanoid.iff")

object_mobile_skeleton_shared_insect_basic = SharedCreatureObjectTemplate:new {
	acceleration = {4,2},
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
	collisionLength = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.5,
	containerType = 1,
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
	postureAlignToTerrain = {1,1,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 166,
	speed = {7.25,0.88},
	stepHeight = 0.2,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 422447477,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_insect_basic, "object/mobile/skeleton/shared_insect_basic.iff")

object_mobile_skeleton_shared_insect_mantis = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 2.3,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.5,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 89,
	speed = {8.28,4.74},
	stepHeight = 0.75,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 4047561864,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_insect_mantis, "object/mobile/skeleton/shared_insect_mantis.iff")

object_mobile_skeleton_shared_insect_moth = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.25,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 78,
	speed = {7.06,3.04},
	stepHeight = 1.35,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 3715444431,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_insect_moth, "object/mobile/skeleton/shared_insect_moth.iff")

object_mobile_skeleton_shared_ito = SharedCreatureObjectTemplate:new {
	acceleration = {4,2},
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
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 211,
	speed = {6,2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 4016222327,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_ito, "object/mobile/skeleton/shared_ito.iff")

object_mobile_skeleton_shared_kaadu = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
	animationMapFilename = "",
	appearanceFilename = "",
	arrangementDescriptors = {},

	cameraHeight = 2.2,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1024,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionHeight = 1.8,
	collisionLength = 3.1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.75,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 125,
	speed = {11.5,2.47},
	stepHeight = 0.75,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1.8,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 3497999971,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_kaadu, "object/mobile/skeleton/shared_kaadu.iff")

object_mobile_skeleton_shared_lin_demolition = SharedCreatureObjectTemplate:new {
	acceleration = {4,2},
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
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 208,
	speed = {6,2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 765355707,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_lin_demolition, "object/mobile/skeleton/shared_lin_demolition.iff")

object_mobile_skeleton_shared_lizard_basic = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 3.2,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.7,
	containerType = 1,
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
	postureAlignToTerrain = {1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 91,
	speed = {7.23,1.23},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 2532063942,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_lizard_basic, "object/mobile/skeleton/shared_lizard_basic.iff")

object_mobile_skeleton_shared_lizard_giant = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 22.13,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 9,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 132,
	speed = {11.22,3.28},
	stepHeight = 0.75,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {45,90},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 873783873,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_lizard_giant, "object/mobile/skeleton/shared_lizard_giant.iff")

object_mobile_skeleton_shared_mouse_droid = SharedCreatureObjectTemplate:new {
	acceleration = {4,2},
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
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 214,
	speed = {6,2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 340337386,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_mouse_droid, "object/mobile/skeleton/shared_mouse_droid.iff")

object_mobile_skeleton_shared_mynock = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.25,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 145,
	speed = {8.11,3.03},
	stepHeight = 1.4,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 1147356714,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_mynock, "object/mobile/skeleton/shared_mynock.iff")

object_mobile_skeleton_shared_orb = SharedCreatureObjectTemplate:new {
	acceleration = {4,2},
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
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 225,
	speed = {6,2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 984617406,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_orb, "object/mobile/skeleton/shared_orb.iff")

object_mobile_skeleton_shared_pig = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 1.7,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0.4,
	collisionRadius = 0.5,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 202,
	speed = {9.5,1.26},
	stepHeight = 0.75,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 1813957157,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_pig, "object/mobile/skeleton/shared_pig.iff")

object_mobile_skeleton_shared_probe_droid = SharedCreatureObjectTemplate:new {
	acceleration = {4,2},
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
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 216,
	speed = {9,2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 3856845356,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_probe_droid, "object/mobile/skeleton/shared_probe_droid.iff")

object_mobile_skeleton_shared_protocol_droid = SharedCreatureObjectTemplate:new {
	acceleration = {4,2},
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
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 217,
	speed = {3,1},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 3037551555,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_protocol_droid, "object/mobile/skeleton/shared_protocol_droid.iff")

object_mobile_skeleton_shared_rabbit = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0.1,
	collisionRadius = 0.3,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 92,
	speed = {3.38,1.13},
	stepHeight = 0.25,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 161991049,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_rabbit, "object/mobile/skeleton/shared_rabbit.iff")

object_mobile_skeleton_shared_rancor = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 5.6,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 2.2,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 161,
	speed = {7.01,1.25},
	stepHeight = 1.6,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 270823856,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_rancor, "object/mobile/skeleton/shared_rancor.iff")

object_mobile_skeleton_shared_rat = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 1.1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.3,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 199,
	speed = {7.76,0.75},
	stepHeight = 0.25,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 1932908380,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_rat, "object/mobile/skeleton/shared_rat.iff")

object_mobile_skeleton_shared_robo_bartender = SharedCreatureObjectTemplate:new {
	acceleration = {4,2},
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
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 205,
	speed = {6,2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 2976038956,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_robo_bartender, "object/mobile/skeleton/shared_robo_bartender.iff")

object_mobile_skeleton_shared_simian_ape = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 189,
	speed = {8.65,0.57},
	stepHeight = 0.75,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 1735902555,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_simian_ape, "object/mobile/skeleton/shared_simian_ape.iff")

object_mobile_skeleton_shared_simian_monkey = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionRadius = 0.4,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 179,
	speed = {7.75,1.3},
	stepHeight = 0.75,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 75660389,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_simian_monkey, "object/mobile/skeleton/shared_simian_monkey.iff")

object_mobile_skeleton_shared_snake = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 5,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.2,
	containerType = 1,
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
	postureAlignToTerrain = {1,1,1,1,1,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 98,
	speed = {5.65,3.5},
	stepHeight = 0.25,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 253409232,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_snake, "object/mobile/skeleton/shared_snake.iff")

object_mobile_skeleton_shared_spider = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
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
	collisionLength = 3.04,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0,
	collisionRadius = 0.5,
	containerType = 1,
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
	postureAlignToTerrain = {1,1,1,1,1,1,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 118,
	speed = {9.34,2.58},
	stepHeight = 0.75,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 4213186397,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_spider, "object/mobile/skeleton/shared_spider.iff")

object_mobile_skeleton_shared_spider_droid = SharedCreatureObjectTemplate:new {
	acceleration = {4,2},
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
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 219,
	speed = {6,2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 460559210,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_spider_droid, "object/mobile/skeleton/shared_spider_droid.iff")

object_mobile_skeleton_shared_tauntaun = SharedCreatureObjectTemplate:new {
	acceleration = {9,3},
	animationMapFilename = "",
	appearanceFilename = "",
	arrangementDescriptors = {},

	cameraHeight = 1.35,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1024,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionHeight = 1.8,
	collisionLength = 2.8,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	collisionOffsetX = 0,
	collisionOffsetZ = 0.4,
	collisionRadius = 0.5,
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 88,
	speed = {9.39,1.36},
	stepHeight = 0.75,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1.2,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 3679278095,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_tauntaun, "object/mobile/skeleton/shared_tauntaun.iff")

object_mobile_skeleton_shared_tt8l = SharedCreatureObjectTemplate:new {
	acceleration = {4,2},
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
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 209,
	speed = {6,2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 2778895664,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_tt8l, "object/mobile/skeleton/shared_tt8l.iff")

object_mobile_skeleton_shared_tt8l_y7 = SharedCreatureObjectTemplate:new {
	acceleration = {4,2},
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
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 221,
	speed = {6,2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 1315980442,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_tt8l_y7, "object/mobile/skeleton/shared_tt8l_y7.iff")

object_mobile_skeleton_shared_wed_treadwell = SharedCreatureObjectTemplate:new {
	acceleration = {4,2},
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
	containerType = 1,
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
	slotDescriptors = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 223,
	speed = {6,2},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	totalCellNumber = 0,
	turnRate = {90,180},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75,

	clientObjectCRC = 2765187251,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_skeleton_shared_wed_treadwell, "object/mobile/skeleton/shared_wed_treadwell.iff")
