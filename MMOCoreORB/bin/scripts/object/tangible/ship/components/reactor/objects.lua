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


object_tangible_ship_components_reactor_rct_tiefighter_basic = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/rct_tiefighter_basic.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:rct_tiefighter_basic_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_tiefighter_basic_n",
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

	clientObjectCRC = 1363026125,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_rct_tiefighter_basic, "object/tangible/ship/components/reactor/rct_tiefighter_basic.iff")

object_tangible_ship_components_reactor_rct_z95_basic = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/rct_z95_basic.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:rct_z95_basic_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_z95_basic_n",
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

	clientObjectCRC = 3484082121,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_rct_z95_basic, "object/tangible/ship/components/reactor/rct_z95_basic.iff")

object_tangible_ship_components_reactor_shared_rct_armek_phase_grinder = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_armek_phase_grinder.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_armek_phase_grinder_n",
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

	clientObjectCRC = 1838799948,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_armek_phase_grinder, "object/tangible/ship/components/reactor/shared_rct_armek_phase_grinder.iff")

object_tangible_ship_components_reactor_shared_rct_armek_super_collider = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_armek_super_collider.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_armek_super_collider_n",
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

	clientObjectCRC = 655443437,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_armek_super_collider, "object/tangible/ship/components/reactor/shared_rct_armek_super_collider.iff")

object_tangible_ship_components_reactor_shared_rct_armek_ultra_collider = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_armek_ultra_collider.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_armek_ultra_collider_n",
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

	clientObjectCRC = 479861884,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_armek_ultra_collider, "object/tangible/ship/components/reactor/shared_rct_armek_ultra_collider.iff")

object_tangible_ship_components_reactor_shared_rct_corellian_modified_bt3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_corellian_modified_bt3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_corellian_modified_bt3_n",
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

	clientObjectCRC = 2144194829,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_corellian_modified_bt3, "object/tangible/ship/components/reactor/shared_rct_corellian_modified_bt3.iff")

object_tangible_ship_components_reactor_shared_rct_corellian_modified_bt5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_corellian_modified_bt5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_corellian_modified_bt5_n",
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

	clientObjectCRC = 3441663380,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_corellian_modified_bt5, "object/tangible/ship/components/reactor/shared_rct_corellian_modified_bt5.iff")

object_tangible_ship_components_reactor_shared_rct_cygnus_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_cygnus_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_cygnus_advanced_n",
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

	clientObjectCRC = 4106488287,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_cygnus_advanced, "object/tangible/ship/components/reactor/shared_rct_cygnus_advanced.iff")

object_tangible_ship_components_reactor_shared_rct_cygnus_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_cygnus_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_cygnus_mk1_n",
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

	clientObjectCRC = 2061868907,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_cygnus_mk1, "object/tangible/ship/components/reactor/shared_rct_cygnus_mk1.iff")

object_tangible_ship_components_reactor_shared_rct_cygnus_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_cygnus_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_cygnus_mk2_n",
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

	clientObjectCRC = 2717005820,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_cygnus_mk2, "object/tangible/ship/components/reactor/shared_rct_cygnus_mk2.iff")

object_tangible_ship_components_reactor_shared_rct_cygnus_supercharged_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_cygnus_supercharged_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_cygnus_supercharged_mk2_n",
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

	clientObjectCRC = 2482451537,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_cygnus_supercharged_mk2, "object/tangible/ship/components/reactor/shared_rct_cygnus_supercharged_mk2.iff")

object_tangible_ship_components_reactor_shared_rct_cygnus_tuned_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_cygnus_tuned_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_cygnus_tuned_mk1_n",
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

	clientObjectCRC = 2632377171,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_cygnus_tuned_mk1, "object/tangible/ship/components/reactor/shared_rct_cygnus_tuned_mk1.iff")

object_tangible_ship_components_reactor_shared_rct_freitek_improved_powerhouse_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_freitek_improved_powerhouse_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_freitek_improved_powerhouse_mk1_n",
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

	clientObjectCRC = 274444164,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_freitek_improved_powerhouse_mk1, "object/tangible/ship/components/reactor/shared_rct_freitek_improved_powerhouse_mk1.iff")

object_tangible_ship_components_reactor_shared_rct_freitek_level1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_freitek_level1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_freitek_level1_n",
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

	clientObjectCRC = 2089644371,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_freitek_level1, "object/tangible/ship/components/reactor/shared_rct_freitek_level1.iff")

