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


object_static_terrain_tatooine_shared_pinnacle_sacred_tatooine = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/poi_tato_sacred_pinnacle.apt",
	arrangementDescriptors = {},

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

	detailedDescription = "@string_table:Tatooine Sacred Pinnacle",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 20,

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

	clientObjectCRC = 2387521344,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_terrain_tatooine_shared_pinnacle_sacred_tatooine, "object/static/terrain/tatooine/shared_pinnacle_sacred_tatooine.iff")

object_static_terrain_tatooine_shared_poi_sarlacc_collision_floor = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/poi_tato_sarlacc_collision.apt",
	arrangementDescriptors = {},

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

	detailedDescription = "@string_table:Sarlacc Floor Collision",

	gameObjectType = 5,

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

	clientObjectCRC = 3940129403,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_terrain_tatooine_shared_poi_sarlacc_collision_floor, "object/static/terrain/tatooine/shared_poi_sarlacc_collision_floor.iff")

object_static_terrain_tatooine_shared_rock_arch_large_tatooine_style_1 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/rock_tatt_arch_lrg.apt",
	arrangementDescriptors = {},

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

	detailedDescription = "@string_table:Tatooine Rock Arch",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 20,

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

	clientObjectCRC = 3663567208,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_terrain_tatooine_shared_rock_arch_large_tatooine_style_1, "object/static/terrain/tatooine/shared_rock_arch_large_tatooine_style_1.iff")

object_static_terrain_tatooine_shared_rock_arch_medium_tatooine_style_1 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/rock_tatt_arch_med.apt",
	arrangementDescriptors = {},

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

	detailedDescription = "@string_table:Tatooine Rock Arch",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 20,

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

	clientObjectCRC = 3478274265,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_terrain_tatooine_shared_rock_arch_medium_tatooine_style_1, "object/static/terrain/tatooine/shared_rock_arch_medium_tatooine_style_1.iff")

object_static_terrain_tatooine_shared_rock_arch_small_tatooine_style_1 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/rock_tatt_arch_sm.apt",
	arrangementDescriptors = {},

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

	detailedDescription = "@string_table:Tatooine Rock Arch",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 20,

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

	clientObjectCRC = 3539268114,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_terrain_tatooine_shared_rock_arch_small_tatooine_style_1, "object/static/terrain/tatooine/shared_rock_arch_small_tatooine_style_1.iff")

object_static_terrain_tatooine_shared_rock_mushroom_tatooine_style_1 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/rock_tatt_mushroom.apt",
	arrangementDescriptors = {},

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

	detailedDescription = "@string_table:Tatooine Rock Mushroom",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 20,

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

	clientObjectCRC = 611566460,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_terrain_tatooine_shared_rock_mushroom_tatooine_style_1, "object/static/terrain/tatooine/shared_rock_mushroom_tatooine_style_1.iff")

object_static_terrain_tatooine_shared_rock_spire_fin_tatooine = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/rock_tatt_spire_fin.apt",
	arrangementDescriptors = {},

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

	detailedDescription = "@string_table:Tatooine Rock Spire",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 60,

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

	clientObjectCRC = 1526101729,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_terrain_tatooine_shared_rock_spire_fin_tatooine, "object/static/terrain/tatooine/shared_rock_spire_fin_tatooine.iff")

object_static_terrain_tatooine_shared_rock_spire_lumpy_tatooine = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/rock_tatt_spire_lumpy.apt",
	arrangementDescriptors = {},

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

	detailedDescription = "@string_table:Tatooine Rock Spire",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 20,

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

	clientObjectCRC = 3421956208,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_terrain_tatooine_shared_rock_spire_lumpy_tatooine, "object/static/terrain/tatooine/shared_rock_spire_lumpy_tatooine.iff")

object_static_terrain_tatooine_shared_rock_spire_lumpy_tatooine_style_1 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/rock_tatt_spire_lumpy_a1.apt",
	arrangementDescriptors = {},

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

	detailedDescription = "@string_table:Tatooine Rock Spire",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 20,

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

	clientObjectCRC = 1746495727,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_terrain_tatooine_shared_rock_spire_lumpy_tatooine_style_1, "object/static/terrain/tatooine/shared_rock_spire_lumpy_tatooine_style_1.iff")

object_static_terrain_tatooine_shared_rock_spire_lumpy_tatooine_style_2 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/rock_tatt_spire_lumpy_a2.apt",
	arrangementDescriptors = {},

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

	detailedDescription = "@string_table:Tatooine Rock Spire",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 20,

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

	clientObjectCRC = 3004088440,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_terrain_tatooine_shared_rock_spire_lumpy_tatooine_style_2, "object/static/terrain/tatooine/shared_rock_spire_lumpy_tatooine_style_2.iff")

object_static_terrain_tatooine_shared_rock_spire_skinny_tatooine = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/rock_tatt_spire_skinny.apt",
	arrangementDescriptors = {},

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

	detailedDescription = "@string_table:Tatooine Rock Spire",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 17,

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

	clientObjectCRC = 505839558,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_terrain_tatooine_shared_rock_spire_skinny_tatooine, "object/static/terrain/tatooine/shared_rock_spire_skinny_tatooine.iff")

object_static_terrain_tatooine_shared_rock_spire_skinny_tatooine_style_1 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/rock_tatt_spire_skinny_a1.apt",
	arrangementDescriptors = {},

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

	detailedDescription = "@string_table:Tatooine Rock Spire",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 20,

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

	clientObjectCRC = 24378186,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_terrain_tatooine_shared_rock_spire_skinny_tatooine_style_1, "object/static/terrain/tatooine/shared_rock_spire_skinny_tatooine_style_1.iff")

object_static_terrain_tatooine_shared_rock_spire_skinny_tatooine_style_2 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/rock_tatt_spire_skinny_a2.apt",
	arrangementDescriptors = {},

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

	detailedDescription = "@string_table:Tatooine Rock Spire",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 20,

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

	clientObjectCRC = 3664008157,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_terrain_tatooine_shared_rock_spire_skinny_tatooine_style_2, "object/static/terrain/tatooine/shared_rock_spire_skinny_tatooine_style_2.iff")

object_static_terrain_tatooine_shared_rock_spire_smooth_tatooine = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/rock_tatt_spire_smooth.apt",
	arrangementDescriptors = {},

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

	detailedDescription = "@string_table:Tatooine Rock Spire",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 20,

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

	clientObjectCRC = 3455314010,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_terrain_tatooine_shared_rock_spire_smooth_tatooine, "object/static/terrain/tatooine/shared_rock_spire_smooth_tatooine.iff")

object_static_terrain_tatooine_shared_rock_spire_smooth_tatooine_style_1 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/rock_tatt_spire_smooth_a1.apt",
	arrangementDescriptors = {},

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

	detailedDescription = "@string_table:Tatooine Rock Spire",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 20,

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

	clientObjectCRC = 323068853,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_terrain_tatooine_shared_rock_spire_smooth_tatooine_style_1, "object/static/terrain/tatooine/shared_rock_spire_smooth_tatooine_style_1.iff")

object_static_terrain_tatooine_shared_rock_spire_smooth_tatooine_style_2 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/rock_tatt_spire_smooth_a2.apt",
	arrangementDescriptors = {},

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

	detailedDescription = "@string_table:Tatooine Rock Spire",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 20,

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

	clientObjectCRC = 3361082146,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_terrain_tatooine_shared_rock_spire_smooth_tatooine_style_2, "object/static/terrain/tatooine/shared_rock_spire_smooth_tatooine_style_2.iff")
