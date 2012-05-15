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


object_tangible_bug_jar_shared_craftable_bug_habitat = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/bug_jar/shared_craftable_bug_habitat.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/edb_con_barrel_lg_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8211,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_item_ingredients_d:bug_habitat",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@craft_item_ingredients_d:bug_habitat",

	noBuildRadius = 0,

	objectName = "@craft_item_ingredients_n:bug_habitat",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3865262015,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_bug_jar_shared_craftable_bug_habitat, "object/tangible/bug_jar/shared_craftable_bug_habitat.iff")

object_tangible_bug_jar_shared_sample_bats = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/bug_jar/shared_sample_bats.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/edb_con_tato_jar_bugs_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8222,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_item_ingredients_d:sample_bugs",

	gameObjectType = 8222,

	locationReservationRadius = 0,
	lookAtText = "@craft_item_ingredients_d:sample_bugs",

	noBuildRadius = 0,

	objectName = "@craft_item_ingredients_n:sample_bats",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 649283460,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/bug_jar/shared_sample_bugs.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_bug_jar_shared_sample_bats, "object/tangible/bug_jar/shared_sample_bats.iff")

object_tangible_bug_jar_shared_sample_bees = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/bug_jar/shared_sample_bees.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/edb_con_tato_jar_berries_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8222,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_item_ingredients_d:sample_bugs",

	gameObjectType = 8222,

	locationReservationRadius = 0,
	lookAtText = "@craft_item_ingredients_d:sample_bugs",

	noBuildRadius = 0,

	objectName = "@craft_item_ingredients_n:sample_bees",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2990947640,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/bug_jar/shared_sample_bugs.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_bug_jar_shared_sample_bees, "object/tangible/bug_jar/shared_sample_bees.iff")

object_tangible_bug_jar_shared_sample_bugs = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/bug_jar/shared_sample_bugs.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/edb_con_tato_jar_bugs_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8222,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_item_ingredients_d:sample_bugs",

	gameObjectType = 8222,

	locationReservationRadius = 0,
	lookAtText = "@craft_item_ingredients_d:sample_bugs",

	noBuildRadius = 0,

	objectName = "@craft_item_ingredients_n:sample_bugs",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1650774020,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_bug_jar_shared_sample_bugs, "object/tangible/bug_jar/shared_sample_bugs.iff")

object_tangible_bug_jar_shared_sample_butterflies = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/bug_jar/shared_sample_butterflies.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/edb_con_tato_jar_bugs_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8222,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_item_ingredients_d:sample_bugs",

	gameObjectType = 8222,

	locationReservationRadius = 0,
	lookAtText = "@craft_item_ingredients_d:sample_bugs",

	noBuildRadius = 0,

	objectName = "@craft_item_ingredients_n:sample_butterflies",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3511677766,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/bug_jar/shared_sample_bugs.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_bug_jar_shared_sample_butterflies, "object/tangible/bug_jar/shared_sample_butterflies.iff")

object_tangible_bug_jar_shared_sample_flies = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/bug_jar/shared_sample_flies.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/edb_con_tato_jar_funk_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8222,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_item_ingredients_d:sample_bugs",

	gameObjectType = 8222,

	locationReservationRadius = 0,
	lookAtText = "@craft_item_ingredients_d:sample_bugs",

	noBuildRadius = 0,

	objectName = "@craft_item_ingredients_n:sample_flies",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1920617264,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/bug_jar/shared_sample_bugs.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_bug_jar_shared_sample_flies, "object/tangible/bug_jar/shared_sample_flies.iff")

object_tangible_bug_jar_shared_sample_glowzees = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/bug_jar/shared_sample_glowzees.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/edb_con_tato_jar_guts_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8222,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_item_ingredients_d:sample_bugs",

	gameObjectType = 8222,

	locationReservationRadius = 0,
	lookAtText = "@craft_item_ingredients_d:sample_bugs",

	noBuildRadius = 0,

	objectName = "@craft_item_ingredients_n:sample_glowzees",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 543867771,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/bug_jar/shared_sample_bugs.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_bug_jar_shared_sample_glowzees, "object/tangible/bug_jar/shared_sample_glowzees.iff")

object_tangible_bug_jar_shared_sample_moths = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/bug_jar/shared_sample_moths.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/edb_con_tato_jar_bugs_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8222,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_item_ingredients_d:sample_bugs",

	gameObjectType = 8222,

	locationReservationRadius = 0,
	lookAtText = "@craft_item_ingredients_d:sample_bugs",

	noBuildRadius = 0,

	objectName = "@craft_item_ingredients_n:sample_moths",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1330824406,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/bug_jar/shared_sample_bugs.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_bug_jar_shared_sample_moths, "object/tangible/bug_jar/shared_sample_moths.iff")