object_tangible_ship_components_reactor_shared_rct_freitek_performance_level1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_freitek_performance_level1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_freitek_performance_level1_n",
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

	clientObjectCRC = 3762511133,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_freitek_performance_level1, "object/tangible/ship/components/reactor/shared_rct_freitek_performance_level1.iff")

object_tangible_ship_components_reactor_shared_rct_freitek_powerhouse_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_freitek_powerhouse_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_freitek_powerhouse_mk1_n",
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

	clientObjectCRC = 1756278622,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_freitek_powerhouse_mk1, "object/tangible/ship/components/reactor/shared_rct_freitek_powerhouse_mk1.iff")

object_tangible_ship_components_reactor_shared_rct_freitek_powerhouse_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_freitek_powerhouse_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_freitek_powerhouse_mk2_n",
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

	clientObjectCRC = 3015247817,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_freitek_powerhouse_mk2, "object/tangible/ship/components/reactor/shared_rct_freitek_powerhouse_mk2.iff")

object_tangible_ship_components_reactor_shared_rct_freitek_powerhouse_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_freitek_powerhouse_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_freitek_powerhouse_mk3_n",
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

	clientObjectCRC = 4206125124,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_freitek_powerhouse_mk3, "object/tangible/ship/components/reactor/shared_rct_freitek_powerhouse_mk3.iff")

object_tangible_ship_components_reactor_shared_rct_generic = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_generic.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:rct_generic",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_generic",
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

	clientObjectCRC = 393073933,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_generic, "object/tangible/ship/components/reactor/shared_rct_generic.iff")

object_tangible_ship_components_reactor_shared_rct_incom_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_incom_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_incom_advanced_n",
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

	clientObjectCRC = 469546362,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_incom_advanced, "object/tangible/ship/components/reactor/shared_rct_incom_advanced.iff")

object_tangible_ship_components_reactor_shared_rct_incom_custom_mark2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_incom_custom_mark2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_incom_custom_mark2_n",
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

	clientObjectCRC = 273987032,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_incom_custom_mark2, "object/tangible/ship/components/reactor/shared_rct_incom_custom_mark2.iff")

object_tangible_ship_components_reactor_shared_rct_incom_elite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_incom_elite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_incom_elite_n",
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

	clientObjectCRC = 1003263168,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_incom_elite, "object/tangible/ship/components/reactor/shared_rct_incom_elite.iff")

object_tangible_ship_components_reactor_shared_rct_incom_improved_mark1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_incom_improved_mark1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_incom_improved_mark1_n",
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

	clientObjectCRC = 3090093197,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_incom_improved_mark1, "object/tangible/ship/components/reactor/shared_rct_incom_improved_mark1.iff")

object_tangible_ship_components_reactor_shared_rct_incom_mark1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_incom_mark1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_incom_mark1_n",
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

	clientObjectCRC = 2674049481,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_incom_mark1, "object/tangible/ship/components/reactor/shared_rct_incom_mark1.iff")

object_tangible_ship_components_reactor_shared_rct_incom_mark2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_incom_mark2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_incom_mark2_n",
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

	clientObjectCRC = 1148545374,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_incom_mark2, "object/tangible/ship/components/reactor/shared_rct_incom_mark2.iff")

object_tangible_ship_components_reactor_shared_rct_incom_mark3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_incom_mark3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_incom_mark3_n",
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

	clientObjectCRC = 225971923,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_incom_mark3, "object/tangible/ship/components/reactor/shared_rct_incom_mark3.iff")

object_tangible_ship_components_reactor_shared_rct_incom_mark4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_incom_mark4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_incom_mark4_n",
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

	clientObjectCRC = 4137362887,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_incom_mark4, "object/tangible/ship/components/reactor/shared_rct_incom_mark4.iff")

object_tangible_ship_components_reactor_shared_rct_incom_mark5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_incom_mark5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_incom_mark5_n",
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

	clientObjectCRC = 3214295626,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_incom_mark5, "object/tangible/ship/components/reactor/shared_rct_incom_mark5.iff")

object_tangible_ship_components_reactor_shared_rct_kessel_imperial_kdy_powermaster = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_kessel_imperial_kdy_powermaster.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_kessel_imperial_kdy_powermaster_n",
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

	clientObjectCRC = 3711183726,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_kessel_imperial_kdy_powermaster, "object/tangible/ship/components/reactor/shared_rct_kessel_imperial_kdy_powermaster.iff")

object_tangible_ship_components_reactor_shared_rct_kessel_imperial_sds_secret_ops = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_kessel_imperial_sds_secret_ops.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_kessel_imperial_sds_secret_ops_n",
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

	clientObjectCRC = 3454365984,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_kessel_imperial_sds_secret_ops, "object/tangible/ship/components/reactor/shared_rct_kessel_imperial_sds_secret_ops.iff")

