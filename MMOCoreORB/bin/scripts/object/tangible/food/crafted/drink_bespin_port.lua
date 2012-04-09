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


object_tangible_food_crafted_drink_bespin_port = object_tangible_food_crafted_shared_drink_bespin_port:new {
	templateType = CONSUMABLE,

	duration = 1,
	filling = 10,
	nutrition = 10,

	effectType = 3, -- Event Based Buff
	eventTypes = {CRAFTINGEXPERIMENTATION},

	fillingMin = 25,
	fillingMax = 15,
	flavorMin = 1,
	flavorMax = 1,
	nutritionMin = 3,
	nutritionMax = 12,
	quantityMin = 5,
	quantityMax = 8,

	modifiers = { "experiment_bonus", 0 },

	buffName = "food.experiment_bonus",
	buffCRC = 0x9B38A4CB,
	speciesRestriction = "",

	numberExperimentalProperties = {1, 1, 1, 1, 2, 2, 2, 1},
	experimentalProperties = {"XX", "XX", "XX", "XX", "DR", "OQ", "OQ", "PE", "FL", "OQ", "XX"},
	experimentalWeights = {1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1},
	experimentalGroupTitles = {"null", "null", "null", "null", "exp_nutrition", "exp_quantity", "exp_filling", "null"},
	experimentalSubGroupTitles = {"null", "null", "hitpoints", "quantity_bonus", "nutrition", "quantity", "filling", "stomach"},
	experimentalMin = {0, 0, 1000, 0, 120, 100, 120, 1},
	experimentalMax = {0, 0, 1000, 0, 75, 60, 80, 1},
	experimentalPrecision = {0, 0, 0, 0, 10, 10, 10, 0},
}

ObjectTemplates:addTemplate(object_tangible_food_crafted_drink_bespin_port, "object/tangible/food/crafted/drink_bespin_port.iff")
