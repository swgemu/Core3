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


object_tangible_ship_components_weapon_shared_weapon_incom_disruptor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/xwing_weapon_neg_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:weapon_incom_disruptor_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1416211325,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_weapon_incom_disruptor, "object/tangible/ship/components/weapon/shared_weapon_incom_disruptor.iff")

object_tangible_ship_components_weapon_shared_weapon_slayn_ioncannon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/xwing_weapon_neg_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:weapon_slayn_ioncannon_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3090870041,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_weapon_slayn_ioncannon, "object/tangible/ship/components/weapon/shared_weapon_slayn_ioncannon.iff")

object_tangible_ship_components_weapon_shared_weapon_subpro_tripleblaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/xwing_weapon1_neg_s04.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:weapon_subpro_tripleblaster_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1718453703,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_weapon_subpro_tripleblaster, "object/tangible/ship/components/weapon/shared_weapon_subpro_tripleblaster.iff")

object_tangible_ship_components_weapon_shared_weapon_test = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/cmp_xwing_gun_neg_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:weapon_test_01_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:weapon_test_01_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 583355334,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_weapon_test, "object/tangible/ship/components/weapon/shared_weapon_test.iff")

object_tangible_ship_components_weapon_shared_wpn_armek_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_armek_advanced_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3432873939,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_armek_advanced, "object/tangible/ship/components/weapon/shared_wpn_armek_advanced.iff")

object_tangible_ship_components_weapon_shared_wpn_armek_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_armek_elite_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2927442761,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_armek_elite, "object/tangible/ship/components/weapon/shared_wpn_armek_elite.iff")

object_tangible_ship_components_weapon_shared_wpn_armek_sw4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_armek_sw4_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3078564587,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_armek_sw4, "object/tangible/ship/components/weapon/shared_wpn_armek_sw4.iff")

object_tangible_ship_components_weapon_shared_wpn_armek_sw6 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_armek_sw6_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 627434993,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_armek_sw6, "object/tangible/ship/components/weapon/shared_wpn_armek_sw6.iff")

object_tangible_ship_components_weapon_shared_wpn_armek_sw7 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_armek_sw7_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1818788476,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_armek_sw7, "object/tangible/ship/components/weapon/shared_wpn_armek_sw7.iff")

object_tangible_ship_components_weapon_shared_wpn_armek_sw8 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_armek_sw8_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3596791406,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_armek_sw8, "object/tangible/ship/components/weapon/shared_wpn_armek_sw8.iff")

object_tangible_ship_components_weapon_shared_wpn_awing_blaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:wpn_awing_blaster",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_awing_blaster",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1392493131,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_awing_blaster, "object/tangible/ship/components/weapon/shared_wpn_awing_blaster.iff")

object_tangible_ship_components_weapon_shared_wpn_borstel_rg9 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_borstel_rg9_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1971958873,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_borstel_rg9, "object/tangible/ship/components/weapon/shared_wpn_borstel_rg9.iff")

object_tangible_ship_components_weapon_shared_wpn_bwing_blaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:wpn_bwing_blaster",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_bwing_blaster",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1787466156,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_bwing_blaster, "object/tangible/ship/components/weapon/shared_wpn_bwing_blaster.iff")

object_tangible_ship_components_weapon_shared_wpn_capitalship_turret_test = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:weapon_turret",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:weapon_turret",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3311096308,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_capitalship_turret_test, "object/tangible/ship/components/weapon/shared_wpn_capitalship_turret_test.iff")

object_tangible_ship_components_weapon_shared_wpn_corellian_1d = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_corellian_1d_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2087182522,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_corellian_1d, "object/tangible/ship/components/weapon/shared_wpn_corellian_1d.iff")

object_tangible_ship_components_weapon_shared_wpn_corellian_ag1g_laser = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_corellian_ag1g_laser_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3460040348,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_corellian_ag1g_laser, "object/tangible/ship/components/weapon/shared_wpn_corellian_ag1g_laser.iff")

object_tangible_ship_components_weapon_shared_wpn_corellian_ag2g_quad_laser = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_corellian_ag2g_quad_laser_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2989343947,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_corellian_ag2g_quad_laser, "object/tangible/ship/components/weapon/shared_wpn_corellian_ag2g_quad_laser.iff")

object_tangible_ship_components_weapon_shared_wpn_corellian_cruiser_grade_blaster_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_corellian_cruiser_grade_blaster_mk1_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2213766317,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_corellian_cruiser_grade_blaster_mk1, "object/tangible/ship/components/weapon/shared_wpn_corellian_cruiser_grade_blaster_mk1.iff")

object_tangible_ship_components_weapon_shared_wpn_corvette_turret_sm_s01 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:weapon_turret",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:weapon_turret",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1361242261,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_corvette_turret_sm_s01, "object/tangible/ship/components/weapon/shared_wpn_corvette_turret_sm_s01.iff")

