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


object_tangible_ship_components_armor_shared_arm_corellian_advanced_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_corellian_advanced_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_corellian_advanced_durasteel_n",
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

	clientObjectCRC = 3014828629,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_corellian_advanced_durasteel, "object/tangible/ship/components/armor/shared_arm_corellian_advanced_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_corellian_cheap_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_corellian_cheap_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_corellian_cheap_durasteel_n",
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

	clientObjectCRC = 2711392870,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_corellian_cheap_durasteel, "object/tangible/ship/components/armor/shared_arm_corellian_cheap_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_corellian_elite_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_corellian_elite_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_corellian_elite_durasteel_n",
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

	clientObjectCRC = 1457378842,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_corellian_elite_durasteel, "object/tangible/ship/components/armor/shared_arm_corellian_elite_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_corellian_enhanced_elite_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_corellian_enhanced_elite_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_corellian_enhanced_elite_plastisteel_n",
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

	clientObjectCRC = 4170685241,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_corellian_enhanced_elite_plastisteel, "object/tangible/ship/components/armor/shared_arm_corellian_enhanced_elite_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_corellian_heavy_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_corellian_heavy_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_corellian_heavy_durasteel_n",
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

	clientObjectCRC = 912895666,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_corellian_heavy_durasteel, "object/tangible/ship/components/armor/shared_arm_corellian_heavy_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_corellian_improved_advanced_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_corellian_improved_advanced_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_corellian_improved_advanced_durasteel_n",
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

	clientObjectCRC = 3145007708,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_corellian_improved_advanced_durasteel, "object/tangible/ship/components/armor/shared_arm_corellian_improved_advanced_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_corellian_light_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_corellian_light_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_corellian_light_durasteel_n",
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

	clientObjectCRC = 1182016930,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_corellian_light_durasteel, "object/tangible/ship/components/armor/shared_arm_corellian_light_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_corellian_modified_heavy_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_corellian_modified_heavy_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_corellian_modified_heavy_durasteel_n",
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

	clientObjectCRC = 4076917946,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_corellian_modified_heavy_durasteel, "object/tangible/ship/components/armor/shared_arm_corellian_modified_heavy_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_corellian_reinforced_light_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_corellian_reinforced_light_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_corellian_reinforced_light_durasteel_n",
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

	clientObjectCRC = 2793909249,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_corellian_reinforced_light_durasteel, "object/tangible/ship/components/armor/shared_arm_corellian_reinforced_light_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_corellian_reinforced_supreme_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_corellian_reinforced_supreme_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_corellian_reinforced_supreme_durasteel_n",
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

	clientObjectCRC = 792770319,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_corellian_reinforced_supreme_durasteel, "object/tangible/ship/components/armor/shared_arm_corellian_reinforced_supreme_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_corellian_special_standard_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_corellian_special_standard_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_corellian_special_standard_durasteel_n",
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

	clientObjectCRC = 3131875437,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_corellian_special_standard_durasteel, "object/tangible/ship/components/armor/shared_arm_corellian_special_standard_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_corellian_standard_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_corellian_standard_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_corellian_standard_durasteel_n",
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

	clientObjectCRC = 2484547864,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_corellian_standard_durasteel, "object/tangible/ship/components/armor/shared_arm_corellian_standard_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_corellian_supreme_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_corellian_supreme_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_corellian_supreme_durasteel_n",
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

	clientObjectCRC = 3245469229,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_corellian_supreme_durasteel, "object/tangible/ship/components/armor/shared_arm_corellian_supreme_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_cygnus_light_weave = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_cygnus_light_weave.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_cygnus_light_weave_n",
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

	clientObjectCRC = 2417515644,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_cygnus_light_weave, "object/tangible/ship/components/armor/shared_arm_cygnus_light_weave.iff")

object_tangible_ship_components_armor_shared_arm_cygnus_standard_weave = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_cygnus_standard_weave.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_cygnus_standard_weave_n",
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

	clientObjectCRC = 1396020444,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_cygnus_standard_weave, "object/tangible/ship/components/armor/shared_arm_cygnus_standard_weave.iff")

object_tangible_ship_components_armor_shared_arm_freitek_deluxe_light = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_freitek_deluxe_light.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_freitek_deluxe_light_n",
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

	clientObjectCRC = 203726257,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_freitek_deluxe_light, "object/tangible/ship/components/armor/shared_arm_freitek_deluxe_light.iff")

object_tangible_ship_components_armor_shared_arm_freitek_standard = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_freitek_standard.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_freitek_standard_n",
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

	clientObjectCRC = 1109511404,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_freitek_standard, "object/tangible/ship/components/armor/shared_arm_freitek_standard.iff")

object_tangible_ship_components_armor_shared_arm_gallofree_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_gallofree_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_gallofree_mk1_n",
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

	clientObjectCRC = 39221168,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_gallofree_mk1, "object/tangible/ship/components/armor/shared_arm_gallofree_mk1.iff")

object_tangible_ship_components_armor_shared_arm_gallofree_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_gallofree_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_gallofree_mk2_n",
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

	clientObjectCRC = 3644972839,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_gallofree_mk2, "object/tangible/ship/components/armor/shared_arm_gallofree_mk2.iff")

