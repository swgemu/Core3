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


object_tangible_wearables_helmet_shared_helmet_atat = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/helmet/shared_helmet_atat.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/helmet_atat_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/helmet_closed_full.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 256,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:helmet_atat",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:helmet_atat",

	noBuildRadius = 0,

	objectName = "@wearables_name:helmet_atat",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4140396271,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_armor_base.iff", "object/tangible/wearables/base/shared_base_helmet_closed_full.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_helmet_shared_helmet_atat, "object/tangible/wearables/helmet/shared_helmet_atat.iff")

object_tangible_wearables_helmet_shared_helmet_fighter_blacksun_ace = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/helmet/shared_helmet_fighter_blacksun_ace.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/helmet_fighter_blacksun_m.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/helmet_closed_full.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 256,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:helmet_fighter_blacksun_ace",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:helmet_fighter_blacksun_ace",

	noBuildRadius = 0,

	objectName = "@wearables_name:helmet_fighter_blacksun_ace",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 430117123,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_armor_base.iff", "object/tangible/wearables/base/shared_base_helmet_closed_full.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_helmet_shared_helmet_fighter_blacksun_ace, "object/tangible/wearables/helmet/shared_helmet_fighter_blacksun_ace.iff")

object_tangible_wearables_helmet_shared_helmet_fighter_imperial_ace = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/helmet/shared_helmet_fighter_imperial_ace.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/helmet_fighter_imperial_ace_m.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/helmet_closed_full.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 256,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:helmet_fighter_imperial_ace",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:helmet_fighter_imperial_ace",

	noBuildRadius = 0,

	objectName = "@wearables_name:helmet_fighter_imperial_ace",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2580358001,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_armor_base.iff", "object/tangible/wearables/base/shared_base_helmet_closed_full.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_helmet_shared_helmet_fighter_imperial_ace, "object/tangible/wearables/helmet/shared_helmet_fighter_imperial_ace.iff")

object_tangible_wearables_helmet_shared_helmet_fighter_privateer_ace = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/helmet/shared_helmet_fighter_privateer_ace.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/helmet_fighter_hutt_m.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/helmet_closed_full.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 256,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:helmet_fighter_privateer_ace",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:helmet_fighter_privateer_ace",

	noBuildRadius = 0,

	objectName = "@wearables_name:helmet_fighter_privateer_ace",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1909608537,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_armor_base.iff", "object/tangible/wearables/base/shared_base_helmet_closed_full.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_helmet_shared_helmet_fighter_privateer_ace, "object/tangible/wearables/helmet/shared_helmet_fighter_privateer_ace.iff")

object_tangible_wearables_helmet_shared_helmet_fighter_rebel_ace = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/helmet/shared_helmet_fighter_rebel_ace.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/helmet_fighter_rebel_ace_m.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/helmet_closed_full.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 256,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:helmet_fighter_rebel_ace",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:helmet_fighter_rebel_ace",

	noBuildRadius = 0,

	objectName = "@wearables_name:helmet_fighter_rebel_ace",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4143277653,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_armor_base.iff", "object/tangible/wearables/base/shared_base_helmet_closed_full.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_helmet_shared_helmet_fighter_rebel_ace, "object/tangible/wearables/helmet/shared_helmet_fighter_rebel_ace.iff")

object_tangible_wearables_helmet_shared_helmet_s06 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/helmet/shared_helmet_s06.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/helmet_s06_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/helmet_closed_full.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 256,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:helmet_s06",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:helmet_s06",

	noBuildRadius = 0,

	objectName = "@wearables_name:helmet_s06",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1007682682,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_armor_base.iff", "object/tangible/wearables/base/shared_base_helmet_closed_full.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_helmet_shared_helmet_s06, "object/tangible/wearables/helmet/shared_helmet_s06.iff")

object_tangible_wearables_helmet_shared_helmet_tie_fighter = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/helmet/shared_helmet_tie_fighter.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/helmet_tie_fighter_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/helmet_closed_full.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 256,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:helmet_tie_fighter",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:helmet_tie_fighter",

	noBuildRadius = 0,

	objectName = "@wearables_name:helmet_tie_fighter",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 49314199,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_armor_base.iff", "object/tangible/wearables/base/shared_base_helmet_closed_full.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_helmet_shared_helmet_tie_fighter, "object/tangible/wearables/helmet/shared_helmet_tie_fighter.iff")

object_tangible_wearables_helmet_shared_helmet_tusken_raider_s01 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/helmet/shared_helmet_tusken_raider_s01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/helmet_tusken_raider_s01_m.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/helmet_closed_full.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 256,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:helmet_tusken_raider_s01",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:helmet_tusken_raider_s01",

	noBuildRadius = 0,

	objectName = "@wearables_name:helmet_tusken_raider_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4156063051,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_armor_base.iff", "object/tangible/wearables/base/shared_base_helmet_closed_full.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_helmet_shared_helmet_tusken_raider_s01, "object/tangible/wearables/helmet/shared_helmet_tusken_raider_s01.iff")

object_tangible_wearables_helmet_shared_helmet_tusken_raider_s02 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/helmet/shared_helmet_tusken_raider_s02.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/helmet_tusken_raider_s02_m.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/helmet_closed_full.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 256,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:helmet_tusken_raider_s02",

	gameObjectType = 256,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:helmet_tusken_raider_s02",

	noBuildRadius = 0,

	objectName = "@wearables_name:helmet_tusken_raider_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 749721052,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_armor_base.iff", "object/tangible/wearables/base/shared_base_helmet_closed_full.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_helmet_shared_helmet_tusken_raider_s02, "object/tangible/wearables/helmet/shared_helmet_tusken_raider_s02.iff")
