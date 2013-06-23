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


object_tangible_component_chemistry_shared_biologic_effect_controller = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_biologic_effect_controller.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_healing_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:bio_effect_controller",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:bio_effect_controller",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:bio_effect_controller",
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

	clientObjectCRC = 3704098001,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_biologic_effect_controller, "object/tangible/component/chemistry/shared_biologic_effect_controller.iff")

object_tangible_component_chemistry_shared_biologic_effect_controller_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_biologic_effect_controller_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_healing_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:bio_effect_controller_advanced",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:bio_effect_controller_advanced",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:bio_effect_controller_advanced",
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

	clientObjectCRC = 2300334388,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/chemistry/shared_biologic_effect_controller.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_biologic_effect_controller_advanced, "object/tangible/component/chemistry/shared_biologic_effect_controller_advanced.iff")

object_tangible_component_chemistry_shared_chemistry_component = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_chemistry_component.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemistry_ingredients_d:chemistry_base_component",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:chemistry_base_component",

	noBuildRadius = 0,

	objectName = "@craft_chemistry_ingredients_n:chemistry_base_component",
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

	clientObjectCRC = 1107717367,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_chemistry_component, "object/tangible/component/chemistry/shared_chemistry_component.iff")

object_tangible_component_chemistry_shared_dispersal_mechanism = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_dispersal_mechanism.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_healing_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:dispersal_mechanism",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dispersal_mechanism",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:dispersal_mechanism",
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

	clientObjectCRC = 2561274877,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_dispersal_mechanism, "object/tangible/component/chemistry/shared_dispersal_mechanism.iff")

object_tangible_component_chemistry_shared_dispersal_mechanism_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_dispersal_mechanism_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_healing_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:dispersal_mechanism_advanced",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dispersal_mechanism_advanced",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:dispersal_mechanism_advanced",
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

	clientObjectCRC = 1183326232,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/chemistry/shared_dispersal_mechanism.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_dispersal_mechanism_advanced, "object/tangible/component/chemistry/shared_dispersal_mechanism_advanced.iff")

object_tangible_component_chemistry_shared_dispersal_mechanism_quest = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_dispersal_mechanism_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_healing_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:dispersal_mechanism_quest",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dispersal_mechanism_advanced",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:dispersal_mechanism_quest",
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

	clientObjectCRC = 3662200732,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/chemistry/shared_dispersal_mechanism.iff", "object/tangible/component/chemistry/shared_dispersal_mechanism_advanced.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_dispersal_mechanism_quest, "object/tangible/component/chemistry/shared_dispersal_mechanism_quest.iff")

object_tangible_component_chemistry_shared_endrost = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_endrost.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/con_fs_quest_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 4194316,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@community_crafting_d:endrost",

	gameObjectType = 4194316,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@community_crafting_n:endrost",
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

	clientObjectCRC = 1566810278,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_endrost, "object/tangible/component/chemistry/shared_endrost.iff")

object_tangible_component_chemistry_shared_infection_amplifier = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_infection_amplifier.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_healing_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:infection_amplifier",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:infection_amplifier",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:infection_amplifier",
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

	clientObjectCRC = 1679113487,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_infection_amplifier, "object/tangible/component/chemistry/shared_infection_amplifier.iff")

object_tangible_component_chemistry_shared_infection_amplifier_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_infection_amplifier_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_healing_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:infection_amplifier_advanced",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:infection_amplifier_advanced",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:infection_amplifier_advanced",
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

	clientObjectCRC = 1129599787,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/chemistry/shared_infection_amplifier.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_infection_amplifier_advanced, "object/tangible/component/chemistry/shared_infection_amplifier_advanced.iff")

object_tangible_component_chemistry_shared_infection_amplifier_donkuwah = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_infection_amplifier_donkuwah.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/edb_con_tato_jar_funk_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:infection_amplifier_donkuwah",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:infection_amplifier_donkuwah",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:infection_amplifier_donkuwah",
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

	clientObjectCRC = 2542466646,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/chemistry/shared_infection_amplifier.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_infection_amplifier_donkuwah, "object/tangible/component/chemistry/shared_infection_amplifier_donkuwah.iff")

object_tangible_component_chemistry_shared_janta_blood = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_janta_blood.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/edb_con_tato_jar_funk_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:janta_blood",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:janta_blood",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:janta_blood",
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

	clientObjectCRC = 1058893195,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/chemistry/shared_biologic_effect_controller.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_janta_blood, "object/tangible/component/chemistry/shared_janta_blood.iff")

