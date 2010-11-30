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


object_ship_shared_assaultship = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/distant_assaultship.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_assaultship.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3844148531
}

ObjectTemplates:addClientTemplate(object_ship_shared_assaultship, "object/ship/shared_assaultship.iff")

object_ship_shared_awing = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/awing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/ship/client_shared_awing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:awing swg-se test",

	noBuildRadius = 0,

	objectName = "@:awing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1006768204
}

ObjectTemplates:addClientTemplate(object_ship_shared_awing, "object/ship/shared_awing.iff")

object_ship_shared_awing_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/awing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_awing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2304550097
}

ObjectTemplates:addClientTemplate(object_ship_shared_awing_tier1, "object/ship/shared_awing_tier1.iff")

object_ship_shared_awing_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/awing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_awing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1380650054
}

ObjectTemplates:addClientTemplate(object_ship_shared_awing_tier2, "object/ship/shared_awing_tier2.iff")

object_ship_shared_awing_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/awing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_awing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 457599947
}

ObjectTemplates:addClientTemplate(object_ship_shared_awing_tier3, "object/ship/shared_awing_tier3.iff")

object_ship_shared_awing_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/awing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_awing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3768926431
}

ObjectTemplates:addClientTemplate(object_ship_shared_awing_tier4, "object/ship/shared_awing_tier4.iff")

object_ship_shared_awing_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/awing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_awing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2846369618
}

ObjectTemplates:addClientTemplate(object_ship_shared_awing_tier5, "object/ship/shared_awing_tier5.iff")

object_ship_shared_basic_hutt_light = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:hutt_light",

	noBuildRadius = 0,

	objectName = "@:hutt_light",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 762962365
}

ObjectTemplates:addClientTemplate(object_ship_shared_basic_hutt_light, "object/ship/shared_basic_hutt_light.iff")

object_ship_shared_basic_tiefighter = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiefighter.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:tiefighter swg-se test",

	noBuildRadius = 0,

	objectName = "@:tiefighter swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2423388993
}

ObjectTemplates:addClientTemplate(object_ship_shared_basic_tiefighter, "object/ship/shared_basic_tiefighter.iff")

object_ship_shared_basic_z95 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/z95_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_z95.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:z95 swg-se test",

	noBuildRadius = 0,

	objectName = "@:z95 swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 237307345
}

ObjectTemplates:addClientTemplate(object_ship_shared_basic_z95, "object/ship/shared_basic_z95.iff")

object_ship_shared_blacksun_heavy_s01 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1689683950
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s01, "object/ship/shared_blacksun_heavy_s01.iff")

object_ship_shared_blacksun_heavy_s01_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 42858675
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s01_tier1, "object/ship/shared_blacksun_heavy_s01_tier1.iff")

object_ship_shared_blacksun_heavy_s01_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3650768932
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s01_tier2, "object/ship/shared_blacksun_heavy_s01_tier2.iff")

object_ship_shared_blacksun_heavy_s01_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2425829289
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s01_tier3, "object/ship/shared_blacksun_heavy_s01_tier3.iff")

object_ship_shared_blacksun_heavy_s01_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1802771645
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s01_tier4, "object/ship/shared_blacksun_heavy_s01_tier4.iff")

object_ship_shared_blacksun_heavy_s01_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 578386736
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s01_tier5, "object/ship/shared_blacksun_heavy_s01_tier5.iff")

object_ship_shared_blacksun_heavy_s02 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3215011705
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s02, "object/ship/shared_blacksun_heavy_s02.iff")

object_ship_shared_blacksun_heavy_s02_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 213478710
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s02_tier1, "object/ship/shared_blacksun_heavy_s02_tier1.iff")

object_ship_shared_blacksun_heavy_s02_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3618555297
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s02_tier2, "object/ship/shared_blacksun_heavy_s02_tier2.iff")

object_ship_shared_blacksun_heavy_s02_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2661524012
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s02_tier3, "object/ship/shared_blacksun_heavy_s02_tier3.iff")

object_ship_shared_blacksun_heavy_s02_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1698728248
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s02_tier4, "object/ship/shared_blacksun_heavy_s02_tier4.iff")

object_ship_shared_blacksun_heavy_s02_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 743304885
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s02_tier5, "object/ship/shared_blacksun_heavy_s02_tier5.iff")

object_ship_shared_blacksun_heavy_s03 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s03.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4138486004
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s03, "object/ship/shared_blacksun_heavy_s03.iff")

object_ship_shared_blacksun_heavy_s03_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s03.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4111854296
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s03_tier1, "object/ship/shared_blacksun_heavy_s03_tier1.iff")

object_ship_shared_blacksun_heavy_s03_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s03.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 771899983
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s03_tier2, "object/ship/shared_blacksun_heavy_s03_tier2.iff")

object_ship_shared_blacksun_heavy_s03_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s03.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1729045954
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s03_tier3, "object/ship/shared_blacksun_heavy_s03_tier3.iff")

object_ship_shared_blacksun_heavy_s03_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s03.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2632715990
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s03_tier4, "object/ship/shared_blacksun_heavy_s03_tier4.iff")

object_ship_shared_blacksun_heavy_s03_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s03.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3588319579
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s03_tier5, "object/ship/shared_blacksun_heavy_s03_tier5.iff")

object_ship_shared_blacksun_heavy_s04 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s04.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 223306720
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s04, "object/ship/shared_blacksun_heavy_s04.iff")

object_ship_shared_blacksun_heavy_s04_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s04.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 282084924
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s04_tier1, "object/ship/shared_blacksun_heavy_s04_tier1.iff")

object_ship_shared_blacksun_heavy_s04_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s04.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3418877611
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s04_tier2, "object/ship/shared_blacksun_heavy_s04_tier2.iff")

object_ship_shared_blacksun_heavy_s04_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s04.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2194311462
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s04_tier3, "object/ship/shared_blacksun_heavy_s04_tier3.iff")

object_ship_shared_blacksun_heavy_s04_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s04.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2032771634
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s04_tier4, "object/ship/shared_blacksun_heavy_s04_tier4.iff")

object_ship_shared_blacksun_heavy_s04_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_heavy_s04.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 807716287
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_heavy_s04_tier5, "object/ship/shared_blacksun_heavy_s04_tier5.iff")

object_ship_shared_blacksun_light_s01 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2025920948
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s01, "object/ship/shared_blacksun_light_s01.iff")

object_ship_shared_blacksun_light_s01_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1922069411
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s01_tier1, "object/ship/shared_blacksun_light_s01_tier1.iff")

object_ship_shared_blacksun_light_s01_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2844252980
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s01_tier2, "object/ship/shared_blacksun_light_s01_tier2.iff")

object_ship_shared_blacksun_light_s01_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3767188665
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s01_tier3, "object/ship/shared_blacksun_light_s01_tier3.iff")

object_ship_shared_blacksun_light_s01_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 459904941
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s01_tier4, "object/ship/shared_blacksun_light_s01_tier4.iff")

object_ship_shared_blacksun_light_s01_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1382346784
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s01_tier5, "object/ship/shared_blacksun_light_s01_tier5.iff")

object_ship_shared_blacksun_light_s02 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2748756259
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s02, "object/ship/shared_blacksun_light_s02.iff")

object_ship_shared_blacksun_light_s02_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2091181606
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s02_tier1, "object/ship/shared_blacksun_light_s02_tier1.iff")

object_ship_shared_blacksun_light_s02_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2813546161
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s02_tier2, "object/ship/shared_blacksun_light_s02_tier2.iff")

object_ship_shared_blacksun_light_s02_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4005439804
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s02_tier3, "object/ship/shared_blacksun_light_s02_tier3.iff")

object_ship_shared_blacksun_light_s02_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 358416936
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s02_tier4, "object/ship/shared_blacksun_light_s02_tier4.iff")

object_ship_shared_blacksun_light_s02_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1548772773
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s02_tier5, "object/ship/shared_blacksun_light_s02_tier5.iff")

object_ship_shared_blacksun_light_s03 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s03.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3940275886
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s03, "object/ship/shared_blacksun_light_s03.iff")

object_ship_shared_blacksun_light_s03_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s03.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2231919048
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s03_tier1, "object/ship/shared_blacksun_light_s03_tier1.iff")

object_ship_shared_blacksun_light_s03_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s03.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1579141471
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s03_tier2, "object/ship/shared_blacksun_light_s03_tier2.iff")

object_ship_shared_blacksun_light_s03_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s03.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 387100370
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s03_tier3, "object/ship/shared_blacksun_light_s03_tier3.iff")

