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


object_tangible_component_clothing_shared_cargo_pocket = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_cargo_pocket.apt",
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

	detailedDescription = "@craft_clothing_ingredients_d:cargo_pocket",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:cargo_pocket",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:cargo_pocket",
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

	clientObjectCRC = 3621976108,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_clothing_shared_cargo_pocket, "object/tangible/component/clothing/shared_cargo_pocket.iff")

object_tangible_component_clothing_shared_clasp_heavy_duty = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_acc_slaving_collar.apt",
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

	detailedDescription = "@craft_clothing_ingredients_d:clasp_heavy_duty",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@craft_clothing_ingredients_d:clasp_heavy_duty",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:clasp_heavy_duty",
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

	clientObjectCRC = 948917712,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_clothing_shared_clasp_heavy_duty, "object/tangible/component/clothing/shared_clasp_heavy_duty.iff")

object_tangible_component_clothing_shared_clothing_treatment_crystalline = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_clothing_treatment_crystalline.apt",
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

	detailedDescription = "@craft_clothing_ingredients_d:clothing_treatment_crystalline",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@craft_clothing_ingredients_d:clothing_treatment_crystalline",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:clothing_treatment_crystalline",
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

	clientObjectCRC = 1281925235,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_clothing_shared_clothing_treatment_crystalline, "object/tangible/component/clothing/shared_clothing_treatment_crystalline.iff")

object_tangible_component_clothing_shared_component_base = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_dye_generic.apt",
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

	detailedDescription = "@craft_clothing_ingredients_d:component_base",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:component_base",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:component_base",
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

	clientObjectCRC = 347363744,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_clothing_shared_component_base, "object/tangible/component/clothing/shared_component_base.iff")

object_tangible_component_clothing_shared_fiberplast_panel = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_synthetic_cloth.apt",
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

	detailedDescription = "@craft_clothing_ingredients_d:fiberplast_panel",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:fiberplast_panel",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:fiberplast_panel",
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

	clientObjectCRC = 967991397,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_clothing_shared_fiberplast_panel, "object/tangible/component/clothing/shared_fiberplast_panel.iff")

object_tangible_component_clothing_shared_jewelry_setting = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_jewelry_setting.apt",
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

	detailedDescription = "@craft_clothing_ingredients_d:jewelry_setting",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@craft_clothing_ingredients_d:jewelry_setting",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:jewelry_setting",
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

	clientObjectCRC = 3580972841,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_clothing_shared_jewelry_setting, "object/tangible/component/clothing/shared_jewelry_setting.iff")

object_tangible_component_clothing_shared_leather_heavy_duty = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_synthetic_cloth.apt",
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

	detailedDescription = "@craft_clothing_ingredients_d:leather_heavy_duty",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@craft_clothing_ingredients_d:leather_heavy_duty",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:leather_heavy_duty",
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

	clientObjectCRC = 2558785369,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_clothing_shared_leather_heavy_duty, "object/tangible/component/clothing/shared_leather_heavy_duty.iff")

object_tangible_component_clothing_shared_metal_fasteners = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_tool_sandstat.apt",
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

	detailedDescription = "@weapon_detail:metal_fasteners",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:metal_fasteners",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:metal_fasteners",
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

	clientObjectCRC = 1732023387,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_clothing_shared_metal_fasteners, "object/tangible/component/clothing/shared_metal_fasteners.iff")

object_tangible_component_clothing_shared_padding_segment = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_disguise_disguise_kit_s1.apt",
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

	detailedDescription = "@craft_clothing_ingredients_d:padding_segment",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@craft_clothing_ingredients_d:padding_segment",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:padding_segment",
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

	clientObjectCRC = 449019087,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_clothing_shared_padding_segment, "object/tangible/component/clothing/shared_padding_segment.iff")

object_tangible_component_clothing_shared_reinforced_fiber_panels = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_synthetic_cloth.apt",
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

	detailedDescription = "@craft_clothing_ingredients_d:reinforced_fiber_panels",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:reinforced_fiber_panels",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:reinforced_fiber_panels",
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

	clientObjectCRC = 142903413,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_clothing_shared_reinforced_fiber_panels, "object/tangible/component/clothing/shared_reinforced_fiber_panels.iff")

object_tangible_component_clothing_shared_shoe_sole = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_shoe_sole.apt",
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

	detailedDescription = "@craft_clothing_ingredients_d:shoe_sole",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@craft_clothing_ingredients_d:shoe_sole",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:shoe_sole",
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

	clientObjectCRC = 845264699,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_clothing_shared_shoe_sole, "object/tangible/component/clothing/shared_shoe_sole.iff")

object_tangible_component_clothing_shared_synthetic_cloth = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_synthetic_cloth.apt",
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

	detailedDescription = "@craft_clothing_ingredients_d:synthetic_cloth",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@craft_clothing_ingredients_d:synthetic_cloth",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:synthetic_cloth",
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

	clientObjectCRC = 2133284732,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_clothing_shared_synthetic_cloth, "object/tangible/component/clothing/shared_synthetic_cloth.iff")

object_tangible_component_clothing_shared_trim = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_trim.apt",
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

	detailedDescription = "@craft_clothing_ingredients_d:trim",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@craft_clothing_ingredients_d:trim",

	noBuildRadius = 0,

	objectName = "@craft_clothing_ingredients_n:trim",
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

	clientObjectCRC = 3684307948,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_component_clothing_shared_trim, "object/tangible/component/clothing/shared_trim.iff")
