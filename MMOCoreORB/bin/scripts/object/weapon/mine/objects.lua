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


object_weapon_mine_shared_wp_mine_anti_vehicle = SharedWeaponObjectTemplate:new {
	clientTemplateFileName = "object/weapon/mine/shared_wp_mine_anti_vehicle.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mine_anti_vehicle.apt",
	arrangementDescriptorFilename = "",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_grenade_large_01.cdf",
	clientGameObjectType = 131077,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:mine_a_v",

	gameObjectType = 131077,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:mine_a_v",

	noBuildRadius = 0,

	objectName = "@weapon_name:mine_a_v",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1109205423,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/mine/base/shared_mine_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_mine_shared_wp_mine_anti_vehicle, "object/weapon/mine/shared_wp_mine_anti_vehicle.iff")

object_weapon_mine_shared_wp_mine_drx55 = SharedWeaponObjectTemplate:new {
	clientTemplateFileName = "object/weapon/mine/shared_wp_mine_drx55.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mine_drx55.apt",
	arrangementDescriptorFilename = "",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_grenade_fragmentation.cdf",
	clientGameObjectType = 131077,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:mine_drx",

	gameObjectType = 131077,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:mine_drx",

	noBuildRadius = 0,

	objectName = "@weapon_name:mine_drx",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 1308699589,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/mine/base/shared_mine_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_mine_shared_wp_mine_drx55, "object/weapon/mine/shared_wp_mine_drx55.iff")

object_weapon_mine_shared_wp_mine_xg = SharedWeaponObjectTemplate:new {
	clientTemplateFileName = "object/weapon/mine/shared_wp_mine_xg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/wp_mine_xg.apt",
	arrangementDescriptorFilename = "",
	attackType = 1,

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_grenade_large_02.cdf",
	clientGameObjectType = 131077,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@weapon_detail:mine_xg",

	gameObjectType = 131077,

	locationReservationRadius = 0,
	lookAtText = "@weapon_lookat:mine_xg",

	noBuildRadius = 0,

	objectName = "@weapon_name:mine_xg",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	weaponEffect = "bolt",
	weaponEffectIndex = 0,

	clientObjectCRC = 350273897,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/weapon/base/shared_base_weapon.iff", "object/weapon/ranged/base/shared_base_ranged_weapon.iff", "object/weapon/mine/base/shared_mine_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_weapon_mine_shared_wp_mine_xg, "object/weapon/mine/shared_wp_mine_xg.iff")
