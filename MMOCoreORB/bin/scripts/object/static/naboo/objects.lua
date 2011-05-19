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


object_static_naboo_shared_waterfall_200m = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/eft_whitewater_6m.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_whitewater_6meter.cdf",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:Whitewater Mesh",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2421347186,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff", "object/static/naboo/shared_waterfall_naboo_theed_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_naboo_shared_waterfall_200m, "object/static/naboo/shared_waterfall_200m.iff")

object_static_naboo_shared_waterfall_all_thin_forked = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/eft_all_waterfall_thin_forked.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_whitewater_tall_forked.cdf",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:Whitewater Mesh",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2586864352,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff", "object/static/naboo/shared_waterfall_naboo_theed_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_naboo_shared_waterfall_all_thin_forked, "object/static/naboo/shared_waterfall_all_thin_forked.iff")

object_static_naboo_shared_waterfall_all_wide_short = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/eft_all_waterfall_wide_short.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_whitewater_wide_short.cdf",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:Whitewater Mesh",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1454317490,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff", "object/static/naboo/shared_waterfall_naboo_theed_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_naboo_shared_waterfall_all_wide_short, "object/static/naboo/shared_waterfall_all_wide_short.iff")

object_static_naboo_shared_waterfall_mist_lg = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/thed_wter_falls_anim1.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_waterfall_mist_lg.cdf",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:Whitewater Mesh",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4151923875,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff", "object/static/naboo/shared_waterfall_naboo_theed_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_naboo_shared_waterfall_mist_lg, "object/static/naboo/shared_waterfall_mist_lg.iff")

object_static_naboo_shared_waterfall_mist_small = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/thed_wter_falls_anim1.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_waterfall_mist_small.cdf",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:Whitewater Mesh",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3240630762,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff", "object/static/naboo/shared_waterfall_naboo_theed_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_naboo_shared_waterfall_mist_small, "object/static/naboo/shared_waterfall_mist_small.iff")

object_static_naboo_shared_waterfall_naboo_crest_01 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/pt_waterfall_whitewater_s02_l0.prt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_waterfall_naboo_theed.cdf",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:Naboo Waterfall",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4101701818,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff", "object/static/naboo/shared_waterfall_naboo_theed_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_naboo_shared_waterfall_naboo_crest_01, "object/static/naboo/shared_waterfall_naboo_crest_01.iff")

object_static_naboo_shared_waterfall_naboo_falls_01 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/pt_waterfall_whitewater_s02_l1.prt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_waterfall_naboo_theed.cdf",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:Naboo Waterfall",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 282497930,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff", "object/static/naboo/shared_waterfall_naboo_theed_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_naboo_shared_waterfall_naboo_falls_01, "object/static/naboo/shared_waterfall_naboo_falls_01.iff")

object_static_naboo_shared_waterfall_naboo_hangar = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/eft_nboo_thed_waterfall_hangar.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_whitewater_6meter.cdf",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:Whitewater Mesh",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 370991757,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff", "object/static/naboo/shared_waterfall_naboo_theed_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_naboo_shared_waterfall_naboo_hangar, "object/static/naboo/shared_waterfall_naboo_hangar.iff")

object_static_naboo_shared_waterfall_naboo_keren = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/eft_nboo_waterfall_moenia.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_whitewater_keren.cdf",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:Whitewater Mesh",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3951584767,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff", "object/static/naboo/shared_waterfall_naboo_theed_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_naboo_shared_waterfall_naboo_keren, "object/static/naboo/shared_waterfall_naboo_keren.iff")

object_static_naboo_shared_waterfall_naboo_theed_base = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/thed_wter_falls_anim1.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_waterfall_naboo_theed.cdf",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:Naboo Waterfall",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4195612510,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_naboo_shared_waterfall_naboo_theed_base, "object/static/naboo/shared_waterfall_naboo_theed_base.iff")

object_static_naboo_shared_waterfall_naboo_theed_style_1 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/pt_invisible_particle.prt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_waterfall_naboo_theed.cdf",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:Naboo Waterfall",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3625221420,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff", "object/static/naboo/shared_waterfall_naboo_theed_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_naboo_shared_waterfall_naboo_theed_style_1, "object/static/naboo/shared_waterfall_naboo_theed_style_1.iff")

object_static_naboo_shared_whitewater_6meter = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/eft_whitewater_6m.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_whitewater_6m.cdf",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:Whitewater Mesh",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4015665582,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff", "object/static/naboo/shared_waterfall_naboo_theed_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_naboo_shared_whitewater_6meter, "object/static/naboo/shared_whitewater_6meter.iff")
