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


object_tangible_food_spice_spice_neutron_pixey = object_tangible_food_spice_shared_spice_neutron_pixey:new {
	templateType = CONSUMABLE,

	duration = 800,
	filling = 0,
	nutrition = 0,

	effectType = 5,

	fillingMin = 0,
	fillingMax = 0,
	flavorMin = 0,
	flavorMax = 0,
	nutritionMin = 0,
	nutritionMax = 0,
	quantityMin = 0,
	quantityMax = 0,

	modifiers = { "health", 1000, "strength" , 200, "constitution", 200, "action", 500, "quickness", 50, "stamina", 50 },

	buffName = "neutron_pixey",
	buffCRC = 0,
	speciesRestriction = "",

	numberExperimentalProperties = {1, 1, 3},
	experimentalProperties = {"XX", "XX", "DR", "OQ", "UT"},
	experimentalWeights = {1, 1, 4, 1, 1},
	experimentalGroupTitles = {"null", "null", "exp_nutrition"},
	experimentalSubGroupTitles = {"null", "null", "hitpoints"},
	experimentalMin = {0, 0, 1000},
	experimentalMax = {0, 0, 1000},
	experimentalPrecision = {0, 0, 0},
}

ObjectTemplates:addTemplate(object_tangible_food_spice_spice_neutron_pixey, "object/tangible/food/spice/spice_neutron_pixey.iff")