object_tangible_ship_components_armor_shared_arm_generic = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_generic.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:armor_generic",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_generic",
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

	clientObjectCRC = 1622491618,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_generic, "object/tangible/ship/components/armor/shared_arm_generic.iff")

object_tangible_ship_components_armor_shared_arm_incom_light_plate = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_incom_light_plate.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_incom_light_plate_n",
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

	clientObjectCRC = 1227421656,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_incom_light_plate, "object/tangible/ship/components/armor/shared_arm_incom_light_plate.iff")

object_tangible_ship_components_armor_shared_arm_incom_modified_standard_plate = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_incom_modified_standard_plate.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_incom_modified_standard_plate_n",
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

	clientObjectCRC = 2366385613,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_incom_modified_standard_plate, "object/tangible/ship/components/armor/shared_arm_incom_modified_standard_plate.iff")

object_tangible_ship_components_armor_shared_arm_incom_standard_plate = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_incom_standard_plate.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_incom_standard_plate_n",
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

	clientObjectCRC = 641382819,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_incom_standard_plate, "object/tangible/ship/components/armor/shared_arm_incom_standard_plate.iff")

object_tangible_ship_components_armor_shared_arm_kessel_imperial_rendili_crystalline_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_kessel_imperial_rendili_crystalline_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_kessel_imperial_rendili_crystalline_durasteel_n",
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

	clientObjectCRC = 1625601979,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_kessel_imperial_rendili_crystalline_durasteel, "object/tangible/ship/components/armor/shared_arm_kessel_imperial_rendili_crystalline_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_kessel_imperial_sds_imperial_impervious = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_kessel_imperial_sds_imperial_impervious.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_kessel_imperial_sds_imperial_impervious_n",
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

	clientObjectCRC = 3348661069,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_kessel_imperial_sds_imperial_impervious, "object/tangible/ship/components/armor/shared_arm_kessel_imperial_sds_imperial_impervious.iff")

object_tangible_ship_components_armor_shared_arm_kessel_imperial_sfs_imperial_finest = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_kessel_imperial_sfs_imperial_finest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_kessel_imperial_sfs_imperial_finest_n",
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

	clientObjectCRC = 1099045901,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_kessel_imperial_sfs_imperial_finest, "object/tangible/ship/components/armor/shared_arm_kessel_imperial_sfs_imperial_finest.iff")

object_tangible_ship_components_armor_shared_arm_kessel_rebel_mandal_corrugated_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_kessel_rebel_mandal_corrugated_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_kessel_rebel_mandal_corrugated_plastisteel_n",
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

	clientObjectCRC = 4176245510,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_kessel_rebel_mandal_corrugated_plastisteel, "object/tangible/ship/components/armor/shared_arm_kessel_rebel_mandal_corrugated_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_kessel_rebel_slayn_flexsteel_multilayer = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_kessel_rebel_slayn_flexsteel_multilayer.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_kessel_rebel_slayn_flexsteel_multilayer_n",
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

	clientObjectCRC = 3545922834,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_kessel_rebel_slayn_flexsteel_multilayer, "object/tangible/ship/components/armor/shared_arm_kessel_rebel_slayn_flexsteel_multilayer.iff")

object_tangible_ship_components_armor_shared_arm_kessel_rebel_sorosuub_spidershell_plating = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_kessel_rebel_sorosuub_spidershell_plating.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_kessel_rebel_sorosuub_spidershell_plating_n",
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

	clientObjectCRC = 1672663550,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_kessel_rebel_sorosuub_spidershell_plating, "object/tangible/ship/components/armor/shared_arm_kessel_rebel_sorosuub_spidershell_plating.iff")

