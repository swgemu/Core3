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


object_tangible_ship_components_shield_generator_shared_shd_armek_plasma_shell_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_armek_plasma_shell_elite_n",
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

	clientObjectCRC = 4005496660,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_armek_plasma_shell_elite, "object/tangible/ship/components/shield_generator/shared_shd_armek_plasma_shell_elite.iff")

object_tangible_ship_components_shield_generator_shared_shd_armek_plasma_shell_elite_2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_armek_plasma_shell_elite_2_n",
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

	clientObjectCRC = 3941953467,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_armek_plasma_shell_elite_2, "object/tangible/ship/components/shield_generator/shared_shd_armek_plasma_shell_elite_2.iff")

object_tangible_ship_components_shield_generator_shared_shd_armek_plasma_shell_s1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_armek_plasma_shell_s1_n",
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

	clientObjectCRC = 4043998830,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_armek_plasma_shell_s1, "object/tangible/ship/components/shield_generator/shared_shd_armek_plasma_shell_s1.iff")

object_tangible_ship_components_shield_generator_shared_shd_armek_plasma_shell_s2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_armek_plasma_shell_s2_n",
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

	clientObjectCRC = 706555641,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_armek_plasma_shell_s2, "object/tangible/ship/components/shield_generator/shared_shd_armek_plasma_shell_s2.iff")

object_tangible_ship_components_shield_generator_shared_shd_armek_plasma_shell_s3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_armek_plasma_shell_s3_n",
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

	clientObjectCRC = 1662011764,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_armek_plasma_shell_s3, "object/tangible/ship/components/shield_generator/shared_shd_armek_plasma_shell_s3.iff")

object_tangible_ship_components_shield_generator_shared_shd_armek_plasma_shell_s6 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_armek_plasma_shell_s6_n",
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

	clientObjectCRC = 183086458,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_armek_plasma_shell_s6, "object/tangible/ship/components/shield_generator/shared_shd_armek_plasma_shell_s6.iff")

object_tangible_ship_components_shield_generator_shared_shd_cygnus_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_cygnus_elite_n",
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

	clientObjectCRC = 587137384,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_cygnus_elite, "object/tangible/ship/components/shield_generator/shared_shd_cygnus_elite.iff")

object_tangible_ship_components_shield_generator_shared_shd_cygnus_improved_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_cygnus_improved_mk2_n",
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

	clientObjectCRC = 172501282,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_cygnus_improved_mk2, "object/tangible/ship/components/shield_generator/shared_shd_cygnus_improved_mk2.iff")

object_tangible_ship_components_shield_generator_shared_shd_cygnus_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_cygnus_mk1_n",
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

	clientObjectCRC = 2092831252,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_cygnus_mk1, "object/tangible/ship/components/shield_generator/shared_shd_cygnus_mk1.iff")

object_tangible_ship_components_shield_generator_shared_shd_cygnus_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_cygnus_mk2_n",
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

	clientObjectCRC = 2812918403,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_cygnus_mk2, "object/tangible/ship/components/shield_generator/shared_shd_cygnus_mk2.iff")

object_tangible_ship_components_shield_generator_shared_shd_cygnus_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_cygnus_mk3_n",
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

	clientObjectCRC = 4003781902,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_cygnus_mk3, "object/tangible/ship/components/shield_generator/shared_shd_cygnus_mk3.iff")

object_tangible_ship_components_shield_generator_shared_shd_cygnus_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_cygnus_mk4_n",
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

	clientObjectCRC = 357037594,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_cygnus_mk4, "object/tangible/ship/components/shield_generator/shared_shd_cygnus_mk4.iff")

object_tangible_ship_components_shield_generator_shared_shd_cygnus_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_cygnus_mk5_n",
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

	clientObjectCRC = 1548390807,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_cygnus_mk5, "object/tangible/ship/components/shield_generator/shared_shd_cygnus_mk5.iff")

object_tangible_ship_components_shield_generator_shared_shd_cygnus_special_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_cygnus_special_mk1_n",
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

	clientObjectCRC = 491149550,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_cygnus_special_mk1, "object/tangible/ship/components/shield_generator/shared_shd_cygnus_special_mk1.iff")

object_tangible_ship_components_shield_generator_shared_shd_dual_deflector_s1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_dual_deflector_s1_n",
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

	clientObjectCRC = 3651549547,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_dual_deflector_s1, "object/tangible/ship/components/shield_generator/shared_shd_dual_deflector_s1.iff")

object_tangible_ship_components_shield_generator_shared_shd_dual_deflector_s2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_dual_deflector_s2_n",
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

	clientObjectCRC = 45191676,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_dual_deflector_s2, "object/tangible/ship/components/shield_generator/shared_shd_dual_deflector_s2.iff")

