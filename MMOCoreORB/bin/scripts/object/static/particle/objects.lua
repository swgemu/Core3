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


object_static_particle_shared_particle_bactatank_bubbles = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_bactatank_bubbles.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_bacta_tank_lg_bubbles.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1473993018,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_bactatank_bubbles, "object/static/particle/shared_particle_bactatank_bubbles.iff")

object_static_particle_shared_particle_campfire_style_1 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_campfire_style_1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_campfire_s01.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2524188092,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_campfire_style_1, "object/static/particle/shared_particle_campfire_style_1.iff")

object_static_particle_shared_particle_distant_ships = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_distant_ships.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_distant_ships.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2407390404,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_distant_ships, "object/static/particle/shared_particle_distant_ships.iff")

object_static_particle_shared_particle_distant_ships_dogfight_t_vs_x = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_distant_ships_dogfight_t_vs_x.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_sky_battle_tie_vs_xwing.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 169978190,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_distant_ships_dogfight_t_vs_x, "object/static/particle/shared_particle_distant_ships_dogfight_t_vs_x.iff")

object_static_particle_shared_particle_distant_ships_dogfight_t_vs_x_2 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_distant_ships_dogfight_t_vs_x_2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_sky_battle_tie_vs_xwing_2.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4214314868,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_distant_ships_dogfight_t_vs_x_2, "object/static/particle/shared_particle_distant_ships_dogfight_t_vs_x_2.iff")

object_static_particle_shared_particle_distant_ships_dogfight_t_vs_x_3 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_distant_ships_dogfight_t_vs_x_3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_sky_battle_tie_vs_xwing_3.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2990289145,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_distant_ships_dogfight_t_vs_x_3, "object/static/particle/shared_particle_distant_ships_dogfight_t_vs_x_3.iff")

object_static_particle_shared_particle_distant_ships_dogfight_tb_vs_bw = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_distant_ships_dogfight_tb_vs_bw.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_sky_battle_tie_bomber_vs_bwing.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4182775907,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_distant_ships_dogfight_tb_vs_bw, "object/static/particle/shared_particle_distant_ships_dogfight_tb_vs_bw.iff")

object_static_particle_shared_particle_distant_ships_dogfight_tb_vs_bw_2 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_distant_ships_dogfight_tb_vs_bw_2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_sky_battle_tie_bomber_vs_bwing_2.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 800723222,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_distant_ships_dogfight_tb_vs_bw_2, "object/static/particle/shared_particle_distant_ships_dogfight_tb_vs_bw_2.iff")

object_static_particle_shared_particle_distant_ships_dogfight_tb_vs_bw_3 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_distant_ships_dogfight_tb_vs_bw_3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_sky_battle_tie_bomber_vs_bwing_3.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1723299483,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_distant_ships_dogfight_tb_vs_bw_3, "object/static/particle/shared_particle_distant_ships_dogfight_tb_vs_bw_3.iff")

object_static_particle_shared_particle_distant_ships_dogfight_ti_vs_aw = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_distant_ships_dogfight_ti_vs_aw.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_sky_battle_tie_interceptor_vs_awing.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 155186459,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_distant_ships_dogfight_ti_vs_aw, "object/static/particle/shared_particle_distant_ships_dogfight_ti_vs_aw.iff")

object_static_particle_shared_particle_distant_ships_dogfight_ti_vs_aw_2 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_distant_ships_dogfight_ti_vs_aw_2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_sky_battle_tie_interceptor_vs_awing_2.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2769318877,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_distant_ships_dogfight_ti_vs_aw_2, "object/static/particle/shared_particle_distant_ships_dogfight_ti_vs_aw_2.iff")

object_static_particle_shared_particle_distant_ships_dogfight_ti_vs_aw_3 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_distant_ships_dogfight_ti_vs_aw_3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_sky_battle_tie_interceptor_vs_awing_3.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3961328720,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_distant_ships_dogfight_ti_vs_aw_3, "object/static/particle/shared_particle_distant_ships_dogfight_ti_vs_aw_3.iff")

object_static_particle_shared_particle_distant_ships_imperial = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_distant_ships_imperial.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_distant_ships_imperial.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3417625546,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_distant_ships_imperial, "object/static/particle/shared_particle_distant_ships_imperial.iff")

object_static_particle_shared_particle_distant_ships_rebel = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_distant_ships_rebel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_distant_ships_rebel.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3663577642,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_distant_ships_rebel, "object/static/particle/shared_particle_distant_ships_rebel.iff")

object_static_particle_shared_particle_geyser_01_l0 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_geyser_01_l0.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_geyser_01_l0.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1932156871,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_geyser_01_l0, "object/static/particle/shared_particle_geyser_01_l0.iff")

object_static_particle_shared_particle_geyser_01_l1 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_geyser_01_l1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_geyser_01_l1.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 975648842,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_geyser_01_l1, "object/static/particle/shared_particle_geyser_01_l1.iff")

object_static_particle_shared_particle_geyser_01_l2 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_geyser_01_l2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_geyser_01_l2.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3778056413,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_geyser_01_l2, "object/static/particle/shared_particle_geyser_01_l2.iff")

object_static_particle_shared_particle_geyser_01_l3 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_geyser_01_l3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_geyser_01_l3.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2822633296,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_geyser_01_l3, "object/static/particle/shared_particle_geyser_01_l3.iff")

object_static_particle_shared_particle_geyser_center = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_geyser_center.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_geyser_center.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1698821405,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_geyser_center, "object/static/particle/shared_particle_geyser_center.iff")

object_static_particle_shared_particle_lg_explosion = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_lg_explosion.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_lg_explosion.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3840511804,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_lg_explosion, "object/static/particle/shared_particle_lg_explosion.iff")

object_static_particle_shared_particle_magic_sparks = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_magic_sparks.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_magic_sparks.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 736770694,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_magic_sparks, "object/static/particle/shared_particle_magic_sparks.iff")

object_static_particle_shared_particle_md_explosion = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_md_explosion.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_md_explosion.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2827947559,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_md_explosion, "object/static/particle/shared_particle_md_explosion.iff")