object_tangible_ship_components_reactor_shared_rct_kessel_imperial_sfs_special_forces = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_kessel_imperial_sfs_special_forces.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_kessel_imperial_sfs_special_forces_n",
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

	clientObjectCRC = 159411222,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_kessel_imperial_sfs_special_forces, "object/tangible/ship/components/reactor/shared_rct_kessel_imperial_sfs_special_forces.iff")

object_tangible_ship_components_reactor_shared_rct_kessel_rebel_incom_overdriven_elite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_kessel_rebel_incom_overdriven_elite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_kessel_rebel_incom_overdriven_elite_n",
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

	clientObjectCRC = 3518404345,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_kessel_rebel_incom_overdriven_elite, "object/tangible/ship/components/reactor/shared_rct_kessel_rebel_incom_overdriven_elite.iff")

object_tangible_ship_components_reactor_shared_rct_kessel_rebel_mandal_modified_gorax = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_kessel_rebel_mandal_modified_gorax.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_kessel_rebel_mandal_modified_gorax_n",
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

	clientObjectCRC = 110330195,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_kessel_rebel_mandal_modified_gorax, "object/tangible/ship/components/reactor/shared_rct_kessel_rebel_mandal_modified_gorax.iff")

object_tangible_ship_components_reactor_shared_rct_kessel_rebel_slayn_high_output_experimental = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_kessel_rebel_slayn_high_output_experimental.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_kessel_rebel_slayn_high_output_experimental_n",
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

	clientObjectCRC = 1643853797,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_kessel_rebel_slayn_high_output_experimental, "object/tangible/ship/components/reactor/shared_rct_kessel_rebel_slayn_high_output_experimental.iff")

object_tangible_ship_components_reactor_shared_rct_koensayr_charged_supernova = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_koensayr_charged_supernova.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_koensayr_charged_supernova_n",
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

	clientObjectCRC = 1619443827,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_koensayr_charged_supernova, "object/tangible/ship/components/reactor/shared_rct_koensayr_charged_supernova.iff")

object_tangible_ship_components_reactor_shared_rct_koensayr_enhanced_supernova_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_koensayr_enhanced_supernova_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_koensayr_enhanced_supernova_mk2_n",
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

	clientObjectCRC = 4212259517,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_koensayr_enhanced_supernova_mk2, "object/tangible/ship/components/reactor/shared_rct_koensayr_enhanced_supernova_mk2.iff")

object_tangible_ship_components_reactor_shared_rct_koensayr_supernova = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_koensayr_supernova.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_koensayr_supernova_n",
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

	clientObjectCRC = 2993433692,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_koensayr_supernova, "object/tangible/ship/components/reactor/shared_rct_koensayr_supernova.iff")

object_tangible_ship_components_reactor_shared_rct_koensayr_supernova_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_koensayr_supernova_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_koensayr_supernova_advanced_n",
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

	clientObjectCRC = 4233117404,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_koensayr_supernova_advanced, "object/tangible/ship/components/reactor/shared_rct_koensayr_supernova_advanced.iff")

object_tangible_ship_components_reactor_shared_rct_koensayr_supernova_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_koensayr_supernova_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_koensayr_supernova_mk2_n",
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

	clientObjectCRC = 1605967841,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_koensayr_supernova_mk2, "object/tangible/ship/components/reactor/shared_rct_koensayr_supernova_mk2.iff")

object_tangible_ship_components_reactor_shared_rct_koensayr_supernova_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_koensayr_supernova_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_koensayr_supernova_mk3_n",
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

	clientObjectCRC = 380926060,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_koensayr_supernova_mk3, "object/tangible/ship/components/reactor/shared_rct_koensayr_supernova_mk3.iff")

object_tangible_ship_components_reactor_shared_rct_kse_custom_lx11 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_kse_custom_lx11.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_kse_custom_lx11_n",
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

	clientObjectCRC = 396907608,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_kse_custom_lx11, "object/tangible/ship/components/reactor/shared_rct_kse_custom_lx11.iff")

object_tangible_ship_components_reactor_shared_rct_kse_lx11 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_kse_lx11.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_kse_lx11_n",
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

	clientObjectCRC = 3490595180,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_kse_lx11, "object/tangible/ship/components/reactor/shared_rct_kse_lx11.iff")

object_tangible_ship_components_reactor_shared_rct_kse_lx21 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_kse_lx21.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_kse_lx21_n",
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

	clientObjectCRC = 4252391140,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_kse_lx21, "object/tangible/ship/components/reactor/shared_rct_kse_lx21.iff")