object_tangible_ship_components_shield_generator_shared_shd_gallofree_defender_2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_gallofree_defender_2_n",
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

	clientObjectCRC = 2812483779,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_gallofree_defender_2, "object/tangible/ship/components/shield_generator/shared_shd_gallofree_defender_2.iff")

object_tangible_ship_components_shield_generator_shared_shd_gallofree_defender_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_gallofree_defender_elite_n",
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

	clientObjectCRC = 673595337,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_gallofree_defender_elite, "object/tangible/ship/components/shield_generator/shared_shd_gallofree_defender_elite.iff")

object_tangible_ship_components_shield_generator_shared_shd_generic = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:shd_generic",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_generic",
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

	clientObjectCRC = 904269427,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_generic, "object/tangible/ship/components/shield_generator/shared_shd_generic.iff")

object_tangible_ship_components_shield_generator_shared_shd_incom_mark2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_incom_mark2_n",
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

	clientObjectCRC = 92167148,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_incom_mark2, "object/tangible/ship/components/shield_generator/shared_shd_incom_mark2.iff")

object_tangible_ship_components_shield_generator_shared_shd_incom_mark5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_incom_mark5_n",
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

	clientObjectCRC = 4271730936,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_incom_mark5, "object/tangible/ship/components/shield_generator/shared_shd_incom_mark5.iff")

object_tangible_ship_components_shield_generator_shared_shd_incom_mark9 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_incom_mark9_n",
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

	clientObjectCRC = 2676028541,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_incom_mark9, "object/tangible/ship/components/shield_generator/shared_shd_incom_mark9.iff")

object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_incom_rayshield_advanced_n",
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

	clientObjectCRC = 3501222654,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_advanced, "object/tangible/ship/components/shield_generator/shared_shd_incom_rayshield_advanced.iff")

object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_r4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:shd_incom_rayshield_r4_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_incom_rayshield_r4_n",
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

	clientObjectCRC = 328452728,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_r4, "object/tangible/ship/components/shield_generator/shared_shd_incom_rayshield_r4.iff")

object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_r7 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_incom_rayshield_r7_n",
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

	clientObjectCRC = 3364119279,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_r7, "object/tangible/ship/components/shield_generator/shared_shd_incom_rayshield_r7.iff")

object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_x1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_incom_rayshield_x1_n",
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

	clientObjectCRC = 2507824966,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_x1, "object/tangible/ship/components/shield_generator/shared_shd_incom_rayshield_x1.iff")

object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_x12 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_incom_rayshield_x12_n",
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

	clientObjectCRC = 1807948417,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_x12, "object/tangible/ship/components/shield_generator/shared_shd_incom_rayshield_x12.iff")

object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_x2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_incom_rayshield_x2_n",
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

	clientObjectCRC = 1315829713,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_x2, "object/tangible/ship/components/shield_generator/shared_shd_incom_rayshield_x2.iff")

object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_x5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_incom_rayshield_x5_n",
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

	clientObjectCRC = 3046038725,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_x5, "object/tangible/ship/components/shield_generator/shared_shd_incom_rayshield_x5.iff")

object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_x7 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_incom_rayshield_x7_n",
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

	clientObjectCRC = 664015839,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_x7, "object/tangible/ship/components/shield_generator/shared_shd_incom_rayshield_x7.iff")

object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_x9 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_incom_rayshield_x9_n",
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

	clientObjectCRC = 3566426176,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_x9, "object/tangible/ship/components/shield_generator/shared_shd_incom_rayshield_x9.iff")

object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_z1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_incom_rayshield_z1_n",
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

	clientObjectCRC = 2737456566,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_z1, "object/tangible/ship/components/shield_generator/shared_shd_incom_rayshield_z1.iff")

object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_z5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_incom_rayshield_z5_n",
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

	clientObjectCRC = 2212415029,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_z5, "object/tangible/ship/components/shield_generator/shared_shd_incom_rayshield_z5.iff")

object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_z7 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_incom_rayshield_z7_n",
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

	clientObjectCRC = 298060079,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_incom_rayshield_z7, "object/tangible/ship/components/shield_generator/shared_shd_incom_rayshield_z7.iff")

object_tangible_ship_components_shield_generator_shared_shd_incom_techscreen_1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_incom_techscreen_1_n",
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

	clientObjectCRC = 2855050390,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_incom_techscreen_1, "object/tangible/ship/components/shield_generator/shared_shd_incom_techscreen_1.iff")

object_tangible_ship_components_shield_generator_shared_shd_incom_techscreen_2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_incom_techscreen_2_n",
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

	clientObjectCRC = 1899705345,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_incom_techscreen_2, "object/tangible/ship/components/shield_generator/shared_shd_incom_techscreen_2.iff")

