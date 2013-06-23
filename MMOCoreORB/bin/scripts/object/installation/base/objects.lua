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


object_installation_base_shared_construction_installation_base = SharedInstallationObjectTemplate:new {
	clientTemplateFileName = "object/installation/base/shared_construction_installation_base.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ply_all_construction_sign.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "",
	clientGameObjectType = 4097,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 4097,

	locationReservationRadius = 0,
	lookAtText = "@player_structure:temporary_structure",

	noBuildRadius = 0,

	objectName = "@player_structure:temporary_structure",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/installation/base/shared_installation_base.sfp",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 1,

	clientObjectCRC = 544424204,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_installation_base_shared_construction_installation_base, "object/installation/base/shared_construction_installation_base.iff")

object_installation_base_shared_installation_base = SharedInstallationObjectTemplate:new {
	clientTemplateFileName = "object/installation/base/shared_installation_base.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "",
	clientGameObjectType = 4096,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_n:default_craftable",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_installation",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/installation/base/shared_installation_base.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1610526259,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_installation_base_shared_installation_base, "object/installation/base/shared_installation_base.iff")

object_installation_base_shared_installation_default = SharedInstallationObjectTemplate:new {
	clientTemplateFileName = "object/installation/base/shared_installation_default.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "",
	clientGameObjectType = 4096,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_n:default_craftable",

	gameObjectType = 4096,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_installation",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 0,
	slotDescriptorFilename = "abstract/slot/descriptor/tangible.iff",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "footprint/installation/base/shared_installation_base.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4138250553,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_installation_base_shared_installation_default, "object/installation/base/shared_installation_default.iff")