object_tangible_ship_components_reactor_shared_rct_kse_rct_x = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_kse_rct_x.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_kse_rct_x_n",
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

	clientObjectCRC = 379835158,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_kse_rct_x, "object/tangible/ship/components/reactor/shared_rct_kse_rct_x.iff")

object_tangible_ship_components_reactor_shared_rct_kse_rct_z = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_kse_rct_z.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_kse_rct_z_n",
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

	clientObjectCRC = 2226723852,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_kse_rct_z, "object/tangible/ship/components/reactor/shared_rct_kse_rct_z.iff")

object_tangible_ship_components_reactor_shared_rct_kse_supreme = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_kse_supreme.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_kse_supreme_n",
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

	clientObjectCRC = 3961940522,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_kse_supreme, "object/tangible/ship/components/reactor/shared_rct_kse_supreme.iff")

object_tangible_ship_components_reactor_shared_rct_mandal_dx_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_mandal_dx_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_mandal_dx_advanced_n",
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

	clientObjectCRC = 3433957122,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_mandal_dx_advanced, "object/tangible/ship/components/reactor/shared_rct_mandal_dx_advanced.iff")

object_tangible_ship_components_reactor_shared_rct_mandal_dxr = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_mandal_dxr.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_mandal_dxr_n",
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

	clientObjectCRC = 917671788,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_mandal_dxr, "object/tangible/ship/components/reactor/shared_rct_mandal_dxr.iff")

object_tangible_ship_components_reactor_shared_rct_mandal_dxr2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_mandal_dxr2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_mandal_dxr2_n",
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

	clientObjectCRC = 1602175062,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_mandal_dxr2, "object/tangible/ship/components/reactor/shared_rct_mandal_dxr2.iff")

object_tangible_ship_components_reactor_shared_rct_mandal_dxr3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_mandal_dxr3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_mandal_dxr3_n",
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

	clientObjectCRC = 376580059,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_mandal_dxr3, "object/tangible/ship/components/reactor/shared_rct_mandal_dxr3.iff")

object_tangible_ship_components_reactor_shared_rct_mandal_dxr4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_mandal_dxr4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_mandal_dxr4_n",
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

	clientObjectCRC = 3985706191,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_mandal_dxr4, "object/tangible/ship/components/reactor/shared_rct_mandal_dxr4.iff")

object_tangible_ship_components_reactor_shared_rct_mandal_dxr5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_mandal_dxr5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_mandal_dxr5_n",
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

	clientObjectCRC = 2761714498,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_mandal_dxr5, "object/tangible/ship/components/reactor/shared_rct_mandal_dxr5.iff")

object_tangible_ship_components_reactor_shared_rct_mandal_dxr6 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_mandal_dxr6.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_mandal_dxr6_n",
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

	clientObjectCRC = 2139866069,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_mandal_dxr6, "object/tangible/ship/components/reactor/shared_rct_mandal_dxr6.iff")

object_tangible_ship_components_reactor_shared_rct_mandalor_gorax = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_mandalor_gorax.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_mandalor_gorax_n",
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

	clientObjectCRC = 2046773021,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_mandalor_gorax, "object/tangible/ship/components/reactor/shared_rct_mandalor_gorax.iff")

object_tangible_ship_components_reactor_shared_rct_mandalor_gorax_elite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_mandalor_gorax_elite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_mandalor_gorax_elite_n",
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

	clientObjectCRC = 3008300066,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_mandalor_gorax_elite, "object/tangible/ship/components/reactor/shared_rct_mandalor_gorax_elite.iff")

object_tangible_ship_components_reactor_shared_rct_mission_reward_imperial_rss_advanced_military = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_mission_reward_imperial_rss_advanced_military.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_mission_reward_imperial_rss_advanced_military_n",
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

	clientObjectCRC = 2253318306,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_mission_reward_imperial_rss_advanced_military, "object/tangible/ship/components/reactor/shared_rct_mission_reward_imperial_rss_advanced_military.iff")

object_tangible_ship_components_reactor_shared_rct_mission_reward_imperial_sds_high_output = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_mission_reward_imperial_sds_high_output.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_mission_reward_imperial_sds_high_output_n",
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

	clientObjectCRC = 1448525431,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_mission_reward_imperial_sds_high_output, "object/tangible/ship/components/reactor/shared_rct_mission_reward_imperial_sds_high_output.iff")

