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


object_ship_player_shared_player_awing = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/awing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_awing"},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/ship/client_shared_awing.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_awing",

	noBuildRadius = 0,

	objectName = "@space_ship:player_awing",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2823165423,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_awing.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_awing, "object/ship/player/shared_player_awing.iff")

object_ship_player_shared_player_basic_hutt_light = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_lighthuttfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s01.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_basic_hutt_light",

	noBuildRadius = 0,

	objectName = "@space_ship:player_basic_hutt_light",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 770455739,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_basic_hutt_light.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_basic_hutt_light, "object/ship/player/shared_player_basic_hutt_light.iff")

object_ship_player_shared_player_basic_tiefighter = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_tiefighterlight"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiefighter.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_basic_tiefighter",

	noBuildRadius = 0,

	objectName = "@space_ship:player_basic_tiefighter",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2430870087,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_tiefighter.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_basic_tiefighter, "object/ship/player/shared_player_basic_tiefighter.iff")

object_ship_player_shared_player_basic_z95 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/z95_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_z95headhunter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_z95.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_basic_z95",

	noBuildRadius = 0,

	objectName = "@space_ship:player_basic_z95",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 960125460,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_z95.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_basic_z95, "object/ship/player/shared_player_basic_z95.iff")

object_ship_player_shared_player_blacksun_heavy_s01 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_heavyblacksunfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s01.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_blacksun_heavy_s01",

	noBuildRadius = 0,

	objectName = "@space_ship:player_blacksun_heavy_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2406012699,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_blacksun_heavy_s01.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_blacksun_heavy_s01, "object/ship/player/shared_player_blacksun_heavy_s01.iff")

object_ship_player_shared_player_blacksun_heavy_s02 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_heavyblacksunfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s02.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_blacksun_heavy_s02",

	noBuildRadius = 0,

	objectName = "@space_ship:player_blacksun_heavy_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1417641868,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_blacksun_heavy_s02.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_blacksun_heavy_s02, "object/ship/player/shared_player_blacksun_heavy_s02.iff")

object_ship_player_shared_player_blacksun_heavy_s03 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_heavyblacksunfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s03.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_blacksun_heavy_s03",

	noBuildRadius = 0,

	objectName = "@space_ship:player_blacksun_heavy_s03",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 494016513,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_blacksun_heavy_s03.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_blacksun_heavy_s03, "object/ship/player/shared_player_blacksun_heavy_s03.iff")

object_ship_player_shared_player_blacksun_heavy_s04 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_heavyblacksunfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s04.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_blacksun_heavy_s04",

	noBuildRadius = 0,

	objectName = "@space_ship:player_blacksun_heavy_s04",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3868275477,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_blacksun_heavy_s04.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_blacksun_heavy_s04, "object/ship/player/shared_player_blacksun_heavy_s04.iff")

object_ship_player_shared_player_blacksun_light_s01 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_lightblacksunfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s01.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_blacksun_light_s01",

	noBuildRadius = 0,

	objectName = "@space_ship:player_blacksun_light_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2468301121,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_blacksun_light_s01.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_blacksun_light_s01, "object/ship/player/shared_player_blacksun_light_s01.iff")

object_ship_player_shared_player_blacksun_light_s02 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_lightblacksunfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s02.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_blacksun_light_s02",

	noBuildRadius = 0,

	objectName = "@space_ship:player_blacksun_light_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1208541654,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_blacksun_light_s02.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_blacksun_light_s02, "object/ship/player/shared_player_blacksun_light_s02.iff")

object_ship_player_shared_player_blacksun_light_s03 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_lightblacksunfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s03.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_blacksun_light_s03",

	noBuildRadius = 0,

	objectName = "@space_ship:player_blacksun_light_s03",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 17139291,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_blacksun_light_s03.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_blacksun_light_s03, "object/ship/player/shared_player_blacksun_light_s03.iff")

object_ship_player_shared_player_blacksun_light_s04 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_lightblacksunfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s04.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_blacksun_light_s04",

	noBuildRadius = 0,

	objectName = "@space_ship:player_blacksun_light_s04",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4209421647,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_blacksun_light_s04.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_blacksun_light_s04, "object/ship/player/shared_player_blacksun_light_s04.iff")

