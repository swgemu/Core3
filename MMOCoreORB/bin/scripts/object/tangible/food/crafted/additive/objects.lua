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


object_tangible_food_crafted_additive_shared_additive_base = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/food/crafted/additive/shared_additive_base.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_medic_antidote_sm_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262144,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:food_additive",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:food_additive",

	noBuildRadius = 0,

	objectName = "@food_name:food_additive",
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

	clientObjectCRC = 4284585922,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/base/shared_base_crafted_food.iff", "object/tangible/food/base/shared_dish_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_food_crafted_additive_shared_additive_base, "object/tangible/food/crafted/additive/shared_additive_base.iff")

object_tangible_food_crafted_additive_shared_additive_heavy = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/food/crafted/additive/shared_additive_heavy.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_medic_bacta_tank_advanced.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262144,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:food_additive_heavy",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:food_additive_heavy",

	noBuildRadius = 0,

	objectName = "@food_name:food_additive_heavy",
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

	clientObjectCRC = 2284977295,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/base/shared_base_crafted_food.iff", "object/tangible/food/base/shared_dish_base.iff", "object/tangible/food/crafted/additive/shared_additive_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_food_crafted_additive_shared_additive_heavy, "object/tangible/food/crafted/additive/shared_additive_heavy.iff")

object_tangible_food_crafted_additive_shared_additive_light = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/food/crafted/additive/shared_additive_light.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_medic_antidote_sm_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262144,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:food_additive_light",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:food_additive_light",

	noBuildRadius = 0,

	objectName = "@food_name:food_additive_light",
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

	clientObjectCRC = 1231667281,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/base/shared_base_crafted_food.iff", "object/tangible/food/base/shared_dish_base.iff", "object/tangible/food/crafted/additive/shared_additive_base.iff", "object/tangible/food/crafted/additive/shared_additive_heavy.iff", "object/tangible/food/crafted/additive/shared_additive_medium.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_food_crafted_additive_shared_additive_light, "object/tangible/food/crafted/additive/shared_additive_light.iff")

object_tangible_food_crafted_additive_shared_additive_medium = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/food/crafted/additive/shared_additive_medium.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_medic_bacta_tank.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262144,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:food_additive_medium",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:food_additive_medium",

	noBuildRadius = 0,

	objectName = "@food_name:food_additive_medium",
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

	clientObjectCRC = 282579048,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/base/shared_base_crafted_food.iff", "object/tangible/food/base/shared_dish_base.iff", "object/tangible/food/crafted/additive/shared_additive_base.iff", "object/tangible/food/crafted/additive/shared_additive_heavy.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_food_crafted_additive_shared_additive_medium, "object/tangible/food/crafted/additive/shared_additive_medium.iff")