object_tangible_ship_components_reactor_shared_rct_mission_reward_neutral_subpro_military = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_mission_reward_neutral_subpro_military.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_mission_reward_neutral_subpro_military_n",
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

	clientObjectCRC = 2954387594,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_mission_reward_neutral_subpro_military, "object/tangible/ship/components/reactor/shared_rct_mission_reward_neutral_subpro_military.iff")

object_tangible_ship_components_reactor_shared_rct_mission_reward_rebel_slayn_hypervortex = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_mission_reward_rebel_slayn_hypervortex.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_mission_reward_rebel_slayn_hypervortex_n",
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

	clientObjectCRC = 2609742784,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_mission_reward_rebel_slayn_hypervortex, "object/tangible/ship/components/reactor/shared_rct_mission_reward_rebel_slayn_hypervortex.iff")

object_tangible_ship_components_reactor_shared_rct_moncal_overdriver_s1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_moncal_overdriver_s1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_moncal_overdriver_s1_n",
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

	clientObjectCRC = 4111600702,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_moncal_overdriver_s1, "object/tangible/ship/components/reactor/shared_rct_moncal_overdriver_s1.iff")

object_tangible_ship_components_reactor_shared_rct_moncal_overdriver_s2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_moncal_overdriver_s2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_moncal_overdriver_s2_n",
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

	clientObjectCRC = 772121769,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_moncal_overdriver_s2, "object/tangible/ship/components/reactor/shared_rct_moncal_overdriver_s2.iff")

object_tangible_ship_components_reactor_shared_rct_prototype_reactor = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_prototype_reactor.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_prototype",
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

	clientObjectCRC = 2835039376,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_prototype_reactor, "object/tangible/ship/components/reactor/shared_rct_prototype_reactor.iff")

object_tangible_ship_components_reactor_shared_rct_rendili_type5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_rendili_type5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_rendili_type5_n",
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

	clientObjectCRC = 2057207911,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_rendili_type5, "object/tangible/ship/components/reactor/shared_rct_rendili_type5.iff")

object_tangible_ship_components_reactor_shared_rct_rendili_type7 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_rendili_type7.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_rendili_type7_n",
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

	clientObjectCRC = 3900985213,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_rendili_type7, "object/tangible/ship/components/reactor/shared_rct_rendili_type7.iff")

object_tangible_ship_components_reactor_shared_rct_rendili_type_x_elite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_rendili_type_x_elite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_rendili_type_x_elite_n",
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

	clientObjectCRC = 1521298929,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_rendili_type_x_elite, "object/tangible/ship/components/reactor/shared_rct_rendili_type_x_elite.iff")

object_tangible_ship_components_reactor_shared_rct_reward_armek_elite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_reward_armek_elite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:rct_reward",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_reward_armek_elite",
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

	clientObjectCRC = 4229165572,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_reward_armek_elite, "object/tangible/ship/components/reactor/shared_rct_reward_armek_elite.iff")

object_tangible_ship_components_reactor_shared_rct_reward_incom_elite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_reward_incom_elite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:rct_reward",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_reward_incom_elite",
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

	clientObjectCRC = 1119723348,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_reward_incom_elite, "object/tangible/ship/components/reactor/shared_rct_reward_incom_elite.iff")

object_tangible_ship_components_reactor_shared_rct_reward_slayn_elite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_reward_slayn_elite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:rct_reward",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_reward_slayn_elite",
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

	clientObjectCRC = 3567473688,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_reward_slayn_elite, "object/tangible/ship/components/reactor/shared_rct_reward_slayn_elite.iff")

object_tangible_ship_components_reactor_shared_rct_reward_subpro_elite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_reward_subpro_elite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:rct_reward",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_reward_subpro_elite",
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

	clientObjectCRC = 2500440467,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_reward_subpro_elite, "object/tangible/ship/components/reactor/shared_rct_reward_subpro_elite.iff")

object_tangible_ship_components_reactor_shared_rct_reward_taim_elite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_reward_taim_elite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:rct_reward",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_reward_taim_elite",
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

	clientObjectCRC = 1252227058,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_reward_taim_elite, "object/tangible/ship/components/reactor/shared_rct_reward_taim_elite.iff")

object_tangible_ship_components_reactor_shared_rct_rss_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_rss_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_rss_advanced_n",
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

	clientObjectCRC = 1571711759,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_rss_advanced, "object/tangible/ship/components/reactor/shared_rct_rss_advanced.iff")

object_tangible_ship_components_reactor_shared_rct_rss_x12 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_rss_x12.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_rss_x12_n",
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

	clientObjectCRC = 682785613,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_rss_x12, "object/tangible/ship/components/reactor/shared_rct_rss_x12.iff")