object_ship_shared_blacksun_light_s03_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s03.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3975251398
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s03_tier4, "object/ship/shared_blacksun_light_s03_tier4.iff")

object_ship_shared_blacksun_light_s03_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s03.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2784813643
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s03_tier5, "object/ship/shared_blacksun_light_s03_tier5.iff")

object_ship_shared_blacksun_light_s04 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s04.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 288947642
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s04, "object/ship/shared_blacksun_light_s04.iff")

object_ship_shared_blacksun_light_s04_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s04.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1624100140
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s04_tier1, "object/ship/shared_blacksun_light_s04_tier1.iff")

object_ship_shared_blacksun_light_s04_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s04.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3151652283
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s04_tier2, "object/ship/shared_blacksun_light_s04_tier2.iff")

object_ship_shared_blacksun_light_s04_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s04.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4074177078
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s04_tier3, "object/ship/shared_blacksun_light_s04_tier3.iff")

object_ship_shared_blacksun_light_s04_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s04.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 154413346
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s04_tier4, "object/ship/shared_blacksun_light_s04_tier4.iff")

object_ship_shared_blacksun_light_s04_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_light_s04.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1077497519
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_light_s04_tier5, "object/ship/shared_blacksun_light_s04_tier5.iff")

object_ship_shared_blacksun_medium_s01 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1249737248
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s01, "object/ship/shared_blacksun_medium_s01.iff")

object_ship_shared_blacksun_medium_s01_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3687774721
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s01_tier1, "object/ship/shared_blacksun_medium_s01_tier1.iff")

object_ship_shared_blacksun_medium_s01_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 14242454
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s01_tier2, "object/ship/shared_blacksun_medium_s01_tier2.iff")

object_ship_shared_blacksun_medium_s01_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1238643995
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s01_tier3, "object/ship/shared_blacksun_medium_s01_tier3.iff")

object_ship_shared_blacksun_medium_s01_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2989956623
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s01_tier4, "object/ship/shared_blacksun_medium_s01_tier4.iff")

object_ship_shared_blacksun_medium_s01_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4214913410
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s01_tier5, "object/ship/shared_blacksun_medium_s01_tier5.iff")

object_ship_shared_blacksun_medium_s02 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2439697079
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s02, "object/ship/shared_blacksun_medium_s02.iff")

object_ship_shared_blacksun_medium_s02_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3589959556
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s02_tier1, "object/ship/shared_blacksun_medium_s02_tier1.iff")

object_ship_shared_blacksun_medium_s02_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 250464019
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s02_tier2, "object/ship/shared_blacksun_medium_s02_tier2.iff")

object_ship_shared_blacksun_medium_s02_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1205903518
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s02_tier3, "object/ship/shared_blacksun_medium_s02_tier3.iff")

object_ship_shared_blacksun_medium_s02_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3154348938
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s02_tier4, "object/ship/shared_blacksun_medium_s02_tier4.iff")

object_ship_shared_blacksun_medium_s02_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4111395847
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s02_tier5, "object/ship/shared_blacksun_medium_s02_tier5.iff")

object_ship_shared_blacksun_medium_s03 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s03.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3630675258
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s03, "object/ship/shared_blacksun_medium_s03.iff")

object_ship_shared_blacksun_medium_s03_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s03.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 743893098
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s03_tier1, "object/ship/shared_blacksun_medium_s03_tier1.iff")

object_ship_shared_blacksun_medium_s03_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s03.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4148248829
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s03_tier2, "object/ship/shared_blacksun_medium_s03_tier2.iff")

object_ship_shared_blacksun_medium_s03_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s03.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3192661872
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s03_tier3, "object/ship/shared_blacksun_medium_s03_tier3.iff")

object_ship_shared_blacksun_medium_s03_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s03.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1169099876
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s03_tier4, "object/ship/shared_blacksun_medium_s03_tier4.iff")

object_ship_shared_blacksun_medium_s03_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s03.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 211971049
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s03_tier5, "object/ship/shared_blacksun_medium_s03_tier5.iff")

object_ship_shared_blacksun_medium_s04 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s04.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 595893806
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s04, "object/ship/shared_blacksun_medium_s04.iff")

object_ship_shared_blacksun_medium_s04_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s04.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3381871758
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s04_tier1, "object/ship/shared_blacksun_medium_s04_tier1.iff")

object_ship_shared_blacksun_medium_s04_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s04.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 310701081
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s04_tier2, "object/ship/shared_blacksun_medium_s04_tier2.iff")

object_ship_shared_blacksun_medium_s04_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s04.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1535740820
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s04_tier3, "object/ship/shared_blacksun_medium_s04_tier3.iff")

object_ship_shared_blacksun_medium_s04_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s04.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2691342464
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s04_tier4, "object/ship/shared_blacksun_medium_s04_tier4.iff")

object_ship_shared_blacksun_medium_s04_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_medium_s04.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3915892493
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_medium_s04_tier5, "object/ship/shared_blacksun_medium_s04_tier5.iff")

object_ship_shared_blacksun_transport = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/blacksun_transport.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_transport.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "@:blacksun_transport",

	noBuildRadius = 0,

	objectName = "@:blacksun_transport",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 806145873
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_transport, "object/ship/shared_blacksun_transport.iff")

object_ship_shared_blacksun_transport_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/blacksun_transport.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_transport.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3217548599
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_transport_tier1, "object/ship/shared_blacksun_transport_tier1.iff")

object_ship_shared_blacksun_transport_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/blacksun_transport.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_transport.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1691372960
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_transport_tier2, "object/ship/shared_blacksun_transport_tier2.iff")

object_ship_shared_blacksun_transport_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/blacksun_transport.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_transport.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 769468973
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_transport_tier3, "object/ship/shared_blacksun_transport_tier3.iff")

object_ship_shared_blacksun_transport_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/blacksun_transport.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_transport.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3594387769
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_transport_tier4, "object/ship/shared_blacksun_transport_tier4.iff")

object_ship_shared_blacksun_transport_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/blacksun_transport.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_blacksun_transport.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2670945972
}

ObjectTemplates:addClientTemplate(object_ship_shared_blacksun_transport_tier5, "object/ship/shared_blacksun_transport_tier5.iff")

object_ship_shared_bwing = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/bwing_cockpit_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/ship/client_shared_bwing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 784528209
}

ObjectTemplates:addClientTemplate(object_ship_shared_bwing, "object/ship/shared_bwing.iff")

object_ship_shared_bwing_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/bwing_cockpit_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/ship/client_shared_bwing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3935148784
}

ObjectTemplates:addClientTemplate(object_ship_shared_bwing_tier1, "object/ship/shared_bwing_tier1.iff")

object_ship_shared_bwing_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/bwing_cockpit_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/ship/client_shared_bwing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 832189031
}

ObjectTemplates:addClientTemplate(object_ship_shared_bwing_tier2, "object/ship/shared_bwing_tier2.iff")

object_ship_shared_bwing_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/bwing_cockpit_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/ship/client_shared_bwing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2023183850
}

ObjectTemplates:addClientTemplate(object_ship_shared_bwing_tier3, "object/ship/shared_bwing_tier3.iff")

object_ship_shared_bwing_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/bwing_cockpit_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/ship/client_shared_bwing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2205449982
}

ObjectTemplates:addClientTemplate(object_ship_shared_bwing_tier4, "object/ship/shared_bwing_tier4.iff")

object_ship_shared_bwing_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/bwing_cockpit_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/ship/client_shared_bwing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3396934003
}

ObjectTemplates:addClientTemplate(object_ship_shared_bwing_tier5, "object/ship/shared_bwing_tier5.iff")

object_ship_shared_civshuttle = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/shuttle.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_civtransport.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 907129698
}

ObjectTemplates:addClientTemplate(object_ship_shared_civshuttle, "object/ship/shared_civshuttle.iff")

object_ship_shared_civspeeder1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/distant_air_speeder_1.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_civtaxi.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4120399097
}

ObjectTemplates:addClientTemplate(object_ship_shared_civspeeder1, "object/ship/shared_civspeeder1.iff")

object_ship_shared_civspeeder2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/distant_air_speeder_2.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_civtaxi.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 781182062
}

ObjectTemplates:addClientTemplate(object_ship_shared_civspeeder2, "object/ship/shared_civspeeder2.iff")

object_ship_shared_civtaxi = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/distant_air_taxi.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_civtaxi.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3717426532
}

ObjectTemplates:addClientTemplate(object_ship_shared_civtaxi, "object/ship/shared_civtaxi.iff")

object_ship_shared_civtransport = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/transport.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_civtransport.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 952499678
}

