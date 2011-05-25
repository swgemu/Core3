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


object_tangible_food_foraged_shared_edible_jar_berries = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_tato_jar_berries_s01.apt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@food_detail:edible_berries",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:edible_berries",

	noBuildRadius = 0,

	objectName = "@food_name:edible_berries",
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

	clientObjectCRC = 1405655823,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/base/shared_base_food.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_foraged_shared_edible_jar_berries, "object/tangible/food/foraged/shared_edible_jar_berries.iff")

object_tangible_food_foraged_shared_edible_jar_bugs = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_tato_jar_bugs_s01.apt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@food_detail:edible_bugs",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:edible_bugs",

	noBuildRadius = 0,

	objectName = "@food_name:edible_bugs",
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

	clientObjectCRC = 2220813342,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/base/shared_base_food.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_foraged_shared_edible_jar_bugs, "object/tangible/food/foraged/shared_edible_jar_bugs.iff")

object_tangible_food_foraged_shared_edible_jar_fungus = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_tato_jar_guts_s01.apt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@food_detail:edible_fungus",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:edible_fungus",

	noBuildRadius = 0,

	objectName = "@food_name:edible_fungus",
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

	clientObjectCRC = 404667969,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/base/shared_base_food.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_foraged_shared_edible_jar_fungus, "object/tangible/food/foraged/shared_edible_jar_fungus.iff")

object_tangible_food_foraged_shared_edible_jar_funk = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_tato_jar_funk_s01.apt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@food_detail:edible_funk",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:edible_funk",

	noBuildRadius = 0,

	objectName = "@food_name:edible_funk",
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

	clientObjectCRC = 3997953331,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/base/shared_base_food.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_foraged_shared_edible_jar_funk, "object/tangible/food/foraged/shared_edible_jar_funk.iff")

object_tangible_food_foraged_shared_edible_jar_livers = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_tato_jar_guts_s01.apt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@food_detail:edible_livers",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:edible_livers",

	noBuildRadius = 0,

	objectName = "@food_name:edible_livers",
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

	clientObjectCRC = 4279994826,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/base/shared_base_food.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_foraged_shared_edible_jar_livers, "object/tangible/food/foraged/shared_edible_jar_livers.iff")

object_tangible_food_foraged_shared_foraged_fruit_s1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_food_fruit_melon.apt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@food_detail:foraged_fruit_1",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:foraged_fruit_1",

	noBuildRadius = 0,

	objectName = "@food_name:foraged_fruit_1",
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

	clientObjectCRC = 1125771498,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/base/shared_base_food.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_foraged_shared_foraged_fruit_s1, "object/tangible/food/foraged/shared_foraged_fruit_s1.iff")

object_tangible_food_foraged_shared_foraged_fruit_s2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_food_fruit_s2.apt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@food_detail:foraged_fruit_2",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:foraged_fruit_2",

	noBuildRadius = 0,

	objectName = "@food_name:foraged_fruit_2",
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

	clientObjectCRC = 2551070845,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/base/shared_base_food.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_foraged_shared_foraged_fruit_s2, "object/tangible/food/foraged/shared_foraged_fruit_s2.iff")

object_tangible_food_foraged_shared_foraged_fruit_s3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_food_fruit_s3.apt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@food_detail:foraged_fruit_3",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:foraged_fruit_3",

	noBuildRadius = 0,

	objectName = "@food_name:foraged_fruit_3",
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

	clientObjectCRC = 3506644976,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/base/shared_base_food.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_foraged_shared_foraged_fruit_s3, "object/tangible/food/foraged/shared_foraged_fruit_s3.iff")

object_tangible_food_foraged_shared_foraged_fruit_s4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_food_fruit_s4.apt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@food_detail:foraged_fruit_4",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:foraged_fruit_4",

	noBuildRadius = 0,

	objectName = "@food_name:foraged_fruit_4",
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

	clientObjectCRC = 719326436,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/base/shared_base_food.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_foraged_shared_foraged_fruit_s4, "object/tangible/food/foraged/shared_foraged_fruit_s4.iff")

object_tangible_food_foraged_shared_foraged_fruit_s5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_food_fruit_s5.apt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@food_detail:foraged_fruit_5",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:foraged_fruit_5",

	noBuildRadius = 0,

	objectName = "@food_name:foraged_fruit_5",
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

	clientObjectCRC = 1676503913,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/base/shared_base_food.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_foraged_shared_foraged_fruit_s5, "object/tangible/food/foraged/shared_foraged_fruit_s5.iff")

object_tangible_food_foraged_shared_foraged_vegetable_s2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_food_vegetable_s2.apt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@food_detail:foraged_vegetable_1",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:foraged_vegetable_1",

	noBuildRadius = 0,

	objectName = "@food_name:foraged_vegetable_1",
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

	clientObjectCRC = 2375994584,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/base/shared_base_food.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_foraged_shared_foraged_vegetable_s2, "object/tangible/food/foraged/shared_foraged_vegetable_s2.iff")

object_tangible_food_foraged_shared_foraged_vegetable_s3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_food_vegetable_s3.apt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@food_detail:foraged_vegetable_2",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:foraged_vegetable_2",

	noBuildRadius = 0,

	objectName = "@food_name:foraged_vegetable_2",
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

	clientObjectCRC = 3298011989,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/base/shared_base_food.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_foraged_shared_foraged_vegetable_s3, "object/tangible/food/foraged/shared_foraged_vegetable_s3.iff")

object_tangible_food_foraged_shared_foraged_vegetable_s4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_food_vegetable_s4.apt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@food_detail:foraged_vegetable_3",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:foraged_vegetable_3",

	noBuildRadius = 0,

	objectName = "@food_name:foraged_vegetable_3",
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

	clientObjectCRC = 1064337473,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/base/shared_base_food.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_foraged_shared_foraged_vegetable_s4, "object/tangible/food/foraged/shared_foraged_vegetable_s4.iff")

object_tangible_food_foraged_shared_foraged_vegetable_s5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_food_vegetable_s5.apt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "@food_detail:foraged_vegetable_4",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:foraged_vegetable_4",

	noBuildRadius = 0,

	objectName = "@food_name:foraged_vegetable_4",
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

	clientObjectCRC = 1987962828,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/base/shared_base_food.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_foraged_shared_foraged_vegetable_s5, "object/tangible/food/foraged/shared_foraged_vegetable_s5.iff")
