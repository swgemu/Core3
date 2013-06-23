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


object_tangible_wearables_necklace_shared_bestine_quest_badge = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_bestine_quest_badge.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s08_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:bestine_quest_badge",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:bestine_quest_badge",

	noBuildRadius = 0,

	objectName = "@wearables_name:bestine_quest_badge",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3954123718,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_bestine_quest_badge, "object/tangible/wearables/necklace/shared_bestine_quest_badge.iff")

object_tangible_wearables_necklace_shared_necklace_adorned_beads = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_adorned_beads.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s08_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_adorned_beads",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_adorned_beads",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1050230351,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_adorned_beads, "object/tangible/wearables/necklace/shared_necklace_adorned_beads.iff")

object_tangible_wearables_necklace_shared_necklace_base = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_base.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_s01",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_s01",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3453591411,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_base, "object/tangible/wearables/necklace/shared_necklace_base.iff")

object_tangible_wearables_necklace_shared_necklace_blue_gadget = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_blue_gadget.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s02_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_blue_gadget",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_blue_gadget",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3584437673,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_blue_gadget, "object/tangible/wearables/necklace/shared_necklace_blue_gadget.iff")

object_tangible_wearables_necklace_shared_necklace_brass_charm = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_brass_charm.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s08_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_brass_charm",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_brass_charm",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4150202535,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_brass_charm, "object/tangible/wearables/necklace/shared_necklace_brass_charm.iff")

object_tangible_wearables_necklace_shared_necklace_bright_bauble = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_bright_bauble.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s08_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_bright_bauble",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_bright_bauble",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3040940329,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_bright_bauble, "object/tangible/wearables/necklace/shared_necklace_bright_bauble.iff")

object_tangible_wearables_necklace_shared_necklace_complex_pattern = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_complex_pattern.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s02_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_complex_pattern",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_complex_pattern",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 974368601,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_complex_pattern, "object/tangible/wearables/necklace/shared_necklace_complex_pattern.iff")

object_tangible_wearables_necklace_shared_necklace_convoluted_adornment = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_convoluted_adornment.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s02_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_convoluted_adornment",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_convoluted_adornment",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2325808611,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_convoluted_adornment, "object/tangible/wearables/necklace/shared_necklace_convoluted_adornment.iff")

object_tangible_wearables_necklace_shared_necklace_crushed_brooch = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_crushed_brooch.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s02_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_crushed_brooch",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_crushed_brooch",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1155738012,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_crushed_brooch, "object/tangible/wearables/necklace/shared_necklace_crushed_brooch.iff")

object_tangible_wearables_necklace_shared_necklace_elaborate_necklet = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_elaborate_necklet.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s02_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_elaborate_necklet",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_elaborate_necklet",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 283875663,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_elaborate_necklet, "object/tangible/wearables/necklace/shared_necklace_elaborate_necklet.iff")

object_tangible_wearables_necklace_shared_necklace_flashy_choker = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_flashy_choker.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s07_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_flashy_choker",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_flashy_choker",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2530110745,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_flashy_choker, "object/tangible/wearables/necklace/shared_necklace_flashy_choker.iff")

object_tangible_wearables_necklace_shared_necklace_hologram_locket = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_hologram_locket.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s07_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_hologram_locket",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_hologram_locket",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3024190115,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_hologram_locket, "object/tangible/wearables/necklace/shared_necklace_hologram_locket.iff")

object_tangible_wearables_necklace_shared_necklace_ice_pendant = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_ice_pendant.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s08_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_ice_pendant",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_ice_pendant",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3734395119,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_ice_pendant, "object/tangible/wearables/necklace/shared_necklace_ice_pendant.iff")

object_tangible_wearables_necklace_shared_necklace_iron_brooch = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_iron_brooch.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s02_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_iron_brooch",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_iron_brooch",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4144828811,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_iron_brooch, "object/tangible/wearables/necklace/shared_necklace_iron_brooch.iff")

object_tangible_wearables_necklace_shared_necklace_iron_choker = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_iron_choker.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s02_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_iron_choker",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_iron_choker",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 840414348,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_iron_choker, "object/tangible/wearables/necklace/shared_necklace_iron_choker.iff")

object_tangible_wearables_necklace_shared_necklace_jeweled_pendant = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_jeweled_pendant.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s08_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_jeweled_pendant",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_jeweled_pendant",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 218269484,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_jeweled_pendant, "object/tangible/wearables/necklace/shared_necklace_jeweled_pendant.iff")

object_tangible_wearables_necklace_shared_necklace_knickknack = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_knickknack.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s07_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_knickknack",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_knickknack",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3512942236,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_knickknack, "object/tangible/wearables/necklace/shared_necklace_knickknack.iff")

object_tangible_wearables_necklace_shared_necklace_living_chains = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_living_chains.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s03_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_living_chains",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_living_chains",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3087789204,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_living_chains, "object/tangible/wearables/necklace/shared_necklace_living_chains.iff")

object_tangible_wearables_necklace_shared_necklace_magnificent_lavaliere = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_magnificent_lavaliere.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s07_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_magnificent_lavaliere",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_magnificent_lavaliere",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2122077046,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_magnificent_lavaliere, "object/tangible/wearables/necklace/shared_necklace_magnificent_lavaliere.iff")

object_tangible_wearables_necklace_shared_necklace_nyax = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_nyax.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s02_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_nyax",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:necklace_nyax",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_nyax",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3448479035,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_nyax, "object/tangible/wearables/necklace/shared_necklace_nyax.iff")

object_tangible_wearables_necklace_shared_necklace_opulent_cameo = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_opulent_cameo.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s07_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_opulent_cameo",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_opulent_cameo",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 118177721,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_opulent_cameo, "object/tangible/wearables/necklace/shared_necklace_opulent_cameo.iff")

