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


object_tangible_medicine_crafted_medpack_disease_area_action_a = object_tangible_medicine_crafted_shared_medpack_disease_area_action_a:new {
	gameObjectType = 8240,
	templateType = DOTPACK,
	medicineUse = 5,
	effectiveness = 100,
	duration = 300,
	range = 15,
	rangeMod = 1.0,
	pool = 3,
	dotType = DISEASED,
	potency = 150,
	commandToExecute = "/applydisease",
	area = 10,

	numberExperimentalProperties = {1, 1, 2, 2, 2, 2, 2, 2, 2, 1},
	experimentalProperties = {"XX", "XX", "OQ", "PE", "OQ", "UT", "CD", "OQ", "CD", "OQ", "OQ", "PE", "OQ", "PE", "DR", "OQ", "XX"},
	experimentalWeights = {1, 1, 2, 1, 2, 1, 1, 2, 1, 2, 2, 1, 2, 1, 1, 1, 1},
	experimentalGroupTitles = {"null", "null", "exp_effectiveness", "expCharges", "expCharges", "exp_effectiveness", "expEaseOfUse", "expEaseOfUse", "exp_effectiveness", "null"},
	experimentalSubGroupTitles = {"null", "null", "power", "charges", "range", "area", "skillmodmin", "potency", "duration", "hitpoints"},
	experimentalMin = {0, 0, 10, 5, 15, 10, 60, 25, 120, 1000},
	experimentalMax = {0, 0, 20, 15, 20, 5, 40, 50, 600, 1000},
	experimentalPrecision = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},

}

ObjectTemplates:addTemplate(object_tangible_medicine_crafted_medpack_disease_area_action_a, "object/tangible/medicine/crafted/medpack_disease_area_action_a.iff")
