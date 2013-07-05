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


object_mobile_tatooine_npc_shared_aaph_koden = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_aaph_koden.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/zab_f.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_zabrak_f.cdf",
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

	detailedDescription = "@npc_detail:zabrak_base_female",

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

	scale = {1, 1.12},
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

	clientObjectCRC = 2210665097,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_aaph_koden, "object/mobile/tatooine_npc/shared_aaph_koden.iff")

object_mobile_tatooine_npc_shared_binna_jode = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_binna_jode.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_f.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_f.cdf",
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

	detailedDescription = "@npc_detail:human_base_female",

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

	clientObjectCRC = 3420862161,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_binna_jode, "object/mobile/tatooine_npc/shared_binna_jode.iff")

object_mobile_tatooine_npc_shared_blerx_tango = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_blerx_tango.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 2463657324,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_blerx_tango, "object/mobile/tatooine_npc/shared_blerx_tango.iff")

object_mobile_tatooine_npc_shared_boshek = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_boshek.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 1226761307,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_boshek, "object/mobile/tatooine_npc/shared_boshek.iff")

object_mobile_tatooine_npc_shared_brea_tonnika = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_brea_tonnika.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_f.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_f.cdf",
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

	detailedDescription = "@npc_detail:human_base_female",

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

	clientObjectCRC = 4285124243,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_brea_tonnika, "object/mobile/tatooine_npc/shared_brea_tonnika.iff")

object_mobile_tatooine_npc_shared_capt_loftus = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_capt_loftus.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 4289563473,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_capt_loftus, "object/mobile/tatooine_npc/shared_capt_loftus.iff")

object_mobile_tatooine_npc_shared_farious_gletch = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_farious_gletch.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 1952005063,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_farious_gletch, "object/mobile/tatooine_npc/shared_farious_gletch.iff")

object_mobile_tatooine_npc_shared_figrin_dan = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_figrin_dan.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/bith_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 861642395,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_figrin_dan, "object/mobile/tatooine_npc/shared_figrin_dan.iff")

object_mobile_tatooine_npc_shared_fixer = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_fixer.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 119383383,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_fixer, "object/mobile/tatooine_npc/shared_fixer.iff")

object_mobile_tatooine_npc_shared_hedon_istee = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_hedon_istee.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 4094763986,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_hedon_istee, "object/mobile/tatooine_npc/shared_hedon_istee.iff")

object_mobile_tatooine_npc_shared_ikka_gesul = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_ikka_gesul.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_f.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_f.cdf",
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

	detailedDescription = "@npc_detail:human_base_female",

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

	clientObjectCRC = 1541010497,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_ikka_gesul, "object/mobile/tatooine_npc/shared_ikka_gesul.iff")

object_mobile_tatooine_npc_shared_jilljoo_jab = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_jilljoo_jab.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_f.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_f.cdf",
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

	detailedDescription = "@npc_detail:human_base_female",

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

	clientObjectCRC = 3479474175,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_jilljoo_jab, "object/mobile/tatooine_npc/shared_jilljoo_jab.iff")

object_mobile_tatooine_npc_shared_kaeline_ungasan = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_kaeline_ungasan.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 28682516,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_kaeline_ungasan, "object/mobile/tatooine_npc/shared_kaeline_ungasan.iff")

object_mobile_tatooine_npc_shared_kitster_banai = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_kitster_banai.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 1703616350,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_kitster_banai, "object/mobile/tatooine_npc/shared_kitster_banai.iff")

object_mobile_tatooine_npc_shared_kormund_thrylle = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_kormund_thrylle.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 1211559365,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_kormund_thrylle, "object/mobile/tatooine_npc/shared_kormund_thrylle.iff")

object_mobile_tatooine_npc_shared_lilas_dinhint = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_lilas_dinhint.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 253776339,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_lilas_dinhint, "object/mobile/tatooine_npc/shared_lilas_dinhint.iff")