object_tangible_ship_components_weapon_shared_wpn_cygnus_destroyer_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_cygnus_destroyer_mk1_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4229372390,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_cygnus_destroyer_mk1, "object/tangible/ship/components/weapon/shared_wpn_cygnus_destroyer_mk1.iff")

object_tangible_ship_components_weapon_shared_wpn_cygnus_destroyer_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_cygnus_destroyer_mk2_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 654356849,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_cygnus_destroyer_mk2, "object/tangible/ship/components/weapon/shared_wpn_cygnus_destroyer_mk2.iff")

object_tangible_ship_components_weapon_shared_wpn_cygnus_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_cygnus_elite_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3038804521,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_cygnus_elite, "object/tangible/ship/components/weapon/shared_wpn_cygnus_elite.iff")

object_tangible_ship_components_weapon_shared_wpn_cygnus_eradicator_1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_cygnus_eradicator_1_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 526650114,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_cygnus_eradicator_1, "object/tangible/ship/components/weapon/shared_wpn_cygnus_eradicator_1.iff")

object_tangible_ship_components_weapon_shared_wpn_freitek_cannoneer_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_freitek_cannoneer_mk1_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 373679875,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_freitek_cannoneer_mk1, "object/tangible/ship/components/weapon/shared_wpn_freitek_cannoneer_mk1.iff")

object_tangible_ship_components_weapon_shared_wpn_generic = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:wpn_generic",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_generic",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1333192542,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_generic, "object/tangible/ship/components/weapon/shared_wpn_generic.iff")

object_tangible_ship_components_weapon_shared_wpn_gyrhil_auto_blaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_gyrhil_auto_blaster_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 90081547,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_gyrhil_auto_blaster, "object/tangible/ship/components/weapon/shared_wpn_gyrhil_auto_blaster.iff")

object_tangible_ship_components_weapon_shared_wpn_gyrhil_r9x = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_gyrhil_r9x_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1218898024,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_gyrhil_r9x, "object/tangible/ship/components/weapon/shared_wpn_gyrhil_r9x.iff")

object_tangible_ship_components_weapon_shared_wpn_haor_chall_speedblaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_haor_chall_speedblaster_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 762044667,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_haor_chall_speedblaster, "object/tangible/ship/components/weapon/shared_wpn_haor_chall_speedblaster.iff")

object_tangible_ship_components_weapon_shared_wpn_hk_modified_scorcher_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_hk_modified_scorcher_elite_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2957562610,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_hk_modified_scorcher_elite, "object/tangible/ship/components/weapon/shared_wpn_hk_modified_scorcher_elite.iff")

object_tangible_ship_components_weapon_shared_wpn_hk_scorcher = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_hk_scorcher_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1555262455,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_hk_scorcher, "object/tangible/ship/components/weapon/shared_wpn_hk_scorcher.iff")

object_tangible_ship_components_weapon_shared_wpn_hk_scorcher_2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_hk_scorcher_2_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2715164541,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_hk_scorcher_2, "object/tangible/ship/components/weapon/shared_wpn_hk_scorcher_2.iff")

object_tangible_ship_components_weapon_shared_wpn_hk_scorcher_3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_hk_scorcher_3_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3906697456,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_hk_scorcher_3, "object/tangible/ship/components/weapon/shared_wpn_hk_scorcher_3.iff")

object_tangible_ship_components_weapon_shared_wpn_hk_scorcher_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_hk_scorcher_advanced_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3110719195,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_hk_scorcher_advanced, "object/tangible/ship/components/weapon/shared_wpn_hk_scorcher_advanced.iff")

object_tangible_ship_components_weapon_shared_wpn_hk_scorcher_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_hk_scorcher_elite_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 146304976,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_hk_scorcher_elite, "object/tangible/ship/components/weapon/shared_wpn_hk_scorcher_elite.iff")

object_tangible_ship_components_weapon_shared_wpn_hk_scorcher_heavy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_hk_scorcher_heavy_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2570101673,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_hk_scorcher_heavy, "object/tangible/ship/components/weapon/shared_wpn_hk_scorcher_heavy.iff")

object_tangible_ship_components_weapon_shared_wpn_incom_advanced_blaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_incom_advanced_blaster_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 939423053,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_incom_advanced_blaster, "object/tangible/ship/components/weapon/shared_wpn_incom_advanced_blaster.iff")

object_tangible_ship_components_weapon_shared_wpn_incom_blaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_incom_blaster_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3446201616,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_incom_blaster, "object/tangible/ship/components/weapon/shared_wpn_incom_blaster.iff")

object_tangible_ship_components_weapon_shared_wpn_incom_disruptor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:weapon_incom_disruptor_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3407371780,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_incom_disruptor, "object/tangible/ship/components/weapon/shared_wpn_incom_disruptor.iff")

object_tangible_ship_components_weapon_shared_wpn_incom_elite_quad_blaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_incom_elite_quad_blaster_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 655771385,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_incom_elite_quad_blaster, "object/tangible/ship/components/weapon/shared_wpn_incom_elite_quad_blaster.iff")