ObjectTemplates:addClientTemplate(object_ship_shared_civtransport, "object/ship/shared_civtransport.iff")

object_ship_shared_corvette = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/corellian_corvette.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_corvette.cdf",
	clientGameObjectType = 536870914,
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

	gameObjectType = 536870914,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:corellian_corvette",

	noBuildRadius = 0,

	objectName = "@space_ship:corellian_corvette",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 562522734
}

ObjectTemplates:addClientTemplate(object_ship_shared_corvette, "object/ship/shared_corvette.iff")

object_ship_shared_corvette_interior = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/corellian_corvette.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_corvette.cdf",
	clientGameObjectType = 536870914,
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

	gameObjectType = 536870914,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:corellian_corvette",

	noBuildRadius = 0,

	objectName = "@space_ship:corellian_corvette",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/corellian_corvette_pob.pob",

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

	clientObjectCRC = 3035559423
}

ObjectTemplates:addClientTemplate(object_ship_shared_corvette_interior, "object/ship/shared_corvette_interior.iff")

object_ship_shared_decimator = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/vt49_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_decimator.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2362865628
}

ObjectTemplates:addClientTemplate(object_ship_shared_decimator, "object/ship/shared_decimator.iff")

object_ship_shared_decimator_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/vt49_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_decimator.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2353591998
}

ObjectTemplates:addClientTemplate(object_ship_shared_decimator_tier1, "object/ship/shared_decimator_tier1.iff")

object_ship_shared_decimator_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/vt49_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_decimator.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1465867817
}

ObjectTemplates:addClientTemplate(object_ship_shared_decimator_tier2, "object/ship/shared_decimator_tier2.iff")

object_ship_shared_decimator_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/vt49_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_decimator.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 508705188
}

ObjectTemplates:addClientTemplate(object_ship_shared_decimator_tier3, "object/ship/shared_decimator_tier3.iff")

object_ship_shared_decimator_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/vt49_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_decimator.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3853587120
}

ObjectTemplates:addClientTemplate(object_ship_shared_decimator_tier4, "object/ship/shared_decimator_tier4.iff")

object_ship_shared_decimator_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/vt49_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_decimator.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2898031933
}

ObjectTemplates:addClientTemplate(object_ship_shared_decimator_tier5, "object/ship/shared_decimator_tier5.iff")

object_ship_shared_droid_fighter = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/droid_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_droid_fighter.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2308789341
}

ObjectTemplates:addClientTemplate(object_ship_shared_droid_fighter, "object/ship/shared_droid_fighter.iff")

object_ship_shared_droid_fighter_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/droid_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_droid_fighter.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 14973297
}

ObjectTemplates:addClientTemplate(object_ship_shared_droid_fighter_tier1, "object/ship/shared_droid_fighter_tier1.iff")

object_ship_shared_droid_fighter_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/droid_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_droid_fighter.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3690189286
}

ObjectTemplates:addClientTemplate(object_ship_shared_droid_fighter_tier2, "object/ship/shared_droid_fighter_tier2.iff")

object_ship_shared_droid_fighter_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/droid_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_droid_fighter.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2466166379
}

ObjectTemplates:addClientTemplate(object_ship_shared_droid_fighter_tier3, "object/ship/shared_droid_fighter_tier3.iff")

object_ship_shared_droid_fighter_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/droid_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_droid_fighter.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1763548543
}

ObjectTemplates:addClientTemplate(object_ship_shared_droid_fighter_tier4, "object/ship/shared_droid_fighter_tier4.iff")

object_ship_shared_droid_fighter_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/droid_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_droid_fighter.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 537983730
}

ObjectTemplates:addClientTemplate(object_ship_shared_droid_fighter_tier5, "object/ship/shared_droid_fighter_tier5.iff")

object_ship_shared_escape_pod = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/escape_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_escape_pod.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2997532055
}

ObjectTemplates:addClientTemplate(object_ship_shared_escape_pod, "object/ship/shared_escape_pod.iff")

object_ship_shared_escape_pod_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/escape_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_escape_pod.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2280868888
}

ObjectTemplates:addClientTemplate(object_ship_shared_escape_pod_tier1, "object/ship/shared_escape_pod_tier1.iff")

object_ship_shared_escape_pod_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/escape_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_escape_pod.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1558504591
}

ObjectTemplates:addClientTemplate(object_ship_shared_escape_pod_tier2, "object/ship/shared_escape_pod_tier2.iff")

object_ship_shared_escape_pod_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/escape_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_escape_pod.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 367624962
}

ObjectTemplates:addClientTemplate(object_ship_shared_escape_pod_tier3, "object/ship/shared_escape_pod_tier3.iff")

object_ship_shared_escape_pod_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/escape_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_escape_pod.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3993675798
}

ObjectTemplates:addClientTemplate(object_ship_shared_escape_pod_tier4, "object/ship/shared_escape_pod_tier4.iff")

object_ship_shared_escape_pod_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/escape_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_escape_pod.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2802306971
}

ObjectTemplates:addClientTemplate(object_ship_shared_escape_pod_tier5, "object/ship/shared_escape_pod_tier5.iff")

object_ship_shared_firespray = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/kse_firespray_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_firespray.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:firespray swg-se test",

	noBuildRadius = 0,

	objectName = "@:firespray swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3319462575
}

ObjectTemplates:addClientTemplate(object_ship_shared_firespray, "object/ship/shared_firespray.iff")

object_ship_shared_firespray_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/kse_firespray_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_firespray.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1391589453
}

ObjectTemplates:addClientTemplate(object_ship_shared_firespray_tier1, "object/ship/shared_firespray_tier1.iff")

object_ship_shared_firespray_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/kse_firespray_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_firespray.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2313572570
}

ObjectTemplates:addClientTemplate(object_ship_shared_firespray_tier2, "object/ship/shared_firespray_tier2.iff")

object_ship_shared_firespray_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/kse_firespray_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_firespray.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3236640599
}

ObjectTemplates:addClientTemplate(object_ship_shared_firespray_tier3, "object/ship/shared_firespray_tier3.iff")

object_ship_shared_firespray_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/kse_firespray_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_firespray.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 990387267
}

ObjectTemplates:addClientTemplate(object_ship_shared_firespray_tier4, "object/ship/shared_firespray_tier4.iff")

object_ship_shared_firespray_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/kse_firespray_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_firespray.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1912961998
}

ObjectTemplates:addClientTemplate(object_ship_shared_firespray_tier5, "object/ship/shared_firespray_tier5.iff")

object_ship_shared_freighterheavy = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/cargo_freighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freighterheavy.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2210460492
}

ObjectTemplates:addClientTemplate(object_ship_shared_freighterheavy, "object/ship/shared_freighterheavy.iff")

object_ship_shared_freighterheavy_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/cargo_freighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freighterheavy.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 237176683
}

ObjectTemplates:addClientTemplate(object_ship_shared_freighterheavy_tier1, "object/ship/shared_freighterheavy_tier1.iff")

object_ship_shared_freighterheavy_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/cargo_freighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freighterheavy.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3576999932
}

ObjectTemplates:addClientTemplate(object_ship_shared_freighterheavy_tier2, "object/ship/shared_freighterheavy_tier2.iff")

object_ship_shared_freighterheavy_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/cargo_freighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freighterheavy.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2621032561
}

ObjectTemplates:addClientTemplate(object_ship_shared_freighterheavy_tier3, "object/ship/shared_freighterheavy_tier3.iff")

object_ship_shared_freighterheavy_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/cargo_freighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freighterheavy.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1742398309
}

ObjectTemplates:addClientTemplate(object_ship_shared_freighterheavy_tier4, "object/ship/shared_freighterheavy_tier4.iff")

object_ship_shared_freighterheavy_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/cargo_freighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freighterheavy.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 785876200
}

ObjectTemplates:addClientTemplate(object_ship_shared_freighterheavy_tier5, "object/ship/shared_freighterheavy_tier5.iff")

object_ship_shared_freighterlight = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/cargo_freighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freighterlight.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1117310866
}

ObjectTemplates:addClientTemplate(object_ship_shared_freighterlight, "object/ship/shared_freighterlight.iff")

object_ship_shared_freighterlight_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/cargo_freighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freighterlight.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2981606241
}

ObjectTemplates:addClientTemplate(object_ship_shared_freighterlight_tier1, "object/ship/shared_freighterlight_tier1.iff")

object_ship_shared_freighterlight_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/cargo_freighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freighterlight.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1788877814
}

ObjectTemplates:addClientTemplate(object_ship_shared_freighterlight_tier2, "object/ship/shared_freighterlight_tier2.iff")