object_static_particle_shared_particle_mine_explosion = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_mine_explosion.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_mine_explosion.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 84116728,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_mine_explosion, "object/static/particle/shared_particle_mine_explosion.iff")

object_static_particle_shared_particle_mine_warning = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_mine_warning.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_mine_warning.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1732966696,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_mine_warning, "object/static/particle/shared_particle_mine_warning.iff")

object_static_particle_shared_particle_newbie_airport_sign = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_newbie_airport_sign.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_newbie_airport_sign.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2597597224,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_newbie_airport_sign, "object/static/particle/shared_particle_newbie_airport_sign.iff")

object_static_particle_shared_particle_newbie_arrow = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_newbie_arrow.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_newbie_arrow.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2059002681,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_newbie_arrow, "object/static/particle/shared_particle_newbie_arrow.iff")

object_static_particle_shared_particle_newbie_bomb_debris = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_newbie_bomb_debris.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_newbie_bombed_spot.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 247210913,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_newbie_bomb_debris, "object/static/particle/shared_particle_newbie_bomb_debris.iff")

object_static_particle_shared_particle_newbie_bombed_spot = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_newbie_bombed_spot.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_newbie_bombed_spot.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1187500001,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_newbie_bombed_spot, "object/static/particle/shared_particle_newbie_bombed_spot.iff")

object_static_particle_shared_particle_newbie_hanging_smoke = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_newbie_hanging_smoke.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_newbie_hanging_smoke.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1643854677,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_newbie_hanging_smoke, "object/static/particle/shared_particle_newbie_hanging_smoke.iff")

object_static_particle_shared_particle_newbie_refrigerator_steam = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_newbie_refrigerator_steam.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_newbie_refrigerator_steam.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1272311156,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_newbie_refrigerator_steam, "object/static/particle/shared_particle_newbie_refrigerator_steam.iff")

object_static_particle_shared_particle_newbie_siren = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_newbie_siren.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_newbie_siren.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1940697475,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_newbie_siren, "object/static/particle/shared_particle_newbie_siren.iff")

object_static_particle_shared_particle_newbie_spotlight = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_newbie_spotlight.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_newbie_spotlight.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4173485801,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_newbie_spotlight, "object/static/particle/shared_particle_newbie_spotlight.iff")

object_static_particle_shared_particle_newbie_steam = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_newbie_steam.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_newbie_steam.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2193561176,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_newbie_steam, "object/static/particle/shared_particle_newbie_steam.iff")

object_static_particle_shared_particle_newbie_wall_mech_lights_blue = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_newbie_wall_mech_lights_blue.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_newbie_wall_mech_lights_blue.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2655971520,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_newbie_wall_mech_lights_blue, "object/static/particle/shared_particle_newbie_wall_mech_lights_blue.iff")

object_static_particle_shared_particle_newbie_wall_mech_lights_red = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_newbie_wall_mech_lights_red.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_newbie_wall_mech_lights_red.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 726419148,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_newbie_wall_mech_lights_red, "object/static/particle/shared_particle_newbie_wall_mech_lights_red.iff")

object_static_particle_shared_particle_newbie_wall_mech_lights_yellow = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_newbie_wall_mech_lights_yellow.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_newbie_wall_mech_lights_yellow.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2545325419,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_newbie_wall_mech_lights_yellow, "object/static/particle/shared_particle_newbie_wall_mech_lights_yellow.iff")

object_static_particle_shared_particle_seagulls_flock = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_seagulls_flock.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_birds_flock.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2141382138,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_seagulls_flock, "object/static/particle/shared_particle_seagulls_flock.iff")

object_static_particle_shared_particle_sm_explosion = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_sm_explosion.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_sm_explosion.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3981248322,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_sm_explosion, "object/static/particle/shared_particle_sm_explosion.iff")

object_static_particle_shared_particle_smoke = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_smoke.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_smoke.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3175786729,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_smoke, "object/static/particle/shared_particle_smoke.iff")

object_static_particle_shared_particle_test_1 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/unshaded_geyser_test.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1641393609,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_1, "object/static/particle/shared_particle_test_1.iff")

object_static_particle_shared_particle_test_10 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_10.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_10.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3432501582,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_10, "object/static/particle/shared_particle_test_10.iff")

object_static_particle_shared_particle_test_100 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_100.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_100.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1309247123,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_100, "object/static/particle/shared_particle_test_100.iff")

object_static_particle_shared_particle_test_11 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_11.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_11.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2241509059,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_11, "object/static/particle/shared_particle_test_11.iff")

object_static_particle_shared_particle_test_12 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_12.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_12.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1586306644,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_12, "object/static/particle/shared_particle_test_12.iff")

object_static_particle_shared_particle_test_13 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_13.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_13.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 394295769,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_13, "object/static/particle/shared_particle_test_13.iff")

object_static_particle_shared_particle_test_14 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_14.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_14.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3965932237,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_14, "object/static/particle/shared_particle_test_14.iff")

object_static_particle_shared_particle_test_15 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_15.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_15.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2775463232,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_15, "object/static/particle/shared_particle_test_15.iff")

object_static_particle_shared_particle_test_16 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_16.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_16.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2121899479,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_16, "object/static/particle/shared_particle_test_16.iff")

object_static_particle_shared_particle_test_17 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_17.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_17.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 930413146,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_17, "object/static/particle/shared_particle_test_17.iff")

object_static_particle_shared_particle_test_18 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_18.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_18.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2373899848,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_18, "object/static/particle/shared_particle_test_18.iff")

object_static_particle_shared_particle_test_19 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_19.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_19.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3295916485,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_19, "object/static/particle/shared_particle_test_19.iff")

object_static_particle_shared_particle_test_2 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_2.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "sample/amb_waterfall_large_lp.sam",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3133277534,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_2, "object/static/particle/shared_particle_test_2.iff")

object_static_particle_shared_particle_test_20 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_20.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_20.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3790587590,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_20, "object/static/particle/shared_particle_test_20.iff")

