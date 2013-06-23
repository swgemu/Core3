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


object_building_poi_hq_shared_hutt_lrg = SharedBuildingObjectTemplate:new {
	clientTemplateFileName = "object/building/poi/hq/shared_hutt_lrg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:hq_hutt_lrg",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_tato_house_lg_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/tatooine_flora_large.lay",
	totalCellNumber = 10,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2883928313,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff", "object/building/poi/base/shared_base_poi_building.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_building_poi_hq_shared_hutt_lrg, "object/building/poi/hq/shared_hutt_lrg.iff")

object_building_poi_hq_shared_hutt_med = SharedBuildingObjectTemplate:new {
	clientTemplateFileName = "object/building/poi/hq/shared_hutt_med.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:hq_hutt_med",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_tato_house_m_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/tatooine_flora_large.lay",
	totalCellNumber = 8,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3359402016,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff", "object/building/poi/base/shared_base_poi_building.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_building_poi_hq_shared_hutt_med, "object/building/poi/hq/shared_hutt_med.iff")

object_building_poi_hq_shared_hutt_sm = SharedBuildingObjectTemplate:new {
	clientTemplateFileName = "object/building/poi/hq/shared_hutt_sm.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:hq_hutt_sm",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/ply_tato_house_sm_s01_fp1.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/tatooine_flora_large.lay",
	totalCellNumber = 3,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1295187033,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff", "object/building/poi/base/shared_base_poi_building.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_building_poi_hq_shared_hutt_sm, "object/building/poi/hq/shared_hutt_sm.iff")

object_building_poi_hq_shared_imperial_lrg = SharedBuildingObjectTemplate:new {
	clientTemplateFileName = "object/building/poi/hq/shared_imperial_lrg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:hq_imperial_lrg",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_police_station_impl_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/tatooine_flora_large.lay",
	totalCellNumber = 12,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1970934894,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff", "object/building/poi/base/shared_base_poi_building.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_building_poi_hq_shared_imperial_lrg, "object/building/poi/hq/shared_imperial_lrg.iff")

object_building_poi_hq_shared_imperial_med = SharedBuildingObjectTemplate:new {
	clientTemplateFileName = "object/building/poi/hq/shared_imperial_med.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:hq_imperial_med",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_guard_house_impl_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/tatooine_flora_large.lay",
	totalCellNumber = 2,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 379796663,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff", "object/building/poi/base/shared_base_poi_building.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_building_poi_hq_shared_imperial_med, "object/building/poi/hq/shared_imperial_med.iff")

object_building_poi_hq_shared_imperial_sm = SharedBuildingObjectTemplate:new {
	clientTemplateFileName = "object/building/poi/hq/shared_imperial_sm.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:hq_imperial_sm",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_impl_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/tatooine_flora_large.lay",
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 759219915,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff", "object/building/poi/base/shared_base_poi_building.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_building_poi_hq_shared_imperial_sm, "object/building/poi/hq/shared_imperial_sm.iff")

object_building_poi_hq_shared_rebel_lrg = SharedBuildingObjectTemplate:new {
	clientTemplateFileName = "object/building/poi/hq/shared_rebel_lrg.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:hq_rebel_lrg",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_police_station_rebl_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/tatooine_flora_large.lay",
	totalCellNumber = 12,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1900138383,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff", "object/building/poi/base/shared_base_poi_building.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_building_poi_hq_shared_rebel_lrg, "object/building/poi/hq/shared_rebel_lrg.iff")

object_building_poi_hq_shared_rebel_med = SharedBuildingObjectTemplate:new {
	clientTemplateFileName = "object/building/poi/hq/shared_rebel_med.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:hq_rebel_med",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_base_guard_house_rebl_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/tatooine_flora_large.lay",
	totalCellNumber = 2,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 312010582,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff", "object/building/poi/base/shared_base_poi_building.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_building_poi_hq_shared_rebel_med, "object/building/poi/hq/shared_rebel_med.iff")

object_building_poi_hq_shared_rebel_sm = SharedBuildingObjectTemplate:new {
	clientTemplateFileName = "object/building/poi/hq/shared_rebel_sm.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/rock_pebbleclump_a3.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 512,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 255,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,
	customizationVariableMapping = {},

	detailedDescription = "@building_detail:base_military_building",

	gameObjectType = 512,

	interiorLayoutFileName = "",

	locationReservationRadius = 0,
	lookAtText = "@building_lookat:base_military_building",

	noBuildRadius = 64,

	objectName = "@poi_n:hq_rebel_sm",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "appearance/mun_all_military_storage_shed_rebl_s01.pob",

	rangedIntCustomizationVariables = {},

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 2,

	targetable = 0,
	terrainModificationFileName = "terrain/tatooine_flora_large.lay",
	totalCellNumber = 6,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2752460800,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/building/base/shared_base_building.iff", "object/building/base/shared_base_military_building.iff", "object/building/poi/base/shared_base_poi_building.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_building_poi_hq_shared_rebel_sm, "object/building/poi/hq/shared_rebel_sm.iff")