object_tangible_ship_components_armor_shared_arm_koensayr_advanced_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_koensayr_advanced_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_koensayr_advanced_durasteel_n",
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

	clientObjectCRC = 828530711,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_koensayr_advanced_durasteel, "object/tangible/ship/components/armor/shared_arm_koensayr_advanced_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_koensayr_b5_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_koensayr_b5_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_koensayr_b5_durasteel_n",
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

	clientObjectCRC = 1171221751,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_koensayr_b5_durasteel, "object/tangible/ship/components/armor/shared_arm_koensayr_b5_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_koensayr_b9_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_koensayr_b9_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_koensayr_b9_durasteel_n",
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

	clientObjectCRC = 3460991428,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_koensayr_b9_durasteel, "object/tangible/ship/components/armor/shared_arm_koensayr_b9_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_koensayr_elite_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_koensayr_elite_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_koensayr_elite_plastisteel_n",
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

	clientObjectCRC = 2857270890,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_koensayr_elite_plastisteel, "object/tangible/ship/components/armor/shared_arm_koensayr_elite_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_koensayr_enhanced_heavy_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_koensayr_enhanced_heavy_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_koensayr_enhanced_heavy_durasteel_n",
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

	clientObjectCRC = 3973535465,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_koensayr_enhanced_heavy_durasteel, "object/tangible/ship/components/armor/shared_arm_koensayr_enhanced_heavy_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_koensayr_enhanced_standard_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_koensayr_enhanced_standard_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_koensayr_enhanced_standard_durasteel_n",
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

	clientObjectCRC = 935608310,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_koensayr_enhanced_standard_durasteel, "object/tangible/ship/components/armor/shared_arm_koensayr_enhanced_standard_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_koensayr_heavy_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_koensayr_heavy_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_koensayr_heavy_durasteel_n",
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

	clientObjectCRC = 1092389644,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_koensayr_heavy_durasteel, "object/tangible/ship/components/armor/shared_arm_koensayr_heavy_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_koensayr_improved_elite_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_koensayr_improved_elite_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_koensayr_improved_elite_plastisteel_n",
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

	clientObjectCRC = 2296134538,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_koensayr_improved_elite_plastisteel, "object/tangible/ship/components/armor/shared_arm_koensayr_improved_elite_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_koensayr_light_advanced_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_koensayr_light_advanced_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_koensayr_light_advanced_durasteel_n",
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

	clientObjectCRC = 1035628527,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_koensayr_light_advanced_durasteel, "object/tangible/ship/components/armor/shared_arm_koensayr_light_advanced_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_koensayr_limited_heavy_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_koensayr_limited_heavy_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_koensayr_limited_heavy_durasteel_n",
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

	clientObjectCRC = 2917985380,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_koensayr_limited_heavy_durasteel, "object/tangible/ship/components/armor/shared_arm_koensayr_limited_heavy_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_koensayr_limited_supreme_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_koensayr_limited_supreme_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_koensayr_limited_supreme_durasteel_n",
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

	clientObjectCRC = 2534423202,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_koensayr_limited_supreme_durasteel, "object/tangible/ship/components/armor/shared_arm_koensayr_limited_supreme_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_koensayr_promotional_b9_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_koensayr_promotional_b9_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_koensayr_promotional_b9_durasteel_n",
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

	clientObjectCRC = 167045731,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_koensayr_promotional_b9_durasteel, "object/tangible/ship/components/armor/shared_arm_koensayr_promotional_b9_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_koensayr_reinforced_b5_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_koensayr_reinforced_b5_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_koensayr_reinforced_b5_durasteel_n",
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

	clientObjectCRC = 258640314,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_koensayr_reinforced_b5_durasteel, "object/tangible/ship/components/armor/shared_arm_koensayr_reinforced_b5_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_koensayr_special_supreme_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_koensayr_special_supreme_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_koensayr_special_supreme_durasteel_n",
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

	clientObjectCRC = 1378987090,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_koensayr_special_supreme_durasteel, "object/tangible/ship/components/armor/shared_arm_koensayr_special_supreme_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_koensayr_standard_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_koensayr_standard_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_koensayr_standard_durasteel_n",
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

	clientObjectCRC = 382202714,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_koensayr_standard_durasteel, "object/tangible/ship/components/armor/shared_arm_koensayr_standard_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_koensayr_supreme_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_koensayr_supreme_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_koensayr_supreme_durasteel_n",
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

	clientObjectCRC = 1438984098,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_koensayr_supreme_durasteel, "object/tangible/ship/components/armor/shared_arm_koensayr_supreme_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_koensayr_thick_advanced_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_koensayr_thick_advanced_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_koensayr_thick_advanced_durasteel_n",
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

	clientObjectCRC = 3772847383,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_koensayr_thick_advanced_durasteel, "object/tangible/ship/components/armor/shared_arm_koensayr_thick_advanced_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_kse_advanced_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_kse_advanced_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_kse_advanced_durasteel_n",
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

	clientObjectCRC = 987276877,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_kse_advanced_durasteel, "object/tangible/ship/components/armor/shared_arm_kse_advanced_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_kse_customized_advanced_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_kse_customized_advanced_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_kse_customized_advanced_durasteel_n",
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

	clientObjectCRC = 2637845243,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_kse_customized_advanced_durasteel, "object/tangible/ship/components/armor/shared_arm_kse_customized_advanced_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_kse_elite_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_kse_elite_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_kse_elite_durasteel_n",
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

	clientObjectCRC = 3918028246,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_kse_elite_durasteel, "object/tangible/ship/components/armor/shared_arm_kse_elite_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_kse_heavy_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_kse_heavy_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_kse_heavy_durasteel_n",
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

	clientObjectCRC = 2302420350,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_kse_heavy_durasteel, "object/tangible/ship/components/armor/shared_arm_kse_heavy_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_kse_intermediate_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_kse_intermediate_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_kse_intermediate_durasteel_n",
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

	clientObjectCRC = 2472601379,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_kse_intermediate_durasteel, "object/tangible/ship/components/armor/shared_arm_kse_intermediate_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_kse_limited_heavy_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_kse_limited_heavy_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_kse_limited_heavy_durasteel_n",
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

	clientObjectCRC = 754583097,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_kse_limited_heavy_durasteel, "object/tangible/ship/components/armor/shared_arm_kse_limited_heavy_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_kse_modified_heavy_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_kse_modified_heavy_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_kse_modified_heavy_durasteel_n",
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

	clientObjectCRC = 759538289,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_kse_modified_heavy_durasteel, "object/tangible/ship/components/armor/shared_arm_kse_modified_heavy_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_kse_modified_light_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_kse_modified_light_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_kse_modified_light_durasteel_n",
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

	clientObjectCRC = 1566058849,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_kse_modified_light_durasteel, "object/tangible/ship/components/armor/shared_arm_kse_modified_light_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_kse_modified_supreme_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_kse_modified_supreme_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_kse_modified_supreme_durasteel_n",
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

	clientObjectCRC = 2288993339,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_kse_modified_supreme_durasteel, "object/tangible/ship/components/armor/shared_arm_kse_modified_supreme_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_kse_standard_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_kse_standard_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_kse_standard_durasteel_n",
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

	clientObjectCRC = 494744832,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_kse_standard_durasteel, "object/tangible/ship/components/armor/shared_arm_kse_standard_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_kse_supreme_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_kse_supreme_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_kse_supreme_durasteel_n",
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

	clientObjectCRC = 706111172,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_kse_supreme_durasteel, "object/tangible/ship/components/armor/shared_arm_kse_supreme_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_mandal_advanced_composite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mandal_advanced_composite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mandal_advanced_composite_n",
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

	clientObjectCRC = 1688248880,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mandal_advanced_composite, "object/tangible/ship/components/armor/shared_arm_mandal_advanced_composite.iff")

