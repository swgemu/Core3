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


object_tangible_wearables_gloves_shared_gloves_corsec = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/gloves_s02_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/gloves.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777224,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:gloves_corsec",

	gameObjectType = 16777224,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:gloves_corsec",

	noBuildRadius = 0,

	objectName = "@wearables_name:gloves_corsec",
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

	clientObjectCRC = 2451059154,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_gloves.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_gloves_shared_gloves_corsec, "object/tangible/wearables/gloves/shared_gloves_corsec.iff")

object_tangible_wearables_gloves_shared_gloves_s02 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/gloves_s02_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/gloves.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777224,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:gloves_s02",

	gameObjectType = 16777224,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:gloves_s02",

	noBuildRadius = 0,

	objectName = "@wearables_name:gloves_s02",
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

	clientObjectCRC = 1702772985,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_gloves.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_gloves_shared_gloves_s02, "object/tangible/wearables/gloves/shared_gloves_s02.iff")

object_tangible_wearables_gloves_shared_gloves_s03 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/gloves_s03_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/gloves_long.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777224,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:gloves_s03",

	gameObjectType = 16777224,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:gloves_s03",

	noBuildRadius = 0,

	objectName = "@wearables_name:gloves_s03",
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

	clientObjectCRC = 745744244,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_gloves_long.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_gloves_shared_gloves_s03, "object/tangible/wearables/gloves/shared_gloves_s03.iff")

object_tangible_wearables_gloves_shared_gloves_s06 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/gloves_s06_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/gloves.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777224,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:gloves_s06",

	gameObjectType = 16777224,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:gloves_s06",

	noBuildRadius = 0,

	objectName = "@wearables_name:gloves_s06",
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

	clientObjectCRC = 1166721914,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_gloves.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_gloves_shared_gloves_s06, "object/tangible/wearables/gloves/shared_gloves_s06.iff")

object_tangible_wearables_gloves_shared_gloves_s07 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/gloves_s07_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/gloves_long.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777224,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:gloves_s07",

	gameObjectType = 16777224,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:gloves_s07",

	noBuildRadius = 0,

	objectName = "@wearables_name:gloves_s07",
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

	clientObjectCRC = 210216183,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_gloves_long.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_gloves_shared_gloves_s07, "object/tangible/wearables/gloves/shared_gloves_s07.iff")

object_tangible_wearables_gloves_shared_gloves_s10 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/gloves_s10_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/gloves_long.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777224,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:gloves_s10",

	gameObjectType = 16777224,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:gloves_s10",

	noBuildRadius = 0,

	objectName = "@wearables_name:gloves_s10",
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

	clientObjectCRC = 3964437147,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_gloves_long.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_gloves_shared_gloves_s10, "object/tangible/wearables/gloves/shared_gloves_s10.iff")

object_tangible_wearables_gloves_shared_gloves_s11 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/gloves_s11_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/gloves_long.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777224,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:gloves_s11",

	gameObjectType = 16777224,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:gloves_s11",

	noBuildRadius = 0,

	objectName = "@wearables_name:gloves_s11",
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

	clientObjectCRC = 2772559126,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_gloves_long.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_gloves_shared_gloves_s11, "object/tangible/wearables/gloves/shared_gloves_s11.iff")

object_tangible_wearables_gloves_shared_gloves_s12 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/gloves_s12_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/gloves.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777224,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:gloves_s12",

	gameObjectType = 16777224,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:gloves_s12",

	noBuildRadius = 0,

	objectName = "@wearables_name:gloves_s12",
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

	clientObjectCRC = 2119585153,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_gloves.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_gloves_shared_gloves_s12, "object/tangible/wearables/gloves/shared_gloves_s12.iff")

object_tangible_wearables_gloves_shared_gloves_s13 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/gloves_s13_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/gloves_long.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777224,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:gloves_s13",

	gameObjectType = 16777224,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:gloves_s13",

	noBuildRadius = 0,

	objectName = "@wearables_name:gloves_s13",
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

	clientObjectCRC = 928721420,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_gloves_long.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_gloves_shared_gloves_s13, "object/tangible/wearables/gloves/shared_gloves_s13.iff")

object_tangible_wearables_gloves_shared_gloves_s14 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/gloves_s14_f.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/gloves.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777224,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:gloves_s14",

	gameObjectType = 16777224,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:gloves_s14",

	noBuildRadius = 0,

	objectName = "@wearables_name:gloves_s14",
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

	clientObjectCRC = 3434610968,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_gloves.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_gloves_shared_gloves_s14, "object/tangible/wearables/gloves/shared_gloves_s14.iff")

object_tangible_wearables_gloves_shared_gloves_tusken_raider = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/gloves_tusken_raider_m.sat",
	arrangementDescriptorFilename = "abstract/slot/arrangement/wearables/gloves.iff",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16777224,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:gloves_tusken_raider",

	gameObjectType = 16777224,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:gloves_tusken_raider",

	noBuildRadius = 0,

	objectName = "@wearables_name:gloves_tusken_raider",
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

	clientObjectCRC = 1738692931,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_gloves.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_gloves_shared_gloves_tusken_raider, "object/tangible/wearables/gloves/shared_gloves_tusken_raider.iff")
