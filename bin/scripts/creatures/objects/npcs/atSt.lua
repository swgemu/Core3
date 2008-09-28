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
atSt = Creature:new {
	objectName = "atSt", -- name of the lua Object
	creatureType = "NPC",
    faction = "Imperial",
    gender = "",
	
	stfName = "an AT-ST",
	objectCRC = 2128352281,
	socialGroup = "Imperial",
	named = TRUE, 
	
	level = 100,	
	xp = 10000,
	
	combatFlags = ATTACKABLE_FLAG + ENEMY_FLAG + AGGRESSIVE_FLAG,
	
	healthMax = 55000,
    healthMin = 50000,
    strength = 5000,
    constitution = 5000,

    actionMax = 55000,
    actionMin = 50000,
    quickness = 5000,
    stamina = 5000,

    mindMax = 55000,
    mindMin = 50000,
    focus = 5000,
    willpower = 5000,	

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

	attackCreatureOnSight = "", -- Enter socialGroups 

	weapon = "object/weapon/ranged/vehicle/shared_vehicle_atst_ranged.iff", -- File path to weapon -> object\xxx\xxx\xx
	weaponName = "Imperial Cannon", -- Name ex. 'a Vibrolance'
	weaponTemp = "vehicle_atst_ranged", -- Weapon Template ex. 'lance_vibrolance'
	weaponClass = "RifleRangedWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
	weaponEquipped = 1,
	weaponMinDamage = 350,
	weaponMaxDamage = 500,
	weaponAttackSpeed = 1.0,
	weaponDamageType = "BLAST", -- ELECTRICITY, KINETIC, etc
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

	lootGroup = "0,11,15,19,21,33,34", -- Group it belongs to for loot

	tame = 0,  -- Likely hood to be tamed

	milk = 0,

	boneType = "",
	boneMax = 0,

	hideType = "",
	hideMax = 0,

	meatType = "",
	meatMax = 0,

	skills = { "stormTrooperAttack2" },
	respawnTimer = 1800, 
	
	behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(atSt, 2128352281) --- Add to global creature table
