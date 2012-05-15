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


object_tangible_component_armor_shared_armor_layer = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_layer.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_layer",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_layer",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_layer",
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

	clientObjectCRC = 3871435906,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_layer, "object/tangible/component/armor/shared_armor_layer.iff")

object_tangible_component_armor_shared_armor_layer_acid = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_layer_acid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_layer_acid",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_layer_acid",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_layer_acid",
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

	clientObjectCRC = 3368394489,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_layer_acid, "object/tangible/component/armor/shared_armor_layer_acid.iff")

object_tangible_component_armor_shared_armor_layer_blast = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_layer_blast.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_layer_blast",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_layer_blast",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_layer_blast",
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

	clientObjectCRC = 3979633097,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_layer_blast, "object/tangible/component/armor/shared_armor_layer_blast.iff")

object_tangible_component_armor_shared_armor_layer_cold = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_layer_cold.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_layer_cold",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_layer_cold",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_layer_cold",
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

	clientObjectCRC = 1118558688,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_layer_cold, "object/tangible/component/armor/shared_armor_layer_cold.iff")

object_tangible_component_armor_shared_armor_layer_electrical = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_layer_electrical.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_layer_electrical",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_layer_electrical",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_layer_electrical",
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

	clientObjectCRC = 2194125131,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_layer_electrical, "object/tangible/component/armor/shared_armor_layer_electrical.iff")

object_tangible_component_armor_shared_armor_layer_energy = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_layer_energy.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_layer_energy",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_layer_energy",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_layer_energy",
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

	clientObjectCRC = 2938969271,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_layer_energy, "object/tangible/component/armor/shared_armor_layer_energy.iff")

object_tangible_component_armor_shared_armor_layer_environmental = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_layer_environmental.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_layer_environmental",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_layer_environmental",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_layer_environmental",
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

	clientObjectCRC = 2751814176,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_layer_environmental, "object/tangible/component/armor/shared_armor_layer_environmental.iff")

object_tangible_component_armor_shared_armor_layer_heat = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_layer_heat.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_layer_heat",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_layer_heat",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_layer_heat",
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

	clientObjectCRC = 3125319440,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_layer_heat, "object/tangible/component/armor/shared_armor_layer_heat.iff")

object_tangible_component_armor_shared_armor_layer_kinetic = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_layer_kinetic.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_layer_kinetic",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_layer_kinetic",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_layer_kinetic",
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

	clientObjectCRC = 2095312993,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_layer_kinetic, "object/tangible/component/armor/shared_armor_layer_kinetic.iff")

object_tangible_component_armor_shared_armor_layer_nightsister = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_layer_nightsister.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_layer_nightsister",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_layer_nightsister",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_layer_nightsister",
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

	clientObjectCRC = 3536633958,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_layer_nightsister, "object/tangible/component/armor/shared_armor_layer_nightsister.iff")

object_tangible_component_armor_shared_armor_layer_restraint = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_layer_restraint.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_layer_restraint",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_layer_restraint",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_layer_restraint",
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

	clientObjectCRC = 3874261151,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_layer_restraint, "object/tangible/component/armor/shared_armor_layer_restraint.iff")

object_tangible_component_armor_shared_armor_layer_ris = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_layer_ris.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_layer_ris",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_layer_ris",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_layer_ris",
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

	clientObjectCRC = 2996647863,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_layer_ris, "object/tangible/component/armor/shared_armor_layer_ris.iff")

object_tangible_component_armor_shared_armor_layer_stun = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_layer_stun.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_layer_stun",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_layer_stun",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_layer_stun",
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

	clientObjectCRC = 203108001,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_layer_stun, "object/tangible/component/armor/shared_armor_layer_stun.iff")

object_tangible_component_armor_shared_armor_module_heavy = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_module_heavy.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_module.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_module_heavy",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_module_heavy",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_module_heavy",
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

	clientObjectCRC = 1321171754,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_module_heavy, "object/tangible/component/armor/shared_armor_module_heavy.iff")

object_tangible_component_armor_shared_armor_module_light = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_module_light.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_module.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_module_light",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_module_light",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_module_light",
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

	clientObjectCRC = 2414299124,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_module_light, "object/tangible/component/armor/shared_armor_module_light.iff")