object_ship_player_shared_player_blacksun_medium_s01 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_mediumblacksunfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s01.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_blacksun_medium_s01",

	noBuildRadius = 0,

	objectName = "@space_ship:player_blacksun_medium_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2060411448,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_blacksun_medium_s01.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_blacksun_medium_s01, "object/ship/player/shared_player_blacksun_medium_s01.iff")

object_ship_player_shared_player_blacksun_medium_s02 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_mediumblacksunfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s02.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_blacksun_medium_s02",

	noBuildRadius = 0,

	objectName = "@space_ship:player_blacksun_medium_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2715339439,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_blacksun_medium_s02.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_blacksun_medium_s02, "object/ship/player/shared_player_blacksun_medium_s02.iff")

object_ship_player_shared_player_blacksun_medium_s03 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_mediumblacksunfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s03.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_blacksun_medium_s03",

	noBuildRadius = 0,

	objectName = "@space_ship:player_blacksun_medium_s03",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3906317602,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_blacksun_medium_s03.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_blacksun_medium_s03, "object/ship/player/shared_player_blacksun_medium_s03.iff")

object_ship_player_shared_player_blacksun_medium_s04 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_mediumblacksunfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s04.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_blacksun_medium_s04",

	noBuildRadius = 0,

	objectName = "@space_ship:player_blacksun_medium_s04",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 322340406,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_blacksun_medium_s04.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_blacksun_medium_s04, "object/ship/player/shared_player_blacksun_medium_s04.iff")

object_ship_player_shared_player_bwing = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/bwing_cockpit_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_bwing"},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/ship/client_shared_bwing.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_bwing",

	noBuildRadius = 0,

	objectName = "@space_ship:player_bwing",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3129407218,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_bwing.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_bwing, "object/ship/player/shared_player_bwing.iff")

object_ship_player_shared_player_corvette = SharedShipObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/ship/client_shared_yt1300.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "string_id_table",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_corvette",

	noBuildRadius = 0,

	objectName = "@space_ship:player_corvette",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/corellian_corvette_pob.pob",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1738437900,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_corvette, "object/ship/player/shared_player_corvette.iff")

object_ship_player_shared_player_decimator = SharedShipObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_decimator"},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/ship/client_shared_decimator.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "string_id_table",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_decimator",

	noBuildRadius = 0,

	objectName = "@space_ship:player_decimator",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/vt49.pob",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3150522393,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_decimator, "object/ship/player/shared_player_decimator.iff")

object_ship_player_shared_player_firespray = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/kse_firespray_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_firespray"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_firespray.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_firespray",

	noBuildRadius = 0,

	objectName = "@space_ship:player_firespray",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4073039210,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_firespray.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_firespray, "object/ship/player/shared_player_firespray.iff")

object_ship_player_shared_player_hutt_heavy_s01 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_heavyhuttfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_heavy_s01.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_hutt_heavy_s01",

	noBuildRadius = 0,

	objectName = "@space_ship:player_hutt_heavy_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 354676203,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_hutt_heavy_s01.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_hutt_heavy_s01, "object/ship/player/shared_player_hutt_heavy_s01.iff")

object_ship_player_shared_player_hutt_heavy_s02 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_heavyhuttfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_heavy_s02.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_hutt_heavy_s02",

	noBuildRadius = 0,

	objectName = "@space_ship:player_hutt_heavy_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3459532156,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_hutt_heavy_s02.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_hutt_heavy_s02, "object/ship/player/shared_player_hutt_heavy_s02.iff")

object_ship_player_shared_player_hutt_light_s01 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_lighthuttfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s01.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_hutt_light_s01",

	noBuildRadius = 0,

	objectName = "@space_ship:player_hutt_light_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 156529585,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_hutt_light_s01.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_hutt_light_s01, "object/ship/player/shared_player_hutt_light_s01.iff")

