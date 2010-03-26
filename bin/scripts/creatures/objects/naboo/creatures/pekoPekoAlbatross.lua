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
pekoPekoAlbatross = Creature:new {
	objectName = "pekoPekoAlbatross",  -- Lua Object Name
	creatureType = "ANIMAL",
	gender = "",

	speciesName = "peko_peko_albatross",
	stfName = "mob/creature_names",
	objectCRC = 1032288412, 
	socialGroup = "Peko Peko",
	level = 155,
	
	combatFlags = ATTACKABLE_FLAG + ENEMY_FLAG,

	healthMax = 91000,
	healthMin = 74000,
	strength = 10000,
	constitution = 10000,

	actionMax = 91000,
	actionMin = 74000,
	quickness = 10000,
	stamina = 10000,

	mindMax = 91000,
	mindMin = 74000,
	focus = 10000,
	willpower = 10000,

	height = 2.3, -- Size of creature
	armor = 2, -- 0 = None; 1 = Light; 2 = Medium; 3 = Heavy
	kinetic = 100,
	energy = 80,
	electricity = 90,
	stun = 25,
	blast = 30,
	heat = 80,
	cold = 80,
	acid = 25,
	lightsaber = 0,

	accuracy = 380,

	healer = 0,

	pack = 1,
	herd = 0,
	stalker = 0,
	killer = 1,
	ferocity = 0,
	aggressive = 0,
	invincible = 0, 

	meleeDefense = 1, 
	rangedDefense = 1,

	attackCreatureOnSight = "", -- Enter socialGroups 

	weapon = "object/weapon/creature/shared_creature_default_weapon.iff", -- File path to weapon -> object\xxx\xxx\xx
      	weaponName = "Creature Defualt", -- Name ex. 'a Vibrolance'
      	weaponTemp = "creature_default_weapon", -- Weapon Template ex. 'lance_vibrolance'
     	weaponClass = "UnarmedMeleeWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
      	weaponEquipped = 0,
      	weaponMinDamage = 945,
      	weaponMaxDamage = 1600,
      	weaponAttackSpeed = 2,
      	weaponDamageType = "KINETIC", -- ELECTRICITY, KINETIC, etc
      	weaponArmorPiercing = "NONE", -- LIGHT, NONE, MEDIUM, HEAVY

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

	boneType = "bone_avian_naboo",
	boneMax = 100,

	hideType = "hide_wooly_naboo",
	hideMax = 120,

	meatType = "meat_avian_naboo",
	meatMax = 400,

	skills = { "pekoPekoAttack5", "pekoPekoAttack6", "pekoPekoAttack7" },
	respawnTimer = 3600,

	behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(pekoPekoAlbatross, 1032288412) --  Add to Global Table