object_ship_shared_freighterlight_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/cargo_freighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freighterlight.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 598572155
}

ObjectTemplates:addClientTemplate(object_ship_shared_freighterlight_tier3, "object/ship/shared_freighterlight_tier3.iff")

object_ship_shared_freighterlight_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/cargo_freighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freighterlight.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3629012847
}

ObjectTemplates:addClientTemplate(object_ship_shared_freighterlight_tier4, "object/ship/shared_freighterlight_tier4.iff")

object_ship_shared_freighterlight_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/cargo_freighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freighterlight.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2437099746
}

ObjectTemplates:addClientTemplate(object_ship_shared_freighterlight_tier5, "object/ship/shared_freighterlight_tier5.iff")

object_ship_shared_freightermedium = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/cargo_freighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freightermedium.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3398686729
}

ObjectTemplates:addClientTemplate(object_ship_shared_freightermedium, "object/ship/shared_freightermedium.iff")

object_ship_shared_freightermedium_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/cargo_freighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freightermedium.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1092912234
}

ObjectTemplates:addClientTemplate(object_ship_shared_freightermedium_tier1, "object/ship/shared_freightermedium_tier1.iff")

object_ship_shared_freightermedium_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/cargo_freighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freightermedium.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2587045117
}

ObjectTemplates:addClientTemplate(object_ship_shared_freightermedium_tier2, "object/ship/shared_freightermedium_tier2.iff")

object_ship_shared_freightermedium_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/cargo_freighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freightermedium.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3544075120
}

ObjectTemplates:addClientTemplate(object_ship_shared_freightermedium_tier3, "object/ship/shared_freightermedium_tier3.iff")

object_ship_shared_freightermedium_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/cargo_freighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freightermedium.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 685596772
}

ObjectTemplates:addClientTemplate(object_ship_shared_freightermedium_tier4, "object/ship/shared_freightermedium_tier4.iff")

object_ship_shared_freightermedium_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/cargo_freighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freightermedium.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1641023465
}

ObjectTemplates:addClientTemplate(object_ship_shared_freightermedium_tier5, "object/ship/shared_freightermedium_tier5.iff")

object_ship_shared_hutt_heavy_s01 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_heavy_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1217600546
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_heavy_s01, "object/ship/shared_hutt_heavy_s01.iff")

object_ship_shared_hutt_heavy_s01_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_heavy_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3993388117
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_heavy_s01_tier1, "object/ship/shared_hutt_heavy_s01_tier1.iff")

object_ship_shared_hutt_heavy_s01_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_heavy_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 890367170
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_heavy_s01_tier2, "object/ship/shared_hutt_heavy_s01_tier2.iff")

object_ship_shared_hutt_heavy_s01_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_heavy_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2082245455
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_heavy_s01_tier3, "object/ship/shared_hutt_heavy_s01_tier3.iff")

object_ship_shared_hutt_heavy_s01_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_heavy_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2281676891
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_heavy_s01_tier4, "object/ship/shared_hutt_heavy_s01_tier4.iff")

object_ship_shared_hutt_heavy_s01_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_heavy_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3472017366
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_heavy_s01_tier5, "object/ship/shared_hutt_heavy_s01_tier5.iff")

object_ship_shared_hutt_heavy_s02 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_heavy_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2474947765
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_heavy_s02, "object/ship/shared_hutt_heavy_s02.iff")

object_ship_shared_hutt_heavy_s02_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_heavy_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3761426896
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_heavy_s02_tier1, "object/ship/shared_hutt_heavy_s02_tier1.iff")

object_ship_shared_hutt_heavy_s02_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_heavy_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 992311623
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_heavy_s02_tier2, "object/ship/shared_hutt_heavy_s02_tier2.iff")

object_ship_shared_hutt_heavy_s02_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_heavy_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1915231946
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_heavy_s02_tier3, "object/ship/shared_hutt_heavy_s02_tier3.iff")

object_ship_shared_hutt_heavy_s02_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_heavy_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2311796190
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_heavy_s02_tier4, "object/ship/shared_hutt_heavy_s02_tier4.iff")

object_ship_shared_hutt_heavy_s02_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_heavy_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3234222675
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_heavy_s02_tier5, "object/ship/shared_hutt_heavy_s02_tier5.iff")

object_ship_shared_hutt_light_s01 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1424261752
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_light_s01, "object/ship/shared_hutt_light_s01.iff")

object_ship_shared_hutt_light_s01_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2652622661
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_light_s01_tier1, "object/ship/shared_hutt_light_s01_tier1.iff")

object_ship_shared_hutt_light_s01_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1158440914
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_light_s01_tier2, "object/ship/shared_hutt_light_s01_tier2.iff")

object_ship_shared_hutt_light_s01_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 201392223
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_light_s01_tier3, "object/ship/shared_hutt_light_s01_tier3.iff")

object_ship_shared_hutt_light_s01_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4158794571
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_light_s01_tier4, "object/ship/shared_hutt_light_s01_tier4.iff")

object_ship_shared_hutt_light_s01_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3203353798
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_light_s01_tier5, "object/ship/shared_hutt_light_s01_tier5.iff")

object_ship_shared_hutt_light_s02 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2415078127
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_light_s02, "object/ship/shared_hutt_light_s02.iff")

object_ship_shared_hutt_light_s02_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2419022528
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_light_s02_tier1, "object/ship/shared_hutt_light_s02_tier1.iff")

object_ship_shared_hutt_light_s02_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1262023255
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_light_s02_tier2, "object/ship/shared_hutt_light_s02_tier2.iff")

object_ship_shared_hutt_light_s02_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 37066202
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_light_s02_tier3, "object/ship/shared_hutt_light_s02_tier3.iff")

object_ship_shared_hutt_light_s02_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4191600334
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_light_s02_tier4, "object/ship/shared_hutt_light_s02_tier4.iff")

object_ship_shared_hutt_light_s02_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2967198019
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_light_s02_tier5, "object/ship/shared_hutt_light_s02_tier5.iff")

object_ship_shared_hutt_medium_s01 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_medium_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3267992484
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_medium_s01, "object/ship/shared_hutt_medium_s01.iff")

object_ship_shared_hutt_medium_s01_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_medium_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2698486044
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_medium_s01_tier1, "object/ship/shared_hutt_medium_s01_tier1.iff")

object_ship_shared_hutt_medium_s01_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_medium_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2076182923
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_medium_s01_tier2, "object/ship/shared_hutt_medium_s01_tier2.iff")

object_ship_shared_hutt_medium_s01_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_medium_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 852323846
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_medium_s01_tier3, "object/ship/shared_hutt_medium_s01_tier3.iff")

object_ship_shared_hutt_medium_s01_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_medium_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3375252754
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_medium_s01_tier4, "object/ship/shared_hutt_medium_s01_tier4.iff")

object_ship_shared_hutt_medium_s01_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_medium_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_medium_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2149786271
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_medium_s01_tier5, "object/ship/shared_hutt_medium_s01_tier5.iff")

object_ship_shared_hutt_medium_s02 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_medium_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 433992499
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_medium_s02, "object/ship/shared_hutt_medium_s02.iff")

object_ship_shared_hutt_medium_s02_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_medium_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2934125721
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_medium_s02_tier1, "object/ship/shared_hutt_medium_s02_tier1.iff")

object_ship_shared_hutt_medium_s02_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_medium_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1978965006
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_medium_s02_tier2, "object/ship/shared_hutt_medium_s02_tier2.iff")

object_ship_shared_hutt_medium_s02_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_medium_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1023015811
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_medium_s02_tier3, "object/ship/shared_hutt_medium_s02_tier3.iff")

object_ship_shared_hutt_medium_s02_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_medium_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3340423319
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_medium_s02_tier4, "object/ship/shared_hutt_medium_s02_tier4.iff")

object_ship_shared_hutt_medium_s02_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_medium_body_s02.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_medium_s02.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2383918874
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_medium_s02_tier5, "object/ship/shared_hutt_medium_s02_tier5.iff")

object_ship_shared_hutt_transport = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_transport.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_transport.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 472470685
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_transport, "object/ship/shared_hutt_transport.iff")

object_ship_shared_hutt_transport_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_transport.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_transport.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1397512657
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_transport_tier1, "object/ship/shared_hutt_transport_tier1.iff")

object_ship_shared_hutt_transport_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_transport.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_transport.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2287726918
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_transport_tier2, "object/ship/shared_hutt_transport_tier2.iff")

object_ship_shared_hutt_transport_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_transport.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_transport.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3243677387
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_transport_tier3, "object/ship/shared_hutt_transport_tier3.iff")

