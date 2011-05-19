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


object_tangible_terminal_shared_terminal_ballot_box = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_mun_ballot_box.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_ballot_box",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_ballot_box",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 909741262,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_ballot_box, "object/tangible/terminal/shared_terminal_ballot_box.iff")

object_tangible_terminal_shared_terminal_bank = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_bank.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/terminal/client_shared_terminal_bank.cdf",
	clientGameObjectType = 16385,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_bank",

	gameObjectType = 16385,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_bank",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_bank",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1989986645,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_bank, "object/tangible/terminal/shared_terminal_bank.iff")

object_tangible_terminal_shared_terminal_bazaar = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_bazaar.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/terminal/client_shared_terminal_bazaar.cdf",
	clientGameObjectType = 16386,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 4,
	containerVolumeLimit = -1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_bazaar",

	gameObjectType = 16386,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_bazaar",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_bazaar",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3631323563,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_bazaar, "object/tangible/terminal/shared_terminal_bazaar.iff")

object_tangible_terminal_shared_terminal_bestine_quests_01 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_free_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16384,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_bestine_01",

	gameObjectType = 16384,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_bestine_01",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_bestine_01",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 234637781,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_bestine_quests_01, "object/tangible/terminal/shared_terminal_bestine_quests_01.iff")

object_tangible_terminal_shared_terminal_bestine_quests_02 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_free_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16384,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_bestine_02",

	gameObjectType = 16384,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_bestine_02",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_bestine_02",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3605782850,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_bestine_quests_02, "object/tangible/terminal/shared_terminal_bestine_quests_02.iff")

object_tangible_terminal_shared_terminal_bestine_quests_03 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_free_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16384,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_bestine_03",

	gameObjectType = 16384,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_bestine_03",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_bestine_03",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2682685135,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_bestine_quests_03, "object/tangible/terminal/shared_terminal_bestine_quests_03.iff")

object_tangible_terminal_shared_terminal_bounty_droid = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_free_s2.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_bounty_droid",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_bounty_droid",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_bounty_droid",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4023071175,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_bounty_droid, "object/tangible/terminal/shared_terminal_bounty_droid.iff")

object_tangible_terminal_shared_terminal_character_builder = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/thm_prp_kiosk_statue.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_character_builder",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_character_builder",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1444012427,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_character_builder, "object/tangible/terminal/shared_terminal_character_builder.iff")

object_tangible_terminal_shared_terminal_city = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_imp_data_terminal_s2.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16384,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_city",

	gameObjectType = 16384,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_city",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_city",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 379393128,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_city, "object/tangible/terminal/shared_terminal_city.iff")

object_tangible_terminal_shared_terminal_city_vote = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_mun_ballot_box.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16384,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_city_vote",

	gameObjectType = 16384,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_city_vote",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1204497275,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_city_vote, "object/tangible/terminal/shared_terminal_city_vote.iff")

object_tangible_terminal_shared_terminal_cloning = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_cloning.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/terminal/client_shared_terminal_cloning.cdf",
	clientGameObjectType = 16387,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_cloning",

	gameObjectType = 16387,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_cloning",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_cloning",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3781560082,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_cloning, "object/tangible/terminal/shared_terminal_cloning.iff")

object_tangible_terminal_shared_terminal_command_console = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_tech_command_console_s01.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/terminal/client_shared_terminal_geo_bunker.cdf",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_geo_bunker",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_geo_bunker",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_geo_bunker",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 245813721,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_command_console, "object/tangible/terminal/shared_terminal_command_console.iff")

object_tangible_terminal_shared_terminal_dark_enclave_challenge = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_djt_voting.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8211,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_dark_enclave_challenge",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_dark_enclave_challenge",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1992103782,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_dark_enclave_challenge, "object/tangible/terminal/shared_terminal_dark_enclave_challenge.iff")

object_tangible_terminal_shared_terminal_dark_enclave_voting = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_ljt_voting.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8211,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_dark_enclave_voting",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_dark_enclave_voting",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2329382269,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_dark_enclave_voting, "object/tangible/terminal/shared_terminal_dark_enclave_voting.iff")

object_tangible_terminal_shared_terminal_elevator = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/thm_all_elevator_panel_updown_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16384,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_elevator",

	gameObjectType = 16384,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_elevator",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 278443635,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_elevator, "object/tangible/terminal/shared_terminal_elevator.iff")