object_tangible_component_armor_shared_armor_segment = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment",
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

	clientObjectCRC = 1357044619,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment, "object/tangible/component/armor/shared_armor_segment.iff")

object_tangible_component_armor_shared_armor_segment_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_advanced",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_advanced",
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

	clientObjectCRC = 34830358,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_advanced, "object/tangible/component/armor/shared_armor_segment_advanced.iff")

object_tangible_component_armor_shared_armor_segment_bone = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_bone.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_bone",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_bone",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_bone",
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

	clientObjectCRC = 1150752581,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_bone, "object/tangible/component/armor/shared_armor_segment_bone.iff")

object_tangible_component_armor_shared_armor_segment_bone_acklay = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_bone_acklay.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_bone_acklay",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_bone_acklay",

	noBuildRadius = 0,

	objectName = "@craft_armor_ingredients_n:armor_segment_bone_acklay",
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

	clientObjectCRC = 1282707003,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_bone.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_bone_acklay, "object/tangible/component/armor/shared_armor_segment_bone_acklay.iff")

object_tangible_component_armor_shared_armor_segment_bone_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_bone_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_bone_advanced",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_bone",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_bone_advanced",
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

	clientObjectCRC = 2814096223,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_bone.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_bone_advanced, "object/tangible/component/armor/shared_armor_segment_bone_advanced.iff")

object_tangible_component_armor_shared_armor_segment_bone_donkuwah = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_bone_donkuwah.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_bone_donkuwah",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_bone_donkuwah",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_bone_donkuwah",
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

	clientObjectCRC = 1936004642,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_bone.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_bone_donkuwah, "object/tangible/component/armor/shared_armor_segment_bone_donkuwah.iff")

object_tangible_component_armor_shared_armor_segment_bone_kimogila = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_bone_kimogila.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_bone_kimogila",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_bone_kimogila",

	noBuildRadius = 0,

	objectName = "@craft_armor_ingredients_n:armor_segment_bone_kimogila",
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

	clientObjectCRC = 2307142178,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_bone.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_bone_kimogila, "object/tangible/component/armor/shared_armor_segment_bone_kimogila.iff")

object_tangible_component_armor_shared_armor_segment_bone_voritor_lizard = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_bone_voritor_lizard.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_bone_voritor_lizard",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_bone_voritor_lizard",

	noBuildRadius = 0,

	objectName = "@craft_armor_ingredients_n:armor_segment_bone_voritor_lizard",
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

	clientObjectCRC = 534961284,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_bone.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_bone_voritor_lizard, "object/tangible/component/armor/shared_armor_segment_bone_voritor_lizard.iff")

object_tangible_component_armor_shared_armor_segment_chitin = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_chitin.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_chitin",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_chitin",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_chitin",
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

	clientObjectCRC = 3560749582,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_chitin, "object/tangible/component/armor/shared_armor_segment_chitin.iff")

object_tangible_component_armor_shared_armor_segment_chitin_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_chitin_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_chitin_advanced",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_chitin_advanced",
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

	clientObjectCRC = 2809337004,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_chitin.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_chitin_advanced, "object/tangible/component/armor/shared_armor_segment_chitin_advanced.iff")

object_tangible_component_armor_shared_armor_segment_chitin_brackaset = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_chitin_brackaset.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_chitin_brackaset",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_chitin_brackaset",

	noBuildRadius = 0,

	objectName = "@craft_armor_ingredients_n:armor_segment_chitin_brackaset",
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

	clientObjectCRC = 3248573794,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_chitin.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_chitin_brackaset, "object/tangible/component/armor/shared_armor_segment_chitin_brackaset.iff")

object_tangible_component_armor_shared_armor_segment_chitin_kliknick = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_chitin_kliknick.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_chitin_kliknick",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_chitin_kliknick",
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

	clientObjectCRC = 2446761645,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_chitin.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_chitin_kliknick, "object/tangible/component/armor/shared_armor_segment_chitin_kliknick.iff")