object_tangible_ship_components_reactor_shared_rct_rss_x8 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_rss_x8.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_rss_x8_n",
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

	clientObjectCRC = 729478764,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_rss_x8, "object/tangible/ship/components/reactor/shared_rct_rss_x8.iff")

object_tangible_ship_components_reactor_shared_rct_sds_elite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_sds_elite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_sds_elite_n",
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

	clientObjectCRC = 1687773799,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_sds_elite, "object/tangible/ship/components/reactor/shared_rct_sds_elite.iff")

object_tangible_ship_components_reactor_shared_rct_sds_imperial_1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_sds_imperial_1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_sds_imperial_1_n",
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

	clientObjectCRC = 1892978886,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_sds_imperial_1, "object/tangible/ship/components/reactor/shared_rct_sds_imperial_1.iff")

object_tangible_ship_components_reactor_shared_rct_sds_special_forces_1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_sds_special_forces_1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_sds_special_forces_1_n",
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

	clientObjectCRC = 3970052034,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_sds_special_forces_1, "object/tangible/ship/components/reactor/shared_rct_sds_special_forces_1.iff")

object_tangible_ship_components_reactor_shared_rct_seinar_enhanced_level1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_seinar_enhanced_level1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_seinar_enhanced_level1_n",
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

	clientObjectCRC = 293975026,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_seinar_enhanced_level1, "object/tangible/ship/components/reactor/shared_rct_seinar_enhanced_level1.iff")

object_tangible_ship_components_reactor_shared_rct_seinar_level1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_seinar_level1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_seinar_level1_n",
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

	clientObjectCRC = 78015690,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_seinar_level1, "object/tangible/ship/components/reactor/shared_rct_seinar_level1.iff")

object_tangible_ship_components_reactor_shared_rct_seinar_level2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_seinar_level2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_seinar_level2_n",
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

	clientObjectCRC = 3752969309,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_seinar_level2, "object/tangible/ship/components/reactor/shared_rct_seinar_level2.iff")

object_tangible_ship_components_reactor_shared_rct_seinar_level3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_seinar_level3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_seinar_level3_n",
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

	clientObjectCRC = 2528945104,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_seinar_level3, "object/tangible/ship/components/reactor/shared_rct_seinar_level3.iff")

object_tangible_ship_components_reactor_shared_rct_seinar_level4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_seinar_level4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_seinar_level4_n",
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

	clientObjectCRC = 1834977476,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_seinar_level4, "object/tangible/ship/components/reactor/shared_rct_seinar_level4.iff")

object_tangible_ship_components_reactor_shared_rct_sfs_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_sfs_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_sfs_advanced_n",
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

	clientObjectCRC = 928581541,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_sfs_advanced, "object/tangible/ship/components/reactor/shared_rct_sfs_advanced.iff")

object_tangible_ship_components_reactor_shared_rct_sfs_elite = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_sfs_elite.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_sfs_elite_n",
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

	clientObjectCRC = 1802806379,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_sfs_elite, "object/tangible/ship/components/reactor/shared_rct_sfs_elite.iff")

object_tangible_ship_components_reactor_shared_rct_sfs_imperial_1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_sfs_imperial_1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_sfs_imperial_1_n",
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

	clientObjectCRC = 1601368700,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_sfs_imperial_1, "object/tangible/ship/components/reactor/shared_rct_sfs_imperial_1.iff")

object_tangible_ship_components_reactor_shared_rct_sfs_imperial_2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_sfs_imperial_2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_sfs_imperial_2_n",
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

	clientObjectCRC = 2221234923,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_sfs_imperial_2, "object/tangible/ship/components/reactor/shared_rct_sfs_imperial_2.iff")

object_tangible_ship_components_reactor_shared_rct_sfs_imperial_3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_sfs_imperial_3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_sfs_imperial_3_n",
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

	clientObjectCRC = 3446160742,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_sfs_imperial_3, "object/tangible/ship/components/reactor/shared_rct_sfs_imperial_3.iff")

object_tangible_ship_components_reactor_shared_rct_sfs_imperial_4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_sfs_imperial_4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_sfs_imperial_4_n",
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

	clientObjectCRC = 915084914,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_sfs_imperial_4, "object/tangible/ship/components/reactor/shared_rct_sfs_imperial_4.iff")

object_tangible_ship_components_reactor_shared_rct_sfs_imperial_5 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_sfs_imperial_5.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_sfs_imperial_5_n",
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

	clientObjectCRC = 2139517439,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_sfs_imperial_5, "object/tangible/ship/components/reactor/shared_rct_sfs_imperial_5.iff")

