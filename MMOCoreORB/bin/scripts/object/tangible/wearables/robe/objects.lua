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


object_tangible_wearables_robe_shared_aakuan_robe = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_aakuan_robe.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_s05_h0_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/cloak.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777221,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:aakuan_robe",

	gameObjectType = 16777221,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_s05",

	noBuildRadius = 0,

	objectName = "@wearables_name:aakuan_robe",
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

	clientObjectCRC = 518208123,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_cloak.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_aakuan_robe, "object/tangible/wearables/robe/shared_aakuan_robe.iff")

object_tangible_wearables_robe_shared_robe_inquisitor = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_inquisitor.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_inquisitor_m.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/robe_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777229,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_inquisitor",

	gameObjectType = 16777229,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_inquisitor",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_inquisitor",
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

	clientObjectCRC = 3169107890,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_robe_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_inquisitor, "object/tangible/wearables/robe/shared_robe_inquisitor.iff")

object_tangible_wearables_robe_shared_robe_jedi_dark_s01 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_jedi_dark_s01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_jedi_dark_s01_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jedi_jumpsuit.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777221,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_jedi_dark_s01",

	gameObjectType = 16777221,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_jedi_dark_s01",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_jedi_dark_s01",
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

	clientObjectCRC = 3047595977,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_cloak.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_jedi_dark_s01, "object/tangible/wearables/robe/shared_robe_jedi_dark_s01.iff")

object_tangible_wearables_robe_shared_robe_jedi_dark_s02 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_jedi_dark_s02.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_jedi_dark_s02_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jedi_jumpsuit.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777221,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_jedi_dark_s02",

	gameObjectType = 16777221,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_jedi_dark_s02",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_jedi_dark_s02",
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

	clientObjectCRC = 1857107806,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_cloak.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_jedi_dark_s02, "object/tangible/wearables/robe/shared_robe_jedi_dark_s02.iff")

object_tangible_wearables_robe_shared_robe_jedi_dark_s03 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_jedi_dark_s03.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_jedi_dark_s03_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jedi_jumpsuit.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777221,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_jedi_dark_s03",

	gameObjectType = 16777221,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_jedi_dark_s03",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_jedi_dark_s03",
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

	clientObjectCRC = 666652883,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_cloak.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_jedi_dark_s03, "object/tangible/wearables/robe/shared_robe_jedi_dark_s03.iff")

object_tangible_wearables_robe_shared_robe_jedi_dark_s04 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_jedi_dark_s04.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_jedi_dark_s04_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jedi_jumpsuit.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777221,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_jedi_dark_s04",

	gameObjectType = 16777221,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_jedi_dark_s04",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_jedi_dark_s04",
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

	clientObjectCRC = 3697245127,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_cloak.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_jedi_dark_s04, "object/tangible/wearables/robe/shared_robe_jedi_dark_s04.iff")

object_tangible_wearables_robe_shared_robe_jedi_dark_s05 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_jedi_dark_s05.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_jedi_dark_s05_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jedi_robe.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777221,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_jedi_dark_s05",

	gameObjectType = 16777221,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_jedi_dark_s05",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_jedi_dark_s05",
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

	clientObjectCRC = 2505186378,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_cloak.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_jedi_dark_s05, "object/tangible/wearables/robe/shared_robe_jedi_dark_s05.iff")

object_tangible_wearables_robe_shared_robe_jedi_light_s01 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_jedi_light_s01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_jedi_light_s01_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jedi_jumpsuit.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777221,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_jedi_light_s01",

	gameObjectType = 16777221,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_jedi_light_s01",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_jedi_light_s01",
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

	clientObjectCRC = 3064236439,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_cloak.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_jedi_light_s01, "object/tangible/wearables/robe/shared_robe_jedi_light_s01.iff")

object_tangible_wearables_robe_shared_robe_jedi_light_s02 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_jedi_light_s02.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_jedi_light_s02_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jedi_jumpsuit.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777221,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_jedi_light_s02",

	gameObjectType = 16777221,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_jedi_light_s02",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_jedi_light_s02",
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

	clientObjectCRC = 1840455936,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_cloak.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_jedi_light_s02, "object/tangible/wearables/robe/shared_robe_jedi_light_s02.iff")

object_tangible_wearables_robe_shared_robe_jedi_light_s03 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_jedi_light_s03.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_jedi_light_s03_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jedi_jumpsuit.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777221,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_jedi_light_s03",

	gameObjectType = 16777221,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_jedi_light_s03",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_jedi_light_s03",
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

	clientObjectCRC = 616449677,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_cloak.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_jedi_light_s03, "object/tangible/wearables/robe/shared_robe_jedi_light_s03.iff")

object_tangible_wearables_robe_shared_robe_jedi_light_s04 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_jedi_light_s04.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_jedi_light_s04_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jedi_jumpsuit.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777221,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_jedi_light_s04",

	gameObjectType = 16777221,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_jedi_light_s04",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_jedi_light_s04",
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

	clientObjectCRC = 3747442073,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_cloak.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_jedi_light_s04, "object/tangible/wearables/robe/shared_robe_jedi_light_s04.iff")