object_static_particle_shared_particle_test_21 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_21.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_21.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2833424715,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_21, "object/static/particle/shared_particle_test_21.iff")

object_static_particle_shared_particle_test_22 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_22.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_22.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1945438684,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_22, "object/static/particle/shared_particle_test_22.iff")

object_static_particle_shared_particle_test_23 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_23.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_23.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 989359697,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_23, "object/static/particle/shared_particle_test_23.iff")

object_static_particle_shared_particle_test_24 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_24.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_24.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3239789893,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_24, "object/static/particle/shared_particle_test_24.iff")

object_static_particle_shared_particle_test_25 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_25.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_25.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2283152072,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_25, "object/static/particle/shared_particle_test_25.iff")

object_static_particle_shared_particle_test_26 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_26.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_26.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1392609887,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_26, "object/static/particle/shared_particle_test_26.iff")

object_static_particle_shared_particle_test_27 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_27.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_27.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 437054930,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_27, "object/static/particle/shared_particle_test_27.iff")

object_static_particle_shared_particle_test_28 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_28.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_28.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2684797376,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_28, "object/static/particle/shared_particle_test_28.iff")

object_static_particle_shared_particle_test_29 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_29.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_29.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3909854797,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_29, "object/static/particle/shared_particle_test_29.iff")

object_static_particle_shared_particle_test_3 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_invisible_particle.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4090454739,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_3, "object/static/particle/shared_particle_test_3.iff")

object_static_particle_shared_particle_test_30 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_30.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_30.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4207397822,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_30, "object/static/particle/shared_particle_test_30.iff")

object_static_particle_shared_particle_test_31 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_31.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_31.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3016404019,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_31, "object/static/particle/shared_particle_test_31.iff")

object_static_particle_shared_particle_test_32 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_32.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_32.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1759315108,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_32, "object/static/particle/shared_particle_test_32.iff")

object_static_particle_shared_particle_test_33 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_33.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_33.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 567305001,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_33, "object/static/particle/shared_particle_test_33.iff")

object_static_particle_shared_particle_test_34 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_34.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_34.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3660793917,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_34, "object/static/particle/shared_particle_test_34.iff")

object_static_particle_shared_particle_test_35 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_35.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_35.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2470326192,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_35, "object/static/particle/shared_particle_test_35.iff")

object_static_particle_shared_particle_test_36 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_36.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_36.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1210681127,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_36, "object/static/particle/shared_particle_test_36.iff")

object_static_particle_shared_particle_test_37 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_37.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_37.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 19194026,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_37, "object/static/particle/shared_particle_test_37.iff")

object_static_particle_shared_particle_test_38 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_38.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_38.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3140406456,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_38, "object/static/particle/shared_particle_test_38.iff")

object_static_particle_shared_particle_test_39 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_39.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_39.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4062423861,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_39, "object/static/particle/shared_particle_test_39.iff")

object_static_particle_shared_particle_test_4 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_invisible_particle.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 137120199,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_4, "object/static/particle/shared_particle_test_4.iff")

object_static_particle_shared_particle_test_40 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_40.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_40.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3139430870,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_40, "object/static/particle/shared_particle_test_40.iff")

object_static_particle_shared_particle_test_41 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_41.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_41.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4061302363,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_41, "object/static/particle/shared_particle_test_41.iff")

object_static_particle_shared_particle_test_42 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_42.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_42.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 688203468,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_42, "object/static/particle/shared_particle_test_42.iff")

object_static_particle_shared_particle_test_43 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_43.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_43.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1611153729,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_43, "object/static/particle/shared_particle_test_43.iff")

object_static_particle_shared_particle_test_44 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_44.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_44.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2615896661,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_44, "object/static/particle/shared_particle_test_44.iff")

object_static_particle_shared_particle_test_45 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_45.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_45.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3538292184,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_45, "object/static/particle/shared_particle_test_45.iff")

object_static_particle_shared_particle_test_46 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_46.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_46.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 166831439,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_46, "object/static/particle/shared_particle_test_46.iff")

object_static_particle_shared_particle_test_47 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_47.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_47.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1090306754,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_47, "object/static/particle/shared_particle_test_47.iff")

object_static_particle_shared_particle_test_48 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_48.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_48.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4210486992,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_48, "object/static/particle/shared_particle_test_48.iff")

object_static_particle_shared_particle_test_49 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_49.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_49.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3019606365,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_49, "object/static/particle/shared_particle_test_49.iff")

object_static_particle_shared_particle_test_5 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_invisible_particle.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1092693578,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_5, "object/static/particle/shared_particle_test_5.iff")

object_static_particle_shared_particle_test_50 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_50.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_50.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2688017582,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_50, "object/static/particle/shared_particle_test_50.iff")

object_static_particle_shared_particle_test_51 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_51.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_51.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3912925987,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_51, "object/static/particle/shared_particle_test_51.iff")

object_static_particle_shared_particle_test_52 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_52.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_52.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 841821108,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_52, "object/static/particle/shared_particle_test_52.iff")

object_static_particle_shared_particle_test_53 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_53.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_53.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2065714233,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_53, "object/static/particle/shared_particle_test_53.iff")

object_static_particle_shared_particle_test_54 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_54.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_54.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2160289581,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_54, "object/static/particle/shared_particle_test_54.iff")

object_static_particle_shared_particle_test_55 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_55.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_55.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3385720992,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_55, "object/static/particle/shared_particle_test_55.iff")

object_static_particle_shared_particle_test_56 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_56.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_56.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 316254263,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_56, "object/static/particle/shared_particle_test_56.iff")

object_static_particle_shared_particle_test_57 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_57.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_57.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1540673466,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_57, "object/static/particle/shared_particle_test_57.iff")

object_static_particle_shared_particle_test_58 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_58.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_58.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3789480872,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_58, "object/static/particle/shared_particle_test_58.iff")

object_static_particle_shared_particle_test_59 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_59.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_59.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2832434213,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_59, "object/static/particle/shared_particle_test_59.iff")

object_static_particle_shared_particle_test_6 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_6.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_6.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2587264733,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_6, "object/static/particle/shared_particle_test_6.iff")

