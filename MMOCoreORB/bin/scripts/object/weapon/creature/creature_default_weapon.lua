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


object_weapon_creature_creature_default_weapon = object_weapon_creature_shared_creature_default_weapon:new {

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
	attackType = MELEEATTACK,
	
	-- ENERGY, KINETIC, ELECTRICITY, STUN, BLAST, HEAT, COLD, ACID, FORCE, LIGHTSABER
	damageType = KINETIC,
	
	-- NONE, LIGHT, MEDIUM, HEAVY
	armorPiercing = NONE, 
	
	-- combat_rangedspecialize_bactarifle, combat_rangedspecialize_rifle, combat_rangedspecialize_pistol, combat_rangedspecialize_heavy, combat_rangedspecialize_carbine
	-- combat_meleespecialize_unarmed, combat_meleespecialize_twohand, combat_meleespecialize_polearm, combat_meleespecialize_onehand, combat_general,
	-- combat_meleespecialize_twohandlightsaber, combat_meleespecialize_polearmlightsaber, combat_meleespecialize_onehandlightsaber
	xpType = "combat_meleespecialize_unarmed",
	       
	-- See http://www.ocdsoft.com/files/certifications.xls
	certificationsRequired = {  },

	-- See http://www.ocdsoft.com/files/accuracy.xls
	creatureAccuracyModifiers = { "unarmed_accuracy" },
	
	-- See http://www.ocdsoft.com/files/defense.xls
	defenderDefenseModifiers = { "unarmed_passive_defense", "melee_defense" },
	
	-- can be dodge, counterattack, or block or a combination
	-- Secondary defense when equipped
	defenderSecondaryDefenseModifiers = { "dodge", "counterattack" },
	
	-- See http://www.ocdsoft.com/files/speed.xls
	speedModifiers = { "unarmed_speed" },
	
	-- carbine_damage, onehandmelee_damage, pistol_damage, rifle_damage, twohandmelee_damage, unarmed_damage
	damageModifiers = { "unarmed_damage" },
	       
	
	-- The values below are the default values.  To be used for blue frog objects primarily
	healthAttackCost = 0,
	actionAttackCost = 0,
	mindAttackCost = 0,
	forceCost = 0,
	
	pointBlankAccuracy = 7,
	pointBlankRange = 0,
	
	idealRange = 5,
	idealAccuracy = 7,
	
	maxRange = 5,
	maxRangeAccuracy = 7,

	minDamage = 20,
	maxDamage = 90,
	
	attackSpeed = 3.7,
	
	woundsRatio = 5

}

ObjectTemplates:addTemplate(object_weapon_creature_creature_default_weapon, "object/weapon/creature/creature_default_weapon.iff")
