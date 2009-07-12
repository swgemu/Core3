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


object_weapon_ranged_rifle_shared_rifle_acid_beam = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_beam_rifle.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_acid_beam",

	gameObjectType = 131078,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_acid_beam",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 39
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_acid_beam, 3329701535)

object_weapon_ranged_rifle_shared_rifle_beam = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_beam_rifle.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_beam",

	gameObjectType = 131084,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_beam",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 7
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_beam, 852163759)

object_weapon_ranged_rifle_shared_rifle_berserker = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_berserker.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_berserker",

	gameObjectType = 131084,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rifle_berserker",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_berserker",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 35
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_berserker, 1604898449)

object_weapon_ranged_rifle_shared_rifle_bowcaster = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_bowcaster.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_bowcaster",

	gameObjectType = 131084,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rifle_bowcaster",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_bowcaster",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 15
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_bowcaster, 2976096139)

object_weapon_ranged_rifle_shared_rifle_cdef = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_dlt20.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_cdef",

	gameObjectType = 131084,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rifle_cdef",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_cdef",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 7
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_cdef, 3496137221)

object_weapon_ranged_rifle_shared_rifle_dlt20 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_dlt20.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_dlt20",

	gameObjectType = 131084,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rifle_dlt20",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_dlt20",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 7
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_dlt20, 1650151261)

object_weapon_ranged_rifle_shared_rifle_dlt20a = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_dlt20.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_dlt20a",

	gameObjectType = 131084,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rifle_dlt20a",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_dlt20a",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 7
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_dlt20a, 2200111432)

object_weapon_ranged_rifle_shared_rifle_e11 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_carbine_e11.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_e11",

	gameObjectType = 131084,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rifle_e11",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_e11",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 9
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_e11, 4027327053)

object_weapon_ranged_rifle_shared_rifle_ewok_crossbow = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_ewok_crossbow.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_ewok_crossbow",

	gameObjectType = 131084,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rifle_ewok_crossbow",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_ewok_crossbow",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 22
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_ewok_crossbow, 917715390)

object_weapon_ranged_rifle_shared_rifle_flame_thrower = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_flamer.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_flame_thrower",

	gameObjectType = 131078,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_flame_thrower",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 21
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_flame_thrower, 3238374228)

object_weapon_ranged_rifle_shared_rifle_jawa_ion = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_jawa_ion.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_jawa_ion",

	gameObjectType = 131084,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rifle_jawa_ion",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_jawa_ion",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 12
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_jawa_ion, 1928416827)

object_weapon_ranged_rifle_shared_rifle_laser = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_laser.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_laser",

	gameObjectType = 131084,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rifle_laser",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_laser",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 7
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_laser, 1390088554)

object_weapon_ranged_rifle_shared_rifle_laser_noob = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_laser.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_laser_noob",

	gameObjectType = 131084,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rifle_laser_noob",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_laser_noob",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 7
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_laser_noob, 378484773)

object_weapon_ranged_rifle_shared_rifle_lightning = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_lightning_cannon.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_lightning",

	gameObjectType = 131078,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_lightning",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "rocket",
	weaponEffectIndex = 3
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_lightning, 708413629)

object_weapon_ranged_rifle_shared_rifle_sg82 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_sg82.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_sg82",

	gameObjectType = 131084,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rifle_sg82",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_sg82",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 13
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_sg82, 3248736753)

object_weapon_ranged_rifle_shared_rifle_spraystick = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_spraystick.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_spraystick",

	gameObjectType = 131084,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rifle_spraystick",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_spraystick",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 16
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_spraystick, 284980584)

object_weapon_ranged_rifle_shared_rifle_t21 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_t21.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_t21",

	gameObjectType = 131084,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rifle_t21",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_t21",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 7
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_t21, 1951509016)

object_weapon_ranged_rifle_shared_rifle_tenloss_dxr6_disruptor_loot = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_carbine_dxr6_combined.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_tenloss_dxr6_disruptor",

	gameObjectType = 131084,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rifle_tenloss_dxr6_disruptor",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_tenloss_dxr6_disruptor",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 34
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_tenloss_dxr6_disruptor_loot, 20961126)

object_weapon_ranged_rifle_shared_rifle_tusken = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_tusken_s01.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_tusken",

	gameObjectType = 131084,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rifle_tusken",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_tusken",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "projectile_rifle",
	weaponEffectIndex = 1
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_tusken, 2874182418)

object_weapon_ranged_rifle_shared_rifle_victor_tusken = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_tusken_s01.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:rifle_victor_tusken",

	gameObjectType = 131084,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:rifle_victor_tusken",

	noBuildRadius = 0,

	objectName = "@weapon_name:rifle_victor_tusken",
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

	useStructureFootprintOutline = 0,

	weaponEffect = "projectile_rifle",
	weaponEffectIndex = 1
}

ObjectTemplates:addTemplate(object_weapon_ranged_rifle_shared_rifle_victor_tusken, 4165527266)
