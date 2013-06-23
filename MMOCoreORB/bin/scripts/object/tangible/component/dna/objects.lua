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


object_tangible_component_dna_shared_dna_sample_above_average = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_sample_above_average.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_sample.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_dna_components_d:above_average_quality_dna",

	gameObjectType = 262155,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:above_average_quality_dna",
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

	clientObjectCRC = 3272908463,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_dna_sample.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_sample_above_average, "object/tangible/component/dna/shared_dna_sample_above_average.iff")

object_tangible_component_dna_shared_dna_sample_average = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_sample_average.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_sample.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_dna_components_d:average_quality_dna",

	gameObjectType = 262155,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:average_quality_dna",
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

	clientObjectCRC = 2524715920,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_dna_sample.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_sample_average, "object/tangible/component/dna/shared_dna_sample_average.iff")

object_tangible_component_dna_shared_dna_sample_below_average = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_sample_below_average.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_sample.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_dna_components_d:below_average_quality_dna",

	gameObjectType = 262155,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:below_average_quality_dna",
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

	clientObjectCRC = 675784259,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_dna_sample.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_sample_below_average, "object/tangible/component/dna/shared_dna_sample_below_average.iff")

object_tangible_component_dna_shared_dna_sample_high = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_sample_high.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_sample.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_dna_components_d:high_quality_dna",

	gameObjectType = 262155,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:high_quality_dna",
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

	clientObjectCRC = 3034626514,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_dna_sample.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_sample_high, "object/tangible/component/dna/shared_dna_sample_high.iff")

object_tangible_component_dna_shared_dna_sample_low = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_sample_low.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_sample.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_dna_components_d:low_quality_dna",

	gameObjectType = 262155,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:low_quality_dna",
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

	clientObjectCRC = 2579345010,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_dna_sample.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_sample_low, "object/tangible/component/dna/shared_dna_sample_low.iff")

object_tangible_component_dna_shared_dna_sample_very_high = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_sample_very_high.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_sample.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_dna_components_d:very_high_quality_dna",

	gameObjectType = 262155,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:very_high_quality_dna",
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

	clientObjectCRC = 299885620,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_dna_sample.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_sample_very_high, "object/tangible/component/dna/shared_dna_sample_very_high.iff")

object_tangible_component_dna_shared_dna_sample_very_low = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_sample_very_low.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_sample.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_dna_components_d:very_low_quality_dna",

	gameObjectType = 262155,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:very_low_quality_dna",
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

	clientObjectCRC = 1076609940,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_dna_sample.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_sample_very_low, "object/tangible/component/dna/shared_dna_sample_very_low.iff")

object_tangible_component_dna_shared_dna_template_angler = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_angler.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_angler",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_angler",
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

	clientObjectCRC = 461916189,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_angler, "object/tangible/component/dna/shared_dna_template_angler.iff")

object_tangible_component_dna_shared_dna_template_bantha = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_bantha.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_bantha",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_bantha",
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

	clientObjectCRC = 726704759,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_bantha, "object/tangible/component/dna/shared_dna_template_bantha.iff")

object_tangible_component_dna_shared_dna_template_bearded_jax = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_bearded_jax.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_bearded_jax",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_bearded_jax",
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

	clientObjectCRC = 727178963,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_bearded_jax, "object/tangible/component/dna/shared_dna_template_bearded_jax.iff")

object_tangible_component_dna_shared_dna_template_blurrg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_blurrg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_blurrg",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_blurrg",
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

	clientObjectCRC = 1265107329,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_blurrg, "object/tangible/component/dna/shared_dna_template_blurrg.iff")

object_tangible_component_dna_shared_dna_template_bol = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_bol.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_bol",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_bol",
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

	clientObjectCRC = 706373854,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_bol, "object/tangible/component/dna/shared_dna_template_bol.iff")

