--Copyright (C) 2008 <SWGEmu>


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

tuskenExecutionerRandom = Creature:new {
	objectName = "tuskenExecutionerRandom",  -- Lua Object Name
	creatureType = "NPC",
	faction = "tusken_raider", 
	factionPoints = 20,
	gender = "",

	speciesName = "tusken_executioner",
	stfName = "mob/creature_names", 
	objectCRC = 3780705985, 
	socialGroup = "tusken_raider",
	 

	level = 289,
	
	combatFlags = ATTACKABLE_FLAG + ENEMY_FLAG + AGGRESSIVE_FLAG,

	healthMax = 320000,
	healthMin = 270000,
	strength = 50000,
	constitution = 50000,

	actionMax = 320000,
	actionMin = 270000,
	quickness = 50000,
	stamina = 50000,

	mindMax = 320000,
	mindMin = 270000,
	focus = 50000,
	willpower = 50000,

	height = 1, -- Size of creature
	armor = 3, -- 0 = None; 1 = Light; 2 = Medium; 3 = Heavy
	kinetic = 85,
	energy = 80,
	electricity = 30,
	stun = 80,
	blast = 45,
	heat = 100,
	cold = 0,
	acid = 45,
	lightsaber = 0,

	accuracy = 450,

	healer = 0,

	pack = 1,
	herd = 0,
	stalker = 1,
	killer = 1,
	aggressive = 1,
	invincible = 0, 

	  
	meleeDefense = 1,    
	rangedDefense = 1,

	attackCreatureOnSight = "", -- Enter socialGroups 

	weapon = "object/weapon/ranged/rifle/shared_rifle_tusken.iff", -- File path to weapon -> object\xxx\xxx\xx
	weaponName = "a Tusken Rifle", -- Name ex. 'a Vibrolance'
	weaponTemp = "rifle_tusken", -- Weapon Template ex. 'lance_vibrolance'
	weaponClass = "RifleRangedWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
	weaponEquipped = 1,
	weaponMinDamage = 1250,
	weaponMaxDamage = 2750,
	weaponAttackSpeed = 1.6,
	weaponDamageType = "ENERGY", -- ELECTRICITY, KINETIC, etc
	weaponArmorPiercing = "LIGHT", -- LIGHT, NONE, MEDIUM, HEAVY

	alternateWeapon = "", -- File path to weapon -> object\xxx\xxx\xx
	alternateWeaponName = "", -- Name ex. 'a Vibrolance'
	alternateWeaponTemp = "", -- Weapon Template ex. 'lance_vibrolance'
	alternateWeaponClass = "", -- Weapon Class ex. 'PolearmMeleeWeapon'
	alternateWeaponEquipped = 0,
	alternateWeaponMinDamage = 0,
	alternateWeaponMaxDamage = 0,
	alternateWeaponAttackSpeed = 0,
	alternateWeaponDamageType = "", -- ELECTRICITY, KINETIC, etc
	alternateWeaponArmorPiercing = "", -- LIGHT, NONE, MEDIUM, HEAVY

	internalNPCDamageModifier = 0.3, -- Damage Modifier to other NPC's

	lootGroup = "1,11,15,19,24,25,33,99", -- Group it belongs to for loot

	tame = 0,  -- Likely hood to be tamed

	milk = 0,

	boneType = "",
	boneMax = 0,

	hideType = "",
	hideMax = 0,

	meatType = "",
	meatMax = 0,

	skills = { "tuskenRangedAttack5", "tuskenRangedAttack6", "tuskenRangedAttack7",  "tuskenRangedAttack8", "tuskenRangedAttack9", "tuskenRangedAttack10", "tuskenRangedAttack11", "tuskenRangedAttack12",  "tuskenRangedAttack13" },
	respawnTimer = 36000,

	behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(tuskenExecutionerRandom, 3780705985) -- Add to Global Table