object_tangible_ship_components_weapon_shared_wpn_incom_heavy_blaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_incom_heavy_blaster_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2709580640,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_incom_heavy_blaster, "object/tangible/ship/components/weapon/shared_wpn_incom_heavy_blaster.iff")

object_tangible_ship_components_weapon_shared_wpn_incom_heavy_quad_blaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_incom_heavy_quad_blaster_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4090385282,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_incom_heavy_quad_blaster, "object/tangible/ship/components/weapon/shared_wpn_incom_heavy_quad_blaster.iff")

object_tangible_ship_components_weapon_shared_wpn_incom_light_blaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_incom_light_blaster_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 745205415,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_incom_light_blaster, "object/tangible/ship/components/weapon/shared_wpn_incom_light_blaster.iff")

object_tangible_ship_components_weapon_shared_wpn_incom_proton_missile_s01 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/missile_proton_torpedo_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:weapon_test_01_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:weapon_test_01_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2585546139,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_incom_proton_missile_s01, "object/tangible/ship/components/weapon/shared_wpn_incom_proton_missile_s01.iff")

object_tangible_ship_components_weapon_shared_wpn_incom_quad_blaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_incom_quad_blaster_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2691880126,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_incom_quad_blaster, "object/tangible/ship/components/weapon/shared_wpn_incom_quad_blaster.iff")

object_tangible_ship_components_weapon_shared_wpn_incom_seismic_missile_s01 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/missile_proton_torpedo_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:weapon_test_01_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:weapon_test_01_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 134787828,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_incom_seismic_missile_s01, "object/tangible/ship/components/weapon/shared_wpn_incom_seismic_missile_s01.iff")

object_tangible_ship_components_weapon_shared_wpn_incom_shredder = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_incom_shredder_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 819793875,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_incom_shredder, "object/tangible/ship/components/weapon/shared_wpn_incom_shredder.iff")

object_tangible_ship_components_weapon_shared_wpn_incom_tt13 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_incom_tt13_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3885305221,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_incom_tt13, "object/tangible/ship/components/weapon/shared_wpn_incom_tt13.iff")

object_tangible_ship_components_weapon_shared_wpn_incom_tt8 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_incom_tt8_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4021441179,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_incom_tt8, "object/tangible/ship/components/weapon/shared_wpn_incom_tt8.iff")

object_tangible_ship_components_weapon_shared_wpn_kdy_pounder_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_kdy_pounder_mk1_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 667601641,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_kdy_pounder_mk1, "object/tangible/ship/components/weapon/shared_wpn_kdy_pounder_mk1.iff")

object_tangible_ship_components_weapon_shared_wpn_kessel_imperial_rendili_prototype_x = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_kessel_imperial_rendili_prototype_x_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1429969329,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_kessel_imperial_rendili_prototype_x, "object/tangible/ship/components/weapon/shared_wpn_kessel_imperial_rendili_prototype_x.iff")

object_tangible_ship_components_weapon_shared_wpn_kessel_imperial_sds_experimental_secret_ops = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_kessel_imperial_sds_experimental_secret_ops_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3083127705,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_kessel_imperial_sds_experimental_secret_ops, "object/tangible/ship/components/weapon/shared_wpn_kessel_imperial_sds_experimental_secret_ops.iff")

object_tangible_ship_components_weapon_shared_wpn_kessel_imperial_sfs_elite_ops = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_kessel_imperial_sfs_elite_ops_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4028755301,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_kessel_imperial_sfs_elite_ops, "object/tangible/ship/components/weapon/shared_wpn_kessel_imperial_sfs_elite_ops.iff")

object_tangible_ship_components_weapon_shared_wpn_kessel_rebel_incom_dualcore_flashcannon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_kessel_rebel_incom_dualcore_flashcannon_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2645130727,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_kessel_rebel_incom_dualcore_flashcannon, "object/tangible/ship/components/weapon/shared_wpn_kessel_rebel_incom_dualcore_flashcannon.iff")

object_tangible_ship_components_weapon_shared_wpn_kessel_rebel_riiz_combine_slammer_cannon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_kessel_rebel_riiz_combine_slammer_cannon_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 89824351,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_kessel_rebel_riiz_combine_slammer_cannon, "object/tangible/ship/components/weapon/shared_wpn_kessel_rebel_riiz_combine_slammer_cannon.iff")

object_tangible_ship_components_weapon_shared_wpn_kessel_rebel_unknown_rayslinger = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_kessel_rebel_unknown_rayslinger_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 953073966,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_kessel_rebel_unknown_rayslinger, "object/tangible/ship/components/weapon/shared_wpn_kessel_rebel_unknown_rayslinger.iff")

object_tangible_ship_components_weapon_shared_wpn_koensayr_deluxe_ion_accelerator = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_koensayr_deluxe_ion_accelerator_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3911315270,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_koensayr_deluxe_ion_accelerator, "object/tangible/ship/components/weapon/shared_wpn_koensayr_deluxe_ion_accelerator.iff")