object_tangible_ship_components_shield_generator_shared_shd_incom_techscreen_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_incom_techscreen_elite_n",
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

	clientObjectCRC = 754371356,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_incom_techscreen_elite, "object/tangible/ship/components/shield_generator/shared_shd_incom_techscreen_elite.iff")

object_tangible_ship_components_shield_generator_shared_shd_interlaced_graviton = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_interlaced_graviton_n",
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

	clientObjectCRC = 1716616411,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_interlaced_graviton, "object/tangible/ship/components/shield_generator/shared_shd_interlaced_graviton.iff")

object_tangible_ship_components_shield_generator_shared_shd_kessel_imperial_cygnus_experimental_system = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_kessel_imperial_cygnus_experimental_system_n",
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

	clientObjectCRC = 980498708,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_kessel_imperial_cygnus_experimental_system, "object/tangible/ship/components/shield_generator/shared_shd_kessel_imperial_cygnus_experimental_system.iff")

object_tangible_ship_components_shield_generator_shared_shd_kessel_imperial_sds_secret_ops = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_kessel_imperial_sds_secret_ops_n",
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

	clientObjectCRC = 3075481852,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_kessel_imperial_sds_secret_ops, "object/tangible/ship/components/shield_generator/shared_shd_kessel_imperial_sds_secret_ops.iff")

object_tangible_ship_components_shield_generator_shared_shd_kessel_imperial_sfs_megapolyweb = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_kessel_imperial_sfs_megapolyweb_n",
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

	clientObjectCRC = 485167241,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_kessel_imperial_sfs_megapolyweb, "object/tangible/ship/components/shield_generator/shared_shd_kessel_imperial_sfs_megapolyweb.iff")

object_tangible_ship_components_shield_generator_shared_shd_kessel_rebel_incom_rayshield_overdriver = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_kessel_rebel_incom_rayshield_overdriver_n",
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

	clientObjectCRC = 3631366873,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_kessel_rebel_incom_rayshield_overdriver, "object/tangible/ship/components/shield_generator/shared_shd_kessel_rebel_incom_rayshield_overdriver.iff")

object_tangible_ship_components_shield_generator_shared_shd_kessel_rebel_sorosuub_ion_mesh_projection = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_kessel_rebel_sorosuub_ion_mesh_projection_n",
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

	clientObjectCRC = 2671377903,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_kessel_rebel_sorosuub_ion_mesh_projection, "object/tangible/ship/components/shield_generator/shared_shd_kessel_rebel_sorosuub_ion_mesh_projection.iff")

object_tangible_ship_components_shield_generator_shared_shd_kessel_rebel_unknown_proton_interweave_system = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_kessel_rebel_unknown_proton_interweave_system_n",
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

	clientObjectCRC = 3294081937,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_kessel_rebel_unknown_proton_interweave_system, "object/tangible/ship/components/shield_generator/shared_shd_kessel_rebel_unknown_proton_interweave_system.iff")

object_tangible_ship_components_shield_generator_shared_shd_koensayr_deflector_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_koensayr_deflector_advanced_n",
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

	clientObjectCRC = 3659868328,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_koensayr_deflector_advanced, "object/tangible/ship/components/shield_generator/shared_shd_koensayr_deflector_advanced.iff")

object_tangible_ship_components_shield_generator_shared_shd_koensayr_deflector_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_koensayr_deflector_elite_n",
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

	clientObjectCRC = 4054911210,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_koensayr_deflector_elite, "object/tangible/ship/components/shield_generator/shared_shd_koensayr_deflector_elite.iff")

object_tangible_ship_components_shield_generator_shared_shd_koensayr_deflector_m1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_koensayr_deflector_m1_n",
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

	clientObjectCRC = 3189603642,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_koensayr_deflector_m1, "object/tangible/ship/components/shield_generator/shared_shd_koensayr_deflector_m1.iff")

object_tangible_ship_components_shield_generator_shared_shd_koensayr_deflector_m2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_koensayr_deflector_m2_n",
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

	clientObjectCRC = 1695208877,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_koensayr_deflector_m2, "object/tangible/ship/components/shield_generator/shared_shd_koensayr_deflector_m2.iff")

object_tangible_ship_components_shield_generator_shared_shd_koensayr_deflector_m3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_koensayr_deflector_m3_n",
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

	clientObjectCRC = 738701856,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_koensayr_deflector_m3, "object/tangible/ship/components/shield_generator/shared_shd_koensayr_deflector_m3.iff")

object_tangible_ship_components_shield_generator_shared_shd_koensayr_deflector_m6 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_koensayr_deflector_m6_n",
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

	clientObjectCRC = 1174296110,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_koensayr_deflector_m6, "object/tangible/ship/components/shield_generator/shared_shd_koensayr_deflector_m6.iff")

