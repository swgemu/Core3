--Copyright (C) 2007 <SWGEmu>
 
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

imperialAtAt = Creature:new {
	objectName = "imperialAtAt", -- name of the lua Object
	creatureType = "NPC",
    faction = "imperial",
    gender = "",
	
	stfName = "an AT-AT",
	objectCRC = 4274898142,
	socialGroup = "imperial",
	named = TRUE, 
	
	level = 500,
	xp = 10000,
	
	combatFlags = 0,
	
	healthMax = 1200000,
    healthMin = 1000000,
    strength = 50000,
    constitution = 50000,

    actionMax = 1200000,
    actionMin = 1000000,
    quickness = 50000,
    stamina = 50000,

    mindMax = 1200000,
    mindMin = 1000000,
    focus = 50000,
    willpower = 50000,	
	
	height = 1,
	armor = 3, -- from http://web.archive.org/web/20050513205858/http://swg.allakhazam.com/db/bestiary.html?swgbeast=3736
	kinetic = 90,
	energy = 90,
	electricity = 90,
	stun = 100,
	blast = 10,
	heat = 90,
	cold = 90,
	acid = 90,
	lightSaber = 0,	
	
	accuracy = 300,

	healer = 0,
	pack = 1,
	herd = 0,
	stalker = 0,
	killer = 1,
	aggressive = 0,
	invincible = 0, 

	  meleeDefense = 1,  
	  rangedDefense = 1,

	attackCreatureOnSight = "", -- Enter socialGroups 

	weapon = "object/weapon/ranged/vehicle/shared_vehicle_atst_ranged.iff", -- File path to weapon -> object\xxx\xxx\xx
	weaponName = "Imperial Cannon", -- Name ex. 'a Vibrolance'
	weaponTemp = "vehicle_atst_ranged", -- Weapon Template ex. 'lance_vibrolance'
	weaponClass = "RifleRangedWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
	weaponEquipped = 1,
	weaponMinDamage = 450,
	weaponMaxDamage = 850,
	weaponAttackSpeed = 1,
	weaponDamageType = "BLAST", -- ELECTRICITY, KINETIC, etc
	weaponArmorPiercing = "HEAVY", -- LIGHT, NONE, MEDIUM, HEAVY

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

	lootGroup = "0,11,15,19,34,39,40", -- Group it belongs to for lootelongs to for loot

	tame = 0,  -- Likely hood to be tamed

	milk = 0,

	boneType = "",
	boneMax = 0,

	hideType = "",
    hideMax = 0,

    meatType = "",
    meatMax = 0,

	skills = { "atAttack1", "atAttack2", "atAttack3", "atAttack4", "atAttack5", "atAttack6", "atAttack7", "atAttack8", "atAttack9", "atAttack10", "atAttack12" },
	respawnTimer = 3600, 
	
	behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(imperialAtAt, 4274898142) --- Add to global creature table
