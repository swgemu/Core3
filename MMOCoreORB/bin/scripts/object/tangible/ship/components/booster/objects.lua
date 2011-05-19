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


object_tangible_ship_components_booster_shared_booster_test = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_nemoidian_bird_cage.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@booster_test:base",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@booster_test:base",
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

	clientObjectCRC = 1784141535,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_booster_test, "object/tangible/ship/components/booster/shared_booster_test.iff")

object_tangible_ship_components_booster_shared_bst_corellian_advanced_thrust_enhancer = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_corellian_advanced_thrust_enhancer_n",
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

	clientObjectCRC = 95367825,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_corellian_advanced_thrust_enhancer, "object/tangible/ship/components/booster/shared_bst_corellian_advanced_thrust_enhancer.iff")

object_tangible_ship_components_booster_shared_bst_corellian_elite_thrust_enhancer = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_corellian_elite_thrust_enhancer_n",
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

	clientObjectCRC = 4019311987,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_corellian_elite_thrust_enhancer, "object/tangible/ship/components/booster/shared_bst_corellian_elite_thrust_enhancer.iff")

object_tangible_ship_components_booster_shared_bst_corellian_experimental_tjh3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_corellian_experimental_tjh3_n",
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

	clientObjectCRC = 788395141,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_corellian_experimental_tjh3, "object/tangible/ship/components/booster/shared_bst_corellian_experimental_tjh3.iff")

object_tangible_ship_components_booster_shared_bst_corellian_heavy_thrust_enhancer = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_corellian_heavy_thrust_enhancer_n",
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

	clientObjectCRC = 369299921,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_corellian_heavy_thrust_enhancer, "object/tangible/ship/components/booster/shared_bst_corellian_heavy_thrust_enhancer.iff")

object_tangible_ship_components_booster_shared_bst_corellian_highly_modified_elite_thrust_enhancer = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_corellian_highly_modified_elite_thrust_enhancer_n",
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

	clientObjectCRC = 307950030,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_corellian_highly_modified_elite_thrust_enhancer, "object/tangible/ship/components/booster/shared_bst_corellian_highly_modified_elite_thrust_enhancer.iff")

object_tangible_ship_components_booster_shared_bst_corellian_performance_advanced_thrust_enhancer = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_corellian_performance_advanced_thrust_enhancer_n",
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

	clientObjectCRC = 2687766710,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_corellian_performance_advanced_thrust_enhancer, "object/tangible/ship/components/booster/shared_bst_corellian_performance_advanced_thrust_enhancer.iff")

object_tangible_ship_components_booster_shared_bst_corellian_promotional_standard_thrust_enhancer = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_corellian_promotional_standard_thrust_enhancer_n",
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

	clientObjectCRC = 679723055,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_corellian_promotional_standard_thrust_enhancer, "object/tangible/ship/components/booster/shared_bst_corellian_promotional_standard_thrust_enhancer.iff")

object_tangible_ship_components_booster_shared_bst_corellian_standard_thrust_enhancer = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_corellian_standard_thrust_enhancer_n",
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

	clientObjectCRC = 82609038,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_corellian_standard_thrust_enhancer, "object/tangible/ship/components/booster/shared_bst_corellian_standard_thrust_enhancer.iff")

object_tangible_ship_components_booster_shared_bst_corellian_tjh3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_corellian_tjh3_n",
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

	clientObjectCRC = 3342663764,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_corellian_tjh3, "object/tangible/ship/components/booster/shared_bst_corellian_tjh3.iff")

object_tangible_ship_components_booster_shared_bst_corellian_tuned_heavy_thrust_enhancer = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_corellian_tuned_heavy_thrust_enhancer_n",
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

	clientObjectCRC = 3003301835,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_corellian_tuned_heavy_thrust_enhancer, "object/tangible/ship/components/booster/shared_bst_corellian_tuned_heavy_thrust_enhancer.iff")

object_tangible_ship_components_booster_shared_bst_cygnus_flashboost3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_cygnus_flashboost3_n",
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

	clientObjectCRC = 2062222960,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_cygnus_flashboost3, "object/tangible/ship/components/booster/shared_bst_cygnus_flashboost3.iff")

object_tangible_ship_components_booster_shared_bst_cygnus_flashboost4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_cygnus_flashboost4_n",
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

	clientObjectCRC = 2164796772,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_cygnus_flashboost4, "object/tangible/ship/components/booster/shared_bst_cygnus_flashboost4.iff")

object_tangible_ship_components_booster_shared_bst_freitek_outrunner_x1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_freitek_outrunner_x1_n",
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

	clientObjectCRC = 367538652,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_freitek_outrunner_x1, "object/tangible/ship/components/booster/shared_bst_freitek_outrunner_x1.iff")

object_tangible_ship_components_booster_shared_bst_gallofree_light = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_gallofree_light_n",
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

	clientObjectCRC = 2309515131,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_gallofree_light, "object/tangible/ship/components/booster/shared_bst_gallofree_light.iff")

object_tangible_ship_components_booster_shared_bst_generic = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/xwing_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:bst_generic",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_generic",
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

	clientObjectCRC = 3848915623,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_generic, "object/tangible/ship/components/booster/shared_bst_generic.iff")