object_tangible_component_dna_shared_dna_template_bolle_bol = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_bolle_bol.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_bolle_bol",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_bolle_bol",
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

	clientObjectCRC = 214227430,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_bolle_bol, "object/tangible/component/dna/shared_dna_template_bolle_bol.iff")

object_tangible_component_dna_shared_dna_template_bolma = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_bolma.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_bolma",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_bolma",
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

	clientObjectCRC = 1395080056,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_bolma, "object/tangible/component/dna/shared_dna_template_bolma.iff")

object_tangible_component_dna_shared_dna_template_brackaset = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_brackaset.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_brackaset",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_brackaset",
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

	clientObjectCRC = 3633553517,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_brackaset, "object/tangible/component/dna/shared_dna_template_brackaset.iff")

object_tangible_component_dna_shared_dna_template_carrion_spat = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_carrion_spat.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_carrion_spat",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_carrion_spat",
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

	clientObjectCRC = 1875152726,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_carrion_spat, "object/tangible/component/dna/shared_dna_template_carrion_spat.iff")

object_tangible_component_dna_shared_dna_template_choku = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_choku.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_choku",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_choku",
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

	clientObjectCRC = 262963315,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_choku, "object/tangible/component/dna/shared_dna_template_choku.iff")

object_tangible_component_dna_shared_dna_template_dalyrake = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_dalyrake.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_dalyrake",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_dalyrake",
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

	clientObjectCRC = 1214055048,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_dalyrake, "object/tangible/component/dna/shared_dna_template_dalyrake.iff")

object_tangible_component_dna_shared_dna_template_dewback = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_dewback.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_dewback",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_dewback",
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

	clientObjectCRC = 1144992157,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_dewback, "object/tangible/component/dna/shared_dna_template_dewback.iff")

object_tangible_component_dna_shared_dna_template_eopie = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_eopie.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_eopie",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_eopie",
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

	clientObjectCRC = 1680199838,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_eopie, "object/tangible/component/dna/shared_dna_template_eopie.iff")

object_tangible_component_dna_shared_dna_template_falumpaset = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_falumpaset.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_falumpaset",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_falumpaset",
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

	clientObjectCRC = 671613943,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_falumpaset, "object/tangible/component/dna/shared_dna_template_falumpaset.iff")

object_tangible_component_dna_shared_dna_template_fambaa = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_fambaa.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_fambaa",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_fambaa",
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

	clientObjectCRC = 1331331454,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_fambaa, "object/tangible/component/dna/shared_dna_template_fambaa.iff")

object_tangible_component_dna_shared_dna_template_generic = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_generic.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_dna_components_d:dna_template_generic",

	gameObjectType = 262155,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_generic",
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

	clientObjectCRC = 836379806,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_generic, "object/tangible/component/dna/shared_dna_template_generic.iff")

object_tangible_component_dna_shared_dna_template_gualama = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_gualama.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_gualama",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_gualama",
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

	clientObjectCRC = 17241294,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_gualama, "object/tangible/component/dna/shared_dna_template_gualama.iff")

object_tangible_component_dna_shared_dna_template_guf_drolg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_guf_drolg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_guf_drolg",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_guf_drolg",
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

	clientObjectCRC = 774185499,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_guf_drolg, "object/tangible/component/dna/shared_dna_template_guf_drolg.iff")

object_tangible_component_dna_shared_dna_template_gurrcat = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_gurrcat.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_gurrcat",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_gurrcat",
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

	clientObjectCRC = 1857431024,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_gurrcat, "object/tangible/component/dna/shared_dna_template_gurrcat.iff")

object_tangible_component_dna_shared_dna_template_gurreck = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_gurreck.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_gurreck",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_gurreck",
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

	clientObjectCRC = 3322704079,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_gurreck, "object/tangible/component/dna/shared_dna_template_gurreck.iff")