object_tangible_component_armor_shared_armor_segment_chitin_kliknick_adv = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_chitin_kliknick_adv.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_chitin_kliknick_adv",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment",

	noBuildRadius = 0,

	objectName = "@craft_armor_ingredients_n:armor_segment_chitin_kliknick_adv",
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

	clientObjectCRC = 2037172516,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_chitin.iff", "object/tangible/component/armor/shared_armor_segment_chitin_kliknick.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_chitin_kliknick_adv, "object/tangible/component/armor/shared_armor_segment_chitin_kliknick_adv.iff")

object_tangible_component_armor_shared_armor_segment_chitin_sharnaff = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_chitin_sharnaff.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_chitin_sharnaff",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_chitin_sharnaff",

	noBuildRadius = 0,

	objectName = "@craft_armor_ingredients_n:armor_segment_chitin_sharnaff",
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

	clientObjectCRC = 1708779648,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_chitin.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_chitin_sharnaff, "object/tangible/component/armor/shared_armor_segment_chitin_sharnaff.iff")

object_tangible_component_armor_shared_armor_segment_composite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_composite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_clothing_ingredients_d:armor_segment_composite",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_composite",
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

	clientObjectCRC = 3596548182,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_composite, "object/tangible/component/armor/shared_armor_segment_composite.iff")

object_tangible_component_armor_shared_armor_segment_composite_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_composite_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_clothing_ingredients_d:armor_segment_composite_advanced",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_composite_advanced",
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

	clientObjectCRC = 2764212654,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_composite.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_composite_advanced, "object/tangible/component/armor/shared_armor_segment_composite_advanced.iff")

object_tangible_component_armor_shared_armor_segment_composite_krayt = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_composite_krayt.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_clothing_ingredients_d:armor_segment_composite_krayt",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_composite_krayt",
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

	clientObjectCRC = 2649372559,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_composite.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_composite_krayt, "object/tangible/component/armor/shared_armor_segment_composite_krayt.iff")

object_tangible_component_armor_shared_armor_segment_enhancement_brackaset = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_enhancement_brackaset.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_enhancement_brackaset",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_enhancement_brackaset",

	noBuildRadius = 0,

	objectName = "@craft_armor_ingredients_n:armor_segment_enhancement_brackaset",
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

	clientObjectCRC = 591672738,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_base_armor_segment_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_enhancement_brackaset, "object/tangible/component/armor/shared_armor_segment_enhancement_brackaset.iff")

object_tangible_component_armor_shared_armor_segment_enhancement_dragonet = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_enhancement_dragonet.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_enhancement_dragonet",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_enhancement_dragonet",

	noBuildRadius = 0,

	objectName = "@craft_armor_ingredients_n:armor_segment_enhancement_dragonet",
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

	clientObjectCRC = 433071916,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_base_armor_segment_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_enhancement_dragonet, "object/tangible/component/armor/shared_armor_segment_enhancement_dragonet.iff")

object_tangible_component_armor_shared_armor_segment_enhancement_fambaa = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_enhancement_fambaa.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_enhancement_fambaa",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_enhancement_fambaa",

	noBuildRadius = 0,

	objectName = "@craft_armor_ingredients_n:armor_segment_enhancement_fambaa",
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

	clientObjectCRC = 409289522,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_base_armor_segment_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_enhancement_fambaa, "object/tangible/component/armor/shared_armor_segment_enhancement_fambaa.iff")

object_tangible_component_armor_shared_armor_segment_enhancement_janta = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_enhancement_janta.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/con_gen_organic_hide_lg.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_enchancement_janta",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_enhancement_janta",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_enhancement_janta",
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

	clientObjectCRC = 184239884,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_base_armor_segment_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_enhancement_janta, "object/tangible/component/armor/shared_armor_segment_enhancement_janta.iff")

object_tangible_component_armor_shared_armor_segment_enhancement_kimogila = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_enhancement_kimogila.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_enhancement_kimogila",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_enhancement_kimogila",

	noBuildRadius = 0,

	objectName = "@craft_armor_ingredients_n:armor_segment_enhancement_kimogila",
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

	clientObjectCRC = 3365812164,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_base_armor_segment_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_enhancement_kimogila, "object/tangible/component/armor/shared_armor_segment_enhancement_kimogila.iff")