object_tangible_ship_components_booster_shared_bst_incom_deluxe_fynock = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_incom_deluxe_fynock_n",
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

	clientObjectCRC = 1705883702,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_incom_deluxe_fynock, "object/tangible/ship/components/booster/shared_bst_incom_deluxe_fynock.iff")

object_tangible_ship_components_booster_shared_bst_incom_elite_sls_1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_incom_elite_sls_1_n",
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

	clientObjectCRC = 3900405472,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_incom_elite_sls_1, "object/tangible/ship/components/booster/shared_bst_incom_elite_sls_1.iff")

object_tangible_ship_components_booster_shared_bst_incom_enhanced_mynock = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_incom_enhanced_mynock_n",
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

	clientObjectCRC = 3742318303,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_incom_enhanced_mynock, "object/tangible/ship/components/booster/shared_bst_incom_enhanced_mynock.iff")

object_tangible_ship_components_booster_shared_bst_incom_fynock = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_incom_fynock_n",
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

	clientObjectCRC = 1410368784,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_incom_fynock, "object/tangible/ship/components/booster/shared_bst_incom_fynock.iff")

object_tangible_ship_components_booster_shared_bst_incom_intimidator_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_incom_intimidator_mk1_n",
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

	clientObjectCRC = 3520766481,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_incom_intimidator_mk1, "object/tangible/ship/components/booster/shared_bst_incom_intimidator_mk1.iff")

object_tangible_ship_components_booster_shared_bst_incom_intimidator_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_incom_intimidator_mk2_n",
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

	clientObjectCRC = 181209734,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_incom_intimidator_mk2, "object/tangible/ship/components/booster/shared_bst_incom_intimidator_mk2.iff")

object_tangible_ship_components_booster_shared_bst_incom_intimidator_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_incom_intimidator_mk3_n",
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

	clientObjectCRC = 1136684299,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_incom_intimidator_mk3, "object/tangible/ship/components/booster/shared_bst_incom_intimidator_mk3.iff")

object_tangible_ship_components_booster_shared_bst_incom_intimidator_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_incom_intimidator_mk4_n",
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

	clientObjectCRC = 3089319455,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_incom_intimidator_mk4, "object/tangible/ship/components/booster/shared_bst_incom_intimidator_mk4.iff")

object_tangible_ship_components_booster_shared_bst_incom_mynock = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_incom_mynock_n",
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

	clientObjectCRC = 3336637930,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_incom_mynock, "object/tangible/ship/components/booster/shared_bst_incom_mynock.iff")

object_tangible_ship_components_booster_shared_bst_incom_nkj31 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_incom_nkj31_n",
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

	clientObjectCRC = 1721827885,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_incom_nkj31, "object/tangible/ship/components/booster/shared_bst_incom_nkj31.iff")

object_tangible_ship_components_booster_shared_bst_incom_performance_nkj31 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_incom_performance_nkj31_n",
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

	clientObjectCRC = 47183178,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_incom_performance_nkj31, "object/tangible/ship/components/booster/shared_bst_incom_performance_nkj31.iff")

object_tangible_ship_components_booster_shared_bst_incom_sls_1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_incom_sls_1_n",
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

	clientObjectCRC = 2524451923,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_incom_sls_1, "object/tangible/ship/components/booster/shared_bst_incom_sls_1.iff")

object_tangible_ship_components_booster_shared_bst_incom_supercharged_vynock = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_incom_supercharged_vynock_n",
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

	clientObjectCRC = 4118504437,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_incom_supercharged_vynock, "object/tangible/ship/components/booster/shared_bst_incom_supercharged_vynock.iff")

object_tangible_ship_components_booster_shared_bst_incom_vynock = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_incom_vynock_n",
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

	clientObjectCRC = 2064805592,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_incom_vynock, "object/tangible/ship/components/booster/shared_bst_incom_vynock.iff")

object_tangible_ship_components_booster_shared_bst_kde_br12 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kde_br12_n",
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

	clientObjectCRC = 744508372,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kde_br12, "object/tangible/ship/components/booster/shared_bst_kde_br12.iff")

object_tangible_ship_components_booster_shared_bst_kessel_imperial_cygnus_hyperthrust = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kessel_imperial_cygnus_hyperthrust_n",
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

	clientObjectCRC = 793081046,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kessel_imperial_cygnus_hyperthrust, "object/tangible/ship/components/booster/shared_bst_kessel_imperial_cygnus_hyperthrust.iff")

object_tangible_ship_components_booster_shared_bst_kessel_imperial_sds_experimental_b7 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kessel_imperial_sds_experimental_b7_n",
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

	clientObjectCRC = 1606808856,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kessel_imperial_sds_experimental_b7, "object/tangible/ship/components/booster/shared_bst_kessel_imperial_sds_experimental_b7.iff")

object_tangible_ship_components_booster_shared_bst_kessel_imperial_sfs_ultra_thrust = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kessel_imperial_sfs_ultra_thrust_n",
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

	clientObjectCRC = 53752884,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kessel_imperial_sfs_ultra_thrust, "object/tangible/ship/components/booster/shared_bst_kessel_imperial_sfs_ultra_thrust.iff")

