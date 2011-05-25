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


object_tangible_component_droid_repair_shared_capacitor_high_discharge = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/wp_mine_drx55.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262148,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_droid_ingredients_d:capacitor_high_discharge",

	gameObjectType = 262148,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:capacitor_high_discharge",

	noBuildRadius = 0,

	objectName = "@craft_droid_ingredients_n:capacitor_high_discharge",
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

	clientObjectCRC = 475400384,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/droid/repair/shared_capacitor_low_discharge.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_droid_repair_shared_capacitor_high_discharge, "object/tangible/component/droid/repair/shared_capacitor_high_discharge.iff")

object_tangible_component_droid_repair_shared_capacitor_low_discharge = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_jewelry_setting.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262148,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_droid_ingredients_d:capacitor_low_discharge",

	gameObjectType = 262148,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:capacitor_low_discharge",

	noBuildRadius = 0,

	objectName = "@craft_droid_ingredients_n:capacitor_low_discharge",
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

	clientObjectCRC = 3184279961,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_droid_repair_shared_capacitor_low_discharge, "object/tangible/component/droid/repair/shared_capacitor_low_discharge.iff")

object_tangible_component_droid_repair_shared_diagnostic_circuit = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_electronic_module_simple.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262148,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_droid_ingredients_d:diagnostic_circuit",

	gameObjectType = 262148,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:diagnostic_circuit",

	noBuildRadius = 0,

	objectName = "@craft_droid_ingredients_n:diagnostic_circuit",
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

	clientObjectCRC = 1770332803,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_droid_repair_shared_diagnostic_circuit, "object/tangible/component/droid/repair/shared_diagnostic_circuit.iff")

object_tangible_component_droid_repair_shared_diagnostic_circuit_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_tool_engineering_analysis_board.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262148,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_droid_ingredients_d:diagnostic_circuit_advanced",

	gameObjectType = 262148,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:diagnostic_circuit_advanced",

	noBuildRadius = 0,

	objectName = "@craft_droid_ingredients_n:diagnostic_circuit_advanced",
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

	clientObjectCRC = 1133144792,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/droid/repair/shared_diagnostic_circuit.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_droid_repair_shared_diagnostic_circuit_advanced, "object/tangible/component/droid/repair/shared_diagnostic_circuit_advanced.iff")

object_tangible_component_droid_repair_shared_power_supply_redundant = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_weapon_targeting_computer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262148,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_droid_ingredients_d:power_supply_redundant",

	gameObjectType = 262148,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:power_supply_redundant",

	noBuildRadius = 0,

	objectName = "@craft_droid_ingredients_n:power_supply_redundant",
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

	clientObjectCRC = 2336135433,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_droid_repair_shared_power_supply_redundant, "object/tangible/component/droid/repair/shared_power_supply_redundant.iff")

object_tangible_component_droid_repair_shared_power_supply_redundant_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_tool_impulse_detector_s2.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262148,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_droid_ingredients_d:power_supply_redundant_advanced",

	gameObjectType = 262148,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:power_supply_redundant_advanced",

	noBuildRadius = 0,

	objectName = "@craft_droid_ingredients_n:power_supply_redundant_advanced",
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

	clientObjectCRC = 1755831948,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/droid/repair/shared_power_supply_redundant.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_droid_repair_shared_power_supply_redundant_advanced, "object/tangible/component/droid/repair/shared_power_supply_redundant_advanced.iff")

object_tangible_component_droid_repair_shared_repair_unit_casing = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_warhead_electronic.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262148,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_droid_ingredients_d:repair_unit_casing",

	gameObjectType = 262148,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:repair_unit_casing",

	noBuildRadius = 0,

	objectName = "@craft_droid_ingredients_n:repair_unit_casing",
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

	clientObjectCRC = 2421721438,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_droid_repair_shared_repair_unit_casing, "object/tangible/component/droid/repair/shared_repair_unit_casing.iff")

object_tangible_component_droid_repair_shared_repair_unit_casing_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_warhead_electronic.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262148,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_droid_ingredients_d:repair_unit_casing_advanced",

	gameObjectType = 262148,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:repair_unit_casing_advanced",

	noBuildRadius = 0,

	objectName = "@craft_droid_ingredients_n:repair_unit_casing_advanced",
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

	clientObjectCRC = 295372848,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/droid/repair/shared_repair_unit_casing.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_droid_repair_shared_repair_unit_casing_advanced, "object/tangible/component/droid/repair/shared_repair_unit_casing_advanced.iff")

object_tangible_component_droid_repair_shared_unit_delivery_cartridge = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_medpak_broad_spectrum.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262148,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_droid_ingredients_d:unit_delivery_cartridge",

	gameObjectType = 262148,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:unit_delivery_cartridge",

	noBuildRadius = 0,

	objectName = "@craft_droid_ingredients_n:unit_delivery_cartridge",
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

	clientObjectCRC = 3230177189,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_droid_repair_shared_unit_delivery_cartridge, "object/tangible/component/droid/repair/shared_unit_delivery_cartridge.iff")

object_tangible_component_droid_repair_shared_unit_delivery_cartridge_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_medpak_broad_spectrum.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262148,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_droid_ingredients_d:unit_delivery_cartridge_advanced",

	gameObjectType = 262148,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:unit_delivery_cartridge_advanced",

	noBuildRadius = 0,

	objectName = "@craft_droid_ingredients_n:unit_delivery_cartridge_advanced",
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

	clientObjectCRC = 1878973727,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/droid/repair/shared_unit_delivery_cartridge.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_droid_repair_shared_unit_delivery_cartridge_advanced, "object/tangible/component/droid/repair/shared_unit_delivery_cartridge_advanced.iff")
