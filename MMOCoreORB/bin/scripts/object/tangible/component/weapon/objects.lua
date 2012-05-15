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


object_tangible_component_weapon_shared_acklay_bone_reinforcement_core = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_acklay_bone_reinforcement_core.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/poi_all_skeleton_human_body.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:acklay_bone_reinforcement_core",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:acklay_bone_reinforcement_core",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:acklay_bone_reinforcement_core",
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

	clientObjectCRC = 4088226280,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_reinforcement_core.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_acklay_bone_reinforcement_core, "object/tangible/component/weapon/shared_acklay_bone_reinforcement_core.iff")

object_tangible_component_weapon_shared_base_blaster_power_handler_enhancement = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_base_blaster_power_handler_enhancement.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_blaster_power_handler.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_power_handler_enhancement",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_power_handler_enhancement",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_power_handler_enhancement",
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

	clientObjectCRC = 3003199598,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_base_blaster_power_handler_enhancement, "object/tangible/component/weapon/shared_base_blaster_power_handler_enhancement.iff")

object_tangible_component_weapon_shared_base_projectile_feed_mechanism_enhancement = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_base_projectile_feed_mechanism_enhancement.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_projectile_feed_mechanism.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:projectile_feed_mechanism_enhancement",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:projectile_feed_mechanism_enhancement",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:projectile_feed_mechanism_enhancement",
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

	clientObjectCRC = 2928380904,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_base_projectile_feed_mechanism_enhancement, "object/tangible/component/weapon/shared_base_projectile_feed_mechanism_enhancement.iff")

object_tangible_component_weapon_shared_base_vibro_unit_enhancement = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_base_vibro_unit_enhancement.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_blade_vibro_unit.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blade_vibro_unit_enhancement",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blade_vibro_unit_enhancement",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blade_vibro_unit_enhancement",
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

	clientObjectCRC = 1563728747,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_base_vibro_unit_enhancement, "object/tangible/component/weapon/shared_base_vibro_unit_enhancement.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s01 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_l_t1",
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

	clientObjectCRC = 1710329756,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s01, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s01.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s01_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s01_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_l_t1",
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

	clientObjectCRC = 2092661773,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s01_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s01_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s02 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s02.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_l_t2",
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

	clientObjectCRC = 3202754315,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s02, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s02.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s02_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s02_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_l_t2",
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

	clientObjectCRC = 2421758291,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s02_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s02_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s03 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s03.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s03.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_l_t3",
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

	clientObjectCRC = 4159389830,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s03, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s03.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s03_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s03_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s03.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_l_t3",
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

	clientObjectCRC = 3422078361,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s03_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s03_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s04 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s04.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s04.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_l_t4",
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

	clientObjectCRC = 201878418,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s04, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s04.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s04_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s04_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s04.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_l_t4",
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

	clientObjectCRC = 1297927768,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s04_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s04_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s05 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s05.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s05.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_l_t5",
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

	clientObjectCRC = 1157958687,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s05, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s05.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s05_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s05_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s05.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_l_t5",
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

	clientObjectCRC = 385684114,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s05_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s05_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s06 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s06.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s06.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_l_t6",
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

	clientObjectCRC = 2652021896,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s06, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s06.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s06_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s06_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s06.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_l_t6",
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

	clientObjectCRC = 4196366284,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s06_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s06_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s07 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s07.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s07.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_l_t7",
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

	clientObjectCRC = 3609182981,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s07, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s07.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s07_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s07_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s07.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_l_t7",
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

	clientObjectCRC = 2713627398,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_lg_s07_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_lg_s07_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s01 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_m_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_m_t1",
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

	clientObjectCRC = 4222005055,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s01, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s01.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s01_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s01_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_m_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_m_t1",
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

	clientObjectCRC = 3666495250,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s01_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s01_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s02 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s02.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_m_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_m_t2",
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

	clientObjectCRC = 548472744,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s02, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s02.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s02_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s02_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_m_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_m_t2",
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

	clientObjectCRC = 912794188,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s02_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s02_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s03 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s03.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_m_s03.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_m_t3",
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

	clientObjectCRC = 1773953061,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s03, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s03.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s03_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s03_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_m_s03.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_m_t3",
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

	clientObjectCRC = 1841954438,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s03_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s03_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s04 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s04.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_m_s04.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_m_t4",
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

	clientObjectCRC = 2455718705,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s04, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s04.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s04_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s04_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_m_s04.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_m_t4",
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

	clientObjectCRC = 3949851975,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s04_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s04_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s05 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s05.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_m_s05.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_m_t5",
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

	clientObjectCRC = 3679595708,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s05, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s05.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s05_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s05_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_m_s05.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_m_t5",
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

	clientObjectCRC = 2966169997,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s05_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s05_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s06 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s06.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_m_s06.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_m_t6",
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

	clientObjectCRC = 4555819,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s06, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s06.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s06_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s06_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_m_s06.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_m_t6",
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

	clientObjectCRC = 1546538195,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s06_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s06_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s07 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s07.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_m_s07.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_m_t7",
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

	clientObjectCRC = 1229513638,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s07, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s07.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s07_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s07_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_m_s07.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_m_t7",
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

	clientObjectCRC = 126849049,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_m_s07_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_m_s07_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s01 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_sm_t1",
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

	clientObjectCRC = 3175095314,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s01, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s01.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s01_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s01_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_sm_t1",
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

	clientObjectCRC = 867179315,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s01_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s01_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s02 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s02.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_sm_t2",
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

	clientObjectCRC = 1717023877,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s02, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s02.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s02_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s02_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_sm_t2",
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

	clientObjectCRC = 3746725485,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s02_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s02_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s03 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s03.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s03.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_sm_t3",
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

	clientObjectCRC = 794481416,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s03, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s03.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s03_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s03_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s03.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_sm_t3",
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

	clientObjectCRC = 2230559399,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s03_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s03_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s04 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s04.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s04.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_sm_t4",
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

	clientObjectCRC = 3568957468,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s04, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s04.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s04_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s04_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s04.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_sm_t4",
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

	clientObjectCRC = 39299430,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s04_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s04_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s05 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s05.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s05.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_sm_t5",
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

	clientObjectCRC = 2645860241,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s05, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s05.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s05_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s05_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s05.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_sm_t5",
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

	clientObjectCRC = 1509324204,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s05_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s05_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s06 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s06.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s06.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_sm_t6",
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

	clientObjectCRC = 1185101574,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s06, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s06.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s06_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s06_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s06.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_sm_t6",
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

	clientObjectCRC = 3037991154,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s06_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s06_lg.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s07 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s07.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s07.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_sm_t7",
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

	clientObjectCRC = 263082123,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s07, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s07.iff")

