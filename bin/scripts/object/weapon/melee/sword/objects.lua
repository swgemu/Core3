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
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_bestine_quest_sword, 4064578026)

object_weapon_melee_sword_shared_sword_01 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_sword_s01.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_01, 2166507187)

object_weapon_melee_sword_shared_sword_01_noob = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_sword_s01.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_01_noob, 4026227863)

object_weapon_melee_sword_shared_sword_02 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_sword_s02.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_02, 1513483812)

object_weapon_melee_sword_shared_sword_blade_ryyk = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_sword_ryyk_blade.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_blade_ryyk, 1543947481)

object_weapon_melee_sword_shared_sword_curved_nyax = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_sword_s02.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_curved_nyax, 686325746)

object_weapon_melee_sword_shared_sword_lightsaber_anakin = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_anakin.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_anakin.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_lightsaber_anakin, 4148631342)

object_weapon_melee_sword_shared_sword_lightsaber_andael = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_andael.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_lightsaber_andael, 214802309)

object_weapon_melee_sword_shared_sword_lightsaber_ben = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_ben.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_lightsaber_ben, 2309363184)

object_weapon_melee_sword_shared_sword_lightsaber_dugald = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_dugald.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_lightsaber_dugald, 1815706117)

object_weapon_melee_sword_shared_sword_lightsaber_leather = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_leather.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_lightsaber_leather, 3799429195)

object_weapon_melee_sword_shared_sword_lightsaber_luke = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_luke.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_lightsaber_luke, 672927666)

object_weapon_melee_sword_shared_sword_lightsaber_luke_2h_test = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_luke_2h_test.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_lightsaber_luke_2h_test, 3534521944)

object_weapon_melee_sword_shared_sword_lightsaber_mace = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_mace.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_lightsaber_mace, 1964241543)

object_weapon_melee_sword_shared_sword_lightsaber_nebu = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_nebu.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_lightsaber_nebu, 949430622)

object_weapon_melee_sword_shared_sword_lightsaber_obi = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_obi.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_lightsaber_obi, 913289864)

object_weapon_melee_sword_shared_sword_lightsaber_quigon = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_quigon.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_lightsaber_quigon, 2556113704)

object_weapon_melee_sword_shared_sword_lightsaber_sleekblack = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_sleekblack.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_lightsaber_sleekblack, 2429759563)

object_weapon_melee_sword_shared_sword_lightsaber_sleeksilver = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_sleeksilver.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_lightsaber_sleeksilver, 3172079785)

object_weapon_melee_sword_shared_sword_lightsaber_vader = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_vader.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_lightsaber_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_lightsaber_vader, 2913927315)

object_weapon_melee_sword_shared_sword_nyax = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_sword_s01.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_nyax, 371913339)

object_weapon_melee_sword_shared_sword_rantok = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_sword_rantok.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0
}

ObjectTemplates:addTemplate(object_weapon_melee_sword_shared_sword_rantok, 3125045014)