object_tangible_ship_components_booster_shared_bst_kessel_rebel_incom_quicksilver = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kessel_rebel_incom_quicksilver_n",
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

	clientObjectCRC = 419026085,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kessel_rebel_incom_quicksilver, "object/tangible/ship/components/booster/shared_bst_kessel_rebel_incom_quicksilver.iff")

object_tangible_ship_components_booster_shared_bst_kessel_rebel_incom_windrunner = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kessel_rebel_incom_windrunner_n",
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

	clientObjectCRC = 3378973624,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kessel_rebel_incom_windrunner, "object/tangible/ship/components/booster/shared_bst_kessel_rebel_incom_windrunner.iff")

object_tangible_ship_components_booster_shared_bst_kessel_rebel_mandal_lightning_m1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kessel_rebel_mandal_lightning_m1_n",
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

	clientObjectCRC = 3998248231,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kessel_rebel_mandal_lightning_m1, "object/tangible/ship/components/booster/shared_bst_kessel_rebel_mandal_lightning_m1.iff")

object_tangible_ship_components_booster_shared_bst_koensayr_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_koensayr_advanced_n",
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

	clientObjectCRC = 4027189608,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_koensayr_advanced, "object/tangible/ship/components/booster/shared_bst_koensayr_advanced.iff")

object_tangible_ship_components_booster_shared_bst_koensayr_charged_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_koensayr_charged_advanced_n",
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

	clientObjectCRC = 2298767702,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_koensayr_charged_advanced, "object/tangible/ship/components/booster/shared_bst_koensayr_charged_advanced.iff")

object_tangible_ship_components_booster_shared_bst_koensayr_deluxe_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_koensayr_deluxe_elite_n",
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

	clientObjectCRC = 511836444,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_koensayr_deluxe_elite, "object/tangible/ship/components/booster/shared_bst_koensayr_deluxe_elite.iff")

object_tangible_ship_components_booster_shared_bst_koensayr_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_koensayr_elite_n",
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

	clientObjectCRC = 528263488,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_koensayr_elite, "object/tangible/ship/components/booster/shared_bst_koensayr_elite.iff")

object_tangible_ship_components_booster_shared_bst_koensayr_evh12 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_koensayr_evh12_n",
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

	clientObjectCRC = 1204424540,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_koensayr_evh12, "object/tangible/ship/components/booster/shared_bst_koensayr_evh12.iff")

object_tangible_ship_components_booster_shared_bst_koensayr_heavy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_koensayr_heavy_n",
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

	clientObjectCRC = 2398381369,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_koensayr_heavy, "object/tangible/ship/components/booster/shared_bst_koensayr_heavy.iff")

object_tangible_ship_components_booster_shared_bst_koensayr_improved_standard = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_koensayr_improved_standard_n",
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

	clientObjectCRC = 894005127,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_koensayr_improved_standard, "object/tangible/ship/components/booster/shared_bst_koensayr_improved_standard.iff")

object_tangible_ship_components_booster_shared_bst_koensayr_modified_heavy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_koensayr_modified_heavy_n",
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

	clientObjectCRC = 1813570456,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_koensayr_modified_heavy, "object/tangible/ship/components/booster/shared_bst_koensayr_modified_heavy.iff")

object_tangible_ship_components_booster_shared_bst_koensayr_racer_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_koensayr_racer_mk1_n",
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

	clientObjectCRC = 2813746586,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_koensayr_racer_mk1, "object/tangible/ship/components/booster/shared_bst_koensayr_racer_mk1.iff")

object_tangible_ship_components_booster_shared_bst_koensayr_racer_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_koensayr_racer_mk2_n",
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

	clientObjectCRC = 2090988813,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_koensayr_racer_mk2, "object/tangible/ship/components/booster/shared_bst_koensayr_racer_mk2.iff")

object_tangible_ship_components_booster_shared_bst_koensayr_racer_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_koensayr_racer_mk3_n",
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

	clientObjectCRC = 900502144,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_koensayr_racer_mk3, "object/tangible/ship/components/booster/shared_bst_koensayr_racer_mk3.iff")

object_tangible_ship_components_booster_shared_bst_koensayr_racer_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_koensayr_racer_mk4_n",
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

	clientObjectCRC = 3461331348,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_koensayr_racer_mk4, "object/tangible/ship/components/booster/shared_bst_koensayr_racer_mk4.iff")

object_tangible_ship_components_booster_shared_bst_koensayr_special_evh12 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_koensayr_special_evh12_n",
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

	clientObjectCRC = 2437955271,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_koensayr_special_evh12, "object/tangible/ship/components/booster/shared_bst_koensayr_special_evh12.iff")

object_tangible_ship_components_booster_shared_bst_koensayr_standard = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_koensayr_standard_n",
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

	clientObjectCRC = 3498550211,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_koensayr_standard, "object/tangible/ship/components/booster/shared_bst_koensayr_standard.iff")

