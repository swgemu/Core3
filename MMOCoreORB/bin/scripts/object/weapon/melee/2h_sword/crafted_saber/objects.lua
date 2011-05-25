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


object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_gen1 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_anakin.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen1_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_gen1_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_gen1_2h",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1123043338,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_gen1, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen1.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_gen2 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_anakin.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen2_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_gen2_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_gen2_2h",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 2582110365,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_gen2, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen2.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_gen3 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_anakin.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen3_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_gen3_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_gen3_2h",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3505030928,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_gen3, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen3.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_gen4 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_anakin.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen4_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_gen4_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_gen4_2h",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 722054148,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_gen4, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen4.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_gen5 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_anakin.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen5_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_gen5_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_gen5_2h",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1644481417,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_gen5, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen5.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s1 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_anakin.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3520543309,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s1, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s1.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s10 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_quigon.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1933498416,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s10, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s10.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s10_gen1 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_quigon.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen1_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type10",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 2821972348,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen1.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s10_gen1, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s10_gen1.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s10_gen2 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_quigon.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen2_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type10",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1931758059,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen2.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s10_gen2, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s10_gen2.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s10_gen3 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_quigon.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen3_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type10",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 975777382,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen3.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s10_gen3, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s10_gen3.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s10_gen4 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_quigon.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen4_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type10",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3251242354,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen4.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s10_gen4, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s10_gen4.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s11 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_sleekblack.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 976469949,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s11, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s11.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s11_gen1 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_sleekblack.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen1_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type11",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 681787675,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen1.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s11_gen1, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s11_gen1.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s11_gen2 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_sleekblack.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen2_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type11",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 4088719756,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen2.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s11_gen2, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s11_gen2.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s11_gen3 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_sleekblack.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen3_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type11",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3132722689,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen3.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s11_gen3, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s11_gen3.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s11_gen4 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_sleekblack.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen4_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type11",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1096459541,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen4.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s11_gen4, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s11_gen4.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s12 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_sleeksilver.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3777238826,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s12, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s12.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s12_gen1 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_sleeksilver.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen1_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type12",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 2916334597,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen1.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s12_gen1, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s12_gen1.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s12_gen2 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_sleeksilver.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen2_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type12",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1992561810,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen2.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s12_gen2, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s12_gen2.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s12_gen3 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_sleeksilver.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen3_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type12",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1070166815,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen3.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s12_gen3, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s12_gen3.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s12_gen4 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_sleeksilver.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen4_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type12",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3291109387,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen4.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s12_gen4, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s12_gen4.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s13 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_vader.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 2821288103,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s13, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s13.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s13_gen1 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_vader.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen1_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type13",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 759372898,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen1.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s13_gen1, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s13_gen1.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s13_gen2 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_vader.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen2_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type13",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 4132746485,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen2.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s13_gen2, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s13_gen2.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s13_gen3 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_vader.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen3_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type13",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3210335096,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen3.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s13_gen3, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s13_gen3.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s13_gen4 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_vader.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen4_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type13",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1153103980,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen4.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s13_gen4, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s13_gen4.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s1_gen1 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_anakin.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen1_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1113262465,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen1.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s1_gen1, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s1_gen1.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s1_gen2 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_anakin.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen2_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 2571936022,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen2.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s1_gen2, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s1_gen2.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s1_gen3 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_anakin.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen3_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3493971611,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen3.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s1_gen3, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s1_gen3.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s1_gen4 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_anakin.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen4_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type1",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 732097935,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen4.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s1_gen4, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s1_gen4.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s2 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_andael.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 180392666,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s2, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s2.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s2_gen1 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_andael.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen1_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3341546655,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen1.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s2_gen1, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s2_gen1.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s2_gen2 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_andael.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen2_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 473717768,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen2.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s2_gen2, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s2_gen2.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s2_gen3 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_andael.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen3_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1429289861,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen3.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s2_gen3, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s2_gen3.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s2_gen4 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_andael.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen4_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type2",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 2933002385,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen4.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s2_gen4, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s2_gen4.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s3 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_ben.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1137571159,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s3, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s3.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s3_gen1 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_ben.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen1_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type3",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1203459320,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen1.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s3_gen1, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s3_gen1.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s3_gen2 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_ben.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen2_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type3",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 2628582511,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen2.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s3_gen2, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s3_gen2.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s3_gen3 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_ben.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen3_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type3",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3584138210,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen3.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s3_gen3, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s3_gen3.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s3_gen4 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_ben.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen4_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type3",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 776122614,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen4.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s3_gen4, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s3_gen4.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s4 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_dugald.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3090079299,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s4, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s4.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s4_gen1 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_dugald.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen1_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type4",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3372946196,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen1.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s4_gen1, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s4_gen1.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s4_gen2 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_dugald.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen2_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type4",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 303872899,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen2.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s4_gen2, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s4_gen2.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s4_gen3 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_dugald.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen3_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type4",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1527897102,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen3.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s4_gen3, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s4_gen3.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s4_gen4 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_dugald.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen4_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type4",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 2700277530,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen4.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s4_gen4, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s4_gen4.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s5 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_leather.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 4045650382,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s5, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s5.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s5_gen1 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_leather.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen1_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type5",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1234940787,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen1.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s5_gen1, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s5_gen1.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s5_gen2 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_leather.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen2_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type5",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 2458655716,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen2.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s5_gen2, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s5_gen2.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s5_gen3 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_leather.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen3_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type5",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3682696297,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen3.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s5_gen3, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s5_gen3.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s5_gen4 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_leather.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen4_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type5",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 543315837,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen4.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s5_gen4, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s5_gen4.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s6 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_luke.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 708055385,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s6, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s6.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s6_gen1 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_luke.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen1_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type6",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3437973101,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen1.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s6_gen1, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s6_gen1.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s6_gen2 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_luke.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen2_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type6",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 402450170,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen2.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s6_gen2, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s6_gen2.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s6_gen3 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_luke.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen3_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type6",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1592885623,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen3.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s6_gen3, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s6_gen3.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s6_gen4 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_luke.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen4_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type6",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 2769463907,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen4.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s6_gen4, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s6_gen4.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s7 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_mace.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1664710356,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s7, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s7.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s7_gen1 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_mace.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen1_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type7",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1283190282,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen1.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s7_gen1, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s7_gen1.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s7_gen2 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_mace.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen2_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type7",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 2540455581,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen2.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s7_gen2, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s7_gen2.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s7_gen3 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_mace.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen3_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type7",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3730907408,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen3.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s7_gen3, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s7_gen3.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s7_gen4 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_mace.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen4_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type7",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 629279236,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen4.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s7_gen4, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s7_gen4.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s8 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_nebu.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3644021446,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s8, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s8.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s8_gen1 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_nebu.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen1_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type8",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3578452994,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen1.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s8_gen1, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s8_gen1.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s8_gen2 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_nebu.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen2_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type8",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 241005717,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen2.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s8_gen2, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s8_gen2.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s8_gen3 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_nebu.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen3_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type8",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1196430104,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen3.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s8_gen3, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s8_gen3.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s8_gen4 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_nebu.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen4_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type8",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3165861900,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen4.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s8_gen4, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s8_gen4.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s9 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_obi.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 2419998027,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s9, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s9.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s9_gen1 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_obi.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen1_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type9",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1440382053,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen1.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s9_gen1, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s9_gen1.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s9_gen2 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_obi.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen2_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type9",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 2395854066,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen2.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s9_gen2, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s9_gen2.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s9_gen3 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_obi.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen3_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type9",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3351294847,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen3.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s9_gen3, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s9_gen3.iff")

object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s9_gen4 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lightsaber_blade_obi.lsb",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
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

	detailedDescription = "@weapon_detail:sword_lightsaber_gen4_2h",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:sword_lightsaber_2h",

	noBuildRadius = 0,

	objectName = "@weapon_name:sword_lightsaber_2h_type9",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/default_lightsaber.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1008965739,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_crafted_lightsaber_base.iff", "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_gen4.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_crafted_saber_shared_sword_lightsaber_two_handed_s9_gen4, "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s9_gen4.iff")
