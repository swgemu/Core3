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


object_tangible_skill_buff_shared_skill_buff_carbine_accuracy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_blue.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:carbine_accuracy",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:carbine_accuracy",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3070103050,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_carbine_accuracy, "object/tangible/skill_buff/shared_skill_buff_carbine_accuracy.iff")

object_tangible_skill_buff_shared_skill_buff_carbine_speed = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_orange.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:carbine_speed",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:carbine_speed",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2417642005,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_carbine_speed, "object/tangible/skill_buff/shared_skill_buff_carbine_speed.iff")

object_tangible_skill_buff_shared_skill_buff_heavy_weapon_accuracy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_blue.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:heavy_weapon_accuracy",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:heavy_weapon_accuracy",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1148030361,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_heavy_weapon_accuracy, "object/tangible/skill_buff/shared_skill_buff_heavy_weapon_accuracy.iff")

object_tangible_skill_buff_shared_skill_buff_heavy_weapon_speed = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_orange.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:heavy_weapon_speed",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:heavy_weapon_speed",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2003739536,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_heavy_weapon_speed, "object/tangible/skill_buff/shared_skill_buff_heavy_weapon_speed.iff")

object_tangible_skill_buff_shared_skill_buff_mask_scent = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_brown.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:mask_scent",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:mask_scent",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2803312333,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_mask_scent, "object/tangible/skill_buff/shared_skill_buff_mask_scent.iff")

object_tangible_skill_buff_shared_skill_buff_melee_accuracy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_purple.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:melee_accuracy",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:melee_accuracy",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 687567212,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_melee_accuracy, "object/tangible/skill_buff/shared_skill_buff_melee_accuracy.iff")

object_tangible_skill_buff_shared_skill_buff_melee_defense = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_darkblue.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:melee_defense",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:melee_defense",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3148321230,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_melee_defense, "object/tangible/skill_buff/shared_skill_buff_melee_defense.iff")

object_tangible_skill_buff_shared_skill_buff_onehandmelee_accuracy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_purple.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:onehandmelee_accuracy",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:onehandmelee_accuracy",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 336832987,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_onehandmelee_accuracy, "object/tangible/skill_buff/shared_skill_buff_onehandmelee_accuracy.iff")

object_tangible_skill_buff_shared_skill_buff_onehandmelee_speed = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_green.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:onehandmelee_speed",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:onehandmelee_speed",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3043511880,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_onehandmelee_speed, "object/tangible/skill_buff/shared_skill_buff_onehandmelee_speed.iff")

object_tangible_skill_buff_shared_skill_buff_pistol_accuracy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_blue.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:pistol_accuracy",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:pistol_accuracy",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4053673313,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_pistol_accuracy, "object/tangible/skill_buff/shared_skill_buff_pistol_accuracy.iff")

object_tangible_skill_buff_shared_skill_buff_pistol_speed = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_orange.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:pistol_speed",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:pistol_speed",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3705181543,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_pistol_speed, "object/tangible/skill_buff/shared_skill_buff_pistol_speed.iff")

object_tangible_skill_buff_shared_skill_buff_polearm_accuracy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_purple.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:polearm_accuracy",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:polearm_accuracy",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2877612542,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_polearm_accuracy, "object/tangible/skill_buff/shared_skill_buff_polearm_accuracy.iff")

object_tangible_skill_buff_shared_skill_buff_polearm_speed = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_green.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:polearm_speed",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:polearm_speed",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2574942749,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_polearm_speed, "object/tangible/skill_buff/shared_skill_buff_polearm_speed.iff")

object_tangible_skill_buff_shared_skill_buff_ranged_accuracy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_blue.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:ranged_accuracy",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:ranged_accuracy",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2321374102,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_ranged_accuracy, "object/tangible/skill_buff/shared_skill_buff_ranged_accuracy.iff")

object_tangible_skill_buff_shared_skill_buff_ranged_defense = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_darkblue.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:ranged_defense",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:ranged_defense",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 655697476,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_ranged_defense, "object/tangible/skill_buff/shared_skill_buff_ranged_defense.iff")

object_tangible_skill_buff_shared_skill_buff_rifle_accuracy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_blue.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:rifle_accuracy",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:rifle_accuracy",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1676691901,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_rifle_accuracy, "object/tangible/skill_buff/shared_skill_buff_rifle_accuracy.iff")

object_tangible_skill_buff_shared_skill_buff_rifle_speed = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_orange.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:rifle_speed",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:rifle_speed",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1002436514,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_rifle_speed, "object/tangible/skill_buff/shared_skill_buff_rifle_speed.iff")

object_tangible_skill_buff_shared_skill_buff_thrown_accuracy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_darkpurple.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:thrown_accuracy",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:thrown_accuracy",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 675038361,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_thrown_accuracy, "object/tangible/skill_buff/shared_skill_buff_thrown_accuracy.iff")

object_tangible_skill_buff_shared_skill_buff_thrown_speed = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_darkgreen.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:thrown_speed",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:thrown_speed",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2671557576,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_thrown_speed, "object/tangible/skill_buff/shared_skill_buff_thrown_speed.iff")

object_tangible_skill_buff_shared_skill_buff_twohandmelee_accuracy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_purple.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:twohandmelee_accuracy",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:twohandmelee_accuracy",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1962907578,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_twohandmelee_accuracy, "object/tangible/skill_buff/shared_skill_buff_twohandmelee_accuracy.iff")

object_tangible_skill_buff_shared_skill_buff_twohandmelee_speed = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_green.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:twohandmelee_speed",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:twohandmelee_speed",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2007596912,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_twohandmelee_speed, "object/tangible/skill_buff/shared_skill_buff_twohandmelee_speed.iff")

object_tangible_skill_buff_shared_skill_buff_unarmed_accuracy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_purple.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:unarmed_accuracy",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:unarmed_accuracy",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2213257613,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_unarmed_accuracy, "object/tangible/skill_buff/shared_skill_buff_unarmed_accuracy.iff")

object_tangible_skill_buff_shared_skill_buff_unarmed_speed = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/item/client_shared_skill_buff_green.cdf",
	clientGameObjectType = 8218,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@skill_buff_d:unarmed_speed",

	gameObjectType = 8218,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@skill_buff_n:unarmed_speed",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2704330106,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/skill_buff/base/shared_skill_buff_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_skill_buff_shared_skill_buff_unarmed_speed, "object/tangible/skill_buff/shared_skill_buff_unarmed_speed.iff")
