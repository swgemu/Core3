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


object_creature_npc_droid_crafted_shared_2_1b_surgical_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_2_1b_surgical_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/droid_21b.sat",
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
	lookAtText = "@droid_lookat:b_surgical_droid_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:b_surgical_droid_crafted",
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
	species = 220,
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

	clientObjectCRC = 2915843418,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_2_1b_surgical_droid_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_2_1b_surgical_droid, "object/creature/npc/droid/crafted/shared_2_1b_surgical_droid.iff")

object_creature_npc_droid_crafted_shared_2_1b_surgical_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_2_1b_surgical_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/droid_21b.sat",
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
	lookAtText = "@droid_lookat:b_surgical_droid_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:b_surgical_droid_crafted_advanced",
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
	species = 220,
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

	clientObjectCRC = 1752432055,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_2_1b_surgical_droid_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_2_1b_surgical_droid_advanced, "object/creature/npc/droid/crafted/shared_2_1b_surgical_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_3po_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_3po_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/protocol_droid_gold.sat",
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
	lookAtText = "@droid_lookat:po_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:po_crafted",
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
	species = 217,
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

	clientObjectCRC = 2764227037,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_3po_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_3po_droid, "object/creature/npc/droid/crafted/shared_3po_droid.iff")

object_creature_npc_droid_crafted_shared_3po_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_3po_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/protocol_droid_gold.sat",
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
	lookAtText = "@droid_lookat:po_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:po_crafted_advanced",
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
	species = 217,
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

	clientObjectCRC = 604017168,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_3po_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_3po_droid_advanced, "object/creature/npc/droid/crafted/shared_3po_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_bomarr_monk_spider_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_bomarr_monk_spider_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/spider_droid.sat",
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
	lookAtText = "@droid_lookat:bomarr_monk_spider_droid",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:bomarr_monk_spider_droid_crafted",
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
	waterModPercent = 0.5,

	clientObjectCRC = 3172589023,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_bomarr_monk_spider_droid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_bomarr_monk_spider_droid, "object/creature/npc/droid/crafted/shared_bomarr_monk_spider_droid.iff")

object_creature_npc_droid_crafted_shared_bomarr_monk_spider_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_bomarr_monk_spider_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/spider_droid.sat",
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
	lookAtText = "@droid_lookat:bomarr_monk_spider_droid",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:bomarr_monk_spider_droid_crafted_advanced",
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
	waterModPercent = 0.5,

	clientObjectCRC = 2295784813,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_bomarr_monk_spider_droid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_bomarr_monk_spider_droid_advanced, "object/creature/npc/droid/crafted/shared_bomarr_monk_spider_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_cll_8_binary_load_lifter = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_cll_8_binary_load_lifter.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/cll8.sat",
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
	lookAtText = "@droid_lookat:cll_8_binary_load_lifter_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:cll_8_binary_load_lifter_crafted",
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
	species = 213,
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

	clientObjectCRC = 1144214850,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_cll_8_binary_load_lifter_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_cll_8_binary_load_lifter, "object/creature/npc/droid/crafted/shared_cll_8_binary_load_lifter.iff")

object_creature_npc_droid_crafted_shared_cll_8_binary_load_lifter_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_cll_8_binary_load_lifter_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/cll8.sat",
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
	lookAtText = "@droid_lookat:cll_8_binary_load_lifter_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:cll_8_binary_load_lifter_crafted_advanced",
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
	species = 213,
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

	clientObjectCRC = 2691944817,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_cll_8_binary_load_lifter_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_cll_8_binary_load_lifter_advanced, "object/creature/npc/droid/crafted/shared_cll_8_binary_load_lifter_advanced.iff")

