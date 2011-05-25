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


object_tangible_food_spice_shared_spice_base = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_tato_bowl_full_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:spice",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:spice",

	noBuildRadius = 0,

	objectName = "@food_name:spice",
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

	clientObjectCRC = 2073269551,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_spice_shared_spice_base, "object/tangible/food/spice/shared_spice_base.iff")

object_tangible_food_spice_shared_spice_booster_blue = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_poison_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:booster_blue",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:booster_blue",

	noBuildRadius = 0,

	objectName = "@food_name:booster_blue",
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

	clientObjectCRC = 2516008025,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/spice/shared_spice_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_spice_shared_spice_booster_blue, "object/tangible/food/spice/shared_spice_booster_blue.iff")

object_tangible_food_spice_shared_spice_crash_n_burn = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_antidote_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:crash_n_burn",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:crash_n_burn",

	noBuildRadius = 0,

	objectName = "@food_name:crash_n_burn",
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

	clientObjectCRC = 96283804,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/spice/shared_spice_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_spice_shared_spice_crash_n_burn, "object/tangible/food/spice/shared_spice_crash_n_burn.iff")

object_tangible_food_spice_shared_spice_droid_lube = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:droid_lube",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:droid_lube",

	noBuildRadius = 0,

	objectName = "@food_name:droid_lube",
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

	clientObjectCRC = 1700944368,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/spice/shared_spice_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_spice_shared_spice_droid_lube, "object/tangible/food/spice/shared_spice_droid_lube.iff")

object_tangible_food_spice_shared_spice_giggledust = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_tato_jar_spice_s02.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:giggledust",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:giggledust",

	noBuildRadius = 0,

	objectName = "@food_name:giggledust",
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

	clientObjectCRC = 1878192398,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/spice/shared_spice_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_spice_shared_spice_giggledust, "object/tangible/food/spice/shared_spice_giggledust.iff")

object_tangible_food_spice_shared_spice_grey_gabaki = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_spice_container.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:grey_gabaki",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:grey_gabaki",

	noBuildRadius = 0,

	objectName = "@food_name:grey_gabaki",
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

	clientObjectCRC = 4012257661,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/spice/shared_spice_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_spice_shared_spice_grey_gabaki, "object/tangible/food/spice/shared_spice_grey_gabaki.iff")

object_tangible_food_spice_shared_spice_gunjack = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_antidote_lg_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:gunjack",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:gunjack",

	noBuildRadius = 0,

	objectName = "@food_name:gunjack",
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

	clientObjectCRC = 3162646760,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/spice/shared_spice_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_spice_shared_spice_gunjack, "object/tangible/food/spice/shared_spice_gunjack.iff")

object_tangible_food_spice_shared_spice_kliknik_boost = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_food_meat_loaf_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:bio_kliknik_fortitude_boost",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:bio_kliknik_fortitude_boost",

	noBuildRadius = 0,

	objectName = "@food_name:bio_kliknik_fortitude_boost",
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

	clientObjectCRC = 2365942016,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/spice/shared_spice_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_spice_shared_spice_kliknik_boost, "object/tangible/food/spice/shared_spice_kliknik_boost.iff")

object_tangible_food_spice_shared_spice_kwi_boost = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_food_meat_loaf_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:bio_kwi_adrenal_boost",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:bio_kwi_adrenal_boost",

	noBuildRadius = 0,

	objectName = "@food_name:bio_kwi_adrenal_boost",
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

	clientObjectCRC = 3381348892,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/spice/shared_spice_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_spice_shared_spice_kwi_boost, "object/tangible/food/spice/shared_spice_kwi_boost.iff")

object_tangible_food_spice_shared_spice_muon_gold = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_medpak_broad_spectrum.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:muon_gold",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:muon_gold",

	noBuildRadius = 0,

	objectName = "@food_name:muon_gold",
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

	clientObjectCRC = 3112742541,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/spice/shared_spice_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_spice_shared_spice_muon_gold, "object/tangible/food/spice/shared_spice_muon_gold.iff")

