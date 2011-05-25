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


object_mobile_vendor_shared_aqualish_female = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/aqualish_f_01.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_dressed_commoner_tatooine_alien_m_01.cdf",
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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "@npc_lookat:aqualish_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:aqualish_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.85, 0.9},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 9,
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

	clientObjectCRC = 3405269957,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff", "object/mobile/shared_aqualish_male.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_aqualish_female, "object/mobile/vendor/shared_aqualish_female.iff")

object_mobile_vendor_shared_aqualish_male = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/aqualish_m_01.sat",
	arrangementDescriptorFilename = "",

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
	lookAtText = "@npc_lookat:aqualish_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:aqualish_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.89, 0.95},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 9,
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

	clientObjectCRC = 3560977643,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_aqualish_male, "object/mobile/vendor/shared_aqualish_male.iff")

object_mobile_vendor_shared_bith_female = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/bith_f.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_dressed_commoner_tatooine_bith_m_03.cdf",
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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "@npc_lookat:bith_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:bith_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.75, 0.875},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 12,
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

	clientObjectCRC = 2071723635,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff", "object/mobile/shared_bith_male.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_bith_female, "object/mobile/vendor/shared_bith_female.iff")

object_mobile_vendor_shared_bith_male = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/bith_m.sat",
	arrangementDescriptorFilename = "",

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
	lookAtText = "@npc_lookat:bith_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:bith_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.75, 0.875},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 12,
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

	clientObjectCRC = 1947827481,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_bith_male, "object/mobile/vendor/shared_bith_male.iff")

object_mobile_vendor_shared_bothan_female = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/bth_f.sat",
	arrangementDescriptorFilename = "",

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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "@npc_lookat:bothan_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:bothan_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.76, 0.88},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 5,
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

	clientObjectCRC = 132576068,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_bothan_female, "object/mobile/vendor/shared_bothan_female.iff")

object_mobile_vendor_shared_bothan_male = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/bth_m.sat",
	arrangementDescriptorFilename = "",

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
	lookAtText = "@npc_lookat:bothan_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:bothan_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.76, 0.88},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 5,
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

	clientObjectCRC = 2454014624,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_bothan_male, "object/mobile/vendor/shared_bothan_male.iff")

object_mobile_vendor_shared_devaronian_male = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/devaronian_m.sat",
	arrangementDescriptorFilename = "",

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
	lookAtText = "@npc_lookat:devaronian_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:devaronian_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.8, 0.95},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 17,
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

	clientObjectCRC = 2095623604,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_devaronian_male, "object/mobile/vendor/shared_devaronian_male.iff")

object_mobile_vendor_shared_gran_male = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/gran_m.sat",
	arrangementDescriptorFilename = "",

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
	lookAtText = "@npc_lookat:gran_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:gran_base_male",
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
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 28,
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

	clientObjectCRC = 3310863058,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_gran_male, "object/mobile/vendor/shared_gran_male.iff")

object_mobile_vendor_shared_human_female = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_f.sat",
	arrangementDescriptorFilename = "",

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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "@npc_lookat:human_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:human_base_female",
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
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
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

	clientObjectCRC = 847857791,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_human_female, "object/mobile/vendor/shared_human_female.iff")

object_mobile_vendor_shared_human_male = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

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
	lookAtText = "@npc_lookat:human_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:human_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {1, 1.12},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
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

	clientObjectCRC = 1639282596,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_human_male, "object/mobile/vendor/shared_human_male.iff")

object_mobile_vendor_shared_ishi_tib_male = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/ishi_tib_m.sat",
	arrangementDescriptorFilename = "",

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
	lookAtText = "@npc_lookat:ishi_tib_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:ishi_tib_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.85, 0.95},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 32,
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

	clientObjectCRC = 2586473426,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_ishi_tib_male, "object/mobile/vendor/shared_ishi_tib_male.iff")

object_mobile_vendor_shared_ithorian_female = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/ith_f.sat",
	arrangementDescriptorFilename = "",

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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "@npc_lookat:ithorian_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:ithorian_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.9, 1.3},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 33,
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

	clientObjectCRC = 2809871871,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_ithorian_female, "object/mobile/vendor/shared_ithorian_female.iff")

object_mobile_vendor_shared_ithorian_male = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/ith_m.sat",
	arrangementDescriptorFilename = "",

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
	lookAtText = "@npc_lookat:ithorian_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:ithorian_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.9, 1.3},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 33,
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

	clientObjectCRC = 571361166,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_ithorian_male, "object/mobile/vendor/shared_ithorian_male.iff")

object_mobile_vendor_shared_moncal_female = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/mon_f.sat",
	arrangementDescriptorFilename = "",

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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "@npc_lookat:moncal_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:moncal_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.88, 1},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 3,
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

	clientObjectCRC = 2191212436,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_moncal_female, "object/mobile/vendor/shared_moncal_female.iff")

object_mobile_vendor_shared_moncal_male = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/mon_m.sat",
	arrangementDescriptorFilename = "",

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
	lookAtText = "@npc_lookat:moncal_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:moncal_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.88, 1},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 3,
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

	clientObjectCRC = 1887068219,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_moncal_male, "object/mobile/vendor/shared_moncal_male.iff")