object_creature_npc_droid_crafted_shared_dark_trooper_phase_ii = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_dark_trooper_phase_ii.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/dark_trooper_2.sat",
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
	gender = 0,

	locationReservationRadius = 0,
	lookAtText = "@droid_lookat:dark_trooper_phase_ii_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:dark_trooper_phase_ii_crafted",
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
	species = 207,
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

	clientObjectCRC = 3813952229,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_dark_trooper_phase_ii, "object/creature/npc/droid/crafted/shared_dark_trooper_phase_ii.iff")

object_creature_npc_droid_crafted_shared_dark_trooper_phase_ii_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_dark_trooper_phase_ii_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/dark_trooper_2.sat",
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
	gender = 0,

	locationReservationRadius = 0,
	lookAtText = "@droid_lookat:dark_trooper_phase_ii_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:dark_trooper_phase_ii_crafted_advanced",
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
	species = 207,
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

	clientObjectCRC = 320581973,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_dark_trooper_phase_ii_advanced, "object/creature/npc/droid/crafted/shared_dark_trooper_phase_ii_advanced.iff")

object_creature_npc_droid_crafted_shared_droideka = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_droideka.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/droideka.sat",
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
	lookAtText = "@droid_lookat:droideka_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:droideka_crafted",
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
	species = 210,
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

	clientObjectCRC = 3178328195,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_droideka_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_droideka, "object/creature/npc/droid/crafted/shared_droideka.iff")

object_creature_npc_droid_crafted_shared_droideka_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_droideka_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/droideka.sat",
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
	lookAtText = "@droid_lookat:droideka_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:droideka_crafted_advanced",
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
	species = 210,
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

	clientObjectCRC = 2397633499,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_droideka_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_droideka_advanced, "object/creature/npc/droid/crafted/shared_droideka_advanced.iff")

object_creature_npc_droid_crafted_shared_dz_70_fugitive_tracker_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_dz_70_fugitive_tracker_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/dz70.sat",
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
	lookAtText = "@droid_lookat:dz_70_fugitive_tracker_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:dz_70_fugitive_tracker_crafted",
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
	species = 222,
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

	clientObjectCRC = 3709391789,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_dz_70_fugitive_tracker_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_dz_70_fugitive_tracker_droid, "object/creature/npc/droid/crafted/shared_dz_70_fugitive_tracker_droid.iff")

object_creature_npc_droid_crafted_shared_dz_70_fugitive_tracker_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_dz_70_fugitive_tracker_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/dz70.sat",
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
	lookAtText = "@droid_lookat:dz_70_fugitive_tracker_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:dz_70_fugitive_tracker_crafted_advanced",
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
	species = 222,
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

	clientObjectCRC = 1848917490,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_dz_70_fugitive_tracker_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_dz_70_fugitive_tracker_droid_advanced, "object/creature/npc/droid/crafted/shared_dz_70_fugitive_tracker_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_eg_6_power_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_eg_6_power_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/eg6.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/droid/client_shared_dro_gonk.cdf",
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
	lookAtText = "@droid_lookat:eg_6_power_droid_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:eg_6_power_droid_crafted",
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
	species = 215,
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

	clientObjectCRC = 2388417509,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_eg_6_power_droid_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_eg_6_power_droid, "object/creature/npc/droid/crafted/shared_eg_6_power_droid.iff")

object_creature_npc_droid_crafted_shared_eg_6_power_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_eg_6_power_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/eg6.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/droid/client_shared_dro_gonk.cdf",
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
	lookAtText = "@droid_lookat:eg_6_power_droid_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:eg_6_power_droid_crafted_advanced",
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
	species = 215,
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

	clientObjectCRC = 2251263338,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_eg_6_power_droid_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_eg_6_power_droid_advanced, "object/creature/npc/droid/crafted/shared_eg_6_power_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_ig_assassin_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_ig_assassin_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/ig88.sat",
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
	lookAtText = "@droid_lookat:ig_assassin_droid_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:ig_assassin_droid_crafted",
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
	species = 203,
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

	clientObjectCRC = 103856343,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_ig_assassin_droid_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_ig_assassin_droid, "object/creature/npc/droid/crafted/shared_ig_assassin_droid.iff")

