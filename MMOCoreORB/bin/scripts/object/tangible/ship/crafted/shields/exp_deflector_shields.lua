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


object_tangible_ship_crafted_shields_exp_deflector_shields = object_tangible_ship_crafted_shields_shared_exp_deflector_shields:new {


	numberExperimentalProperties = {1, 1, 2, 1, 2, 2, 1, 2, 3, 3, 3},
	experimentalProperties = {"XX", "XX", "OQ", "UT", "XX", "OQ", "UT", "OQ", "UT", "XX", "CD", "OQ", "CD", "OQ", "SR", "CD", "OQ", "SR", "CD", "OQ", "SR"},
	experimentalWeights = {1, 1, 1, 2, 1, 1, 2, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	experimentalGroupTitles = {"null", "null", "exp_hp", "null", "exp_mass", "exp_armorhpmax", "null", "exp_energy_maintenance", "exp_shield_max_front_hp", "exp_shield_max_back_hp", "exp_shield_recharge"},
	experimentalSubGroupTitles = {"null", "null", "hitpointsmax", "efficiency", "mass", "armorhpmax", "energy_efficiency", "energy_maintenance", "shield_max_front_hp", "shield_max_back_hp", "shield_recharge"},
	experimentalMin = {0, 0, 935, 1, 33150, 468, 1, 2550, 1559, 1559, 12470},
	experimentalMax = {0, 0, 1265, 1, 44850, 633, 1, 3450, 2109, 2109, 16871},
	experimentalPrecision = {0, 0, 10, 0, 10, 10, 0, 10, 10, 10, 0},
	experimentalCombineType = {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1},
}

ObjectTemplates:addTemplate(object_tangible_ship_crafted_shields_exp_deflector_shields, "object/tangible/ship/crafted/shields/exp_deflector_shields.iff")