object_tangible_ship_components_weapon_shared_wpn_koensayr_ion_accelerator = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_koensayr_ion_accelerator_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2517260475,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_koensayr_ion_accelerator, "object/tangible/ship/components/weapon/shared_wpn_koensayr_ion_accelerator.iff")

object_tangible_ship_components_weapon_shared_wpn_koensayr_ion_accelerator_2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_koensayr_ion_accelerator_2_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3827108741,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_koensayr_ion_accelerator_2, "object/tangible/ship/components/weapon/shared_wpn_koensayr_ion_accelerator_2.iff")

object_tangible_ship_components_weapon_shared_wpn_koensayr_ion_accelerator_3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_koensayr_ion_accelerator_3_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2903534600,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_koensayr_ion_accelerator_3, "object/tangible/ship/components/weapon/shared_wpn_koensayr_ion_accelerator_3.iff")

object_tangible_ship_components_weapon_shared_wpn_koensayr_ion_accelerator_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_koensayr_ion_accelerator_advanced_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3935855718,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_koensayr_ion_accelerator_advanced, "object/tangible/ship/components/weapon/shared_wpn_koensayr_ion_accelerator_advanced.iff")

object_tangible_ship_components_weapon_shared_wpn_koensayr_light_disruptor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_koensayr_light_disruptor_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2964865390,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_koensayr_light_disruptor, "object/tangible/ship/components/weapon/shared_wpn_koensayr_light_disruptor.iff")

object_tangible_ship_components_weapon_shared_wpn_koensayr_tuned_light_disruptor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_koensayr_tuned_light_disruptor_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2324723441,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_koensayr_tuned_light_disruptor, "object/tangible/ship/components/weapon/shared_wpn_koensayr_tuned_light_disruptor.iff")

object_tangible_ship_components_weapon_shared_wpn_kse_double_blaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_kse_double_blaster_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1309584223,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_kse_double_blaster, "object/tangible/ship/components/weapon/shared_wpn_kse_double_blaster.iff")

object_tangible_ship_components_weapon_shared_wpn_kse_light_disruptor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_kse_light_disruptor_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1496618540,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_kse_light_disruptor, "object/tangible/ship/components/weapon/shared_wpn_kse_light_disruptor.iff")

object_tangible_ship_components_weapon_shared_wpn_mandal_advanced_annihilator = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_mandal_advanced_annihilator_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1864468167,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_mandal_advanced_annihilator, "object/tangible/ship/components/weapon/shared_wpn_mandal_advanced_annihilator.iff")

object_tangible_ship_components_weapon_shared_wpn_mandal_annihilator_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_mandal_annihilator_mk2_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2171243660,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_mandal_annihilator_mk2, "object/tangible/ship/components/weapon/shared_wpn_mandal_annihilator_mk2.iff")

object_tangible_ship_components_weapon_shared_wpn_mandal_annilhator_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_mandal_annilhator_mk1_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3043215801,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_mandal_annilhator_mk1, "object/tangible/ship/components/weapon/shared_wpn_mandal_annilhator_mk1.iff")

object_tangible_ship_components_weapon_shared_wpn_mandal_elite_annihilator = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_mandal_elite_annihilator_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1203586695,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_mandal_elite_annihilator, "object/tangible/ship/components/weapon/shared_wpn_mandal_elite_annihilator.iff")

object_tangible_ship_components_weapon_shared_wpn_mandal_enhanced_mangler_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_mandal_enhanced_mangler_mk1_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 945058875,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_mandal_enhanced_mangler_mk1, "object/tangible/ship/components/weapon/shared_wpn_mandal_enhanced_mangler_mk1.iff")

object_tangible_ship_components_weapon_shared_wpn_mandal_heavy_annihilator = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_mandal_heavy_annihilator_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4039829327,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_mandal_heavy_annihilator, "object/tangible/ship/components/weapon/shared_wpn_mandal_heavy_annihilator.iff")

object_tangible_ship_components_weapon_shared_wpn_mandal_mangler_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_mandal_mangler_mk1_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3229356354,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_mandal_mangler_mk1, "object/tangible/ship/components/weapon/shared_wpn_mandal_mangler_mk1.iff")

object_tangible_ship_components_weapon_shared_wpn_mandal_qv3_disruptor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_mandal_qv3_disruptor_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2181339101,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_mandal_qv3_disruptor, "object/tangible/ship/components/weapon/shared_wpn_mandal_qv3_disruptor.iff")

object_tangible_ship_components_weapon_shared_wpn_mandal_qv5_disruptor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_mandal_qv5_disruptor_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1168567199,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_mandal_qv5_disruptor, "object/tangible/ship/components/weapon/shared_wpn_mandal_qv5_disruptor.iff")

object_tangible_ship_components_weapon_shared_wpn_mandal_super_mangler = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_mandal_super_mangler_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1966553634,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_mandal_super_mangler, "object/tangible/ship/components/weapon/shared_wpn_mandal_super_mangler.iff")