object_tangible_ship_components_booster_shared_bst_kse_als_1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kse_als_1_n",
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

	clientObjectCRC = 4146162190,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kse_als_1, "object/tangible/ship/components/booster/shared_bst_kse_als_1.iff")

object_tangible_ship_components_booster_shared_bst_kse_bti1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kse_bti1_n",
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

	clientObjectCRC = 2827178862,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kse_bti1, "object/tangible/ship/components/booster/shared_bst_kse_bti1.iff")

object_tangible_ship_components_booster_shared_bst_kse_bti2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kse_bti2_n",
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

	clientObjectCRC = 1939143673,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kse_bti2, "object/tangible/ship/components/booster/shared_bst_kse_bti2.iff")

object_tangible_ship_components_booster_shared_bst_kse_bti3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kse_bti3_n",
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

	clientObjectCRC = 983145588,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kse_bti3, "object/tangible/ship/components/booster/shared_bst_kse_bti3.iff")

object_tangible_ship_components_booster_shared_bst_kse_cb6 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kse_cb6_n",
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

	clientObjectCRC = 1082190673,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kse_cb6, "object/tangible/ship/components/booster/shared_bst_kse_cb6.iff")

object_tangible_ship_components_booster_shared_bst_kse_deluxe_bti3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kse_deluxe_bti3_n",
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

	clientObjectCRC = 1877470958,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kse_deluxe_bti3, "object/tangible/ship/components/booster/shared_bst_kse_deluxe_bti3.iff")

object_tangible_ship_components_booster_shared_bst_kse_elite_als_1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kse_elite_als_1_n",
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

	clientObjectCRC = 4147447022,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kse_elite_als_1, "object/tangible/ship/components/booster/shared_bst_kse_elite_als_1.iff")

object_tangible_ship_components_booster_shared_bst_kse_enhanced_bti2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kse_enhanced_bti2_n",
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

	clientObjectCRC = 1680098180,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kse_enhanced_bti2, "object/tangible/ship/components/booster/shared_bst_kse_enhanced_bti2.iff")

object_tangible_ship_components_booster_shared_bst_kse_performance_bti1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kse_performance_bti1_n",
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

	clientObjectCRC = 1644149004,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kse_performance_bti1, "object/tangible/ship/components/booster/shared_bst_kse_performance_bti1.iff")

object_tangible_ship_components_booster_shared_bst_kse_performance_cb6 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kse_performance_cb6_n",
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

	clientObjectCRC = 3050826285,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kse_performance_cb6, "object/tangible/ship/components/booster/shared_bst_kse_performance_cb6.iff")

object_tangible_ship_components_booster_shared_bst_kuat_military_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kuat_military_mk1_n",
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

	clientObjectCRC = 3536291891,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kuat_military_mk1, "object/tangible/ship/components/booster/shared_bst_kuat_military_mk1.iff")

object_tangible_ship_components_booster_shared_bst_kuat_military_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kuat_military_mk2_n",
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

	clientObjectCRC = 164634788,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kuat_military_mk2, "object/tangible/ship/components/booster/shared_bst_kuat_military_mk2.iff")

object_tangible_ship_components_booster_shared_bst_kuat_military_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kuat_military_mk3_n",
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

	clientObjectCRC = 1088243497,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kuat_military_mk3, "object/tangible/ship/components/booster/shared_bst_kuat_military_mk3.iff")

object_tangible_ship_components_booster_shared_bst_kuat_military_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_kuat_military_mk4_n",
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

	clientObjectCRC = 3141430333,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_kuat_military_mk4, "object/tangible/ship/components/booster/shared_bst_kuat_military_mk4.iff")

object_tangible_ship_components_booster_shared_bst_mandal_deluxe_jbj_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_mandal_deluxe_jbj_mk4_n",
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

	clientObjectCRC = 2694479901,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_mandal_deluxe_jbj_mk4, "object/tangible/ship/components/booster/shared_bst_mandal_deluxe_jbj_mk4.iff")

object_tangible_ship_components_booster_shared_bst_mandal_enhanced_jbj_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_mandal_enhanced_jbj_mk1_n",
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

	clientObjectCRC = 1206714092,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_mandal_enhanced_jbj_mk1, "object/tangible/ship/components/booster/shared_bst_mandal_enhanced_jbj_mk1.iff")

object_tangible_ship_components_booster_shared_bst_mandal_improved_jbj_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_mandal_improved_jbj_mk3_n",
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

	clientObjectCRC = 3157954036,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_mandal_improved_jbj_mk3, "object/tangible/ship/components/booster/shared_bst_mandal_improved_jbj_mk3.iff")

object_tangible_ship_components_booster_shared_bst_mandal_jbj_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_mandal_jbj_mk1_n",
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

	clientObjectCRC = 3869490887,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_mandal_jbj_mk1, "object/tangible/ship/components/booster/shared_bst_mandal_jbj_mk1.iff")

object_tangible_ship_components_booster_shared_bst_mandal_jbj_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_mandal_jbj_mk2_n",
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

	clientObjectCRC = 1035212368,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_mandal_jbj_mk2, "object/tangible/ship/components/booster/shared_bst_mandal_jbj_mk2.iff")

