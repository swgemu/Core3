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


object_tangible_wearables_bodysuit_shared_bodysuit_atat = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/bodysuit/shared_bodysuit_atat.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/bodysuit_atat_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jumpsuit_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777219,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_atat",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:bodysuit_atat",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_atat",
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

	clientObjectCRC = 2562125101,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_jumpsuit_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_bodysuit_shared_bodysuit_atat, "object/tangible/wearables/bodysuit/shared_bodysuit_atat.iff")

object_tangible_wearables_bodysuit_shared_bodysuit_atat_quest = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/bodysuit/shared_bodysuit_atat_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/bodysuit_atat_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jumpsuit_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777219,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_atat_quest",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:bodysuit_atat",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_atat_quest",
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

	clientObjectCRC = 2859919047,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_jumpsuit_longsleeve.iff", "object/tangible/wearables/bodysuit/shared_bodysuit_atat.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_bodysuit_shared_bodysuit_atat_quest, "object/tangible/wearables/bodysuit/shared_bodysuit_atat_quest.iff")

object_tangible_wearables_bodysuit_shared_bodysuit_bwing = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/bodysuit/shared_bodysuit_bwing.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/bodysuit_bwing_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jumpsuit_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777219,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_bwing",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:bodysuit_bwing",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_bwing",
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

	clientObjectCRC = 2920765612,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_jumpsuit_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_bodysuit_shared_bodysuit_bwing, "object/tangible/wearables/bodysuit/shared_bodysuit_bwing.iff")

object_tangible_wearables_bodysuit_shared_bodysuit_bwing_quest = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/bodysuit/shared_bodysuit_bwing_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/bodysuit_bwing_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jumpsuit_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777219,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_bwing_quest",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:bodysuit_bwing",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_bwing_quest",
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

	clientObjectCRC = 2675213661,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_jumpsuit_longsleeve.iff", "object/tangible/wearables/bodysuit/shared_bodysuit_bwing.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_bodysuit_shared_bodysuit_bwing_quest, "object/tangible/wearables/bodysuit/shared_bodysuit_bwing_quest.iff")

object_tangible_wearables_bodysuit_shared_bodysuit_s01 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/bodysuit/shared_bodysuit_s01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/bodysuit_s01_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jumpsuit_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777219,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_s01",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:bodysuit_s01",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_s01",
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

	clientObjectCRC = 3519793019,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_jumpsuit_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_bodysuit_shared_bodysuit_s01, "object/tangible/wearables/bodysuit/shared_bodysuit_s01.iff")

object_tangible_wearables_bodysuit_shared_bodysuit_s06 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/bodysuit/shared_bodysuit_s06.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/bodysuit_s06_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jumpsuit_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777219,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_s06",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:bodysuit_s06",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_s06",
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

	clientObjectCRC = 707325039,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_jumpsuit_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_bodysuit_shared_bodysuit_s06, "object/tangible/wearables/bodysuit/shared_bodysuit_s06.iff")

object_tangible_wearables_bodysuit_shared_bodysuit_s07 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/bodysuit/shared_bodysuit_s07.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/bodysuit_s07_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jumpsuit_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777219,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_s07",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:bodysuit_s07",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_s07",
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

	clientObjectCRC = 1663405026,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_jumpsuit_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_bodysuit_shared_bodysuit_s07, "object/tangible/wearables/bodysuit/shared_bodysuit_s07.iff")

object_tangible_wearables_bodysuit_shared_bodysuit_s08 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/bodysuit/shared_bodysuit_s08.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/bodysuit_s08_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jumpsuit_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777219,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_s08",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:bodysuit_s08",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_s08",
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

	clientObjectCRC = 3643779056,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_jumpsuit_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_bodysuit_shared_bodysuit_s08, "object/tangible/wearables/bodysuit/shared_bodysuit_s08.iff")

