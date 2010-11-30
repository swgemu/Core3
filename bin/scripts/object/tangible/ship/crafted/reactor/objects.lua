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


object_tangible_ship_crafted_reactor_shared_advanced_fusion_core = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:advanced_fusion_core",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:advanced_fusion_core",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2957310385
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_advanced_fusion_core, "object/tangible/ship/crafted/reactor/shared_advanced_fusion_core.iff")

object_tangible_ship_crafted_reactor_shared_advanced_power_distributor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:advanced_power_distributor",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:advanced_power_distributor",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4065301062
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_advanced_power_distributor, "object/tangible/ship/crafted/reactor/shared_advanced_power_distributor.iff")

object_tangible_ship_crafted_reactor_shared_base_reactor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/cmp_xwing_cowl_neg_s02.apt",
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

	detailedDescription = "@base_reactor:base",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@base_reactor:base",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4073763603
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_base_reactor, "object/tangible/ship/crafted/reactor/shared_base_reactor.iff")

object_tangible_ship_crafted_reactor_shared_base_reactor_subcomponent = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:base_reactor_subcomponent",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_reactor_subcomponent",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2892822392
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_base_reactor_subcomponent, "object/tangible/ship/crafted/reactor/shared_base_reactor_subcomponent.iff")

object_tangible_ship_crafted_reactor_shared_base_reactor_subcomponent_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:base_reactor_subcomponent_mk1",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_reactor_subcomponent_mk1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3936392569
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_base_reactor_subcomponent_mk1, "object/tangible/ship/crafted/reactor/shared_base_reactor_subcomponent_mk1.iff")

object_tangible_ship_crafted_reactor_shared_base_reactor_subcomponent_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:base_reactor_subcomponent_mk2",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_reactor_subcomponent_mk2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 834092526
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_base_reactor_subcomponent_mk2, "object/tangible/ship/crafted/reactor/shared_base_reactor_subcomponent_mk2.iff")

object_tangible_ship_crafted_reactor_shared_base_reactor_subcomponent_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:base_reactor_subcomponent_mk3",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_reactor_subcomponent_mk3",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2025478755
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_base_reactor_subcomponent_mk3, "object/tangible/ship/crafted/reactor/shared_base_reactor_subcomponent_mk3.iff")

object_tangible_ship_crafted_reactor_shared_base_reactor_subcomponent_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:base_reactor_subcomponent_mk4",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_reactor_subcomponent_mk4",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2203677047
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_base_reactor_subcomponent_mk4, "object/tangible/ship/crafted/reactor/shared_base_reactor_subcomponent_mk4.iff")

object_tangible_ship_crafted_reactor_shared_base_reactor_subcomponent_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:base_reactor_subcomponent_mk5",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_reactor_subcomponent_mk5",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3394508538
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_base_reactor_subcomponent_mk5, "object/tangible/ship/crafted/reactor/shared_base_reactor_subcomponent_mk5.iff")

object_tangible_ship_crafted_reactor_shared_basic_reactor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/cmp_xwing_cowl_neg_s02.apt",
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

	detailedDescription = "@space_crafting_n:base_reactor",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:base_reactor",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1900869763
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_basic_reactor, "object/tangible/ship/crafted/reactor/shared_basic_reactor.iff")

object_tangible_ship_crafted_reactor_shared_fusion_reactor_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
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

	detailedDescription = "@space_crafting_d:fusion_reactor_mk1",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:fusion_reactor_mk1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3172827767
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_fusion_reactor_mk1, "object/tangible/ship/crafted/reactor/shared_fusion_reactor_mk1.iff")

object_tangible_ship_crafted_reactor_shared_fusion_reactor_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level3"},
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

	detailedDescription = "@space_crafting_d:fusion_reactor_mk2",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:fusion_reactor_mk2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1711942368
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_fusion_reactor_mk2, "object/tangible/ship/crafted/reactor/shared_fusion_reactor_mk2.iff")

object_tangible_ship_crafted_reactor_shared_fusion_reactor_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level5"},
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

	detailedDescription = "@space_crafting_d:fusion_reactor_mk3",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:fusion_reactor_mk3",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 789007725
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_fusion_reactor_mk3, "object/tangible/ship/crafted/reactor/shared_fusion_reactor_mk3.iff")

