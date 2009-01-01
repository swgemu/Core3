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
blackSunAssassinDWB = Creature:new {
	objectName = "blackSunAssassinDWB",  -- Lua Object Name
	creatureType = "NPC",
	gender = "",

	speciesName = "mand_bunker_blksun_assassin",
	stfName = "mob/creature_names",
	objectCRC = 3627888108, 
	socialGroup = "Death Watch",
	level = 107,

	combatFlags = ATTACKABLE_FLAG + ENEMY_FLAG + AGGRESSIVE_FLAG,

	healthMax = 36000,
	healthMin = 29000,
	strength = 9000,
	constitution = 9000,

	actionMax = 36000,
	actionMin = 29000,
	quickness = 9000,
	stamina = 9000,

	mindMax = 36000,
	mindMin = 29000,
	focus = 9000,
	willpower = 9000,

	height = 1, -- Size of creature
	armor = 1, -- 0 = None; 1 = Light; 2 = Medium; 3 = Heavy
	kinetic = 55,
	energy = 55,
	electricity = 80,
	stun = 45,
	blast = 70,
	heat = 45,
	cold = 75,
	acid = 55,
	lightsaber = 0,

	accuracy = 300,

	healer = 0,

	pack = 0,
	herd = 0,
	stalker = 0,
	killer = 1,
	aggressive = 1,
	invincible = 0, 

	meleeDefense = 1,  
	rangedDefense = 1,

	attackCreatureOnSight = "", -- Enter socialGroups 

	weapon = "object/weapon/ranged/rifle/shared_rifle_tenloss_dxr6_disruptor_loot.iff", -- File path to weapon -> object\xxx\xxx\xx
	weaponName = "DXR6 Tenloss Disruptor Rifle", -- Name ex. 'a Vibrolance'
	weaponTemp = "rifle_dxr6", -- Weapon Template ex. 'lance_vibrolance'
	weaponClass = "RifleRangedWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
	weaponEquipped = 1,
	weaponMinDamage = 600,
	weaponMaxDamage = 800,
	weaponAttackSpeed = 1.5,
	weaponDamageType = "ENERGY", -- ELECTRICITY, KINETIC, etc
	weaponArmorPiercing = "MEDIUM", -- LIGHT, NONE, MEDIUM, HEAVY

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

	lootGroup = "0,1,3,4,11,15,19,33,49,50,102", -- Group it belongs to for loot

	tame = 0,  -- Likely hood to be tamed

	milk = 0,

	boneType = "",
	boneMax = 0,

	hideType = "",
	hideMax = 0,

	meatType = "",
	meatMax = 0,

	skills = { "dwbAttack40", "dwbAttack41", "dwbAttack42", "dwbAttack43", "dwbAttack44", "dwbAttack45", "dwbAttack46", "dwbAttack47", "dwbAttack48", "dwbAttack49", "dwbAttack50", "dwbAttack51"  },
	respawnTimer = 120,

	behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(blackSunAssassinDWB, 3627888108) --  Add to Global Table
