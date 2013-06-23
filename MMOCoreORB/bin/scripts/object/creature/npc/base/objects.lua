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


object_creature_npc_base_shared_aqualish_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_aqualish_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/aqualish_f_01.sat",
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
	lookAtText = "@npc_lookat:aqualish_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:aqualish_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 1,
	rangedIntCustomizationVariables = {},

	scale = {0.85, 0.9},
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

	clientObjectCRC = 2762844902,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_aqualish_base_female, "object/creature/npc/base/shared_aqualish_base_female.iff")

object_creature_npc_base_shared_aqualish_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_aqualish_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:aqualish_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 1,
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

	clientObjectCRC = 643792170,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_aqualish_base_male, "object/creature/npc/base/shared_aqualish_base_male.iff")

object_creature_npc_base_shared_aqualish_s02_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_aqualish_s02_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/aqualish_f_02.sat",
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
	lookAtText = "@npc_lookat:aqualish_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:aqualish_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 1,
	rangedIntCustomizationVariables = {},

	scale = {0.85, 0.9},
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

	clientObjectCRC = 1130200645,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_aqualish_s02_base_female, "object/creature/npc/base/shared_aqualish_s02_base_female.iff")

object_creature_npc_base_shared_aqualish_s02_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_aqualish_s02_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/aqualish_m_02.sat",
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

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:aqualish_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 1,
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

	clientObjectCRC = 1420546336,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_aqualish_s02_base_male, "object/creature/npc/base/shared_aqualish_s02_base_male.iff")

object_creature_npc_base_shared_aqualish_s03_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_aqualish_s03_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/aqualish_f_03.sat",
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
	lookAtText = "@npc_lookat:aqualish_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:aqualish_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 1,
	rangedIntCustomizationVariables = {},

	scale = {0.85, 0.9},
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

	clientObjectCRC = 1418612504,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_aqualish_s03_base_female, "object/creature/npc/base/shared_aqualish_s03_base_female.iff")

object_creature_npc_base_shared_aqualish_s03_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_aqualish_s03_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/aqualish_m_03.sat",
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

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:aqualish_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 1,
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

	clientObjectCRC = 2309238866,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_aqualish_s03_base_male, "object/creature/npc/base/shared_aqualish_s03_base_male.iff")

object_creature_npc_base_shared_base_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_base_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1026,
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

	gameObjectType = 1026,
	gender = 2,

	locationReservationRadius = 0,
	lookAtText = "@droid_lookat:base_droid",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:base_droid",
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

	clientObjectCRC = 3496555527,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_base_droid, "object/creature/npc/base/shared_base_droid.iff")

object_creature_npc_base_shared_base_npc = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_base_npc.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "",
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
	gender = 2,

	locationReservationRadius = 0,
	lookAtText = "@npc_lookat:base_npc",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:base_npc",
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

	clientObjectCRC = 636692298,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_base_npc, "object/creature/npc/base/shared_base_npc.iff")

object_creature_npc_base_shared_base_npc_theme_park = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_base_npc_theme_park.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "",
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
	gender = 2,

	locationReservationRadius = 0,
	lookAtText = "@theme_park_lookat:base_npc_theme_park",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@theme_park_name:base_npc_theme_park",
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

	clientObjectCRC = 654644587,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_base_npc_theme_park, "object/creature/npc/base/shared_base_npc_theme_park.iff")

object_creature_npc_base_shared_bith_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_bith_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/bith_f.sat",
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
	lookAtText = "@npc_lookat:bith_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
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

	clientObjectCRC = 2412520178,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_bith_base_female, "object/creature/npc/base/shared_bith_base_female.iff")

object_creature_npc_base_shared_bith_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_bith_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 1042888288,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_bith_base_male, "object/creature/npc/base/shared_bith_base_male.iff")

object_creature_npc_base_shared_bothan_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_bothan_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 3759013611,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_bothan_base_female, "object/creature/npc/base/shared_bothan_base_female.iff")

object_creature_npc_base_shared_bothan_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_bothan_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 1590149475,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_bothan_base_male, "object/creature/npc/base/shared_bothan_base_male.iff")

object_creature_npc_base_shared_chadra_fan_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_chadra_fan_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/chadra_fan_f.sat",
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
	lookAtText = "@npc_lookat:chadra_fan_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:chadra_fan_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.49, 0.51},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 14,
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

	clientObjectCRC = 896393245,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_chadra_fan_base_female, "object/creature/npc/base/shared_chadra_fan_base_female.iff")