object_ship_shared_hutt_transport_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_transport.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_transport.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 984989151
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_transport_tier4, "object/ship/shared_hutt_transport_tier4.iff")

object_ship_shared_hutt_transport_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_transport.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_transport.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1941494354
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_transport_tier5, "object/ship/shared_hutt_transport_tier5.iff")

object_ship_shared_hutt_turret_ship = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s03.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_turret_ship.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2822462280
}

ObjectTemplates:addClientTemplate(object_ship_shared_hutt_turret_ship, "object/ship/shared_hutt_turret_ship.iff")

object_ship_shared_imperial_gunboat = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/imperial_gunboat.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_imperial_gunboat.cdf",
	clientGameObjectType = 536870914,
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

	gameObjectType = 536870914,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:imperial_gunboat",

	noBuildRadius = 0,

	objectName = "@space_ship:imperial_gunboat",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3259306099
}

ObjectTemplates:addClientTemplate(object_ship_shared_imperial_gunboat, "object/ship/shared_imperial_gunboat.iff")

object_ship_shared_imperial_gunboat_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/imperial_gunboat.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_imperial_gunboat.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1910102521
}

ObjectTemplates:addClientTemplate(object_ship_shared_imperial_gunboat_tier1, "object/ship/shared_imperial_gunboat_tier1.iff")

object_ship_shared_imperial_gunboat_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/imperial_gunboat.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_imperial_gunboat.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2865656174
}

ObjectTemplates:addClientTemplate(object_ship_shared_imperial_gunboat_tier2, "object/ship/shared_imperial_gunboat_tier2.iff")

object_ship_shared_imperial_gunboat_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/imperial_gunboat.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_imperial_gunboat.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3821213411
}

ObjectTemplates:addClientTemplate(object_ship_shared_imperial_gunboat_tier3, "object/ship/shared_imperial_gunboat_tier3.iff")

object_ship_shared_imperial_gunboat_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/imperial_gunboat.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_imperial_gunboat.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 404766199
}

ObjectTemplates:addClientTemplate(object_ship_shared_imperial_gunboat_tier4, "object/ship/shared_imperial_gunboat_tier4.iff")

object_ship_shared_imperial_gunboat_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/imperial_gunboat.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_imperial_gunboat.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1361926778
}

ObjectTemplates:addClientTemplate(object_ship_shared_imperial_gunboat_tier5, "object/ship/shared_imperial_gunboat_tier5.iff")

object_ship_shared_lambdashuttle = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/lambda_shuttle_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_lambdashuttle.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 979946526
}

ObjectTemplates:addClientTemplate(object_ship_shared_lambdashuttle, "object/ship/shared_lambdashuttle.iff")

object_ship_shared_lambdashuttle_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/lambda_shuttle_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_lambdashuttle.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1746838902
}

ObjectTemplates:addClientTemplate(object_ship_shared_lambdashuttle_tier1, "object/ship/shared_lambdashuttle_tier1.iff")

object_ship_shared_lambdashuttle_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/lambda_shuttle_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_lambdashuttle.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3003715041
}

ObjectTemplates:addClientTemplate(object_ship_shared_lambdashuttle_tier2, "object/ship/shared_lambdashuttle_tier2.iff")

object_ship_shared_lambdashuttle_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/lambda_shuttle_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_lambdashuttle.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4194593388
}

ObjectTemplates:addClientTemplate(object_ship_shared_lambdashuttle_tier3, "object/ship/shared_lambdashuttle_tier3.iff")

object_ship_shared_lambdashuttle_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/lambda_shuttle_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_lambdashuttle.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 31932792
}

ObjectTemplates:addClientTemplate(object_ship_shared_lambdashuttle_tier4, "object/ship/shared_lambdashuttle_tier4.iff")

object_ship_shared_lambdashuttle_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/lambda_shuttle_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_lambdashuttle.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1223304949
}

ObjectTemplates:addClientTemplate(object_ship_shared_lambdashuttle_tier5, "object/ship/shared_lambdashuttle_tier5.iff")

object_ship_shared_merchant_cruiser_light_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/merchant_cruiser_light.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_merchant_cruiser_light.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2543011646
}

ObjectTemplates:addClientTemplate(object_ship_shared_merchant_cruiser_light_tier1, "object/ship/shared_merchant_cruiser_light_tier1.iff")

object_ship_shared_merchant_cruiser_light_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/merchant_cruiser_light.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_merchant_cruiser_light.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1283780521
}

ObjectTemplates:addClientTemplate(object_ship_shared_merchant_cruiser_light_tier2, "object/ship/shared_merchant_cruiser_light_tier2.iff")

object_ship_shared_merchant_cruiser_light_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/merchant_cruiser_light.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_merchant_cruiser_light.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 92899364
}

ObjectTemplates:addClientTemplate(object_ship_shared_merchant_cruiser_light_tier3, "object/ship/shared_merchant_cruiser_light_tier3.iff")

object_ship_shared_merchant_cruiser_light_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/merchant_cruiser_light.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_merchant_cruiser_light.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4268401456
}

ObjectTemplates:addClientTemplate(object_ship_shared_merchant_cruiser_light_tier4, "object/ship/shared_merchant_cruiser_light_tier4.iff")

object_ship_shared_merchant_cruiser_light_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/merchant_cruiser_light.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_merchant_cruiser_light.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3077031101
}

ObjectTemplates:addClientTemplate(object_ship_shared_merchant_cruiser_light_tier5, "object/ship/shared_merchant_cruiser_light_tier5.iff")

object_ship_shared_merchant_cruiser_medium = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/merchant_cruiser_medium.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_merchant_cruiser_medium.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "@:merchant_cruiser_medium",

	noBuildRadius = 0,

	objectName = "@:merchant_cruiser_medium",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4266302506
}

ObjectTemplates:addClientTemplate(object_ship_shared_merchant_cruiser_medium, "object/ship/shared_merchant_cruiser_medium.iff")

object_ship_shared_merchant_cruiser_medium_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/merchant_cruiser_medium.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_merchant_cruiser_medium.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3883212856
}

ObjectTemplates:addClientTemplate(object_ship_shared_merchant_cruiser_medium_tier1, "object/ship/shared_merchant_cruiser_medium_tier1.iff")

object_ship_shared_merchant_cruiser_medium_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/merchant_cruiser_medium.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_merchant_cruiser_medium.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1013090479
}

ObjectTemplates:addClientTemplate(object_ship_shared_merchant_cruiser_medium_tier2, "object/ship/shared_merchant_cruiser_medium_tier2.iff")

object_ship_shared_merchant_cruiser_medium_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/merchant_cruiser_medium.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_merchant_cruiser_medium.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1970269986
}

ObjectTemplates:addClientTemplate(object_ship_shared_merchant_cruiser_medium_tier3, "object/ship/shared_merchant_cruiser_medium_tier3.iff")

object_ship_shared_merchant_cruiser_medium_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/merchant_cruiser_medium.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_merchant_cruiser_medium.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2391589942
}

ObjectTemplates:addClientTemplate(object_ship_shared_merchant_cruiser_medium_tier4, "object/ship/shared_merchant_cruiser_medium_tier4.iff")

object_ship_shared_merchant_cruiser_medium_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/merchant_cruiser_medium.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_merchant_cruiser_medium.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3347162043
}

ObjectTemplates:addClientTemplate(object_ship_shared_merchant_cruiser_medium_tier5, "object/ship/shared_merchant_cruiser_medium_tier5.iff")

object_ship_shared_nebulon = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/nebulon_frigate.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_nebulon.cdf",
	clientGameObjectType = 536870914,
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

	gameObjectType = 536870914,

	locationReservationRadius = 0,
	lookAtText = "@space/ship_names:nebulon",

	noBuildRadius = 0,

	objectName = "@space/ship_names:nebulon",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2407618193
}

ObjectTemplates:addClientTemplate(object_ship_shared_nebulon, "object/ship/shared_nebulon.iff")

object_ship_shared_probe_droid_pod = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/probe_droid_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_probe_droid_pod.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 327912933
}

ObjectTemplates:addClientTemplate(object_ship_shared_probe_droid_pod, "object/ship/shared_probe_droid_pod.iff")

object_ship_shared_probe_droid_pod_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/probe_droid_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_probe_droid_pod.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2888320846
}

ObjectTemplates:addClientTemplate(object_ship_shared_probe_droid_pod_tier1, "object/ship/shared_probe_droid_pod_tier1.iff")

object_ship_shared_probe_droid_pod_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/probe_droid_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_probe_droid_pod.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2000678873
}

