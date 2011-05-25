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


object_installation_faction_perk_turret_shared_block_lg = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ins_all_def_turret_lg_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/installation/client_shared_turret_block_large.cdf",
	clientGameObjectType = 4100,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@turret_n:base",

	gameObjectType = 4100,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 32,

	objectName = "@turret_n:block_large",
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
	structureFootprintFileName = "footprint/faction_perk/turret/turret_base.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2286796965,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/turret/base/shared_turret_base.iff", "object/installation/faction_perk/turret/base/shared_faction_turret_base.iff"}
}

ObjectTemplates:addClientTemplate(object_installation_faction_perk_turret_shared_block_lg, "object/installation/faction_perk/turret/shared_block_lg.iff")

object_installation_faction_perk_turret_shared_block_med = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ins_all_def_turret_m_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/installation/client_shared_turret_block_med.cdf",
	clientGameObjectType = 4100,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@turret_n:base",

	gameObjectType = 4100,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 32,

	objectName = "@turret_n:block_medium",
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
	structureFootprintFileName = "footprint/faction_perk/turret/turret_base.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1869715208,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/turret/base/shared_turret_base.iff", "object/installation/faction_perk/turret/base/shared_faction_turret_base.iff"}
}

ObjectTemplates:addClientTemplate(object_installation_faction_perk_turret_shared_block_med, "object/installation/faction_perk/turret/shared_block_med.iff")

object_installation_faction_perk_turret_shared_block_sm = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ins_all_def_turret_sm_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/installation/client_shared_turret_block_small.cdf",
	clientGameObjectType = 4100,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@turret_n:base",

	gameObjectType = 4100,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 32,

	objectName = "@turret_n:block_small",
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
	structureFootprintFileName = "footprint/faction_perk/turret/turret_base.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1969720102,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/turret/base/shared_turret_base.iff", "object/installation/faction_perk/turret/base/shared_faction_turret_base.iff"}
}

ObjectTemplates:addClientTemplate(object_installation_faction_perk_turret_shared_block_sm, "object/installation/faction_perk/turret/shared_block_sm.iff")

object_installation_faction_perk_turret_shared_dish_lg = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ins_all_def_turret_lg_s03.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/installation/client_shared_turret_dish_large.cdf",
	clientGameObjectType = 4100,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@turret_n:base",

	gameObjectType = 4100,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 32,

	objectName = "@turret_n:dish_large",
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
	structureFootprintFileName = "footprint/faction_perk/turret/turret_base.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1581064772,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/turret/base/shared_turret_base.iff", "object/installation/faction_perk/turret/base/shared_faction_turret_base.iff"}
}

ObjectTemplates:addClientTemplate(object_installation_faction_perk_turret_shared_dish_lg, "object/installation/faction_perk/turret/shared_dish_lg.iff")

object_installation_faction_perk_turret_shared_dish_sm = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ins_all_def_turret_sm_s03.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/installation/client_shared_turret_dish_small.cdf",
	clientGameObjectType = 4100,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@turret_n:base",

	gameObjectType = 4100,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 32,

	objectName = "@turret_n:dish_small",
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
	structureFootprintFileName = "footprint/faction_perk/turret/turret_base.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2736220615,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/turret/base/shared_turret_base.iff", "object/installation/faction_perk/turret/base/shared_faction_turret_base.iff"}
}

ObjectTemplates:addClientTemplate(object_installation_faction_perk_turret_shared_dish_sm, "object/installation/faction_perk/turret/shared_dish_sm.iff")

object_installation_faction_perk_turret_shared_tower_lg = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ins_all_def_turret_lg_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/installation/client_shared_turret_tower_large.cdf",
	clientGameObjectType = 4100,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@turret_n:base",

	gameObjectType = 4100,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 32,

	objectName = "@turret_n:tower_large",
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
	structureFootprintFileName = "footprint/faction_perk/turret/turret_base.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3604402557,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/turret/base/shared_turret_base.iff", "object/installation/faction_perk/turret/base/shared_faction_turret_base.iff"}
}

ObjectTemplates:addClientTemplate(object_installation_faction_perk_turret_shared_tower_lg, "object/installation/faction_perk/turret/shared_tower_lg.iff")

object_installation_faction_perk_turret_shared_tower_med = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ins_all_def_turret_m_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/installation/client_shared_turret_tower_med.cdf",
	clientGameObjectType = 4100,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@turret_n:base",

	gameObjectType = 4100,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 32,

	objectName = "@turret_n:tower_medium",
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
	structureFootprintFileName = "footprint/faction_perk/turret/turret_base.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2960737285,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/turret/base/shared_turret_base.iff", "object/installation/faction_perk/turret/base/shared_faction_turret_base.iff"}
}

ObjectTemplates:addClientTemplate(object_installation_faction_perk_turret_shared_tower_med, "object/installation/faction_perk/turret/shared_tower_med.iff")

object_installation_faction_perk_turret_shared_tower_sm = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ins_all_def_turret_sm_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/installation/client_shared_turret_tower_small.cdf",
	clientGameObjectType = 4100,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 2,
	containerVolumeLimit = 20,
	customizationVariableMapping = {},

	detailedDescription = "@turret_n:base",

	gameObjectType = 4100,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 32,

	objectName = "@turret_n:tower_small",
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
	structureFootprintFileName = "footprint/faction_perk/turret/turret_base.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 737975038,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/turret/base/shared_turret_base.iff", "object/installation/faction_perk/turret/base/shared_faction_turret_base.iff"}
}

ObjectTemplates:addClientTemplate(object_installation_faction_perk_turret_shared_tower_sm, "object/installation/faction_perk/turret/shared_tower_sm.iff")
