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
rebelSurfaceMarshal = Creature:new {
	objectName = "rebelSurfaceMarshal",  -- Lua Object Name
	creatureType = "NPC",
	faction = "rebel", 
	factionPoints = 20,
	gender = "",

	speciesName = "rebel_surface_marshal",
	stfName = "mob/creature_names", 
	objectCRC = 7469172, 
	socialGroup = "rebel",	

	level = 30,	

	combatFlags = 0,

	healthMax = 10200,
	healthMin = 8400,
	strength = 1000,
	constitution = 1000,

	actionMax = 10200,
	actionMin = 8400,
	quickness = 1000,
	stamina = 1000,

	mindMax = 10200,
	mindMin = 8400,
	focus = 1000,
	willpower = 1000,

	height = 1, -- Size of creature
	armor = 1, -- 0 = None; 1 = Light; 2 = Medium; 3 = Heavy
	kinetic = 0,
	energy = 0,
	electricity = 40,
	stun = -1,
	blast = 0,
	heat = 40,
	cold = -1,
	acid = -1,
	lightsaber = 0,

	accuracy = 360,

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

	--Officer Class:
	weapon = "object/weapon/ranged/rifle/shared_rifle_t21.iff", -- File path to weapon -> object\xxx\xxx\xx
	weaponName = "officer's t21", -- Name ex. 'a Vibrolance'
	weaponTemp = "rifle_t21", -- Weapon Template ex. 'lance_vibrolance'
	weaponClass = "RifleRangedWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
	weaponEquipped = 1,
	weaponMinDamage = 290,
	weaponMaxDamage = 300,
	weaponAttackSpeed = 2,
	weaponDamageType = "ENERGY", -- ELECTRICITY, KINETIC, etc
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

	lootGroup = "0,1,3,4,11,15,19,33,97,98", -- Group it belongs to for loot

	tame = 0,  -- Likely hood to be tamed

	milk = 0,

	boneType = "",
	boneMax = 0,

	hideType = "",
	hideMax = 0,

	meatType = "",
	meatMax = 0,

	skills = { "rebelSurfaceMarshalAttack1", "rebelSurfaceMarshalAttack2", "rebelSurfaceMarshalAttack3" },
	respawnTimer = 300,

	behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(rebelSurfaceMarshal, 7469172) --  Add to Global Table
