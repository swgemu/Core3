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


object_tangible_wearables_earring_shared_earring_base = SharedTangibleObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {"earring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s01",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 901601080,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ear_either.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_earring_shared_earring_base, "object/tangible/wearables/earring/shared_earring_base.iff")

object_tangible_wearables_earring_shared_earring_s01 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/earring_s01.apt",
	arrangementDescriptors = {"earring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s01",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:earring_s01",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1313672121,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ear_either.iff", "object/tangible/wearables/earring/shared_earring_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_earring_shared_earring_s01, "object/tangible/wearables/earring/shared_earring_s01.iff")

object_tangible_wearables_earring_shared_earring_s02 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/earring_s02.apt",
	arrangementDescriptors = {"earring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s02",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:earring_s02",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2505745198,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ear_either.iff", "object/tangible/wearables/earring/shared_earring_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_earring_shared_earring_s02, "object/tangible/wearables/earring/shared_earring_s02.iff")

object_tangible_wearables_earring_shared_earring_s03 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/earring_s03.apt",
	arrangementDescriptors = {"earring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s03",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:earring_s03",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s03",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3696739491,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ear_either.iff", "object/tangible/wearables/earring/shared_earring_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_earring_shared_earring_s03, "object/tangible/wearables/earring/shared_earring_s03.iff")

object_tangible_wearables_earring_shared_earring_s04 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/earring_s04.apt",
	arrangementDescriptors = {"earring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s04",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:earring_s04",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s04",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 666169271,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ear_either.iff", "object/tangible/wearables/earring/shared_earring_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_earring_shared_earring_s04, "object/tangible/wearables/earring/shared_earring_s04.iff")

object_tangible_wearables_earring_shared_earring_s05 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/earring_s05.apt",
	arrangementDescriptors = {"earring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s05",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:earring_s05",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s05",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1857652794,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ear_either.iff", "object/tangible/wearables/earring/shared_earring_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_earring_shared_earring_s05, "object/tangible/wearables/earring/shared_earring_s05.iff")

object_tangible_wearables_earring_shared_earring_s06 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/earring_s06.apt",
	arrangementDescriptors = {"earring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s06",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:earring_s06",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s06",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3048087725,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ear_either.iff", "object/tangible/wearables/earring/shared_earring_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_earring_shared_earring_s06, "object/tangible/wearables/earring/shared_earring_s06.iff")

object_tangible_wearables_earring_shared_earring_s07 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/earring_s07.apt",
	arrangementDescriptors = {"earring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s07",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:earring_s07",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s07",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4238559008,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ear_either.iff", "object/tangible/wearables/earring/shared_earring_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_earring_shared_earring_s07, "object/tangible/wearables/earring/shared_earring_s07.iff")

object_tangible_wearables_earring_shared_earring_s08 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/earring_s08.apt",
	arrangementDescriptors = {"earring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s08",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:earring_s08",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s08",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1185508146,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ear_either.iff", "object/tangible/wearables/earring/shared_earring_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_earring_shared_earring_s08, "object/tangible/wearables/earring/shared_earring_s08.iff")

object_tangible_wearables_earring_shared_earring_s09 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/earring_s09.apt",
	arrangementDescriptors = {"earring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s09",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:earring_s09",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s09",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 262409407,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ear_either.iff", "object/tangible/wearables/earring/shared_earring_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_earring_shared_earring_s09, "object/tangible/wearables/earring/shared_earring_s09.iff")

object_tangible_wearables_earring_shared_earring_s10 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/earring_s10.apt",
	arrangementDescriptors = {"earring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s10",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:earring_s10",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s10",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 476602700,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ear_either.iff", "object/tangible/wearables/earring/shared_earring_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_earring_shared_earring_s10, "object/tangible/wearables/earring/shared_earring_s10.iff")

object_tangible_wearables_earring_shared_earring_s11 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/earring_s10.apt",
	arrangementDescriptors = {"earring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s10",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:earring_s10",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s10",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1432684225,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ear_either.iff", "object/tangible/wearables/earring/shared_earring_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_earring_shared_earring_s11, "object/tangible/wearables/earring/shared_earring_s11.iff")

object_tangible_wearables_earring_shared_earring_s12 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/earring_s12.apt",
	arrangementDescriptors = {"earring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s12",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:earring_s12",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s12",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2389880406,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ear_either.iff", "object/tangible/wearables/earring/shared_earring_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_earring_shared_earring_s12, "object/tangible/wearables/earring/shared_earring_s12.iff")

object_tangible_wearables_earring_shared_earring_s13 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/earring_s13_m.apt",
	arrangementDescriptors = {"earring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s13",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:earring_s13",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s13",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3347040731,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ear_either.iff", "object/tangible/wearables/earring/shared_earring_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_earring_shared_earring_s13, "object/tangible/wearables/earring/shared_earring_s13.iff")

object_tangible_wearables_earring_shared_earring_s14 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/earring_s14_m.apt",
	arrangementDescriptors = {"earring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s14",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:earring_s14",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s14",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1016914639,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ear_either.iff", "object/tangible/wearables/earring/shared_earring_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_earring_shared_earring_s14, "object/tangible/wearables/earring/shared_earring_s14.iff")

object_tangible_wearables_earring_shared_earring_s15 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/earring_s15_m.apt",
	arrangementDescriptors = {"earring_l"},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 2097156,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@wearables_detail:earring_s15",

	gameObjectType = 2097156,

	locationReservationRadius = 0,
	lookAtText = "@wearables_lookat:earring_s15",

	noBuildRadius = 0,

	objectName = "@wearables_name:earring_s15",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"crafted_components"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1972471106,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/wearables/base/shared_wearables_base.iff", "object/tangible/wearables/base/shared_base_ear_either.iff", "object/tangible/wearables/earring/shared_earring_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_wearables_earring_shared_earring_s15, "object/tangible/wearables/earring/shared_earring_s15.iff")