object_tangible_component_dna_shared_dna_template_kaadu = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_kaadu.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_kaadu",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_kaadu",
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

	clientObjectCRC = 1112595757,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_kaadu, "object/tangible/component/dna/shared_dna_template_kaadu.iff")

object_tangible_component_dna_shared_dna_template_kahmurra = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_kahmurra.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_kahmurra",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_kahmurra",
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

	clientObjectCRC = 1394407158,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_kahmurra, "object/tangible/component/dna/shared_dna_template_kahmurra.iff")

object_tangible_component_dna_shared_dna_template_kimogila = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_kimogila.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_kimogila",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_kimogila",
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

	clientObjectCRC = 2155310796,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_kimogila, "object/tangible/component/dna/shared_dna_template_kimogila.iff")

object_tangible_component_dna_shared_dna_template_krahbu = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_krahbu.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_krahbu",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_krahbu",
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

	clientObjectCRC = 67998893,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_krahbu, "object/tangible/component/dna/shared_dna_template_krahbu.iff")

object_tangible_component_dna_shared_dna_template_kusak = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_kusak.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_kusak",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_kusak",
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

	clientObjectCRC = 4199501468,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_kusak, "object/tangible/component/dna/shared_dna_template_kusak.iff")

object_tangible_component_dna_shared_dna_template_narglatch = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_narglatch.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_narglatch",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_narglatch",
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

	clientObjectCRC = 2079919048,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_narglatch, "object/tangible/component/dna/shared_dna_template_narglatch.iff")

object_tangible_component_dna_shared_dna_template_pugoriss = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_pugoriss.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_pugoriss",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_pugoriss",
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

	clientObjectCRC = 3819931989,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_pugoriss, "object/tangible/component/dna/shared_dna_template_pugoriss.iff")

object_tangible_component_dna_shared_dna_template_rancor = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_rancor.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_rancor",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_rancor",
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

	clientObjectCRC = 324550464,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_rancor, "object/tangible/component/dna/shared_dna_template_rancor.iff")

object_tangible_component_dna_shared_dna_template_ronto = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_ronto.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_ronto",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_ronto",
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

	clientObjectCRC = 1390548887,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_ronto, "object/tangible/component/dna/shared_dna_template_ronto.iff")

object_tangible_component_dna_shared_dna_template_sand_panther = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_sand_panther.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_sand_panther",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_sand_panther",
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

	clientObjectCRC = 2605574472,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_sand_panther, "object/tangible/component/dna/shared_dna_template_sand_panther.iff")

object_tangible_component_dna_shared_dna_template_snorbal = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_snorbal.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_snorbal",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_snorbal",
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

	clientObjectCRC = 3055149098,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_snorbal, "object/tangible/component/dna/shared_dna_template_snorbal.iff")

object_tangible_component_dna_shared_dna_template_torton = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_torton.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_torton",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_torton",
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

	clientObjectCRC = 1232171307,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_torton, "object/tangible/component/dna/shared_dna_template_torton.iff")

object_tangible_component_dna_shared_dna_template_tybis = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_tybis.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_tybis",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_tybis",
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

	clientObjectCRC = 3076355230,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_tybis, "object/tangible/component/dna/shared_dna_template_tybis.iff")

object_tangible_component_dna_shared_dna_template_veermok = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_veermok.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_veermok",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_veermok",
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

	clientObjectCRC = 3141045747,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_veermok, "object/tangible/component/dna/shared_dna_template_veermok.iff")

object_tangible_component_dna_shared_dna_template_zucca_boar = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/dna/shared_dna_template_zucca_boar.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_dna_data_disc.apt",
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

	detailedDescription = "@craft_dna_components_d:dna_template_zucca_boar",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dna_component",

	noBuildRadius = 0,

	objectName = "@craft_dna_components_n:dna_template_zucca_boar",
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

	clientObjectCRC = 228699959,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_dna_shared_dna_template_zucca_boar, "object/tangible/component/dna/shared_dna_template_zucca_boar.iff")