object_tangible_wearables_necklace_shared_necklace_ornamental_ratchet = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_ornamental_ratchet.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s02_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_ornamental_ratchet",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_ornamental_ratchet",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2206646823,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_ornamental_ratchet, "object/tangible/wearables/necklace/shared_necklace_ornamental_ratchet.iff")

object_tangible_wearables_necklace_shared_necklace_pawl_chain = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_pawl_chain.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s07_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_pawl_chain",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_pawl_chain",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1137026386,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_pawl_chain, "object/tangible/wearables/necklace/shared_necklace_pawl_chain.iff")

object_tangible_wearables_necklace_shared_necklace_platinum_pin = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_platinum_pin.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s07_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_platinum_pin",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_platinum_pin",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2922514792,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_platinum_pin, "object/tangible/wearables/necklace/shared_necklace_platinum_pin.iff")

object_tangible_wearables_necklace_shared_necklace_reebo_charm = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_reebo_charm.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s07_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_reebo_charm",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_reebo_charm",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3826079370,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_reebo_charm, "object/tangible/wearables/necklace/shared_necklace_reebo_charm.iff")

object_tangible_wearables_necklace_shared_necklace_rosy_pearl = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_rosy_pearl.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s01_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_rosy_pearl",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_rosy_pearl",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2107115657,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_rosy_pearl, "object/tangible/wearables/necklace/shared_necklace_rosy_pearl.iff")

object_tangible_wearables_necklace_shared_necklace_rusty_beads = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_rusty_beads.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s08_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_rusty_beads",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_rusty_beads",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 509359350,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_rusty_beads, "object/tangible/wearables/necklace/shared_necklace_rusty_beads.iff")

object_tangible_wearables_necklace_shared_necklace_s01 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_s01.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s01_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_s01",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:necklace_s01",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_s01",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 705351361,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_s01, "object/tangible/wearables/necklace/shared_necklace_s01.iff")

object_tangible_wearables_necklace_shared_necklace_s02 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_s02.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s02_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_s02",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:necklace_s02",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_s02",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4045235798,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_s02, "object/tangible/wearables/necklace/shared_necklace_s02.iff")

object_tangible_wearables_necklace_shared_necklace_s03 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_s03.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s03_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_s03",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:necklace_s03",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_s03",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3088056795,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_s03, "object/tangible/wearables/necklace/shared_necklace_s03.iff")

object_tangible_wearables_necklace_shared_necklace_s04 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_s04.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s04_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_s04",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:necklace_s04",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_s04",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1140009679,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_s04, "object/tangible/wearables/necklace/shared_necklace_s04.iff")

object_tangible_wearables_necklace_shared_necklace_s05 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_s05.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s05_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_s05",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:necklace_s05",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_s05",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 184438082,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_s05, "object/tangible/wearables/necklace/shared_necklace_s05.iff")

object_tangible_wearables_necklace_shared_necklace_s06 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_s06.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s06_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_s06",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:necklace_s06",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_s06",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3521766869,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_s06, "object/tangible/wearables/necklace/shared_necklace_s06.iff")

object_tangible_wearables_necklace_shared_necklace_s07 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_s07.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s07_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_s07",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:necklace_s07",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_s07",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2565112408,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_s07, "object/tangible/wearables/necklace/shared_necklace_s07.iff")

object_tangible_wearables_necklace_shared_necklace_s08 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_s08.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s08_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_s08",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:necklace_s08",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_s08",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 586067530,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_s08, "object/tangible/wearables/necklace/shared_necklace_s08.iff")

object_tangible_wearables_necklace_shared_necklace_s09 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_s09.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s09_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_s09",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:necklace_s09",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_s09",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1810090439,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_s09, "object/tangible/wearables/necklace/shared_necklace_s09.iff")

object_tangible_wearables_necklace_shared_necklace_s09_quest = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_s09_quest.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s09_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_s09_quest",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:necklace_s09",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_s09_quest",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4204967934,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_s09_quest, "object/tangible/wearables/necklace/shared_necklace_s09_quest.iff")

object_tangible_wearables_necklace_shared_necklace_s10 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_s10.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s10_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_s10",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:necklace_s10",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_s10",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2016388148,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_s10, "object/tangible/wearables/necklace/shared_necklace_s10.iff")

object_tangible_wearables_necklace_shared_necklace_s11 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_s11.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s11_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_s11",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:necklace_s11",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_s11",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 824361913,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_s11, "object/tangible/wearables/necklace/shared_necklace_s11.iff")

object_tangible_wearables_necklace_shared_necklace_s12 = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_s12.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s12_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_s12",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:necklace_s12",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_s12",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3929369390,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_s12, "object/tangible/wearables/necklace/shared_necklace_s12.iff")

object_tangible_wearables_necklace_shared_necklace_sparkling_bijou = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_sparkling_bijou.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s07_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_sparkling_bijou",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_sparkling_bijou",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4111333468,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_sparkling_bijou, "object/tangible/wearables/necklace/shared_necklace_sparkling_bijou.iff")

object_tangible_wearables_necklace_shared_necklace_wampum = SharedTangibleObjectTemplate:new {
	clientTemplateFileName = "object/tangible/wearables/necklace/shared_necklace_wampum.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "appearance/necklace_s03_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/neck.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097155,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:necklace_wampum",

	gameObjectType = 2097155,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:necklace_wampum",
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
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3192072783,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_neck.iff", "object/tangible/wearables/necklace/shared_necklace_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_necklace_shared_necklace_wampum, "object/tangible/wearables/necklace/shared_necklace_wampum.iff")
