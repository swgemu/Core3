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
moDarkJediMaster = Creature:new {
	objectName = "moDarkJediMaster",  -- Lua Object Name
	creatureType = "NPC",
	gender = "",

	speciesName = "dark_jedi_master",
	stfName = "mob/creature_names", 
	objectCRC = 2005105485, 
	socialGroup = "sith",
	level = 291,
	
	combatFlags = ATTACKABLE_FLAG + ENEMY_FLAG + AGGRESSIVE_FLAG,

	healthMax = 392000,
	healthMin = 321000,
	strength = 50000,
	constitution = 50000,

	actionMax = 392000,
	actionMin = 321000,
	quickness = 50000,
	stamina = 50000,

	mindMax = 392000,
	mindMin = 321000,
	focus = 50000,
	willpower = 50000,

	height = 1, -- Size of creature
	armor = 3, -- Just a guess
	kinetic = 90,
	energy = 90,
	electricity = 90,
	stun = 90,
 	blast = 90,
 	heat = 90,
 	cold = 90,
 	acid = 90,
 	lightSaber = 0, 

	accuracy = 400,

	healer = 0,

	pack = 1,
	herd = 0,
	stalker = 0,
	killer = 1,
	ferocity = 0,
	aggressive = 1,
	invincible = 0, 
	  
    meleeDefense = 1,  	  
    rangedDefense = 1,

	attackCreatureOnSight = "", -- Enter socialGroups 

	weapon = "object/weapon/melee/polearm/crafted_saber/shared_sword_lightsaber_polearm_s2_gen4.iff", -- File path to weapon -> object\xxx\xxx\xx
	weaponName = "Master Saber", -- Name ex. 'a Vibrolance'
	weaponTemp = "sword_lightsaber_polearm_s2_gen4", -- Weapon Template ex. 'lance_vibrolance'
	weaponClass = "PolearmJediWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
	weaponEquipped = 1,
	weaponMinDamage = 1800,
	weaponMaxDamage = 3310,
	weaponAttackSpeed = 2,
	weaponDamageType = "LIGHTSABER", -- ELECTRICITY, KINETIC, etc
	weaponArmorPiercing = "MEDIUM", -- LIGHT, NONE, MEDIUM, HEAVY

	alternateWeapon = "object/weapon/melee/2h_sword/crafted_saber/shared_sword_lightsaber_two_handed_s9_gen4.iff", -- File path to weapon -> object\xxx\xxx\xx
	alternateWeaponName = "Master Saber", -- Name ex. 'a Vibrolance'
	alternateWeaponTemp = "sword_lightsaber_two_handed_s9_gen4", -- Weapon Template ex. 'lance_vibrolance'
	alternateWeaponClass = "TwoHandedJediWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
	alternateWeaponEquipped = 1,
	alternateWeaponMinDamage = 1800,
	alternateWeaponMaxDamage = 3310,
	alternateWeaponAttackSpeed = 1,
	alternateWeaponDamageType = "LIGHTSABER", -- ELECTRICITY, KINETIC, etc
	alternateWeaponArmorPiercing = "MEDIUM", -- LIGHT, NONE, MEDIUM, HEAVY

	internalNPCDamageModifier = 0.3, -- Damage Modifier to other NPC's

	lootGroup = "0,1,3,11,15,19,33,39,40,100", -- Group it belongs to for loot

	tame = 0,
	datapadItemCRC = 0,
	mountCRC = 0,
	mountSpeed = 0,
	mountAcceleration = 0,

	milk = 0,

	boneType = "",
	boneMax = 0,

	hideType = "",
	hideMax = 0,

	meatType = "",
	meatMax = 0,

	skills = { "oneHandedJediAttack1", "oneHandedJediAttack2", "oneHandedJediAttack3", "oneHandedJediAttack4", "oneHandedJediAttack5", "oneHandedJediAttack6", "oneHandedJediAttack7", "oneHandedJediAttack8" },
	respawnTimer = 432000,

	behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(moDarkJediMaster, 2005105485) --  Add to Global Table
