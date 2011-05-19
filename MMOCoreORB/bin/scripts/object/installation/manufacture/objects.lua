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


object_installation_manufacture_shared_clothing_factory = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ins_all_factory_clothing.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/installation/client_shared_manufacture_clothing_factory.cdf",
	clientGameObjectType = 4097,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 4097,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@installation_n:clothing_factory",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ingredient_hopper", "output_hopper", "manf_schematic", "crafted_components", "anythingNoMod1"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/installation/manufacture/shared_clothing_factory.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2037216595,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/manufacture/base/shared_manufacture_base.iff"}
}

ObjectTemplates:addClientTemplate(object_installation_manufacture_shared_clothing_factory, "object/installation/manufacture/shared_clothing_factory.iff")

object_installation_manufacture_shared_food_factory = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ins_all_factory_organic.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/installation/client_shared_manufacture_food_factory.cdf",
	clientGameObjectType = 4097,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 4097,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@installation_n:food_factory",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ingredient_hopper", "output_hopper", "manf_schematic", "crafted_components", "anythingNoMod1"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/installation/manufacture/shared_food_factory.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2484565682,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/manufacture/base/shared_manufacture_base.iff"}
}

ObjectTemplates:addClientTemplate(object_installation_manufacture_shared_food_factory, "object/installation/manufacture/shared_food_factory.iff")

object_installation_manufacture_shared_structure_factory = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ins_all_factory_machine.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/installation/client_shared_manufacture_structure_factory.cdf",
	clientGameObjectType = 4097,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 4097,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@installation_n:structure_factory",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ingredient_hopper", "output_hopper", "manf_schematic", "crafted_components", "anythingNoMod1"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/installation/manufacture/shared_structure_factory.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1556571915,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/manufacture/base/shared_manufacture_base.iff"}
}

ObjectTemplates:addClientTemplate(object_installation_manufacture_shared_structure_factory, "object/installation/manufacture/shared_structure_factory.iff")

object_installation_manufacture_shared_weapon_factory = SharedInstallationObjectTemplate:new {
	appearanceFilename = "appearance/ins_all_factory_item.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "clientdata/installation/client_shared_manufacture_weapon_factory.cdf",
	clientGameObjectType = 4097,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 4097,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "@installation_n:item_factory",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ingredient_hopper", "output_hopper", "manf_schematic", "crafted_components", "anythingNoMod1"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/installation/manufacture/shared_weapon_factory.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1304272380,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/manufacture/base/shared_manufacture_base.iff"}
}

ObjectTemplates:addClientTemplate(object_installation_manufacture_shared_weapon_factory, "object/installation/manufacture/shared_weapon_factory.iff")

object_installation_manufacture_shared_weapon_installation = SharedInstallationObjectTemplate:new {
	appearanceFilename = "",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 15,
	clientDataFile = "",
	clientGameObjectType = 4097,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@item_n:default_craftable",

	gameObjectType = 4097,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_installation",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"ingredient_hopper", "output_hopper", "manf_schematic", "crafted_components", "anythingNoMod1"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "footprint/installation/mining_ore/shared_mining_ore_harvester_style_2.sfp",
	surfaceType = 1,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 415547091,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/installation/base/shared_installation_base.iff", "object/installation/manufacture/base/shared_manufacture_base.iff"}
}

ObjectTemplates:addClientTemplate(object_installation_manufacture_shared_weapon_installation, "object/installation/manufacture/shared_weapon_installation.iff")