object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s07_lg = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s07_lg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s07.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_barrel_sm_t7",
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

	clientObjectCRC = 4004891704,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_barrel_wp_muzzle_sm_s07_lg, "object/tangible/component/weapon/shared_blaster_barrel_wp_muzzle_sm_s07_lg.iff")

object_tangible_component_weapon_shared_blaster_pistol_barrel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_pistol_barrel",
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

	clientObjectCRC = 3001062270,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_pistol_barrel, "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff")

object_tangible_component_weapon_shared_blaster_pistol_barrel_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_pistol_barrel_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel_advanced",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel_advanced",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_pistol_barrel_advanced",
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

	clientObjectCRC = 4250066631,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_pistol_barrel_advanced, "object/tangible/component/weapon/shared_blaster_pistol_barrel_advanced.iff")

object_tangible_component_weapon_shared_blaster_pistol_barrel_quest = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_pistol_barrel_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_pistol_barrel_quest",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_pistol_barrel_advanced",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_pistol_barrel_quest",
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

	clientObjectCRC = 2263958541,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel.iff", "object/tangible/component/weapon/shared_blaster_pistol_barrel_advanced.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_pistol_barrel_quest, "object/tangible/component/weapon/shared_blaster_pistol_barrel_quest.iff")

object_tangible_component_weapon_shared_blaster_power_handler = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_power_handler.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_blaster_power_handler.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_power_handler",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_power_handler",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_power_handler",
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

	clientObjectCRC = 3399297408,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_power_handler, "object/tangible/component/weapon/shared_blaster_power_handler.iff")

object_tangible_component_weapon_shared_blaster_power_handler_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_power_handler_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_blaster_power_handler.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_power_handler_advanced",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_power_handler_advanced",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_power_handler_advanced",
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

	clientObjectCRC = 1426378303,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_power_handler.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_power_handler_advanced, "object/tangible/component/weapon/shared_blaster_power_handler_advanced.iff")

object_tangible_component_weapon_shared_blaster_power_handler_enhancement_durability = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_power_handler_enhancement_durability.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_blaster_power_handler.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_power_handler_enhancement_durability",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_power_handler_enhancement_durability",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_power_handler_enhancement_durability",
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

	clientObjectCRC = 1717492287,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_base_blaster_power_handler_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_power_handler_enhancement_durability, "object/tangible/component/weapon/shared_blaster_power_handler_enhancement_durability.iff")

object_tangible_component_weapon_shared_blaster_power_handler_enhancement_krayt = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_power_handler_enhancement_krayt.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/edb_con_tato_jar_guts_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_power_handler_enhancement_krayt",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_power_handler_enhancement_krayt",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_power_handler_enhancement_krayt",
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

	clientObjectCRC = 3981194570,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_base_blaster_power_handler_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_power_handler_enhancement_krayt, "object/tangible/component/weapon/shared_blaster_power_handler_enhancement_krayt.iff")

object_tangible_component_weapon_shared_blaster_power_handler_enhancement_max_damage = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_power_handler_enhancement_max_damage.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_blaster_power_handler.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_power_handler_enhancement_max_damage",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_power_handler_enhancement_max_damage",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_power_handler_enhancement_max_damage",
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

	clientObjectCRC = 3285791160,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_base_blaster_power_handler_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_power_handler_enhancement_max_damage, "object/tangible/component/weapon/shared_blaster_power_handler_enhancement_max_damage.iff")

object_tangible_component_weapon_shared_blaster_power_handler_enhancement_min_damage = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_power_handler_enhancement_min_damage.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_blaster_power_handler.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_power_handler_enhancement_min_damage",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_power_handler_enhancement_min_damage",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_power_handler_enhancement_min_damage",
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

	clientObjectCRC = 4158958561,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_base_blaster_power_handler_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_power_handler_enhancement_min_damage, "object/tangible/component/weapon/shared_blaster_power_handler_enhancement_min_damage.iff")

object_tangible_component_weapon_shared_blaster_power_handler_quest = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_power_handler_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_blaster_power_handler.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_power_handler_quest",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_power_handler_advanced",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_power_handler_quest",
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

	clientObjectCRC = 3074802434,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_power_handler.iff", "object/tangible/component/weapon/shared_blaster_power_handler_advanced.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_power_handler_quest, "object/tangible/component/weapon/shared_blaster_power_handler_quest.iff")