object_tangible_ship_crafted_reactor_shared_fusion_reactor_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level7"},
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

	detailedDescription = "@space_crafting_d:fusion_reactor_mk4",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:fusion_reactor_mk4",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3571738233
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_fusion_reactor_mk4, "object/tangible/ship/crafted/reactor/shared_fusion_reactor_mk4.iff")

object_tangible_ship_crafted_reactor_shared_fusion_reactor_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {"cert_ordnance_level9"},
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

	detailedDescription = "@space_crafting_d:fusion_reactor_mk5",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:fusion_reactor_mk5",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2649293300
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_fusion_reactor_mk5, "object/tangible/ship/crafted/reactor/shared_fusion_reactor_mk5.iff")

object_tangible_ship_crafted_reactor_shared_reactor_limiter_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:reactor_limiter_mk1",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:reactor_limiter_mk1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 118151162
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_reactor_limiter_mk1, "object/tangible/ship/crafted/reactor/shared_reactor_limiter_mk1.iff")

object_tangible_ship_crafted_reactor_shared_reactor_limiter_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:reactor_limiter_mk2",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:reactor_limiter_mk2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3692920685
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_reactor_limiter_mk2, "object/tangible/ship/crafted/reactor/shared_reactor_limiter_mk2.iff")

object_tangible_ship_crafted_reactor_shared_reactor_limiter_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:reactor_limiter_mk3",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:reactor_limiter_mk3",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2500860128
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_reactor_limiter_mk3, "object/tangible/ship/crafted/reactor/shared_reactor_limiter_mk3.iff")

object_tangible_ship_crafted_reactor_shared_reactor_limiter_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:reactor_limiter_mk4",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:reactor_limiter_mk4",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1861432308
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_reactor_limiter_mk4, "object/tangible/ship/crafted/reactor/shared_reactor_limiter_mk4.iff")

object_tangible_ship_crafted_reactor_shared_reactor_limiter_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:reactor_limiter_mk5",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:reactor_limiter_mk5",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 670979193
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_reactor_limiter_mk5, "object/tangible/ship/crafted/reactor/shared_reactor_limiter_mk5.iff")

object_tangible_ship_crafted_reactor_shared_reactor_overcharger_mk1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:reactor_overcharger_mk1",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:reactor_overcharger_mk1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1124351052
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_reactor_overcharger_mk1, "object/tangible/ship/crafted/reactor/shared_reactor_overcharger_mk1.iff")

object_tangible_ship_crafted_reactor_shared_reactor_overcharger_mk2 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:reactor_overcharger_mk2",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:reactor_overcharger_mk2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2551420123
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_reactor_overcharger_mk2, "object/tangible/ship/crafted/reactor/shared_reactor_overcharger_mk2.iff")

object_tangible_ship_crafted_reactor_shared_reactor_overcharger_mk3 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:reactor_overcharger_mk3",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:reactor_overcharger_mk3",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3508466518
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_reactor_overcharger_mk3, "object/tangible/ship/crafted/reactor/shared_reactor_overcharger_mk3.iff")

object_tangible_ship_crafted_reactor_shared_reactor_overcharger_mk4 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:reactor_overcharger_mk4",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:reactor_overcharger_mk4",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 721279042
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_reactor_overcharger_mk4, "object/tangible/ship/crafted/reactor/shared_reactor_overcharger_mk4.iff")

object_tangible_ship_crafted_reactor_shared_reactor_overcharger_mk5 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:reactor_overcharger_mk5",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:reactor_overcharger_mk5",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1676722127
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_reactor_overcharger_mk5, "object/tangible/ship/crafted/reactor/shared_reactor_overcharger_mk5.iff")

object_tangible_ship_crafted_reactor_shared_standard_fusion_core = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:standard_fusion_core",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:standard_fusion_core",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3532622984
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_standard_fusion_core, "object/tangible/ship/crafted/reactor/shared_standard_fusion_core.iff")

object_tangible_ship_crafted_reactor_shared_standard_power_distributor = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
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

	detailedDescription = "@space_crafting_d:standard_power_distributor",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_crafting_n:standard_power_distributor",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2827748660
}

ObjectTemplates:addClientTemplate(object_tangible_ship_crafted_reactor_shared_standard_power_distributor, "object/tangible/ship/crafted/reactor/shared_standard_power_distributor.iff")
