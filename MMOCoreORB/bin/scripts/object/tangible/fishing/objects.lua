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


object_tangible_fishing_shared_fishing_pole = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/fishing/shared_fishing_pole.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_fishing_pole.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/hold_r.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8214,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_n:fishing_pole",

	gameObjectType = 8214,

	locationReservationRadius = 0,
	lookAtText = "@container_lookat:base_container",

	noBuildRadius = 0,

	objectName = "@item_n:fishing_pole",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1813029717,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/container/base/shared_base_container.iff", "object/tangible/container/base/shared_base_container_volume.iff", "object/tangible/wearables/base/shared_base_backpack.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_fishing_shared_fishing_pole, "object/tangible/fishing/shared_fishing_pole.iff")

object_tangible_fishing_shared_marker = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/fishing/shared_marker.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/eqp_fishing_float.apt",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/back.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8213,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 50,
	customizationVariableMapping = {},

	detailedDescription = "@item_n:fishing_marker",

	gameObjectType = 8213,

	locationReservationRadius = 0,
	lookAtText = "@container_lookat:base_container",

	noBuildRadius = 0,

	objectName = "@item_n:fishing_marker",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 0,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1763394438,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/container/base/shared_base_container.iff", "object/tangible/container/base/shared_base_container_volume.iff", "object/tangible/wearables/base/shared_base_backpack.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_fishing_shared_marker, "object/tangible/fishing/shared_marker.iff")

object_tangible_fishing_shared_splash = SharedStaticObjectTemplate:new {
	clientTemplateFileName = "object/tangible/fishing/shared_splash.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/pt_splash.prt",
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

	clientObjectCRC = 1084993175,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/particle/base/shared_static_particle_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_fishing_shared_splash, "object/tangible/fishing/shared_splash.iff")
