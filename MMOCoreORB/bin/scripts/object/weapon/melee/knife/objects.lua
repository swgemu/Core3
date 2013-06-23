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


object_weapon_melee_knife_shared_knife_dagger = SharedWeaponObjectTemplate:new {
	clientTemplateFileName = "object/weapon/melee/knife/shared_knife_dagger.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mle_knife_dagger.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_knife.cdf",
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

	detailedDescription = "@weapon_detail:knife_dagger",

	gameObjectType = 131079,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:knife_dagger",

	noBuildRadius = 0,

	objectName = "@weapon_name:knife_dagger",
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

	clientObjectCRC = 4040009714,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/sword/base/shared_sword_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_melee_knife_shared_knife_dagger, "object/weapon/melee/knife/shared_knife_dagger.iff")

object_weapon_melee_knife_shared_knife_donkuwah = SharedWeaponObjectTemplate:new {
	clientTemplateFileName = "object/weapon/melee/knife/shared_knife_donkuwah.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mle_knife_stone.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_knife.cdf",
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

	detailedDescription = "@weapon_detail:knife_donkuwah",

	gameObjectType = 131079,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:knife_donkuwah",

	noBuildRadius = 0,

	objectName = "@weapon_name:knife_donkuwah",
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

	clientObjectCRC = 532251396,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/sword/base/shared_sword_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_melee_knife_shared_knife_donkuwah, "object/weapon/melee/knife/shared_knife_donkuwah.iff")

object_weapon_melee_knife_shared_knife_janta = SharedWeaponObjectTemplate:new {
	clientTemplateFileName = "object/weapon/melee/knife/shared_knife_janta.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mle_knife_stone.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_knife.cdf",
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

	detailedDescription = "@weapon_detail:knife_janta",

	gameObjectType = 131079,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:knife_janta",

	noBuildRadius = 0,

	objectName = "@weapon_name:knife_janta",
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

	clientObjectCRC = 2255187692,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/sword/base/shared_sword_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_melee_knife_shared_knife_janta, "object/weapon/melee/knife/shared_knife_janta.iff")

object_weapon_melee_knife_shared_knife_stone = SharedWeaponObjectTemplate:new {
	clientTemplateFileName = "object/weapon/melee/knife/shared_knife_stone.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mle_knife_stone.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_knife.cdf",
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

	detailedDescription = "@weapon_detail:knife_stone",

	gameObjectType = 131079,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:knife_stone",

	noBuildRadius = 0,

	objectName = "@weapon_name:knife_stone",
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

	clientObjectCRC = 1218550121,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/sword/base/shared_sword_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_melee_knife_shared_knife_stone, "object/weapon/melee/knife/shared_knife_stone.iff")

object_weapon_melee_knife_shared_knife_stone_noob = SharedWeaponObjectTemplate:new {
	clientTemplateFileName = "object/weapon/melee/knife/shared_knife_stone_noob.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mle_knife_stone.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_knife.cdf",
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

	detailedDescription = "@weapon_detail:knife_stone_noob",

	gameObjectType = 131079,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:knife_stone_noob",

	noBuildRadius = 0,

	objectName = "@weapon_name:knife_stone_noob",
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

	clientObjectCRC = 1606995338,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/sword/base/shared_sword_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_melee_knife_shared_knife_stone_noob, "object/weapon/melee/knife/shared_knife_stone_noob.iff")

object_weapon_melee_knife_shared_knife_survival = SharedWeaponObjectTemplate:new {
	clientTemplateFileName = "object/weapon/melee/knife/shared_knife_survival.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mle_knife_survival.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_knife.cdf",
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

	detailedDescription = "@weapon_detail:knife_survival",

	gameObjectType = 131079,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:knife_survival",

	noBuildRadius = 0,

	objectName = "@weapon_name:knife_survival",
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

	clientObjectCRC = 530531036,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/sword/base/shared_sword_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_melee_knife_shared_knife_survival, "object/weapon/melee/knife/shared_knife_survival.iff")

object_weapon_melee_knife_shared_knife_vibroblade = SharedWeaponObjectTemplate:new {
	clientTemplateFileName = "object/weapon/melee/knife/shared_knife_vibroblade.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mle_sword_vibroblade.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_small_edged_vibro.cdf",
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

	detailedDescription = "@weapon_detail:knife_vibroblade",

	gameObjectType = 131079,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:knife_vibroblade",

	noBuildRadius = 0,

	objectName = "@weapon_name:knife_vibroblade",
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

	clientObjectCRC = 4211610935,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/sword/base/shared_sword_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_melee_knife_shared_knife_vibroblade, "object/weapon/melee/knife/shared_knife_vibroblade.iff")

object_weapon_melee_knife_shared_knife_vibroblade_quest = SharedWeaponObjectTemplate:new {
	clientTemplateFileName = "object/weapon/melee/knife/shared_knife_vibroblade_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mle_sword_vibroblade.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/weapon/client_melee_small_edged_vibro.cdf",
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

	detailedDescription = "@weapon_detail:knife_vibroblade_quest",

	gameObjectType = 131079,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:knife_vibroblade",

	noBuildRadius = 0,

	objectName = "@weapon_name:knife_vibroblade_quest",
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

	clientObjectCRC = 3270607602,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/melee/base/shared_base_melee.iff", "object/weapon/melee/sword/base/shared_sword_base.iff", "object/weapon/melee/knife/shared_knife_vibroblade.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_melee_knife_shared_knife_vibroblade_quest, "object/weapon/melee/knife/shared_knife_vibroblade_quest.iff")
