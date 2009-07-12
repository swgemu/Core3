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


object_creature_player_shared_bothan_female = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/bth_f.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_human_f.cdf",
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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:bothan",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 5,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_bothan_female, 491942670)

object_creature_player_shared_bothan_male = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/bth_m.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_human_m.cdf",
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
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:bothan",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 5,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_bothan_male, 1542946611)

object_creature_player_shared_human_female = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_f.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_human_f.cdf",
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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:human",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 0,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_human_female, 4294949865)

object_creature_player_shared_human_male = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_human_m.cdf",
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
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:human",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 0,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_human_male, 2937962913)

object_creature_player_shared_ithorian_female = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/ith_f.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_ithorian_f.cdf",
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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:ithorian",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 33,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_ithorian_female, 3017834515)

object_creature_player_shared_ithorian_male = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/ith_m.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_ithorian_m.cdf",
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
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:ithorian",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 33,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_ithorian_male, 951764932)

object_creature_player_shared_moncal_female = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/mon_f.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_moncal_f.cdf",
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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:moncalamari",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 3,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_moncal_female, 2553266142)

object_creature_player_shared_moncal_male = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/mon_m.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_moncal_m.cdf",
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
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:moncalamari",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 3,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_moncal_male, 3116914088)

object_creature_player_shared_rodian_female = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/rod_f.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_rodian_f.cdf",
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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:rodian",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 1,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_rodian_female, 3261342811)

object_creature_player_shared_rodian_male = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/rod_m.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_rodian_m.cdf",
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
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:rodian",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 1,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_rodian_male, 200920476)

object_creature_player_shared_sullustan_female = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/sul_f.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_sullustan_f.cdf",
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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:sullustan",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 49,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_sullustan_female, 359871514)

object_creature_player_shared_sullustan_male = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/sul_m.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_sullustan_m.cdf",
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
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:sullustan",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 49,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_sullustan_male, 194222500)

object_creature_player_shared_trandoshan_female = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/trn_f.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_trandoshan_f.cdf",
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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:trandoshan",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 2,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_trandoshan_female, 406594758)

object_creature_player_shared_trandoshan_male = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/trn_m.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_trandoshan_m.cdf",
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
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:trandoshan",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 2,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_trandoshan_male, 1355045775)

object_creature_player_shared_twilek_female = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/twk_f.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_twilek_f.cdf",
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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:twilek",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 6,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_twilek_female, 2224509660)

object_creature_player_shared_twilek_male = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/twk_m.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_twilek_m.cdf",
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
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:twilek",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 6,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_twilek_male, 4068532859)

object_creature_player_shared_wookiee_female = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/wke_f.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_wookiee_f.cdf",
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
	customizationVariableMapping = {{"/private/index_texture_1", "/shared_owner/index_texture_1"}},

	detailedDescription = "",

	gameObjectType = 1025,
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:wookiee",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 4,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_wookiee_female, 229336546)

object_creature_player_shared_wookiee_male = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/wke_m.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_wookiee_m.cdf",
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
	customizationVariableMapping = {{"/private/index_texture_1", "/shared_owner/index_texture_1"}},

	detailedDescription = "",

	gameObjectType = 1025,
	gender = 0,

	locationReservationRadius = 0,
	lookAtText = "@:e",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:wookiee",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 4,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_wookiee_male, 90470685)

object_creature_player_shared_zabrak_female = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/zab_f.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_zabrak_f.cdf",
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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:zabrak",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 7,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_zabrak_female, 2850250749)

object_creature_player_shared_zabrak_male = SharedCreatureObjectTemplate:new {
	acceleration = {0,0},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/zab_m.sat",
	arrangementDescriptor = "rider",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/player/client_shared_player_zabrak_m.cdf",
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
	lookAtText = "",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 1,
	noBuildRadius = 0,

	objectName = "@species:zabrak",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 26,
	slopeModPercent = 0.0125,
	slotDescriptor = {"inventory", "datapad", "default_weapon", "mission_bag", "hat", "hair", "earring_r", "earring_l", "eyes", "mouth", "neck", "cloak", "back", "chest1", "chest2", "chest3_r", "chest3_l", "bicep_r", "bicep_l", "bracer_lower_r", "bracer_upper_r", "bracer_lower_l", "bracer_upper_l", "wrist_r", "wrist_l", "gloves", "hold_r", "hold_l", "ring_r", "ring_l", "utility_belt", "pants1", "pants2", "shoes", "ghost", "bank"},
	snapToTerrain = 1,
	socketDestinations = {},
	species = 7,
	speed = {0,0},
	stepHeight = 0.5,
	structureFootprintFileName = "",
	surfaceType = 0,
	swimHeight = 1,

	targetable = 1,
	turnRate = {0,0},

	useStructureFootprintOutline = 0,

	warpTolerance = 17,
	waterModPercent = 0.75
}

ObjectTemplates:addTemplate(object_creature_player_shared_zabrak_male, 3791955286)
