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


object_static_space_spacestation_shared_corsec_outpost_01 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/spacestation_outpost_corsec.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:pristine wall",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@string_table:pristine wall",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 1,

	totalCellNumber = 0,

	clientObjectCRC = 2081400463,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/structure/base/shared_static_structure_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_space_spacestation_shared_corsec_outpost_01, "object/static/space/spacestation/shared_corsec_outpost_01.iff")

object_static_space_spacestation_shared_destroyed_imperial_spacestation_01 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/rebel_station_destroyed.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:pristine wall",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@string_table:pristine wall",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 1,

	totalCellNumber = 0,

	clientObjectCRC = 51631832,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/structure/base/shared_static_structure_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_space_spacestation_shared_destroyed_imperial_spacestation_01, "object/static/space/spacestation/shared_destroyed_imperial_spacestation_01.iff")

object_static_space_spacestation_shared_destroyed_neutral_spacestation_01 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/neutral_station_destroyed.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:pristine wall",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@string_table:pristine wall",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 1,

	totalCellNumber = 0,

	clientObjectCRC = 1249810321,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/structure/base/shared_static_structure_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_space_spacestation_shared_destroyed_neutral_spacestation_01, "object/static/space/spacestation/shared_destroyed_neutral_spacestation_01.iff")

object_static_space_spacestation_shared_destroyed_rebel_spacestation_01 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/rebel_station_destroyed.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:pristine wall",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@string_table:pristine wall",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 1,

	totalCellNumber = 0,

	clientObjectCRC = 2680136017,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/structure/base/shared_static_structure_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_space_spacestation_shared_destroyed_rebel_spacestation_01, "object/static/space/spacestation/shared_destroyed_rebel_spacestation_01.iff")

object_static_space_spacestation_shared_imperial_outpost_01 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/spacestation_outpost_imperial_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:pristine wall",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@string_table:pristine wall",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 1,

	totalCellNumber = 0,

	clientObjectCRC = 2798221309,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/structure/base/shared_static_structure_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_space_spacestation_shared_imperial_outpost_01, "object/static/space/spacestation/shared_imperial_outpost_01.iff")

object_static_space_spacestation_shared_imperial_spacestation_01 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/spacestation_imperial.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:pristine wall",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@string_table:pristine wall",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 1,

	totalCellNumber = 0,

	clientObjectCRC = 1432735117,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/structure/base/shared_static_structure_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_space_spacestation_shared_imperial_spacestation_01, "object/static/space/spacestation/shared_imperial_spacestation_01.iff")

object_static_space_spacestation_shared_mining_outpost_01 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/spacestation_outpost_mining.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:pristine wall",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@string_table:pristine wall",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 1,

	totalCellNumber = 0,

	clientObjectCRC = 2821130357,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/structure/base/shared_static_structure_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_space_spacestation_shared_mining_outpost_01, "object/static/space/spacestation/shared_mining_outpost_01.iff")

object_static_space_spacestation_shared_neutral_spacestation_01 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/spacestation_outpost_imperial_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:pristine wall",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@string_table:pristine wall",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 1,

	totalCellNumber = 0,

	clientObjectCRC = 1020449754,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/structure/base/shared_static_structure_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_space_spacestation_shared_neutral_spacestation_01, "object/static/space/spacestation/shared_neutral_spacestation_01.iff")

object_static_space_spacestation_shared_pirate_outpost_01 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/spacestation_outpost_pirate.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:pristine wall",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@string_table:pristine wall",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 1,

	totalCellNumber = 0,

	clientObjectCRC = 1500513199,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/structure/base/shared_static_structure_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_space_spacestation_shared_pirate_outpost_01, "object/static/space/spacestation/shared_pirate_outpost_01.iff")

object_static_space_spacestation_shared_pirate_outpost_asteroid = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/spacestation_pirate_asteroid.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:pristine wall",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@string_table:pristine wall",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 1,

	totalCellNumber = 0,

	clientObjectCRC = 1677357980,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/structure/base/shared_static_structure_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_space_spacestation_shared_pirate_outpost_asteroid, "object/static/space/spacestation/shared_pirate_outpost_asteroid.iff")

object_static_space_spacestation_shared_rebel_outpost_01 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/spacestation_outpost_rebel_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:pristine wall",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@string_table:pristine wall",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 1,

	totalCellNumber = 0,

	clientObjectCRC = 2870024383,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/structure/base/shared_static_structure_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_space_spacestation_shared_rebel_outpost_01, "object/static/space/spacestation/shared_rebel_outpost_01.iff")

object_static_space_spacestation_shared_rebel_spacestation_01 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/spacestation_outpost_imperial_s01.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:pristine wall",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@string_table:pristine wall",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 1,

	totalCellNumber = 0,

	clientObjectCRC = 2738509482,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/structure/base/shared_static_structure_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_space_spacestation_shared_rebel_spacestation_01, "object/static/space/spacestation/shared_rebel_spacestation_01.iff")

object_static_space_spacestation_shared_rsf_spacestation = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/spacestation_rsf.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:pristine wall",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@string_table:pristine wall",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 1,

	totalCellNumber = 0,

	clientObjectCRC = 1595448737,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/structure/base/shared_static_structure_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_space_spacestation_shared_rsf_spacestation, "object/static/space/spacestation/shared_rsf_spacestation.iff")

object_static_space_spacestation_shared_tradefed_destroyed_hulk = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/spacestation_tradefed_destroyed_hulk.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:pristine wall",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@string_table:pristine wall",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 1,

	totalCellNumber = 0,

	clientObjectCRC = 4274432492,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/structure/base/shared_static_structure_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_space_spacestation_shared_tradefed_destroyed_hulk, "object/static/space/spacestation/shared_tradefed_destroyed_hulk.iff")

object_static_space_spacestation_shared_tradefed_outpost_01 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/spacestation_outpost_tradefed.apt",
	arrangementDescriptors = {},

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 536870915,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "@string_table:pristine wall",

	gameObjectType = 536870915,

	locationReservationRadius = 0,
	lookAtText = "@string_table:pristine wall",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	surfaceType = 1,

	totalCellNumber = 0,

	clientObjectCRC = 58780545,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/structure/base/shared_static_structure_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_space_spacestation_shared_tradefed_outpost_01, "object/static/space/spacestation/shared_tradefed_outpost_01.iff")