object_static_particle_shared_particle_test_60 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_60.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_60.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2370827046,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_60, "object/static/particle/shared_particle_test_60.iff")

object_static_particle_shared_particle_test_61 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_61.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_61.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3292697771,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_61, "object/static/particle/shared_particle_test_61.iff")

object_static_particle_shared_particle_test_62 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_62.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_62.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 525679676,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_62, "object/static/particle/shared_particle_test_62.iff")

object_static_particle_shared_particle_test_63 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_63.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_63.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1448631217,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_63, "object/static/particle/shared_particle_test_63.iff")

object_static_particle_shared_particle_test_64 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_64.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_64.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2914742437,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_64, "object/static/particle/shared_particle_test_64.iff")

object_static_particle_shared_particle_test_65 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_65.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_65.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3837138728,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_65, "object/static/particle/shared_particle_test_65.iff")

object_static_particle_shared_particle_test_66 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_66.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_66.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1067564991,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_66, "object/static/particle/shared_particle_test_66.iff")

object_static_particle_shared_particle_test_67 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_67.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_67.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1991039026,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_67, "object/static/particle/shared_particle_test_67.iff")

object_static_particle_shared_particle_test_68 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_68.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_68.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3433493536,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_68, "object/static/particle/shared_particle_test_68.iff")

object_static_particle_shared_particle_test_69 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_69.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_69.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2242614189,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_69, "object/static/particle/shared_particle_test_69.iff")

object_static_particle_shared_particle_test_7 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_7.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_7.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3543916880,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_7, "object/static/particle/shared_particle_test_7.iff")

object_static_particle_shared_particle_test_70 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_70.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_70.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2523397726,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_70, "object/static/particle/shared_particle_test_70.iff")

object_static_particle_shared_particle_test_71 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_71.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_71.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3748305363,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_71, "object/static/particle/shared_particle_test_71.iff")

object_static_particle_shared_particle_test_72 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_72.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_72.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 75313476,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_72, "object/static/particle/shared_particle_test_72.iff")

object_static_particle_shared_particle_test_73 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_73.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_73.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1299207881,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_73, "object/static/particle/shared_particle_test_73.iff")

object_static_particle_shared_particle_test_74 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_74.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_74.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3063119325,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_74, "object/static/particle/shared_particle_test_74.iff")

object_static_particle_shared_particle_test_75 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_75.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_75.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4288551504,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_75, "object/static/particle/shared_particle_test_75.iff")

object_static_particle_shared_particle_test_76 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_76.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_76.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 613003975,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_76, "object/static/particle/shared_particle_test_76.iff")

object_static_particle_shared_particle_test_77 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_77.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_77.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1837421898,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_77, "object/static/particle/shared_particle_test_77.iff")

object_static_particle_shared_particle_test_78 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_78.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_78.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3616471384,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_78, "object/static/particle/shared_particle_test_78.iff")

object_static_particle_shared_particle_test_79 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_79.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_79.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2659426005,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_79, "object/static/particle/shared_particle_test_79.iff")

object_static_particle_shared_particle_test_8 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_8.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_8.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1764871490,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_8, "object/static/particle/shared_particle_test_8.iff")

object_static_particle_shared_particle_test_80 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_80.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_80.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 251639798,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_80, "object/static/particle/shared_particle_test_80.iff")

object_static_particle_shared_particle_test_81 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_81.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_81.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1207095419,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_81, "object/static/particle/shared_particle_test_81.iff")

object_static_particle_shared_particle_test_82 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_82.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_82.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2632284396,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_82, "object/static/particle/shared_particle_test_82.iff")

object_static_particle_shared_particle_test_83 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_83.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_83.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3588759393,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_83, "object/static/particle/shared_particle_test_83.iff")

object_static_particle_shared_particle_test_84 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_84.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_84.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 772486261,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_84, "object/static/particle/shared_particle_test_84.iff")

object_static_particle_shared_particle_test_85 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_85.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_85.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1728467960,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_85, "object/static/particle/shared_particle_test_85.iff")

object_static_particle_shared_particle_test_86 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_86.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_86.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3155295087,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_86, "object/static/particle/shared_particle_test_86.iff")

object_static_particle_shared_particle_test_87 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_87.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_87.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4112293090,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_87, "object/static/particle/shared_particle_test_87.iff")

object_static_particle_shared_particle_test_88 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_88.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_88.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1326887152,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_88, "object/static/particle/shared_particle_test_88.iff")

object_static_particle_shared_particle_test_89 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_89.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_89.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 102487933,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_89, "object/static/particle/shared_particle_test_89.iff")

object_static_particle_shared_particle_test_9 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_9.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_9.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 540846799,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_9, "object/static/particle/shared_particle_test_9.iff")

object_static_particle_shared_particle_test_90 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_90.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_90.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 366459534,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_90, "object/static/particle/shared_particle_test_90.iff")

object_static_particle_shared_particle_test_91 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_91.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_91.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1557847299,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_91, "object/static/particle/shared_particle_test_91.iff")

object_static_particle_shared_particle_test_92 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_92.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_92.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2278389140,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_92, "object/static/particle/shared_particle_test_92.iff")

object_static_particle_shared_particle_test_93 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_93.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_93.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3468694041,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_93, "object/static/particle/shared_particle_test_93.iff")

object_static_particle_shared_particle_test_94 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_94.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_94.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 891500813,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_94, "object/static/particle/shared_particle_test_94.iff")

object_static_particle_shared_particle_test_95 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_95.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_95.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2083413632,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_95, "object/static/particle/shared_particle_test_95.iff")

object_static_particle_shared_particle_test_96 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_96.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_96.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2805593623,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_96, "object/static/particle/shared_particle_test_96.iff")

object_static_particle_shared_particle_test_97 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_97.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_97.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3996422554,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_97, "object/static/particle/shared_particle_test_97.iff")

object_static_particle_shared_particle_test_98 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_98.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_98.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1413397896,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_98, "object/static/particle/shared_particle_test_98.iff")