object_tangible_ship_components_shield_generator_shared_shd_koensayr_deflector_m8 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_koensayr_deflector_m8_n",
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

	clientObjectCRC = 3069779377,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_koensayr_deflector_m8, "object/tangible/ship/components/shield_generator/shared_shd_koensayr_deflector_m8.iff")

object_tangible_ship_components_shield_generator_shared_shd_koensayr_improved_deflector_m1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_koensayr_improved_deflector_m1_n",
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

	clientObjectCRC = 2795036189,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_koensayr_improved_deflector_m1, "object/tangible/ship/components/shield_generator/shared_shd_koensayr_improved_deflector_m1.iff")

object_tangible_ship_components_shield_generator_shared_shd_koensayr_modified_deflector_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_koensayr_modified_deflector_advanced_n",
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

	clientObjectCRC = 2846210589,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_koensayr_modified_deflector_advanced, "object/tangible/ship/components/shield_generator/shared_shd_koensayr_modified_deflector_advanced.iff")

object_tangible_ship_components_shield_generator_shared_shd_kse_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_kse_elite_n",
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

	clientObjectCRC = 1176481939,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_kse_elite, "object/tangible/ship/components/shield_generator/shared_shd_kse_elite.iff")

object_tangible_ship_components_shield_generator_shared_shd_kse_enhanced_military_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_kse_enhanced_military_mk1_n",
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

	clientObjectCRC = 3332739328,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_kse_enhanced_military_mk1, "object/tangible/ship/components/shield_generator/shared_shd_kse_enhanced_military_mk1.iff")

object_tangible_ship_components_shield_generator_shared_shd_kse_military_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_kse_military_mk1_n",
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

	clientObjectCRC = 3352793075,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_kse_military_mk1, "object/tangible/ship/components/shield_generator/shared_shd_kse_military_mk1.iff")

object_tangible_ship_components_shield_generator_shared_shd_kse_military_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_kse_military_mk2_n",
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

	clientObjectCRC = 482355044,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_kse_military_mk2, "object/tangible/ship/components/shield_generator/shared_shd_kse_military_mk2.iff")

object_tangible_ship_components_shield_generator_shared_shd_kse_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_kse_mk3_n",
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

	clientObjectCRC = 4019567364,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_kse_mk3, "object/tangible/ship/components/shield_generator/shared_shd_kse_mk3.iff")

object_tangible_ship_components_shield_generator_shared_shd_kse_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_kse_mk4_n",
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

	clientObjectCRC = 343314448,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_kse_mk4, "object/tangible/ship/components/shield_generator/shared_shd_kse_mk4.iff")

object_tangible_ship_components_shield_generator_shared_shd_kse_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_kse_mk5_n",
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

	clientObjectCRC = 1568405405,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_kse_mk5, "object/tangible/ship/components/shield_generator/shared_shd_kse_mk5.iff")

object_tangible_ship_components_shield_generator_shared_shd_kse_mk6 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_kse_mk6_n",
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

	clientObjectCRC = 2255249162,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_kse_mk6, "object/tangible/ship/components/shield_generator/shared_shd_kse_mk6.iff")

object_tangible_ship_components_shield_generator_shared_shd_kse_mk7 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_kse_mk7_n",
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

	clientObjectCRC = 3479255175,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_kse_mk7, "object/tangible/ship/components/shield_generator/shared_shd_kse_mk7.iff")

object_tangible_ship_components_shield_generator_shared_shd_mandal_double_protector_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_mandal_double_protector_mk1_n",
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

	clientObjectCRC = 442744867,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_mandal_double_protector_mk1, "object/tangible/ship/components/shield_generator/shared_shd_mandal_double_protector_mk1.iff")

object_tangible_ship_components_shield_generator_shared_shd_mandal_flexshield_ks25 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_mandal_flexshield_ks25_n",
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

	clientObjectCRC = 2330337362,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_mandal_flexshield_ks25, "object/tangible/ship/components/shield_generator/shared_shd_mandal_flexshield_ks25.iff")

object_tangible_ship_components_shield_generator_shared_shd_mandal_flexshield_ks5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_mandal_flexshield_ks5_n",
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

	clientObjectCRC = 2144035461,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_mandal_flexshield_ks5, "object/tangible/ship/components/shield_generator/shared_shd_mandal_flexshield_ks5.iff")

object_tangible_ship_components_shield_generator_shared_shd_mandal_flexshield_ks7 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_mandal_flexshield_ks7_n",
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

	clientObjectCRC = 3989941663,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_mandal_flexshield_ks7, "object/tangible/ship/components/shield_generator/shared_shd_mandal_flexshield_ks7.iff")

object_tangible_ship_components_shield_generator_shared_shd_mandal_flexshield_kx1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_mandal_flexshield_kx1_n",
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

	clientObjectCRC = 2869402958,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_mandal_flexshield_kx1, "object/tangible/ship/components/shield_generator/shared_shd_mandal_flexshield_kx1.iff")