object_tangible_ship_components_booster_shared_bst_mandal_jbj_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_mandal_jbj_mk3_n",
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

	clientObjectCRC = 1958310365,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_mandal_jbj_mk3, "object/tangible/ship/components/booster/shared_bst_mandal_jbj_mk3.iff")

object_tangible_ship_components_booster_shared_bst_mandal_jbj_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_mandal_jbj_mk4_n",
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

	clientObjectCRC = 2405063369,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_mandal_jbj_mk4, "object/tangible/ship/components/booster/shared_bst_mandal_jbj_mk4.iff")

object_tangible_ship_components_booster_shared_bst_mandal_jbj_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_mandal_jbj_mk5_n",
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

	clientObjectCRC = 3327606084,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_mandal_jbj_mk5, "object/tangible/ship/components/booster/shared_bst_mandal_jbj_mk5.iff")

object_tangible_ship_components_booster_shared_bst_mandal_limited_jbj_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_mandal_limited_jbj_mk5_n",
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

	clientObjectCRC = 3105704550,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_mandal_limited_jbj_mk5, "object/tangible/ship/components/booster/shared_bst_mandal_limited_jbj_mk5.iff")

object_tangible_ship_components_booster_shared_bst_mandal_modified_jbj_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_mandal_modified_jbj_mk2_n",
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

	clientObjectCRC = 2916150549,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_mandal_modified_jbj_mk2, "object/tangible/ship/components/booster/shared_bst_mandal_modified_jbj_mk2.iff")

object_tangible_ship_components_booster_shared_bst_mission_reward_imperial_rss_ion_booster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_mission_reward_imperial_rss_ion_booster_n",
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

	clientObjectCRC = 2616547998,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_mission_reward_imperial_rss_ion_booster, "object/tangible/ship/components/booster/shared_bst_mission_reward_imperial_rss_ion_booster.iff")

object_tangible_ship_components_booster_shared_bst_mission_reward_neutral_mandal_m_series = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_mission_reward_neutral_mandal_m_series_n",
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

	clientObjectCRC = 2251024280,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_mission_reward_neutral_mandal_m_series, "object/tangible/ship/components/booster/shared_bst_mission_reward_neutral_mandal_m_series.iff")

object_tangible_ship_components_booster_shared_bst_mission_reward_neutral_mandal_q_series = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_mission_reward_neutral_mandal_q_series_n",
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

	clientObjectCRC = 3643360208,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_mission_reward_neutral_mandal_q_series, "object/tangible/ship/components/booster/shared_bst_mission_reward_neutral_mandal_q_series.iff")

object_tangible_ship_components_booster_shared_bst_mission_reward_rebel_novaldex_hypernova = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_mission_reward_rebel_novaldex_hypernova_n",
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

	clientObjectCRC = 1314651324,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_mission_reward_rebel_novaldex_hypernova, "object/tangible/ship/components/booster/shared_bst_mission_reward_rebel_novaldex_hypernova.iff")

object_tangible_ship_components_booster_shared_bst_mission_reward_rebel_qualdex_halcyon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_mission_reward_rebel_qualdex_halcyon_n",
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

	clientObjectCRC = 2730673872,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_mission_reward_rebel_qualdex_halcyon, "object/tangible/ship/components/booster/shared_bst_mission_reward_rebel_qualdex_halcyon.iff")

object_tangible_ship_components_booster_shared_bst_moncal_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_moncal_advanced_n",
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

	clientObjectCRC = 3124355866,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_moncal_advanced, "object/tangible/ship/components/booster/shared_bst_moncal_advanced.iff")

object_tangible_ship_components_booster_shared_bst_moncal_charged_heavy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_moncal_charged_heavy_n",
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

	clientObjectCRC = 3234187742,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_moncal_charged_heavy, "object/tangible/ship/components/booster/shared_bst_moncal_charged_heavy.iff")

object_tangible_ship_components_booster_shared_bst_moncal_deluxe_standard = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_moncal_deluxe_standard_n",
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

	clientObjectCRC = 3884337187,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_moncal_deluxe_standard, "object/tangible/ship/components/booster/shared_bst_moncal_deluxe_standard.iff")

object_tangible_ship_components_booster_shared_bst_moncal_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_moncal_elite_n",
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

	clientObjectCRC = 3306025844,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_moncal_elite, "object/tangible/ship/components/booster/shared_bst_moncal_elite.iff")

object_tangible_ship_components_booster_shared_bst_moncal_enhanced_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_moncal_enhanced_elite_n",
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

	clientObjectCRC = 2418943761,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_moncal_enhanced_elite, "object/tangible/ship/components/booster/shared_bst_moncal_enhanced_elite.iff")

object_tangible_ship_components_booster_shared_bst_moncal_heavy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_moncal_heavy_n",
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

	clientObjectCRC = 1418018573,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_moncal_heavy, "object/tangible/ship/components/booster/shared_bst_moncal_heavy.iff")

