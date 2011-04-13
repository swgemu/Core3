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


object_intangible_ship_shared_awing_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/awing_body.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_awing_pcd.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:awing_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:awing_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3231609067
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_awing_pcd, "object/intangible/ship/shared_awing_pcd.iff")

object_intangible_ship_shared_basic_hutt_light_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s01.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_d:newbie_ship",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:hutt_light_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3117731697
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_basic_hutt_light_pcd, "object/intangible/ship/shared_basic_hutt_light_pcd.iff")

object_intangible_ship_shared_basic_tiefighter_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_d:newbie_ship",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:tiefighter_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3542586269
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_basic_tiefighter_pcd, "object/intangible/ship/shared_basic_tiefighter_pcd.iff")

object_intangible_ship_shared_basic_z95_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/z95_body.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_d:newbie_ship",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:z95_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1951744339
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_basic_z95_pcd, "object/intangible/ship/shared_basic_z95_pcd.iff")

object_intangible_ship_shared_blacksun_heavy_s01_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_heavy_pcd_s01.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:blacksun_heavy_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:blacksun_heavy_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1920551856
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_blacksun_heavy_s01_pcd, "object/intangible/ship/shared_blacksun_heavy_s01_pcd.iff")

object_intangible_ship_shared_blacksun_heavy_s02_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_heavy_pcd_s02.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:blacksun_heavy_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:blacksun_heavy_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1622780077
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_blacksun_heavy_s02_pcd, "object/intangible/ship/shared_blacksun_heavy_s02_pcd.iff")

object_intangible_ship_shared_blacksun_heavy_s03_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_heavy_pcd_s03.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:blacksun_heavy_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:blacksun_heavy_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2461598411
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_blacksun_heavy_s03_pcd, "object/intangible/ship/shared_blacksun_heavy_s03_pcd.iff")

object_intangible_ship_shared_blacksun_heavy_s04_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s02.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_heavy_pcd_s04.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:blacksun_heavy_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:blacksun_heavy_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1161326231
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_blacksun_heavy_s04_pcd, "object/intangible/ship/shared_blacksun_heavy_s04_pcd.iff")

object_intangible_ship_shared_blacksun_light_s01_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_light_pcd_s01.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:blacksun_light_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:blacksun_light_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4287843959
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_blacksun_light_s01_pcd, "object/intangible/ship/shared_blacksun_light_s01_pcd.iff")

object_intangible_ship_shared_blacksun_light_s02_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_light_pcd_s02.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:blacksun_light_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:blacksun_light_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3981684074
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_blacksun_light_s02_pcd, "object/intangible/ship/shared_blacksun_light_s02_pcd.iff")

object_intangible_ship_shared_blacksun_light_s03_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s02.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_light_pcd_s01.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:blacksun_light_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:blacksun_light_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 525534988
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_blacksun_light_s03_pcd, "object/intangible/ship/shared_blacksun_light_s03_pcd.iff")

object_intangible_ship_shared_blacksun_light_s04_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s02.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_light_pcd_s02.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:blacksun_light_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:blacksun_light_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3369233232
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_blacksun_light_s04_pcd, "object/intangible/ship/shared_blacksun_light_s04_pcd.iff")

object_intangible_ship_shared_blacksun_medium_s01_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_medium_pcd_s01.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:blacksun_medium_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:blacksun_medium_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3830604387
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_blacksun_medium_s01_pcd, "object/intangible/ship/shared_blacksun_medium_s01_pcd.iff")

object_intangible_ship_shared_blacksun_medium_s02_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_medium_pcd_s02.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:blacksun_medium_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:blacksun_medium_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4136796542
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_blacksun_medium_s02_pcd, "object/intangible/ship/shared_blacksun_medium_s02_pcd.iff")

object_intangible_ship_shared_blacksun_medium_s03_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s02.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_medium_pcd_s01.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:blacksun_medium_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:blacksun_medium_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 76688152
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_blacksun_medium_s03_pcd, "object/intangible/ship/shared_blacksun_medium_s03_pcd.iff")

object_intangible_ship_shared_blacksun_medium_s04_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s02.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_medium_pcd_s02.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:blacksun_medium_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:blacksun_medium_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3541256004
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_blacksun_medium_s04_pcd, "object/intangible/ship/shared_blacksun_medium_s04_pcd.iff")