ObjectTemplates:addClientTemplate(object_ship_shared_probe_droid_pod_tier2, "object/ship/shared_probe_droid_pod_tier2.iff")

object_ship_shared_probe_droid_pod_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/probe_droid_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_probe_droid_pod.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1043499092
}

ObjectTemplates:addClientTemplate(object_ship_shared_probe_droid_pod_tier3, "object/ship/shared_probe_droid_pod_tier3.iff")

object_ship_shared_probe_droid_pod_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/probe_droid_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_probe_droid_pod.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3318850368
}

ObjectTemplates:addClientTemplate(object_ship_shared_probe_droid_pod_tier4, "object/ship/shared_probe_droid_pod_tier4.iff")

object_ship_shared_probe_droid_pod_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/probe_droid_pod.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_probe_droid_pod.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2363278541
}

ObjectTemplates:addClientTemplate(object_ship_shared_probe_droid_pod_tier5, "object/ship/shared_probe_droid_pod_tier5.iff")

object_ship_shared_prototype_hutt_light = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s01.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:hutt_light",

	noBuildRadius = 0,

	objectName = "@:prototype_hutt_light",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1036884978
}

ObjectTemplates:addClientTemplate(object_ship_shared_prototype_hutt_light, "object/ship/shared_prototype_hutt_light.iff")

object_ship_shared_prototype_tiefighter = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiefighter.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:tiefighter swg-se test",

	noBuildRadius = 0,

	objectName = "@:prototype_tie",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2160427278
}

ObjectTemplates:addClientTemplate(object_ship_shared_prototype_tiefighter, "object/ship/shared_prototype_tiefighter.iff")

object_ship_shared_prototype_z95 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/z95_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_z95.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:z95 swg-se test",

	noBuildRadius = 0,

	objectName = "@:z95_prototype",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1141820662
}

ObjectTemplates:addClientTemplate(object_ship_shared_prototype_z95, "object/ship/shared_prototype_z95.iff")

object_ship_shared_rebel_gunboat = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/rebel_gunboat.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_rebel_gunboat.cdf",
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
	lookAtText = "@space_ship:rebel_gunboat",

	noBuildRadius = 0,

	objectName = "@space_ship:rebel_gunboat",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3542721164
}

ObjectTemplates:addClientTemplate(object_ship_shared_rebel_gunboat, "object/ship/shared_rebel_gunboat.iff")

object_ship_shared_rebel_gunboat_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/rebel_gunboat.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_rebel_gunboat.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 137363241
}

ObjectTemplates:addClientTemplate(object_ship_shared_rebel_gunboat_tier1, "object/ship/shared_rebel_gunboat_tier1.iff")

object_ship_shared_rebel_gunboat_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/rebel_gunboat.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_rebel_gunboat.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3543685054
}

ObjectTemplates:addClientTemplate(object_ship_shared_rebel_gunboat_tier2, "object/ship/shared_rebel_gunboat_tier2.iff")

object_ship_shared_rebel_gunboat_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/rebel_gunboat.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_rebel_gunboat.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2587177011
}

ObjectTemplates:addClientTemplate(object_ship_shared_rebel_gunboat_tier3, "object/ship/shared_rebel_gunboat_tier3.iff")

object_ship_shared_rebel_gunboat_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/rebel_gunboat.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_rebel_gunboat.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1641421607
}

ObjectTemplates:addClientTemplate(object_ship_shared_rebel_gunboat_tier4, "object/ship/shared_rebel_gunboat_tier4.iff")

object_ship_shared_rebel_gunboat_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/rebel_gunboat.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_rebel_gunboat.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 685472938
}

ObjectTemplates:addClientTemplate(object_ship_shared_rebel_gunboat_tier5, "object/ship/shared_rebel_gunboat_tier5.iff")

object_ship_shared_rebel_shuttle_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/shuttle_rebel.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_rebel_shuttle.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 282943774
}

ObjectTemplates:addClientTemplate(object_ship_shared_rebel_shuttle_tier1, "object/ship/shared_rebel_shuttle_tier1.iff")

object_ship_shared_rebel_shuttle_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/shuttle_rebel.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_rebel_shuttle.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3419064713
}

ObjectTemplates:addClientTemplate(object_ship_shared_rebel_shuttle_tier2, "object/ship/shared_rebel_shuttle_tier2.iff")

object_ship_shared_rebel_shuttle_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/shuttle_rebel.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_rebel_shuttle.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2194124292
}

ObjectTemplates:addClientTemplate(object_ship_shared_rebel_shuttle_tier3, "object/ship/shared_rebel_shuttle_tier3.iff")

object_ship_shared_rebel_shuttle_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/shuttle_rebel.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_rebel_shuttle.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2032436496
}

ObjectTemplates:addClientTemplate(object_ship_shared_rebel_shuttle_tier4, "object/ship/shared_rebel_shuttle_tier4.iff")

object_ship_shared_rebel_shuttle_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/shuttle_rebel.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_rebel_shuttle.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 808051357
}

ObjectTemplates:addClientTemplate(object_ship_shared_rebel_shuttle_tier5, "object/ship/shared_rebel_shuttle_tier5.iff")

object_ship_shared_smuggler_warlord_ship_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/smuggler_warlord_ship.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_smuggler_warlord_ship.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1243384778
}

ObjectTemplates:addClientTemplate(object_ship_shared_smuggler_warlord_ship_tier1, "object/ship/shared_smuggler_warlord_ship_tier1.iff")

object_ship_shared_smuggler_warlord_ship_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/smuggler_warlord_ship.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_smuggler_warlord_ship.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2433426269
}

ObjectTemplates:addClientTemplate(object_ship_shared_smuggler_warlord_ship_tier2, "object/ship/shared_smuggler_warlord_ship_tier2.iff")

object_ship_shared_smuggler_warlord_ship_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/smuggler_warlord_ship.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_smuggler_warlord_ship.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3624289488
}

ObjectTemplates:addClientTemplate(object_ship_shared_smuggler_warlord_ship_tier3, "object/ship/shared_smuggler_warlord_ship_tier3.iff")

object_ship_shared_smuggler_warlord_ship_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/smuggler_warlord_ship.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_smuggler_warlord_ship.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 602238916
}

ObjectTemplates:addClientTemplate(object_ship_shared_smuggler_warlord_ship_tier4, "object/ship/shared_smuggler_warlord_ship_tier4.iff")

object_ship_shared_smuggler_warlord_ship_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/smuggler_warlord_ship.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_smuggler_warlord_ship.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1793591369
}

ObjectTemplates:addClientTemplate(object_ship_shared_smuggler_warlord_ship_tier5, "object/ship/shared_smuggler_warlord_ship_tier5.iff")

object_ship_shared_sorosuub_space_yacht = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/sorosuub_space_yacht_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_sorosuub_space_yacht.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:sorosuub_space_yacht",

	noBuildRadius = 0,

	objectName = "@ship_n:sorosuub_space_yacht",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2502364217
}

ObjectTemplates:addClientTemplate(object_ship_shared_sorosuub_space_yacht, "object/ship/shared_sorosuub_space_yacht.iff")

object_ship_shared_spacestation_imperial = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/spacestation_outpost_imperial_s01.apt",
	arrangementDescriptors = {"ship_control_device"},

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

	detailedDescription = "string_id_table",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:spacestation_imperial",

	noBuildRadius = 0,

	objectName = "@space_ship:spacestation_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3165332223
}

ObjectTemplates:addClientTemplate(object_ship_shared_spacestation_imperial, "object/ship/shared_spacestation_imperial.iff")

object_ship_shared_spacestation_neutral = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/spacestation_neutral.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_spacestation_neutral.cdf",
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

	detailedDescription = "string_id_table",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:spacestation_neutral",

	noBuildRadius = 0,

	objectName = "@space_ship:spacestation_neutral",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4164831037
}

ObjectTemplates:addClientTemplate(object_ship_shared_spacestation_neutral, "object/ship/shared_spacestation_neutral.iff")

object_ship_shared_spacestation_rebel = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/spacestation_rebel.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_spacestation_rebel.cdf",
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

	detailedDescription = "string_id_table",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@space_ship:spacestation_rebel",

	noBuildRadius = 0,

	objectName = "@space_ship:spacestation_rebel",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 431716433
}

ObjectTemplates:addClientTemplate(object_ship_shared_spacestation_rebel, "object/ship/shared_spacestation_rebel.iff")

object_ship_shared_star_destroyer = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/star_destroyer_space.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_star_destroyer.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3207599336
}

ObjectTemplates:addClientTemplate(object_ship_shared_star_destroyer, "object/ship/shared_star_destroyer.iff")