object_tangible_component_chemistry_shared_liquid_delivery_suspension = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_liquid_delivery_suspension.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_healing_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:liquid_suspension",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:liquid_suspension",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:liquid_suspension",
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

	clientObjectCRC = 3358009919,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_liquid_delivery_suspension, "object/tangible/component/chemistry/shared_liquid_delivery_suspension.iff")

object_tangible_component_chemistry_shared_liquid_delivery_suspension_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_liquid_delivery_suspension_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_healing_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:liquid_suspension_advanced",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:liquid_suspension_advanced",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:liquid_suspension_advanced",
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

	clientObjectCRC = 1862978449,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/chemistry/shared_liquid_delivery_suspension.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_liquid_delivery_suspension_advanced, "object/tangible/component/chemistry/shared_liquid_delivery_suspension_advanced.iff")

object_tangible_component_chemistry_shared_liquid_delivery_suspension_quest = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_liquid_delivery_suspension_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_healing_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:liquid_suspension_quest",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:liquid_suspension_advanced",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:liquid_suspension_quest",
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

	clientObjectCRC = 2125828642,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/chemistry/shared_liquid_delivery_suspension.iff", "object/tangible/component/chemistry/shared_liquid_delivery_suspension_advanced.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_liquid_delivery_suspension_quest, "object/tangible/component/chemistry/shared_liquid_delivery_suspension_quest.iff")

object_tangible_component_chemistry_shared_quest_stimpack_a = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_quest_stimpack_a.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:quest_stimpack_a",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:quest_stimpack_a",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:quest_stimpack_a",
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

	clientObjectCRC = 478044743,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_quest_stimpack_a, "object/tangible/component/chemistry/shared_quest_stimpack_a.iff")

object_tangible_component_chemistry_shared_rancor_bile = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_rancor_bile.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/edb_con_tato_jar_guts_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:rancor_bile",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rancor_bile",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:rancor_bile",
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

	clientObjectCRC = 317047330,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/chemistry/shared_dispersal_mechanism.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_rancor_bile, "object/tangible/component/chemistry/shared_rancor_bile.iff")

object_tangible_component_chemistry_shared_release_mechanism_duration = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_release_mechanism_duration.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:release_mech_duration",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:release_mech_duration",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:release_mech_duration",
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

	clientObjectCRC = 1870489005,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_release_mechanism_duration, "object/tangible/component/chemistry/shared_release_mechanism_duration.iff")

object_tangible_component_chemistry_shared_release_mechanism_duration_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_release_mechanism_duration_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:release_mech_duration_advanced",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:release_mech_duration_advanced",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:release_mech_duration_advanced",
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

	clientObjectCRC = 282084455,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/chemistry/shared_release_mechanism_duration.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_release_mechanism_duration_advanced, "object/tangible/component/chemistry/shared_release_mechanism_duration_advanced.iff")

object_tangible_component_chemistry_shared_resilience_compound = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_resilience_compound.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_healing_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:resilience_compound",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:resilience_compound",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:resilience_compound",
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

	clientObjectCRC = 2132263971,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_resilience_compound, "object/tangible/component/chemistry/shared_resilience_compound.iff")

object_tangible_component_chemistry_shared_resilience_compound_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_resilience_compound_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_healing_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:resilience_compound_advanced",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:resilience_compound_advanced",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:resilience_compound_advanced",
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

	clientObjectCRC = 101893931,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/chemistry/shared_resilience_compound.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_resilience_compound_advanced, "object/tangible/component/chemistry/shared_resilience_compound_advanced.iff")

object_tangible_component_chemistry_shared_solid_delivery_shell = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_solid_delivery_shell.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:solid_delivery_shell",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:solid_delivery_shell",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:solid_delivery_shell",
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

	clientObjectCRC = 2203679790,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_solid_delivery_shell, "object/tangible/component/chemistry/shared_solid_delivery_shell.iff")

object_tangible_component_chemistry_shared_solid_delivery_shell_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_solid_delivery_shell_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:solid_delivery_shell_advanced",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:solid_delivery_shell_advanced",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:solid_delivery_shell_advanced",
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

	clientObjectCRC = 2952575979,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/chemistry/shared_solid_delivery_shell.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_solid_delivery_shell_advanced, "object/tangible/component/chemistry/shared_solid_delivery_shell_advanced.iff")

object_tangible_component_chemistry_shared_spider_venom = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/chemistry/shared_spider_venom.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_drink.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262146,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_chemical_ingredients_d:spider_venom",

	gameObjectType = 262146,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:spider_venom",

	noBuildRadius = 0,

	objectName = "@craft_chemical_ingredients_n:spider_venom",
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

	clientObjectCRC = 3428815879,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/chemistry/shared_infection_amplifier.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_chemistry_shared_spider_venom, "object/tangible/component/chemistry/shared_spider_venom.iff")