object_intangible_ship_shared_bwing_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/bwing_cockpit_pod.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_bwing_pcd.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:bwing_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:bwing_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4256405331
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_bwing_pcd, "object/intangible/ship/shared_bwing_pcd.iff")

object_intangible_ship_shared_decimator_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/vt49_npc.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_decimator_pcd.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:decimator_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:decimator_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 816398955
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_decimator_pcd, "object/intangible/ship/shared_decimator_pcd.iff")

object_intangible_ship_shared_firespray_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/kse_firespray_body.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_firespray_pcd.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:firespray_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:firespray_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3214165542
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_firespray_pcd, "object/intangible/ship/shared_firespray_pcd.iff")

object_intangible_ship_shared_hutt_heavy_s01_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_hutt_heavy_pcd_s01.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:hutt_heavy_s01_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:hutt_heavy_s01_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2913916856
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_hutt_heavy_s01_pcd, "object/intangible/ship/shared_hutt_heavy_s01_pcd.iff")

object_intangible_ship_shared_hutt_heavy_s02_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_hutt_heavy_pcd_s02.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:hutt_heavy_s02_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:hutt_heavy_s02_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3211670693
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_hutt_heavy_s02_pcd, "object/intangible/ship/shared_hutt_heavy_s02_pcd.iff")

object_intangible_ship_shared_hutt_light_s01_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_hutt_light_pcd_s01.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:hutt_light_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:hutt_light_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 541381247
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_hutt_light_s01_pcd, "object/intangible/ship/shared_hutt_light_s01_pcd.iff")

object_intangible_ship_shared_hutt_light_s02_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_hutt_light_pcd_s02.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:hutt_light_s02_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:hutt_light_s02_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 847524194
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_hutt_light_s02_pcd, "object/intangible/ship/shared_hutt_light_s02_pcd.iff")

object_intangible_ship_shared_hutt_medium_s01_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_medium_body_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_hutt_medium_pcd_s01.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:hutt_medium_s01_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:hutt_medium_s01_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 437951543
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_hutt_medium_s01_pcd, "object/intangible/ship/shared_hutt_medium_s01_pcd.iff")

object_intangible_ship_shared_hutt_medium_s02_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_medium_body_s02.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_hutt_medium_pcd_s02.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:hutt_medium_s02_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:hutt_medium_s02_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 148537130
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_hutt_medium_s02_pcd, "object/intangible/ship/shared_hutt_medium_s02_pcd.iff")

object_intangible_ship_shared_hutt_turret_ship_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s03.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_hutt_turret_ship.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:hutt_turret_ship_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:hutt_turret_ship_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3431555714
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_hutt_turret_ship_pcd, "object/intangible/ship/shared_hutt_turret_ship_pcd.iff")

object_intangible_ship_shared_navicomputer_1 = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_droidinterface_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2059,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "",

	gameObjectType = 2059,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"inventory", "datapad"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3404705593
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_navicomputer_1, "object/intangible/ship/shared_navicomputer_1.iff")

object_intangible_ship_shared_navicomputer_2 = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_droidinterface_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2059,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "",

	gameObjectType = 2059,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"inventory", "datapad"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 301467566
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_navicomputer_2, "object/intangible/ship/shared_navicomputer_2.iff")

object_intangible_ship_shared_navicomputer_3 = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_droidinterface_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2059,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "",

	gameObjectType = 2059,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"inventory", "datapad"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1492475939
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_navicomputer_3, "object/intangible/ship/shared_navicomputer_3.iff")

object_intangible_ship_shared_navicomputer_4 = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_droidinterface_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2059,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "",

	gameObjectType = 2059,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"inventory", "datapad"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2736147255
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_navicomputer_4, "object/intangible/ship/shared_navicomputer_4.iff")

object_intangible_ship_shared_navicomputer_5 = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_droidinterface_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2059,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "",

	gameObjectType = 2059,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"inventory", "datapad"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3927649466
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_navicomputer_5, "object/intangible/ship/shared_navicomputer_5.iff")

object_intangible_ship_shared_navicomputer_6 = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_droidinterface_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2059,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "",

	gameObjectType = 2059,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"inventory", "datapad"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 822903853
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_navicomputer_6, "object/intangible/ship/shared_navicomputer_6.iff")

object_intangible_ship_shared_navicomputer_base = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_droidinterface_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2059,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "",

	gameObjectType = 2059,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"inventory", "datapad"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1537107009
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_navicomputer_base, "object/intangible/ship/shared_navicomputer_base.iff")

