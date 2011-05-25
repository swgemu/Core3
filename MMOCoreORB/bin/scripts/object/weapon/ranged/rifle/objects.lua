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
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131078,
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 39,

	clientObjectCRC = 3329701535,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_acid_beam, "object/weapon/ranged/rifle/shared_rifle_acid_beam.iff")

object_weapon_ranged_rifle_shared_rifle_beam = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_beam_rifle.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131084,
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 7,

	clientObjectCRC = 852163759,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_beam, "object/weapon/ranged/rifle/shared_rifle_beam.iff")

object_weapon_ranged_rifle_shared_rifle_berserker = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_berserker.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131084,
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 35,

	clientObjectCRC = 1604898449,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_berserker, "object/weapon/ranged/rifle/shared_rifle_berserker.iff")

object_weapon_ranged_rifle_shared_rifle_bowcaster = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_bowcaster.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131084,
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 15,

	clientObjectCRC = 2976096139,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_bowcaster, "object/weapon/ranged/rifle/shared_rifle_bowcaster.iff")

object_weapon_ranged_rifle_shared_rifle_cdef = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_dlt20.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131084,
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 7,

	clientObjectCRC = 3496137221,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_cdef, "object/weapon/ranged/rifle/shared_rifle_cdef.iff")

object_weapon_ranged_rifle_shared_rifle_dlt20 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_dlt20.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131084,
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 7,

	clientObjectCRC = 1650151261,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_dlt20, "object/weapon/ranged/rifle/shared_rifle_dlt20.iff")

object_weapon_ranged_rifle_shared_rifle_dlt20a = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_dlt20.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131084,
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 7,

	clientObjectCRC = 2200111432,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_dlt20a, "object/weapon/ranged/rifle/shared_rifle_dlt20a.iff")

object_weapon_ranged_rifle_shared_rifle_e11 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_carbine_e11.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131084,
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

	clientObjectCRC = 4027327053,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_e11, "object/weapon/ranged/rifle/shared_rifle_e11.iff")

object_weapon_ranged_rifle_shared_rifle_ewok_crossbow = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_ewok_crossbow.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131084,
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 22,

	clientObjectCRC = 917715390,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_ewok_crossbow, "object/weapon/ranged/rifle/shared_rifle_ewok_crossbow.iff")

object_weapon_ranged_rifle_shared_rifle_flame_thrower = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_flamer.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131078,
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 21,

	clientObjectCRC = 3238374228,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_flame_thrower, "object/weapon/ranged/rifle/shared_rifle_flame_thrower.iff")

object_weapon_ranged_rifle_shared_rifle_jawa_ion = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_jawa_ion.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131084,
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 12,

	clientObjectCRC = 1928416827,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_jawa_ion, "object/weapon/ranged/rifle/shared_rifle_jawa_ion.iff")

object_weapon_ranged_rifle_shared_rifle_laser = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_laser.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131084,
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 7,

	clientObjectCRC = 1390088554,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_laser, "object/weapon/ranged/rifle/shared_rifle_laser.iff")

object_weapon_ranged_rifle_shared_rifle_laser_noob = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_laser.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131084,
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 7,

	clientObjectCRC = 378484773,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_laser_noob, "object/weapon/ranged/rifle/shared_rifle_laser_noob.iff")

object_weapon_ranged_rifle_shared_rifle_lightning = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_lightning_cannon.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131078,
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "rocket",
	weaponEffectIndex = 3,

	clientObjectCRC = 708413629,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_lightning, "object/weapon/ranged/rifle/shared_rifle_lightning.iff")

object_weapon_ranged_rifle_shared_rifle_sg82 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_sg82.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131084,
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 13,

	clientObjectCRC = 3248736753,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_sg82, "object/weapon/ranged/rifle/shared_rifle_sg82.iff")

object_weapon_ranged_rifle_shared_rifle_spraystick = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_pistol_spraystick.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131084,
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 16,

	clientObjectCRC = 284980584,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_spraystick, "object/weapon/ranged/rifle/shared_rifle_spraystick.iff")

object_weapon_ranged_rifle_shared_rifle_t21 = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_t21.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131084,
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 7,

	clientObjectCRC = 1951509016,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_t21, "object/weapon/ranged/rifle/shared_rifle_t21.iff")

object_weapon_ranged_rifle_shared_rifle_tenloss_dxr6_disruptor_loot = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_carbine_dxr6_combined.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131084,
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 34,

	clientObjectCRC = 20961126,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_tenloss_dxr6_disruptor_loot, "object/weapon/ranged/rifle/shared_rifle_tenloss_dxr6_disruptor_loot.iff")

object_weapon_ranged_rifle_shared_rifle_tusken = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_tusken_s01.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131084,
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

	clientObjectCRC = 2874182418,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_tusken, "object/weapon/ranged/rifle/shared_rifle_tusken.iff")

object_weapon_ranged_rifle_shared_rifle_victor_tusken = SharedWeaponObjectTemplate:new {
	appearanceFilename = "appearance/wp_rifle_tusken_s01.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_both.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 131084,
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

	clientObjectCRC = 4165527266,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/ranged/rifle/base/shared_rifle_base.iff"}
}

ObjectTemplates:addClientTemplate(object_weapon_ranged_rifle_shared_rifle_victor_tusken, "object/weapon/ranged/rifle/shared_rifle_victor_tusken.iff")
