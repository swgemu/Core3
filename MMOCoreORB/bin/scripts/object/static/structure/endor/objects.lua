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


object_static_structure_endor_shared_endor_cap = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_village_tree_catwlk_cap_s01.apt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 3,

	totalCellNumber = 0,

	clientObjectCRC = 1412682900,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/structure/base/shared_static_structure_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_structure_endor_shared_endor_cap, "object/static/structure/endor/shared_endor_cap.iff")

object_static_structure_endor_shared_endor_catwalk = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/thm_endr_village_tree_catwlk_s01.apt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 255,
	collisionActionFlags = 1,
	collisionActionPassFlags = 0,
	collisionMaterialBlockFlags = 1,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "string_id_table",

	gameObjectType = 5,

	locationReservationRadius = 0,
	lookAtText = "string_id_table",

	noBuildRadius = 0,

	objectName = "@obj_n:unknown_object",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 1,
	scaleThresholdBeforeExtentTest = 0.5,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 3,

	totalCellNumber = 0,

	clientObjectCRC = 2834035953,
	derivedFromTemplates = {"object/object/base/shared_base_object.iff", "object/static/base/shared_static_base.iff", "object/static/structure/base/shared_static_structure_base.iff"}
}

ObjectTemplates:addClientTemplate(object_static_structure_endor_shared_endor_catwalk, "object/static/structure/endor/shared_endor_catwalk.iff")

object_static_structure_endor_shared_endr_imprv_bannerpole_s01 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/mun_corl_imprv_bannerpole_s01.apt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "clientdata/structure/endr_imprv_bannerpole_s01.cdf",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "",

	gameObjectType = 5,

	lookAtText = "",

	noBuildRadius = 1,

	objectName = "@item_n:banner_corellia",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 1,

	totalCellNumber = 0,

	clientObjectCRC = 2166795982,
	derivedFromTemplates = {}
}

ObjectTemplates:addClientTemplate(object_static_structure_endor_shared_endr_imprv_bannerpole_s01, "object/static/structure/endor/shared_endr_imprv_bannerpole_s01.iff")

object_static_structure_endor_shared_endr_imprv_flagpole_s01 = SharedStaticObjectTemplate:new {
	appearanceFilename = "appearance/mun_corl_imprv_flagpole_s01.apt",
	arrangementDescriptorFilename = "",

	clearFloraRadius = 0,
	clientDataFile = "clientdata/structure/endr_imprv_flagpole_s01.cdf",
	clientGameObjectType = 5,
	collisionActionBlockFlags = 0,
	collisionActionFlags = 0,
	collisionActionPassFlags = 1,
	collisionMaterialBlockFlags = 0,
	collisionMaterialFlags = 1,
	collisionMaterialPassFlags = 0,
	containerType = 0,
	containerVolumeLimit = 0,

	detailedDescription = "",

	gameObjectType = 5,

	lookAtText = "",

	noBuildRadius = 1,

	objectName = "@item_n:flag_corellia",
	onlyVisibleInTools = 0,

	portalLayoutFilename = "",

	scale = 0,
	scaleThresholdBeforeExtentTest = 0,
	sendToClient = 1,
	slotDescriptorFilename = "",
	snapToTerrain = 0,
	surfaceType = 1,

	totalCellNumber = 0,

	clientObjectCRC = 4084104443,
	derivedFromTemplates = {}
}

ObjectTemplates:addClientTemplate(object_static_structure_endor_shared_endr_imprv_flagpole_s01, "object/static/structure/endor/shared_endr_imprv_flagpole_s01.iff")
