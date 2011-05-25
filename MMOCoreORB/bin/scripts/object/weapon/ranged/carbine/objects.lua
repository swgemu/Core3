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


object_weapon_ranged_carbine_shared_carbine_cdef = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_carbine_dh17.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131083,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:carbine_cdef",

	gameObjectType = 131083,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:carbine_cdef",

	noBuildRadius = 0,

	objectName = "@weapon_name:carbine_cdef",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 8,

	clientObjectCRC = 583942574,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/carbine/base/shared_carbine_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_carbine_shared_carbine_cdef, "object/weapon/ranged/carbine/shared_carbine_cdef.iff")

object_weapon_ranged_carbine_shared_carbine_cdef_corsec = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_carbine_dh17.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131083,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:carbine_cdef_corsec",

	gameObjectType = 131083,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:carbine_cdef_corsec",

	noBuildRadius = 0,

	objectName = "@weapon_name:carbine_cdef_corsec",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 8,

	clientObjectCRC = 227072559,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/carbine/base/shared_carbine_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_carbine_shared_carbine_cdef_corsec, "object/weapon/ranged/carbine/shared_carbine_cdef_corsec.iff")

object_weapon_ranged_carbine_shared_carbine_dh17 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_carbine_dh17.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131083,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:carbine_dh17",

	gameObjectType = 131083,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:carbine_dh17",

	noBuildRadius = 0,

	objectName = "@weapon_name:carbine_dh17",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 8,

	clientObjectCRC = 683543232,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/carbine/base/shared_carbine_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_carbine_shared_carbine_dh17, "object/weapon/ranged/carbine/shared_carbine_dh17.iff")

object_weapon_ranged_carbine_shared_carbine_dh17_black = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_carbine_dh17_black.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131083,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:carbine_dh17_black",

	gameObjectType = 131083,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:carbine_dh17_black",

	noBuildRadius = 0,

	objectName = "@weapon_name:carbine_dh17_black",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 8,

	clientObjectCRC = 648744456,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/carbine/base/shared_carbine_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_carbine_shared_carbine_dh17_black, "object/weapon/ranged/carbine/shared_carbine_dh17_black.iff")

object_weapon_ranged_carbine_shared_carbine_dh17_snubnose = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_carbine_dh17_snubnose.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131083,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:carbine_dh17_snubnose",

	gameObjectType = 131083,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:carbine_dh17_snubnose",

	noBuildRadius = 0,

	objectName = "@weapon_name:carbine_dh17_snubnose",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 8,

	clientObjectCRC = 1881783933,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/carbine/base/shared_carbine_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_carbine_shared_carbine_dh17_snubnose, "object/weapon/ranged/carbine/shared_carbine_dh17_snubnose.iff")

object_weapon_ranged_carbine_shared_carbine_dxr6 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_carbine_dxr6.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131083,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:carbine_dxr6",

	gameObjectType = 131083,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:carbine_dxr6",

	noBuildRadius = 0,

	objectName = "@weapon_name:carbine_dxr6",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 10,

	clientObjectCRC = 2050793147,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/carbine/base/shared_carbine_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_carbine_shared_carbine_dxr6, "object/weapon/ranged/carbine/shared_carbine_dxr6.iff")

object_weapon_ranged_carbine_shared_carbine_e11 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_carbine_e11.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131083,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:carbine_e11",

	gameObjectType = 131083,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:carbine_e11",

	noBuildRadius = 0,

	objectName = "@weapon_name:carbine_e11",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 9,

	clientObjectCRC = 3034123480,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/carbine/base/shared_carbine_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_carbine_shared_carbine_e11, "object/weapon/ranged/carbine/shared_carbine_e11.iff")

object_weapon_ranged_carbine_shared_carbine_e11_quest = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_carbine_e11.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131083,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:carbine_e11_quest",

	gameObjectType = 131083,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:carbine_e11",

	noBuildRadius = 0,

	objectName = "@weapon_name:carbine_e11_quest",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 9,

	clientObjectCRC = 861424280,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/carbine/base/shared_carbine_base.iff", "object/weapon/ranged/carbine/shared_carbine_e11.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_carbine_shared_carbine_e11_quest, "object/weapon/ranged/carbine/shared_carbine_e11_quest.iff")

object_weapon_ranged_carbine_shared_carbine_e11_victor_quest = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_carbine_e11.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131083,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:carbine_e11_victor_quest",

	gameObjectType = 131083,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:carbine_e11_victor_quest",

	noBuildRadius = 0,

	objectName = "@weapon_name:carbine_e11_victor_quest",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 28,

	clientObjectCRC = 1297312489,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/carbine/base/shared_carbine_base.iff", "object/weapon/ranged/carbine/shared_carbine_e11.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_carbine_shared_carbine_e11_victor_quest, "object/weapon/ranged/carbine/shared_carbine_e11_victor_quest.iff")

object_weapon_ranged_carbine_shared_carbine_ee3 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_carbine_ee3.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131083,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:carbine_ee3",

	gameObjectType = 131083,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:carbine_ee3",

	noBuildRadius = 0,

	objectName = "@weapon_name:carbine_ee3",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 9,

	clientObjectCRC = 749154215,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/carbine/base/shared_carbine_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_carbine_shared_carbine_ee3, "object/weapon/ranged/carbine/shared_carbine_ee3.iff")

object_weapon_ranged_carbine_shared_carbine_elite = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_carbine_elite.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131083,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:carbine_elite",

	gameObjectType = 131083,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:carbine_elite",

	noBuildRadius = 0,

	objectName = "@weapon_name:carbine_elite",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 5,

	clientObjectCRC = 971375722,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/carbine/base/shared_carbine_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_carbine_shared_carbine_elite, "object/weapon/ranged/carbine/shared_carbine_elite.iff")

object_weapon_ranged_carbine_shared_carbine_laser = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_carbine_laser.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131083,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:carbine_laser",

	gameObjectType = 131083,

	locationReservationRadius = 0,
	lookAtText = "@weapon_name:carbine_laser",

	noBuildRadius = 0,

	objectName = "@weapon_name:carbine_laser",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 5,

	clientObjectCRC = 2121432077,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/carbine/base/shared_carbine_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_carbine_shared_carbine_laser, "object/weapon/ranged/carbine/shared_carbine_laser.iff")

object_weapon_ranged_carbine_shared_carbine_nym_slugthrower = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_carbine_slug_carbine_s01.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131083,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:carbine_nym_slugthrower",

	gameObjectType = 131083,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:carbine_nym_slugthrower",

	noBuildRadius = 0,

	objectName = "@weapon_name:carbine_nym_slugthrower",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "projectile_rifle",
	weaponEffectIndex = 1,

	clientObjectCRC = 1757923070,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/carbine/base/shared_carbine_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_carbine_shared_carbine_nym_slugthrower, "object/weapon/ranged/carbine/shared_carbine_nym_slugthrower.iff")
