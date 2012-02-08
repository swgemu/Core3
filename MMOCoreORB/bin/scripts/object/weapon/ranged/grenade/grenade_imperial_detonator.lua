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


object_weapon_ranged_grenade_grenade_imperial_detonator = object_weapon_ranged_grenade_shared_grenade_imperial_detonator:new {


	healthAttackCost = 125,
	actionAttackCost = 125,
	mindAttackCost = 50,
	forceCost = 0,

	pointBlankRange = 0,
	pointBlankAccuracy = -10,

	idealRange = 20,
	idealAccuracy = 15,

	maxRange = 32,
	maxRangeAccuracy = -30,

	minDamage = 100,
	maxDamage = 550,

	attackSpeed = 6,

	woundsRatio = 10,

	numberExperimentalProperties = {1, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 2},
	experimentalProperties = {"XX", "XX", "OQ", "SR", "OQ", "SR", "OQ", "SR", "OQ", "SR", "SR", "OQ", "SR", "OQ", "SR", "OQ", "SR", "OQ", "SR", "XX", "OQ", "SR", "OQ", "SR", "OQ", "SR"},
	experimentalWeights = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	experimentalGroupTitles = {"null", "null", "expDamage", "expDamage", "expDamage", "expDamage", "null", "expRange", "expRange", "expRange", "expRange", "null", "expEffeciency", "expEffeciency", "expEffeciency"},
	experimentalSubGroupTitles = {"null", "null", "mindamage", "maxdamage", "attackspeed", "woundchance", "hitpoints", "zerorangemod", "maxrangemod", "midrangemod", "midrange", "maxrange", "attackhealthcost", "attackactioncost", "attackmindcost"},
	experimentalMin = {0, 0, 645, 1300, 6, 7, 1000, -16, -45, 0, 10, 64, 163, 163, 65},
	experimentalMax = {0, 0, 989, 2000, 2.5, 13, 1000, 14, -15, 30, 30, 64, 88, 88, 35},
	experimentalPrecision = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
}

ObjectTemplates:addTemplate(object_weapon_ranged_grenade_grenade_imperial_detonator, "object/weapon/ranged/grenade/grenade_imperial_detonator.iff")
