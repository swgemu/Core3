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


object_draft_schematic_instrument_shared_instrument_bandfill = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/instrument/shared_instrument_bandfill.iff"
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

	clientObjectCRC = 1069929316,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/instrument/shared_instrument_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_instrument_shared_instrument_bandfill, "object/draft_schematic/instrument/shared_instrument_bandfill.iff")

object_draft_schematic_instrument_shared_instrument_base = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/instrument/shared_instrument_base.iff"
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

	clientObjectCRC = 3133647251,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_instrument_shared_instrument_base, "object/draft_schematic/instrument/shared_instrument_base.iff")

object_draft_schematic_instrument_shared_instrument_drums = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/instrument/shared_instrument_drums.iff"
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

	clientObjectCRC = 592945841,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/instrument/shared_instrument_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_instrument_shared_instrument_drums, "object/draft_schematic/instrument/shared_instrument_drums.iff")

object_draft_schematic_instrument_shared_instrument_fanfar = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/instrument/shared_instrument_fanfar.iff"
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

	clientObjectCRC = 1598981907,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/instrument/shared_instrument_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_instrument_shared_instrument_fanfar, "object/draft_schematic/instrument/shared_instrument_fanfar.iff")

object_draft_schematic_instrument_shared_instrument_fizz = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/instrument/shared_instrument_fizz.iff"
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

	clientObjectCRC = 1476982860,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/instrument/shared_instrument_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_instrument_shared_instrument_fizz, "object/draft_schematic/instrument/shared_instrument_fizz.iff")

object_draft_schematic_instrument_shared_instrument_flute_droopy = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/instrument/shared_instrument_flute_droopy.iff"
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

	clientObjectCRC = 3913461118,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/instrument/shared_instrument_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_instrument_shared_instrument_flute_droopy, "object/draft_schematic/instrument/shared_instrument_flute_droopy.iff")

object_draft_schematic_instrument_shared_instrument_kloo_horn = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/instrument/shared_instrument_kloo_horn.iff"
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

	clientObjectCRC = 4207775926,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/instrument/shared_instrument_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_instrument_shared_instrument_kloo_horn, "object/draft_schematic/instrument/shared_instrument_kloo_horn.iff")

object_draft_schematic_instrument_shared_instrument_mandoviol = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/instrument/shared_instrument_mandoviol.iff"
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

	clientObjectCRC = 1835965889,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/instrument/shared_instrument_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_instrument_shared_instrument_mandoviol, "object/draft_schematic/instrument/shared_instrument_mandoviol.iff")

object_draft_schematic_instrument_shared_instrument_nalargon = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/instrument/shared_instrument_nalargon.iff"
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

	clientObjectCRC = 2180987107,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/instrument/shared_instrument_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_instrument_shared_instrument_nalargon, "object/draft_schematic/instrument/shared_instrument_nalargon.iff")

object_draft_schematic_instrument_shared_instrument_omni_box = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/instrument/shared_instrument_omni_box.iff"
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

	clientObjectCRC = 3365239168,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/instrument/shared_instrument_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_instrument_shared_instrument_omni_box, "object/draft_schematic/instrument/shared_instrument_omni_box.iff")

object_draft_schematic_instrument_shared_instrument_organ_figrin_dan = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/instrument/shared_instrument_organ_figrin_dan.iff"
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

	clientObjectCRC = 12716542,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/instrument/shared_instrument_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_instrument_shared_instrument_organ_figrin_dan, "object/draft_schematic/instrument/shared_instrument_organ_figrin_dan.iff")

object_draft_schematic_instrument_shared_instrument_organ_max_rebo = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/instrument/shared_instrument_organ_max_rebo.iff"
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

	clientObjectCRC = 747863128,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/instrument/shared_instrument_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_instrument_shared_instrument_organ_max_rebo, "object/draft_schematic/instrument/shared_instrument_organ_max_rebo.iff")

object_draft_schematic_instrument_shared_instrument_slitherhorn = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/instrument/shared_instrument_slitherhorn.iff"
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

	clientObjectCRC = 2027141215,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/instrument/shared_instrument_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_instrument_shared_instrument_slitherhorn, "object/draft_schematic/instrument/shared_instrument_slitherhorn.iff")

object_draft_schematic_instrument_shared_instrument_traz = SharedDraftSchematicObjectTemplate:new {
	clientTemplateFileName = "object/draft_schematic/instrument/shared_instrument_traz.iff"
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

	clientObjectCRC = 1146643573,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/intangible/base/shared_base_intangible.iff", "object/draft_schematic/base/shared_base_draft_schematic.iff", "object/draft_schematic/instrument/shared_instrument_base.iff"}
]]
}

ObjectTemplates:addClientTemplate(object_draft_schematic_instrument_shared_instrument_traz, "object/draft_schematic/instrument/shared_instrument_traz.iff")