object_tangible_component_weapon_shared_blaster_rifle_barrel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s04.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_rifle_barrel",
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

	clientObjectCRC = 260681278,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_rifle_barrel, "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff")

object_tangible_component_weapon_shared_blaster_rifle_barrel_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_blaster_rifle_barrel_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s04.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blaster_rifle_barrel_advanced",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blaster_rifle_barrel_advanced",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blaster_rifle_barrel_advanced",
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

	clientObjectCRC = 992626072,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_blaster_rifle_barrel_advanced, "object/tangible/component/weapon/shared_blaster_rifle_barrel_advanced.iff")

object_tangible_component_weapon_shared_chemical_dispersion_mechanism = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_chemical_dispersion_mechanism.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_chemical_dispersion.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:chemical_dispersion_mechanism",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:chemical_dispersion_mechanism",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:chemical_dispersion_mechanism",
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

	clientObjectCRC = 1194049951,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_chemical_dispersion_mechanism, "object/tangible/component/weapon/shared_chemical_dispersion_mechanism.iff")

object_tangible_component_weapon_shared_chemical_dispersion_mechanism_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_chemical_dispersion_mechanism_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_chemical_dispersion.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:chemical_dispersion_mechanism_advanced",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:chemical_dispersion_mechanism_advanced",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:chemical_dispersion_mechanism_advanced",
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

	clientObjectCRC = 1411275981,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_chemical_dispersion_mechanism.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_chemical_dispersion_mechanism_advanced, "object/tangible/component/weapon/shared_chemical_dispersion_mechanism_advanced.iff")

object_tangible_component_weapon_shared_corvette_rifle_barrel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_corvette_rifle_barrel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:corvette_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:corvette_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:corvette_rifle_barrel",
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

	clientObjectCRC = 3758372574,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_blaster_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_corvette_rifle_barrel, "object/tangible/component/weapon/shared_corvette_rifle_barrel.iff")

object_tangible_component_weapon_shared_energization_crystals = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_energization_crystals.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_electronic_module_simple.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:energization_crystals",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:energization_crystals",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:energization_crystals",
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

	clientObjectCRC = 491130592,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_energization_crystals, "object/tangible/component/weapon/shared_energization_crystals.iff")

object_tangible_component_weapon_shared_galven_tube_circuits = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_galven_tube_circuits.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_electronic_module_simple.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:galven_tube_circuits",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:galven_tube_circuits",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:galven_tube_circuits",
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

	clientObjectCRC = 4061079973,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_galven_tube_circuits, "object/tangible/component/weapon/shared_galven_tube_circuits.iff")

object_tangible_component_weapon_shared_geonosian_power_cube = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_geonosian_power_cube.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_sp_ppack_bomb.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:geonosian_power_cube",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:geonosian_power_cube",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:geonosian_power_cube",
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

	clientObjectCRC = 2313307226,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/weapon/shared_geonosian_power_cube_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_geonosian_power_cube, "object/tangible/component/weapon/shared_geonosian_power_cube.iff")

object_tangible_component_weapon_shared_geonosian_power_cube_base = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_geonosian_power_cube_base.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_sp_ppack_bomb.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:geonosian_power_cube_base",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:geonosian_power_cube",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:geonosian_power_cube_base",
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

	clientObjectCRC = 4092441918,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_geonosian_power_cube_base, "object/tangible/component/weapon/shared_geonosian_power_cube_base.iff")

object_tangible_component_weapon_shared_geonosian_power_cube_green = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_geonosian_power_cube_green.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_sp_ppack_bomb.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:geonosian_power_cube_green",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:geonosian_power_cube_green",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:geonosian_power_cube_green",
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

	clientObjectCRC = 2570329564,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/weapon/shared_geonosian_power_cube_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_geonosian_power_cube_green, "object/tangible/component/weapon/shared_geonosian_power_cube_green.iff")

object_tangible_component_weapon_shared_geonosian_power_cube_red = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_geonosian_power_cube_red.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_sp_ppack_bomb.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:geonosian_power_cube_red",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:geonosian_power_cube_red",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:geonosian_power_cube_red",
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

	clientObjectCRC = 98191878,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/weapon/shared_geonosian_power_cube_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_geonosian_power_cube_red, "object/tangible/component/weapon/shared_geonosian_power_cube_red.iff")

object_tangible_component_weapon_shared_geonosian_power_cube_yellow = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_geonosian_power_cube_yellow.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_sp_ppack_bomb.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:geonosian_power_cube_yellow",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:geonosian_power_cube_yellow",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:geonosian_power_cube_yellow",
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

	clientObjectCRC = 783478248,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/weapon/shared_geonosian_power_cube_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_geonosian_power_cube_yellow, "object/tangible/component/weapon/shared_geonosian_power_cube_yellow.iff")

object_tangible_component_weapon_shared_geonosian_reinforcement_core = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_geonosian_reinforcement_core.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_sword_core.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:geonosian_reinforcement_core",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:geonosian_reinforcement_core",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:geonosian_reinforcement_core",
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

	clientObjectCRC = 2362781931,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_reinforcement_core.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_geonosian_reinforcement_core, "object/tangible/component/weapon/shared_geonosian_reinforcement_core.iff")