object_tangible_component_armor_shared_armor_segment_enhancement_krayt = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_enhancement_krayt.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/con_gen_organic_hide_lg.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_enchancement_krayt",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_enhancement_krayt",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_enhancement_krayt",
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

	clientObjectCRC = 1719593091,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_base_armor_segment_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_enhancement_krayt, "object/tangible/component/armor/shared_armor_segment_enhancement_krayt.iff")

object_tangible_component_armor_shared_armor_segment_enhancement_nightsister = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_enhancement_nightsister.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_enchancement_nightsister",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_enhancement_krayt",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_enhancement_nightsister",
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

	clientObjectCRC = 2132900638,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_base_armor_segment_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_enhancement_nightsister, "object/tangible/component/armor/shared_armor_segment_enhancement_nightsister.iff")

object_tangible_component_armor_shared_armor_segment_enhancement_rancor = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_enhancement_rancor.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/con_gen_organic_hide_lg.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_enchancement_rancor",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_enhancement_rancor",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_enhancement_rancor",
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

	clientObjectCRC = 1147665676,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_base_armor_segment_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_enhancement_rancor, "object/tangible/component/armor/shared_armor_segment_enhancement_rancor.iff")

object_tangible_component_armor_shared_armor_segment_enhancement_sharnaff = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_enhancement_sharnaff.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_enhancement_sharnaff",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_enhancement_sharnaff",

	noBuildRadius = 0,

	objectName = "@craft_armor_ingredients_n:armor_segment_enhancement_sharnaff",
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

	clientObjectCRC = 604719765,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_base_armor_segment_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_enhancement_sharnaff, "object/tangible/component/armor/shared_armor_segment_enhancement_sharnaff.iff")

object_tangible_component_armor_shared_armor_segment_enhancement_voritor_lizard = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_enhancement_voritor_lizard.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_enhancement_voritor_lizard",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_enhancement_voritor_lizard",

	noBuildRadius = 0,

	objectName = "@craft_armor_ingredients_n:armor_segment_enhancement_voritor_lizard",
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

	clientObjectCRC = 2169359198,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_base_armor_segment_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_enhancement_voritor_lizard, "object/tangible/component/armor/shared_armor_segment_enhancement_voritor_lizard.iff")

object_tangible_component_armor_shared_armor_segment_kashyyykian_black_mtn = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_kashyyykian_black_mtn.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_clothing_ingredients_d:armor_segment_kashyyykian_black_mtn",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_kashyyykian_black_mtn",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_kashyyykian_black_mtn",
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

	clientObjectCRC = 923046063,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_kashyyykian_black_mtn, "object/tangible/component/armor/shared_armor_segment_kashyyykian_black_mtn.iff")

object_tangible_component_armor_shared_armor_segment_kashyyykian_black_mtn_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_kashyyykian_black_mtn_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_clothing_ingredients_d:armor_segment_kashyyykian_black_mtn_advanced",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_kashyyykian_black_mtn_advanced",
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

	clientObjectCRC = 4080254682,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_kashyyykian_black_mtn.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_kashyyykian_black_mtn_advanced, "object/tangible/component/armor/shared_armor_segment_kashyyykian_black_mtn_advanced.iff")

object_tangible_component_armor_shared_armor_segment_kashyyykian_ceremonial = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_kashyyykian_ceremonial.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_clothing_ingredients_d:armor_segment_kashyyykian_ceremonial",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_kashyyykian_ceremonial",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_kashyyykian_ceremonial",
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

	clientObjectCRC = 3045138551,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_kashyyykian_ceremonial, "object/tangible/component/armor/shared_armor_segment_kashyyykian_ceremonial.iff")

object_tangible_component_armor_shared_armor_segment_kashyyykian_ceremonial_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_kashyyykian_ceremonial_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_clothing_ingredients_d:armor_segment_kashyyykian_ceremonial_advanced",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_kashyyykian_ceremonial_advanced",
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

	clientObjectCRC = 2163584319,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_kashyyykian_ceremonial.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_kashyyykian_ceremonial_advanced, "object/tangible/component/armor/shared_armor_segment_kashyyykian_ceremonial_advanced.iff")

