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


object_draft_schematic_munition_component_shared_ammo_projectile = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/munition/component/shared_ammo_projectile.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_datapad.iff",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2049,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 2049,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "string_id_table",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4036740128,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/munition/shared_base_munition.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_munition_component_shared_ammo_projectile, "object/draft_schematic/munition/component/shared_ammo_projectile.iff")

object_draft_schematic_munition_component_shared_ammo_projectile_entanglement = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/munition/component/shared_ammo_projectile_entanglement.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_datapad.iff",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2049,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 2049,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "string_id_table",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 443220500,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/munition/shared_base_munition.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_munition_component_shared_ammo_projectile_entanglement, "object/draft_schematic/munition/component/shared_ammo_projectile_entanglement.iff")

object_draft_schematic_munition_component_shared_base_munition_enhancer = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/munition/component/shared_base_munition_enhancer.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_datapad.iff",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2049,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 2049,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "string_id_table",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3506113789,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_munition_component_shared_base_munition_enhancer, "object/draft_schematic/munition/component/shared_base_munition_enhancer.iff")

object_draft_schematic_munition_component_shared_enhanced_charge_composition = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/munition/component/shared_enhanced_charge_composition.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_datapad.iff",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2049,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 2049,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "string_id_table",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3153150043,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/munition/shared_base_munition.iff", "object/draft_schematic/munition/shared_base_munition_enhancer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_munition_component_shared_enhanced_charge_composition, "object/draft_schematic/munition/component/shared_enhanced_charge_composition.iff")

object_draft_schematic_munition_component_shared_enhanced_charge_shaping = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/munition/component/shared_enhanced_charge_shaping.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_datapad.iff",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2049,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 2049,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "string_id_table",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3158528693,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/munition/shared_base_munition.iff", "object/draft_schematic/munition/shared_base_munition_enhancer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_munition_component_shared_enhanced_charge_shaping, "object/draft_schematic/munition/component/shared_enhanced_charge_shaping.iff")

object_draft_schematic_munition_component_shared_enhanced_destructive_pulse_channeling = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/munition/component/shared_enhanced_destructive_pulse_channeling.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_datapad.iff",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2049,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 2049,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "string_id_table",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2401022295,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/munition/shared_base_munition.iff", "object/draft_schematic/munition/shared_base_munition_enhancer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_munition_component_shared_enhanced_destructive_pulse_channeling, "object/draft_schematic/munition/component/shared_enhanced_destructive_pulse_channeling.iff")

object_draft_schematic_munition_component_shared_enhanced_fragmentation_sleeve = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/munition/component/shared_enhanced_fragmentation_sleeve.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_datapad.iff",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2049,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 2049,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "string_id_table",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3256653222,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/munition/shared_base_munition.iff", "object/draft_schematic/munition/shared_base_munition_enhancer.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_munition_component_shared_enhanced_fragmentation_sleeve, "object/draft_schematic/munition/component/shared_enhanced_fragmentation_sleeve.iff")

object_draft_schematic_munition_component_shared_warhead_chemical = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/munition/component/shared_warhead_chemical.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_datapad.iff",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2049,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 2049,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "string_id_table",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1156003088,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/munition/shared_base_munition.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_munition_component_shared_warhead_chemical, "object/draft_schematic/munition/component/shared_warhead_chemical.iff")

object_draft_schematic_munition_component_shared_warhead_fusing_mechanism = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/munition/component/shared_warhead_fusing_mechanism.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_datapad.iff",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2049,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 2049,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "string_id_table",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 3955180920,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/munition/shared_base_munition.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_munition_component_shared_warhead_fusing_mechanism, "object/draft_schematic/munition/component/shared_warhead_fusing_mechanism.iff")

object_draft_schematic_munition_component_shared_warhead_heavy = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/munition/component/shared_warhead_heavy.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_datapad.iff",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2049,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 2049,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "string_id_table",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 2232358950,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/munition/shared_base_munition.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_munition_component_shared_warhead_heavy, "object/draft_schematic/munition/component/shared_warhead_heavy.iff")

object_draft_schematic_munition_component_shared_warhead_light = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/munition/component/shared_warhead_light.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_datapad.iff",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2049,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 2049,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "string_id_table",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 1146561784,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/munition/shared_base_munition.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_munition_component_shared_warhead_light, "object/draft_schematic/munition/component/shared_warhead_light.iff")

object_draft_schematic_munition_component_shared_warhead_medium = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/munition/component/shared_warhead_medium.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_datapad.iff",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2049,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 2049,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "string_id_table",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 536805307,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/munition/shared_base_munition.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_munition_component_shared_warhead_medium, "object/draft_schematic/munition/component/shared_warhead_medium.iff")

object_draft_schematic_munition_component_shared_warhead_stabilizer = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/munition/component/shared_warhead_stabilizer.iff"
	--Data below here is deprecated and loaded from the tres, keeping for easy lookups
--[[
	appearanceFilename = "",
	arrangementDescriptorFilename = "abstract/slot/arrangement/arrangement_datapad.iff",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2049,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 0,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 2049,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "string_id_table",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 0,

	totalCellNumber = 0,

	clientObjectCRC = 4065626322,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/munition/shared_base_munition.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_munition_component_shared_warhead_stabilizer, "object/draft_schematic/munition/component/shared_warhead_stabilizer.iff")
