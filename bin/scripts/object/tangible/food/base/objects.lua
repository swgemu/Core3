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


object_tangible_food_base_shared_alcoholic_drink_base = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_glass_s2_full.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8216,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:base_alcoholic_drink",

	gameObjectType = 8216,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:base_alcoholic_drink",

	noBuildRadius = 0,

	objectName = "@craft_food_ingredients_n:base_alcoholic_drink",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 57637204
}

ObjectTemplates:addClientTemplate(object_tangible_food_base_shared_alcoholic_drink_base, "object/tangible/food/base/shared_alcoholic_drink_base.iff")

object_tangible_food_base_shared_base_crafted_food = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_food_fruit_melon.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:base_food",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:base_food",

	noBuildRadius = 0,

	objectName = "@food_name:base_food",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3304775743
}

ObjectTemplates:addClientTemplate(object_tangible_food_base_shared_base_crafted_food, "object/tangible/food/base/shared_base_crafted_food.iff")

object_tangible_food_base_shared_base_food = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_food_fruit_melon.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:base_food",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:base_food",

	noBuildRadius = 0,

	objectName = "@food_name:base_food",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3228094758
}

ObjectTemplates:addClientTemplate(object_tangible_food_base_shared_base_food, "object/tangible/food/base/shared_base_food.iff")

object_tangible_food_base_shared_desert_base = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_filled_pastry.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:desert",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:desert",

	noBuildRadius = 0,

	objectName = "@craft_food_ingredients_n:desert",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 314474339
}

ObjectTemplates:addClientTemplate(object_tangible_food_base_shared_desert_base, "object/tangible/food/base/shared_desert_base.iff")

object_tangible_food_base_shared_dish_base = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_dish_casserole_full.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:food_dish",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:food_dish",

	noBuildRadius = 0,

	objectName = "@food_name:food_dish",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3988054565
}

ObjectTemplates:addClientTemplate(object_tangible_food_base_shared_dish_base, "object/tangible/food/base/shared_dish_base.iff")

object_tangible_food_base_shared_drink_base = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_glass_s1_full.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8216,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:base_drink",

	gameObjectType = 8216,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:base_drink",

	noBuildRadius = 0,

	objectName = "@craft_food_ingredients_n:base_drink",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 224626249
}

ObjectTemplates:addClientTemplate(object_tangible_food_base_shared_drink_base, "object/tangible/food/base/shared_drink_base.iff")

object_tangible_food_base_shared_meal_base = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_plate_s1_full.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:meal",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:meal",

	noBuildRadius = 0,

	objectName = "@craft_food_ingredients_n:meal",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 549891041
}

ObjectTemplates:addClientTemplate(object_tangible_food_base_shared_meal_base, "object/tangible/food/base/shared_meal_base.iff")

object_tangible_food_base_shared_meat_base = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_meat_item.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:base_meat",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:base_meat",

	noBuildRadius = 0,

	objectName = "@craft_food_ingredients_n:base_meat",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 407188941
}

ObjectTemplates:addClientTemplate(object_tangible_food_base_shared_meat_base, "object/tangible/food/base/shared_meat_base.iff")

object_tangible_food_base_shared_side_dish_base = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_bowl_full.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:side_dish",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:side_dish",

	noBuildRadius = 0,

	objectName = "@craft_food_ingredients_n:side_dish",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 666169127
}

ObjectTemplates:addClientTemplate(object_tangible_food_base_shared_side_dish_base, "object/tangible/food/base/shared_side_dish_base.iff")

object_tangible_food_base_shared_veggie_base = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_vegetable_item.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:base_veggie",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:base_veggie",

	noBuildRadius = 0,

	objectName = "@craft_food_ingredients_n:base_veggie",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2342861658
}

ObjectTemplates:addClientTemplate(object_tangible_food_base_shared_veggie_base, "object/tangible/food/base/shared_veggie_base.iff")
