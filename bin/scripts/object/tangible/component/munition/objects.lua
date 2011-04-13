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


object_tangible_component_munition_shared_acklay_venom = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_nutrient_supplements_liquid.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262150,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_munition_ingredients_d:acklay_venom",

	gameObjectType = 262150,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:acklay_venom",

	noBuildRadius = 0,

	objectName = "@craft_munition_ingredients_n:acklay_venom",
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

	clientObjectCRC = 3684259216
}

ObjectTemplates:addClientTemplate(object_tangible_component_munition_shared_acklay_venom, "object/tangible/component/munition/shared_acklay_venom.iff")

object_tangible_component_munition_shared_ammo_projectile = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_ammo_projectile.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262150,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_munition_ingredients_d:ammo_projectile",

	gameObjectType = 262150,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:ammo_projectile",

	noBuildRadius = 0,

	objectName = "@craft_munition_ingredients_n:ammo_projectile",
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

	clientObjectCRC = 4029895422
}

ObjectTemplates:addClientTemplate(object_tangible_component_munition_shared_ammo_projectile, "object/tangible/component/munition/shared_ammo_projectile.iff")

object_tangible_component_munition_shared_ammo_projectile_entanglement = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_ammo_projectile_entanglement.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262150,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_munition_ingredients_d:ammo_projectile_entanglement",

	gameObjectType = 262150,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:ammo_projectile_entanglement",

	noBuildRadius = 0,

	objectName = "@craft_munition_ingredients_n:ammo_projectile_entanglement",
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

	clientObjectCRC = 1717162905
}

ObjectTemplates:addClientTemplate(object_tangible_component_munition_shared_ammo_projectile_entanglement, "object/tangible/component/munition/shared_ammo_projectile_entanglement.iff")

object_tangible_component_munition_shared_base_munition_enhancer = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_electronic_module_simple.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262150,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_munition_ingredients_d:munition_enhancer",

	gameObjectType = 262150,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:munition_enhancer",

	noBuildRadius = 0,

	objectName = "@craft_munition_ingredients_n:munition_enhancer",
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

	clientObjectCRC = 1098837027
}

ObjectTemplates:addClientTemplate(object_tangible_component_munition_shared_base_munition_enhancer, "object/tangible/component/munition/shared_base_munition_enhancer.iff")

object_tangible_component_munition_shared_enhanced_charge_composition = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_electronic_module_simple.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262150,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_munition_ingredients_d:enhanced_charge_composition",

	gameObjectType = 262150,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:enhanced_charge_composition",

	noBuildRadius = 0,

	objectName = "@craft_munition_ingredients_n:enhanced_charge_composition",
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

	clientObjectCRC = 1739187546
}

ObjectTemplates:addClientTemplate(object_tangible_component_munition_shared_enhanced_charge_composition, "object/tangible/component/munition/shared_enhanced_charge_composition.iff")

object_tangible_component_munition_shared_enhanced_charge_shaping = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_electronic_module_simple.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262150,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_munition_ingredients_d:enhanced_charge_shaping",

	gameObjectType = 262150,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:enhanced_charge_shaping",

	noBuildRadius = 0,

	objectName = "@craft_munition_ingredients_n:enhanced_charge_shaping",
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

	clientObjectCRC = 411019932
}

ObjectTemplates:addClientTemplate(object_tangible_component_munition_shared_enhanced_charge_shaping, "object/tangible/component/munition/shared_enhanced_charge_shaping.iff")

object_tangible_component_munition_shared_enhanced_destructive_pulse_channeling = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_electronic_module_simple.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262150,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_munition_ingredients_d:enhanced_destructive_pulse_channeling",

	gameObjectType = 262150,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:enhanced_destructive_pulse_channeling",

	noBuildRadius = 0,

	objectName = "@craft_munition_ingredients_n:enhanced_destructive_pulse_channeling",
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

	clientObjectCRC = 3545355156
}

ObjectTemplates:addClientTemplate(object_tangible_component_munition_shared_enhanced_destructive_pulse_channeling, "object/tangible/component/munition/shared_enhanced_destructive_pulse_channeling.iff")