object_tangible_ship_components_armor_shared_arm_mandal_composite_j5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mandal_composite_j5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mandal_composite_j5_n",
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

	clientObjectCRC = 2614891769,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mandal_composite_j5, "object/tangible/ship/components/armor/shared_arm_mandal_composite_j5.iff")

object_tangible_ship_components_armor_shared_arm_mandal_composite_j7 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mandal_composite_j7.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mandal_composite_j7_n",
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

	clientObjectCRC = 164027363,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mandal_composite_j7, "object/tangible/ship/components/armor/shared_arm_mandal_composite_j7.iff")

object_tangible_ship_components_armor_shared_arm_mandal_custom_heavy_composite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mandal_custom_heavy_composite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mandal_custom_heavy_composite_n",
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

	clientObjectCRC = 2443269363,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mandal_custom_heavy_composite, "object/tangible/ship/components/armor/shared_arm_mandal_custom_heavy_composite.iff")

object_tangible_ship_components_armor_shared_arm_mandal_double_insulated_i5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mandal_double_insulated_i5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mandal_double_insulated_i5_n",
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

	clientObjectCRC = 4187492746,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mandal_double_insulated_i5, "object/tangible/ship/components/armor/shared_arm_mandal_double_insulated_i5.iff")

object_tangible_ship_components_armor_shared_arm_mandal_double_insulated_i7 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mandal_double_insulated_i7.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mandal_double_insulated_i7_n",
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

	clientObjectCRC = 1803738768,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mandal_double_insulated_i7, "object/tangible/ship/components/armor/shared_arm_mandal_double_insulated_i7.iff")

object_tangible_ship_components_armor_shared_arm_mandal_double_plated_composite_j7 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mandal_double_plated_composite_j7.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mandal_double_plated_composite_j7_n",
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

	clientObjectCRC = 2556935456,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mandal_double_plated_composite_j7, "object/tangible/ship/components/armor/shared_arm_mandal_double_plated_composite_j7.iff")

object_tangible_ship_components_armor_shared_arm_mandal_elite_composite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mandal_elite_composite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mandal_elite_composite_n",
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

	clientObjectCRC = 2373681857,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mandal_elite_composite, "object/tangible/ship/components/armor/shared_arm_mandal_elite_composite.iff")

object_tangible_ship_components_armor_shared_arm_mandal_enhanced_elite_composite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mandal_enhanced_elite_composite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mandal_enhanced_elite_composite_n",
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

	clientObjectCRC = 1466373688,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mandal_enhanced_elite_composite, "object/tangible/ship/components/armor/shared_arm_mandal_enhanced_elite_composite.iff")

object_tangible_ship_components_armor_shared_arm_mandal_enhanced_heavy_composite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mandal_enhanced_heavy_composite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mandal_enhanced_heavy_composite_n",
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

	clientObjectCRC = 936603280,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mandal_enhanced_heavy_composite, "object/tangible/ship/components/armor/shared_arm_mandal_enhanced_heavy_composite.iff")

object_tangible_ship_components_armor_shared_arm_mandal_heavy_composite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mandal_heavy_composite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mandal_heavy_composite_n",
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

	clientObjectCRC = 3989830249,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mandal_heavy_composite, "object/tangible/ship/components/armor/shared_arm_mandal_heavy_composite.iff")

object_tangible_ship_components_armor_shared_arm_mandal_insulated_i7 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mandal_insulated_i7.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mandal_insulated_i7_n",
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

	clientObjectCRC = 156429997,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mandal_insulated_i7, "object/tangible/ship/components/armor/shared_arm_mandal_insulated_i7.iff")