object_mobile_vendor_shared_nikto_male = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/nikto_m.sat",
	arrangementDescriptorFilename = "",

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
	lookAtText = "@npc_lookat:nikto_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:nikto_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.8, 0.95},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 42,
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

	clientObjectCRC = 2537817486,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_nikto_male, "object/mobile/vendor/shared_nikto_male.iff")

object_mobile_vendor_shared_quarren_male = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/quarren_m.sat",
	arrangementDescriptorFilename = "",

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
	lookAtText = "@npc_lookat:quarren_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:quarren_base_male",
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
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 46,
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

	clientObjectCRC = 4181918992,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_quarren_male, "object/mobile/vendor/shared_quarren_male.iff")

object_mobile_vendor_shared_rodian_female = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/rod_f.sat",
	arrangementDescriptorFilename = "",

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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "@npc_lookat:rodian_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:rodian_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.88, 1},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 1,
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

	clientObjectCRC = 3637552145,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_rodian_female, "object/mobile/vendor/shared_rodian_female.iff")

object_mobile_vendor_shared_rodian_male = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/rod_m.sat",
	arrangementDescriptorFilename = "",

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
	lookAtText = "@npc_lookat:rodian_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:rodian_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.88, 1},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 1,
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

	clientObjectCRC = 3259758607,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_rodian_male, "object/mobile/vendor/shared_rodian_male.iff")

object_mobile_vendor_shared_sullustan_female = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/sul_f.sat",
	arrangementDescriptorFilename = "",

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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "@npc_lookat:sullustan_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:sullustan_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {1, 1.12},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 49,
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

	clientObjectCRC = 3520820662,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_sullustan_female, "object/mobile/vendor/shared_sullustan_female.iff")

object_mobile_vendor_shared_sullustan_male = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/sul_m.sat",
	arrangementDescriptorFilename = "",

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
	lookAtText = "@npc_lookat:sullustan_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:sullustan_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.76, 0.88},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 49,
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

	clientObjectCRC = 3699957250,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_sullustan_male, "object/mobile/vendor/shared_sullustan_male.iff")

object_mobile_vendor_shared_trandoshan_female = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/trn_f.sat",
	arrangementDescriptorFilename = "",

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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "@npc_lookat:trandoshan_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:trandoshan_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {1.12, 1.24},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 2,
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

	clientObjectCRC = 4277366403,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_trandoshan_female, "object/mobile/vendor/shared_trandoshan_female.iff")

object_mobile_vendor_shared_trandoshan_male = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/trn_m.sat",
	arrangementDescriptorFilename = "",

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
	lookAtText = "@npc_lookat:trandoshan_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:trandoshan_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {1.12, 1.24},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 2,
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

	clientObjectCRC = 1147135587,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_trandoshan_male, "object/mobile/vendor/shared_trandoshan_male.iff")

object_mobile_vendor_shared_twilek_female = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/twk_f.sat",
	arrangementDescriptorFilename = "",

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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "@npc_lookat:twilek_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:twilek_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {1, 1.12},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 6,
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

	clientObjectCRC = 2653147798,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_twilek_female, "object/mobile/vendor/shared_twilek_female.iff")

object_mobile_vendor_shared_twilek_male = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/twk_m.sat",
	arrangementDescriptorFilename = "",

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
	lookAtText = "@npc_lookat:twilek_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:twilek_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {1, 1.12},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 6,
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

	clientObjectCRC = 993187816,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_twilek_male, "object/mobile/vendor/shared_twilek_male.iff")

object_mobile_vendor_shared_weequay_male = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/weequay_m.sat",
	arrangementDescriptorFilename = "",

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
	lookAtText = "@npc_lookat:weequay_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:weequay_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.75, 0.85},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 55,
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

	clientObjectCRC = 2188503843,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_weequay_male, "object/mobile/vendor/shared_weequay_male.iff")

object_mobile_vendor_shared_wookiee_female = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/wke_f.sat",
	arrangementDescriptorFilename = "",

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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "@npc_lookat:wookiee_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:wookiee_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {1.24, 1.36},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 4,
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

	clientObjectCRC = 3668976196,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_wookiee_female, "object/mobile/vendor/shared_wookiee_female.iff")

object_mobile_vendor_shared_wookiee_male = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/wke_m.sat",
	arrangementDescriptorFilename = "",

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
	lookAtText = "@npc_lookat:wookiee_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:wookiee_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {1.24, 1.36},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 4,
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

	clientObjectCRC = 3356658315,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_wookiee_male, "object/mobile/vendor/shared_wookiee_male.iff")

object_mobile_vendor_shared_zabrak_female = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/zab_f.sat",
	arrangementDescriptorFilename = "",

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
	gender = 1,

	locationReservationRadius = 0,
	lookAtText = "@npc_lookat:zabrak_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:zabrak_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.94, 1.06},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 7,
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

	clientObjectCRC = 3008880567,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_zabrak_female, "object/mobile/vendor/shared_zabrak_female.iff")

object_mobile_vendor_shared_zabrak_male = SharedCreatureObjectTemplate:new {
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/zab_m.sat",
	arrangementDescriptorFilename = "",

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
	lookAtText = "@npc_lookat:zabrak_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 0,
	noBuildRadius = 0,

	objectName = "@npc_name:zabrak_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.94, 1.06},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 7,
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

	clientObjectCRC = 733384901,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
}

ObjectTemplates:addClientTemplate(object_mobile_vendor_shared_zabrak_male, "object/mobile/vendor/shared_zabrak_male.iff")