object_ship_shared_supplyship = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/distant_supplyship.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_freighterlight.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4043601537
}

ObjectTemplates:addClientTemplate(object_ship_shared_supplyship, "object/ship/shared_supplyship.iff")

object_ship_shared_tie_in = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter_in.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiefighter.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:tie_in",

	noBuildRadius = 0,

	objectName = "@:tie_in",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1874889307
}

ObjectTemplates:addClientTemplate(object_ship_shared_tie_in, "object/ship/shared_tie_in.iff")

object_ship_shared_tie_light_duty = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tie_light_duty.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:tie_light_duty",

	noBuildRadius = 0,

	objectName = "@:tie_light_duty",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1231580532
}

ObjectTemplates:addClientTemplate(object_ship_shared_tie_light_duty, "object/ship/shared_tie_light_duty.iff")

object_ship_shared_tieadvanced = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_advanced.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieadvanced.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 212073063
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieadvanced, "object/ship/shared_tieadvanced.iff")

object_ship_shared_tieadvanced_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_advanced.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieadvanced.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4294368666
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieadvanced_tier1, "object/ship/shared_tieadvanced_tier1.iff")

object_ship_shared_tieadvanced_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_advanced.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieadvanced.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 618755341
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieadvanced_tier2, "object/ship/shared_tieadvanced_tier2.iff")

object_ship_shared_tieadvanced_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_advanced.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieadvanced.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1844187776
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieadvanced_tier3, "object/ship/shared_tieadvanced_tier3.iff")

object_ship_shared_tieadvanced_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_advanced.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieadvanced.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2517580180
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieadvanced_tier4, "object/ship/shared_tieadvanced_tier4.iff")

object_ship_shared_tieadvanced_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_advanced.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieadvanced.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3741474329
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieadvanced_tier5, "object/ship/shared_tieadvanced_tier5.iff")

object_ship_shared_tieaggressor = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_aggressor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieaggressor.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3457688983
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieaggressor, "object/ship/shared_tieaggressor.iff")

object_ship_shared_tieaggressor_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_aggressor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieadvanced.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1918801119
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieaggressor_tier1, "object/ship/shared_tieaggressor_tier1.iff")

object_ship_shared_tieaggressor_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_aggressor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieadvanced.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2840149064
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieaggressor_tier2, "object/ship/shared_tieaggressor_tier2.iff")

object_ship_shared_tieaggressor_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_aggressor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieadvanced.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3762576325
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieaggressor_tier3, "object/ship/shared_tieaggressor_tier3.iff")

object_ship_shared_tieaggressor_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_aggressor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieadvanced.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 463958225
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieaggressor_tier4, "object/ship/shared_tieaggressor_tier4.iff")

object_ship_shared_tieaggressor_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_aggressor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieadvanced.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1386878812
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieaggressor_tier5, "object/ship/shared_tieaggressor_tier5.iff")

object_ship_shared_tiebomber = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_bomber_b.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/ship/client_shared_tiebomber.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1689489833
}

ObjectTemplates:addClientTemplate(object_ship_shared_tiebomber, "object/ship/shared_tiebomber.iff")

object_ship_shared_tiebomber_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_bomber_b.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiebomber.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 800011159
}

ObjectTemplates:addClientTemplate(object_ship_shared_tiebomber_tier1, "object/ship/shared_tiebomber_tier1.iff")

object_ship_shared_tiebomber_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_bomber_b.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiebomber.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4105739008
}

ObjectTemplates:addClientTemplate(object_ship_shared_tiebomber_tier2, "object/ship/shared_tiebomber_tier2.iff")

object_ship_shared_tiebomber_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_bomber_b.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiebomber.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3182820493
}

ObjectTemplates:addClientTemplate(object_ship_shared_tiebomber_tier3, "object/ship/shared_tiebomber_tier3.iff")

object_ship_shared_tiebomber_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_bomber_b.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiebomber.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1180096409
}

ObjectTemplates:addClientTemplate(object_ship_shared_tiebomber_tier4, "object/ship/shared_tiebomber_tier4.iff")

object_ship_shared_tiebomber_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_bomber_b.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiebomber.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 257667092
}

ObjectTemplates:addClientTemplate(object_ship_shared_tiebomber_tier5, "object/ship/shared_tiebomber_tier5.iff")

object_ship_shared_tiefighter = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiefighter.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2677969389
}

ObjectTemplates:addClientTemplate(object_ship_shared_tiefighter, "object/ship/shared_tiefighter.iff")

object_ship_shared_tiefighter_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiefighter.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 719737899
}

ObjectTemplates:addClientTemplate(object_ship_shared_tiefighter_tier1, "object/ship/shared_tiefighter_tier1.iff")

object_ship_shared_tiefighter_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiefighter.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4059167932
}

ObjectTemplates:addClientTemplate(object_ship_shared_tiefighter_tier2, "object/ship/shared_tiefighter_tier2.iff")

object_ship_shared_tiefighter_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiefighter.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3103562545
}

ObjectTemplates:addClientTemplate(object_ship_shared_tiefighter_tier3, "object/ship/shared_tiefighter_tier3.iff")

object_ship_shared_tiefighter_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiefighter.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1126150181
}

ObjectTemplates:addClientTemplate(object_ship_shared_tiefighter_tier4, "object/ship/shared_tiefighter_tier4.iff")

object_ship_shared_tiefighter_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tiefighter.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 169007016
}

ObjectTemplates:addClientTemplate(object_ship_shared_tiefighter_tier5, "object/ship/shared_tiefighter_tier5.iff")

object_ship_shared_tieinterceptor = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_interceptor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieinterceptor.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2986877248
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieinterceptor, "object/ship/shared_tieinterceptor.iff")

object_ship_shared_tieinterceptor_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_interceptor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieinterceptor.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3034789135
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieinterceptor_tier1, "object/ship/shared_tieinterceptor_tier1.iff")

object_ship_shared_tieinterceptor_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_interceptor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieinterceptor.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1878302104
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieinterceptor_tier2, "object/ship/shared_tieinterceptor_tier2.iff")

object_ship_shared_tieinterceptor_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_interceptor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieinterceptor.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 653916693
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieinterceptor_tier3, "object/ship/shared_tieinterceptor_tier3.iff")

object_ship_shared_tieinterceptor_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_interceptor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieinterceptor.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3709522177
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieinterceptor_tier4, "object/ship/shared_tieinterceptor_tier4.iff")

object_ship_shared_tieinterceptor_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_interceptor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieinterceptor.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2484582028
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieinterceptor_tier5, "object/ship/shared_tieinterceptor_tier5.iff")

object_ship_shared_tieoppressor = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_oppressor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieoppressor.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3234528257
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieoppressor, "object/ship/shared_tieoppressor.iff")

object_ship_shared_tieoppressor_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_oppressor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieoppressor.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3138516559
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieoppressor_tier1, "object/ship/shared_tieoppressor_tier1.iff")

object_ship_shared_tieoppressor_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_oppressor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieoppressor.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1611030232
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieoppressor_tier2, "object/ship/shared_tieoppressor_tier2.iff")

object_ship_shared_tieoppressor_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_oppressor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieoppressor.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 688601429
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieoppressor_tier3, "object/ship/shared_tieoppressor_tier3.iff")

object_ship_shared_tieoppressor_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_oppressor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieoppressor.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3538424385
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieoppressor_tier4, "object/ship/shared_tieoppressor_tier4.iff")

object_ship_shared_tieoppressor_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/tie_oppressor.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_tieoppressor.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2615506380
}

ObjectTemplates:addClientTemplate(object_ship_shared_tieoppressor_tier5, "object/ship/shared_tieoppressor_tier5.iff")

object_ship_shared_transport_science = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/transport_science.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_transport_science.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "@:transport_science",

	noBuildRadius = 0,

	objectName = "@:transport_science",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1879411884
}

ObjectTemplates:addClientTemplate(object_ship_shared_transport_science, "object/ship/shared_transport_science.iff")

object_ship_shared_transport_science_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/transport_science.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_transport_science.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1650455622
}

ObjectTemplates:addClientTemplate(object_ship_shared_transport_science_tier1, "object/ship/shared_transport_science_tier1.iff")

object_ship_shared_transport_science_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/transport_science.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_transport_science.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3108527313
}

ObjectTemplates:addClientTemplate(object_ship_shared_transport_science_tier2, "object/ship/shared_transport_science_tier2.iff")

