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


object_tangible_medicine_shared_antidote_sm_s1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_antidote_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:antidote_sm_s1",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:antidote_sm_s1",

	noBuildRadius = 0,

	objectName = "@medicine_name:antidote_sm_s1",
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

	clientObjectCRC = 1440189415,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_antidote_sm_s1, "object/tangible/medicine/shared_antidote_sm_s1.iff")

object_tangible_medicine_shared_grenade_area_disease = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/pt_healing_grenade.prt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_grenade_area_disease.cdf",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:healing_grenade",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:base_medicine",

	noBuildRadius = 0,

	objectName = "@medicine_name:healing_grenade",
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

	clientObjectCRC = 4251613254,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_grenade_area_disease, "object/tangible/medicine/shared_grenade_area_disease.iff")

object_tangible_medicine_shared_grenade_area_poison = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/pt_healing_grenade.prt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_grenade_area_poison.cdf",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:healing_grenade",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:base_medicine",

	noBuildRadius = 0,

	objectName = "@medicine_name:healing_grenade",
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

	clientObjectCRC = 407306967,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_grenade_area_poison, "object/tangible/medicine/shared_grenade_area_poison.iff")

object_tangible_medicine_shared_grenade_disease = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/pt_healing_grenade.prt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_grenade_disease.cdf",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:healing_grenade",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:base_medicine",

	noBuildRadius = 0,

	objectName = "@medicine_name:healing_grenade",
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

	clientObjectCRC = 1464815996,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_grenade_disease, "object/tangible/medicine/shared_grenade_disease.iff")

object_tangible_medicine_shared_grenade_poison = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/pt_healing_grenade.prt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_grenade_poison.cdf",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:healing_grenade",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:base_medicine",

	noBuildRadius = 0,

	objectName = "@medicine_name:healing_grenade",
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

	clientObjectCRC = 3318575411,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_grenade_poison, "object/tangible/medicine/shared_grenade_poison.iff")

object_tangible_medicine_shared_healing_grenade = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/pt_healing_grenade.prt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_grenade_healing.cdf",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:healing_grenade",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:base_medicine",

	noBuildRadius = 0,

	objectName = "@medicine_name:healing_grenade",
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

	clientObjectCRC = 1436861013,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_healing_grenade, "object/tangible/medicine/shared_healing_grenade.iff")

object_tangible_medicine_shared_healing_grenade_longrange = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/pt_medic_healing_energy_area.prt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_grenade_healing.cdf",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:healing_grenade",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:base_medicine",

	noBuildRadius = 0,

	objectName = "@medicine_name:healing_grenade",
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

	clientObjectCRC = 517120211,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_healing_grenade_longrange, "object/tangible/medicine/shared_healing_grenade_longrange.iff")

object_tangible_medicine_shared_medic_damage = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medic_damage",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medic_damage",

	noBuildRadius = 0,

	objectName = "@medicine_name:medic_damage",
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

	clientObjectCRC = 354709332,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medic_damage, "object/tangible/medicine/shared_medic_damage.iff")

object_tangible_medicine_shared_medikit_tool_advanced = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_medical_console.apt",
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
	containerVolumeLimit = 5,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medic_tool_advanced",

	gameObjectType = 8197,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medic_tool_advanced",

	noBuildRadius = 0,

	objectName = "@medicine_name:medic_tool_advanced",
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

	clientObjectCRC = 1604165582,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medikit_tool_advanced, "object/tangible/medicine/shared_medikit_tool_advanced.iff")

object_tangible_medicine_shared_medikit_tool_basic = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_medical_console.apt",
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
	containerVolumeLimit = 5,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medic_tool",

	gameObjectType = 8197,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medic_tool",

	noBuildRadius = 0,

	objectName = "@medicine_name:medic_tool",
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

	clientObjectCRC = 2114140377,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medikit_tool_basic, "object/tangible/medicine/shared_medikit_tool_basic.iff")

object_tangible_medicine_shared_medpack_blinded = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_m_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medic_blinded",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medic_blinded",

	noBuildRadius = 0,

	objectName = "@medicine_name:medic_blinded",
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

	clientObjectCRC = 765314717,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_blinded, "object/tangible/medicine/shared_medpack_blinded.iff")

object_tangible_medicine_shared_medpack_cure_disease = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_antidote_lg_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medic_cure_disease",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medic_cure_disease",

	noBuildRadius = 0,

	objectName = "@medicine_name:medic_cure_disease",
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

	clientObjectCRC = 3567534855,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_cure_disease, "object/tangible/medicine/shared_medpack_cure_disease.iff")

object_tangible_medicine_shared_medpack_cure_poison = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_antidote_m_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medic_cure_poison",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medic_cure_poison",

	noBuildRadius = 0,

	objectName = "@medicine_name:medic_cure_poison",
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

	clientObjectCRC = 1928193020,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_cure_poison, "object/tangible/medicine/shared_medpack_cure_poison.iff")