object_tangible_ship_components_booster_shared_bst_moncal_jlc37 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_moncal_jlc37_n",
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

	clientObjectCRC = 4144415819,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_moncal_jlc37, "object/tangible/ship/components/booster/shared_bst_moncal_jlc37.iff")

object_tangible_ship_components_booster_shared_bst_moncal_limited_jlc37 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_moncal_limited_jlc37_n",
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

	clientObjectCRC = 124704737,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_moncal_limited_jlc37, "object/tangible/ship/components/booster/shared_bst_moncal_limited_jlc37.iff")

object_tangible_ship_components_booster_shared_bst_moncal_rare_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_moncal_rare_advanced_n",
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

	clientObjectCRC = 2113743234,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_moncal_rare_advanced, "object/tangible/ship/components/booster/shared_bst_moncal_rare_advanced.iff")

object_tangible_ship_components_booster_shared_bst_moncal_standard = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_moncal_standard_n",
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

	clientObjectCRC = 2595506609,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_moncal_standard, "object/tangible/ship/components/booster/shared_bst_moncal_standard.iff")

object_tangible_ship_components_booster_shared_bst_novaldex_pulsar = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_novaldex_pulsar_n",
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

	clientObjectCRC = 2871976232,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_novaldex_pulsar, "object/tangible/ship/components/booster/shared_bst_novaldex_pulsar.iff")

object_tangible_ship_components_booster_shared_bst_novaldex_pulsar_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_novaldex_pulsar_advanced_n",
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

	clientObjectCRC = 1333284272,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_novaldex_pulsar_advanced, "object/tangible/ship/components/booster/shared_bst_novaldex_pulsar_advanced.iff")

object_tangible_ship_components_booster_shared_bst_novaldex_quasar = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_novaldex_quasar_n",
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

	clientObjectCRC = 3470077476,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_novaldex_quasar, "object/tangible/ship/components/booster/shared_bst_novaldex_quasar.iff")

object_tangible_ship_components_booster_shared_bst_novaldex_quasar_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_novaldex_quasar_advanced_n",
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

	clientObjectCRC = 3009788712,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_novaldex_quasar_advanced, "object/tangible/ship/components/booster/shared_bst_novaldex_quasar_advanced.iff")

object_tangible_ship_components_booster_shared_bst_qualdex_xboost_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_qualdex_xboost_mk1_n",
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

	clientObjectCRC = 554255149,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_qualdex_xboost_mk1, "object/tangible/ship/components/booster/shared_bst_qualdex_xboost_mk1.iff")

object_tangible_ship_components_booster_shared_bst_qualdex_xboost_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_qualdex_xboost_mk2_n",
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

	clientObjectCRC = 4196330426,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_qualdex_xboost_mk2, "object/tangible/ship/components/booster/shared_bst_qualdex_xboost_mk2.iff")

object_tangible_ship_components_booster_shared_bst_qualdex_xboost_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_qualdex_xboost_mk3_n",
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

	clientObjectCRC = 3004402743,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_qualdex_xboost_mk3, "object/tangible/ship/components/booster/shared_bst_qualdex_xboost_mk3.iff")

object_tangible_ship_components_booster_shared_bst_qualdex_xboost_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_qualdex_xboost_mk4_n",
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

	clientObjectCRC = 1223730979,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_qualdex_xboost_mk4, "object/tangible/ship/components/booster/shared_bst_qualdex_xboost_mk4.iff")

object_tangible_ship_components_booster_shared_bst_reward_incom_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_item_d:bst_reward",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:bst_reward_incom_elite",
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

	clientObjectCRC = 3656597256,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_reward_incom_elite, "object/tangible/ship/components/booster/shared_bst_reward_incom_elite.iff")

object_tangible_ship_components_booster_shared_bst_reward_koensayr_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_item_d:bst_reward",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:bst_reward_koensayr_elite",
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

	clientObjectCRC = 2006126864,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_reward_koensayr_elite, "object/tangible/ship/components/booster/shared_bst_reward_koensayr_elite.iff")

object_tangible_ship_components_booster_shared_bst_reward_kuat_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_item_d:bst_reward",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:bst_reward_kuat_elite",
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

	clientObjectCRC = 3954154692,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_reward_kuat_elite, "object/tangible/ship/components/booster/shared_bst_reward_kuat_elite.iff")

object_tangible_ship_components_booster_shared_bst_reward_novaldex_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_item_d:bst_reward",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:bst_reward_novaldex_elite",
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

	clientObjectCRC = 621880457,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_reward_novaldex_elite, "object/tangible/ship/components/booster/shared_bst_reward_novaldex_elite.iff")

object_tangible_ship_components_booster_shared_bst_reward_qualdex_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space_item_d:bst_reward",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:bst_reward_qualdex_elite",
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

	clientObjectCRC = 2436545673,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_reward_qualdex_elite, "object/tangible/ship/components/booster/shared_bst_reward_qualdex_elite.iff")

object_tangible_ship_components_booster_shared_bst_rss_special = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_rss_special_n",
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

	clientObjectCRC = 3925642831,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_rss_special, "object/tangible/ship/components/booster/shared_bst_rss_special.iff")