object_ship_shared_transport_science_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/transport_science.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_transport_science.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4031069020
}

ObjectTemplates:addClientTemplate(object_ship_shared_transport_science_tier3, "object/ship/shared_transport_science_tier3.iff")

object_ship_shared_transport_science_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/transport_science.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_transport_science.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 195432520
}

ObjectTemplates:addClientTemplate(object_ship_shared_transport_science_tier4, "object/ship/shared_transport_science_tier4.iff")

object_ship_shared_transport_science_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/transport_science.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_transport_science.cdf",
	clientGameObjectType = 536870916,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 536870916,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1118533573
}

ObjectTemplates:addClientTemplate(object_ship_shared_transport_science_tier5, "object/ship/shared_transport_science_tier5.iff")

object_ship_shared_xwing = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/xwing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_xwing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1476764354
}

ObjectTemplates:addClientTemplate(object_ship_shared_xwing, "object/ship/shared_xwing.iff")

object_ship_shared_xwing_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/xwing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_xwing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1201246834
}

ObjectTemplates:addClientTemplate(object_ship_shared_xwing_tier1, "object/ship/shared_xwing_tier1.iff")

object_ship_shared_xwing_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/xwing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_xwing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2626566885
}

ObjectTemplates:addClientTemplate(object_ship_shared_xwing_tier2, "object/ship/shared_xwing_tier2.iff")

object_ship_shared_xwing_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/xwing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_xwing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3582156136
}

ObjectTemplates:addClientTemplate(object_ship_shared_xwing_tier3, "object/ship/shared_xwing_tier3.iff")

object_ship_shared_xwing_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/xwing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_xwing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 778073724
}

ObjectTemplates:addClientTemplate(object_ship_shared_xwing_tier4, "object/ship/shared_xwing_tier4.iff")

object_ship_shared_xwing_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/xwing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_xwing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1735201265
}

ObjectTemplates:addClientTemplate(object_ship_shared_xwing_tier5, "object/ship/shared_xwing_tier5.iff")

object_ship_shared_ykl37r = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/ykl37r_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:ykl37r",

	noBuildRadius = 0,

	objectName = "@ship_n:ykl37r",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2370729898
}

ObjectTemplates:addClientTemplate(object_ship_shared_ykl37r, "object/ship/shared_ykl37r.iff")

object_ship_shared_ykl37r_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/ykl37r_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:ykl37r",

	noBuildRadius = 0,

	objectName = "@ship_n:ykl37r",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 212362802
}

ObjectTemplates:addClientTemplate(object_ship_shared_ykl37r_tier1, "object/ship/shared_ykl37r_tier1.iff")

object_ship_shared_ykl37r_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/ykl37r_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:ykl37r",

	noBuildRadius = 0,

	objectName = "@ship_n:ykl37r",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3619671717
}

ObjectTemplates:addClientTemplate(object_ship_shared_ykl37r_tier2, "object/ship/shared_ykl37r_tier2.iff")

object_ship_shared_ykl37r_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/ykl37r_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:ykl37r",

	noBuildRadius = 0,

	objectName = "@ship_n:ykl37r",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2662508840
}

ObjectTemplates:addClientTemplate(object_ship_shared_ykl37r_tier3, "object/ship/shared_ykl37r_tier3.iff")

object_ship_shared_ykl37r_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/ykl37r_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:ykl37r",

	noBuildRadius = 0,

	objectName = "@ship_n:ykl37r",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1699840572
}

ObjectTemplates:addClientTemplate(object_ship_shared_ykl37r_tier4, "object/ship/shared_ykl37r_tier4.iff")

object_ship_shared_ykl37r_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/ykl37r_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:ykl37r",

	noBuildRadius = 0,

	objectName = "@ship_n:ykl37r",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 744285617
}

ObjectTemplates:addClientTemplate(object_ship_shared_ykl37r_tier5, "object/ship/shared_ykl37r_tier5.iff")

object_ship_shared_yt1300 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/yt1300_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_yt1300.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4019421648
}

ObjectTemplates:addClientTemplate(object_ship_shared_yt1300, "object/ship/shared_yt1300.iff")

object_ship_shared_yt1300_interior = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/yt1300_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_yt1300.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1347113891
}

ObjectTemplates:addClientTemplate(object_ship_shared_yt1300_interior, "object/ship/shared_yt1300_interior.iff")

object_ship_shared_yt1300_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/yt1300_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_yt1300.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3582257391
}

ObjectTemplates:addClientTemplate(object_ship_shared_yt1300_tier1, "object/ship/shared_yt1300_tier1.iff")

object_ship_shared_yt1300_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/yt1300_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_yt1300.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 244531320
}

ObjectTemplates:addClientTemplate(object_ship_shared_yt1300_tier2, "object/ship/shared_yt1300_tier2.iff")

object_ship_shared_yt1300_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/yt1300_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_yt1300.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1201547253
}

ObjectTemplates:addClientTemplate(object_ship_shared_yt1300_tier3, "object/ship/shared_yt1300_tier3.iff")

object_ship_shared_yt1300_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/yt1300_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_yt1300.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3162311905
}

ObjectTemplates:addClientTemplate(object_ship_shared_yt1300_tier4, "object/ship/shared_yt1300_tier4.iff")

object_ship_shared_yt1300_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/yt1300_npc.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_yt1300.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4117785452
}

ObjectTemplates:addClientTemplate(object_ship_shared_yt1300_tier5, "object/ship/shared_yt1300_tier5.iff")

object_ship_shared_ywing = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/ywing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_ywing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2852456612
}

ObjectTemplates:addClientTemplate(object_ship_shared_ywing, "object/ship/shared_ywing.iff")

object_ship_shared_ywing_longprobe = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/ywing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_ywing_longprobe.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:ywing_lp",

	noBuildRadius = 0,

	objectName = "@:ywing_lp",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3553113506
}

ObjectTemplates:addClientTemplate(object_ship_shared_ywing_longprobe, "object/ship/shared_ywing_longprobe.iff")

object_ship_shared_ywing_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/ywing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_ywing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2593551104
}

ObjectTemplates:addClientTemplate(object_ship_shared_ywing_tier1, "object/ship/shared_ywing_tier1.iff")

object_ship_shared_ywing_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/ywing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_ywing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1099029399
}

ObjectTemplates:addClientTemplate(object_ship_shared_ywing_tier2, "object/ship/shared_ywing_tier2.iff")

object_ship_shared_ywing_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/ywing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_ywing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 143440922
}

ObjectTemplates:addClientTemplate(object_ship_shared_ywing_tier3, "object/ship/shared_ywing_tier3.iff")

object_ship_shared_ywing_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/ywing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_ywing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4084176654
}

ObjectTemplates:addClientTemplate(object_ship_shared_ywing_tier4, "object/ship/shared_ywing_tier4.iff")

object_ship_shared_ywing_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/ywing_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_ywing.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3127046275
}

ObjectTemplates:addClientTemplate(object_ship_shared_ywing_tier5, "object/ship/shared_ywing_tier5.iff")

object_ship_shared_z95 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/z95_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_z95.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "@:xwing swg-se test",

	noBuildRadius = 0,

	objectName = "@:xwing swg-sw test",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 3963433956
}

ObjectTemplates:addClientTemplate(object_ship_shared_z95, "object/ship/shared_z95.iff")

object_ship_shared_z95_tier1 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/z95_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_z95.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 603334641
}

ObjectTemplates:addClientTemplate(object_ship_shared_z95_tier1, "object/ship/shared_z95_tier1.iff")

object_ship_shared_z95_tier2 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/z95_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_z95.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 4175531878
}

ObjectTemplates:addClientTemplate(object_ship_shared_z95_tier2, "object/ship/shared_z95_tier2.iff")

object_ship_shared_z95_tier3 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/z95_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_z95.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 2985093355
}

ObjectTemplates:addClientTemplate(object_ship_shared_z95_tier3, "object/ship/shared_z95_tier3.iff")

object_ship_shared_z95_tier4 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/z95_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_z95.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 1242547199
}

ObjectTemplates:addClientTemplate(object_ship_shared_z95_tier4, "object/ship/shared_z95_tier4.iff")

object_ship_shared_z95_tier5 = SharedShipObjectTemplate:new {
	appearanceFilename = "appearance/z95_body.apt",
	arrangementDescriptors = {"ship_control_device"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_z95.cdf",
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

	detailedDescription = "",

	gameObjectType = 536870913,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

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

	clientObjectCRC = 50504818
}

ObjectTemplates:addClientTemplate(object_ship_shared_z95_tier5, "object/ship/shared_z95_tier5.iff")