object_tangible_component_armor_shared_armor_segment_kashyyykian_hunting = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_kashyyykian_hunting.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_clothing_ingredients_d:armor_segment_kashyyykian_hunting",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_kashyyykian_hunting",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_kashyyykian_hunting",
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

	clientObjectCRC = 3253647713,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_kashyyykian_hunting, "object/tangible/component/armor/shared_armor_segment_kashyyykian_hunting.iff")

object_tangible_component_armor_shared_armor_segment_kashyyykian_hunting_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_kashyyykian_hunting_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_clothing_ingredients_d:armor_segment_kashyyykian_hunting_advanced",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_kashyyykian_hunting_advanced",
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

	clientObjectCRC = 2762649224,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_kashyyykian_hunting.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_kashyyykian_hunting_advanced, "object/tangible/component/armor/shared_armor_segment_kashyyykian_hunting_advanced.iff")

object_tangible_component_armor_shared_armor_segment_padded = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_padded.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_clothing_ingredients_d:armor_segment_padded",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_padded",
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

	clientObjectCRC = 1728449296,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_padded, "object/tangible/component/armor/shared_armor_segment_padded.iff")

object_tangible_component_armor_shared_armor_segment_padded_acklay = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_padded_acklay.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_clothing_ingredients_d:armor_segment_padded_acklay",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_padded_acklay",
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

	clientObjectCRC = 962320502,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_padded.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_padded_acklay, "object/tangible/component/armor/shared_armor_segment_padded_acklay.iff")

object_tangible_component_armor_shared_armor_segment_padded_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_padded_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_clothing_ingredients_d:armor_segment_padded_advanced",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_padded_advanced",
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

	clientObjectCRC = 3071514894,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_padded.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_padded_advanced, "object/tangible/component/armor/shared_armor_segment_padded_advanced.iff")

object_tangible_component_armor_shared_armor_segment_padded_dune_lizard = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_padded_dune_lizard.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_padded_dune_lizard",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_padded_dune_lizard",

	noBuildRadius = 0,

	objectName = "@craft_armor_ingredients_n:armor_segment_padded_dune_lizard",
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

	clientObjectCRC = 2051360405,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_padded.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_padded_dune_lizard, "object/tangible/component/armor/shared_armor_segment_padded_dune_lizard.iff")

object_tangible_component_armor_shared_armor_segment_padded_fambaa = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_padded_fambaa.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_padded_fambaa",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_padded_fambaa",

	noBuildRadius = 0,

	objectName = "@craft_armor_ingredients_n:armor_segment_padded_fambaa",
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

	clientObjectCRC = 2619219671,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_padded.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_padded_fambaa, "object/tangible/component/armor/shared_armor_segment_padded_fambaa.iff")

object_tangible_component_armor_shared_armor_segment_padded_rancor = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_padded_rancor.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_padded_rancor",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_padded_rancor",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_padded_rancor",
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

	clientObjectCRC = 3223101673,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_padded.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_padded_rancor, "object/tangible/component/armor/shared_armor_segment_padded_rancor.iff")

object_tangible_component_armor_shared_armor_segment_ris = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_ris.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_ris",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_ris",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_ris",
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

	clientObjectCRC = 1466801045,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_ris, "object/tangible/component/armor/shared_armor_segment_ris.iff")

object_tangible_component_armor_shared_armor_segment_ris_acklay = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_ris_acklay.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_ris_acklay",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_ris_acklay",

	noBuildRadius = 0,

	objectName = "@craft_armor_ingredients_n:armor_segment_ris_acklay",
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

	clientObjectCRC = 3553286313,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_ris.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_ris_acklay, "object/tangible/component/armor/shared_armor_segment_ris_acklay.iff")

object_tangible_component_armor_shared_armor_segment_ubese = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_ubese.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_ubese",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_ubese",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_ubese",
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

	clientObjectCRC = 2314491777,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_ubese, "object/tangible/component/armor/shared_armor_segment_ubese.iff")