object_ship_player_shared_player_hutt_light_s02 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_lighthuttfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s02.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_hutt_light_s02",

	noBuildRadius = 0,

	objectName = "@space_ship:player_hutt_light_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3527662374,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_hutt_light_s02.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_hutt_light_s02, "object/ship/player/shared_player_hutt_light_s02.iff")

object_ship_player_shared_player_hutt_medium_s01 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_mediumhuttfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_medium_s01.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_hutt_medium_s01",

	noBuildRadius = 0,

	objectName = "@space_ship:player_hutt_medium_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 996310896,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_hutt_medium_s01.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_hutt_medium_s01, "object/ship/player/shared_player_hutt_medium_s01.iff")

object_ship_player_shared_player_hutt_medium_s02 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_mediumhuttfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_medium_s02.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_hutt_medium_s02",

	noBuildRadius = 0,

	objectName = "@space_ship:player_hutt_medium_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3765819367,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_hutt_medium_s02.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_hutt_medium_s02, "object/ship/player/shared_player_hutt_medium_s02.iff")

object_ship_player_shared_player_hutt_turret_ship = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s03.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_hutt_turret_ship"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_turret_ship.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_hutt_turret_ship",

	noBuildRadius = 0,

	objectName = "@space_ship:player_hutt_turret_ship",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid", "ship_gunner1"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2830008910,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_hutt_turret_ship.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_hutt_turret_ship, "object/ship/player/shared_player_hutt_turret_ship.iff")

object_ship_player_shared_player_prototype_hutt_light = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_lighthuttfighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s01.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_prototype_hutt_light",

	noBuildRadius = 0,

	objectName = "@space_ship:player_prototype_hutt_light",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1541926498,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_basic_hutt_light.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_prototype_hutt_light, "object/ship/player/shared_player_prototype_hutt_light.iff")

object_ship_player_shared_player_prototype_tiefighter = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_tiefighterlight"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiefighter.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_prototype_tiefighter",

	noBuildRadius = 0,

	objectName = "@space_ship:player_prototype_tiefighter",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3874485406,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_tiefighter.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_prototype_tiefighter, "object/ship/player/shared_player_prototype_tiefighter.iff")

object_ship_player_shared_player_prototype_z95 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/z95_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_z95headhunter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_z95.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_prototype_z95",

	noBuildRadius = 0,

	objectName = "@space_ship:player_prototype_z95",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4125787031,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_z95.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_prototype_z95, "object/ship/player/shared_player_prototype_z95.iff")

object_ship_player_shared_player_sorosuub_space_yacht = SharedShipObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/ship/client_shared_sorosuub_space_yacht.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "string_id_table",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_sorosuub_space_yacht",

	noBuildRadius = 0,

	objectName = "@space_ship:player_sorosuub_space_yacht",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/sorosuub_space_yacht.pob",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4077746601,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_sorosuub_space_yacht, "object/ship/player/shared_player_sorosuub_space_yacht.iff")

object_ship_player_shared_player_tie_in = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter_in.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_tiefighterin"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiefighter.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_tie_in",

	noBuildRadius = 0,

	objectName = "@space_ship:player_tie_in",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 500982809,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_tie_in.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_tie_in, "object/ship/player/shared_player_tie_in.iff")

object_ship_player_shared_player_tie_light_duty = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_tiefighterlight"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiefighter.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_tie_light_duty",

	noBuildRadius = 0,

	objectName = "@space_ship:player_tie_light_duty",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 349740221,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_tiefighter.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_tie_light_duty, "object/ship/player/shared_player_tie_light_duty.iff")

object_ship_player_shared_player_tieadvanced = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_advanced.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_tieadvanced"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieadvanced.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_tieadvanced",

	noBuildRadius = 0,

	objectName = "@space_ship:player_tieadvanced",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 537219045,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_tieadvanced.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_tieadvanced, "object/ship/player/shared_player_tieadvanced.iff")

object_ship_player_shared_player_tieaggressor = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_aggressor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_tieadvanced"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieaggressor.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_tieaggressor",

	noBuildRadius = 0,

	objectName = "@space_ship:player_tieaggressor",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid", "ship_gunner1"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3313666579,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_tieaggressor.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_tieaggressor, "object/ship/player/shared_player_tieaggressor.iff")