object_tangible_component_munition_shared_enhanced_fragmentation_sleeve = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_electronic_module_simple.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262150,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_munition_ingredients_d:enhanced_fragmentation_sleeve",

	gameObjectType = 262150,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:enhanced_fragmentation_sleeve",

	noBuildRadius = 0,

	objectName = "@craft_munition_ingredients_n:enhanced_fragmentation_sleeve",
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

	clientObjectCRC = 628465189
}

ObjectTemplates:addClientTemplate(object_tangible_component_munition_shared_enhanced_fragmentation_sleeve, "object/tangible/component/munition/shared_enhanced_fragmentation_sleeve.iff")

object_tangible_component_munition_shared_kliknick_gland = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_tato_jar_guts_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262150,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_munition_ingredients_d:kliknick_gland",

	gameObjectType = 262150,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:kliknick_gland",

	noBuildRadius = 0,

	objectName = "@craft_munition_ingredients_n:kliknick_gland",
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

	clientObjectCRC = 3311758812
}

ObjectTemplates:addClientTemplate(object_tangible_component_munition_shared_kliknick_gland, "object/tangible/component/munition/shared_kliknick_gland.iff")

object_tangible_component_munition_shared_warhead_chemical = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_warhead_chemical.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262150,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_munition_ingredients_d:warhead_chemical",

	gameObjectType = 262150,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:warhead_chemical",

	noBuildRadius = 0,

	objectName = "@craft_munition_ingredients_n:warhead_chemical",
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

	clientObjectCRC = 3966888720
}

ObjectTemplates:addClientTemplate(object_tangible_component_munition_shared_warhead_chemical, "object/tangible/component/munition/shared_warhead_chemical.iff")

object_tangible_component_munition_shared_warhead_fusing_mechanism = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_electronic_module_simple.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262150,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_munition_ingredients_d:warhead_fusing_mechanism",

	gameObjectType = 262150,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:warhead_fusing_mechanism",

	noBuildRadius = 0,

	objectName = "@craft_munition_ingredients_n:warhead_fusing_mechanism",
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

	clientObjectCRC = 896289962
}

ObjectTemplates:addClientTemplate(object_tangible_component_munition_shared_warhead_fusing_mechanism, "object/tangible/component/munition/shared_warhead_fusing_mechanism.iff")

object_tangible_component_munition_shared_warhead_heavy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_warhead_heavy.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262150,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_munition_ingredients_d:warhead_heavy",

	gameObjectType = 262150,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:warhead_heavy",

	noBuildRadius = 0,

	objectName = "@craft_munition_ingredients_n:warhead_heavy",
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

	clientObjectCRC = 2416425450
}

ObjectTemplates:addClientTemplate(object_tangible_component_munition_shared_warhead_heavy, "object/tangible/component/munition/shared_warhead_heavy.iff")

object_tangible_component_munition_shared_warhead_light = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_warhead_electronic.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262150,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_munition_ingredients_d:warhead_light",

	gameObjectType = 262150,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:warhead_light",

	noBuildRadius = 0,

	objectName = "@craft_munition_ingredients_n:warhead_light",
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

	clientObjectCRC = 1365214516
}

ObjectTemplates:addClientTemplate(object_tangible_component_munition_shared_warhead_light, "object/tangible/component/munition/shared_warhead_light.iff")

object_tangible_component_munition_shared_warhead_medium = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_warhead_medium.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262150,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_munition_ingredients_d:warhead_medium",

	gameObjectType = 262150,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:warhead_medium",

	noBuildRadius = 0,

	objectName = "@craft_munition_ingredients_n:warhead_medium",
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

	clientObjectCRC = 1284211616
}

ObjectTemplates:addClientTemplate(object_tangible_component_munition_shared_warhead_medium, "object/tangible/component/munition/shared_warhead_medium.iff")

object_tangible_component_munition_shared_warhead_stabilizer = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_electronic_module_complex.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 262150,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@craft_munition_ingredients_d:warhead_stabilizer",

	gameObjectType = 262150,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:warhead_stabilizer",

	noBuildRadius = 0,

	objectName = "@craft_munition_ingredients_n:warhead_stabilizer",
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

	clientObjectCRC = 1000887058
}

ObjectTemplates:addClientTemplate(object_tangible_component_munition_shared_warhead_stabilizer, "object/tangible/component/munition/shared_warhead_stabilizer.iff")
