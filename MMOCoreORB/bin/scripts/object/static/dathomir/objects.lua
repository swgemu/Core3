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


object_static_dathomir_shared_dath_mistyfalls_waterfall1 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/dathomir/shared_dath_mistyfalls_waterfall1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_dath_mistyfalls_waterfall1.prt",
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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2786092096,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff", "object/static/naboo/shared_waterfall_naboo_theed_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_dathomir_shared_dath_mistyfalls_waterfall1, "object/static/dathomir/shared_dath_mistyfalls_waterfall1.iff")

object_static_dathomir_shared_dath_mistyfalls_waterfall2 = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/static/dathomir/shared_dath_mistyfalls_waterfall2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_dath_mistyfalls_waterfall2.prt",
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
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2097663191,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/terrain/base/shared_static_terrain_base.iff", "object/static/naboo/shared_waterfall_naboo_theed_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_static_dathomir_shared_dath_mistyfalls_waterfall2, "object/static/dathomir/shared_dath_mistyfalls_waterfall2.iff")
