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

imperialStormTrooperCommando = Creature:new {
	objectName = "imperialStormTrooperCommando",  -- Lua Object Name
	creatureType = "NPC",
	faction = "imperial", 
	factionPoints = 20,
	gender = "",

	speciesName = "crackdown_storm_commando",
    stfName = "mob/creature_names",
	objectCRC = 3037629485, 
	socialGroup = "imperial",
	level = 29,
	

	combatFlags = 0,

	healthMax = 9900,
	healthMin = 8100,
	strength = 0,
	constitution = 0,

	actionMax = 9900,
	actionMin = 8100,
	quickness = 0,
	stamina = 0,

	mindMax = 9900,
	mindMin = 8100,
	focus = 0,
	willpower = 0,

	height = 1, -- Size of creature
	armor = 2, -- 0 = None; 1 = Light; 2 = Medium; 3 = Heavy
	kinetic = 30,
	energy = 30,
	electricity = 30,
	stun = 0,
	blast = 30,
	heat = 65,
	cold = 30,
	acid = 0,
	lightsaber = 0,

	accuracy = 0,

	healer = 0,

	pack = 1,
	herd = 0,
	stalker = 1,
	killer = 1,
	aggressive = 0,
	invincible = 0,
	
	meleeDefense = 1,
	rangedDefense = 1,
	
	randomMovement = 0,

	attackCreatureOnSight = "", -- Enter socialGroups 

	weapon = "object/weapon/ranged/rifle/shared_rifle_flame_thrower.iff", -- File path to weapon -> object\xxx\xxx\xx
	weaponName = "Imperial Flame Thrower", -- Name ex. 'a Vibrolance'
	weaponTemp = "rifle_flame_thrower", -- Weapon Template ex. 'lance_vibrolance'
	weaponClass = "HeavyRangedWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
	weaponEquipped = 1,
	weaponMinDamage = 250,
	weaponMaxDamage = 400,
	weaponAttackSpeed = 4.9,
	weaponDamageType = "HEAT", -- ELECTRICITY, KINETIC, etc
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

	lootGroup = "0,11,15,19,33,42", -- Group it belongs to for loot

	tame = 0,  -- Likely hood to be tamed

	milk = 0,

	boneType = "",
	boneMax = 0,

	hideType = "",
	hideMax = 0,

	meatType = "",
	meatMax = 0,

	skills = { "imperialStormTrooperCommandoAttack1", "imperialStormTrooperCommandoAttack2", "imperialStormTrooperCommandoAttack3", "imperialStormTrooperCommandoAttack4" },
	respawnTimer = 60,

	behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(imperialStormTrooperCommando, 3037629485) --  Add to Global Table