object_tangible_ship_components_shield_generator_shared_shd_mandal_protector_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_mandal_protector_mk1_n",
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

	clientObjectCRC = 4072962412,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_mandal_protector_mk1, "object/tangible/ship/components/shield_generator/shared_shd_mandal_protector_mk1.iff")

object_tangible_ship_components_shield_generator_shared_shd_mandalor_flexshield_ks1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_mandalor_flexshield_ks1_n",
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

	clientObjectCRC = 2105182786,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_mandalor_flexshield_ks1, "object/tangible/ship/components/shield_generator/shared_shd_mandalor_flexshield_ks1.iff")

object_tangible_ship_components_shield_generator_shared_shd_mandalor_flexshield_ks18 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_mandalor_flexshield_ks18_n",
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

	clientObjectCRC = 1531190620,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_mandalor_flexshield_ks18, "object/tangible/ship/components/shield_generator/shared_shd_mandalor_flexshield_ks18.iff")

object_tangible_ship_components_shield_generator_shared_shd_mandalor_flexshield_ks3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_mandalor_flexshield_ks3_n",
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

	clientObjectCRC = 4016063832,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_mandalor_flexshield_ks3, "object/tangible/ship/components/shield_generator/shared_shd_mandalor_flexshield_ks3.iff")

object_tangible_ship_components_shield_generator_shared_shd_mission_reward_imperial_cygnus_holoscreen = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_mission_reward_imperial_cygnus_holoscreen_n",
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

	clientObjectCRC = 2343498615,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_mission_reward_imperial_cygnus_holoscreen, "object/tangible/ship/components/shield_generator/shared_shd_mission_reward_imperial_cygnus_holoscreen.iff")

object_tangible_ship_components_shield_generator_shared_shd_mission_reward_imperial_rendili_dual_projector = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_mission_reward_imperial_rendili_dual_projector_n",
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

	clientObjectCRC = 3141363443,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_mission_reward_imperial_rendili_dual_projector, "object/tangible/ship/components/shield_generator/shared_shd_mission_reward_imperial_rendili_dual_projector.iff")

object_tangible_ship_components_shield_generator_shared_shd_mission_reward_neutral_armek_plasma_web = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_mission_reward_neutral_armek_plasma_web_n",
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

	clientObjectCRC = 868794909,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_mission_reward_neutral_armek_plasma_web, "object/tangible/ship/components/shield_generator/shared_shd_mission_reward_neutral_armek_plasma_web.iff")

object_tangible_ship_components_shield_generator_shared_shd_mission_reward_neutral_koensayr_ds23 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_mission_reward_neutral_koensayr_ds23_n",
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

	clientObjectCRC = 489325202,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_mission_reward_neutral_koensayr_ds23, "object/tangible/ship/components/shield_generator/shared_shd_mission_reward_neutral_koensayr_ds23.iff")

object_tangible_ship_components_shield_generator_shared_shd_mission_reward_rebel_incom_k77 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_mission_reward_rebel_incom_k77_n",
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

	clientObjectCRC = 2160478208,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_mission_reward_rebel_incom_k77, "object/tangible/ship/components/shield_generator/shared_shd_mission_reward_rebel_incom_k77.iff")

object_tangible_ship_components_shield_generator_shared_shd_mission_reward_rebel_taim_military_grade = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_mission_reward_rebel_taim_military_grade_n",
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

	clientObjectCRC = 1836682734,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_mission_reward_rebel_taim_military_grade, "object/tangible/ship/components/shield_generator/shared_shd_mission_reward_rebel_taim_military_grade.iff")

object_tangible_ship_components_shield_generator_shared_shd_moncal = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_moncal_n",
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

	clientObjectCRC = 2199200859,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_moncal, "object/tangible/ship/components/shield_generator/shared_shd_moncal.iff")

object_tangible_ship_components_shield_generator_shared_shd_moncal_deluxe_ionweb_a = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_moncal_deluxe_ionweb_a_n",
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

	clientObjectCRC = 1224559248,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_moncal_deluxe_ionweb_a, "object/tangible/ship/components/shield_generator/shared_shd_moncal_deluxe_ionweb_a.iff")

object_tangible_ship_components_shield_generator_shared_shd_moncal_deluxe_ionweb_b = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_moncal_deluxe_ionweb_b_n",
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

	clientObjectCRC = 2481644039,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_moncal_deluxe_ionweb_b, "object/tangible/ship/components/shield_generator/shared_shd_moncal_deluxe_ionweb_b.iff")