object_tangible_wearables_robe_shared_robe_jedi_light_s05 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_jedi_light_s05.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_jedi_light_s05_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jedi_robe.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777221,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_jedi_light_s05",

	gameObjectType = 16777221,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_jedi_light_s05",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_jedi_light_s05",
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

	clientObjectCRC = 2521827860,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_cloak.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_jedi_light_s05, "object/tangible/wearables/robe/shared_robe_jedi_light_s05.iff")

object_tangible_wearables_robe_shared_robe_jedi_padawan = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_jedi_padawan.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_jedi_padawan_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/jedi_jumpsuit.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777221,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_jedi_padawan",

	gameObjectType = 16777221,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_jedi_padawan",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_jedi_padawan",
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

	clientObjectCRC = 901202930,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_cloak.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_jedi_padawan, "object/tangible/wearables/robe/shared_robe_jedi_padawan.iff")

object_tangible_wearables_robe_shared_robe_jedi_test = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_jedi_test.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_s05_h0_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/cloak.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777221,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_s05",

	gameObjectType = 16777221,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_s05",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_s05",
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

	clientObjectCRC = 2041848180,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_cloak.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_jedi_test, "object/tangible/wearables/robe/shared_robe_jedi_test.iff")

object_tangible_wearables_robe_shared_robe_prefect_talmont = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_prefect_talmont.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_prefect_talmont_m.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/robe_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777229,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_prefect_talmont",

	gameObjectType = 16777229,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_prefect_talmont",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_prefect_talmont",
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

	clientObjectCRC = 1197214887,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_robe_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_prefect_talmont, "object/tangible/wearables/robe/shared_robe_prefect_talmont.iff")

object_tangible_wearables_robe_shared_robe_s01 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_s01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_s01_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/robe_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777229,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_s01",

	gameObjectType = 16777229,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_s01",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_s01",
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

	clientObjectCRC = 1986706266,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_robe_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_s01, "object/tangible/wearables/robe/shared_robe_s01.iff")

object_tangible_wearables_robe_shared_robe_s04 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_s04.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_s04_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/robe_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777229,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_s04",

	gameObjectType = 16777229,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_s04",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_s04",
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

	clientObjectCRC = 529751892,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_robe_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_s04, "object/tangible/wearables/robe/shared_robe_s04.iff")

object_tangible_wearables_robe_shared_robe_s05 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_s05.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_s05_h0_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/cloak.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777221,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_s05",

	gameObjectType = 16777221,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_s05",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_s05",
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

	clientObjectCRC = 1453209817,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_cloak.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_s05, "object/tangible/wearables/robe/shared_robe_s05.iff")

object_tangible_wearables_robe_shared_robe_s05_h1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_s05_h1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_s05_h1_m.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/cloak_hooded.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777221,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_s05",

	gameObjectType = 16777221,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_s05",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_s05b",
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

	clientObjectCRC = 956309254,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_cloak_hooded.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_s05_h1, "object/tangible/wearables/robe/shared_robe_s05_h1.iff")

object_tangible_wearables_robe_shared_robe_s12 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_s12.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_s12_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/robe_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777229,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_s12",

	gameObjectType = 16777229,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_s12",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_s12",
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

	clientObjectCRC = 3059031733,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_robe_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_s12, "object/tangible/wearables/robe/shared_robe_s12.iff")

object_tangible_wearables_robe_shared_robe_s18 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_s18.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_s18_wke_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/robe_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777229,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_s18",

	gameObjectType = 16777229,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_s18",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_s18",
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

	clientObjectCRC = 1705432745,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_robe_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_s18, "object/tangible/wearables/robe/shared_robe_s18.iff")

object_tangible_wearables_robe_shared_robe_s27 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_s27.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_s27_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/robe_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777229,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_s27",

	gameObjectType = 16777229,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_s27",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_s27",
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

	clientObjectCRC = 4074040627,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_robe_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_s27, "object/tangible/wearables/robe/shared_robe_s27.iff")

object_tangible_wearables_robe_shared_robe_tusken_raider_s01 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_tusken_raider_s01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_tusken_raider_s01_m.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/robe_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777229,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_tusken_raider_s01",

	gameObjectType = 16777229,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_tusken_raider_s01",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_tusken_raider_s01",
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

	clientObjectCRC = 1357876030,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_robe_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_tusken_raider_s01, "object/tangible/wearables/robe/shared_robe_tusken_raider_s01.iff")

object_tangible_wearables_robe_shared_robe_tusken_raider_s02 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/robe/shared_robe_tusken_raider_s02.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/robe_tusken_raider_s02_m.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/robe_longsleeve.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777229,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:robe_tusken_raider_s02",

	gameObjectType = 16777229,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:robe_tusken_raider_s02",

	noBuildRadius = 0,

	objectName = "@wearables_name:robe_tusken_raider_s02",
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

	clientObjectCRC = 2348295081,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_robe_longsleeve.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_robe_shared_robe_tusken_raider_s02, "object/tangible/wearables/robe/shared_robe_tusken_raider_s02.iff")
