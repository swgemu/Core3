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
grondaElder = Creature:new {
	objectName = "grondaElder",  -- Lua Object Name
	creatureType = "ANIMAL",
	gender = "",

	speciesName = "gronda_elder",
	stfName = "mob/creature_names",
	objectCRC = 2380349390, 
	socialGroup = "Gronda",
	level = 33,

	combatFlags = ATTACKABLE_FLAG + ENEMY_FLAG,

	healthMax = 10200,
	healthMin = 8400,
	strength = 0,
	constitution = 0,

	actionMax = 10200,
	actionMin = 8400,
	quickness = 0,
	stamina = 0,

	mindMax = 10200,
	mindMin = 8400,
	focus = 0,
	willpower = 0,

	height = 1, -- Size of creature
	armor = 1, -- 0 = None; 1 = Light; 2 = Medium; 3 = Heavy
	kinetic = 60,
	energy = 0,
	electricity = 0,
	stun = 25,
	blast = 80,
	heat = 0,
	cold = 0,
	acid = -1,
	lightsaber = 0,

	accuracy = 0,

	healer = 0,

	pack = 1,
	herd = 1,
	stalker = 0,
	killer = 1,
	aggressive = 0,
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

	lootGroup = "0", -- Group it belongs to for loot

	tame = 0,  -- Likely hood to be tamed

	milk = 0,

	boneType = "bone_mammal_corellia",
	boneMax = 180,

	hideType = "hide_leathery_corellia",
	hideMax = 270,

	meatType = "meat_carnivore_corellia",
	meatMax = 360,

	--skills = { " Stun attack", "", "" }
	skills = { "grondaAttack1" },
	respawnTimer = 60,

	behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(grondaElder, 2380349390) --  Add to Global Table
