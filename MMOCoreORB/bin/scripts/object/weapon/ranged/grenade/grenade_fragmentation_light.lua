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


object_weapon_ranged_grenade_grenade_fragmentation_light = object_weapon_ranged_grenade_shared_grenade_fragmentation_light:new {

	objectMenuComponent = "ThrowGrenadeMenuComponent",

	playerRaces = { "object/creature/player/bothan_male.iff",
			"object/creature/player/bothan_female.iff",
			"object/creature/player/human_male.iff",
			"object/creature/player/human_female.iff",
			"object/creature/player/ithorian_male.iff",
			"object/creature/player/ithorian_female.iff",
			"object/creature/player/moncal_male.iff",
			"object/creature/player/moncal_female.iff",
			"object/creature/player/rodian_male.iff",
			"object/creature/player/rodian_female.iff",
			"object/creature/player/sullustan_male.iff",
			"object/creature/player/sullustan_female.iff",
			"object/creature/player/trandoshan_male.iff",
			"object/creature/player/trandoshan_female.iff",
			"object/creature/player/twilek_male.iff",
			"object/creature/player/twilek_female.iff",
			"object/creature/player/wookiee_male.iff",
			"object/creature/player/wookiee_female.iff",
			"object/creature/player/zabrak_male.iff",
			"object/creature/player/zabrak_female.iff" },

	-- RANGEDATTACK, MELEEATTACK, FORCEATTACK, TRAPATTACK, GRENADEATTACK, HEAVYACIDBEAMATTACK,
	-- HEAVYLIGHTNINGBEAMATTACK, HEAVYPARTICLEBEAMATTACK, HEAVYROCKETLAUNCHERATTACK, HEAVYLAUNCHERATTACK
	attackType = GRENADEATTACK,

	-- ENERGY, KINETIC, ELECTRICITY, STUN, BLAST, HEAT, COLD, ACID, LIGHTSABER
	damageType = BLAST,

	-- NONE, LIGHT, MEDIUM, HEAVY
	armorPiercing = NONE,

	-- combat_rangedspecialize_bactarifle, combat_rangedspecialize_rifle, combat_rangedspecialize_pistol, combat_rangedspecialize_heavy, combat_rangedspecialize_carbine
	-- combat_meleespecialize_unarmed, combat_meleespecialize_twohand, combat_meleespecialize_polearm, combat_meleespecialize_onehand, combat_general,
	-- combat_meleespecialize_twohandlightsaber, combat_meleespecialize_polearmlightsaber, combat_meleespecialize_onehandlightsaber
	xpType = "combat_general",

	-- See http://www.ocdsoft.com/files/certifications.xls
	certificationsRequired = { "cert_grenade_fragmentation_light" },

	-- See http://www.ocdsoft.com/files/accuracy.xls
	creatureAccuracyModifiers = { "thrown_accuracy" },

	-- See http://www.ocdsoft.com/files/defense.xls
	defenderDefenseModifiers = { "ranged_defense" },

	-- See http://www.ocdsoft.com/files/speed.xls
	speedModifiers = { "thrown_speed" },

	-- Leave blank for now
	damageModifiers = { },

	useCount = 5,

	combatSpam = "throw_fragmentation",

	healthAttackCost = 50,
	actionAttackCost = 50,
	mindAttackCost = 10,

	pointBlankRange = 0,
	pointBlankAccuracy = -10,

	idealRange = 20,
	idealAccuracy = 15,

	maxRange = 64,
	maxRangeAccuracy = -30,

	minDamage = 50,
	maxDamage = 150,

	attackSpeed = 4,

	woundsRatio = 10,
	animationType = "fragmentation",


	numberExperimentalProperties = {1, 1, 2, 2, 2, 2, 1, 2, 2, 2, 2, 1, 2, 2, 2},
	experimentalProperties = {"XX", "XX", "OQ", "SR", "OQ", "SR", "OQ", "SR", "OQ", "SR", "SR", "OQ", "SR", "OQ", "SR", "OQ", "SR", "OQ", "SR", "XX", "OQ", "SR", "OQ", "SR", "OQ", "SR"},
	experimentalWeights = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	experimentalGroupTitles = {"null", "null", "expDamage", "expDamage", "expDamage", "expDamage", "null", "expRange", "expRange", "expRange", "expRange", "null", "expEffeciency", "expEffeciency", "expEffeciency"},
	experimentalSubGroupTitles = {"null", "null", "mindamage", "maxdamage", "attackspeed", "woundchance", "hitpoints", "zerorangemod", "maxrangemod", "midrangemod", "midrange", "maxrange", "attackhealthcost", "attackactioncost", "attackmindcost"},
	experimentalMin = {0, 0, 130, 220, 5.5, 7, 1000, -16, -45, 0, 10, 64, 75, 65, 13},
	experimentalMax = {0, 0, 170, 760, 2.5, 13, 1000, 14, 15, 30, 30, 64, 35, 25, 7},
	experimentalPrecision = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	experimentalCombineType = {0, 0, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 1, 1},
}

ObjectTemplates:addTemplate(object_weapon_ranged_grenade_grenade_fragmentation_light, "object/weapon/ranged/grenade/grenade_fragmentation_light.iff")
