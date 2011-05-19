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


object_weapon_ranged_pistol_shared_pistol_cdef = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_cdef.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_cdef",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_cdef",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_cdef",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 6,

	clientObjectCRC = 937103853,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_cdef, "object/weapon/ranged/pistol/shared_pistol_cdef.iff")

object_weapon_ranged_pistol_shared_pistol_cdef_corsec = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_cdef.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_cdef_corsec",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_cdef_corsec",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_cdef_corsec",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 6,

	clientObjectCRC = 1753490887,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_cdef_corsec, "object/weapon/ranged/pistol/shared_pistol_cdef_corsec.iff")

object_weapon_ranged_pistol_shared_pistol_cdef_noob = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_cdef.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_cdef_noob",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_cdef_noob",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_cdef_noob",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 6,

	clientObjectCRC = 3483007032,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_cdef_noob, "object/weapon/ranged/pistol/shared_pistol_cdef_noob.iff")

object_weapon_ranged_pistol_shared_pistol_d18 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_d18.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_d18",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_d18",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_d18",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 6,

	clientObjectCRC = 3466260217,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_d18, "object/weapon/ranged/pistol/shared_pistol_d18.iff")

object_weapon_ranged_pistol_shared_pistol_de_10 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_de10.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_de_10",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_de_10",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_de_10",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 2,

	clientObjectCRC = 3368548007,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_de_10, "object/weapon/ranged/pistol/shared_pistol_de_10.iff")

object_weapon_ranged_pistol_shared_pistol_dh17 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_carbine_dh17.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_dh17",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_dh17",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_dh17",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 8,

	clientObjectCRC = 1034640003,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_dh17, "object/weapon/ranged/pistol/shared_pistol_dh17.iff")

object_weapon_ranged_pistol_shared_pistol_dl44 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_dl44.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_dl44",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_dl44",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_dl44",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 8,

	clientObjectCRC = 2829612927,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_dl44, "object/weapon/ranged/pistol/shared_pistol_dl44.iff")

object_weapon_ranged_pistol_shared_pistol_dl44_metal = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_dl44_metal.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_dl44_metal",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_dl44_metal",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_dl44_metal",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 8,

	clientObjectCRC = 1831044635,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_dl44_metal, "object/weapon/ranged/pistol/shared_pistol_dl44_metal.iff")

object_weapon_ranged_pistol_shared_pistol_dx2 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_dx2.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_dx2",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_dx2",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_dx2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 10,

	clientObjectCRC = 260330479,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_dx2, "object/weapon/ranged/pistol/shared_pistol_dx2.iff")

object_weapon_ranged_pistol_shared_pistol_fwg5 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_fwg5.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_fwg5",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_fwg5",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_fwg5",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 6,

	clientObjectCRC = 1508397938,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_fwg5, "object/weapon/ranged/pistol/shared_pistol_fwg5.iff")

object_weapon_ranged_pistol_shared_pistol_fwg5_quest = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_fwg5.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_fwg5_quest",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_fwg5",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_fwg5_quest",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 6,

	clientObjectCRC = 1350493335,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff", "object/weapon/ranged/pistol/shared_pistol_fwg5.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_fwg5_quest, "object/weapon/ranged/pistol/shared_pistol_fwg5_quest.iff")

object_weapon_ranged_pistol_shared_pistol_geonosian_sonic_blaster_loot = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_geonosian.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_geonosian_sonic_blaster",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_geonosian_sonic_blaster",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_geonosian_sonic_blaster",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 24,

	clientObjectCRC = 2311570538,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_geonosian_sonic_blaster_loot, "object/weapon/ranged/pistol/shared_pistol_geonosian_sonic_blaster_loot.iff")

object_weapon_ranged_pistol_shared_pistol_launcher = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_launcher_pistol.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_launcher",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_launcher",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 17,

	clientObjectCRC = 650380647,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_launcher, "object/weapon/ranged/pistol/shared_pistol_launcher.iff")

object_weapon_ranged_pistol_shared_pistol_power5 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_power5.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_power5",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_power5",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_power5",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 6,

	clientObjectCRC = 148689854,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_power5, "object/weapon/ranged/pistol/shared_pistol_power5.iff")

object_weapon_ranged_pistol_shared_pistol_republic_blaster = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_republic_blaster.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_republic_blaster",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_republic_blaster",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 19,

	clientObjectCRC = 258355020,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_republic_blaster, "object/weapon/ranged/pistol/shared_pistol_republic_blaster.iff")

object_weapon_ranged_pistol_shared_pistol_republic_blaster_quest = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_republic_blaster.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_republic_blaster_quest",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_republic_blaster_quest",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 19,

	clientObjectCRC = 4154566547,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_republic_blaster_quest, "object/weapon/ranged/pistol/shared_pistol_republic_blaster_quest.iff")

object_weapon_ranged_pistol_shared_pistol_scatter = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_scatter_pistol.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_scatter",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_scatter",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 18,

	clientObjectCRC = 3345683635,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_scatter, "object/weapon/ranged/pistol/shared_pistol_scatter.iff")

object_weapon_ranged_pistol_shared_pistol_scout_blaster = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_scout.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_scout_blaster",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_scout_blaster",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_scout_blaster",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 6,

	clientObjectCRC = 3883785442,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_scout_blaster, "object/weapon/ranged/pistol/shared_pistol_scout_blaster.iff")

object_weapon_ranged_pistol_shared_pistol_scout_blaster_ammo_test_2 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/mockup_scoutblaster.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131074,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "string_id_table",

	gameObjectType = 131074,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_weapon",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"test_cartridge_ammo_slot"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1438704896,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_scout_blaster_ammo_test_2, "object/weapon/ranged/pistol/shared_pistol_scout_blaster_ammo_test_2.iff")

object_weapon_ranged_pistol_shared_pistol_scout_blaster_corsec = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_scout.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_scout_blaster_corsec",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_scout_blaster_corsec",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_scout_blaster_corsec",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 6,

	clientObjectCRC = 1727125782,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_scout_blaster_corsec, "object/weapon/ranged/pistol/shared_pistol_scout_blaster_corsec.iff")

object_weapon_ranged_pistol_shared_pistol_srcombat = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_srcombat.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_srcombat",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_srcombat",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_srcombat",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 6,

	clientObjectCRC = 874294352,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_srcombat, "object/weapon/ranged/pistol/shared_pistol_srcombat.iff")

object_weapon_ranged_pistol_shared_pistol_striker = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_striker.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_striker",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_striker",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_striker",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "projectile_pistol",
	weaponEffectIndex = 1,

	clientObjectCRC = 1505820957,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_striker, "object/weapon/ranged/pistol/shared_pistol_striker.iff")

object_weapon_ranged_pistol_shared_pistol_striker_noob = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_striker.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_striker_noob",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_striker_noob",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_striker_noob",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 6,

	clientObjectCRC = 1701084599,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_striker_noob, "object/weapon/ranged/pistol/shared_pistol_striker_noob.iff")

object_weapon_ranged_pistol_shared_pistol_tangle = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_tangle.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131082,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:pistol_tangle",

	gameObjectType = 131082,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:pistol_tangle",

	noBuildRadius = 0,

	objectName = "@weapon_name:pistol_tangle",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "projectile_pistol",
	weaponEffectIndex = 1,

	clientObjectCRC = 2758629867,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/pistol/base/shared_pistol_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_pistol_shared_pistol_tangle, "object/weapon/ranged/pistol/shared_pistol_tangle.iff")