object_tangible_ship_components_weapon_shared_wpn_mission_reward_imperial_cygnus_starblaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_mission_reward_imperial_cygnus_starblaster_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2216406766,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_mission_reward_imperial_cygnus_starblaster, "object/tangible/ship/components/weapon/shared_wpn_mission_reward_imperial_cygnus_starblaster.iff")

object_tangible_ship_components_weapon_shared_wpn_mission_reward_imperial_sds_boltdriver = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_mission_reward_imperial_sds_boltdriver_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1584266196,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_mission_reward_imperial_sds_boltdriver, "object/tangible/ship/components/weapon/shared_wpn_mission_reward_imperial_sds_boltdriver.iff")

object_tangible_ship_components_weapon_shared_wpn_mission_reward_neutral_borstel_disruptor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_mission_reward_neutral_borstel_disruptor_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1515757719,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_mission_reward_neutral_borstel_disruptor, "object/tangible/ship/components/weapon/shared_wpn_mission_reward_neutral_borstel_disruptor.iff")

object_tangible_ship_components_weapon_shared_wpn_mission_reward_neutral_hk_military_blaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_mission_reward_neutral_hk_military_blaster_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2865416858,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_mission_reward_neutral_hk_military_blaster, "object/tangible/ship/components/weapon/shared_wpn_mission_reward_neutral_hk_military_blaster.iff")

object_tangible_ship_components_weapon_shared_wpn_mission_reward_neutral_mandal_light_blaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_mission_reward_neutral_mandal_light_blaster_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4071002762,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_mission_reward_neutral_mandal_light_blaster, "object/tangible/ship/components/weapon/shared_wpn_mission_reward_neutral_mandal_light_blaster.iff")

object_tangible_ship_components_weapon_shared_wpn_mission_reward_rebel_incom_tricannon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_mission_reward_rebel_incom_tricannon_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3498715160,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_mission_reward_rebel_incom_tricannon, "object/tangible/ship/components/weapon/shared_wpn_mission_reward_rebel_incom_tricannon.iff")

object_tangible_ship_components_weapon_shared_wpn_mission_reward_rebel_taim_ion_driver = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_mission_reward_rebel_taim_ion_driver_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 219326346,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_mission_reward_rebel_taim_ion_driver, "object/tangible/ship/components/weapon/shared_wpn_mission_reward_rebel_taim_ion_driver.iff")

object_tangible_ship_components_weapon_shared_wpn_moncal_light_blaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_moncal_light_blaster_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3697933765,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_moncal_light_blaster, "object/tangible/ship/components/weapon/shared_wpn_moncal_light_blaster.iff")

object_tangible_ship_components_weapon_shared_wpn_prototype_weapon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_prototype",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1904433726,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_prototype_weapon, "object/tangible/ship/components/weapon/shared_wpn_prototype_weapon.iff")

object_tangible_ship_components_weapon_shared_wpn_prototype_weapon_tie = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_prototype",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1097828961,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_prototype_weapon_tie, "object/tangible/ship/components/weapon/shared_wpn_prototype_weapon_tie.iff")

object_tangible_ship_components_weapon_shared_wpn_rendili_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_rendili_advanced_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1966255607,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_rendili_advanced, "object/tangible/ship/components/weapon/shared_wpn_rendili_advanced.iff")

object_tangible_ship_components_weapon_shared_wpn_rendili_fr13_disruptor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_rendili_fr13_disruptor_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 459008853,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_rendili_fr13_disruptor, "object/tangible/ship/components/weapon/shared_wpn_rendili_fr13_disruptor.iff")

object_tangible_ship_components_weapon_shared_wpn_rendili_fr9_disruptor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_rendili_fr9_disruptor_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 100362336,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_rendili_fr9_disruptor, "object/tangible/ship/components/weapon/shared_wpn_rendili_fr9_disruptor.iff")

object_tangible_ship_components_weapon_shared_wpn_rendili_sc3_disruptor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_rendili_sc3_disruptor_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2784983723,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_rendili_sc3_disruptor, "object/tangible/ship/components/weapon/shared_wpn_rendili_sc3_disruptor.iff")

object_tangible_ship_components_weapon_shared_wpn_rendili_sc8_disruptor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_rendili_sc8_disruptor_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 886506152,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_rendili_sc8_disruptor, "object/tangible/ship/components/weapon/shared_wpn_rendili_sc8_disruptor.iff")

object_tangible_ship_components_weapon_shared_wpn_reward_incom_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:wpn_reward",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_reward_incom_elite",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 983721375,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_reward_incom_elite, "object/tangible/ship/components/weapon/shared_wpn_reward_incom_elite.iff")

object_tangible_ship_components_weapon_shared_wpn_reward_seinar_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:wpn_reward",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_reward_seinar_elite",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3491884496,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_reward_seinar_elite, "object/tangible/ship/components/weapon/shared_wpn_reward_seinar_elite.iff")

