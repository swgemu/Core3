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
	clientTemplateFileName = "object/weapon/melee/2h_sword/shared_2h_sword_battleaxe.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mle_2h_sword_axe_s01.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3488117788,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_2h_sword_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_shared_2h_sword_battleaxe, "object/weapon/melee/2h_sword/shared_2h_sword_battleaxe.iff")

object_weapon_melee_2h_sword_shared_2h_sword_battleaxe_quest = SharedWeaponObjectTemplate:new {
	clientTemplateFileName = "object/weapon/melee/2h_sword/shared_2h_sword_battleaxe_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mle_2h_sword_axe_s01.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 2823273971,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_2h_sword_base.iff", "object/weapon/melee/2h_sword/shared_2h_sword_battleaxe.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_shared_2h_sword_battleaxe_quest, "object/weapon/melee/2h_sword/shared_2h_sword_battleaxe_quest.iff")

object_weapon_melee_2h_sword_shared_2h_sword_blacksun_hack = SharedWeaponObjectTemplate:new {
	clientTemplateFileName = "object/weapon/melee/2h_sword/shared_2h_sword_blacksun_hack.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mle_2h_sword_blacksun_hack.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1699236305,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_2h_sword_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_shared_2h_sword_blacksun_hack, "object/weapon/melee/2h_sword/shared_2h_sword_blacksun_hack.iff")

object_weapon_melee_2h_sword_shared_2h_sword_cleaver = SharedWeaponObjectTemplate:new {
	clientTemplateFileName = "object/weapon/melee/2h_sword/shared_2h_sword_cleaver.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mle_2h_sword_s02.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1737909268,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_2h_sword_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_shared_2h_sword_cleaver, "object/weapon/melee/2h_sword/shared_2h_sword_cleaver.iff")

object_weapon_melee_2h_sword_shared_2h_sword_katana = SharedWeaponObjectTemplate:new {
	clientTemplateFileName = "object/weapon/melee/2h_sword/shared_2h_sword_katana.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mle_2h_sword_s01.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1688331731,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_2h_sword_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_shared_2h_sword_katana, "object/weapon/melee/2h_sword/shared_2h_sword_katana.iff")

object_weapon_melee_2h_sword_shared_2h_sword_katana_quest = SharedWeaponObjectTemplate:new {
	clientTemplateFileName = "object/weapon/melee/2h_sword/shared_2h_sword_katana_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mle_2h_sword_s01.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 2213862016,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_2h_sword_base.iff", "object/weapon/melee/2h_sword/shared_2h_sword_katana.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_shared_2h_sword_katana_quest, "object/weapon/melee/2h_sword/shared_2h_sword_katana_quest.iff")

object_weapon_melee_2h_sword_shared_2h_sword_maul = SharedWeaponObjectTemplate:new {
	clientTemplateFileName = "object/weapon/melee/2h_sword/shared_2h_sword_maul.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mle_2h_sword_maul_s01.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 248141391,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_2h_sword_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_shared_2h_sword_maul, "object/weapon/melee/2h_sword/shared_2h_sword_maul.iff")

object_weapon_melee_2h_sword_shared_2h_sword_scythe = SharedWeaponObjectTemplate:new {
	clientTemplateFileName = "object/weapon/melee/2h_sword/shared_2h_sword_scythe.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mle_2h_sword_s03.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_sword_basic.cdf",
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
	slotDescriptorFilename = "abstract/slot/descriptor/default_weapon.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 3006583634,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/2h_sword/base/shared_2h_sword_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_melee_2h_sword_shared_2h_sword_scythe, "object/weapon/melee/2h_sword/shared_2h_sword_scythe.iff")