object_static_particle_shared_particle_test_99 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_test_99.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/particle_test_99.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 489937413,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_test_99, "object/static/particle/shared_particle_test_99.iff")

object_static_particle_shared_particle_volcano_glow_1 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_volcano_glow_1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_lok_lava_bubblingareaprt.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "clientdata/client_shared_volcano_glow_on.cdf",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:Gravestone",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 1,

	totalCellNumber = 0,

	clientObjectCRC = 1841523220,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/structure/base/shared_static_structure_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_volcano_glow_1, "object/static/particle/shared_particle_volcano_glow_1.iff")

object_static_particle_shared_particle_waterfall_whitewater_s02_l0 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_waterfall_whitewater_s02_l0.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_waterfall_whitewater_s02_l0.prt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2270635651,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_waterfall_whitewater_s02_l0, "object/static/particle/shared_particle_waterfall_whitewater_s02_l0.iff")

object_static_particle_shared_particle_waterfall_whitewater_s02_l1 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_particle_waterfall_whitewater_s02_l1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_waterfall_whitewater_s02_l1.prt",
	arrangementDescriptorFilename = "",

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

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3462021390,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_particle_waterfall_whitewater_s02_l1, "object/static/particle/shared_particle_waterfall_whitewater_s02_l1.iff")

object_static_particle_shared_pt_airport_race_light = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_airport_race_light.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_airport_race_light.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2832359220,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_airport_race_light, "object/static/particle/shared_pt_airport_race_light.iff")

object_static_particle_shared_pt_airport_race_light_group = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_airport_race_light_group.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_airport_race_light_group.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1749781363,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_airport_race_light_group, "object/static/particle/shared_pt_airport_race_light_group.iff")

object_static_particle_shared_pt_birds_flock = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_birds_flock.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_birds_flock.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 574961375,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_birds_flock, "object/static/particle/shared_pt_birds_flock.iff")

object_static_particle_shared_pt_birds_flock_02 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_birds_flock_02.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_birds_flock_02.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 468934100,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_birds_flock_02, "object/static/particle/shared_pt_birds_flock_02.iff")

object_static_particle_shared_pt_bunker_allum_mine_car_01 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_bunker_allum_mine_car_01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_bunker_allum_mine_car_01.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3451183105,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_bunker_allum_mine_car_01, "object/static/particle/shared_pt_bunker_allum_mine_car_01.iff")

object_static_particle_shared_pt_bunker_allum_mine_hallway_vent_steam = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_bunker_allum_mine_hallway_vent_steam.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_bunker_allum_mine_hallway_vent_steam.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3389820098,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_bunker_allum_mine_hallway_vent_steam, "object/static/particle/shared_pt_bunker_allum_mine_hallway_vent_steam.iff")

object_static_particle_shared_pt_bunker_allum_mine_large_steam_gravity = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_bunker_allum_mine_large_steam_gravity.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_bunker_allum_mine_large_steam_gravity.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3610533575,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_bunker_allum_mine_large_steam_gravity, "object/static/particle/shared_pt_bunker_allum_mine_large_steam_gravity.iff")

object_static_particle_shared_pt_bunker_allum_mine_lift_01 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_bunker_allum_mine_lift_01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_bunker_allum_mine_lift_01.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1733362585,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_bunker_allum_mine_lift_01, "object/static/particle/shared_pt_bunker_allum_mine_lift_01.iff")

object_static_particle_shared_pt_burning_smokeandembers_large = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_burning_smokeandembers_large.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_burning_smokeandembers_large.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4112463342,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_burning_smokeandembers_large, "object/static/particle/shared_pt_burning_smokeandembers_large.iff")

object_static_particle_shared_pt_burning_smokeandembers_md = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_burning_smokeandembers_md.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_burning_smokeandembers_md.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3309131413,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_burning_smokeandembers_md, "object/static/particle/shared_pt_burning_smokeandembers_md.iff")

object_static_particle_shared_pt_buzzing_insects_large = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_buzzing_insects_large.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_buzzing_insects_large.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1507296935,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_buzzing_insects_large, "object/static/particle/shared_pt_buzzing_insects_large.iff")

object_static_particle_shared_pt_buzzing_insects_small = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_buzzing_insects_small.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_buzzing_insects_small.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1842090638,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_buzzing_insects_small, "object/static/particle/shared_pt_buzzing_insects_small.iff")

object_static_particle_shared_pt_campfire_s01 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_campfire_s01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_campfire_s01.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 655646750,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_campfire_s01, "object/static/particle/shared_pt_campfire_s01.iff")

object_static_particle_shared_pt_detector = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_detector.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_detector.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4138320669,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_detector, "object/static/particle/shared_pt_detector.iff")

object_static_particle_shared_pt_falling_dirt = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_falling_dirt.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_falling_dirt.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3567175317,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_falling_dirt, "object/static/particle/shared_pt_falling_dirt.iff")

object_static_particle_shared_pt_falling_dirt_all = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_falling_dirt_all.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_falling_dirt_all.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3490534350,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_falling_dirt_all, "object/static/particle/shared_pt_falling_dirt_all.iff")

object_static_particle_shared_pt_falling_dirt_all_loop = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_falling_dirt_all_loop.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_falling_dirt_all_loop.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4246067951,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_falling_dirt_all_loop, "object/static/particle/shared_pt_falling_dirt_all_loop.iff")

object_static_particle_shared_pt_falling_dirt_loop = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_falling_dirt_loop.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_falling_dirt_loop.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2998306057,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_falling_dirt_loop, "object/static/particle/shared_pt_falling_dirt_loop.iff")

object_static_particle_shared_pt_falling_dust = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_falling_dust.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_falling_dust.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1667365428,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_falling_dust, "object/static/particle/shared_pt_falling_dust.iff")

object_static_particle_shared_pt_falling_dust_loop = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_falling_dust_loop.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_falling_dust_loop.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 337159855,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_falling_dust_loop, "object/static/particle/shared_pt_falling_dust_loop.iff")

object_static_particle_shared_pt_falling_rock = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_falling_rock.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_falling_rock.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2545958613,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_falling_rock, "object/static/particle/shared_pt_falling_rock.iff")