object_creature_npc_droid_crafted_shared_ig_assassin_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_ig_assassin_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/ig88.sat",
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
	lookAtText = "@droid_lookat:ig_assassin_droid_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:ig_assassin_droid_crafted",
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
	species = 203,
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

	clientObjectCRC = 3720942075,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_ig_assassin_droid_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_ig_assassin_droid_advanced, "object/creature/npc/droid/crafted/shared_ig_assassin_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_imperial_probot = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_imperial_probot.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/probe_droid.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1027,
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

	gameObjectType = 1027,
	gender = 2,

	locationReservationRadius = 0,
	lookAtText = "@droid_lookat:imperial_probot_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:arakyd_probot_crafted",
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
	species = 216,
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

	clientObjectCRC = 2904803500,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_imperial_probot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_imperial_probot, "object/creature/npc/droid/crafted/shared_imperial_probot.iff")

object_creature_npc_droid_crafted_shared_imperial_probot_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_imperial_probot_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/probe_droid.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1027,
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

	gameObjectType = 1027,
	gender = 2,

	locationReservationRadius = 0,
	lookAtText = "@droid_lookat:imperial_probot_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:arakyd_probot_crafted_advanced",
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
	species = 216,
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

	clientObjectCRC = 2998077962,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_imperial_probot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_imperial_probot_advanced, "object/creature/npc/droid/crafted/shared_imperial_probot_advanced.iff")

object_creature_npc_droid_crafted_shared_it_o_interrogator = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_it_o_interrogator.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/ito.sat",
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
	lookAtText = "@droid_lookat:it_o_interrogator_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:it_o_interrogator_crafted",
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
	waterModPercent = 0.5,

	clientObjectCRC = 3950548383,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_it_o_interrogator_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_it_o_interrogator, "object/creature/npc/droid/crafted/shared_it_o_interrogator.iff")

object_creature_npc_droid_crafted_shared_it_o_interrogator_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_it_o_interrogator_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/ito.sat",
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
	lookAtText = "@droid_lookat:it_o_interrogator_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:it_o_interrogator_crafted_advanced",
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
	waterModPercent = 0.5,

	clientObjectCRC = 1493429482,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_it_o_interrogator_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_it_o_interrogator_advanced, "object/creature/npc/droid/crafted/shared_it_o_interrogator_advanced.iff")

object_creature_npc_droid_crafted_shared_jedi_training_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_jedi_training_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/jedi_training_droid.sat",
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
	lookAtText = "@droid_lookat:jedi_training_droid_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:jedi_training_droid_crafted",
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
	species = 212,
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

	clientObjectCRC = 150852356,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_jedi_training_droid_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_jedi_training_droid, "object/creature/npc/droid/crafted/shared_jedi_training_droid.iff")

object_creature_npc_droid_crafted_shared_jedi_training_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_jedi_training_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/jedi_training_droid.sat",
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
	lookAtText = "@droid_lookat:jedi_training_droid_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:jedi_training_droid_crafted_advanced",
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
	species = 212,
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

	clientObjectCRC = 1150973475,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_jedi_training_droid_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_jedi_training_droid_advanced, "object/creature/npc/droid/crafted/shared_jedi_training_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_le_repair_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_le_repair_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/le_repair.sat",
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
	lookAtText = "@droid_lookat:le_repair_droid",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:le_repair_droid_crafted",
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
	species = 218,
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

	clientObjectCRC = 2448691902,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_le_repair_droid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_le_repair_droid, "object/creature/npc/droid/crafted/shared_le_repair_droid.iff")

