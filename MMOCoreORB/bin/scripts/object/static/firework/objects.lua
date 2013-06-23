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


object_static_firework_shared_fx_01 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/firework/shared_fx_01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_fireworks_complete_s01_blast_blue.prt",
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
	snapToTerrain = 1,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4015660279,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff", "object/static/firework/base/shared_firework_fx_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_firework_shared_fx_01, "object/static/firework/shared_fx_01.iff")

object_static_firework_shared_fx_02 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/firework/shared_fx_02.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_fireworks_complete_s02_trail_blast.prt",
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
	snapToTerrain = 1,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 877507680,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff", "object/static/firework/base/shared_firework_fx_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_firework_shared_fx_02, "object/static/firework/shared_fx_02.iff")

object_static_firework_shared_fx_03 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/firework/shared_fx_03.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_fireworks_complete_s03_trail_shockwave.prt",
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
	snapToTerrain = 1,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2101400557,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff", "object/static/firework/base/shared_firework_fx_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_firework_shared_fx_03, "object/static/firework/shared_fx_03.iff")

object_static_firework_shared_fx_04 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/firework/shared_fx_04.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_fireworks_complete_s04_ring.prt",
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
	snapToTerrain = 1,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2258893049,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff", "object/static/firework/base/shared_firework_fx_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_firework_shared_fx_04, "object/static/firework/shared_fx_04.iff")

object_static_firework_shared_fx_05 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/firework/shared_fx_05.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_fireworks_complete_s05_ring_double.prt",
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
	snapToTerrain = 1,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3484327796,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff", "object/static/firework/base/shared_firework_fx_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_firework_shared_fx_05, "object/static/firework/shared_fx_05.iff")

object_static_firework_shared_fx_10 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/firework/shared_fx_10.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_fireworks_complete_s10_chandelier.prt",
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
	snapToTerrain = 1,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3179247106,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff", "object/static/firework/base/shared_firework_fx_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_firework_shared_fx_10, "object/static/firework/shared_fx_10.iff")

object_static_firework_shared_fx_11 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/firework/shared_fx_11.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_fireworks_complete_s11_blast_sphere.prt",
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
	snapToTerrain = 1,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4101116303,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff", "object/static/firework/base/shared_firework_fx_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_firework_shared_fx_11, "object/static/firework/shared_fx_11.iff")

object_static_firework_shared_fx_18 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/firework/shared_fx_18.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_fireworks_complete_s18_flocking.prt",
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
	snapToTerrain = 1,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4237717764,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff", "object/static/firework/base/shared_firework_fx_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_firework_shared_fx_18, "object/static/firework/shared_fx_18.iff")

object_static_firework_shared_show_launcher = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/firework/shared_show_launcher.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_firework_s1.apt",
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

	detailedDescription = "@firework_d:show",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@firework_n:show",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4092821074,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_firework_shared_show_launcher, "object/static/firework/shared_show_launcher.iff")