object_static_particle_shared_pt_falling_rock_loop = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_falling_rock_loop.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_falling_rock_loop.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2198363460,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_falling_rock_loop, "object/static/particle/shared_pt_falling_rock_loop.iff")

object_static_particle_shared_pt_flocking_bees = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_flocking_bees.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_flocking_bees.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1060739444,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_flocking_bees, "object/static/particle/shared_pt_flocking_bees.iff")

object_static_particle_shared_pt_flocking_bluefish = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_flocking_bluefish.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_flocking_bluefish.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 333751823,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_flocking_bluefish, "object/static/particle/shared_pt_flocking_bluefish.iff")

object_static_particle_shared_pt_flocking_butterflies = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_flocking_butterflies.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_flocking_butterflies.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 360344089,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_flocking_butterflies, "object/static/particle/shared_pt_flocking_butterflies.iff")

object_static_particle_shared_pt_flocking_butterflies_s1 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_flocking_butterflies_s1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_flocking_butterflies_s1.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 409161218,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_flocking_butterflies_s1, "object/static/particle/shared_pt_flocking_butterflies_s1.iff")

object_static_particle_shared_pt_flocking_centipede = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_flocking_centipede.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_flocking_centipede.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2000292545,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_flocking_centipede, "object/static/particle/shared_pt_flocking_centipede.iff")

object_static_particle_shared_pt_flocking_cricket = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_flocking_cricket.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_flocking_cricket.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3738808713,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_flocking_cricket, "object/static/particle/shared_pt_flocking_cricket.iff")

object_static_particle_shared_pt_flocking_frog = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_flocking_frog.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_flocking_frog.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 392100184,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_flocking_frog, "object/static/particle/shared_pt_flocking_frog.iff")

object_static_particle_shared_pt_flocking_frog_s1 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_flocking_frog_s1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_flocking_frog_s1.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 386604484,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_flocking_frog_s1, "object/static/particle/shared_pt_flocking_frog_s1.iff")

object_static_particle_shared_pt_flocking_glowzees = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_flocking_glowzees.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_flocking_glowzees.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1644547623,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_flocking_glowzees, "object/static/particle/shared_pt_flocking_glowzees.iff")

object_static_particle_shared_pt_frn_all_glowing_light_s3 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_frn_all_glowing_light_s3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_frn_all_glowing_light_s3.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3478976599,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_frn_all_glowing_light_s3, "object/static/particle/shared_pt_frn_all_glowing_light_s3.iff")

object_static_particle_shared_pt_geonosian_aquarium_fish = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_geonosian_aquarium_fish.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_flocking_fish_2x4cage.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 951222437,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_geonosian_aquarium_fish, "object/static/particle/shared_pt_geonosian_aquarium_fish.iff")

object_static_particle_shared_pt_green_gunk_spurt = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_green_gunk_spurt.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_green_gunk_spurt.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1329694676,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_green_gunk_spurt, "object/static/particle/shared_pt_green_gunk_spurt.iff")

object_static_particle_shared_pt_green_hanging_smoke = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_green_hanging_smoke.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_green_hanging_smoke.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4118588253,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_green_hanging_smoke, "object/static/particle/shared_pt_green_hanging_smoke.iff")

object_static_particle_shared_pt_green_refrigerator_steam = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_green_refrigerator_steam.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_green_refrigerator_steam.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 613903763,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_green_refrigerator_steam, "object/static/particle/shared_pt_green_refrigerator_steam.iff")

object_static_particle_shared_pt_green_steam = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_green_steam.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_green_steam.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1797841273,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_green_steam, "object/static/particle/shared_pt_green_steam.iff")

object_static_particle_shared_pt_lair_evil_fire_large_green = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_lair_evil_fire_large_green.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_lair_evil_fire_large_green.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2919624693,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_lair_evil_fire_large_green, "object/static/particle/shared_pt_lair_evil_fire_large_green.iff")

object_static_particle_shared_pt_lair_evil_fire_large_red = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_lair_evil_fire_large_red.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_lair_evil_fire_large_red.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1476527814,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_lair_evil_fire_large_red, "object/static/particle/shared_pt_lair_evil_fire_large_red.iff")

object_static_particle_shared_pt_lair_evil_fire_small = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_lair_evil_fire_small.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_lair_evil_fire_small.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 153148481,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_lair_evil_fire_small, "object/static/particle/shared_pt_lair_evil_fire_small.iff")

object_static_particle_shared_pt_lair_med_burn = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_lair_med_burn.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_lair_med_burn.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 669295657,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_lair_med_burn, "object/static/particle/shared_pt_lair_med_burn.iff")

object_static_particle_shared_pt_lair_med_damage = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_lair_med_damage.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_lair_med_damage.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1342131178,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_lair_med_damage, "object/static/particle/shared_pt_lair_med_damage.iff")

object_static_particle_shared_pt_light_blink_blue = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_light_blink_blue.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_light_blink_blue.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1787409199,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_light_blink_blue, "object/static/particle/shared_pt_light_blink_blue.iff")

object_static_particle_shared_pt_light_blink_green = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_light_blink_green.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_light_blink_green.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3099575799,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_light_blink_green, "object/static/particle/shared_pt_light_blink_green.iff")

object_static_particle_shared_pt_light_blink_orange = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_light_blink_orange.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_light_blink_orange.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1680016354,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_light_blink_orange, "object/static/particle/shared_pt_light_blink_orange.iff")

object_static_particle_shared_pt_light_constant_blue = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_light_constant_blue.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_light_constant_blue.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3049235018,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_light_constant_blue, "object/static/particle/shared_pt_light_constant_blue.iff")

object_static_particle_shared_pt_light_streetlamp_blue = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_light_streetlamp_blue.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_light_streetlamp_blue.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 927898294,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_light_streetlamp_blue, "object/static/particle/shared_pt_light_streetlamp_blue.iff")

object_static_particle_shared_pt_light_streetlamp_gold = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_light_streetlamp_gold.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_light_streetlamp_gold.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3933494226,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_light_streetlamp_gold, "object/static/particle/shared_pt_light_streetlamp_gold.iff")