object_tangible_ship_components_armor_shared_arm_mandal_modified_supreme_composite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mandal_modified_supreme_composite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mandal_modified_supreme_composite_n",
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

	clientObjectCRC = 2798415892,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mandal_modified_supreme_composite, "object/tangible/ship/components/armor/shared_arm_mandal_modified_supreme_composite.iff")

object_tangible_ship_components_armor_shared_arm_mandal_modifier_composite_j5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mandal_modifier_composite_j5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mandal_modifier_composite_j5_n",
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

	clientObjectCRC = 2535453726,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mandal_modifier_composite_j5, "object/tangible/ship/components/armor/shared_arm_mandal_modifier_composite_j5.iff")

object_tangible_ship_components_armor_shared_arm_mandal_reinforced_advanced_composite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mandal_reinforced_advanced_composite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mandal_reinforced_advanced_composite_n",
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

	clientObjectCRC = 3155179627,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mandal_reinforced_advanced_composite, "object/tangible/ship/components/armor/shared_arm_mandal_reinforced_advanced_composite.iff")

object_tangible_ship_components_armor_shared_arm_mandal_supreme_composite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mandal_supreme_composite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mandal_supreme_composite_n",
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

	clientObjectCRC = 3572993151,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mandal_supreme_composite, "object/tangible/ship/components/armor/shared_arm_mandal_supreme_composite.iff")

object_tangible_ship_components_armor_shared_arm_mission_reward_imperial_rss_special_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mission_reward_imperial_rss_special_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mission_reward_imperial_rss_special_durasteel_n",
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

	clientObjectCRC = 8094392,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mission_reward_imperial_rss_special_durasteel, "object/tangible/ship/components/armor/shared_arm_mission_reward_imperial_rss_special_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_mission_reward_imperial_sfs_light_military = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mission_reward_imperial_sfs_light_military.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mission_reward_imperial_sfs_light_military_n",
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

	clientObjectCRC = 3133915377,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mission_reward_imperial_sfs_light_military, "object/tangible/ship/components/armor/shared_arm_mission_reward_imperial_sfs_light_military.iff")

object_tangible_ship_components_armor_shared_arm_mission_reward_neutral_kse_handcrafted = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mission_reward_neutral_kse_handcrafted.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mission_reward_neutral_kse_handcrafted_n",
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

	clientObjectCRC = 250102310,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mission_reward_neutral_kse_handcrafted, "object/tangible/ship/components/armor/shared_arm_mission_reward_neutral_kse_handcrafted.iff")

object_tangible_ship_components_armor_shared_arm_mission_reward_rebel_corellian_triplate = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mission_reward_rebel_corellian_triplate.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mission_reward_rebel_corellian_triplate_n",
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

	clientObjectCRC = 935409503,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mission_reward_rebel_corellian_triplate, "object/tangible/ship/components/armor/shared_arm_mission_reward_rebel_corellian_triplate.iff")

object_tangible_ship_components_armor_shared_arm_mission_reward_rebel_incom_ultralight = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_mission_reward_rebel_incom_ultralight.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_mission_reward_rebel_incom_ultralight_n",
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

	clientObjectCRC = 2559663629,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_mission_reward_rebel_incom_ultralight, "object/tangible/ship/components/armor/shared_arm_mission_reward_rebel_incom_ultralight.iff")

object_tangible_ship_components_armor_shared_arm_moncal_advanced_weave = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_moncal_advanced_weave.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_moncal_advanced_weave_n",
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

	clientObjectCRC = 109261874,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_moncal_advanced_weave, "object/tangible/ship/components/armor/shared_arm_moncal_advanced_weave.iff")

object_tangible_ship_components_armor_shared_arm_moncal_elite_weave = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_moncal_elite_weave.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_moncal_elite_weave_n",
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

	clientObjectCRC = 3758987303,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_moncal_elite_weave, "object/tangible/ship/components/armor/shared_arm_moncal_elite_weave.iff")

object_tangible_ship_components_armor_shared_arm_moncal_improved_light_weave = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_moncal_improved_light_weave.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_moncal_improved_light_weave_n",
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

	clientObjectCRC = 2065607228,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_moncal_improved_light_weave, "object/tangible/ship/components/armor/shared_arm_moncal_improved_light_weave.iff")

object_tangible_ship_components_armor_shared_arm_moncal_light_weave = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_moncal_light_weave.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_moncal_light_weave_n",
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

	clientObjectCRC = 3053787299,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_moncal_light_weave, "object/tangible/ship/components/armor/shared_arm_moncal_light_weave.iff")

object_tangible_ship_components_armor_shared_arm_moncal_supreme_weave = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_moncal_supreme_weave.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_moncal_supreme_weave_n",
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

	clientObjectCRC = 1882172430,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_moncal_supreme_weave, "object/tangible/ship/components/armor/shared_arm_moncal_supreme_weave.iff")

object_tangible_ship_components_armor_shared_arm_prototype_armor = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_prototype_armor.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_prototype",
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

	clientObjectCRC = 2845706811,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_prototype_armor, "object/tangible/ship/components/armor/shared_arm_prototype_armor.iff")

object_tangible_ship_components_armor_shared_arm_rendili_tough_plate = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_rendili_tough_plate.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_rendili_tough_plate_n",
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

	clientObjectCRC = 3837917885,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_rendili_tough_plate, "object/tangible/ship/components/armor/shared_arm_rendili_tough_plate.iff")