object_tangible_ship_components_weapon_shared_wpn_reward_slayn_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:wpn_reward",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_reward_slayn_elite",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2898046675,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_reward_slayn_elite, "object/tangible/ship/components/weapon/shared_wpn_reward_slayn_elite.iff")

object_tangible_ship_components_weapon_shared_wpn_reward_subpro_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:wpn_reward",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_reward_subpro_elite",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1280281292,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_reward_subpro_elite, "object/tangible/ship/components/weapon/shared_wpn_reward_subpro_elite.iff")

object_tangible_ship_components_weapon_shared_wpn_reward_taim_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:wpn_reward",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_reward_taim_elite",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2885961571,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_reward_taim_elite, "object/tangible/ship/components/weapon/shared_wpn_reward_taim_elite.iff")

object_tangible_ship_components_weapon_shared_wpn_rss_imperial_cannon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_rss_imperial_cannon_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3583705980,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_rss_imperial_cannon, "object/tangible/ship/components/weapon/shared_wpn_rss_imperial_cannon.iff")

object_tangible_ship_components_weapon_shared_wpn_sds_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_sds_elite_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3939485307,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_sds_elite, "object/tangible/ship/components/weapon/shared_wpn_sds_elite.iff")

object_tangible_ship_components_weapon_shared_wpn_sds_heavy_imperial_spc_forces_cannon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_sds_heavy_imperial_spc_forces_cannon_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1624083757,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_sds_heavy_imperial_spc_forces_cannon, "object/tangible/ship/components/weapon/shared_wpn_sds_heavy_imperial_spc_forces_cannon.iff")

object_tangible_ship_components_weapon_shared_wpn_sds_imperial_blaster_1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_sds_imperial_blaster_1_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3660124331,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_sds_imperial_blaster_1, "object/tangible/ship/components/weapon/shared_wpn_sds_imperial_blaster_1.iff")

object_tangible_ship_components_weapon_shared_wpn_sds_imperial_blaster_2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_sds_imperial_blaster_2_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 20887612,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_sds_imperial_blaster_2, "object/tangible/ship/components/weapon/shared_wpn_sds_imperial_blaster_2.iff")

object_tangible_ship_components_weapon_shared_wpn_sds_imperial_special_forces_cannon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_sds_imperial_special_forces_cannon_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 326500083,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_sds_imperial_special_forces_cannon, "object/tangible/ship/components/weapon/shared_wpn_sds_imperial_special_forces_cannon.iff")

object_tangible_ship_components_weapon_shared_wpn_sds_modified_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_sds_modified_elite_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3416463612,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_sds_modified_elite, "object/tangible/ship/components/weapon/shared_wpn_sds_modified_elite.iff")

object_tangible_ship_components_weapon_shared_wpn_seinar_concussion_missile_s01 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/missile_proton_torpedo_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:weapon_test_01_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:weapon_test_01_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1499653630,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_seinar_concussion_missile_s01, "object/tangible/ship/components/weapon/shared_wpn_seinar_concussion_missile_s01.iff")

object_tangible_ship_components_weapon_shared_wpn_seinar_disruptor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_seinar_disruptor_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3046767372,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_seinar_disruptor, "object/tangible/ship/components/weapon/shared_wpn_seinar_disruptor.iff")

object_tangible_ship_components_weapon_shared_wpn_seinar_heatseeker_missile_s01 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/missile_proton_torpedo_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:weapon_test_01_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:weapon_test_01_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1500305519,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_seinar_heatseeker_missile_s01, "object/tangible/ship/components/weapon/shared_wpn_seinar_heatseeker_missile_s01.iff")

object_tangible_ship_components_weapon_shared_wpn_seinar_ion_cannon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_seinar_ion_cannon_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1847953292,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_seinar_ion_cannon, "object/tangible/ship/components/weapon/shared_wpn_seinar_ion_cannon.iff")

object_tangible_ship_components_weapon_shared_wpn_seinar_linked_cannon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_seinar_linked_cannon_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3708108391,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_seinar_linked_cannon, "object/tangible/ship/components/weapon/shared_wpn_seinar_linked_cannon.iff")

object_tangible_ship_components_weapon_shared_wpn_seinar_ls1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_seinar_ls1_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2396153703,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_seinar_ls1, "object/tangible/ship/components/weapon/shared_wpn_seinar_ls1.iff")

object_tangible_ship_components_weapon_shared_wpn_seinar_ls72 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_seinar_ls72_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4266722432,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_seinar_ls72, "object/tangible/ship/components/weapon/shared_wpn_seinar_ls72.iff")

object_tangible_ship_components_weapon_shared_wpn_sfs_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_sfs_elite_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3844210807,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_sfs_elite, "object/tangible/ship/components/weapon/shared_wpn_sfs_elite.iff")

object_tangible_ship_components_weapon_shared_wpn_sfs_imperial_blaster_1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_sfs_imperial_blaster_1_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1173398646,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_sfs_imperial_blaster_1, "object/tangible/ship/components/weapon/shared_wpn_sfs_imperial_blaster_1.iff")

