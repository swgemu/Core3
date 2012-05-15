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


object_tangible_wearables_ring_shared_aakuan_ring = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/ring/shared_aakuan_ring.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ring_s01.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/ring_either.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:aakuan_ring",

	gameObjectType = 2097153,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:aakuan_ring",

	noBuildRadius = 0,

	objectName = "@wearables_name:aakuan_ring",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 923373873,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ring_either.iff", "object/tangible/wearables/ring/shared_ring_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_ring_shared_aakuan_ring, "object/tangible/wearables/ring/shared_aakuan_ring.iff")

object_tangible_wearables_ring_shared_ring_base = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/ring/shared_ring_base.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/ring_either.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:ring_s01",

	gameObjectType = 2097153,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:ring_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4136025825,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ring_either.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_ring_shared_ring_base, "object/tangible/wearables/ring/shared_ring_base.iff")

object_tangible_wearables_ring_shared_ring_mark_hero = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/ring/shared_ring_mark_hero.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ring_quest_hero.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/ring_either.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:ring_mark_hero",

	gameObjectType = 2097153,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:ring_mark_hero",

	noBuildRadius = 0,

	objectName = "@wearables_name:ring_mark_hero",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3368096094,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ring_either.iff", "object/tangible/wearables/ring/shared_ring_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_ring_shared_ring_mark_hero, "object/tangible/wearables/ring/shared_ring_mark_hero.iff")

object_tangible_wearables_ring_shared_ring_nightsister = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/ring/shared_ring_nightsister.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ring_s03.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/ring_either.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:ring_nightsister",

	gameObjectType = 2097153,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:ring_nightsister",

	noBuildRadius = 0,

	objectName = "@wearables_name:ring_nightsister",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 186168033,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ring_either.iff", "object/tangible/wearables/ring/shared_ring_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_ring_shared_ring_nightsister, "object/tangible/wearables/ring/shared_ring_nightsister.iff")

object_tangible_wearables_ring_shared_ring_s01 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/ring/shared_ring_s01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ring_s01.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/ring_either.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:ring_s01",

	gameObjectType = 2097153,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:ring_s01",

	noBuildRadius = 0,

	objectName = "@wearables_name:ring_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1300460406,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ring_either.iff", "object/tangible/wearables/ring/shared_ring_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_ring_shared_ring_s01, "object/tangible/wearables/ring/shared_ring_s01.iff")

object_tangible_wearables_ring_shared_ring_s02 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/ring/shared_ring_s02.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ring_s02.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/ring_either.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:ring_s02",

	gameObjectType = 2097153,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:ring_s02",

	noBuildRadius = 0,

	objectName = "@wearables_name:ring_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2526338017,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ring_either.iff", "object/tangible/wearables/ring/shared_ring_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_ring_shared_ring_s02, "object/tangible/wearables/ring/shared_ring_s02.iff")

object_tangible_wearables_ring_shared_ring_s03 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/ring/shared_ring_s03.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ring_s03.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/ring_either.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:ring_s03",

	gameObjectType = 2097153,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:ring_s03",

	noBuildRadius = 0,

	objectName = "@wearables_name:ring_s03",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3751394412,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ring_either.iff", "object/tangible/wearables/ring/shared_ring_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_ring_shared_ring_s03, "object/tangible/wearables/ring/shared_ring_s03.iff")

object_tangible_wearables_ring_shared_ring_s03_quest = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/ring/shared_ring_s03_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ring_s03.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/ring_either.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:ring_s03_quest",

	gameObjectType = 2097153,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:ring_s03",

	noBuildRadius = 0,

	objectName = "@wearables_name:ring_s03_quest",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 266162342,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ring_either.iff", "object/tangible/wearables/ring/shared_ring_base.iff", "object/tangible/wearables/ring/shared_ring_s03.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_ring_shared_ring_s03_quest, "object/tangible/wearables/ring/shared_ring_s03_quest.iff")

object_tangible_wearables_ring_shared_ring_s04 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/ring/shared_ring_s04.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ring_s04.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/ring_either.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:ring_s04",

	gameObjectType = 2097153,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:ring_s04",

	noBuildRadius = 0,

	objectName = "@wearables_name:ring_s04",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 612013944,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ring_either.iff", "object/tangible/wearables/ring/shared_ring_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_ring_shared_ring_s04, "object/tangible/wearables/ring/shared_ring_s04.iff")
