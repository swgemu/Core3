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


object_weapon_melee_polearm_shared_lance_controllerfp = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lance_controller.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_metal_lance.cdf",
	clientGameObjectType = 131081,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:lance_controllerfp",

	gameObjectType = 131081,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:lance_controllerfp",

	noBuildRadius = 0,

	objectName = "@weapon_name:lance_controllerfp",
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

	clientObjectCRC = 1316875243
}

ObjectTemplates:addClientTemplate(object_weapon_melee_polearm_shared_lance_controllerfp, "object/weapon/melee/polearm/shared_lance_controllerfp.iff")

object_weapon_melee_polearm_shared_lance_controllerfp_nightsister = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lance_controller.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_metal_lance.cdf",
	clientGameObjectType = 131081,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:lance_controllerfp_nightsister",

	gameObjectType = 131081,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:lance_controllerfp_nightsister",

	noBuildRadius = 0,

	objectName = "@weapon_name:lance_controllerfp_nightsister",
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

	clientObjectCRC = 3796866830
}

ObjectTemplates:addClientTemplate(object_weapon_melee_polearm_shared_lance_controllerfp_nightsister, "object/weapon/melee/polearm/shared_lance_controllerfp_nightsister.iff")

object_weapon_melee_polearm_shared_lance_lightsaber_01 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lance_lightsaber_blade_s01.lsb",
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

	detailedDescription = "@weapon_detail:lance_lightsaber",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@weapon_name:lance_lightsaber",
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

	clientObjectCRC = 3828775483
}

ObjectTemplates:addClientTemplate(object_weapon_melee_polearm_shared_lance_lightsaber_01, "object/weapon/melee/polearm/shared_lance_lightsaber_01.iff")

object_weapon_melee_polearm_shared_lance_lightsaber_02 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lance_lightsaber_blade_s02.lsb",
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

	detailedDescription = "@weapon_detail:lance_lightsaber",

	gameObjectType = 131080,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@weapon_name:lance_lightsaber",
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

	clientObjectCRC = 1059181228
}

ObjectTemplates:addClientTemplate(object_weapon_melee_polearm_shared_lance_lightsaber_02, "object/weapon/melee/polearm/shared_lance_lightsaber_02.iff")

object_weapon_melee_polearm_shared_lance_nightsister = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lance_nightsister.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_nightsister_halberd.cdf",
	clientGameObjectType = 131081,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:lance_nightsister",

	gameObjectType = 131081,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:lance_nightsister",

	noBuildRadius = 0,

	objectName = "@weapon_name:lance_nightsister",
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

	clientObjectCRC = 1613461036
}

ObjectTemplates:addClientTemplate(object_weapon_melee_polearm_shared_lance_nightsister, "object/weapon/melee/polearm/shared_lance_nightsister.iff")

object_weapon_melee_polearm_shared_lance_nightsister_npc_version = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lance_nightsister.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_nightsister_halberd_npc_version.cdf",
	clientGameObjectType = 131081,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:lance_nightsister",

	gameObjectType = 131081,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:lance_nightsister",

	noBuildRadius = 0,

	objectName = "@weapon_name:lance_nightsister",
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

	clientObjectCRC = 770226321
}

ObjectTemplates:addClientTemplate(object_weapon_melee_polearm_shared_lance_nightsister_npc_version, "object/weapon/melee/polearm/shared_lance_nightsister_npc_version.iff")

object_weapon_melee_polearm_shared_lance_staff_janta = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lance_staff_wood_s01.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_wood_lance.cdf",
	clientGameObjectType = 131081,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:lance_staff_janta",

	gameObjectType = 131081,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:lance_staff_janta",

	noBuildRadius = 0,

	objectName = "@weapon_name:lance_staff_janta",
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

	clientObjectCRC = 1705789500
}

ObjectTemplates:addClientTemplate(object_weapon_melee_polearm_shared_lance_staff_janta, "object/weapon/melee/polearm/shared_lance_staff_janta.iff")

object_weapon_melee_polearm_shared_lance_staff_metal = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lance_staff_metal_s01.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_metal_lance.cdf",
	clientGameObjectType = 131081,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:lance_staff_metal",

	gameObjectType = 131081,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:lance_staff_metal",

	noBuildRadius = 0,

	objectName = "@weapon_name:lance_staff_metal",
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

	clientObjectCRC = 978782032
}

ObjectTemplates:addClientTemplate(object_weapon_melee_polearm_shared_lance_staff_metal, "object/weapon/melee/polearm/shared_lance_staff_metal.iff")

object_weapon_melee_polearm_shared_lance_staff_wood_s1 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lance_staff_wood_s01.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_wood_lance.cdf",
	clientGameObjectType = 131081,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:lance_staff_wood_s1",

	gameObjectType = 131081,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:lance_staff_wood_s1",

	noBuildRadius = 0,

	objectName = "@weapon_name:lance_staff_wood_s1",
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

	clientObjectCRC = 1200142292
}

ObjectTemplates:addClientTemplate(object_weapon_melee_polearm_shared_lance_staff_wood_s1, "object/weapon/melee/polearm/shared_lance_staff_wood_s1.iff")

object_weapon_melee_polearm_shared_lance_staff_wood_s2 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lance_staff_wood_s02.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_wood_lance.cdf",
	clientGameObjectType = 131081,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:lance_staff_wood_s2",

	gameObjectType = 131081,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:lance_staff_wood_s2",

	noBuildRadius = 0,

	objectName = "@weapon_name:lance_staff_wood_s2",
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

	clientObjectCRC = 2627673923
}

ObjectTemplates:addClientTemplate(object_weapon_melee_polearm_shared_lance_staff_wood_s2, "object/weapon/melee/polearm/shared_lance_staff_wood_s2.iff")

object_weapon_melee_polearm_shared_lance_vibrolance = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lance_vibrolance.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_polearm_vibro_axe.cdf",
	clientGameObjectType = 131081,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:lance_vibrolance",

	gameObjectType = 131081,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:lance_vibrolance",

	noBuildRadius = 0,

	objectName = "@weapon_name:lance_vibrolance",
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

	clientObjectCRC = 22784428
}

ObjectTemplates:addClientTemplate(object_weapon_melee_polearm_shared_lance_vibrolance, "object/weapon/melee/polearm/shared_lance_vibrolance.iff")

object_weapon_melee_polearm_shared_polearm_vibro_axe = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_mle_lance_vibroaxe.apt",
	arrangementDescriptors = {"hold_r", "hold_l"},
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_polearm_vibro_axe.cdf",
	clientGameObjectType = 131081,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:lance_vibro_axe",

	gameObjectType = 131081,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:lance_vibro_axe",

	noBuildRadius = 0,

	objectName = "@weapon_name:lance_vibro_axe",
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

	clientObjectCRC = 1723256113
}

ObjectTemplates:addClientTemplate(object_weapon_melee_polearm_shared_polearm_vibro_axe, "object/weapon/melee/polearm/shared_polearm_vibro_axe.iff")