object_tangible_ship_components_weapon_shared_wpn_sfs_imperial_blaster_2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_sfs_imperial_blaster_2_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2665942241,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_sfs_imperial_blaster_2, "object/tangible/ship/components/weapon/shared_wpn_sfs_imperial_blaster_2.iff")

object_tangible_ship_components_weapon_shared_wpn_sfs_imperial_blaster_3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_sfs_imperial_blaster_3_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3622464364,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_sfs_imperial_blaster_3, "object/tangible/ship/components/weapon/shared_wpn_sfs_imperial_blaster_3.iff")

object_tangible_ship_components_weapon_shared_wpn_sfs_imperial_blaster_4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_sfs_imperial_blaster_4_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 738803832,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_sfs_imperial_blaster_4, "object/tangible/ship/components/weapon/shared_wpn_sfs_imperial_blaster_4.iff")

object_tangible_ship_components_weapon_shared_wpn_sfs_imperial_special_forces_blaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_sfs_imperial_special_forces_blaster_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 994450521,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_sfs_imperial_special_forces_blaster, "object/tangible/ship/components/weapon/shared_wpn_sfs_imperial_special_forces_blaster.iff")

object_tangible_ship_components_weapon_shared_wpn_sfs_improved_imperial_blaster_2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_sfs_improved_imperial_blaster_2_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3810806571,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_sfs_improved_imperial_blaster_2, "object/tangible/ship/components/weapon/shared_wpn_sfs_improved_imperial_blaster_2.iff")

object_tangible_ship_components_weapon_shared_wpn_slayn_deluxe_light_ioncannon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_slayn_deluxe_light_ioncannon_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 674088640,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_slayn_deluxe_light_ioncannon, "object/tangible/ship/components/weapon/shared_wpn_slayn_deluxe_light_ioncannon.iff")

object_tangible_ship_components_weapon_shared_wpn_slayn_imagerec_missile_s01 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/missile_proton_torpedo_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:weapon_test_01_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:weapon_test_01_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3037690567,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_slayn_imagerec_missile_s01, "object/tangible/ship/components/weapon/shared_wpn_slayn_imagerec_missile_s01.iff")

object_tangible_ship_components_weapon_shared_wpn_slayn_ioncannon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:weapon_slayn_ioncannon_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 659233376,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_slayn_ioncannon, "object/tangible/ship/components/weapon/shared_wpn_slayn_ioncannon.iff")

object_tangible_ship_components_weapon_shared_wpn_slayn_light_ioncannon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_slayn_light_ioncannon_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1606284757,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_slayn_light_ioncannon, "object/tangible/ship/components/weapon/shared_wpn_slayn_light_ioncannon.iff")

object_tangible_ship_components_weapon_shared_wpn_spacestation_rebel_turret_s01 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:weapon_turret",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:weapon_turret",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2455152329,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_spacestation_rebel_turret_s01, "object/tangible/ship/components/weapon/shared_wpn_spacestation_rebel_turret_s01.iff")

object_tangible_ship_components_weapon_shared_wpn_spacestation_rebel_turret_s02 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:weapon_turret",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:weapon_turret",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1229000286,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_spacestation_rebel_turret_s02, "object/tangible/ship/components/weapon/shared_wpn_spacestation_rebel_turret_s02.iff")

object_tangible_ship_components_weapon_shared_wpn_star_destroyer_turret_dome = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:star_destroyer_dome_turret",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:star_destroyer_dome_turret",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3564769891,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_star_destroyer_turret_dome, "object/tangible/ship/components/weapon/shared_wpn_star_destroyer_turret_dome.iff")

object_tangible_ship_components_weapon_shared_wpn_star_destroyer_turret_med = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:star_destroyer_med_turret",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:star_destroyer_med_turret",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 52712658,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_star_destroyer_turret_med, "object/tangible/ship/components/weapon/shared_wpn_star_destroyer_turret_med.iff")

object_tangible_ship_components_weapon_shared_wpn_star_destroyer_turret_square = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:star_destroyer_square_turret",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:star_destroyer_square_turret",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1162390806,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_star_destroyer_turret_square, "object/tangible/ship/components/weapon/shared_wpn_star_destroyer_turret_square.iff")

object_tangible_ship_components_weapon_shared_wpn_std_countermeasure = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:wpn_std_countermeasure",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_std_countermeasure",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1265550250,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_std_countermeasure, "object/tangible/ship/components/weapon/shared_wpn_std_countermeasure.iff")

object_tangible_ship_components_weapon_shared_wpn_subpro_advanced_cannon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_subpro_advanced_cannon_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4160278616,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_subpro_advanced_cannon, "object/tangible/ship/components/weapon/shared_wpn_subpro_advanced_cannon.iff")

object_tangible_ship_components_weapon_shared_wpn_subpro_improved_light_ioncannon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_subpro_improved_light_ioncannon_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2401708828,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_subpro_improved_light_ioncannon, "object/tangible/ship/components/weapon/shared_wpn_subpro_improved_light_ioncannon.iff")

