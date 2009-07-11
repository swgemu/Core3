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
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_awing_pcd.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_awing_pcd, 3231609067)

object_intangible_ship_shared_basic_hutt_light_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s01.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_basic_hutt_light_pcd, 3117731697)

object_intangible_ship_shared_basic_tiefighter_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_basic_tiefighter_pcd, 3542586269)

object_intangible_ship_shared_basic_z95_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/z95_body.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_basic_z95_pcd, 1951744339)

object_intangible_ship_shared_blacksun_heavy_s01_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_heavy_pcd_s01.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_blacksun_heavy_s01_pcd, 1920551856)

object_intangible_ship_shared_blacksun_heavy_s02_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_heavy_pcd_s02.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_blacksun_heavy_s02_pcd, 1622780077)

object_intangible_ship_shared_blacksun_heavy_s03_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s02.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_heavy_pcd_s03.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_blacksun_heavy_s03_pcd, 2461598411)

object_intangible_ship_shared_blacksun_heavy_s04_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_heavy_body_s02.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_heavy_pcd_s04.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_blacksun_heavy_s04_pcd, 1161326231)

object_intangible_ship_shared_blacksun_light_s01_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_light_pcd_s01.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_blacksun_light_s01_pcd, 4287843959)

object_intangible_ship_shared_blacksun_light_s02_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_light_pcd_s02.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_blacksun_light_s02_pcd, 3981684074)

object_intangible_ship_shared_blacksun_light_s03_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s02.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_light_pcd_s01.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_blacksun_light_s03_pcd, 525534988)

object_intangible_ship_shared_blacksun_light_s04_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_light_body_s02.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_light_pcd_s02.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_blacksun_light_s04_pcd, 3369233232)

object_intangible_ship_shared_blacksun_medium_s01_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_medium_pcd_s01.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_blacksun_medium_s01_pcd, 3830604387)

object_intangible_ship_shared_blacksun_medium_s02_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_medium_pcd_s02.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_blacksun_medium_s02_pcd, 4136796542)

object_intangible_ship_shared_blacksun_medium_s03_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s02.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_medium_pcd_s01.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_blacksun_medium_s03_pcd, 76688152)

object_intangible_ship_shared_blacksun_medium_s04_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/black_sun_fighter_medium_body_s02.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_blacksun_medium_pcd_s02.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_blacksun_medium_s04_pcd, 3541256004)

object_intangible_ship_shared_bwing_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/bwing_cockpit_pod.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_bwing_pcd.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_bwing_pcd, 4256405331)

object_intangible_ship_shared_decimator_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/vt49_npc.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_decimator_pcd.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_decimator_pcd, 816398955)

object_intangible_ship_shared_firespray_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/kse_firespray_body.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_firespray_pcd.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_firespray_pcd, 3214165542)

object_intangible_ship_shared_hutt_heavy_s01_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_hutt_heavy_pcd_s01.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_hutt_heavy_s01_pcd, 2913916856)

object_intangible_ship_shared_hutt_heavy_s02_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_hutt_heavy_pcd_s02.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_hutt_heavy_s02_pcd, 3211670693)

object_intangible_ship_shared_hutt_light_s01_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_hutt_light_pcd_s01.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_hutt_light_s01_pcd, 541381247)

object_intangible_ship_shared_hutt_light_s02_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_hutt_light_pcd_s02.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_hutt_light_s02_pcd, 847524194)

object_intangible_ship_shared_hutt_medium_s01_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_medium_body_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_hutt_medium_pcd_s01.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_hutt_medium_s01_pcd, 437951543)

object_intangible_ship_shared_hutt_medium_s02_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_medium_body_s02.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_hutt_medium_pcd_s02.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_hutt_medium_s02_pcd, 148537130)

object_intangible_ship_shared_hutt_turret_ship_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_heavy_body_s03.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_hutt_turret_ship.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_hutt_turret_ship_pcd, 3431555714)

object_intangible_ship_shared_navicomputer_1 = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_droidinterface_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"inventory", "datapad"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_navicomputer_1, 3404705593)

object_intangible_ship_shared_navicomputer_2 = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_droidinterface_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"inventory", "datapad"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_navicomputer_2, 301467566)

object_intangible_ship_shared_navicomputer_3 = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_droidinterface_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"inventory", "datapad"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_navicomputer_3, 1492475939)

object_intangible_ship_shared_navicomputer_4 = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_droidinterface_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"inventory", "datapad"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_navicomputer_4, 2736147255)

object_intangible_ship_shared_navicomputer_5 = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_droidinterface_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"inventory", "datapad"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_navicomputer_5, 3927649466)

object_intangible_ship_shared_navicomputer_6 = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_droidinterface_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"inventory", "datapad"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_navicomputer_6, 822903853)

object_intangible_ship_shared_navicomputer_base = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ship_component_droidinterface_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"inventory", "datapad"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_navicomputer_base, 1537107009)

object_intangible_ship_shared_prototype_hutt_light_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/hutt_fighter_light_body_s01.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/client_shared_hutt_light_s01.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_prototype_hutt_light_pcd, 3320786901)

object_intangible_ship_shared_prototype_tiefighter_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_prototype_tiefighter_pcd, 2937877305)

object_intangible_ship_shared_prototype_z95_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/z95_body.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_prototype_z95_pcd, 3760715561)

object_intangible_ship_shared_sorosuub_space_yacht_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/sorosuub_space_yacht_npc.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_sorosuub_space_yacht_pcd, 264594860)

object_intangible_ship_shared_tie_in_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_tie_in_pcd, 4072676654)

object_intangible_ship_shared_tie_light_duty_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_tie_light_duty_pcd, 3211390)

object_intangible_ship_shared_tieadvanced_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_advanced.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_tieadvanced_pcd, 3041041630)

object_intangible_ship_shared_tieaggressor_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_aggressor.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_tieaggressor_pcd, 3555369555)

object_intangible_ship_shared_tiebomber_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_bomber_b.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_tiebomber_pcd, 3994408379)

object_intangible_ship_shared_tiefighter_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_fighter.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_tiefighter_pcd, 2741040950)

object_intangible_ship_shared_tieinterceptor_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_interceptor.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_tieinterceptor_pcd, 4152772827)

object_intangible_ship_shared_tieoppressor_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/tie_oppressor.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_tieoppressor_pcd, 3673716446)

object_intangible_ship_shared_xwing_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/xwing_body.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_xwing_pcd.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_xwing_pcd, 3314812569)

object_intangible_ship_shared_ykl37r_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ykl37r_npc.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_ykl37r_pcd.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_ykl37r_pcd, 1454524572)

object_intangible_ship_shared_yt1300_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/yt1300_r0.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_yt1300_pcd.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_yt1300_pcd, 2265582340)

object_intangible_ship_shared_ywing_longprobe_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ywing_body.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_ywing_pcd.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_ywing_longprobe_pcd, 3884767324)

object_intangible_ship_shared_ywing_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/ywing_body.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_ywing_pcd.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_ywing_pcd, 758141084)

object_intangible_ship_shared_z95_pcd = SharedIntangibleObjectTemplate:new {
	appearanceFilename = "appearance/z95_body.apt",
	arrangementDescriptor = "",

	clearFloraRadius = 0,
	clientDataFile = "clientData/ship/pcd/client_shared_z95_pcd.cdf",
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
	slotDescriptor = {"ship_control_device"},
	snapToTerrain = 0,
	surfaceType = 0
}

ObjectTemplates:addTemplate(object_intangible_ship_shared_z95_pcd, 628864673)
