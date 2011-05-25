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


object_tangible_vendor_shared_vendor_droid_bartender = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/robo_bartender.sat",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 7,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 4,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:vendor_terminal",

	gameObjectType = 7,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:vendor_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:vendor_terminal",
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

	clientObjectCRC = 887599030,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/vendor/base/shared_base_vendor.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_vendor_shared_vendor_droid_bartender, "object/tangible/vendor/shared_vendor_droid_bartender.iff")

object_tangible_vendor_shared_vendor_droid_power = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eg6.sat",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 7,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 4,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:vendor_terminal",

	gameObjectType = 7,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:vendor_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:vendor_terminal",
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

	clientObjectCRC = 1459672491,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/vendor/base/shared_base_vendor.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_vendor_shared_vendor_droid_power, "object/tangible/vendor/shared_vendor_droid_power.iff")

object_tangible_vendor_shared_vendor_droid_protocol = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/protocol_droid_red.sat",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 7,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 4,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:vendor_terminal",

	gameObjectType = 7,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:vendor_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:vendor_terminal",
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

	clientObjectCRC = 844125696,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/vendor/base/shared_base_vendor.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_vendor_shared_vendor_droid_protocol, "object/tangible/vendor/shared_vendor_droid_protocol.iff")

object_tangible_vendor_shared_vendor_droid_surgical = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/droid_21b.sat",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 7,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 4,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:vendor_terminal",

	gameObjectType = 7,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:vendor_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:vendor_terminal",
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

	clientObjectCRC = 946679884,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/vendor/base/shared_base_vendor.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_vendor_shared_vendor_droid_surgical, "object/tangible/vendor/shared_vendor_droid_surgical.iff")

object_tangible_vendor_shared_vendor_droid_wed = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/wed_treadwell.sat",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 7,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 4,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:vendor_terminal",

	gameObjectType = 7,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:vendor_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:vendor_terminal",
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

	clientObjectCRC = 1745672602,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/vendor/base/shared_base_vendor.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_vendor_shared_vendor_droid_wed, "object/tangible/vendor/shared_vendor_droid_wed.iff")

object_tangible_vendor_shared_vendor_terminal_basic = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_bazaar.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 7,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 4,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:vendor_terminal_basic",

	gameObjectType = 7,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:vendor_terminal_basic",

	noBuildRadius = 0,

	objectName = "@terminal_name:vendor_terminal_basic",
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

	clientObjectCRC = 1946512190,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/vendor/base/shared_base_vendor.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_vendor_shared_vendor_terminal_basic, "object/tangible/vendor/shared_vendor_terminal_basic.iff")

object_tangible_vendor_shared_vendor_terminal_bulky = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_shipping.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 7,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 4,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:vendor_terminal",

	gameObjectType = 7,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:vendor_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:vendor_terminal",
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

	clientObjectCRC = 2831480672,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/vendor/base/shared_base_vendor.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_vendor_shared_vendor_terminal_bulky, "object/tangible/vendor/shared_vendor_terminal_bulky.iff")

object_tangible_vendor_shared_vendor_terminal_fancy = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_travel.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 7,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 4,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:vendor_terminal",

	gameObjectType = 7,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:vendor_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:vendor_terminal",
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

	clientObjectCRC = 3992259223,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/vendor/base/shared_base_vendor.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_vendor_shared_vendor_terminal_fancy, "object/tangible/vendor/shared_vendor_terminal_fancy.iff")

object_tangible_vendor_shared_vendor_terminal_slim = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_mission.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 7,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 4,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:vendor_terminal",

	gameObjectType = 7,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:vendor_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:vendor_terminal",
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

	clientObjectCRC = 3179269297,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/vendor/base/shared_base_vendor.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_vendor_shared_vendor_terminal_slim, "object/tangible/vendor/shared_vendor_terminal_slim.iff")

object_tangible_vendor_shared_vendor_terminal_small = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_bank.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 7,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 4,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:vendor_terminal",

	gameObjectType = 7,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:vendor_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:vendor_terminal",
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

	clientObjectCRC = 2513721920,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/vendor/base/shared_base_vendor.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_vendor_shared_vendor_terminal_small, "object/tangible/vendor/shared_vendor_terminal_small.iff")

object_tangible_vendor_shared_vendor_terminal_standard = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_bazaar.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 7,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 4,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:vendor_terminal",

	gameObjectType = 7,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:vendor_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:vendor_terminal",
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

	clientObjectCRC = 90585643,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/vendor/base/shared_base_vendor.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_vendor_shared_vendor_terminal_standard, "object/tangible/vendor/shared_vendor_terminal_standard.iff")