object_tangible_terminal_shared_terminal_elevator_down = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/thm_all_elevator_panel_down_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16384,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_elevator",

	gameObjectType = 16384,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_elevator",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3298826986,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_elevator_down, "object/tangible/terminal/shared_terminal_elevator_down.iff")

object_tangible_terminal_shared_terminal_elevator_up = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/thm_all_elevator_panel_up_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16384,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_elevator",

	gameObjectType = 16384,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_elevator",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 115529514,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_elevator_up, "object/tangible/terminal/shared_terminal_elevator_up.iff")

object_tangible_terminal_shared_terminal_geo_bunker = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_wall_s3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/terminal/client_shared_terminal_geo_bunker.cdf",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_geo_bunker",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_geo_bunker",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_geo_bunker",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3878794306,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_geo_bunker, "object/tangible/terminal/shared_terminal_geo_bunker.iff")

object_tangible_terminal_shared_terminal_guild = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_imp_data_terminal_s2.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16384,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_guild",

	gameObjectType = 16384,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_guild",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_guild",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 724271921,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_guild, "object/tangible/terminal/shared_terminal_guild.iff")

object_tangible_terminal_shared_terminal_hq = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_free_s3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_name:terminal_hq",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_hq",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_hq",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 489350492,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_hq, "object/tangible/terminal/shared_terminal_hq.iff")

object_tangible_terminal_shared_terminal_hq_imperial = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_free_s3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/terminal/client_shared_terminal_mission.cdf",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_hq_imperial",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_hq_imperial",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_hq_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3161971452,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff", "object/tangible/terminal/shared_terminal_hq.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_hq_imperial, "object/tangible/terminal/shared_terminal_hq_imperial.iff")

object_tangible_terminal_shared_terminal_hq_rebel = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_free_s3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/terminal/client_shared_terminal_mission.cdf",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_hq_rebel",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_hq_rebel",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_hq_rebel",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1176471647,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff", "object/tangible/terminal/shared_terminal_hq.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_hq_rebel, "object/tangible/terminal/shared_terminal_hq_rebel.iff")

object_tangible_terminal_shared_terminal_hq_turret_control = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_imp_data_terminal_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_name:terminal_hq_turret_control",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_hq_turret_control",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_hq_turret_control",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2229698005,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_hq_turret_control, "object/tangible/terminal/shared_terminal_hq_turret_control.iff")

object_tangible_terminal_shared_terminal_imagedesign = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_image_design.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8211,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_imagedesign",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_imagedesign",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_imagedesign",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2511005752,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_imagedesign, "object/tangible/terminal/shared_terminal_imagedesign.iff")

object_tangible_terminal_shared_terminal_insurance = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_shipping.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/terminal/client_shared_terminal_insurance.cdf",
	clientGameObjectType = 16388,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_insurance",

	gameObjectType = 16388,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_insurance",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_insurance",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1029213671,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_insurance, "object/tangible/terminal/shared_terminal_insurance.iff")

object_tangible_terminal_shared_terminal_jukebox = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_free_s2.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@event_perk:jukebox_terminal_description",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@event_perk:jukebox_terminal_name",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 249891408,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_jukebox, "object/tangible/terminal/shared_terminal_jukebox.iff")

object_tangible_terminal_shared_terminal_light_enclave_challenge = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_ljt_voting.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8211,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_light_enclave_challenge",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_light_enclave_challenge",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2945424908,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_light_enclave_challenge, "object/tangible/terminal/shared_terminal_light_enclave_challenge.iff")

object_tangible_terminal_shared_terminal_light_enclave_voting = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_ljt_voting.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8211,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_light_enclave_voting",

	gameObjectType = 8211,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_light_enclave_voting",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1384984494,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_light_enclave_voting, "object/tangible/terminal/shared_terminal_light_enclave_voting.iff")

object_tangible_terminal_shared_terminal_mission = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_mission.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/terminal/client_shared_terminal_mission.cdf",
	clientGameObjectType = 16390,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_mission",

	gameObjectType = 16390,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_mission",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_mission",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"datapad"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2907007746,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_mission, "object/tangible/terminal/shared_terminal_mission.iff")

object_tangible_terminal_shared_terminal_mission_artisan = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_free_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/terminal/client_shared_terminal_mission.cdf",
	clientGameObjectType = 16390,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_mission_artisan",

	gameObjectType = 16390,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_mission_artisan",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_mission_artisan",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"datapad"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3927829015,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_mission_artisan, "object/tangible/terminal/shared_terminal_mission_artisan.iff")

