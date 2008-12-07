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
kraytDragonAncient = Creature:new {
	objectName = "kraytDragonAncient",  -- Lua Object Name
	creatureType = "ANIMAL",
	faction = "Krayt Dragon",
	gender = "",

	speciesName = "krayt_dragon_ancient",
	stfName = "mob/creature_names",
	objectCRC = 1238991743, 
	socialGroup = "Krayt Dragon",
	

	level = 336,
	

	combatFlags = ATTACKABLE_FLAG + ENEMY_FLAG + AGGRESSIVE_FLAG,

	healthMax = 501000,
	healthMin = 410000,
	strength = 100000,
	constitution = 100000,

	actionMax = 501000,
	actionMin = 410000,
	quickness = 100000,
	stamina = 100000,

	mindMax = 501000,
	mindMin = 410000,
	focus = 100000,
	willpower = 100000,

	height = 3, -- Size of creature
	
	armor = 3, -- 0 = None; 1 = Light; 2 = Medium; 3 = Heavy
	kinetic = 95,
	energy = 95,
	electricity = 95,
	stun = 95,
	blast = 95,
	heat = 95,
	cold = 65,
	acid = 95,
	lightsaber = 0,

	accuracy = 300,

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

	weapon = "", -- File path to weapon -> object\xxx\xxx\xx
	weaponName = "", -- Name ex. 'a Vibrolance'
	weaponTemp = "", -- Weapon Template ex. 'lance_vibrolance'
	weaponClass = "", -- Weapon Class ex. 'PolearmMeleeWeapon'
	weaponEquipped = 0,
	weaponMinDamage = 0,
	weaponMaxDamage = 0,
	weaponAttackSpeed = 0,
	weaponDamageType = "", -- ELECTRICITY, KINETIC, etc
	weaponArmorPiercing = "", -- LIGHT, NONE, MEDIUM, HEAVY

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

	lootGroup = "0,11,15,19,33,39,40,51,52,96", -- Group it belongs to for loot

	tame = 0,  -- Likely hood to be tamed

	milk = 0,

	boneType = "bone_mammal_tatooine",
	boneMax = 905,

	hideType = "hide_bristley_tatooine",
	hideMax = 950,

	meatType = "meat_carnivore_tatooine",
	meatMax = 1700,
	skills = { "kraytAttack1", "kraytAttack2", "kraytAttack3", "kraytAttack4", "kraytAttack5", "kraytAttack6", "kraytAttack7" },	
	respawnTimer = 3600, 

	behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(kraytDragonAncient, 1238991743) -- Add to Global Table