object_creature_npc_droid_crafted_shared_le_repair_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_le_repair_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/le_repair.sat",
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
	lookAtText = "@droid_lookat:le_repair_droid",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:le_repair_droid_crafted_advanced",
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
	species = 218,
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

	clientObjectCRC = 256863265,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_le_repair_droid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_le_repair_droid_advanced, "object/creature/npc/droid/crafted/shared_le_repair_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_lin_demolitionmech = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_lin_demolitionmech.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/lin_demolition.sat",
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
	lookAtText = "@droid_lookat:lin_demolitionmech_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:lin_demolitionmech_crafted",
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
	waterModPercent = 0.5,

	clientObjectCRC = 4276460545,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_lin_demolitionmech, "object/creature/npc/droid/crafted/shared_lin_demolitionmech.iff")

object_creature_npc_droid_crafted_shared_lin_demolitionmech_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_lin_demolitionmech_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/lin_demolition.sat",
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
	lookAtText = "@droid_lookat:lin_demolitionmech_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:lin_demolitionmech_crafted_advanced",
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
	waterModPercent = 0.5,

	clientObjectCRC = 3957385280,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_lin_demolitionmech_advanced, "object/creature/npc/droid/crafted/shared_lin_demolitionmech_advanced.iff")

object_creature_npc_droid_crafted_shared_mse_6_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_mse_6_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/mouse_droid.sat",
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
	lookAtText = "@droid_lookat:mse_6_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:mse_6_crafted",
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
	waterModPercent = 0.5,

	clientObjectCRC = 2169488229,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_mse_6_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_mse_6_droid, "object/creature/npc/droid/crafted/shared_mse_6_droid.iff")

object_creature_npc_droid_crafted_shared_mse_6_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_mse_6_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/mouse_droid.sat",
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
	lookAtText = "@droid_lookat:mse_6_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:mse_6_crafted_advanced",
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
	waterModPercent = 0.5,

	clientObjectCRC = 2206627850,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_mse_6_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_mse_6_droid_advanced, "object/creature/npc/droid/crafted/shared_mse_6_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_probe_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_probe_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/maul_probe_droid.sat",
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
	lookAtText = "@droid_lookat:probe_droid",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:probe_droid_crafted",
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
	waterModPercent = 0.5,

	clientObjectCRC = 1995149002,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_maul_probe_droid_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_probe_droid, "object/creature/npc/droid/crafted/shared_probe_droid.iff")

object_creature_npc_droid_crafted_shared_probe_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_probe_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/maul_probe_droid.sat",
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
	lookAtText = "@droid_lookat:probe_droid",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:probe_droid_crafted_advanced",
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
	waterModPercent = 0.5,

	clientObjectCRC = 1470713199,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_maul_probe_droid_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_probe_droid_advanced, "object/creature/npc/droid/crafted/shared_probe_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_r2_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_r2_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/astromech_r2.sat",
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
	lookAtText = "@droid_lookat:r2_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:r2_crafted",
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
	species = 204,
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

	clientObjectCRC = 1532167005,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_r2_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_r2_droid, "object/creature/npc/droid/crafted/shared_r2_droid.iff")

object_creature_npc_droid_crafted_shared_r2_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_r2_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/astromech_r2.sat",
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
	lookAtText = "@droid_lookat:r2_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:r2_crafted_advanced",
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
	species = 204,
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

	clientObjectCRC = 4218729421,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_r2_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_r2_droid_advanced, "object/creature/npc/droid/crafted/shared_r2_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_r3_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_r3_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/astromech_r3.sat",
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
	lookAtText = "@droid_lookat:r3_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:r3_crafted",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 1,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 204,
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

	clientObjectCRC = 2734654643,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_r3_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_r3_droid, "object/creature/npc/droid/crafted/shared_r3_droid.iff")

object_creature_npc_droid_crafted_shared_r3_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_r3_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/astromech_r3.sat",
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
	lookAtText = "@droid_lookat:r3_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:r3_crafted_advanced",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 1,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 204,
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

	clientObjectCRC = 3480632347,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_r3_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_r3_droid_advanced, "object/creature/npc/droid/crafted/shared_r3_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_r4_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_r4_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/astromech_r4.sat",
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
	lookAtText = "@droid_lookat:r4_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:r4_crafted",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 2,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 204,
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

	clientObjectCRC = 1194993751,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_r4_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_r4_droid, "object/creature/npc/droid/crafted/shared_r4_droid.iff")

