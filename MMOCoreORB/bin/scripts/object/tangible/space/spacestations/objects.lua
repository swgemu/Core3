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


object_tangible_space_spacestations_shared_spacestation_imperial_01 = SharedShipObjectTemplate:new {
	clientTemplateFileName = "object/tangible/space/spacestations/shared_spacestation_imperial_01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/spacestation_rebel.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_ship.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_n:spawner",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:station_base",

	noBuildRadius = 0,

	objectName = "@item_n:spawner",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3055118687,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_station_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_space_spacestations_shared_spacestation_imperial_01, "object/tangible/space/spacestations/shared_spacestation_imperial_01.iff")

object_tangible_space_spacestations_shared_spacestation_imperial_battlefield_control = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/space/spacestations/shared_spacestation_imperial_battlefield_control.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/spacestation_neutral.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_ship.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_n:spawner",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:ship_base",

	noBuildRadius = 0,

	objectName = "@item_n:spawner",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2372198483,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_space_spacestations_shared_spacestation_imperial_battlefield_control, "object/tangible/space/spacestations/shared_spacestation_imperial_battlefield_control.iff")

object_tangible_space_spacestations_shared_spacestation_imperial_battlefield_entry = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/space/spacestations/shared_spacestation_imperial_battlefield_entry.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/spacestation_neutral.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_ship.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_n:spawner",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:ship_base",

	noBuildRadius = 0,

	objectName = "@item_n:spawner",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3537441951,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_space_spacestations_shared_spacestation_imperial_battlefield_entry, "object/tangible/space/spacestations/shared_spacestation_imperial_battlefield_entry.iff")

object_tangible_space_spacestations_shared_spacestation_neutral_01 = SharedShipObjectTemplate:new {
	clientTemplateFileName = "object/tangible/space/spacestations/shared_spacestation_neutral_01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/spacestation_neutral.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_ship.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_n:spawner",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:station_base",

	noBuildRadius = 0,

	objectName = "@item_n:spawner",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2417244262,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_station_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_space_spacestations_shared_spacestation_neutral_01, "object/tangible/space/spacestations/shared_spacestation_neutral_01.iff")

object_tangible_space_spacestations_shared_spacestation_rebel_01 = SharedShipObjectTemplate:new {
	clientTemplateFileName = "object/tangible/space/spacestations/shared_spacestation_rebel_01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/spacestation_rebel.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_ship.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_n:spawner",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:station_base",

	noBuildRadius = 0,

	objectName = "@item_n:spawner",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2407802973,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_station_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_space_spacestations_shared_spacestation_rebel_01, "object/tangible/space/spacestations/shared_spacestation_rebel_01.iff")

object_tangible_space_spacestations_shared_spacestation_rebel_battlefield_control = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/space/spacestations/shared_spacestation_rebel_battlefield_control.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/spacestation_rebel.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_ship.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_n:spawner",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:ship_base",

	noBuildRadius = 0,

	objectName = "@item_n:spawner",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3861915556,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_space_spacestations_shared_spacestation_rebel_battlefield_control, "object/tangible/space/spacestations/shared_spacestation_rebel_battlefield_control.iff")

object_tangible_space_spacestations_shared_spacestation_rebel_battlefield_entry = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/space/spacestations/shared_spacestation_rebel_battlefield_entry.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/spacestation_rebel.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_ship.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_n:spawner",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:ship_base",

	noBuildRadius = 0,

	objectName = "@item_n:spawner",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2272557315,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_space_spacestations_shared_spacestation_rebel_battlefield_entry, "object/tangible/space/spacestations/shared_spacestation_rebel_battlefield_entry.iff")