object_tangible_ship_components_weapon_shared_wpn_subpro_light_ioncannon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_subpro_light_ioncannon_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3317340182,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_subpro_light_ioncannon, "object/tangible/ship/components/weapon/shared_wpn_subpro_light_ioncannon.iff")

object_tangible_ship_components_weapon_shared_wpn_subpro_modified_tricannon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_subpro_modified_tricannon_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1471920679,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_subpro_modified_tricannon, "object/tangible/ship/components/weapon/shared_wpn_subpro_modified_tricannon.iff")

object_tangible_ship_components_weapon_shared_wpn_subpro_tricannon = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_subpro_tricannon_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1320399548,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_subpro_tricannon, "object/tangible/ship/components/weapon/shared_wpn_subpro_tricannon.iff")

object_tangible_ship_components_weapon_shared_wpn_subpro_tripleblaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:weapon_subpro_tripleblaster_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3508512617,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_subpro_tripleblaster, "object/tangible/ship/components/weapon/shared_wpn_subpro_tripleblaster.iff")

object_tangible_ship_components_weapon_shared_wpn_subpro_tripleblaster_mark2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_subpro_tripleblaster_mark2_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 449709518,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_subpro_tripleblaster_mark2, "object/tangible/ship/components/weapon/shared_wpn_subpro_tripleblaster_mark2.iff")

object_tangible_ship_components_weapon_shared_wpn_subpro_tripleblaster_mark3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_subpro_tripleblaster_mark3_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1405313603,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_subpro_tripleblaster_mark3, "object/tangible/ship/components/weapon/shared_wpn_subpro_tripleblaster_mark3.iff")

object_tangible_ship_components_weapon_shared_wpn_taim_elite = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_taim_elite_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3622160774,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_taim_elite, "object/tangible/ship/components/weapon/shared_wpn_taim_elite.iff")

object_tangible_ship_components_weapon_shared_wpn_taim_heavy_laser = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_taim_heavy_laser_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1640800907,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_taim_heavy_laser, "object/tangible/ship/components/weapon/shared_wpn_taim_heavy_laser.iff")

object_tangible_ship_components_weapon_shared_wpn_taim_ix4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_taim_ix4_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2408591552,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_taim_ix4, "object/tangible/ship/components/weapon/shared_wpn_taim_ix4.iff")

object_tangible_ship_components_weapon_shared_wpn_taim_ix5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_taim_ix5_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3332200269,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_taim_ix5, "object/tangible/ship/components/weapon/shared_wpn_taim_ix5.iff")

object_tangible_ship_components_weapon_shared_wpn_taim_kx5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_taim_kx5_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1479772015,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_taim_kx5, "object/tangible/ship/components/weapon/shared_wpn_taim_kx5.iff")

object_tangible_ship_components_weapon_shared_wpn_taim_kx8 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_taim_kx8_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1881367655,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_taim_kx8, "object/tangible/ship/components/weapon/shared_wpn_taim_kx8.iff")

object_tangible_ship_components_weapon_shared_wpn_taim_kx9 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_weapon_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_taim_kx9_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 959316970,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_taim_kx9, "object/tangible/ship/components/weapon/shared_wpn_taim_kx9.iff")

object_tangible_ship_components_weapon_shared_wpn_tieadvanced_blaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:wpn_tieadvanced_blaster",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_tieadvanced_blaster",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 6623562,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_tieadvanced_blaster, "object/tangible/ship/components/weapon/shared_wpn_tieadvanced_blaster.iff")

object_tangible_ship_components_weapon_shared_wpn_tiefighter_basic = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:wpn_tiefighter_basic_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_tiefighter_basic_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1543754587,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_tiefighter_basic, "object/tangible/ship/components/weapon/shared_wpn_tiefighter_basic.iff")

object_tangible_ship_components_weapon_shared_wpn_z95_basic = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:wpn_z95_basic_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_z95_basic_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4095704307,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_z95_basic, "object/tangible/ship/components/weapon/shared_wpn_z95_basic.iff")

object_tangible_ship_components_weapon_shared_wpn_z95_blaster = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_weapon_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:wpn_z95_blaster",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:wpn_z95_blaster",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3374006977,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_wpn_z95_blaster, "object/tangible/ship/components/weapon/shared_wpn_z95_blaster.iff")

object_tangible_ship_components_weapon_shared_xwing_weapon_s01_test = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/xwing_weapon_neg_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:weapon_test_01_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:weapon_test_01_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4194726205,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_xwing_weapon_s01_test, "object/tangible/ship/components/weapon/shared_xwing_weapon_s01_test.iff")

object_tangible_ship_components_weapon_shared_xwing_weapon_s02_test = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/xwing_weapon_neg_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741829,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:weapon_test_02_d",

	gameObjectType = 1073741829,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:weapon_test_02_n",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2138475555,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_weapon_shared_xwing_weapon_s02_test, "object/tangible/ship/components/weapon/shared_xwing_weapon_s02_test.iff")
