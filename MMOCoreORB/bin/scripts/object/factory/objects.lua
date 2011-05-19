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


object_factory_shared_factory_crate_armor = SharedFactoryObjectTemplate:new {
	appearanceFilename = "appearance/con_man_armor_sm.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8209,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@factory_d:armor_crate",

	gameObjectType = 8209,

	locationReservationRadius = 0,
	lookAtText = "factory_l",

	noBuildRadius = 0,

	objectName = "@factory_n:armor_crate",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1598099833,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/factory/base/shared_base_factory.iff"}
}

ObjectTemplates:addClientTemplate(object_factory_shared_factory_crate_armor, "object/factory/shared_factory_crate_armor.iff")

object_factory_shared_factory_crate_chemicals = SharedFactoryObjectTemplate:new {
	appearanceFilename = "appearance/con_man_chemicals_sm.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8209,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@factory_d:chemicals_crate",

	gameObjectType = 8209,

	locationReservationRadius = 0,
	lookAtText = "factory_l",

	noBuildRadius = 0,

	objectName = "@factory_n:chemicals_crate",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3401438151,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/factory/base/shared_base_factory.iff"}
}

ObjectTemplates:addClientTemplate(object_factory_shared_factory_crate_chemicals, "object/factory/shared_factory_crate_chemicals.iff")

object_factory_shared_factory_crate_clothing = SharedFactoryObjectTemplate:new {
	appearanceFilename = "appearance/con_man_clothing_sm.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8209,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@factory_d:clothing_factory_crate",

	gameObjectType = 8209,

	locationReservationRadius = 0,
	lookAtText = "factory_l",

	noBuildRadius = 0,

	objectName = "@factory_n:clothing_factory_crate",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2342101395,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/factory/base/shared_base_factory.iff"}
}

ObjectTemplates:addClientTemplate(object_factory_shared_factory_crate_clothing, "object/factory/shared_factory_crate_clothing.iff")

object_factory_shared_factory_crate_electronics = SharedFactoryObjectTemplate:new {
	appearanceFilename = "appearance/con_man_electronics_sm.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8209,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@factory_d:electronics_crate",

	gameObjectType = 8209,

	locationReservationRadius = 0,
	lookAtText = "factory_l",

	noBuildRadius = 0,

	objectName = "@factory_n:electronics_crate",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1584679689,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/factory/base/shared_base_factory.iff"}
}

ObjectTemplates:addClientTemplate(object_factory_shared_factory_crate_electronics, "object/factory/shared_factory_crate_electronics.iff")

object_factory_shared_factory_crate_food = SharedFactoryObjectTemplate:new {
	appearanceFilename = "appearance/con_man_food_sm.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8209,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@factory_d:food_crate",

	gameObjectType = 8209,

	locationReservationRadius = 0,
	lookAtText = "factory_l",

	noBuildRadius = 0,

	objectName = "@factory_n:food_crate",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1184983851,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/factory/base/shared_base_factory.iff"}
}

ObjectTemplates:addClientTemplate(object_factory_shared_factory_crate_food, "object/factory/shared_factory_crate_food.iff")

object_factory_shared_factory_crate_furniture = SharedFactoryObjectTemplate:new {
	appearanceFilename = "appearance/con_man_furniture_sm.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8209,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@factory_d:furniture_crate",

	gameObjectType = 8209,

	locationReservationRadius = 0,
	lookAtText = "factory_l",

	noBuildRadius = 0,

	objectName = "@factory_n:furniture_crate",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3880912033,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/factory/base/shared_base_factory.iff"}
}

ObjectTemplates:addClientTemplate(object_factory_shared_factory_crate_furniture, "object/factory/shared_factory_crate_furniture.iff")

object_factory_shared_factory_crate_generic_items = SharedFactoryObjectTemplate:new {
	appearanceFilename = "appearance/con_man_items_sm.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8209,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@factory_d:generic_items_crate",

	gameObjectType = 8209,

	locationReservationRadius = 0,
	lookAtText = "factory_l",

	noBuildRadius = 0,

	objectName = "@factory_n:generic_items_crate",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 685226208,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/factory/base/shared_base_factory.iff"}
}

ObjectTemplates:addClientTemplate(object_factory_shared_factory_crate_generic_items, "object/factory/shared_factory_crate_generic_items.iff")

object_factory_shared_factory_crate_installation = SharedFactoryObjectTemplate:new {
	appearanceFilename = "appearance/con_man_installation_sm.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8209,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@factory_d:installation_crate",

	gameObjectType = 8209,

	locationReservationRadius = 0,
	lookAtText = "factory_l",

	noBuildRadius = 0,

	objectName = "@factory_n:installation_crate",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 577406456,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/factory/base/shared_base_factory.iff"}
}

ObjectTemplates:addClientTemplate(object_factory_shared_factory_crate_installation, "object/factory/shared_factory_crate_installation.iff")

object_factory_shared_factory_crate_weapon = SharedFactoryObjectTemplate:new {
	appearanceFilename = "appearance/con_man_weapons_sm.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8209,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@factory_d:clothing_factory_crate",

	gameObjectType = 8209,

	locationReservationRadius = 0,
	lookAtText = "factory_l",

	noBuildRadius = 0,

	objectName = "@factory_n:clothing_factory_crate",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4077073151,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/factory/base/shared_base_factory.iff"}
}

ObjectTemplates:addClientTemplate(object_factory_shared_factory_crate_weapon, "object/factory/shared_factory_crate_weapon.iff")