object_creature_npc_base_shared_chadra_fan_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_chadra_fan_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/chadra_fan_m.sat",
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
	lookAtText = "@npc_lookat:chadra_fan_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:chadra_fan_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.5, 0.55},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 14,
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

	clientObjectCRC = 313334022,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_chadra_fan_base_male, "object/creature/npc/base/shared_chadra_fan_base_male.iff")

object_creature_npc_base_shared_dantari_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_dantari_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/dantari_fm.sat",
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
	lookAtText = "@npc_lookat:dantari_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:dantari_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.85, 1},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 16,
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

	clientObjectCRC = 3185808736,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_dantari_base_male, "object/creature/npc/base/shared_dantari_base_male.iff")

object_creature_npc_base_shared_devaronian_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_devaronian_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 4086632991,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_devaronian_base_male, "object/creature/npc/base/shared_devaronian_base_male.iff")

object_creature_npc_base_shared_drall_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_drall_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/drall_f.sat",
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
	lookAtText = "@npc_lookat:drall_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:drall_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 0.5,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 18,
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

	clientObjectCRC = 1636192846,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_drall_base_female, "object/creature/npc/base/shared_drall_base_female.iff")

object_creature_npc_base_shared_drall_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_drall_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/drall_m.sat",
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
	lookAtText = "@npc_lookat:drall_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:drall_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 0.5,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 18,
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

	clientObjectCRC = 999880424,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_drall_base_male, "object/creature/npc/base/shared_drall_base_male.iff")

object_creature_npc_base_shared_dulok_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_dulok_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/dulok_f.sat",
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
	lookAtText = "@npc_lookat:dulok_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:dulok_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 2,
	rangedIntCustomizationVariables = {},

	scale = {0.72, 0.74},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 22,
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

	clientObjectCRC = 2138236706,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_dulok_base_female, "object/creature/npc/base/shared_dulok_base_female.iff")

object_creature_npc_base_shared_dulok_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_dulok_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/dulok_m.sat",
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
	lookAtText = "@npc_lookat:dulok_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:dulok_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 2,
	rangedIntCustomizationVariables = {},

	scale = {0.74, 0.78},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 22,
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

	clientObjectCRC = 748671429,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_dulok_base_male, "object/creature/npc/base/shared_dulok_base_male.iff")

object_creature_npc_base_shared_ewok_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_ewok_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "ewok.map",
	appearanceFilename = "appearance/ewok_f.sat",
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
	lookAtText = "@npc_lookat:ewok_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:ewok_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 1,
	rangedIntCustomizationVariables = {},

	scale = {0.72, 0.74},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 22,
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

	clientObjectCRC = 1504641037,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_ewok_base_female, "object/creature/npc/base/shared_ewok_base_female.iff")

object_creature_npc_base_shared_ewok_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_ewok_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "ewok.map",
	appearanceFilename = "appearance/ewok_m.sat",
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
	lookAtText = "@npc_lookat:ewok_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:ewok_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 1,
	rangedIntCustomizationVariables = {},

	scale = {0.72, 0.74},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 22,
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

	clientObjectCRC = 2588984693,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_ewok_base_male, "object/creature/npc/base/shared_ewok_base_male.iff")

object_creature_npc_base_shared_gamorrean_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_gamorrean_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/gamorrean_m.sat",
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
	lookAtText = "@npc_lookat:gamorrean_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:gamorrean_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 0.85,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 25,
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

	clientObjectCRC = 3906894721,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_gamorrean_base_male, "object/creature/npc/base/shared_gamorrean_base_male.iff")

object_creature_npc_base_shared_geonosian_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_geonosian_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/geonosian_m.sat",
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
	lookAtText = "@npc_lookat:geonosian_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:geonosian_base_male",
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
	species = 228,
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

	clientObjectCRC = 595885541,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_geonosian_base_male, "object/creature/npc/base/shared_geonosian_base_male.iff")

object_creature_npc_base_shared_gorax_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_gorax_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/gorax_m.sat",
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
	lookAtText = "@npc_lookat:gorax_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:gorax_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 10,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 26,
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

	clientObjectCRC = 2975619975,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_gorax_base_male, "object/creature/npc/base/shared_gorax_base_male.iff")

object_creature_npc_base_shared_gran_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_gran_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:gran_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.55, 0.9},
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

	clientObjectCRC = 3900679321,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_gran_base_male, "object/creature/npc/base/shared_gran_base_male.iff")

