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


object_tangible_component_weapon_lightsaber_shared_base_lightsaber_lance_module = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_blade_vibro_unit.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:base_lightsaber_module",

	gameObjectType = 262156,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:base_lightsaber_module",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:base_lightsaber_module",
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

	clientObjectCRC = 3404051263
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_lightsaber_shared_base_lightsaber_lance_module, "object/tangible/component/weapon/lightsaber/shared_base_lightsaber_lance_module.iff")

object_tangible_component_weapon_lightsaber_shared_base_lightsaber_module = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_blade_vibro_unit.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:base_lightsaber_module",

	gameObjectType = 262156,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:base_lightsaber_module",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:base_lightsaber_module",
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

	clientObjectCRC = 2816851382
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_lightsaber_shared_base_lightsaber_module, "object/tangible/component/weapon/lightsaber/shared_base_lightsaber_module.iff")

object_tangible_component_weapon_lightsaber_shared_lightsaber_lance_module_force_crystal = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/force_amplification_crystal.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:lance_force_crystal",

	gameObjectType = 262156,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:lance_force_crystal",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:lance_force_crystal",
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

	clientObjectCRC = 1896638798
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_lightsaber_shared_lightsaber_lance_module_force_crystal, "object/tangible/component/weapon/lightsaber/shared_lightsaber_lance_module_force_crystal.iff")

object_tangible_component_weapon_lightsaber_shared_lightsaber_module_attackspeed = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_blade_vibro_unit.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:lightsaber_module_atkspd",

	gameObjectType = 262156,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:lightsaber_module_atkspd",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:lightsaber_module_atkspd",
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

	clientObjectCRC = 384190732
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_lightsaber_shared_lightsaber_module_attackspeed, "object/tangible/component/weapon/lightsaber/shared_lightsaber_module_attackspeed.iff")

object_tangible_component_weapon_lightsaber_shared_lightsaber_module_color = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_blade_vibro_unit.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:lightsaber_module_color",

	gameObjectType = 262156,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:lightsaber_module_color",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:lightsaber_module_color",
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

	clientObjectCRC = 2224509400
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_lightsaber_shared_lightsaber_module_color, "object/tangible/component/weapon/lightsaber/shared_lightsaber_module_color.iff")

object_tangible_component_weapon_lightsaber_shared_lightsaber_module_damage = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_blade_vibro_unit.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:lightsaber_module_damage",

	gameObjectType = 262156,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:lightsaber_module_damage",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:lightsaber_module_damage",
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

	clientObjectCRC = 3690389169
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_lightsaber_shared_lightsaber_module_damage, "object/tangible/component/weapon/lightsaber/shared_lightsaber_module_damage.iff")

object_tangible_component_weapon_lightsaber_shared_lightsaber_module_force_crystal = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/force_amplification_crystal.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:force_crystal",

	gameObjectType = 262156,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:force_crystal",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:force_crystal",
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

	clientObjectCRC = 4273612814
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_lightsaber_shared_lightsaber_module_force_crystal, "object/tangible/component/weapon/lightsaber/shared_lightsaber_module_force_crystal.iff")

object_tangible_component_weapon_lightsaber_shared_lightsaber_module_forcecost = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_blade_vibro_unit.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:lightsaber_module_forcecost",

	gameObjectType = 262156,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:lightsaber_module_forcecost",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:lightsaber_module_forcecost",
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

	clientObjectCRC = 3573227590
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_lightsaber_shared_lightsaber_module_forcecost, "object/tangible/component/weapon/lightsaber/shared_lightsaber_module_forcecost.iff")

object_tangible_component_weapon_lightsaber_shared_lightsaber_module_krayt_dragon_pearl = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/dragon_pearl.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:krayt_dragon_pearl",

	gameObjectType = 262156,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:krayt_dragon_pearl",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:krayt_dragon_pearl",
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

	clientObjectCRC = 2322379839
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_lightsaber_shared_lightsaber_module_krayt_dragon_pearl, "object/tangible/component/weapon/lightsaber/shared_lightsaber_module_krayt_dragon_pearl.iff")

object_tangible_component_weapon_lightsaber_shared_lightsaber_module_woundchance = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_blade_vibro_unit.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_weapon_ingredients_d:lightsaber_module_woundchance",

	gameObjectType = 262156,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:lightsaber_module_woundchance",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:lightsaber_module_woundchance",
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

	clientObjectCRC = 1396643279
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_lightsaber_shared_lightsaber_module_woundchance, "object/tangible/component/weapon/lightsaber/shared_lightsaber_module_woundchance.iff")

object_tangible_component_weapon_lightsaber_shared_lightsaber_refined_crystal_pack = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/force_amplification_crystal.apt",
	arrangementDescriptors = {},

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

	detailedDescription = "@craft_weapon_ingredients_d:refined_crystal_pack",

	gameObjectType = 262144,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:refined_crystal_pack",

	noBuildRadius = 0,

	objectName = "@craft_weapon_ingredients_n:refined_crystal_pack",
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

	clientObjectCRC = 4078172805
}

ObjectTemplates:addClientTemplate(object_tangible_component_weapon_lightsaber_shared_lightsaber_refined_crystal_pack, "object/tangible/component/weapon/lightsaber/shared_lightsaber_refined_crystal_pack.iff")