object_tangible_ship_components_booster_shared_bst_sap_imperial_1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_sap_imperial_1_n",
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

	clientObjectCRC = 498383661,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_sap_imperial_1, "object/tangible/ship/components/booster/shared_bst_sap_imperial_1.iff")

object_tangible_ship_components_booster_shared_bst_sap_imperial_2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_sap_imperial_2_n",
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

	clientObjectCRC = 3332576186,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_sap_imperial_2, "object/tangible/ship/components/booster/shared_bst_sap_imperial_2.iff")

object_tangible_ship_components_booster_shared_bst_sds_enhanced_imperial_2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_sds_enhanced_imperial_2_n",
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

	clientObjectCRC = 2637703678,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_sds_enhanced_imperial_2, "object/tangible/ship/components/booster/shared_bst_sds_enhanced_imperial_2.iff")

object_tangible_ship_components_booster_shared_bst_sfs_imperial_1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_sfs_imperial_1_n",
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

	clientObjectCRC = 173403376,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_sfs_imperial_1, "object/tangible/ship/components/booster/shared_bst_sfs_imperial_1.iff")

object_tangible_ship_components_booster_shared_bst_sfs_imperial_2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_sfs_imperial_2_n",
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

	clientObjectCRC = 3510781031,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_sfs_imperial_2, "object/tangible/ship/components/booster/shared_bst_sfs_imperial_2.iff")

object_tangible_ship_components_booster_shared_bst_slayn_ion_booster_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_slayn_ion_booster_mk1_n",
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

	clientObjectCRC = 4258532580,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_slayn_ion_booster_mk1, "object/tangible/ship/components/booster/shared_bst_slayn_ion_booster_mk1.iff")

object_tangible_ship_components_booster_shared_bst_sorosuub_enhanced_liberator_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_sorosuub_enhanced_liberator_mk4_n",
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

	clientObjectCRC = 1866927528,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_sorosuub_enhanced_liberator_mk4, "object/tangible/ship/components/booster/shared_bst_sorosuub_enhanced_liberator_mk4.iff")

object_tangible_ship_components_booster_shared_bst_sorosuub_improved_liberator_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_sorosuub_improved_liberator_mk2_n",
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

	clientObjectCRC = 4042319819,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_sorosuub_improved_liberator_mk2, "object/tangible/ship/components/booster/shared_bst_sorosuub_improved_liberator_mk2.iff")

object_tangible_ship_components_booster_shared_bst_sorosuub_liberator_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_sorosuub_liberator_mk1_n",
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

	clientObjectCRC = 2904503853,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_sorosuub_liberator_mk1, "object/tangible/ship/components/booster/shared_bst_sorosuub_liberator_mk1.iff")

object_tangible_ship_components_booster_shared_bst_sorosuub_liberator_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_sorosuub_liberator_mk2_n",
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

	clientObjectCRC = 1980276410,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_sorosuub_liberator_mk2, "object/tangible/ship/components/booster/shared_bst_sorosuub_liberator_mk2.iff")

object_tangible_ship_components_booster_shared_bst_sorosuub_liberator_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_sorosuub_liberator_mk3_n",
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

	clientObjectCRC = 1057356087,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_sorosuub_liberator_mk3, "object/tangible/ship/components/booster/shared_bst_sorosuub_liberator_mk3.iff")

object_tangible_ship_components_booster_shared_bst_sorosuub_liberator_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_sorosuub_liberator_mk4_n",
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

	clientObjectCRC = 3303461411,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_sorosuub_liberator_mk4, "object/tangible/ship/components/booster/shared_bst_sorosuub_liberator_mk4.iff")

object_tangible_ship_components_booster_shared_bst_sorosuub_liberator_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_sorosuub_liberator_mk5_n",
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

	clientObjectCRC = 2381034926,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_sorosuub_liberator_mk5, "object/tangible/ship/components/booster/shared_bst_sorosuub_liberator_mk5.iff")

object_tangible_ship_components_booster_shared_bst_sorosuub_prized_liberator_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_sorosuub_prized_liberator_mk1_n",
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

	clientObjectCRC = 2805387949,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_sorosuub_prized_liberator_mk1, "object/tangible/ship/components/booster/shared_bst_sorosuub_prized_liberator_mk1.iff")

object_tangible_ship_components_booster_shared_bst_sorosuub_supercharged_liberator_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_sorosuub_supercharged_liberator_mk3_n",
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

	clientObjectCRC = 1684575263,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_sorosuub_supercharged_liberator_mk3, "object/tangible/ship/components/booster/shared_bst_sorosuub_supercharged_liberator_mk3.iff")

object_tangible_ship_components_booster_shared_bst_sorosuub_well_tuned_liberator_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_sorosuub_well_tuned_liberator_mk5_n",
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

	clientObjectCRC = 3378470899,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_sorosuub_well_tuned_liberator_mk5, "object/tangible/ship/components/booster/shared_bst_sorosuub_well_tuned_liberator_mk5.iff")

object_tangible_ship_components_booster_shared_bst_subpro_accelatron_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_subpro_accelatron_mk1_n",
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

	clientObjectCRC = 3614410827,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_subpro_accelatron_mk1, "object/tangible/ship/components/booster/shared_bst_subpro_accelatron_mk1.iff")