object_tangible_terminal_shared_terminal_mission_bounty = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_free_s3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/terminal/client_shared_terminal_mission.cdf",
	clientGameObjectType = 16390,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_mission_bounty",

	gameObjectType = 16390,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_mission_bounty",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_mission_bounty",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"datapad"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3951925654,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff", "object/tangible/terminal/shared_terminal_mission.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_mission_bounty, "object/tangible/terminal/shared_terminal_mission_bounty.iff")

object_tangible_terminal_shared_terminal_mission_entertainer = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_imp_data_terminal_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/terminal/client_shared_terminal_mission.cdf",
	clientGameObjectType = 16390,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_mission_entertainer",

	gameObjectType = 16390,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_mission_entertainer",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_mission_entertainer",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"datapad"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2410700040,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_mission_entertainer, "object/tangible/terminal/shared_terminal_mission_entertainer.iff")

object_tangible_terminal_shared_terminal_mission_imperial = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_imp_data_terminal_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/terminal/client_shared_terminal_mission.cdf",
	clientGameObjectType = 16390,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_mission_imperial",

	gameObjectType = 16390,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_mission_imperial",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_mission_imperial",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"datapad"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4186402280,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff", "object/tangible/terminal/shared_terminal_mission.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_mission_imperial, "object/tangible/terminal/shared_terminal_mission_imperial.iff")

object_tangible_terminal_shared_terminal_mission_newbie = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_mission.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/terminal/client_shared_terminal_mission.cdf",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_mission",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_mission",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_mission",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"datapad"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2666426537,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_mission_newbie, "object/tangible/terminal/shared_terminal_mission_newbie.iff")

object_tangible_terminal_shared_terminal_mission_rebel = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_imp_data_terminal_s3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/terminal/client_shared_terminal_mission.cdf",
	clientGameObjectType = 16390,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_mission_rebel",

	gameObjectType = 16390,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_mission_rebel",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_mission_rebel",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"datapad"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2082896080,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff", "object/tangible/terminal/shared_terminal_mission.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_mission_rebel, "object/tangible/terminal/shared_terminal_mission_rebel.iff")

object_tangible_terminal_shared_terminal_mission_scout = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_imp_data_terminal_s2.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/terminal/client_shared_terminal_mission.cdf",
	clientGameObjectType = 16390,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_mission_scout",

	gameObjectType = 16390,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_mission_scout",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_mission_scout",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"datapad"},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 581658756,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_mission_scout, "object/tangible/terminal/shared_terminal_mission_scout.iff")

object_tangible_terminal_shared_terminal_mission_statue = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/thm_prp_kiosk_statue.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/terminal/client_shared_terminal_mission.cdf",
	clientGameObjectType = 16390,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 1,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_mission",

	gameObjectType = 16390,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_mission",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_mission",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {"datapad"},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4114889569,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff", "object/tangible/terminal/shared_terminal_mission.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_mission_statue, "object/tangible/terminal/shared_terminal_mission_statue.iff")

object_tangible_terminal_shared_terminal_newbie_clothing = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_travel.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:newbie_clothing_dispenser",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:newbie_clothing_dispenser",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4290085920,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_newbie_clothing, "object/tangible/terminal/shared_terminal_newbie_clothing.iff")

object_tangible_terminal_shared_terminal_newbie_food = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_travel.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:newbie_food_dispenser",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:newbie_food_dispenser",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2721518483,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_newbie_food, "object/tangible/terminal/shared_terminal_newbie_food.iff")

object_tangible_terminal_shared_terminal_newbie_instrument = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_travel.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:newbie_instrument_dispenser",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:newbie_instrument_dispenser",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3665675874,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_newbie_instrument, "object/tangible/terminal/shared_terminal_newbie_instrument.iff")

object_tangible_terminal_shared_terminal_newbie_medicine = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_travel.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_medicine",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:newbie_medicine_dispenser",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1668873424,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_newbie_medicine, "object/tangible/terminal/shared_terminal_newbie_medicine.iff")

object_tangible_terminal_shared_terminal_newbie_tool = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_travel.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:newbie_tool_dispenser",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:newbie_tool_dispenser",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4182051530,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_newbie_tool, "object/tangible/terminal/shared_terminal_newbie_tool.iff")

object_tangible_terminal_shared_terminal_newsnet = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_free_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@gcw:newsnet_terminal",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@gcw:newsnet_terminal",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 757402672,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_newsnet, "object/tangible/terminal/shared_terminal_newsnet.iff")

