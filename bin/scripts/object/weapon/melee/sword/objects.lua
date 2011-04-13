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


object_weapon_melee_sword_shared_bestine_quest_sword = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_sword_junti_mace.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
	clientGameObjectType = 131079,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:bestine_quest_sword",

	gameObjectType = 131079,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:bestine_quest_sword",

	noBuildRadius = 0,

	objectName = "@weapon_name:bestine_quest_sword",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 4064578026
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_bestine_quest_sword, "object/weapon/melee/sword/shared_bestine_quest_sword.iff")

object_weapon_melee_sword_shared_sword_01 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_sword_s01.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
	clientGameObjectType = 131079,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_01",

	gameObjectType = 131079,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_01",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_01",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 2166507187
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_01, "object/weapon/melee/sword/shared_sword_01.iff")

object_weapon_melee_sword_shared_sword_01_noob = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_sword_s01.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
	clientGameObjectType = 131079,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_01_noob",

	gameObjectType = 131079,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_01_noob",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_01_noob",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 4026227863
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_01_noob, "object/weapon/melee/sword/shared_sword_01_noob.iff")

object_weapon_melee_sword_shared_sword_02 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_sword_s02.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
	clientGameObjectType = 131079,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_02",

	gameObjectType = 131079,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_02",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_02",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 1513483812
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_02, "object/weapon/melee/sword/shared_sword_02.iff")

object_weapon_melee_sword_shared_sword_blade_ryyk = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_sword_ryyk_blade.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
	clientGameObjectType = 131079,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_blade_ryyk",

	gameObjectType = 131079,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_blade_ryyk",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_blade_ryyk",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 1543947481
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_blade_ryyk, "object/weapon/melee/sword/shared_sword_blade_ryyk.iff")

object_weapon_melee_sword_shared_sword_curved_nyax = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_sword_s02.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
	clientGameObjectType = 131079,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_curved_nyax",

	gameObjectType = 131079,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_02",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_curved_nyax",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 686325746
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_curved_nyax, "object/weapon/melee/sword/shared_sword_curved_nyax.iff")

object_weapon_melee_sword_shared_sword_lightsaber_anakin = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_anakin.lsb",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_anakin.cdf",
	clientGameObjectType = 131080,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_lightsaber_anakin",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_anakin",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_anakin",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 4148631342
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_lightsaber_anakin, "object/weapon/melee/sword/shared_sword_lightsaber_anakin.iff")

object_weapon_melee_sword_shared_sword_lightsaber_andael = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_andael.lsb",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
	clientGameObjectType = 131080,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_lightsaber_andael",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_andael",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_andael",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 214802309
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_lightsaber_andael, "object/weapon/melee/sword/shared_sword_lightsaber_andael.iff")

object_weapon_melee_sword_shared_sword_lightsaber_ben = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_ben.lsb",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
	clientGameObjectType = 131080,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_lightsaber_ben",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_ben",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_ben",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 2309363184
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_lightsaber_ben, "object/weapon/melee/sword/shared_sword_lightsaber_ben.iff")

object_weapon_melee_sword_shared_sword_lightsaber_dugald = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_dugald.lsb",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
	clientGameObjectType = 131080,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_lightsaber_dugald",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_dugald",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_dugald",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 1815706117
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_lightsaber_dugald, "object/weapon/melee/sword/shared_sword_lightsaber_dugald.iff")

object_weapon_melee_sword_shared_sword_lightsaber_leather = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_leather.lsb",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
	clientGameObjectType = 131080,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_lightsaber_leather",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_leather",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_leather",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 3799429195
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_lightsaber_leather, "object/weapon/melee/sword/shared_sword_lightsaber_leather.iff")

object_weapon_melee_sword_shared_sword_lightsaber_luke = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_luke.lsb",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
	clientGameObjectType = 131080,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_lightsaber_luke",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_luke",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_luke",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 672927666
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_lightsaber_luke, "object/weapon/melee/sword/shared_sword_lightsaber_luke.iff")

object_weapon_melee_sword_shared_sword_lightsaber_luke_2h_test = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_luke_2h_test.lsb",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
	clientGameObjectType = 131080,
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

	gameObjectType = 131080,

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
	slotDescriptors = {"default_weapon_ammo_slot", "crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3534521944
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_lightsaber_luke_2h_test, "object/weapon/melee/sword/shared_sword_lightsaber_luke_2h_test.iff")

object_weapon_melee_sword_shared_sword_lightsaber_mace = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_mace.lsb",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
	clientGameObjectType = 131080,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_lightsaber_mace",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_mace",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_mace",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 1964241543
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_lightsaber_mace, "object/weapon/melee/sword/shared_sword_lightsaber_mace.iff")

object_weapon_melee_sword_shared_sword_lightsaber_nebu = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_nebu.lsb",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
	clientGameObjectType = 131080,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_lightsaber_nebu",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_nebu",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_nebu",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 949430622
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_lightsaber_nebu, "object/weapon/melee/sword/shared_sword_lightsaber_nebu.iff")

object_weapon_melee_sword_shared_sword_lightsaber_obi = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_obi.lsb",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
	clientGameObjectType = 131080,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_lightsaber_obi",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_obi",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_obi",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 913289864
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_lightsaber_obi, "object/weapon/melee/sword/shared_sword_lightsaber_obi.iff")

object_weapon_melee_sword_shared_sword_lightsaber_quigon = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_quigon.lsb",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
	clientGameObjectType = 131080,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_lightsaber_quigon",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_quigon",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_quigon",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 2556113704
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_lightsaber_quigon, "object/weapon/melee/sword/shared_sword_lightsaber_quigon.iff")

object_weapon_melee_sword_shared_sword_lightsaber_sleekblack = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_sleekblack.lsb",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
	clientGameObjectType = 131080,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_lightsaber_sleekblack",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_sleekblack",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_sleekblack",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 2429759563
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_lightsaber_sleekblack, "object/weapon/melee/sword/shared_sword_lightsaber_sleekblack.iff")

object_weapon_melee_sword_shared_sword_lightsaber_sleeksilver = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_sleeksilver.lsb",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
	clientGameObjectType = 131080,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_lightsaber_sleeksilver",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_sleeksilver",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_sleeksilver",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 3172079785
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_lightsaber_sleeksilver, "object/weapon/melee/sword/shared_sword_lightsaber_sleeksilver.iff")

object_weapon_melee_sword_shared_sword_lightsaber_vader = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_vader.lsb",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
	clientGameObjectType = 131080,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_lightsaber_vader",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_vader",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_vader",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 2913927315
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_lightsaber_vader, "object/weapon/melee/sword/shared_sword_lightsaber_vader.iff")

object_weapon_melee_sword_shared_sword_nyax = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_sword_s01.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
	clientGameObjectType = 131079,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_nyax",

	gameObjectType = 131079,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_nyax",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_nyax",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 371913339
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_nyax, "object/weapon/melee/sword/shared_sword_nyax.iff")

object_weapon_melee_sword_shared_sword_rantok = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_sword_rantok.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
	clientGameObjectType = 131079,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_blade_rantok",

	gameObjectType = 131079,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_blade_rantok",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_blade_rantok",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 3125045014
}

ObjectTemplates:addClientTemplate(object_weapon_melee_sword_shared_sword_rantok, "object/weapon/melee/sword/shared_sword_rantok.iff")