object_tangible_component_weapon_shared_geonosian_solidifying_agent = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_geonosian_solidifying_agent.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_adhesive.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:geonosian_solidifying_agent",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:geonosian_solidifying_agent",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:geonosian_solidifying_agent",
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

	clientObjectCRC = 3710952248,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/weapon/shared_melee_core_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_geonosian_solidifying_agent, "object/tangible/component/weapon/shared_geonosian_solidifying_agent.iff")

object_tangible_component_weapon_shared_geonosian_sword_core = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_geonosian_sword_core.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_sword_core.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:geonosian_sword_core",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:geonosian_sword_core",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:geonosian_sword_core",
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

	clientObjectCRC = 927591163,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_sword_core.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_geonosian_sword_core, "object/tangible/component/weapon/shared_geonosian_sword_core.iff")

object_tangible_component_weapon_shared_laser_cannon_cooling_sleeve = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_laser_cannon_cooling_sleeve.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_laser_cannon.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:laser_cannon_cooling_sleeve",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:laser_cannon_cooling_sleeve",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:laser_cannon_cooling_sleeve",
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

	clientObjectCRC = 2251276199,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_laser_cannon_cooling_sleeve, "object/tangible/component/weapon/shared_laser_cannon_cooling_sleeve.iff")

object_tangible_component_weapon_shared_laser_cannon_gun_tube = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_laser_cannon_gun_tube.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_laser_cannon_gun.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:laser_cannon_gun_tube",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:laser_cannon_gun_tube",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:laser_cannon_gun_tube",
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

	clientObjectCRC = 1385368085,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_laser_cannon_gun_tube, "object/tangible/component/weapon/shared_laser_cannon_gun_tube.iff")

object_tangible_component_weapon_shared_laser_generator = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_laser_generator.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "eqp_comp_weapon_high_power_module.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:laser_generator",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:laser_generator",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:laser_generator",
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

	clientObjectCRC = 695643472,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_laser_generator, "object/tangible/component/weapon/shared_laser_generator.iff")

object_tangible_component_weapon_shared_laser_magnetic_flashback_supressor = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_laser_magnetic_flashback_supressor.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_laser_cannon.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:laser_magnetic_flashback_supressor",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:laser_magnetic_flashback_supressor",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:laser_magnetic_flashback_supressor",
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

	clientObjectCRC = 741674762,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_laser_magnetic_flashback_supressor, "object/tangible/component/weapon/shared_laser_magnetic_flashback_supressor.iff")

object_tangible_component_weapon_shared_melee_core_enhancement = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_melee_core_enhancement.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_sword_core.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:melee_core_enhancement",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blade_vibro_unit",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:melee_core_enhancement",
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

	clientObjectCRC = 3988462144,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_melee_core_enhancement, "object/tangible/component/weapon/shared_melee_core_enhancement.iff")

object_tangible_component_weapon_shared_parallel_weapon_targeting_computer = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_parallel_weapon_targeting_computer.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_weapon_targeting_computer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:parallel_weapon_targeting_computer",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:parallel_weapon_targeting_computer",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:parallel_weapon_targeting_computer",
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

	clientObjectCRC = 466802862,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_parallel_weapon_targeting_computer, "object/tangible/component/weapon/shared_parallel_weapon_targeting_computer.iff")

object_tangible_component_weapon_shared_projectile_feed_mechanism = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_projectile_feed_mechanism.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_projectile_feed_mechanism.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:projectile_feed_mechanism",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:projectile_feed_mechanism",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:projectile_feed_mechanism",
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

	clientObjectCRC = 1361510729,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_projectile_feed_mechanism, "object/tangible/component/weapon/shared_projectile_feed_mechanism.iff")

object_tangible_component_weapon_shared_projectile_feed_mechanism_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_projectile_feed_mechanism_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_projectile_feed_mechanism.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:projectile_feed_mechanism_advanced",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:projectile_feed_mechanism_advanced",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:projectile_feed_mechanism_advanced",
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

	clientObjectCRC = 4156025153,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_projectile_feed_mechanism.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_projectile_feed_mechanism_advanced, "object/tangible/component/weapon/shared_projectile_feed_mechanism_advanced.iff")

object_tangible_component_weapon_shared_projectile_feed_mechanism_enhancement_durability = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_projectile_feed_mechanism_enhancement_durability.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_projectile_feed_mechanism.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:projectile_feed_mechanism_enhancement_durability",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:projectile_feed_mechanism_enhancement_durability",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:projectile_feed_mechanism_enhancement_durability",
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

	clientObjectCRC = 1517204001,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_base_projectile_feed_mechanism_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_projectile_feed_mechanism_enhancement_durability, "object/tangible/component/weapon/shared_projectile_feed_mechanism_enhancement_durability.iff")

object_tangible_component_weapon_shared_projectile_feed_mechanism_enhancement_gorax = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_projectile_feed_mechanism_enhancement_gorax.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/edb_con_tato_jar_funk_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:projectile_feed_mechanism_enhancement_gorax",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:projectile_feed_mechanism_enhancement_gorax",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:projectile_feed_mechanism_enhancement_gorax",
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

	clientObjectCRC = 255106526,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_base_projectile_feed_mechanism_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_projectile_feed_mechanism_enhancement_gorax, "object/tangible/component/weapon/shared_projectile_feed_mechanism_enhancement_gorax.iff")

object_tangible_component_weapon_shared_projectile_feed_mechanism_enhancement_max_damage = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_projectile_feed_mechanism_enhancement_max_damage.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_projectile_feed_mechanism.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:projectile_feed_mechanism_enhancement_max_damage",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:projectile_feed_mechanism_enhancement_max_damage",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:projectile_feed_mechanism_enhancement_max_damage",
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

	clientObjectCRC = 4293482918,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_base_projectile_feed_mechanism_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_projectile_feed_mechanism_enhancement_max_damage, "object/tangible/component/weapon/shared_projectile_feed_mechanism_enhancement_max_damage.iff")