object_tangible_wearables_bodysuit_shared_bodysuit_s12 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/bodysuit/shared_bodysuit_s12.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/bodysuit_s12_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jumpsuit_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777219,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_s12",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:bodysuit_s12",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_s12",
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

	clientObjectCRC = 301228692,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_jumpsuit_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_bodysuit_shared_bodysuit_s12, "object/tangible/wearables/bodysuit/shared_bodysuit_s12.iff")

object_tangible_wearables_bodysuit_shared_bodysuit_s13 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/bodysuit/shared_bodysuit_s13.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/bodysuit_s13_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jumpsuit_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777219,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_s13",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:bodysuit_s13",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_s13",
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

	clientObjectCRC = 1492714777,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_jumpsuit_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_bodysuit_shared_bodysuit_s13, "object/tangible/wearables/bodysuit/shared_bodysuit_s13.iff")

object_tangible_wearables_bodysuit_shared_bodysuit_s14 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/bodysuit/shared_bodysuit_s14.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/bodysuit_s14_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jumpsuit_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777219,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_s14",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:bodysuit_s14",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_s14",
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

	clientObjectCRC = 2736401933,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_jumpsuit_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_bodysuit_shared_bodysuit_s14, "object/tangible/wearables/bodysuit/shared_bodysuit_s14.iff")

object_tangible_wearables_bodysuit_shared_bodysuit_s15 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/bodysuit/shared_bodysuit_s15.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/bodysuit_s15_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jumpsuit_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777219,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_s15",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:bodysuit_s15",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_s15",
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

	clientObjectCRC = 3927394688,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_jumpsuit_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_bodysuit_shared_bodysuit_s15, "object/tangible/wearables/bodysuit/shared_bodysuit_s15.iff")

object_tangible_wearables_bodysuit_shared_bodysuit_s16 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/bodysuit/shared_bodysuit_s16.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/bodysuit_s16_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jumpsuit_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777219,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_s16",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:bodysuit_s16",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_s16",
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

	clientObjectCRC = 822141207,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_jumpsuit_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_bodysuit_shared_bodysuit_s16, "object/tangible/wearables/bodysuit/shared_bodysuit_s16.iff")

object_tangible_wearables_bodysuit_shared_bodysuit_sarlacc_coverall = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/bodysuit/shared_bodysuit_sarlacc_coverall.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/bodysuit_s13_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jumpsuit_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777219,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_sarlacc_coverall",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:bodysuit_sarlacc_coverall",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_sarlacc_coverall",
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

	clientObjectCRC = 2416523857,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_jumpsuit_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_bodysuit_shared_bodysuit_sarlacc_coverall, "object/tangible/wearables/bodysuit/shared_bodysuit_sarlacc_coverall.iff")

object_tangible_wearables_bodysuit_shared_bodysuit_tie_fighter = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/bodysuit/shared_bodysuit_tie_fighter.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/bodysuit_tie_fighter_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jumpsuit_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777219,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_tie_fighter",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:bodysuit_tie_fighter",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_tie_fighter",
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

	clientObjectCRC = 19224104,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_jumpsuit_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_bodysuit_shared_bodysuit_tie_fighter, "object/tangible/wearables/bodysuit/shared_bodysuit_tie_fighter.iff")

object_tangible_wearables_bodysuit_shared_bodysuit_tie_fighter_quest = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/bodysuit/shared_bodysuit_tie_fighter_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/bodysuit_tie_fighter_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jumpsuit_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777219,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bodysuit_tie_fighter_quest",

	gameObjectType = 16777219,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:bodysuit_tie_fighter",

	noBuildRadius = 0,

	objectName = "@wearables_name:bodysuit_tie_fighter_quest",
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

	clientObjectCRC = 184136204,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_jumpsuit_longsleeve.iff", "object/tangible/wearables/bodysuit/shared_bodysuit_tie_fighter.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_bodysuit_shared_bodysuit_tie_fighter_quest, "object/tangible/wearables/bodysuit/shared_bodysuit_tie_fighter_quest.iff")