object_tangible_ship_components_booster_shared_bst_subpro_accelatron_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_subpro_accelatron_mk2_n",
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

	clientObjectCRC = 209199324,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_subpro_accelatron_mk2, "object/tangible/ship/components/booster/shared_bst_subpro_accelatron_mk2.iff")

object_tangible_ship_components_booster_shared_bst_subpro_accelatron_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_subpro_accelatron_mk3_n",
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

	clientObjectCRC = 1165313873,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_subpro_accelatron_mk3, "object/tangible/ship/components/booster/shared_bst_subpro_accelatron_mk3.iff")

object_tangible_ship_components_booster_shared_bst_subpro_accelatron_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_subpro_accelatron_mk4_n",
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

	clientObjectCRC = 3197529157,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_subpro_accelatron_mk4, "object/tangible/ship/components/booster/shared_bst_subpro_accelatron_mk4.iff")

object_tangible_ship_components_booster_shared_bst_subpro_accelatron_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_subpro_accelatron_mk5_n",
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

	clientObjectCRC = 4154133448,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_subpro_accelatron_mk5, "object/tangible/ship/components/booster/shared_bst_subpro_accelatron_mk5.iff")

object_tangible_ship_components_booster_shared_bst_subpro_deluxe_accelatron_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_subpro_deluxe_accelatron_mk3_n",
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

	clientObjectCRC = 2441728107,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_subpro_deluxe_accelatron_mk3, "object/tangible/ship/components/booster/shared_bst_subpro_deluxe_accelatron_mk3.iff")

object_tangible_ship_components_booster_shared_bst_subpro_elite_accelatron_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_subpro_elite_accelatron_mk5_n",
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

	clientObjectCRC = 2539684267,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_subpro_elite_accelatron_mk5, "object/tangible/ship/components/booster/shared_bst_subpro_elite_accelatron_mk5.iff")

object_tangible_ship_components_booster_shared_bst_subpro_enhanced_accelatron_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_subpro_enhanced_accelatron_mk2_n",
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

	clientObjectCRC = 3219799574,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_subpro_enhanced_accelatron_mk2, "object/tangible/ship/components/booster/shared_bst_subpro_enhanced_accelatron_mk2.iff")

object_tangible_ship_components_booster_shared_bst_subpro_modified_accelatron_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_subpro_modified_accelatron_mk4_n",
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

	clientObjectCRC = 3848103440,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_subpro_modified_accelatron_mk4, "object/tangible/ship/components/booster/shared_bst_subpro_modified_accelatron_mk4.iff")

object_tangible_ship_components_booster_shared_bst_subpro_tuned_accelatron_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_subpro_tuned_accelatron_mk1_n",
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

	clientObjectCRC = 2160911375,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_subpro_tuned_accelatron_mk1, "object/tangible/ship/components/booster/shared_bst_subpro_tuned_accelatron_mk1.iff")

object_tangible_ship_components_booster_shared_bst_surronian_accelerator_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_surronian_accelerator_mk1_n",
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

	clientObjectCRC = 3438333204,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_surronian_accelerator_mk1, "object/tangible/ship/components/booster/shared_bst_surronian_accelerator_mk1.iff")

object_tangible_ship_components_booster_shared_bst_surronian_accelerator_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_surronian_accelerator_mk2_n",
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

	clientObjectCRC = 401040771,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_surronian_accelerator_mk2, "object/tangible/ship/components/booster/shared_bst_surronian_accelerator_mk2.iff")

object_tangible_ship_components_booster_shared_bst_surronian_nomad_x4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_surronian_nomad_x4_n",
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

	clientObjectCRC = 1695261878,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_surronian_nomad_x4, "object/tangible/ship/components/booster/shared_bst_surronian_nomad_x4.iff")

object_tangible_ship_components_booster_shared_bst_surronian_nomad_x8 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_booster_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_booster_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_surronian_nomad_x8_n",
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

	clientObjectCRC = 68558899,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_surronian_nomad_x8, "object/tangible/ship/components/booster/shared_bst_surronian_nomad_x8.iff")

object_tangible_ship_components_booster_shared_bst_tiefighter_basic = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/xwing_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:bst_tiefighter_basic_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_tiefighter_basic_n",
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

	clientObjectCRC = 2602586479,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_tiefighter_basic, "object/tangible/ship/components/booster/shared_bst_tiefighter_basic.iff")

object_tangible_ship_components_booster_shared_bst_z95_basic = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/xwing_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:bst_z95_basic_d",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:bst_z95_basic_n",
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

	clientObjectCRC = 623716829,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_bst_z95_basic, "object/tangible/ship/components/booster/shared_bst_z95_basic.iff")

object_tangible_ship_components_booster_shared_xwing_booster_test = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/xwing_booster_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741831,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:xwing_booster",

	gameObjectType = 1073741831,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:xwing_booster",
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

	clientObjectCRC = 1998070919,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_booster_shared_xwing_booster_test, "object/tangible/ship/components/booster/shared_xwing_booster_test.iff")