object_tangible_ship_components_armor_shared_arm_reward_alderaan_elite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_reward_alderaan_elite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:armor_reward",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_reward_alderaan_elite",
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

	clientObjectCRC = 558663557,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_reward_alderaan_elite, "object/tangible/ship/components/armor/shared_arm_reward_alderaan_elite.iff")

object_tangible_ship_components_armor_shared_arm_reward_baktoid_elite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_reward_baktoid_elite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:armor_reward",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_reward_baktoid_elite",
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

	clientObjectCRC = 161167635,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_reward_baktoid_elite, "object/tangible/ship/components/armor/shared_arm_reward_baktoid_elite.iff")

object_tangible_ship_components_armor_shared_arm_reward_freitek_elite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_reward_freitek_elite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:armor_reward",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_reward_freitek_elite",
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

	clientObjectCRC = 554262569,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_reward_freitek_elite, "object/tangible/ship/components/armor/shared_arm_reward_freitek_elite.iff")

object_tangible_ship_components_armor_shared_arm_reward_mandal_elite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_reward_mandal_elite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:armor_reward",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_reward_mandal_elite",
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

	clientObjectCRC = 648039775,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_reward_mandal_elite, "object/tangible/ship/components/armor/shared_arm_reward_mandal_elite.iff")

object_tangible_ship_components_armor_shared_arm_reward_subpro_elite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_reward_subpro_elite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:armor_reward",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_reward_subpro_elite",
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

	clientObjectCRC = 2577499173,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_reward_subpro_elite, "object/tangible/ship/components/armor/shared_arm_reward_subpro_elite.iff")

object_tangible_ship_components_armor_shared_arm_rss_light_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_rss_light_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_rss_light_plastisteel_n",
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

	clientObjectCRC = 3260614501,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_rss_light_plastisteel, "object/tangible/ship/components/armor/shared_arm_rss_light_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_sds_triplate_system = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_sds_triplate_system.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_sds_triplate_system_n",
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

	clientObjectCRC = 4088171955,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_sds_triplate_system, "object/tangible/ship/components/armor/shared_arm_sds_triplate_system.iff")

object_tangible_ship_components_armor_shared_arm_sfs_enhanced_standard_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_sfs_enhanced_standard_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_sfs_enhanced_standard_durasteel_n",
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

	clientObjectCRC = 3164042253,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_sfs_enhanced_standard_durasteel, "object/tangible/ship/components/armor/shared_arm_sfs_enhanced_standard_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_sfs_light_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_sfs_light_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_sfs_light_durasteel_n",
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

	clientObjectCRC = 1705716466,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_sfs_light_durasteel, "object/tangible/ship/components/armor/shared_arm_sfs_light_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_sfs_standard_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_sfs_standard_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_sfs_standard_durasteel_n",
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

	clientObjectCRC = 2872638243,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_sfs_standard_durasteel, "object/tangible/ship/components/armor/shared_arm_sfs_standard_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_slayn_tech_weave = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_slayn_tech_weave.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_slayn_tech_weave_n",
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

	clientObjectCRC = 2741880354,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_slayn_tech_weave, "object/tangible/ship/components/armor/shared_arm_slayn_tech_weave.iff")

object_tangible_ship_components_armor_shared_arm_sorosuub_advanced_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_sorosuub_advanced_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_sorosuub_advanced_plastisteel_n",
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

	clientObjectCRC = 3788237472,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_sorosuub_advanced_plastisteel, "object/tangible/ship/components/armor/shared_arm_sorosuub_advanced_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_sorosuub_elite_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_sorosuub_elite_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_sorosuub_elite_plastisteel_n",
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

	clientObjectCRC = 4256777864,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_sorosuub_elite_plastisteel, "object/tangible/ship/components/armor/shared_arm_sorosuub_elite_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_sorosuub_enhanced_advanced_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_sorosuub_enhanced_advanced_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_sorosuub_enhanced_advanced_plastisteel_n",
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

	clientObjectCRC = 1781793436,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_sorosuub_enhanced_advanced_plastisteel, "object/tangible/ship/components/armor/shared_arm_sorosuub_enhanced_advanced_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_sorosuub_heavy_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_sorosuub_heavy_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_sorosuub_heavy_plastisteel_n",
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

	clientObjectCRC = 1255073600,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_sorosuub_heavy_plastisteel, "object/tangible/ship/components/armor/shared_arm_sorosuub_heavy_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_sorosuub_improved_light_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_sorosuub_improved_light_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_sorosuub_improved_light_plastisteel_n",
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

	clientObjectCRC = 3554465146,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_sorosuub_improved_light_plastisteel, "object/tangible/ship/components/armor/shared_arm_sorosuub_improved_light_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_sorosuub_intemediate_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_sorosuub_intemediate_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_sorosuub_intemediate_plastisteel_n",
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

	clientObjectCRC = 293552888,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_sorosuub_intemediate_plastisteel, "object/tangible/ship/components/armor/shared_arm_sorosuub_intemediate_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_sorosuub_modified_elite_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_sorosuub_modified_elite_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_sorosuub_modified_elite_plastisteel_n",
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

	clientObjectCRC = 3015832844,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_sorosuub_modified_elite_plastisteel, "object/tangible/ship/components/armor/shared_arm_sorosuub_modified_elite_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_sorosuub_special_intermediate_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_sorosuub_special_intermediate_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_sorosuub_special_intermediate_durasteel_n",
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

	clientObjectCRC = 2255439223,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_sorosuub_special_intermediate_durasteel, "object/tangible/ship/components/armor/shared_arm_sorosuub_special_intermediate_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_subpro_advanced_plasisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_subpro_advanced_plasisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_subpro_advanced_plasisteel_n",
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

	clientObjectCRC = 3054433644,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_subpro_advanced_plasisteel, "object/tangible/ship/components/armor/shared_arm_subpro_advanced_plasisteel.iff")