object_tangible_component_armor_shared_armor_segment_ubese_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_ubese_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_ubese_advanced",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_ubese",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_ubese_advanced",
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

	clientObjectCRC = 1032868484,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_ubese.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_ubese_advanced, "object/tangible/component/armor/shared_armor_segment_ubese_advanced.iff")

object_tangible_component_armor_shared_armor_segment_zam = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_zam.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_zam",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_zam",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_zam",
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

	clientObjectCRC = 2378288672,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_zam, "object/tangible/component/armor/shared_armor_segment_zam.iff")

object_tangible_component_armor_shared_armor_segment_zam_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_armor_segment_zam_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_zam_advanced",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_zam",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_zam_advanced",
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

	clientObjectCRC = 452144726,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_armor_segment_zam.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_armor_segment_zam_advanced, "object/tangible/component/armor/shared_armor_segment_zam_advanced.iff")

object_tangible_component_armor_shared_base_armor_segment_enhancement = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_base_armor_segment_enhancement.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_segment.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:armor_segment_enchancement",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:armor_segment_enhancement",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:armor_segment_enhancement",
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

	clientObjectCRC = 524566894,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_base_armor_segment_enhancement, "object/tangible/component/armor/shared_base_armor_segment_enhancement.iff")

object_tangible_component_armor_shared_bone_fragment_woolamander_harrower = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_bone_fragment_woolamander_harrower.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/con_gen_organic_hide_lg.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:bone_fragment_woolamander_harrower",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:bone_fragment_woolamander_harrower",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:bone_fragment_woolamander_harrower",
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

	clientObjectCRC = 4007249575,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_bone_fragment_woolamander_harrower, "object/tangible/component/armor/shared_bone_fragment_woolamander_harrower.iff")

object_tangible_component_armor_shared_deflector_shield_emitter_assembly = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_deflector_shield_emitter_assembly.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_shield_generator.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:deflector_shield_emitter_assembly",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:deflector_shield_emitter_assembly",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:deflector_shield_emitter_assembly",
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

	clientObjectCRC = 3438496009,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_deflector_shield_emitter_assembly, "object/tangible/component/armor/shared_deflector_shield_emitter_assembly.iff")

object_tangible_component_armor_shared_deflector_shield_generator_energy_ray = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_deflector_shield_generator_energy_ray.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_shield_generator.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:deflector_shield_generator_energy_ray",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:deflector_shield_generator_energy_ray",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:deflector_shield_generator_energy_ray",
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

	clientObjectCRC = 1857960052,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_deflector_shield_generator_energy_ray, "object/tangible/component/armor/shared_deflector_shield_generator_energy_ray.iff")

object_tangible_component_armor_shared_deflector_shield_generator_particle = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_deflector_shield_generator_particle.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_shield_generator.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:deflector_shield_generator_particle",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:deflector_shield_generator_particle",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:deflector_shield_generator_particle",
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

	clientObjectCRC = 2738138651,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_deflector_shield_generator_particle, "object/tangible/component/armor/shared_deflector_shield_generator_particle.iff")

object_tangible_component_armor_shared_deflector_shield_ion_feed_unit = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_deflector_shield_ion_feed_unit.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_shield_generator.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:deflector_shield_ion_feed_unit",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:deflector_shield_ion_feed_unit",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:deflector_shield_ion_feed_unit",
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

	clientObjectCRC = 2607341358,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_deflector_shield_ion_feed_unit, "object/tangible/component/armor/shared_deflector_shield_ion_feed_unit.iff")

object_tangible_component_armor_shared_deflector_shield_overload_discharge_unit = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_deflector_shield_overload_discharge_unit.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_shield_generator.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:deflector_shield_overload_discharge_unit",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:deflector_shield_overload_discharge_unit",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:deflector_shield_overload_discharge_unit",
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

	clientObjectCRC = 2649973177,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_deflector_shield_overload_discharge_unit, "object/tangible/component/armor/shared_deflector_shield_overload_discharge_unit.iff")

object_tangible_component_armor_shared_deflector_shield_projector_plate = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_deflector_shield_projector_plate.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_shield_generator.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:deflector_shield_projector_plate",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:deflector_shield_projector_plate",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:deflector_shield_projector_plate",
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

	clientObjectCRC = 2995769746,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_deflector_shield_projector_plate, "object/tangible/component/armor/shared_deflector_shield_projector_plate.iff")