object_tangible_medicine_shared_medpack_damage = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medpack_damage",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medpack_damage",

	noBuildRadius = 0,

	objectName = "@medicine_name:medpack_damage",
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

	clientObjectCRC = 1572232451,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_damage, "object/tangible/medicine/shared_medpack_damage.iff")

object_tangible_medicine_shared_medpack_disease_health = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_antidote_lg_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medic_disease_health",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medic_disease_health",

	noBuildRadius = 0,

	objectName = "@medicine_name:medic_disease_health",
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

	clientObjectCRC = 832861899,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_disease_health, "object/tangible/medicine/shared_medpack_disease_health.iff")

object_tangible_medicine_shared_medpack_dizzy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_m_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medic_dizzy",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medic_dizzy",

	noBuildRadius = 0,

	objectName = "@medicine_name:medic_dizzy",
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

	clientObjectCRC = 2465786722,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_dizzy, "object/tangible/medicine/shared_medpack_dizzy.iff")

object_tangible_medicine_shared_medpack_enhance_action = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_antidote_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medpack_enhance_action",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medpack_enhance_action",

	noBuildRadius = 0,

	objectName = "@medicine_name:medpack_enhance_action",
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

	clientObjectCRC = 2933500212,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_enhance_action, "object/tangible/medicine/shared_medpack_enhance_action.iff")

object_tangible_medicine_shared_medpack_enhance_constitution = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_medpack_lg_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medpack_enhance_constitution",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medpack_enhance_constitution",

	noBuildRadius = 0,

	objectName = "@medicine_name:medpack_enhance_constitution",
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

	clientObjectCRC = 4043375021,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_enhance_constitution, "object/tangible/medicine/shared_medpack_enhance_constitution.iff")

object_tangible_medicine_shared_medpack_enhance_health = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_medpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medpack_enhance_health",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medpack_enhance_health",

	noBuildRadius = 0,

	objectName = "@medicine_name:medpack_enhance_health",
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

	clientObjectCRC = 103448599,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_enhance_health, "object/tangible/medicine/shared_medpack_enhance_health.iff")

object_tangible_medicine_shared_medpack_enhance_quickness = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_antidote_lg_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medpack_enhance_quickness",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medpack_enhance_quickness",

	noBuildRadius = 0,

	objectName = "@medicine_name:medpack_enhance_quickness",
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

	clientObjectCRC = 1230024376,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_enhance_quickness, "object/tangible/medicine/shared_medpack_enhance_quickness.iff")

object_tangible_medicine_shared_medpack_enhance_stamina = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_medbag_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medpack_enhance_stamina",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medpack_enhance_stamina",

	noBuildRadius = 0,

	objectName = "@medicine_name:medpack_enhance_stamina",
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

	clientObjectCRC = 2141072147,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_enhance_stamina, "object/tangible/medicine/shared_medpack_enhance_stamina.iff")

object_tangible_medicine_shared_medpack_enhance_strength = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_medpack_m_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medpack_enhance_strength",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medpack_enhance_strength",

	noBuildRadius = 0,

	objectName = "@medicine_name:medpack_enhance_strength",
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

	clientObjectCRC = 1816954138,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_enhance_strength, "object/tangible/medicine/shared_medpack_enhance_strength.iff")

object_tangible_medicine_shared_medpack_grenade_area = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_antidote_lg_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medpack_area",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medpack_grenade_area",

	noBuildRadius = 0,

	objectName = "@medicine_name:medpack_grenade_area",
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

	clientObjectCRC = 4052941806,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_grenade_area, "object/tangible/medicine/shared_medpack_grenade_area.iff")

object_tangible_medicine_shared_medpack_grenade_damage = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_antidote_m_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medpack_damage",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medpack_damage",

	noBuildRadius = 0,

	objectName = "@medicine_name:medpack_grenade_damage",
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

	clientObjectCRC = 1050069168,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_grenade_damage, "object/tangible/medicine/shared_medpack_grenade_damage.iff")

object_tangible_medicine_shared_medpack_intimidated = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_m_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medic_intimidated",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medic_intimidated",

	noBuildRadius = 0,

	objectName = "@medicine_name:medic_intimidated",
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

	clientObjectCRC = 3337310390,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_intimidated, "object/tangible/medicine/shared_medpack_intimidated.iff")

object_tangible_medicine_shared_medpack_poison_health = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_antidote_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medic_poison_health",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medic_poison_health",

	noBuildRadius = 0,

	objectName = "@medicine_name:medic_poison_health",
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

	clientObjectCRC = 3017797623,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_poison_health, "object/tangible/medicine/shared_medpack_poison_health.iff")