object_tangible_food_spice_shared_spice_neutron_pixey = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_medic_stimpack_sm_s1.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:neutron_pixey",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:neutron_pixey",

	noBuildRadius = 0,

	objectName = "@food_name:neutron_pixey",
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

	clientObjectCRC = 3750021953,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/spice/shared_spice_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_spice_shared_spice_neutron_pixey, "object/tangible/food/spice/shared_spice_neutron_pixey.iff")

object_tangible_food_spice_shared_spice_pyrepenol = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/wp_sp_ppack_bomb.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:pyrepenol",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:pyrepenol",

	noBuildRadius = 0,

	objectName = "@food_name:pyrepenol",
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

	clientObjectCRC = 1073230239,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/spice/shared_spice_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_spice_shared_spice_pyrepenol, "object/tangible/food/spice/shared_spice_pyrepenol.iff")

object_tangible_food_spice_shared_spice_scramjet = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/con_man_chemicals_sm.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:scramjet",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:scramjet",

	noBuildRadius = 0,

	objectName = "@food_name:scramjet",
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

	clientObjectCRC = 3992242678,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/spice/shared_spice_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_spice_shared_spice_scramjet, "object/tangible/food/spice/shared_spice_scramjet.iff")

object_tangible_food_spice_shared_spice_sedative_h4b = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_chemical_dispersion.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:sedative_h4b",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:sedative_h4b",

	noBuildRadius = 0,

	objectName = "@food_name:sedative_h4b",
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

	clientObjectCRC = 4072023421,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/spice/shared_spice_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_spice_shared_spice_sedative_h4b, "object/tangible/food/spice/shared_spice_sedative_h4b.iff")

object_tangible_food_spice_shared_spice_shadowpaw = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_tato_jar_spice_s03.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:shadowpaw",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:shadowpaw",

	noBuildRadius = 0,

	objectName = "@food_name:shadowpaw",
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

	clientObjectCRC = 2778111395,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/spice/shared_spice_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_spice_shared_spice_shadowpaw, "object/tangible/food/spice/shared_spice_shadowpaw.iff")

object_tangible_food_spice_shared_spice_sweetblossom = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_con_tato_jar_spice_s01.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:sweetblossom",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:sweetblossom",

	noBuildRadius = 0,

	objectName = "@food_name:sweetblossom",
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

	clientObjectCRC = 1182200956,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/spice/shared_spice_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_spice_shared_spice_sweetblossom, "object/tangible/food/spice/shared_spice_sweetblossom.iff")

object_tangible_food_spice_shared_spice_thruster_head = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/eqp_comp_warhead_chemical.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:thruster_head",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:thruster_head",

	noBuildRadius = 0,

	objectName = "@food_name:thruster_head",
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

	clientObjectCRC = 732545867,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/spice/shared_spice_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_spice_shared_spice_thruster_head, "object/tangible/food/spice/shared_spice_thruster_head.iff")

object_tangible_food_spice_shared_spice_yarrock = SharedTangibleObjectTemplate:new {
	appearanceFilename = "appearance/edb_food_vegetable_s5.apt",
	arrangementDescriptorFilename = "",

	certificationsRequired = {},
	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 8202,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 51,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 1,
	customizationVariableMapping = {},

	detailedDescription = "@food_detail:yarrock",

	gameObjectType = 8202,

	locationReservationRadius = 0,
	lookAtText = "@food_lookat:yarrock",

	noBuildRadius = 0,

	objectName = "@food_name:yarrock",
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

	clientObjectCRC = 194250139,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/tangible/base/shared_tangible_base.iff", "object/tangible/base/shared_tangible_craftable.iff", "object/tangible/food/spice/shared_spice_base.iff"}
}

ObjectTemplates:addClientTemplate(object_tangible_food_spice_shared_spice_yarrock, "object/tangible/food/spice/shared_spice_yarrock.iff")