object_static_particle_shared_pt_light_streetlamp_green = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_light_streetlamp_green.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_light_streetlamp_green.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 919367971,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_light_streetlamp_green, "object/static/particle/shared_pt_light_streetlamp_green.iff")

object_static_particle_shared_pt_light_streetlamp_red = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_light_streetlamp_red.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_light_streetlamp_red.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3254920808,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_light_streetlamp_red, "object/static/particle/shared_pt_light_streetlamp_red.iff")

object_static_particle_shared_pt_lok_lava_bubblingareaprt = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_lok_lava_bubblingareaprt.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_lok_lava_bubblingareaprt.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3373071606,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_lok_lava_bubblingareaprt, "object/static/particle/shared_pt_lok_lava_bubblingareaprt.iff")

object_static_particle_shared_pt_lok_lava_drop = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_lok_lava_drop.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_lok_lava_drop.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 198238654,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_lok_lava_drop, "object/static/particle/shared_pt_lok_lava_drop.iff")

object_static_particle_shared_pt_lok_lava_spirt = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_lok_lava_spirt.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_lok_lava_spirt.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2234486758,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_lok_lava_spirt, "object/static/particle/shared_pt_lok_lava_spirt.iff")

object_static_particle_shared_pt_lok_volcano = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_lok_volcano.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_lok_volcano.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 893154540,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_lok_volcano, "object/static/particle/shared_pt_lok_volcano.iff")

object_static_particle_shared_pt_lok_volcano_smoke = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_lok_volcano_smoke.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_lok_volcano_smoke.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 693978317,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_lok_volcano_smoke, "object/static/particle/shared_pt_lok_volcano_smoke.iff")

object_static_particle_shared_pt_lok_volcano_smoke_sm = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_lok_volcano_smoke_sm.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_lok_volcano_smoke_sm.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3030325207,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_lok_volcano_smoke_sm, "object/static/particle/shared_pt_lok_volcano_smoke_sm.iff")

object_static_particle_shared_pt_magic_sparks = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_magic_sparks.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_magic_sparks.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4190362861,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_magic_sparks, "object/static/particle/shared_pt_magic_sparks.iff")

object_static_particle_shared_pt_miasma_of_fog_gray = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_miasma_of_fog_gray.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_miasma_of_fog_gray.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4103176691,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_miasma_of_fog_gray, "object/static/particle/shared_pt_miasma_of_fog_gray.iff")

object_static_particle_shared_pt_miasma_of_fog_greenish = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_miasma_of_fog_greenish.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_miasma_of_fog_greenish.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2098974720,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_miasma_of_fog_greenish, "object/static/particle/shared_pt_miasma_of_fog_greenish.iff")

object_static_particle_shared_pt_miasma_of_fog_mustard = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_miasma_of_fog_mustard.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_miasma_of_fog_mustard.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 495620993,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_miasma_of_fog_mustard, "object/static/particle/shared_pt_miasma_of_fog_mustard.iff")

object_static_particle_shared_pt_miasma_of_fog_orange = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_miasma_of_fog_orange.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_miasma_of_fog_orange.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2453321375,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_miasma_of_fog_orange, "object/static/particle/shared_pt_miasma_of_fog_orange.iff")

object_static_particle_shared_pt_miasma_of_fog_red = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_miasma_of_fog_red.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_miasma_of_fog_red.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2493012147,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_miasma_of_fog_red, "object/static/particle/shared_pt_miasma_of_fog_red.iff")

object_static_particle_shared_pt_poi_broken_electronics = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_poi_broken_electronics.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_poi_broken_electronics.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2630854860,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_poi_broken_electronics, "object/static/particle/shared_pt_poi_broken_electronics.iff")

object_static_particle_shared_pt_poi_droid_weld_sparks = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_poi_droid_weld_sparks.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_poi_droid_weld_sparks.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 718197252,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_poi_droid_weld_sparks, "object/static/particle/shared_pt_poi_droid_weld_sparks.iff")

object_static_particle_shared_pt_poi_electricity_2x2 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_poi_electricity_2x2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_poi_electricity_2x2.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 927712692,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_poi_electricity_2x2, "object/static/particle/shared_pt_poi_electricity_2x2.iff")

object_static_particle_shared_pt_sm_explosion = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_sm_explosion.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_sm_explosion.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1063575849,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_sm_explosion, "object/static/particle/shared_pt_sm_explosion.iff")

object_static_particle_shared_pt_smoke = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_smoke.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_smoke.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1921352658,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_smoke, "object/static/particle/shared_pt_smoke.iff")

object_static_particle_shared_pt_smoke_large = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_smoke_large.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_smoke_large.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3471324085,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_smoke_large, "object/static/particle/shared_pt_smoke_large.iff")

object_static_particle_shared_pt_smoke_small = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_smoke_small.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_smoke_small.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4210272156,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_smoke_small, "object/static/particle/shared_pt_smoke_small.iff")

object_static_particle_shared_pt_smoke_tr = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_smoke_tr.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_smoke_tr.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2928460713,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_smoke_tr, "object/static/particle/shared_pt_smoke_tr.iff")

object_static_particle_shared_pt_sonic_pulse = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_sonic_pulse.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_sonic_pulse.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3328660965,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_sonic_pulse, "object/static/particle/shared_pt_sonic_pulse.iff")

object_static_particle_shared_pt_sound_location = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_sound_location.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_sound_location.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1232478276,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_sound_location, "object/static/particle/shared_pt_sound_location.iff")

object_static_particle_shared_pt_sparking_blast_md = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_sparking_blast_md.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_sparking_blast_md.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2573168569,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_sparking_blast_md, "object/static/particle/shared_pt_sparking_blast_md.iff")

object_static_particle_shared_pt_sparks_large = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_sparks_large.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_sparks_large.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 952907796,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_sparks_large, "object/static/particle/shared_pt_sparks_large.iff")

object_static_particle_shared_pt_sparks_small = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_sparks_small.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_sparks_small.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 215460925,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_sparks_small, "object/static/particle/shared_pt_sparks_small.iff")