object_tangible_ship_components_shield_generator_shared_shd_moncal_ionweb_a = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_moncal_ionweb_a_n",
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

	clientObjectCRC = 523179685,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_moncal_ionweb_a, "object/tangible/ship/components/shield_generator/shared_shd_moncal_ionweb_a.iff")

object_tangible_ship_components_shield_generator_shared_shd_moncal_ionweb_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_moncal_ionweb_advanced_n",
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

	clientObjectCRC = 4163014250,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_moncal_ionweb_advanced, "object/tangible/ship/components/shield_generator/shared_shd_moncal_ionweb_advanced.iff")

object_tangible_ship_components_shield_generator_shared_shd_moncal_ionweb_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_moncal_ionweb_elite_n",
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

	clientObjectCRC = 1024099405,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_moncal_ionweb_elite, "object/tangible/ship/components/shield_generator/shared_shd_moncal_ionweb_elite.iff")

object_tangible_ship_components_shield_generator_shared_shd_moncal_ionweb_elite_2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_moncal_ionweb_elite_2_n",
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

	clientObjectCRC = 1650981306,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_moncal_ionweb_elite_2, "object/tangible/ship/components/shield_generator/shared_shd_moncal_ionweb_elite_2.iff")

object_tangible_ship_components_shield_generator_shared_shd_moncal_ionweb_heavy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_moncal_ionweb_heavy_n",
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

	clientObjectCRC = 2894219316,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_moncal_ionweb_heavy, "object/tangible/ship/components/shield_generator/shared_shd_moncal_ionweb_heavy.iff")

object_tangible_ship_components_shield_generator_shared_shd_phased_fullerine_fx12 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_phased_fullerine_fx12_n",
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

	clientObjectCRC = 3258399997,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_phased_fullerine_fx12, "object/tangible/ship/components/shield_generator/shared_shd_phased_fullerine_fx12.iff")

object_tangible_ship_components_shield_generator_shared_shd_phased_fullerine_fx27 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_phased_fullerine_fx27_n",
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

	clientObjectCRC = 2260127611,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_phased_fullerine_fx27, "object/tangible/ship/components/shield_generator/shared_shd_phased_fullerine_fx27.iff")

object_tangible_ship_components_shield_generator_shared_shd_phased_fullerine_fx92 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_phased_fullerine_fx92_n",
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

	clientObjectCRC = 460805949,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_phased_fullerine_fx92, "object/tangible/ship/components/shield_generator/shared_shd_phased_fullerine_fx92.iff")

object_tangible_ship_components_shield_generator_shared_shd_prototype_shield = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_prototype",
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

	clientObjectCRC = 31928618,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_prototype_shield, "object/tangible/ship/components/shield_generator/shared_shd_prototype_shield.iff")

object_tangible_ship_components_shield_generator_shared_shd_rendili = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_rendili_n",
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

	clientObjectCRC = 1045720054,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_rendili, "object/tangible/ship/components/shield_generator/shared_shd_rendili.iff")

object_tangible_ship_components_shield_generator_shared_shd_reward_armek_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:shd_reward",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_reward_armek_elite",
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

	clientObjectCRC = 3327697307,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_reward_armek_elite, "object/tangible/ship/components/shield_generator/shared_shd_reward_armek_elite.iff")

object_tangible_ship_components_shield_generator_shared_shd_reward_incom_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:shd_reward",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_reward_incom_elite",
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

	clientObjectCRC = 2029440203,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_reward_incom_elite, "object/tangible/ship/components/shield_generator/shared_shd_reward_incom_elite.iff")

object_tangible_ship_components_shield_generator_shared_shd_reward_mandalor_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:shd_reward",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_reward_mandalor_elite",
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

	clientObjectCRC = 1626448404,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_reward_mandalor_elite, "object/tangible/ship/components/shield_generator/shared_shd_reward_mandalor_elite.iff")

object_tangible_ship_components_shield_generator_shared_shd_reward_seinar_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:shd_reward",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_reward_seinar_elite",
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

	clientObjectCRC = 3113022153,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_reward_seinar_elite, "object/tangible/ship/components/shield_generator/shared_shd_reward_seinar_elite.iff")

object_tangible_ship_components_shield_generator_shared_shd_reward_taim_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:shd_reward",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_reward_taim_elite",
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

	clientObjectCRC = 1936705340,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_reward_taim_elite, "object/tangible/ship/components/shield_generator/shared_shd_reward_taim_elite.iff")

object_tangible_ship_components_shield_generator_shared_shd_seinar_experimental_a1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_seinar_experimental_a1_n",
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

	clientObjectCRC = 2243790343,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_seinar_experimental_a1, "object/tangible/ship/components/shield_generator/shared_shd_seinar_experimental_a1.iff")

object_tangible_ship_components_shield_generator_shared_shd_seinar_gx3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_seinar_gx3_n",
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

	clientObjectCRC = 1330497147,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_seinar_gx3, "object/tangible/ship/components/shield_generator/shared_shd_seinar_gx3.iff")

