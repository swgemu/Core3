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


object_tangible_ship_crafted_booster_booster_mk4 = object_tangible_ship_crafted_booster_shared_booster_mk4:new {


	numberExperimentalProperties = {1, 1, 2, 1, 2, 2, 1, 2, 3, 3, 3, 3, 3},
	experimentalProperties = {"XX", "XX", "OQ", "UT", "XX", "OQ", "UT", "OQ", "UT", "XX", "OQ", "PE", "CD", "OQ", "PE", "CD", "OQ", "PE", "CD", "OQ", "PE", "CD", "OQ", "PE", "CD", "OQ", "PE"},
	experimentalWeights = {1, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 2},
	experimentalGroupTitles = {"null", "null", "exp_hp", "null", "exp_mass", "exp_armorhpmax", "null", "exp_maintenance", "exp_booster_energy", "exp_booster_recharge", "booster_consumption", "exp_booster_speed", "exp_booster_acceleration"},
	experimentalSubGroupTitles = {"null", "null", "hitpointsmax", "efficiency", "mass", "armorhpmax", "energy_efficiency", "energy_maintenance", "booster_energy", "booster_recharge", "booster_consumption", "booster_speed", "booster_acceleration"},
	experimentalMin = {0, 0, 654, 1, 14196, 327, 1, 748, 932, 23, 93, 14, 19},
	experimentalMax = {0, 0, 1215, 1, 7644, 607, 1, 403, 1730, 43, 173, 27, 35},
	experimentalPrecision = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	experimentalCombineType = {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
}

ObjectTemplates:addTemplate(object_tangible_ship_crafted_booster_booster_mk4, "object/tangible/ship/crafted/booster/booster_mk4.iff")