object_mobile_tatooine_npc_shared_lt_harburik = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_lt_harburik.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 1553404717,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_lt_harburik, "object/mobile/tatooine_npc/shared_lt_harburik.iff")

object_mobile_tatooine_npc_shared_mat_rags = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_mat_rags.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 1901596031,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_mat_rags, "object/mobile/tatooine_npc/shared_mat_rags.iff")

object_mobile_tatooine_npc_shared_melios_purl = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_melios_purl.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 4049550118,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_melios_purl, "object/mobile/tatooine_npc/shared_melios_purl.iff")

object_mobile_tatooine_npc_shared_mikos_denari = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_mikos_denari.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 2971142656,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_mikos_denari, "object/mobile/tatooine_npc/shared_mikos_denari.iff")

object_mobile_tatooine_npc_shared_nitra_vendallan = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_nitra_vendallan.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_f.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_f.cdf",
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

	detailedDescription = "@npc_detail:human_base_female",

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

	clientObjectCRC = 3562269968,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_nitra_vendallan, "object/mobile/tatooine_npc/shared_nitra_vendallan.iff")

object_mobile_tatooine_npc_shared_om_aynat = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_om_aynat.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 197060903,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_om_aynat, "object/mobile/tatooine_npc/shared_om_aynat.iff")

object_mobile_tatooine_npc_shared_pfilbee_jhorn = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_pfilbee_jhorn.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 3055869175,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_pfilbee_jhorn, "object/mobile/tatooine_npc/shared_pfilbee_jhorn.iff")

object_mobile_tatooine_npc_shared_phinea_shantee = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_phinea_shantee.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 1801428554,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_phinea_shantee, "object/mobile/tatooine_npc/shared_phinea_shantee.iff")

object_mobile_tatooine_npc_shared_rakir_banai = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_rakir_banai.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 2174990588,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_rakir_banai, "object/mobile/tatooine_npc/shared_rakir_banai.iff")

object_mobile_tatooine_npc_shared_senni_tonnika = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_senni_tonnika.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_f.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_f.cdf",
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

	detailedDescription = "@npc_detail:human_base_female",

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

	clientObjectCRC = 3876719112,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_senni_tonnika, "object/mobile/tatooine_npc/shared_senni_tonnika.iff")

object_mobile_tatooine_npc_shared_tekil_barje = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_tekil_barje.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 153136187,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_tekil_barje, "object/mobile/tatooine_npc/shared_tekil_barje.iff")

object_mobile_tatooine_npc_shared_tour_aryon = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_tour_aryon.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_f.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_f.cdf",
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

	detailedDescription = "@npc_detail:human_base_female",

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

	clientObjectCRC = 651899937,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_tour_aryon, "object/mobile/tatooine_npc/shared_tour_aryon.iff")

object_mobile_tatooine_npc_shared_vardias_tyne = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_vardias_tyne.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 2121259164,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_vardias_tyne, "object/mobile/tatooine_npc/shared_vardias_tyne.iff")

object_mobile_tatooine_npc_shared_wilhalm_skrim = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_wilhalm_skrim.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 4249752702,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_wilhalm_skrim, "object/mobile/tatooine_npc/shared_wilhalm_skrim.iff")

object_mobile_tatooine_npc_shared_windom_starkiller = SharedCreatureObjectTemplate:new {
	clientTemplateFileName = "object/mobile/tatooine_npc/shared_windom_starkiller.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	acceleration = {6,2},
	animationMapFilename = "all_male.map",
	appearanceFilename = "appearance/hum_m.sat",
	arrangementDescriptorFilename = "",

	cameraHeight = 0,
	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/npc/client_shared_npc_human_m.cdf",
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

	detailedDescription = "@npc_detail:human_base_male",

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

	clientObjectCRC = 1129472596,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/creature/base/shared_base_creature.iff", "object/mobile/shared_mobile.iff", "object/mobile/skeleton/shared_humanoid.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_mobile_tatooine_npc_shared_windom_starkiller, "object/mobile/tatooine_npc/shared_windom_starkiller.iff")