object_tangible_ship_components_reactor_shared_rct_slayn_hypertron_2k = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_slayn_hypertron_2k.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_slayn_hypertron_2k_n",
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

	clientObjectCRC = 3699990858,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_slayn_hypertron_2k, "object/tangible/ship/components/reactor/shared_rct_slayn_hypertron_2k.iff")

object_tangible_ship_components_reactor_shared_rct_slayn_hypertron_4k = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_slayn_hypertron_4k.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_levelten"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_slayn_hypertron_4k_n",
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

	clientObjectCRC = 2256096858,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_slayn_hypertron_4k, "object/tangible/ship/components/reactor/shared_rct_slayn_hypertron_4k.iff")

object_tangible_ship_components_reactor_shared_rct_slayn_vortex_mk1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_slayn_vortex_mk1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_slayn_vortex_mk1_n",
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

	clientObjectCRC = 1273339609,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_slayn_vortex_mk1, "object/tangible/ship/components/reactor/shared_rct_slayn_vortex_mk1.iff")

object_tangible_ship_components_reactor_shared_rct_slayn_vortex_mk2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_slayn_vortex_mk2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_slayn_vortex_mk2_n",
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

	clientObjectCRC = 2431792718,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_slayn_vortex_mk2, "object/tangible/ship/components/reactor/shared_rct_slayn_vortex_mk2.iff")

object_tangible_ship_components_reactor_shared_rct_slayn_vortex_mk3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_slayn_vortex_mk3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_slayn_vortex_mk3_n",
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

	clientObjectCRC = 3657388483,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_slayn_vortex_mk3, "object/tangible/ship/components/reactor/shared_rct_slayn_vortex_mk3.iff")

object_tangible_ship_components_reactor_shared_rct_slayn_vortex_mk4 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_slayn_vortex_mk4.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_slayn_vortex_mk4_n",
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

	clientObjectCRC = 572291799,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_slayn_vortex_mk4, "object/tangible/ship/components/reactor/shared_rct_slayn_vortex_mk4.iff")

object_tangible_ship_components_reactor_shared_rct_sorosuub_fusion_reactor_1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_sorosuub_fusion_reactor_1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level3"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_sorosuub_fusion_reactor_1_n",
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

	clientObjectCRC = 3916801975,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_sorosuub_fusion_reactor_1, "object/tangible/ship/components/reactor/shared_rct_sorosuub_fusion_reactor_1.iff")

object_tangible_ship_components_reactor_shared_rct_sorosuub_fusion_reactor_2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_sorosuub_fusion_reactor_2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_sorosuub_fusion_reactor_2_n",
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

	clientObjectCRC = 845287200,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_sorosuub_fusion_reactor_2, "object/tangible/ship/components/reactor/shared_rct_sorosuub_fusion_reactor_2.iff")

object_tangible_ship_components_reactor_shared_rct_sorosuub_fusion_reactor_3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_sorosuub_fusion_reactor_3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level5"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_sorosuub_fusion_reactor_3_n",
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

	clientObjectCRC = 2070898861,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_sorosuub_fusion_reactor_3, "object/tangible/ship/components/reactor/shared_rct_sorosuub_fusion_reactor_3.iff")

object_tangible_ship_components_reactor_shared_rct_sorosuub_turbine_3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_sorosuub_turbine_3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_sorosuub_turbine_3_n",
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

	clientObjectCRC = 3299280915,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_sorosuub_turbine_3, "object/tangible/ship/components/reactor/shared_rct_sorosuub_turbine_3.iff")

object_tangible_ship_components_reactor_shared_rct_sorosuub_turbine_advanced = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_sorosuub_turbine_advanced.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level9"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_sorosuub_turbine_advanced_n",
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

	clientObjectCRC = 4221084087,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_sorosuub_turbine_advanced, "object/tangible/ship/components/reactor/shared_rct_sorosuub_turbine_advanced.iff")

object_tangible_ship_components_reactor_shared_rct_subpro_aurora = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_subpro_aurora.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_subpro_aurora_n",
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

	clientObjectCRC = 3380404850,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_subpro_aurora, "object/tangible/ship/components/reactor/shared_rct_subpro_aurora.iff")

object_tangible_ship_components_reactor_shared_rct_subpro_aurora_max = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_subpro_aurora_max.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_subpro_aurora_max_n",
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

	clientObjectCRC = 630252106,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_subpro_aurora_max, "object/tangible/ship/components/reactor/shared_rct_subpro_aurora_max.iff")