object_creature_npc_droid_crafted_shared_r4_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_r4_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/astromech_r4.sat",
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
	lookAtText = "@droid_lookat:r4_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:r4_crafted_advanced",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 2,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 204,
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

	clientObjectCRC = 1132172089,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_r4_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_r4_droid_advanced, "object/creature/npc/droid/crafted/shared_r4_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_r5_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_r5_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/astromech_r5.sat",
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
	lookAtText = "@droid_lookat:r5_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:r5_crafted",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 3,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 204,
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

	clientObjectCRC = 3197546425,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_r5_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_r5_droid, "object/creature/npc/droid/crafted/shared_r5_droid.iff")

object_creature_npc_droid_crafted_shared_r5_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_r5_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/astromech_r5.sat",
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
	lookAtText = "@droid_lookat:r5_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:r5_crafted_advanced",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",
	postureAlignToTerrain = {0,0,1,0,0,1,0,1,0,0,0,0,1,1,1},

	race = 3,
	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slopeModAngle = 15,
	slopeModPercent = 0.1,
	slotDescriptorFilename = "abstract/slot/descriptor/player.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	species = 204,
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

	clientObjectCRC = 2004425967,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_r5_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_r5_droid_advanced, "object/creature/npc/droid/crafted/shared_r5_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_ra7_bug_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_ra7_bug_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/ra7.sat",
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
	lookAtText = "@droid_lookat:ra7_bug_droid_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:ra7_bug_droid_crafted",
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
	species = 206,
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

	clientObjectCRC = 1905884809,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_ra7_bug_droid_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_ra7_bug_droid, "object/creature/npc/droid/crafted/shared_ra7_bug_droid.iff")

object_creature_npc_droid_crafted_shared_ra7_bug_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_ra7_bug_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/ra7.sat",
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
	lookAtText = "@droid_lookat:ra7_bug_droid_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:ra7_bug_droid_crafted_advanced",
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
	species = 206,
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

	clientObjectCRC = 298901338,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_ra7_bug_droid_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_ra7_bug_droid_advanced, "object/creature/npc/droid/crafted/shared_ra7_bug_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_red_protocol_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_red_protocol_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/protocol_droid_red.sat",
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
	lookAtText = "@droid_lookat:po_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:po_crafted",
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
	species = 217,
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

	clientObjectCRC = 774994860,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_red_protocol_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_red_protocol_droid, "object/creature/npc/droid/crafted/shared_red_protocol_droid.iff")

object_creature_npc_droid_crafted_shared_red_protocol_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_red_protocol_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/protocol_droid_red.sat",
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
	lookAtText = "@droid_lookat:po_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:po_crafted_advanced",
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
	species = 217,
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

	clientObjectCRC = 2864675349,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_red_protocol_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_red_protocol_droid_advanced, "object/creature/npc/droid/crafted/shared_red_protocol_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_robo_bartender_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_robo_bartender_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/robo_bartender.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 7,
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

	gameObjectType = 7,
	gender = 2,

	locationReservationRadius = 0,
	lookAtText = "@droid_lookat:robo_bartender_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:robo_bartender_crafted",
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
	waterModPercent = 0.5,

	clientObjectCRC = 700179103,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_robo_bartender_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_robo_bartender_droid, "object/creature/npc/droid/crafted/shared_robo_bartender_droid.iff")