object_tangible_component_armor_shared_feather_peko_albatross = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_feather_peko_albatross.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/con_gen_organic_hide_lg.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:feather_peko_albatross",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:feather_peko_albatross",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:feather_peko_albatross",
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

	clientObjectCRC = 2381585751,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_feather_peko_albatross, "object/tangible/component/armor/shared_feather_peko_albatross.iff")

object_tangible_component_armor_shared_heavy_armor_layer = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_heavy_armor_layer.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:heavy_armor_layer",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:heavy_armor_layer",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:heavy_armor_layer",
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

	clientObjectCRC = 3619749395,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_heavy_armor_layer, "object/tangible/component/armor/shared_heavy_armor_layer.iff")

object_tangible_component_armor_shared_heavy_armor_layer_acid = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_heavy_armor_layer_acid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:heavy_armor_layer_acid",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:heavy_armor_layer_acid",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:heavy_armor_layer_acid",
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

	clientObjectCRC = 1874541769,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_heavy_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_heavy_armor_layer_acid, "object/tangible/component/armor/shared_heavy_armor_layer_acid.iff")

object_tangible_component_armor_shared_heavy_armor_layer_blast = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_heavy_armor_layer_blast.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:heavy_armor_layer_blast",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:heavy_armor_layer_blast",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:heavy_armor_layer_blast",
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

	clientObjectCRC = 2097043394,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_heavy_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_heavy_armor_layer_blast, "object/tangible/component/armor/shared_heavy_armor_layer_blast.iff")

object_tangible_component_armor_shared_heavy_armor_layer_cold = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_heavy_armor_layer_cold.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:heavy_armor_layer_cold",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:heavy_armor_layer_cold",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:heavy_armor_layer_cold",
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

	clientObjectCRC = 3855973328,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_heavy_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_heavy_armor_layer_cold, "object/tangible/component/armor/shared_heavy_armor_layer_cold.iff")

object_tangible_component_armor_shared_heavy_armor_layer_electrical = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_heavy_armor_layer_electrical.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:heavy_armor_layer_electrical",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:heavy_armor_layer_electrical",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:heavy_armor_layer_electrical",
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

	clientObjectCRC = 2909170926,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_heavy_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_heavy_armor_layer_electrical, "object/tangible/component/armor/shared_heavy_armor_layer_electrical.iff")

object_tangible_component_armor_shared_heavy_armor_layer_energy = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_heavy_armor_layer_energy.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:heavy_armor_layer_energy",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:heavy_armor_layer_energy",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:heavy_armor_layer_energy",
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

	clientObjectCRC = 1153905054,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_heavy_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_heavy_armor_layer_energy, "object/tangible/component/armor/shared_heavy_armor_layer_energy.iff")

object_tangible_component_armor_shared_heavy_armor_layer_environmental = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_heavy_armor_layer_environmental.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:heavy_armor_layer_environmental",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:heavy_armor_layer_environmental",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:heavy_armor_layer_environmental",
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

	clientObjectCRC = 1639844661,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_heavy_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_heavy_armor_layer_environmental, "object/tangible/component/armor/shared_heavy_armor_layer_environmental.iff")

object_tangible_component_armor_shared_heavy_armor_layer_heat = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_heavy_armor_layer_heat.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:heavy_armor_layer_heat",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:heavy_armor_layer_heat",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:heavy_armor_layer_heat",
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

	clientObjectCRC = 490091808,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_heavy_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_heavy_armor_layer_heat, "object/tangible/component/armor/shared_heavy_armor_layer_heat.iff")

object_tangible_component_armor_shared_heavy_armor_layer_kinetic = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_heavy_armor_layer_kinetic.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:heavy_armor_layer_kinetic",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:heavy_armor_layer_kinetic",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:heavy_armor_layer_kinetic",
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

	clientObjectCRC = 2016162937,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_heavy_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_heavy_armor_layer_kinetic, "object/tangible/component/armor/shared_heavy_armor_layer_kinetic.iff")

