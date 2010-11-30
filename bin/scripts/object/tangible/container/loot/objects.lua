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


object_tangible_container_loot_shared_astromech_container = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/poi_r4_powerdown.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8197,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@container_name:astromech",

	gameObjectType = 8197,

	locationReservationRadius = 0,
	lookAtText = "@container_lookat:base_container",

	noBuildRadius = 0,

	objectName = "@container_name:astromech",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 84456311
}

ObjectTemplates:addClientTemplate(object_tangible_container_loot_shared_astromech_container, "object/tangible/container/loot/shared_astromech_container.iff")

object_tangible_container_loot_shared_computer_container = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_tech_console_sectional_b.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8197,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@container_name:computer",

	gameObjectType = 8197,

	locationReservationRadius = 0,
	lookAtText = "@container_lookat:base_container",

	noBuildRadius = 0,

	objectName = "@container_name:computer",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2996080617
}

ObjectTemplates:addClientTemplate(object_tangible_container_loot_shared_computer_container, "object/tangible/container/loot/shared_computer_container.iff")

object_tangible_container_loot_shared_gas_filter_container = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ins_all_gas_med.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8197,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@container_name:gas_filter",

	gameObjectType = 8197,

	locationReservationRadius = 0,
	lookAtText = "@container_lookat:base_container",

	noBuildRadius = 0,

	objectName = "@container_name:gas_filter",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 349560727
}

ObjectTemplates:addClientTemplate(object_tangible_container_loot_shared_gas_filter_container, "object/tangible/container/loot/shared_gas_filter_container.iff")

object_tangible_container_loot_shared_loot_crate = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_barrel_lg_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8197,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@container_name:loot_crate_d",

	gameObjectType = 8197,

	locationReservationRadius = 0,
	lookAtText = "@container_lookat:base_container",

	noBuildRadius = 0,

	objectName = "@container_name:loot_crate",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1268006083
}

ObjectTemplates:addClientTemplate(object_tangible_container_loot_shared_loot_crate, "object/tangible/container/loot/shared_loot_crate.iff")

object_tangible_container_loot_shared_placable_loot_crate = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/thm_prp_crate_spice.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8197,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@container_name:placable_loot_crate_d",

	gameObjectType = 8197,

	locationReservationRadius = 0,
	lookAtText = "@container_lookat:base_container",

	noBuildRadius = 0,

	objectName = "@container_name:placable_loot_crate",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2362384973
}

ObjectTemplates:addClientTemplate(object_tangible_container_loot_shared_placable_loot_crate, "object/tangible/container/loot/shared_placable_loot_crate.iff")

object_tangible_container_loot_shared_placable_loot_crate_skeleton_bith = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/poi_all_skeleton_bith_headandbody.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8197,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@container_name:placable_loot_crate_skeleton_d",

	gameObjectType = 8197,

	locationReservationRadius = 0,
	lookAtText = "@container_lookat:base_container",

	noBuildRadius = 0,

	objectName = "@container_name:placable_loot_crate_skeleton",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2636682415
}

ObjectTemplates:addClientTemplate(object_tangible_container_loot_shared_placable_loot_crate_skeleton_bith, "object/tangible/container/loot/shared_placable_loot_crate_skeleton_bith.iff")

object_tangible_container_loot_shared_placable_loot_crate_skeleton_human = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/poi_all_skeleton_human_headandbody.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8197,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@container_name:placable_loot_crate_skeleton_d",

	gameObjectType = 8197,

	locationReservationRadius = 0,
	lookAtText = "@container_lookat:base_container",

	noBuildRadius = 0,

	objectName = "@container_name:placable_loot_crate_skeleton",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2665565001
}

ObjectTemplates:addClientTemplate(object_tangible_container_loot_shared_placable_loot_crate_skeleton_human, "object/tangible/container/loot/shared_placable_loot_crate_skeleton_human.iff")

object_tangible_container_loot_shared_placable_loot_crate_skeleton_ithorian = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/poi_all_skeleton_ithorian_headandbody.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8197,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@container_name:placable_loot_crate_skeleton_d",

	gameObjectType = 8197,

	locationReservationRadius = 0,
	lookAtText = "@container_lookat:base_container",

	noBuildRadius = 0,

	objectName = "@container_name:placable_loot_crate_skeleton",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2780389059
}

ObjectTemplates:addClientTemplate(object_tangible_container_loot_shared_placable_loot_crate_skeleton_ithorian, "object/tangible/container/loot/shared_placable_loot_crate_skeleton_ithorian.iff")

object_tangible_container_loot_shared_placable_loot_crate_tech_armoire = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_tech_armoire_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8197,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@container_name:warren_tech_armoire_d",

	gameObjectType = 8197,

	locationReservationRadius = 0,
	lookAtText = "@container_lookat:base_container",

	noBuildRadius = 0,

	objectName = "@container_name:warren_tech_armoire",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2410892657
}

ObjectTemplates:addClientTemplate(object_tangible_container_loot_shared_placable_loot_crate_tech_armoire, "object/tangible/container/loot/shared_placable_loot_crate_tech_armoire.iff")

object_tangible_container_loot_shared_placable_loot_crate_tech_chest = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_tech_chest_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8197,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@container_name:warren_tech_chest_d",

	gameObjectType = 8197,

	locationReservationRadius = 0,
	lookAtText = "@container_lookat:base_container",

	noBuildRadius = 0,

	objectName = "@container_name:warren_tech_chest",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4025920030
}

ObjectTemplates:addClientTemplate(object_tangible_container_loot_shared_placable_loot_crate_tech_chest, "object/tangible/container/loot/shared_placable_loot_crate_tech_chest.iff")

object_tangible_container_loot_shared_placable_loot_crate_trashpile = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/thm_all_imprv_trash_pile_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8197,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@container_name:placable_loot_crate_trashpile_d",

	gameObjectType = 8197,

	locationReservationRadius = 0,
	lookAtText = "@container_lookat:base_container",

	noBuildRadius = 0,

	objectName = "@container_name:placable_loot_crate_trashpile",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2638627675
}

ObjectTemplates:addClientTemplate(object_tangible_container_loot_shared_placable_loot_crate_trashpile, "object/tangible/container/loot/shared_placable_loot_crate_trashpile.iff")

object_tangible_container_loot_shared_player_loot_crate = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_barrel_lg_s1.apt",
	arrangementDescriptors = {},

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

	detailedDescription = "@container_name:locked_loot_crate_d",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@container_name:locked_loot_crate",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3460646661
}

ObjectTemplates:addClientTemplate(object_tangible_container_loot_shared_player_loot_crate, "object/tangible/container/loot/shared_player_loot_crate.iff")