object_tangible_component_weapon_shared_projectile_feed_mechanism_enhancement_min_damage = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_projectile_feed_mechanism_enhancement_min_damage.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_projectile_feed_mechanism.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:projectile_feed_mechanism_enhancement_min_damage",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:projectile_feed_mechanism_enhancement_min_damage",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:projectile_feed_mechanism_enhancement_min_damage",
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

	clientObjectCRC = 3419718655,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_base_projectile_feed_mechanism_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_projectile_feed_mechanism_enhancement_min_damage, "object/tangible/component/weapon/shared_projectile_feed_mechanism_enhancement_min_damage.iff")

object_tangible_component_weapon_shared_projectile_pistol_barrel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_projectile_pistol_barrel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s03.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:projectile_pistol_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:projectile_pistol_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:projectile_pistol_barrel",
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

	clientObjectCRC = 1216914672,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_projectile_pistol_barrel, "object/tangible/component/weapon/shared_projectile_pistol_barrel.iff")

object_tangible_component_weapon_shared_projectile_pistol_barrel_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_projectile_pistol_barrel_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s03.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:projectile_pistol_barrel_advanced",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:projectile_pistol_barrel_advanced",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:projectile_pistol_barrel_advanced",
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

	clientObjectCRC = 3447151631,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_projectile_pistol_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_projectile_pistol_barrel_advanced, "object/tangible/component/weapon/shared_projectile_pistol_barrel_advanced.iff")

object_tangible_component_weapon_shared_projectile_pistol_barrel_quest = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_projectile_pistol_barrel_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_sm_s03.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:projectile_pistol_barrel_quest",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:projectile_pistol_barrel_advanced",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:projectile_pistol_barrel_quest",
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

	clientObjectCRC = 1641350102,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_projectile_pistol_barrel.iff", "object/tangible/component/weapon/shared_projectile_pistol_barrel_advanced.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_projectile_pistol_barrel_quest, "object/tangible/component/weapon/shared_projectile_pistol_barrel_quest.iff")

object_tangible_component_weapon_shared_projectile_rifle_barrel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_projectile_rifle_barrel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s07.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:projectile_rifle_barrel",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:projectile_rifle_barrel",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:projectile_rifle_barrel",
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

	clientObjectCRC = 769812356,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_projectile_rifle_barrel, "object/tangible/component/weapon/shared_projectile_rifle_barrel.iff")

object_tangible_component_weapon_shared_projectile_rifle_barrel_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_projectile_rifle_barrel_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s07.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:projectile_rifle_barrel_advanced",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:projectile_rifle_barrel_advanced",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:projectile_rifle_barrel_advanced",
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

	clientObjectCRC = 594573612,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_projectile_rifle_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_projectile_rifle_barrel_advanced, "object/tangible/component/weapon/shared_projectile_rifle_barrel_advanced.iff")

object_tangible_component_weapon_shared_projectile_rifle_barrel_advanced_quest = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_projectile_rifle_barrel_advanced_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_muzzle_lg_s07.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:projectile_rifle_barrel_advanced_quest",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:projectile_rifle_barrel_advanced",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:projectile_rifle_barrel_advanced_quest",
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

	clientObjectCRC = 2968083189,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_projectile_rifle_barrel.iff", "object/tangible/component/weapon/shared_projectile_rifle_barrel_advanced.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_projectile_rifle_barrel_advanced_quest, "object/tangible/component/weapon/shared_projectile_rifle_barrel_advanced_quest.iff")

object_tangible_component_weapon_shared_rancor_tooth = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_rancor_tooth.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/con_gen_organic_hide_lg.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:rancor_tooth",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rancor_tooth",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:rancor_tooth",
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

	clientObjectCRC = 3366067371,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_sword_core.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_rancor_tooth, "object/tangible/component/weapon/shared_rancor_tooth.iff")

object_tangible_component_weapon_shared_rancor_tooth_quest = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_rancor_tooth_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/con_gen_organic_hide_lg.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:rancor_tooth_quest",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rancor_tooth",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:rancor_tooth_quest",
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

	clientObjectCRC = 829703922,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_sword_core.iff", "object/tangible/component/weapon/shared_rancor_tooth.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_rancor_tooth_quest, "object/tangible/component/weapon/shared_rancor_tooth_quest.iff")

object_tangible_component_weapon_shared_reinforcement_core = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_reinforcement_core.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_sword_core.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:reinforcement_core",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blade_vibro_unit",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:reinforcement_core",
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

	clientObjectCRC = 600823841,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_reinforcement_core, "object/tangible/component/weapon/shared_reinforcement_core.iff")

object_tangible_component_weapon_shared_reinforcement_core_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_reinforcement_core_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_sword_core.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:reinforcement_core_advanced",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blade_vibro_unit",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:reinforcement_core_advanced",
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

	clientObjectCRC = 276012891,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_reinforcement_core.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_reinforcement_core_advanced, "object/tangible/component/weapon/shared_reinforcement_core_advanced.iff")

object_tangible_component_weapon_shared_scope_weapon = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_scope_weapon.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_scope_sm_s03.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:scope_weapon",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:scope_weapon",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:scope_weapon",
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

	clientObjectCRC = 46230492,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_scope_weapon, "object/tangible/component/weapon/shared_scope_weapon.iff")