object_creature_npc_base_shared_gungan_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_gungan_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/gungan_m.sat",
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
	gender = 2,

	locationReservationRadius = 0,
	lookAtText = "@npc_lookat:gungan_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:gungan_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 2,
	rangedIntCustomizationVariables = {},

	scale = {0.85, 1},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 29,
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

	clientObjectCRC = 2826781885,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_gungan_base_male, "object/creature/npc/base/shared_gungan_base_male.iff")

object_creature_npc_base_shared_human_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_human_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:human_base_female",
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

	clientObjectCRC = 53721594,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_human_base_female, "object/creature/npc/base/shared_human_base_female.iff")

object_creature_npc_base_shared_human_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_human_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 2134943660,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_human_base_male, "object/creature/npc/base/shared_human_base_male.iff")

object_creature_npc_base_shared_hutt_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_hutt_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hutt_f.sat",
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
	lookAtText = "@npc_lookat:hutt_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:hutt_base_female",
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
	species = 31,
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

	clientObjectCRC = 36831134,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_hutt_base_female, "object/creature/npc/base/shared_hutt_base_female.iff")

object_creature_npc_base_shared_hutt_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_hutt_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hutt_m.sat",
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
	lookAtText = "@npc_lookat:hutt_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:hutt_base_male",
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
	species = 31,
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

	clientObjectCRC = 3532419442,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_hutt_base_male, "object/creature/npc/base/shared_hutt_base_male.iff")

object_creature_npc_base_shared_ishi_tib_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_ishi_tib_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 3055229554,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_ishi_tib_base_male, "object/creature/npc/base/shared_ishi_tib_base_male.iff")

object_creature_npc_base_shared_ithorian_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_ithorian_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/ithorian_m.sat",
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

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:ithorian_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.9, 1.65},
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

	clientObjectCRC = 1397449143,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_ithorian_base_male, "object/creature/npc/base/shared_ithorian_base_male.iff")

object_creature_npc_base_shared_jawa_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_jawa_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/jawa_m.sat",
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
	lookAtText = "@npc_lookat:jawa_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:jawa_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.95, 1.05},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 34,
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

	clientObjectCRC = 3349422050,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_jawa_base_male, "object/creature/npc/base/shared_jawa_base_male.iff")

object_creature_npc_base_shared_jinda_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_jinda_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/jinda_f.sat",
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
	gender = 2,

	locationReservationRadius = 0,
	lookAtText = "@npc_lookat:jinda_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:jinda_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 3,
	rangedIntCustomizationVariables = {},

	scale = {0.72, 0.74},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 22,
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

	clientObjectCRC = 4291004780,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_jinda_base_female, "object/creature/npc/base/shared_jinda_base_female.iff")

object_creature_npc_base_shared_jinda_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_jinda_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/jinda_m.sat",
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
	gender = 2,

	locationReservationRadius = 0,
	lookAtText = "@npc_lookat:jinda_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:jinda_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 3,
	rangedIntCustomizationVariables = {},

	scale = {0.72, 0.74},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 22,
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

	clientObjectCRC = 242045215,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_jinda_base_male, "object/creature/npc/base/shared_jinda_base_male.iff")

object_creature_npc_base_shared_klatooinian_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_klatooinian_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/klatoonian_m.sat",
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
	lookAtText = "@npc_lookat:klatooinian_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:klatooinian_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = 0.915,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 37,
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

	clientObjectCRC = 3370318767,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_klatooinian_base_male, "object/creature/npc/base/shared_klatooinian_base_male.iff")

object_creature_npc_base_shared_marauder_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_marauder_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/marauder_f.sat",
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
	lookAtText = "@npc_lookat:marauder_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:marauder_base_female",
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
	species = 40,
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

	clientObjectCRC = 2355090288,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_marauder_base_female, "object/creature/npc/base/shared_marauder_base_female.iff")

object_creature_npc_base_shared_marauder_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_marauder_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/marauder_m.sat",
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
	lookAtText = "@npc_lookat:marauder_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:marauder_base_male",
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
	species = 40,
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

	clientObjectCRC = 1688940240,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_marauder_base_male, "object/creature/npc/base/shared_marauder_base_male.iff")

object_creature_npc_base_shared_moncal_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_moncal_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 1371353669,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_moncal_base_female, "object/creature/npc/base/shared_moncal_base_female.iff")

object_creature_npc_base_shared_moncal_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_moncal_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 1617753563,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_moncal_base_male, "object/creature/npc/base/shared_moncal_base_male.iff")

object_creature_npc_base_shared_nikto_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_nikto_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 2839443196,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_nikto_base_male, "object/creature/npc/base/shared_nikto_base_male.iff")