object_tangible_component_armor_shared_heavy_armor_layer_restraint = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_heavy_armor_layer_restraint.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:heavy_armor_layer_restraint",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:heavy_armor_layer_restraint",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:heavy_armor_layer_restraint",
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

	clientObjectCRC = 34964498,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_heavy_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_heavy_armor_layer_restraint, "object/tangible/component/armor/shared_heavy_armor_layer_restraint.iff")

object_tangible_component_armor_shared_heavy_armor_layer_stun = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_heavy_armor_layer_stun.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_armor_layer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:heavy_armor_layer_stun",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:heavy_armor_layer_stun",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:heavy_armor_layer_stun",
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

	clientObjectCRC = 2875559057,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/armor/shared_heavy_armor_layer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_heavy_armor_layer_stun, "object/tangible/component/armor/shared_heavy_armor_layer_stun.iff")

object_tangible_component_armor_shared_hide_gurk_king = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_hide_gurk_king.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/con_gen_organic_hide_lg.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:hide_gurk_king",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:hide_gurk_king",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:hide_gurk_king",
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

	clientObjectCRC = 605934535,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_hide_gurk_king, "object/tangible/component/armor/shared_hide_gurk_king.iff")

object_tangible_component_armor_shared_scale_giant_dune_kimogila = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_scale_giant_dune_kimogila.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/con_gen_organic_hide_lg.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:scale_giant_dune_kimogila",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:scale_giant_dune_kimogila",
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

	clientObjectCRC = 3177620881,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_scale_giant_dune_kimogila, "object/tangible/component/armor/shared_scale_giant_dune_kimogila.iff")

object_tangible_component_armor_shared_shield_generator_facility = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_shield_generator_facility.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_shield_generator.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:shield_generator_facility",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:shield_generator_facility",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:shield_generator_facility",
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

	clientObjectCRC = 3129011017,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_shield_generator_facility, "object/tangible/component/armor/shared_shield_generator_facility.iff")

object_tangible_component_armor_shared_shield_generator_personal = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_shield_generator_personal.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_shield_generator.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/belt.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 264,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:shield_generator_personal",

	gameObjectType = 264,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:shield_generator_personal",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:shield_generator_personal",
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

	clientObjectCRC = 3357133395,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_belt.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_shield_generator_personal, "object/tangible/component/armor/shared_shield_generator_personal.iff")

object_tangible_component_armor_shared_shield_generator_personal_b = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_shield_generator_personal_b.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_shield_generator.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/belt.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 264,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:shield_generator_personal_b",

	gameObjectType = 264,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:shield_generator_personal_b",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:shield_generator_personal_b",
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

	clientObjectCRC = 2352410837,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_belt.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_shield_generator_personal_b, "object/tangible/component/armor/shared_shield_generator_personal_b.iff")

object_tangible_component_armor_shared_shield_generator_personal_c = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_shield_generator_personal_c.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_shield_generator.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/belt.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 264,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:shield_generator_personal_c",

	gameObjectType = 264,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:shield_generator_personal_c",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:shield_generator_personal_c",
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

	clientObjectCRC = 3309016920,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_belt.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_shield_generator_personal_c, "object/tangible/component/armor/shared_shield_generator_personal_c.iff")

object_tangible_component_armor_shared_shield_generator_personal_imperial_test = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_shield_generator_personal_imperial_test.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_shield_generator.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/belt.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 264,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:shield_generator_personal_imperial_test",

	gameObjectType = 264,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:shield_generator_personal_imperial_test",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:shield_generator_personal_imperial_test",
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

	clientObjectCRC = 1034696189,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_belt.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_shield_generator_personal_imperial_test, "object/tangible/component/armor/shared_shield_generator_personal_imperial_test.iff")

object_tangible_component_armor_shared_shield_generator_vehicular = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/armor/shared_shield_generator_vehicular.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_shield_generator.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262145,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_armor_ingredients_d:shield_generator_vehicular",

	gameObjectType = 262145,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:shield_generator_vehicular",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:shield_generator_vehicular",
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

	clientObjectCRC = 4081974766,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_armor_shared_shield_generator_vehicular, "object/tangible/component/armor/shared_shield_generator_vehicular.iff")