object_intangible_ship_shared_prototype_hutt_light_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s01.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_d:prototype_ship",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:hutt_light_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3320786901
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_prototype_hutt_light_pcd, "object/intangible/ship/shared_prototype_hutt_light_pcd.iff")

object_intangible_ship_shared_prototype_tiefighter_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_d:prototype_Ship",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:tiefighter_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2937877305
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_prototype_tiefighter_pcd, "object/intangible/ship/shared_prototype_tiefighter_pcd.iff")

object_intangible_ship_shared_prototype_z95_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/z95_body.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_d:prototype_ship",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:z95_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3760715561
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_prototype_z95_pcd, "object/intangible/ship/shared_prototype_z95_pcd.iff")

object_intangible_ship_shared_sorosuub_space_yacht_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/sorosuub_space_yacht_npc.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:sorosuub_space_yacht_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:sorosuub_space_yacht_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 264594860
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_sorosuub_space_yacht_pcd, "object/intangible/ship/shared_sorosuub_space_yacht_pcd.iff")

object_intangible_ship_shared_tie_in_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:tie_in_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:tie_in_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4072676654
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_tie_in_pcd, "object/intangible/ship/shared_tie_in_pcd.iff")

object_intangible_ship_shared_tie_light_duty_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:tie_light_duty_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:tie_light_duty_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3211390
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_tie_light_duty_pcd, "object/intangible/ship/shared_tie_light_duty_pcd.iff")

object_intangible_ship_shared_tieadvanced_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_advanced.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:tieadvanced_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:tieadvanced_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3041041630
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_tieadvanced_pcd, "object/intangible/ship/shared_tieadvanced_pcd.iff")

object_intangible_ship_shared_tieaggressor_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_aggressor.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:tieaggressor_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:tieaggressor_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3555369555
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_tieaggressor_pcd, "object/intangible/ship/shared_tieaggressor_pcd.iff")

object_intangible_ship_shared_tiebomber_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_bomber_b.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:tiebomber_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:tiebomber_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3994408379
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_tiebomber_pcd, "object/intangible/ship/shared_tiebomber_pcd.iff")

object_intangible_ship_shared_tiefighter_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:tiefighter_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:tiefighter_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2741040950
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_tiefighter_pcd, "object/intangible/ship/shared_tiefighter_pcd.iff")

object_intangible_ship_shared_tieinterceptor_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_interceptor.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:tieinterceptor_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:tieinterceptor_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4152772827
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_tieinterceptor_pcd, "object/intangible/ship/shared_tieinterceptor_pcd.iff")

object_intangible_ship_shared_tieoppressor_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_oppressor.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:tieoppressor_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:tieoppressor_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3673716446
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_tieoppressor_pcd, "object/intangible/ship/shared_tieoppressor_pcd.iff")

object_intangible_ship_shared_xwing_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/xwing_body.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_xwing_pcd.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:test_xwing_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:test_xwing_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3314812569
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_xwing_pcd, "object/intangible/ship/shared_xwing_pcd.iff")

object_intangible_ship_shared_ykl37r_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ykl37r_npc.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_ykl37r_pcd.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:ykl37r_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:ykl37r_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1454524572
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_ykl37r_pcd, "object/intangible/ship/shared_ykl37r_pcd.iff")

object_intangible_ship_shared_yt1300_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/yt1300_r0.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_yt1300_pcd.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:yt1300_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:yt1300_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2265582340
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_yt1300_pcd, "object/intangible/ship/shared_yt1300_pcd.iff")

object_intangible_ship_shared_ywing_longprobe_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ywing_body.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_ywing_pcd.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:ywing_longprobe_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:ywing_longprobe_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3884767324
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_ywing_longprobe_pcd, "object/intangible/ship/shared_ywing_longprobe_pcd.iff")

object_intangible_ship_shared_ywing_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ywing_body.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_ywing_pcd.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:ywing_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:ywing_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 758141084
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_ywing_pcd, "object/intangible/ship/shared_ywing_pcd.iff")

object_intangible_ship_shared_z95_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/z95_body.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_z95_pcd.cdf",
	clientGameObjectType = 2058,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 0,

	detailedDescription = "@space_item_n:z95_pcd",

	gameObjectType = 2058,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space_item_n:z95_pcd",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 628864673
}

ObjectTemplates:addClientTemplate(object_intangible_ship_shared_z95_pcd, "object/intangible/ship/shared_z95_pcd.iff")