object_creature_npc_base_shared_quarren_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_quarren_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:quarren_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.65, 0.9},
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

	clientObjectCRC = 2606234616,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_quarren_base_male, "object/creature/npc/base/shared_quarren_base_male.iff")

object_creature_npc_base_shared_rodian_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_rodian_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 2803462038,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_rodian_base_female, "object/creature/npc/base/shared_rodian_base_female.iff")

object_creature_npc_base_shared_rodian_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_rodian_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 873111919,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_rodian_base_male, "object/creature/npc/base/shared_rodian_base_male.iff")

object_creature_npc_base_shared_selonian_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_selonian_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/selonian_f.sat",
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
	lookAtText = "@npc_lookat:selonian_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:selonian_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.9, 1.1},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 47,
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

	clientObjectCRC = 4114788784,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_selonian_base_female, "object/creature/npc/base/shared_selonian_base_female.iff")

object_creature_npc_base_shared_selonian_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_selonian_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/selonian_m.sat",
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
	lookAtText = "@npc_lookat:selonian_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:selonian_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.9, 1.1},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 47,
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

	clientObjectCRC = 1841868410,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_selonian_base_male, "object/creature/npc/base/shared_selonian_base_male.iff")

object_creature_npc_base_shared_sullustan_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_sullustan_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/sullustan_m.sat",
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
	gender = 2,

	locationReservationRadius = 0,
	lookAtText = "@npc_lookat:sullustan_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:sullustan_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.5, 0.9},
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

	clientObjectCRC = 381383099,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_sullustan_base_male, "object/creature/npc/base/shared_sullustan_base_male.iff")

object_creature_npc_base_shared_trandoshan_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_trandoshan_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 2585187332,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_trandoshan_base_female, "object/creature/npc/base/shared_trandoshan_base_female.iff")

object_creature_npc_base_shared_trandoshan_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_trandoshan_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 193024850,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_trandoshan_base_male, "object/creature/npc/base/shared_trandoshan_base_male.iff")

object_creature_npc_base_shared_tusken_raider_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_tusken_raider_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/tusken_raider_m.sat",
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
	lookAtText = "@npc_lookat:tusken_raider_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 6,
	noBuildRadius = 0,

	objectName = "@npc_name:tusken_raider_base_male",
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
	species = 54,
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

	clientObjectCRC = 344809642,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_tusken_raider_base_male, "object/creature/npc/base/shared_tusken_raider_base_male.iff")

object_creature_npc_base_shared_twilek_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_twilek_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 4167458949,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_twilek_base_female, "object/creature/npc/base/shared_twilek_base_female.iff")

object_creature_npc_base_shared_twilek_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_twilek_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 3121839578,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_twilek_base_male, "object/creature/npc/base/shared_twilek_base_male.iff")

object_creature_npc_base_shared_weequay_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_weequay_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 3478426739,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_weequay_base_male, "object/creature/npc/base/shared_weequay_base_male.iff")

object_creature_npc_base_shared_whiphid_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_whiphid_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/whiphid_f.sat",
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
	lookAtText = "@npc_lookat:whiphid_base_female",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:whiphid_base_female",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.5, 1.3},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 56,
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

	clientObjectCRC = 858760919,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_whiphid_base_female, "object/creature/npc/base/shared_whiphid_base_female.iff")

object_creature_npc_base_shared_whiphid_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_whiphid_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/whiphid_m.sat",
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
	lookAtText = "@npc_lookat:whiphid_base_male",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 5,
	noBuildRadius = 0,

	objectName = "@npc_name:whiphid_base_male",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 0,
	rangedIntCustomizationVariables = {},

	scale = {0.5, 1.3},
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 56,
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

	clientObjectCRC = 929953104,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_whiphid_base_male, "object/creature/npc/base/shared_whiphid_base_male.iff")

object_creature_npc_base_shared_wookiee_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_wookiee_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 3361749167,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_wookiee_base_female, "object/creature/npc/base/shared_wookiee_base_female.iff")

object_creature_npc_base_shared_wookiee_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_wookiee_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 627149744,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_wookiee_base_male, "object/creature/npc/base/shared_wookiee_base_male.iff")

object_creature_npc_base_shared_zabrak_base_female = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_zabrak_base_female.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 2580396153,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_zabrak_base_female, "object/creature/npc/base/shared_zabrak_base_female.iff")

object_creature_npc_base_shared_zabrak_base_male = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/base/shared_zabrak_base_male.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
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

	niche = 5,
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

	clientObjectCRC = 2904879514,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_base_shared_zabrak_base_male, "object/creature/npc/base/shared_zabrak_base_male.iff")
