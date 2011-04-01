--Copyright (C) 2010 <SWGEmu>


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


object_tangible_wearables_armor_ithorian_sentinel_ith_armor_s03_bracer_l = object_tangible_wearables_armor_ithorian_sentinel_shared_ith_armor_s03_bracer_l:new {
	templateType = ARMOROBJECT,

	-- ALL, ALLSEXES, ALLFACTIONS, HUMANOIDS, HUMANOID_FOOTWEAR, HUMANOID_MALES, HUMANOID_FEMALES, HUMANOID_IMPERIALS, HUMANOID_REBELS, WOOKIEES, ITHORIANS, TWILEKS,
	playerUseMask = ITHORIANS,
	,
	-- Damage types in WeaponObject,
	vunerability = STUN + LIGHTSABER,

	-- These are default Blue Frog stats,
	healthEncumbrance = 1,
	actionEncumbrance = 1,
	mindEncumbrance = 1,

	-- LIGHT, MEDIUM, HEAVY,
	rating = LIGHT,

	kinetic = 15,
	energy = 15,
	electricity = 15,
	stun = 15,
	blast = 15,
	heat = 15,
	cold = 15,
	acid = 15,
	lightSaber = 0,
	numberExperimentalProperties = {1, 1, 1, 2, 2, 2, 2, 2, 2, 1, 1, 2, 1},
	experimentalProperties = {"XX", "XX", "XX", "OQ", "SR", "OQ", "SR", "OQ", "UT", "MA", "OQ", "MA", "OQ", "MA", "OQ", "XX", "XX", "OQ", "SR", "XX"},
	experimentalWeights = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	experimentalGroupTitles = {"null", "null", "null", "exp_durability", "exp_quality", "exp_resistance", "exp_durability", "exp_durability", "exp_durability", "null", "null", "exp_resistance", "null"},
	experimentalSubGroupTitles = {"null", "null", "sockets", "hit_points", "armor_effectiveness", "armor_integrity", "armor_health_encumbrance", "armor_action_encumbrance", "armor_mind_encumbrance", "armor_rating", "armor_special_type", "armor_special_effectiveness", "armor_special_integrity"},
	experimentalMin = {0, 0, 0, 1000, 1, 30000, 25, 22, 25, 1, 0, 0, 0},
	experimentalMax = {0, 0, 0, 1000, 40, 50000, 15, 13, 15, 1, 0, 0, 0},
	experimentalPrecision = {0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0},
}

ObjectTemplates:addTemplate(object_tangible_wearables_armor_ithorian_sentinel_ith_armor_s03_bracer_l, "object/tangible/wearables/armor/ithorian_sentinel/ith_armor_s03_bracer_l.iff")