object_static_particle_shared_pt_steam = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_steam.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_steam.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 320796703,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_steam, "object/static/particle/shared_pt_steam.iff")

object_static_particle_shared_pt_steam_rise = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_steam_rise.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_steam_rise.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2327575207,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_steam_rise, "object/static/particle/shared_pt_steam_rise.iff")

object_static_particle_shared_pt_steam_rise_2x2 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_steam_rise_2x2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_steam_rise_2x2.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3748858537,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_steam_rise_2x2, "object/static/particle/shared_pt_steam_rise_2x2.iff")

object_static_particle_shared_pt_stunned_player = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_stunned_player.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_stunned_player.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3872867406,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_stunned_player, "object/static/particle/shared_pt_stunned_player.iff")

object_static_particle_shared_pt_survey = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_survey.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_survey.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4008828338,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_survey, "object/static/particle/shared_pt_survey.iff")

object_static_particle_shared_pt_survey_gas_sample = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_survey_gas_sample.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_survey_gas_sample.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2454176685,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_survey_gas_sample, "object/static/particle/shared_pt_survey_gas_sample.iff")

object_static_particle_shared_pt_survey_liquid_sample = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_survey_liquid_sample.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_survey_liquid_sample.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2673530585,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_survey_liquid_sample, "object/static/particle/shared_pt_survey_liquid_sample.iff")

object_static_particle_shared_pt_survey_lumber_sample = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_survey_lumber_sample.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_survey_lumber_sample.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3827726832,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_survey_lumber_sample, "object/static/particle/shared_pt_survey_lumber_sample.iff")

object_static_particle_shared_pt_survey_mineral_sample = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_survey_mineral_sample.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_survey_mineral_sample.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1570673166,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_survey_mineral_sample, "object/static/particle/shared_pt_survey_mineral_sample.iff")

object_static_particle_shared_pt_survey_moisture_sample = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_survey_moisture_sample.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_survey_moisture_sample.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1547554683,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_survey_moisture_sample, "object/static/particle/shared_pt_survey_moisture_sample.iff")

object_static_particle_shared_pt_survey_tool_liquid = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_survey_tool_liquid.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_survey_tool_liquid.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2160449826,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_survey_tool_liquid, "object/static/particle/shared_pt_survey_tool_liquid.iff")

object_static_particle_shared_pt_survey_tool_lumber = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_survey_tool_lumber.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_survey_tool_lumber.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1247458392,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_survey_tool_lumber, "object/static/particle/shared_pt_survey_tool_lumber.iff")

object_static_particle_shared_pt_survey_tool_mineral = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_survey_tool_mineral.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_survey_tool_mineral.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3745960007,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_survey_tool_mineral, "object/static/particle/shared_pt_survey_tool_mineral.iff")

object_static_particle_shared_pt_survey_tool_moisture = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_survey_tool_moisture.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_survey_tool_moisture.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2864462260,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_survey_tool_moisture, "object/static/particle/shared_pt_survey_tool_moisture.iff")

object_static_particle_shared_pt_trailing_falling_dust = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_trailing_falling_dust.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_trailing_falling_dust.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1930955215,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_trailing_falling_dust, "object/static/particle/shared_pt_trailing_falling_dust.iff")

object_static_particle_shared_pt_trailing_falling_dust_2 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_trailing_falling_dust_2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_trailing_falling_dust_2.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2226030876,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_trailing_falling_dust_2, "object/static/particle/shared_pt_trailing_falling_dust_2.iff")

object_static_particle_shared_pt_waterfall_crest = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_waterfall_crest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_waterfall_crest.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3586703298,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_waterfall_crest, "object/static/particle/shared_pt_waterfall_crest.iff")

object_static_particle_shared_pt_waterfall_mist = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_waterfall_mist.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_waterfall_mist.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3820269470,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_waterfall_mist, "object/static/particle/shared_pt_waterfall_mist.iff")

object_static_particle_shared_pt_waterfall_mist_med = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_waterfall_mist_med.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_waterfall_mist_med.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1019797263,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_waterfall_mist_med, "object/static/particle/shared_pt_waterfall_mist_med.iff")

object_static_particle_shared_pt_waterfall_mist_small = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_waterfall_mist_small.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_waterfall_mist_small.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 730945332,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_waterfall_mist_small, "object/static/particle/shared_pt_waterfall_mist_small.iff")

object_static_particle_shared_pt_waterfall_spray = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_waterfall_spray.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_waterfall_spray.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3705199688,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_waterfall_spray, "object/static/particle/shared_pt_waterfall_spray.iff")

object_static_particle_shared_pt_waterfall_spray_small = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_waterfall_spray_small.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_waterfall_spray_small.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 637915981,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_waterfall_spray_small, "object/static/particle/shared_pt_waterfall_spray_small.iff")

object_static_particle_shared_pt_waterfall_whitewater_s02_l0 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_waterfall_whitewater_s02_l0.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_waterfall_whitewater_s02_l0.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3219447959,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_waterfall_whitewater_s02_l0, "object/static/particle/shared_pt_waterfall_whitewater_s02_l0.iff")

object_static_particle_shared_pt_waterfall_whitewater_s02_l1 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_waterfall_whitewater_s02_l1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_waterfall_whitewater_s02_l1.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4142499610,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_waterfall_whitewater_s02_l1, "object/static/particle/shared_pt_waterfall_whitewater_s02_l1.iff")

object_static_particle_shared_pt_waterfalling_200m = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_waterfalling_200m.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_waterfalling_200m.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2168193478,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_waterfalling_200m, "object/static/particle/shared_pt_waterfalling_200m.iff")

object_static_particle_shared_pt_waterfalling_slow = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_waterfalling_slow.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_waterfalling_slow.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4066371395,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_waterfalling_slow, "object/static/particle/shared_pt_waterfalling_slow.iff")

object_static_particle_shared_pt_webber = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/particle/shared_pt_webber.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_webber.prt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 364658424,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_particle_shared_pt_webber, "object/static/particle/shared_pt_webber.iff")