object_creature_npc_droid_crafted_shared_robo_bartender_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_robo_bartender_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/robo_bartender.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 7,
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

	gameObjectType = 7,
	gender = 2,

	locationReservationRadius = 0,
	lookAtText = "@droid_lookat:robo_bartender_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:robo_bartender_crafted_advanced",
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
	waterModPercent = 0.5,

	clientObjectCRC = 1665563112,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_robo_bartender_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_robo_bartender_droid_advanced, "object/creature/npc/droid/crafted/shared_robo_bartender_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_silver_protocol_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_silver_protocol_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/protocol_droid_silver.sat",
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
	lookAtText = "@droid_lookat:po_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:po_crafted",
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
	species = 217,
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

	clientObjectCRC = 3802774389,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_silver_protocol_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_silver_protocol_droid, "object/creature/npc/droid/crafted/shared_silver_protocol_droid.iff")

object_creature_npc_droid_crafted_shared_silver_protocol_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_silver_protocol_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/protocol_droid_silver.sat",
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
	lookAtText = "@droid_lookat:po_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:po_crafted_advanced",
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
	species = 217,
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

	clientObjectCRC = 4209769049,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_silver_protocol_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_silver_protocol_droid_advanced, "object/creature/npc/droid/crafted/shared_silver_protocol_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_tt_8l_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_tt_8l_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/tt8l.sat",
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
	lookAtText = "@droid_lookat:tt_8l_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:tt_8l_crafted",
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
	waterModPercent = 0.5,

	clientObjectCRC = 3627618627,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_tt_8l_droid, "object/creature/npc/droid/crafted/shared_tt_8l_droid.iff")

object_creature_npc_droid_crafted_shared_tt_8l_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_tt_8l_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/tt8l.sat",
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
	lookAtText = "@droid_lookat:tt_8l_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:tt_8l_crafted_advanced",
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
	waterModPercent = 0.5,

	clientObjectCRC = 3840849400,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_tt_8l_droid_advanced, "object/creature/npc/droid/crafted/shared_tt_8l_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_tt_8l_y7_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_tt_8l_y7_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/tt8l_y7.sat",
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
	lookAtText = "@droid_lookat:tt_8l_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:tt_8l_y7_crafted",
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
	waterModPercent = 0.5,

	clientObjectCRC = 3258466577,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_tt_8l_y7_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_tt_8l_y7_droid, "object/creature/npc/droid/crafted/shared_tt_8l_y7_droid.iff")

object_creature_npc_droid_crafted_shared_tt_8l_y7_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_tt_8l_y7_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/tt8l_y7.sat",
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
	lookAtText = "@droid_lookat:tt_8l_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:tt_8l_y7_crafted_advanced",
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
	waterModPercent = 0.5,

	clientObjectCRC = 3957782001,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_tt_8l_y7_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_tt_8l_y7_droid_advanced, "object/creature/npc/droid/crafted/shared_tt_8l_y7_droid_advanced.iff")

object_creature_npc_droid_crafted_shared_wed_treadwell_droid = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_wed_treadwell_droid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/wed_treadwell.sat",
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
	lookAtText = "@droid_lookat:wed_treadwell_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:wed_treadwell_crafted",
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
	waterModPercent = 0.5,

	clientObjectCRC = 1585315002,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_wed_treadwell_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_wed_treadwell_droid, "object/creature/npc/droid/crafted/shared_wed_treadwell_droid.iff")

object_creature_npc_droid_crafted_shared_wed_treadwell_droid_advanced = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/creature/npc/droid/crafted/shared_wed_treadwell_droid_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {4,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/wed_treadwell.sat",
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
	lookAtText = "@droid_lookat:wed_treadwell_base",

	movementDatatable = "datatables/movement/movement_human.iff",

	niche = 3,
	noBuildRadius = 0,

	objectName = "@droid_name:wed_treadwell_crafted_advanced",
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
	waterModPercent = 0.5,

	clientObjectCRC = 3393855591,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/creature/npc/base/shared_base_npc.iff", "object/creature/npc/base/shared_base_droid.iff", "object/creature/npc/droid/shared_wed_treadwell_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_creature_npc_droid_crafted_shared_wed_treadwell_droid_advanced, "object/creature/npc/droid/crafted/shared_wed_treadwell_droid_advanced.iff")