object_tangible_ship_components_armor_shared_arm_subpro_bargain_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_subpro_bargain_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_subpro_bargain_plastisteel_n",
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

	clientObjectCRC = 762200952,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_subpro_bargain_plastisteel, "object/tangible/ship/components/armor/shared_arm_subpro_bargain_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_subpro_elite_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_subpro_elite_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_subpro_elite_plastisteel_n",
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

	clientObjectCRC = 557901816,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_subpro_elite_plastisteel, "object/tangible/ship/components/armor/shared_arm_subpro_elite_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_subpro_enhanced_supreme_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_subpro_enhanced_supreme_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_subpro_enhanced_supreme_plastisteel_n",
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

	clientObjectCRC = 1248323519,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_subpro_enhanced_supreme_plastisteel, "object/tangible/ship/components/armor/shared_arm_subpro_enhanced_supreme_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_subpro_experimental_advanced_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_subpro_experimental_advanced_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_subpro_experimental_advanced_plastisteel_n",
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

	clientObjectCRC = 2166232467,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_subpro_experimental_advanced_plastisteel, "object/tangible/ship/components/armor/shared_arm_subpro_experimental_advanced_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_subpro_heavy_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_subpro_heavy_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_subpro_heavy_plastisteel_n",
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

	clientObjectCRC = 2520204848,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_subpro_heavy_plastisteel, "object/tangible/ship/components/armor/shared_arm_subpro_heavy_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_subpro_improved_light_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_subpro_improved_light_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_subpro_improved_light_plastisteel_n",
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

	clientObjectCRC = 1038537255,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_subpro_improved_light_plastisteel, "object/tangible/ship/components/armor/shared_arm_subpro_improved_light_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_subpro_improved_standard_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_subpro_improved_standard_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_subpro_improved_standard_durasteel_n",
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

	clientObjectCRC = 1581165137,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_subpro_improved_standard_durasteel, "object/tangible/ship/components/armor/shared_arm_subpro_improved_standard_durasteel.iff")

object_tangible_ship_components_armor_shared_arm_subpro_limited_heavy_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_subpro_limited_heavy_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_subpro_limited_heavy_plastisteel_n",
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

	clientObjectCRC = 2268555312,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_subpro_limited_heavy_plastisteel, "object/tangible/ship/components/armor/shared_arm_subpro_limited_heavy_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_subpro_special_elite_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_subpro_special_elite_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_subpro_special_elite_plastisteel_n",
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

	clientObjectCRC = 4116799240,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_subpro_special_elite_plastisteel, "object/tangible/ship/components/armor/shared_arm_subpro_special_elite_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_subpro_standard_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_subpro_standard_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_subpro_standard_plastisteel_n",
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

	clientObjectCRC = 601305947,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_subpro_standard_plastisteel, "object/tangible/ship/components/armor/shared_arm_subpro_standard_plastisteel.iff")

object_tangible_ship_components_armor_shared_arm_subpro_supreme_plastisteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_arm_subpro_supreme_plastisteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:arm_subpro_supreme_plastisteel_n",
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

	clientObjectCRC = 142850797,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_arm_subpro_supreme_plastisteel, "object/tangible/ship/components/armor/shared_arm_subpro_supreme_plastisteel.iff")

object_tangible_ship_components_armor_shared_armor_alderaan_royal_plate = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_alderaan_royal_plate.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_alderaan_royal_plate_n",
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

	clientObjectCRC = 3192065844,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_alderaan_royal_plate, "object/tangible/ship/components/armor/shared_armor_alderaan_royal_plate.iff")

object_tangible_ship_components_armor_shared_armor_alderaan_royal_weave = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_alderaan_royal_weave.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_alderaan_royal_weave_n",
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

	clientObjectCRC = 3502209132,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_alderaan_royal_weave, "object/tangible/ship/components/armor/shared_armor_alderaan_royal_weave.iff")

object_tangible_ship_components_armor_shared_armor_baktoid_mtt_prototype = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_baktoid_mtt_prototype.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_baktoid_mtt_prototype_n",
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

	clientObjectCRC = 2941453089,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_baktoid_mtt_prototype, "object/tangible/ship/components/armor/shared_armor_baktoid_mtt_prototype.iff")