object_ship_player_shared_player_tiebomber = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_bomber_b.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_tiebomber"},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/ship/client_shared_tiebomber.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_tiebomber",

	noBuildRadius = 0,

	objectName = "@space_ship:player_tiebomber",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1403833964,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_tiebomber.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_tiebomber, "object/ship/player/shared_player_tiebomber.iff")

object_ship_player_shared_player_tiefighter = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_tiefighter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiefighter.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_tiefighter",

	noBuildRadius = 0,

	objectName = "@space_ship:player_tiefighter",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1253337464,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_tiefighter.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_tiefighter, "object/ship/player/shared_player_tiefighter.iff")

object_ship_player_shared_player_tieinterceptor = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_interceptor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_tieinterceptor"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieinterceptor.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_tieinterceptor",

	noBuildRadius = 0,

	objectName = "@space_ship:player_tieinterceptor",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4021866633,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_tieinterceptor.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_tieinterceptor, "object/ship/player/shared_player_tieinterceptor.iff")

object_ship_player_shared_player_tieoppressor = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_oppressor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_tieoppressor"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieoppressor.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_tieoppressor",

	noBuildRadius = 0,

	objectName = "@space_ship:player_tieoppressor",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3411039109,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_tieoppressor.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_tieoppressor, "object/ship/player/shared_player_tieoppressor.iff")

object_ship_player_shared_player_xwing = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/xwing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_xwing"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_xwing.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_xwing",

	noBuildRadius = 0,

	objectName = "@space_ship:player_xwing",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3426854753,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_xwing.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_xwing, "object/ship/player/shared_player_xwing.iff")

object_ship_player_shared_player_ykl37r = SharedShipObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_ykl37r"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_ykl37r.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "string_id_table",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_ykl37r",

	noBuildRadius = 0,

	objectName = "@space_ship:player_ykl37r",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ykl37r.pob",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4283603432,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_ykl37r, "object/ship/player/shared_player_ykl37r.iff")

object_ship_player_shared_player_yt1300 = SharedShipObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_yt1300"},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/ship/client_shared_yt1300.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "string_id_table",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_yt1300",

	noBuildRadius = 0,

	objectName = "@space_ship:player_yt1300",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/yt1300.pob",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2643423122,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_yt1300, "object/ship/player/shared_player_yt1300.iff")

object_ship_player_shared_player_yt1300_decorated_01 = SharedShipObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_yt1300"},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/ship/client_shared_yt1300.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "string_id_table",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_yt1300",

	noBuildRadius = 0,

	objectName = "@space_ship:player_yt1300",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/yt1300.pob",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3619233988,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_yt1300_decorated_01, "object/ship/player/shared_player_yt1300_decorated_01.iff")

object_ship_player_shared_player_ywing = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/ywing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_ywing"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_ywing.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_ywing",

	noBuildRadius = 0,

	objectName = "@space_ship:player_ywing",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid", "ship_gunner1"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1044450567,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_ywing.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_ywing, "object/ship/player/shared_player_ywing.iff")

object_ship_player_shared_player_ywing_longprobe = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/ywing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_ywinglongprobe"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_ywing.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_ywing_longprobe",

	noBuildRadius = 0,

	objectName = "@space_ship:player_ywing_longprobe",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 711184758,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_ywing.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_ywing_longprobe, "object/ship/player/shared_player_ywing_longprobe.iff")

object_ship_player_shared_player_z95 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/z95_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {"cert_starships_z95headhunter"},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_z95.cdf",
	clientGameObjectType = 536870913,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:player_z95",

	noBuildRadius = 0,

	objectName = "@space_ship:player_z95",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_pilot", "ship_droid"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3298750759,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/ship/base/shared_ship_base.iff", "object/ship/base/shared_ship_fighter_base.iff", "object/ship/shared_z95.iff"}
}

ObjectTemplates:addClientTemplate(object_ship_player_shared_player_z95, "object/ship/player/shared_player_z95.iff")
