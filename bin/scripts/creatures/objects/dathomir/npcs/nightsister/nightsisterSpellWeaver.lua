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
nightsisterSpellWeaver = Creature:new {
	objectName = "nightsisterSpellWeaver",  -- Lua Object Name
	creatureType = "NPC",
	faction = "nightsister", 
	factionPoints = 20,
	gender = "",

	speciesName = "nightsister_spell_weaver",
	stfName = "mob/creature_names", 
	objectCRC = 2291851149, 
	socialGroup = "nightsister",
	level = 107,

	combatFlags = ATTACKABLE_FLAG + ENEMY_FLAG + AGGRESSIVE_FLAG,

	healthMax = 30000,
	healthMin = 24000,
	strength = 500,
	constitution = 500,

	actionMax = 30000,
	actionMin = 24000,
	quickness = 500,
	stamina = 500,

	mindMax = 30000,
	mindMin = 24000,
	focus = 500,
	willpower = 500,

	height = 1, -- Size of creature
	armor = 2, -- 0 = None; 1 = Light; 2 = Medium; 3 = Heavy
	kinetic = 15,
	energy = 100,
	electricity = 100,
	stun = 100,
	blast = 15,
	heat = 100,
	cold = 100,
	acid = 100,
	lightsaber = 0,

	accuracy = 370,

	healer = 1,

	pack = 1,
	herd = 0,
	stalker = 0,
	killer = 1,
	aggressive = 1,
	invincible = 0, 

	meleeDefense = 1,  
	rangedDefense = 1,

	attackCreatureOnSight = "", -- Enter socialGroups 

	weapon = "object/weapon/melee/polearm/shared_lance_vibrolance.iff", -- File path to weapon -> object\xxx\xxx\xx
	weaponName = "a Vibrolance", -- Name ex. 'a Vibrolance'
	weaponTemp = "lance_vibrolance", -- Weapon Template ex. 'lance_vibrolance'
	weaponClass = "PolearmMeleeWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
	weaponEquipped = 1,
	weaponMinDamage = 300,
	weaponMaxDamage = 850,
	weaponAttackSpeed = 1.5,
	weaponDamageType = "ELECTRICITY", -- ELECTRICITY, KINETIC, etc
	weaponArmorPiercing = "LIGHT", -- LIGHT, NONE, MEDIUM, HEAVY

	alternateWeapon = "object/weapon/melee/polearm/shared_polearm_vibro_axe.iff", -- File path to weapon -> object\xxx\xxx\xx
	alternateWeaponName = "a Long Vibro Axe", -- Name ex. 'a Vibrolance'
	alternateWeaponTemp = "lance_vibro_axe", -- Weapon Template ex. 'lance_vibrolance'
	alternateWeaponClass = "PolearmMeleeWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
	alternateWeaponEquipped = 1,
	alternateWeaponMinDamage = 350,
	alternateWeaponMaxDamage = 800,
	alternateWeaponAttackSpeed = 1.5,
	alternateWeaponDamageType = "KINETIC", -- ELECTRICITY, KINETIC, etc
	alternateWeaponArmorPiercing = "LIGHT", -- LIGHT, NONE, MEDIUM, HEAVY

	internalNPCDamageModifier = 0.3, -- Damage Modifier to other NPC's

	lootGroup = "0,1,3,4,11,19,30,33,99", -- Group it belongs to for loot

	tame = 0,  -- Likely hood to be tamed

	milk = 0,

	boneType = "",
	boneMax = 0,

	hideType = "",
	hideMax = 0,

	meatType = "",
	meatMax = 0,

	skills = { "nightsisterAttack20", "nightsisterAttack21", "nightsisterAttack22", "nightsisterAttack23", "nightsisterAttack24",  "nightsisterAttack25", "nightsisterAttack26", "nightsisterAttack27", "nightsisterAttack28", "nightsisterAttack29", "nightsisterAttack30", "nightsisterAttack31" },
	respawnTimer = 300,

	behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(nightsisterSpellWeaver, 2291851149) --  Add to Global Table