object_tangible_ship_components_armor_shared_armor_baktoid_shock_armor = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_baktoid_shock_armor.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_baktoid_shock_armor_n",
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

	clientObjectCRC = 2893359892,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_baktoid_shock_armor, "object/tangible/ship/components/armor/shared_armor_baktoid_shock_armor.iff")

object_tangible_ship_components_armor_shared_armor_baktoid_spider_shell_g2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_baktoid_spider_shell_g2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_baktoid_spider_shell_g2_n",
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

	clientObjectCRC = 3860828257,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_baktoid_spider_shell_g2, "object/tangible/ship/components/armor/shared_armor_baktoid_spider_shell_g2.iff")

object_tangible_ship_components_armor_shared_armor_freitek_es4_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_freitek_es4_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_freitek_es4_durasteel_n",
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

	clientObjectCRC = 2157390663,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_freitek_es4_durasteel, "object/tangible/ship/components/armor/shared_armor_freitek_es4_durasteel.iff")

object_tangible_ship_components_armor_shared_armor_freitek_ew6_prototype = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_freitek_ew6_prototype.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_freitek_ew6_prototype_n",
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

	clientObjectCRC = 2136590551,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_freitek_ew6_prototype, "object/tangible/ship/components/armor/shared_armor_freitek_ew6_prototype.iff")

object_tangible_ship_components_armor_shared_armor_mandal_composite_j14 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_mandal_composite_j14.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_mandal_composite_j14_n",
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

	clientObjectCRC = 189197792,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_mandal_composite_j14, "object/tangible/ship/components/armor/shared_armor_mandal_composite_j14.iff")

object_tangible_ship_components_armor_shared_armor_mandal_insulated_i5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_mandal_insulated_i5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_mandal_insulated_i5_n",
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

	clientObjectCRC = 2126398315,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_mandal_insulated_i5, "object/tangible/ship/components/armor/shared_armor_mandal_insulated_i5.iff")

object_tangible_ship_components_armor_shared_armor_seinar_coated_plasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_seinar_coated_plasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_seinar_coated_plasteel_n",
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

	clientObjectCRC = 502029625,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_seinar_coated_plasteel, "object/tangible/ship/components/armor/shared_armor_seinar_coated_plasteel.iff")

object_tangible_ship_components_armor_shared_armor_seinar_enhanced_plasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_seinar_enhanced_plasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_seinar_enhanced_plasteel_n",
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

	clientObjectCRC = 1304001760,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_seinar_enhanced_plasteel, "object/tangible/ship/components/armor/shared_armor_seinar_enhanced_plasteel.iff")

object_tangible_ship_components_armor_shared_armor_subpro_corrugated_durasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_subpro_corrugated_durasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_subpro_corrugated_durasteel_n",
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

	clientObjectCRC = 2835323687,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_subpro_corrugated_durasteel, "object/tangible/ship/components/armor/shared_armor_subpro_corrugated_durasteel.iff")

object_tangible_ship_components_armor_shared_armor_subpro_light_plasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_subpro_light_plasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_subpro_light_plasteel_n",
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

	clientObjectCRC = 3103851668,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_subpro_light_plasteel, "object/tangible/ship/components/armor/shared_armor_subpro_light_plasteel.iff")

object_tangible_ship_components_armor_shared_armor_subpro_reinforced_plasteel = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_subpro_reinforced_plasteel.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_subpro_reinforced_plasteel_n",
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

	clientObjectCRC = 4267599025,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_subpro_reinforced_plasteel, "object/tangible/ship/components/armor/shared_armor_subpro_reinforced_plasteel.iff")

object_tangible_ship_components_armor_shared_armor_test = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_test.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/armor_bone_s01_chest_plate_f.sat",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@armor_test:base",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@armor_test:base",
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

	clientObjectCRC = 1291680085,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_test, "object/tangible/ship/components/armor/shared_armor_test.iff")

object_tangible_ship_components_armor_shared_armor_tiefighter_basic = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_tiefighter_basic.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_tiefighter_basic_n",
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

	clientObjectCRC = 2493559431,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_tiefighter_basic, "object/tangible/ship/components/armor/shared_armor_tiefighter_basic.iff")

object_tangible_ship_components_armor_shared_armor_trilon_custom = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_trilon_custom.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_trilon_custom_n",
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

	clientObjectCRC = 1331552040,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_trilon_custom, "object/tangible/ship/components/armor/shared_armor_trilon_custom.iff")

object_tangible_ship_components_armor_shared_armor_trilon_unknown = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_trilon_unknown.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_trilon_unknown_n",
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

	clientObjectCRC = 2483784578,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_trilon_unknown, "object/tangible/ship/components/armor/shared_armor_trilon_unknown.iff")

object_tangible_ship_components_armor_shared_armor_z95_basic = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/armor/shared_armor_z95_basic.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_armor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741828,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_armor_d",

	gameObjectType = 1073741828,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:armor_z95_basic_n",
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

	clientObjectCRC = 710519304,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_armor_shared_armor_z95_basic, "object/tangible/ship/components/armor/shared_armor_z95_basic.iff")