object_tangible_ship_components_shield_generator_shared_shd_seinar_gx7 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_seinar_gx7_n",
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

	clientObjectCRC = 1874413048,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_seinar_gx7, "object/tangible/ship/components/shield_generator/shared_shd_seinar_gx7.iff")

object_tangible_ship_components_shield_generator_shared_shd_seinar_gx_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_seinar_gx_elite_n",
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

	clientObjectCRC = 2098040456,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_seinar_gx_elite, "object/tangible/ship/components/shield_generator/shared_shd_seinar_gx_elite.iff")

object_tangible_ship_components_shield_generator_shared_shd_seinar_proton_screen_p1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_seinar_proton_screen_p1_n",
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

	clientObjectCRC = 951174675,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_seinar_proton_screen_p1, "object/tangible/ship/components/shield_generator/shared_shd_seinar_proton_screen_p1.iff")

object_tangible_ship_components_shield_generator_shared_shd_seinar_proton_screen_p6 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_seinar_proton_screen_p6_n",
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

	clientObjectCRC = 3276991751,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_seinar_proton_screen_p6, "object/tangible/ship/components/shield_generator/shared_shd_seinar_proton_screen_p6.iff")

object_tangible_ship_components_shield_generator_shared_shd_seinar_reflector_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_seinar_reflector_elite_n",
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

	clientObjectCRC = 3776811256,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_seinar_reflector_elite, "object/tangible/ship/components/shield_generator/shared_shd_seinar_reflector_elite.iff")

object_tangible_ship_components_shield_generator_shared_shd_seinar_reflector_standard = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_seinar_reflector_standard_n",
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

	clientObjectCRC = 2608074768,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_seinar_reflector_standard, "object/tangible/ship/components/shield_generator/shared_shd_seinar_reflector_standard.iff")

object_tangible_ship_components_shield_generator_shared_shd_sfs_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_sfs_advanced_n",
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

	clientObjectCRC = 204265573,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_sfs_advanced, "object/tangible/ship/components/shield_generator/shared_shd_sfs_advanced.iff")

object_tangible_ship_components_shield_generator_shared_shd_sfs_custom_polyweb_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_sfs_custom_polyweb_elite_n",
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

	clientObjectCRC = 4763553,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_sfs_custom_polyweb_elite, "object/tangible/ship/components/shield_generator/shared_shd_sfs_custom_polyweb_elite.iff")

object_tangible_ship_components_shield_generator_shared_shd_sfs_imperial_deluxe_standard = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_sfs_imperial_deluxe_standard_n",
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

	clientObjectCRC = 2062565953,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_sfs_imperial_deluxe_standard, "object/tangible/ship/components/shield_generator/shared_shd_sfs_imperial_deluxe_standard.iff")

object_tangible_ship_components_shield_generator_shared_shd_sfs_imperial_heavy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_sfs_imperial_heavy_n",
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

	clientObjectCRC = 3360322809,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_sfs_imperial_heavy, "object/tangible/ship/components/shield_generator/shared_shd_sfs_imperial_heavy.iff")

object_tangible_ship_components_shield_generator_shared_shd_sfs_imperial_special_forces = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_sfs_imperial_special_forces_n",
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

	clientObjectCRC = 3818296715,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_sfs_imperial_special_forces, "object/tangible/ship/components/shield_generator/shared_shd_sfs_imperial_special_forces.iff")

object_tangible_ship_components_shield_generator_shared_shd_sfs_imperial_standard = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_sfs_imperial_standard_n",
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

	clientObjectCRC = 4149159567,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_sfs_imperial_standard, "object/tangible/ship/components/shield_generator/shared_shd_sfs_imperial_standard.iff")

object_tangible_ship_components_shield_generator_shared_shd_sfs_limited_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_sfs_limited_advanced_n",
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

	clientObjectCRC = 3598481390,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_sfs_limited_advanced, "object/tangible/ship/components/shield_generator/shared_shd_sfs_limited_advanced.iff")

object_tangible_ship_components_shield_generator_shared_shd_sfs_modified_imperial_heavy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_sfs_modified_imperial_heavy_n",
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

	clientObjectCRC = 1316308873,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_sfs_modified_imperial_heavy, "object/tangible/ship/components/shield_generator/shared_shd_sfs_modified_imperial_heavy.iff")

object_tangible_ship_components_shield_generator_shared_shd_sfs_modified_imperial_special_forces = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_sfs_modified_imperial_special_forces_n",
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

	clientObjectCRC = 1435911104,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_sfs_modified_imperial_special_forces, "object/tangible/ship/components/shield_generator/shared_shd_sfs_modified_imperial_special_forces.iff")