object_tangible_terminal_shared_terminal_nym_cave = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_travel.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:newbie_instrument_dispenser",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3880062907,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_nym_cave, "object/tangible/terminal/shared_terminal_nym_cave.iff")

object_tangible_terminal_shared_terminal_player_structure = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_wall_s2.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16392,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_player_structure",

	gameObjectType = 16392,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_player_structure",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_player_structure",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4023332994,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_player_structure, "object/tangible/terminal/shared_terminal_player_structure.iff")

object_tangible_terminal_shared_terminal_player_structure_nosnap = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_wall_s2.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16392,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_player_structure",

	gameObjectType = 16392,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_player_structure",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_player_structure",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 437907033,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_player_structure_nosnap, "object/tangible/terminal/shared_terminal_player_structure_nosnap.iff")

object_tangible_terminal_shared_terminal_player_structure_nosnap_mini = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_diagnostic_screen.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16392,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_player_structure",

	gameObjectType = 16392,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_player_structure",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_player_structure",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 2775644177,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_player_structure_nosnap_mini, "object/tangible/terminal/shared_terminal_player_structure_nosnap_mini.iff")

object_tangible_terminal_shared_terminal_pm_register = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_free_s3.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_pm_register",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_pm_register",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_pm_register",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1004751674,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_pm_register, "object/tangible/terminal/shared_terminal_pm_register.iff")

object_tangible_terminal_shared_terminal_pob_ship = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_wall_s2.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@space/space_interaction:terminal_pob_ship",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@space/space_interaction:terminal_pob_ship",

	noBuildRadius = 0,

	objectName = "@space/space_interaction:terminal_pob_ship",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3308349953,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_pob_ship, "object/tangible/terminal/shared_terminal_pob_ship.iff")

object_tangible_terminal_shared_terminal_ship_interior_security_1 = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_wall_s1.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "clientdata/newbie_tutorial/shared_debris.cdf",
	clientGameObjectType = 4,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:door_security_terminal",

	gameObjectType = 4,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:door_security_terminal",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 965433242,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_ship_interior_security_1, "object/tangible/terminal/shared_terminal_ship_interior_security_1.iff")

object_tangible_terminal_shared_terminal_shipping = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_shipping.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16393,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_shipping",

	gameObjectType = 16393,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_shipping",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_shipping",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1225472505,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_shipping, "object/tangible/terminal/shared_terminal_shipping.iff")

object_tangible_terminal_shared_terminal_skill = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_wall_s2.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "",

	noBuildRadius = 0,

	objectName = "",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 328711509,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_skill, "object/tangible/terminal/shared_terminal_skill.iff")

object_tangible_terminal_shared_terminal_space = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_spaceterminal.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16395,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_space",

	gameObjectType = 16395,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_space",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_space",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1701113915,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_space, "object/tangible/terminal/shared_terminal_space.iff")

object_tangible_terminal_shared_terminal_travel = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/ksk_all_travel.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_travel",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_travel",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_travel",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 0,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 1946349820,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_travel, "object/tangible/terminal/shared_terminal_travel.iff")

object_tangible_terminal_shared_terminal_water_pressure = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/frn_all_data_terminal_wall_s2.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16396,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_water_pressure",

	gameObjectType = 16396,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:terminal_water_pressure",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_water_pressure",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 4062337637,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_terminal_water_pressure, "object/tangible/terminal/shared_terminal_water_pressure.iff")

object_tangible_terminal_shared_test = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/thm_all_elevator_panel_updown_s02.apt",
	arrangementDescriptors = {},

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 16384,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@terminal_detail:terminal_elevator",

	gameObjectType = 16384,

	locationReservationRadius = 0,
	lookAtText = "@terminal_lookat:base_terminal",

	noBuildRadius = 0,

	objectName = "@terminal_name:terminal_elevator",
	onlyVisibleInTools = 0,

	paletteColorCustomizationVariables = {},
	portalLayoutFilename = "",

	rangedIntCustomizationVariables = {},

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptors = {},
	snapToTerrain = 1,
	socketDestinations = {},
	structureFootprintFileName = "",
	surfaceType = 0,

	targetable = 1,
	totalCellNumber = 0,

	useStructureFootprintOutline = 0,

	clientObjectCRC = 3876933537,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/terminal/base/shared_base_terminal.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_terminal_shared_test, "object/tangible/terminal/shared_test.iff")
