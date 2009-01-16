--Copyright (C) 2009 <SWGEmu>


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
nightsisterRanger = Creature:new {
	objectName = "nightsisterRanger",  -- Lua Object Name
	creatureType = "NPC",
	faction = "nightsister", 
	factionPoints = 20,
	gender = "",

	speciesName = "nightsister_ranger",
	stfName = "mob/creature_names", 
	objectCRC = 3628672450, 
	socialGroup = "nightsister",
	level = 78,

	combatFlags = ATTACKABLE_FLAG + ENEMY_FLAG + AGGRESSIVE_FLAG,

	healthMax = 15000,
	healthMin = 12000,
	strength = 3000,
	constitution = 3000,

	actionMax = 15000,
	actionMin = 12000,
	quickness = 3000,
	stamina = 3000,

	mindMax = 15000,
	mindMin = 12000,
	focus = 3000,
	willpower = 3000,

	height = 1, -- Size of creature
	armor = 1, -- 0 = None; 1 = Light; 2 = Medium; 3 = Heavy
	kinetic = 30,
	energy = 30,
	electricity = 100,
	stun = 100,
	blast = 30,
	heat = 100,
	cold = 100,
	acid = 100,
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

	weapon = "object/weapon/melee/baton/shared_baton_gaderiffi.iff", -- File path to weapon -> object\xxx\xxx\xx
	weaponName = "a Gaderiffi", -- Name ex. 'a Vibrolance'
	weaponTemp = "baton_gaderiffi", -- Weapon Template ex. 'lance_vibrolance'
	weaponClass = "OneHandedMeleeWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
	weaponEquipped = 1,
	weaponMinDamage = 164,
	weaponMaxDamage = 459,
	weaponAttackSpeed = 1,
	weaponDamageType = "KINETIC", -- ELECTRICITY, KINETIC, etc
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

	lootGroup = "0,1,3,4,11,15,19,30,99", -- Group it belongs to for loot

	tame = 0,  -- Likely hood to be tamed

	milk = 0,

	boneType = "",
	boneMax = 0,

	hideType = "",
	hideMax = 0,

	meatType = "",
	meatMax = 0,

	skills = { "nightsisterAttack40", "nightsisterAttack41", "nightsisterAttack42", "nightsisterAttack43", "nightsisterAttack44", "nightsisterAttack45", "nightsisterAttack46", "nightsisterAttack47", "nightsisterAttack48", "nightsisterAttack49", "nightsisterAttack50", "nightsisterAttack51" },
	respawnTimer = 300,

	behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(nightsisterRanger, 3628672450) --  Add to Global Table