object_tangible_component_weapon_shared_scope_weapon_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_scope_weapon_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_scope_sm_s03.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:scope_weapon_advanced",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:scope_weapon_advanced",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:scope_weapon_advanced",
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

	clientObjectCRC = 210395856,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_scope_weapon.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_scope_weapon_advanced, "object/tangible/component/weapon/shared_scope_weapon_advanced.iff")

object_tangible_component_weapon_shared_scope_weapon_advanced_quest = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_scope_weapon_advanced_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_scope_sm_s03.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:scope_weapon_advanced_quest",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:scope_weapon_advanced",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:scope_weapon_advanced_quest",
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

	clientObjectCRC = 3286610922,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_scope_weapon.iff", "object/tangible/component/weapon/shared_scope_weapon_advanced.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_scope_weapon_advanced_quest, "object/tangible/component/weapon/shared_scope_weapon_advanced_quest.iff")

object_tangible_component_weapon_shared_scope_weapon_lg_s01 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_scope_weapon_lg_s01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_scope_lg_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:scope_weapon",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:scope_weapon",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:weapon_scope_l_t1",
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

	clientObjectCRC = 1450202343,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_scope_weapon.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_scope_weapon_lg_s01, "object/tangible/component/weapon/shared_scope_weapon_lg_s01.iff")

object_tangible_component_weapon_shared_scope_weapon_lg_s02 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_scope_weapon_lg_s02.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_scope_lg_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:scope_weapon",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:scope_weapon",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:weapon_scope_l_t2",
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

	clientObjectCRC = 2372402288,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_scope_weapon.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_scope_weapon_lg_s02, "object/tangible/component/weapon/shared_scope_weapon_lg_s02.iff")

object_tangible_component_weapon_shared_scope_weapon_lg_s03 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_scope_weapon_lg_s03.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_scope_lg_s03.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:scope_weapon",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:scope_weapon",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:weapon_scope_l_t3",
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

	clientObjectCRC = 3295321085,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_scope_weapon.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_scope_weapon_lg_s03, "object/tangible/component/weapon/shared_scope_weapon_lg_s03.iff")

object_tangible_component_weapon_shared_scope_weapon_sm_s01 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_scope_weapon_sm_s01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_scope_sm_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:scope_weapon",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:scope_weapon",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:weapon_scope_sm_t1",
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

	clientObjectCRC = 2395064169,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_scope_weapon.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_scope_weapon_sm_s01, "object/tangible/component/weapon/shared_scope_weapon_sm_s01.iff")

object_tangible_component_weapon_shared_scope_weapon_sm_s02 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_scope_weapon_sm_s02.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_scope_sm_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:scope_weapon",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:scope_weapon",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:weapon_scope_sm_t2",
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

	clientObjectCRC = 1440116734,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_scope_weapon.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_scope_weapon_sm_s02, "object/tangible/component/weapon/shared_scope_weapon_sm_s02.iff")

object_tangible_component_weapon_shared_scope_weapon_sm_s03 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_scope_weapon_sm_s03.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_scope_sm_s03.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:scope_weapon",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:scope_weapon",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:weapon_scope_sm_t3",
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

	clientObjectCRC = 484116595,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_scope_weapon.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_scope_weapon_sm_s03, "object/tangible/component/weapon/shared_scope_weapon_sm_s03.iff")

object_tangible_component_weapon_shared_scope_weapon_sm_s04 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_scope_weapon_sm_s04.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_scope_sm_s04.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:scope_weapon",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:scope_weapon",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:weapon_scope_sm_t4",
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

	clientObjectCRC = 3879215975,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_scope_weapon.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_scope_weapon_sm_s04, "object/tangible/component/weapon/shared_scope_weapon_sm_s04.iff")

object_tangible_component_weapon_shared_scope_weapon_sm_s05 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_scope_weapon_sm_s05.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_scope_sm_s05.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:scope_weapon",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:scope_weapon",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:weapon_scope_sm_t5",
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

	clientObjectCRC = 2922726634,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_scope_weapon.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_scope_weapon_sm_s05, "object/tangible/component/weapon/shared_scope_weapon_sm_s05.iff")

object_tangible_component_weapon_shared_scope_weapon_sm_s06 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_scope_weapon_sm_s06.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_scope_sm_s06.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:scope_weapon",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:scope_weapon",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:weapon_scope_sm_t6",
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

	clientObjectCRC = 1965223037,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_scope_weapon.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_scope_weapon_sm_s06, "object/tangible/component/weapon/shared_scope_weapon_sm_s06.iff")

object_tangible_component_weapon_shared_spider_spine = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_spider_spine.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/edb_con_tato_jar_funk_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:spider_fang",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:spider_fang",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:spider_fang",
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

	clientObjectCRC = 1418250527,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_base_projectile_feed_mechanism_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_spider_spine, "object/tangible/component/weapon/shared_spider_spine.iff")

object_tangible_component_weapon_shared_stock = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_stock.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_rifle_t21_stock.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:stock_unit",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:stock_unit",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:stock_unit",
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

	clientObjectCRC = 2306652479,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_stock, "object/tangible/component/weapon/shared_stock.iff")

object_tangible_component_weapon_shared_stock_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_stock_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_rifle_t21_stock.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:stock_unit_advanced",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:stock_unit_advanced",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:stock_unit_advanced",
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

	clientObjectCRC = 3440579824,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_stock.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_stock_advanced, "object/tangible/component/weapon/shared_stock_advanced.iff")