object_tangible_medicine_shared_medpack_revive = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_medpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medpack_revive",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medpack_revive",

	noBuildRadius = 0,

	objectName = "@medicine_name:medpack_revive",
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

	clientObjectCRC = 4063460611,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_revive, "object/tangible/medicine/shared_medpack_revive.iff")

object_tangible_medicine_shared_medpack_sm_s1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_medpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medpack_sm_s1",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medpack_sm_s1",

	noBuildRadius = 0,

	objectName = "@medicine_name:medpack_sm_s1",
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

	clientObjectCRC = 215922513,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_sm_s1, "object/tangible/medicine/shared_medpack_sm_s1.iff")

object_tangible_medicine_shared_medpack_stunned = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_m_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medic_stunned",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medic_stunned",

	noBuildRadius = 0,

	objectName = "@medicine_name:medic_stunned",
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

	clientObjectCRC = 4041482351,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_stunned, "object/tangible/medicine/shared_medpack_stunned.iff")

object_tangible_medicine_shared_medpack_wound = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_medpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medpack_wound",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medpack_wound",

	noBuildRadius = 0,

	objectName = "@medicine_name:medpack_wound",
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

	clientObjectCRC = 2936514652,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_wound, "object/tangible/medicine/shared_medpack_wound.iff")

object_tangible_medicine_shared_medpack_wound_action = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_antidote_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medpack_wound_action",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medpack_wound_action",

	noBuildRadius = 0,

	objectName = "@medicine_name:medpack_wound_action",
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

	clientObjectCRC = 457349028,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_wound_action, "object/tangible/medicine/shared_medpack_wound_action.iff")

object_tangible_medicine_shared_medpack_wound_constitution = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_medpack_lg_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medpack_wound_constitution",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medpack_wound_constitution",

	noBuildRadius = 0,

	objectName = "@medicine_name:medpack_wound_constitution",
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

	clientObjectCRC = 1021180765,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_wound_constitution, "object/tangible/medicine/shared_medpack_wound_constitution.iff")

object_tangible_medicine_shared_medpack_wound_health = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_medpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medpack_wound_health",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medpack_wound_health",

	noBuildRadius = 0,

	objectName = "@medicine_name:medpack_wound_health",
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

	clientObjectCRC = 3014770311,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_wound_health, "object/tangible/medicine/shared_medpack_wound_health.iff")

object_tangible_medicine_shared_medpack_wound_quickness = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_antidote_lg_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medpack_wound_quickness",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medpack_wound_quickness",

	noBuildRadius = 0,

	objectName = "@medicine_name:medpack_wound_quickness",
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

	clientObjectCRC = 2548119971,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_wound_quickness, "object/tangible/medicine/shared_medpack_wound_quickness.iff")

object_tangible_medicine_shared_medpack_wound_stamina = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_medbag_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medpack_wound_stamina",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medpack_wound_stamina",

	noBuildRadius = 0,

	objectName = "@medicine_name:medpack_wound_stamina",
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

	clientObjectCRC = 1314610438,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_wound_stamina, "object/tangible/medicine/shared_medpack_wound_stamina.iff")

object_tangible_medicine_shared_medpack_wound_strength = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_medpack_m_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medpack_wound_strength",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medpack_wound_strength",

	noBuildRadius = 0,

	objectName = "@medicine_name:medpack_wound_strength",
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

	clientObjectCRC = 2043273277,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_medpack_wound_strength, "object/tangible/medicine/shared_medpack_wound_strength.iff")

object_tangible_medicine_shared_newbie_heal_mission_medicine = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_antidote_m_s1.apt",
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

	detailedDescription = "@item_n:newbie_mission_medicine",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@item_n:newbie_mission_medicine",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2246906578,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_newbie_heal_mission_medicine, "object/tangible/medicine/shared_newbie_heal_mission_medicine.iff")

object_tangible_medicine_shared_stimpack_sm_s1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:stimpack_sm_s1",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:stimpack_sm_s1",

	noBuildRadius = 0,

	objectName = "@medicine_name:stimpack_sm_s1",
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

	clientObjectCRC = 424530466,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_stimpack_sm_s1, "object/tangible/medicine/shared_stimpack_sm_s1.iff")

object_tangible_medicine_shared_test_fire_blanket = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_synthetic_cloth.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8205,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@medicine_detail:medic_fire_blanket",

	gameObjectType = 8205,

	locationReservationRadius = 0,
	lookAtText = "@medicine_lookat:medic_fire_blanket",

	noBuildRadius = 0,

	objectName = "@medicine_name:medic_fire_blanket",
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

	clientObjectCRC = 120135169,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/medicine/base/shared_base_medicine.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_medicine_shared_test_fire_blanket, "object/tangible/medicine/shared_test_fire_blanket.iff")