object_tangible_ship_components_reactor_shared_rct_subpro_dyna1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_subpro_dyna1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_subpro_dyna1_n",
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

	clientObjectCRC = 3288337981,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_subpro_dyna1, "object/tangible/ship/components/reactor/shared_rct_subpro_dyna1.iff")

object_tangible_ship_components_reactor_shared_rct_subpro_dyna2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_subpro_dyna2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_subpro_dyna2_n",
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

	clientObjectCRC = 521643690,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_subpro_dyna2, "object/tangible/ship/components/reactor/shared_rct_subpro_dyna2.iff")

object_tangible_ship_components_reactor_shared_rct_subpro_special_dyna2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_subpro_special_dyna2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_subpro_special_dyna2_n",
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

	clientObjectCRC = 3847523590,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_subpro_special_dyna2, "object/tangible/ship/components/reactor/shared_rct_subpro_special_dyna2.iff")

object_tangible_ship_components_reactor_shared_rct_taim_experimental_s1 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_taim_experimental_s1.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_taim_experimental_s1_n",
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

	clientObjectCRC = 1580359384,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_taim_experimental_s1, "object/tangible/ship/components/reactor/shared_rct_taim_experimental_s1.iff")

object_tangible_ship_components_reactor_shared_rct_taim_experimental_s2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_taim_experimental_s2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level8"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_taim_experimental_s2_n",
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

	clientObjectCRC = 2233857615,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_taim_experimental_s2, "object/tangible/ship/components/reactor/shared_rct_taim_experimental_s2.iff")

object_tangible_ship_components_reactor_shared_rct_taim_experimental_s3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_taim_experimental_s3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level7"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_taim_experimental_s3_n",
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

	clientObjectCRC = 3425210818,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_taim_experimental_s3, "object/tangible/ship/components/reactor/shared_rct_taim_experimental_s3.iff")

object_tangible_ship_components_reactor_shared_rct_tiefighter_basic = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_tiefighter_basic.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_tiefighter_basic_n",
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

	clientObjectCRC = 3319963808,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_tiefighter_basic, "object/tangible/ship/components/reactor/shared_rct_tiefighter_basic.iff")

object_tangible_ship_components_reactor_shared_rct_unknown_distressed_aluminum = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_unknown_distressed_aluminum.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_unknown_distressed_aluminum_n",
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

	clientObjectCRC = 951546180,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_unknown_distressed_aluminum, "object/tangible/ship/components/reactor/shared_rct_unknown_distressed_aluminum.iff")

object_tangible_ship_components_reactor_shared_rct_unknown_multicore = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_unknown_multicore.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_unknown_multicore_n",
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

	clientObjectCRC = 33823730,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_unknown_multicore, "object/tangible/ship/components/reactor/shared_rct_unknown_multicore.iff")

object_tangible_ship_components_reactor_shared_rct_unknown_proton_chamber = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_unknown_proton_chamber.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level6"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_unknown_proton_chamber_n",
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

	clientObjectCRC = 2573145892,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_unknown_proton_chamber, "object/tangible/ship/components/reactor/shared_rct_unknown_proton_chamber.iff")

object_tangible_ship_components_reactor_shared_rct_watto_sunray_2 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_watto_sunray_2.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level2"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_watto_sunray_2_n",
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

	clientObjectCRC = 1703778737,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_watto_sunray_2, "object/tangible/ship/components/reactor/shared_rct_watto_sunray_2.iff")

object_tangible_ship_components_reactor_shared_rct_watto_sunray_3 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_watto_sunray_3.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level4"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_watto_sunray_3_n",
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

	clientObjectCRC = 746651196,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_watto_sunray_3, "object/tangible/ship/components/reactor/shared_rct_watto_sunray_3.iff")

object_tangible_ship_components_reactor_shared_rct_z95_basic = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_rct_z95_basic.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/ship_component_reactor_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_item:generic_reactor_d",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@space/space_item:rct_z95_basic_n",
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

	clientObjectCRC = 2051660015,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_rct_z95_basic, "object/tangible/ship/components/reactor/shared_rct_z95_basic.iff")

object_tangible_ship_components_reactor_shared_reactor_test = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/ship/components/reactor/shared_reactor_test.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/cmp_xwing_cowl_neg_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {"cert_ordnance_level1"},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 1073741825,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@reactor_test:base",

	gameObjectType = 1073741825,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@reactor_test:base",
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

	clientObjectCRC = 1943796009,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/ship/components/base/shared_ship_component_base.iff", "object/tangible/ship/components/base/shared_ship_component_loot_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_ship_components_reactor_shared_reactor_test, "object/tangible/ship/components/reactor/shared_reactor_test.iff")