object_tangible_component_weapon_shared_stock_advanced_quest = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_stock_advanced_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_rifle_t21_stock.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:stock_unit_advanced_quest",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:stock_unit_advanced",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:stock_unit_advanced_quest",
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

	clientObjectCRC = 473297139,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_stock.iff", "object/tangible/component/weapon/shared_stock_advanced.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_stock_advanced_quest, "object/tangible/component/weapon/shared_stock_advanced_quest.iff")

object_tangible_component_weapon_shared_sword_core = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_sword_core.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_sword_core.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:sword_core",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_core",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:sword_core",
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

	clientObjectCRC = 3001742780,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_sword_core, "object/tangible/component/weapon/shared_sword_core.iff")

object_tangible_component_weapon_shared_sword_core_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_sword_core_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_sword_core.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:sword_core_advanced",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_core_advanced",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:sword_core_advanced",
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

	clientObjectCRC = 639496171,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_sword_core.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_sword_core_advanced, "object/tangible/component/weapon/shared_sword_core_advanced.iff")

object_tangible_component_weapon_shared_sword_core_quest = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_sword_core_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_sword_core.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:sword_core_quest",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_core_advanced",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:sword_core_quest",
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

	clientObjectCRC = 937100583,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_sword_core.iff", "object/tangible/component/weapon/shared_sword_core_advanced.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_sword_core_quest, "object/tangible/component/weapon/shared_sword_core_quest.iff")

object_tangible_component_weapon_shared_turbo_laser_gun_tube = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_turbo_laser_gun_tube.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_turbo_laser.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:turbo_laser_gun_tube",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:turbo_laser_gun_tube",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:turbo_laser_gun_tube",
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

	clientObjectCRC = 2743057273,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_turbo_laser_gun_tube, "object/tangible/component/weapon/shared_turbo_laser_gun_tube.iff")

object_tangible_component_weapon_shared_vibro_unit = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_vibro_unit.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_blade_vibro_unit.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blade_vibro_unit",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blade_vibro_unit",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blade_vibro_unit",
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

	clientObjectCRC = 2075249202,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_vibro_unit, "object/tangible/component/weapon/shared_vibro_unit.iff")

object_tangible_component_weapon_shared_vibro_unit_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_vibro_unit_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_blade_vibro_unit.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blade_vibro_unit_advanced",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blade_vibro_unit_advanced",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blade_vibro_unit_advanced",
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

	clientObjectCRC = 1094994187,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_vibro_unit.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_vibro_unit_advanced, "object/tangible/component/weapon/shared_vibro_unit_advanced.iff")

object_tangible_component_weapon_shared_vibro_unit_enhancement_durability = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_vibro_unit_enhancement_durability.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_blade_vibro_unit.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blade_vibro_unit_enhancement_durability",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blade_vibro_unit_enhancement_durability",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blade_vibro_unit_enhancement_durability",
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

	clientObjectCRC = 719270332,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_base_vibro_unit_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_vibro_unit_enhancement_durability, "object/tangible/component/weapon/shared_vibro_unit_enhancement_durability.iff")

object_tangible_component_weapon_shared_vibro_unit_enhancement_max_damage = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_vibro_unit_enhancement_max_damage.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_blade_vibro_unit.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blade_vibro_unit_enhancement_max_damage",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blade_vibro_unit_enhancement_max_damage",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blade_vibro_unit_enhancement_max_damage",
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

	clientObjectCRC = 2404964923,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_base_vibro_unit_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_vibro_unit_enhancement_max_damage, "object/tangible/component/weapon/shared_vibro_unit_enhancement_max_damage.iff")

object_tangible_component_weapon_shared_vibro_unit_enhancement_min_damage = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_vibro_unit_enhancement_min_damage.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_blade_vibro_unit.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blade_vibro_unit_enhancement_min_damage",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blade_vibro_unit_enhancement_min_damage",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blade_vibro_unit_enhancement_min_damage",
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

	clientObjectCRC = 3143975010,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_base_vibro_unit_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_vibro_unit_enhancement_min_damage, "object/tangible/component/weapon/shared_vibro_unit_enhancement_min_damage.iff")

object_tangible_component_weapon_shared_vibro_unit_enhancement_wounding = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_vibro_unit_enhancement_wounding.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_blade_vibro_unit.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blade_vibro_unit_enhancement_wounding",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blade_vibro_unit_enhancement_wounding",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blade_vibro_unit_enhancement_wounding",
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

	clientObjectCRC = 1279704725,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_base_vibro_unit_enhancement.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_vibro_unit_enhancement_wounding, "object/tangible/component/weapon/shared_vibro_unit_enhancement_wounding.iff")

object_tangible_component_weapon_shared_vibro_unit_nightsister = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_vibro_unit_nightsister.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_blade_vibro_unit.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blade_vibro_unit_nightsister",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blade_vibro_unit_nightsister",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blade_vibro_unit_nightsister",
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

	clientObjectCRC = 3670724056,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_vibro_unit.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_vibro_unit_nightsister, "object/tangible/component/weapon/shared_vibro_unit_nightsister.iff")

object_tangible_component_weapon_shared_vibro_unit_quest = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_vibro_unit_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_blade_vibro_unit.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262152,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:blade_vibro_unit_quest",

	gameObjectType = 262152,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:blade_vibro_unit_quest",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:blade_vibro_unit_quest",
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

	clientObjectCRC = 2177771940,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff", "object/tangible/component/weapon/shared_vibro_unit.iff", "object/tangible/component/weapon/shared_vibro_unit_advanced.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_vibro_unit_quest, "object/tangible/component/weapon/shared_vibro_unit_quest.iff")

