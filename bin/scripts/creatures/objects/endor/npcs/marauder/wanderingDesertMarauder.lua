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
wanderingDesertMarauder = Creature:new {
	objectName = "wanderingDesertMarauder",  -- Lua Object Name
	creatureType = "NPC",
	faction = "marauder", 
	factionPoints = 20,
	gender = "",

	speciesName = "wandering_desert_marauder",
	stfName = "mob/creature_names", 
	objectCRC = 4103644702, 
	socialGroup = "marauder",
	

	level = 47,
	

	combatFlags = ATTACKABLE_FLAG + ENEMY_FLAG + AGGRESSIVE_FLAG,

	healthMax = 12200,
	healthMin = 10000,
	strength = 0,
	constitution = 0,

	actionMax = 12200,
	actionMin = 10000,
	quickness = 0,
	stamina = 0,

	mindMax = 12200,
	mindMin = 10000,
	focus = 0,
	willpower = 0,

	height = 1, -- Size of creature
	armor = 1, -- 0 = None; 1 = Light; 2 = Medium; 3 = Heavy
	kinetic = 25,
	energy = 20,
	electricity = 0,
	stun = -1,
	blast = 0,
	heat = 0,
	cold = -1,
	acid = 0,
	lightsaber = 0,

	accuracy = 300,

	healer = 0,

	pack = 1,
	herd = 0,
	stalker = 0,
	killer = 1,
	aggressive = 1,
	invincible = 0, 

	meleeDefense = 1,  
	rangedDefense = 1,

	attackCreatureOnSight = "", -- Enter socialGroups 

	weapon = "object/weapon/ranged/pistol/shared_pistol_dl44.iff", -- File path to weapon -> object\xxx\xxx\xx
	weaponName = "DL44 Pistol", -- Name ex. 'a Vibrolance'
	weaponTemp = "pistol_dl44", -- Weapon Template ex. 'lance_vibrolance'
	weaponClass = "PistolRangedWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
	weaponEquipped = 1,
	weaponMinDamage = 200,
	weaponMaxDamage =400,
	weaponAttackSpeed = 2,
	weaponDamageType = "ENERGY", -- ELECTRICITY, KINETIC, etc
	weaponArmorPiercing = "LIGHT", -- LIGHT, NONE, MEDIUM, HEAVY

	alternateWeapon = "object/weapon/melee/baton/shared_baton_gaderiffi.iff", -- File path to weapon -> object\xxx\xxx\xx
	alternateWeaponName = "a Gaderiffi", -- Name ex. 'a Vibrolance'
	alternateWeaponTemp = "baton_gaderiffi", -- Weapon Template ex. 'lance_vibrolance'
	alternateWeaponClass = "OneHandedMeleeWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
	alternateWeaponEquipped = 1,
	alternateWeaponMinDamage = 100,
	alternateWeaponMaxDamage = 250,
	alternateWeaponAttackSpeed = 3,
	alternateWeaponDamageType = "KINETIC", -- ELECTRICITY, KINETIC, etc
	alternateWeaponArmorPiercing = "NONE", -- LIGHT, NONE, MEDIUM, HEAVY

	internalNPCDamageModifier = 0.3, -- Damage Modifier to other NPC's

	lootGroup = "0", -- Group it belongs to for loot

	tame = 0,  -- Likely hood to be tamed

	milk = 0,

	boneType = "",
	boneMax = 0,

	hideType = "",
	hideMax = 0,

	meatType = "",
	meatMax = 0,

	skills = { "marauderAttack40", "marauderAttack41", "marauderAttack42", "marauderRangedAttack1", "marauderRangedAttack2", "marauderRangedAttack3" },
	respawnTimer = 300,

	behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(wanderingDesertMarauder, 4103644702) --  Add to Global Table
