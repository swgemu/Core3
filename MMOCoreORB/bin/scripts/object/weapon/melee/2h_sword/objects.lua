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


object_weapon_melee_2h_sword_shared_2h_sword_battleaxe = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_2h_sword_axe_s01.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_2h_axe",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_2h_axe",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_2h_axe",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 3488117788
}

ObjectTemplates:addTemplate(object_weapon_melee_2h_sword_shared_2h_sword_battleaxe, 3488117788)

object_weapon_melee_2h_sword_shared_2h_sword_battleaxe_quest = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_2h_sword_axe_s01.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_2h_axe_quest",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_2h_axe",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_2h_axe_quest",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 2823273971
}

ObjectTemplates:addTemplate(object_weapon_melee_2h_sword_shared_2h_sword_battleaxe_quest, 2823273971)

object_weapon_melee_2h_sword_shared_2h_sword_blacksun_hack = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_2h_sword_blacksun_hack.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_2h_blacksun_hack",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_2h_blacksun_hack",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_2h_blacksun_hack",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 1699236305
}

ObjectTemplates:addTemplate(object_weapon_melee_2h_sword_shared_2h_sword_blacksun_hack, 1699236305)

object_weapon_melee_2h_sword_shared_2h_sword_cleaver = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_2h_sword_s02.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_2h_cleaver",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_2h_cleaver",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_2h_cleaver",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 1737909268
}

ObjectTemplates:addTemplate(object_weapon_melee_2h_sword_shared_2h_sword_cleaver, 1737909268)

object_weapon_melee_2h_sword_shared_2h_sword_katana = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_2h_sword_s01.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_2h_katana",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_2h_katana",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_2h_katana",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 1688331731
}

ObjectTemplates:addTemplate(object_weapon_melee_2h_sword_shared_2h_sword_katana, 1688331731)

object_weapon_melee_2h_sword_shared_2h_sword_katana_quest = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_2h_sword_s01.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_2h_katana_quest",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_2h_katana",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_2h_katana_quest",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 2213862016
}

ObjectTemplates:addTemplate(object_weapon_melee_2h_sword_shared_2h_sword_katana_quest, 2213862016)

object_weapon_melee_2h_sword_shared_2h_sword_maul = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_2h_sword_maul_s01.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_2h_maul",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_2h_maul",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_2h_maul",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 248141391
}

ObjectTemplates:addTemplate(object_weapon_melee_2h_sword_shared_2h_sword_maul, 248141391)

object_weapon_melee_2h_sword_shared_2h_sword_scythe = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_2h_sword_s03.apt",
	arrangementDescriptors = {"hold_r"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:sword_2h_scythe",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_2h_scythe",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_2h_scythe",
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
	weaponEffectIndex = 0,

	clientObjectCRC = 3006583634
}

ObjectTemplates:addTemplate(object_weapon_melee_2h_sword_shared_2h_sword_scythe, 3006583634)