object_tangible_component_weapon_shared_weapon_carbine_laser_stock = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_weapon_carbine_laser_stock.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_carbine_laser_stock.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:laser_carbine_stock_unit",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:laser_carbine_stock_unit",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:laser_carbine_stock_unit",
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

	clientObjectCRC = 3845302346,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_weapon_carbine_laser_stock, "object/tangible/component/weapon/shared_weapon_carbine_laser_stock.iff")

object_tangible_component_weapon_shared_weapon_dlt20_stock = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_weapon_dlt20_stock.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_rifle_dlt20_stock.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:dlt20_stock_unit",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dlt20_stock_unit",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:dlt20_stock_unit",
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

	clientObjectCRC = 784421487,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_weapon_dlt20_stock, "object/tangible/component/weapon/shared_weapon_dlt20_stock.iff")

object_tangible_component_weapon_shared_weapon_dxr6_stock = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_weapon_dxr6_stock.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_carbine_dxr6_stock.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:dxr6_stock_unit",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:dxr6_stock_unit",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:dxr6_stock_unit",
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

	clientObjectCRC = 3265377487,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_weapon_dxr6_stock, "object/tangible/component/weapon/shared_weapon_dxr6_stock.iff")

object_tangible_component_weapon_shared_weapon_e11_stock_closed = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_weapon_e11_stock_closed.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_carbine_e11_stock_closed.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:e11_stock_unit_open",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:e11_stock_unit_open",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:e11_stock_unit_open",
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

	clientObjectCRC = 2778389108,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_weapon_e11_stock_closed, "object/tangible/component/weapon/shared_weapon_e11_stock_closed.iff")

object_tangible_component_weapon_shared_weapon_e11_stock_open = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_weapon_e11_stock_open.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_carbine_e11_stock_open.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:e11_stock_unit_open",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:e11_stock_unit_open",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:e11_stock_unit_open",
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

	clientObjectCRC = 3082135386,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_weapon_e11_stock_open, "object/tangible/component/weapon/shared_weapon_e11_stock_open.iff")

object_tangible_component_weapon_shared_weapon_ee3_stock = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_weapon_ee3_stock.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_carbine_ee3_stock.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:ee3_stock_unit",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:ee3_stock_unit",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:ee3_stock_unit",
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

	clientObjectCRC = 119190783,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_weapon_ee3_stock, "object/tangible/component/weapon/shared_weapon_ee3_stock.iff")

object_tangible_component_weapon_shared_weapon_elite_stock = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_weapon_elite_stock.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_carbine_elite_stock.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:carbine_elite_stock_unit",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:carbine_elite_stock_unit",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:carbine_elite_stock_unit",
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

	clientObjectCRC = 2199807561,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_weapon_elite_stock, "object/tangible/component/weapon/shared_weapon_elite_stock.iff")

object_tangible_component_weapon_shared_weapon_mount = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_weapon_mount.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_weapon_mount.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:weapon_mount",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:weapon_mount",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:weapon_mount",
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

	clientObjectCRC = 4368733,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_weapon_mount, "object/tangible/component/weapon/shared_weapon_mount.iff")

object_tangible_component_weapon_shared_weapon_mount_light = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_weapon_mount_light.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_weapon_mount.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:weapon_mount_light",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:weapon_mount_light",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:weapon_mount_light",
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

	clientObjectCRC = 1483742937,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_weapon_mount_light, "object/tangible/component/weapon/shared_weapon_mount_light.iff")

object_tangible_component_weapon_shared_weapon_rifle_laser_stock = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_weapon_rifle_laser_stock.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_rifle_laser_stock.apt",
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

	detailedDescription = "@craft_weapon_ingredients_d:laser_rifle_stock_unit",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:laser_rifle_stock_unit",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:laser_rifle_stock_unit",
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

	clientObjectCRC = 2098038776,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_weapon_rifle_laser_stock, "object/tangible/component/weapon/shared_weapon_rifle_laser_stock.iff")

object_tangible_component_weapon_shared_weapon_t21_stock = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_weapon_t21_stock.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_rifle_t21_stock.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:t21_stock_unit",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:t21_stock_unit",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:t21_stock_unit",
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

	clientObjectCRC = 1060795790,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_weapon_t21_stock, "object/tangible/component/weapon/shared_weapon_t21_stock.iff")

object_tangible_component_weapon_shared_weapon_targeting_computer = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_weapon_targeting_computer.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_weapon_targeting_computer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:weapon_targeting_computer",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:weapon_targeting_computer",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:weapon_targeting_computer",
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

	clientObjectCRC = 1015355286,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_weapon_targeting_computer, "object/tangible/component/weapon/shared_weapon_targeting_computer.iff")

object_tangible_component_weapon_shared_weapon_trajectory_computer = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/component/weapon/shared_weapon_trajectory_computer.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_comp_weapon_targeting_computer.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262153,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:weapon_trajectory_computer",

	gameObjectType = 262153,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:weapon_trajectory_computer",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:weapon_trajectory_computer",
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

	clientObjectCRC = 1519446623,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/component/base/shared_base_component.iff", "object/tangible/component/base/shared_base_barrel.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_shared_weapon_trajectory_computer, "object/tangible/component/weapon/shared_weapon_trajectory_computer.iff")