object_tangible_ship_components_shield_generator_shared_shd_sfs_modified_polyweb_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_sfs_modified_polyweb_advanced_n",
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

	clientObjectCRC = 2004538016,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_sfs_modified_polyweb_advanced, "object/tangible/ship/components/shield_generator/shared_shd_sfs_modified_polyweb_advanced.iff")

object_tangible_ship_components_shield_generator_shared_shd_sfs_polyweb_4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_sfs_polyweb_4_n",
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

	clientObjectCRC = 610167392,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_sfs_polyweb_4, "object/tangible/ship/components/shield_generator/shared_shd_sfs_polyweb_4.iff")

object_tangible_ship_components_shield_generator_shared_shd_sfs_polyweb_6 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_sfs_polyweb_6_n",
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

	clientObjectCRC = 3057952122,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_sfs_polyweb_6, "object/tangible/ship/components/shield_generator/shared_shd_sfs_polyweb_6.iff")

object_tangible_ship_components_shield_generator_shared_shd_sfs_polyweb_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_sfs_polyweb_advanced_n",
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

	clientObjectCRC = 3475858867,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_sfs_polyweb_advanced, "object/tangible/ship/components/shield_generator/shared_shd_sfs_polyweb_advanced.iff")

object_tangible_ship_components_shield_generator_shared_shd_sfs_polyweb_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_sfs_polyweb_elite_n",
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

	clientObjectCRC = 1384192338,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_sfs_polyweb_elite, "object/tangible/ship/components/shield_generator/shared_shd_sfs_polyweb_elite.iff")

object_tangible_ship_components_shield_generator_shared_shd_taim_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_taim_advanced_n",
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

	clientObjectCRC = 549069337,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_taim_advanced, "object/tangible/ship/components/shield_generator/shared_shd_taim_advanced.iff")

object_tangible_ship_components_shield_generator_shared_shd_taim_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_taim_elite_n",
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

	clientObjectCRC = 3533183005,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_taim_elite, "object/tangible/ship/components/shield_generator/shared_shd_taim_elite.iff")

object_tangible_ship_components_shield_generator_shared_shd_taim_enhanced_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_taim_enhanced_advanced_n",
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

	clientObjectCRC = 412063730,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_taim_enhanced_advanced, "object/tangible/ship/components/shield_generator/shared_shd_taim_enhanced_advanced.iff")

object_tangible_ship_components_shield_generator_shared_shd_taim_heavy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_taim_heavy_n",
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

	clientObjectCRC = 1125176420,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_taim_heavy, "object/tangible/ship/components/shield_generator/shared_shd_taim_heavy.iff")

object_tangible_ship_components_shield_generator_shared_shd_taim_standard = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_taim_standard_n",
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

	clientObjectCRC = 3639474,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_taim_standard, "object/tangible/ship/components/shield_generator/shared_shd_taim_standard.iff")

object_tangible_ship_components_shield_generator_shared_shd_tiefighter_basic = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:shd_tiefighter_basic_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_tiefighter_basic_n",
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

	clientObjectCRC = 605684779,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_tiefighter_basic, "object/tangible/ship/components/shield_generator/shared_shd_tiefighter_basic.iff")

object_tangible_ship_components_shield_generator_shared_shd_unknown_holosteel_x1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_unknown_holosteel_x1_n",
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

	clientObjectCRC = 94312606,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_unknown_holosteel_x1, "object/tangible/ship/components/shield_generator/shared_shd_unknown_holosteel_x1.iff")

object_tangible_ship_components_shield_generator_shared_shd_unknown_holosteel_x2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_unknown_holosteel_x2_n",
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

	clientObjectCRC = 3733499913,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_unknown_holosteel_x2, "object/tangible/ship/components/shield_generator/shared_shd_unknown_holosteel_x2.iff")

object_tangible_ship_components_shield_generator_shared_shd_unknown_proton_projector = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_shield_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_unknown_proton_projector_n",
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

	clientObjectCRC = 2554696462,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_unknown_proton_projector, "object/tangible/ship/components/shield_generator/shared_shd_unknown_proton_projector.iff")

object_tangible_ship_components_shield_generator_shared_shd_z95_basic = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_shield_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741827,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:shd_z95_basic_d",

	gameObjectType = 1073741827,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:shd_z95_basic_n",
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

	clientObjectCRC = 1663130441,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shd_z95_basic, "object/tangible/ship/components/shield_generator/shared_shd_z95_basic.iff")

object_tangible_ship_components_shield_generator_shared_shield_generator_test = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ins_all_pow_fusion_ion_u0.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@shield_generator_test:base",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@shield_generator_test:base",
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

	clientObjectCRC = 2405620850,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_shield_generator_shared_shield_generator_test, "object/tangible/ship/components/shield_generator/shared_shield_generator_test.iff")
