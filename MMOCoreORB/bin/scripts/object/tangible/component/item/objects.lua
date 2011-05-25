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


object_tangible_component_item_shared_electronic_control_unit = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_electronic_module_complex.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262149,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_item_ingredients_d:electronic_control_unit",

	gameObjectType = 262149,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:electronic_control_unit",

	noBuildRadius = 0,

	objectName = "@craft_item_ingredients_n:electronic_control_unit",
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

	clientObjectCRC = 814846904,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_electronic_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_item_shared_electronic_control_unit, "object/tangible/component/item/shared_electronic_control_unit.iff")

object_tangible_component_item_shared_electronic_energy_distributor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_electronic_power_unit.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262149,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_item_ingredients_d:electronic_energy_distributor",

	gameObjectType = 262149,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:electronic_energy_distributor",

	noBuildRadius = 0,

	objectName = "@craft_item_ingredients_n:electronic_energy_distributor",
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

	clientObjectCRC = 3328520335,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_electronic_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_item_shared_electronic_energy_distributor, "object/tangible/component/item/shared_electronic_energy_distributor.iff")

object_tangible_component_item_shared_electronic_power_conditioner = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_electronic_power_unit.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262149,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_item_ingredients_d:electronic_power_conditioner",

	gameObjectType = 262149,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:electronic_power_conditioner",

	noBuildRadius = 0,

	objectName = "@craft_item_ingredients_n:electronic_power_conditioner",
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

	clientObjectCRC = 1024745663,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_electronic_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_item_shared_electronic_power_conditioner, "object/tangible/component/item/shared_electronic_power_conditioner.iff")

object_tangible_component_item_shared_electronics_gp_module = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_electronic_module_simple.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262149,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_item_ingredients_d:electronics_gp_module",

	gameObjectType = 262149,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:electronics_gp_module",

	noBuildRadius = 0,

	objectName = "@craft_item_ingredients_n:electronics_gp_module",
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

	clientObjectCRC = 3786408832,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_electronic_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_item_shared_electronics_gp_module, "object/tangible/component/item/shared_electronics_gp_module.iff")

object_tangible_component_item_shared_electronics_memory_module = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_electronic_module_simple.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262149,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_item_ingredients_d:electronics_memory_module",

	gameObjectType = 262149,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:electronics_memory_module",

	noBuildRadius = 0,

	objectName = "@craft_item_ingredients_n:electronics_memory_module",
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

	clientObjectCRC = 3552886678,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_electronic_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_item_shared_electronics_memory_module, "object/tangible/component/item/shared_electronics_memory_module.iff")

object_tangible_component_item_shared_large_sensor_package = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_electronic_module_complex.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262149,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_item_ingredients_d:large_sensor_package",

	gameObjectType = 262149,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:large_sensor_package",

	noBuildRadius = 0,

	objectName = "@craft_item_ingredients_n:large_sensor_package",
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

	clientObjectCRC = 366580459,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_electronic_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_item_shared_large_sensor_package, "object/tangible/component/item/shared_large_sensor_package.iff")

object_tangible_component_item_shared_micro_sensor_suite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_electronic_module_complex.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262149,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_item_ingredients_d:micro_sensor_suite",

	gameObjectType = 262149,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:micro_sensor_suite",

	noBuildRadius = 0,

	objectName = "@craft_item_ingredients_n:micro_sensor_suite",
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

	clientObjectCRC = 3198540321,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_electronic_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_item_shared_micro_sensor_suite, "object/tangible/component/item/shared_micro_sensor_suite.iff")
