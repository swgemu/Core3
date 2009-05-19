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
geonosianEnhancedKliknik = Creature:new {
  objectName = "geonosianEnhancedKliknik",  -- Lua Object Name
  creatureType = "ANIMAL",
  
  gender = "",

  stfName = "Enhanced Kliknik",
  objectCRC = 2954898028, 
  socialGroup = "self",
  
  level = 98,
  

  combatFlags = ATTACKABLE_FLAG + ENEMY_FLAG + AGGRESSIVE_FLAG,

  healthMax = 38000,
  healthMin = 31000,
  strength = 5000,
  constitution = 5000,

  actionMax = 38000,
  actionMin = 31000,
  quickness = 5000,
  stamina = 5000,

  mindMax = 38000,
  mindMin = 31000,
  focus = 5000,
  willpower = 5000,

  height = 1, -- Size of creature
  armor = 2, -- 0 = None; 1 = Light; 2 = Medium; 3 = Heavy
  kinetic = 40,
  energy = 40,
  electricity = 10,
  stun = 10,
  blast = 10,
  heat = 95,
  cold = -1,
  acid = 10,
  lightsaber = 0,

  accuracy = 300,

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

  weapon = "object/weapon/ranged/rifle/shared_rifle_flame_thrower.iff", -- File path to weapon -> object\xxx\xxx\xx
  weaponName = "Creature Defualt", -- Name ex. 'a Vibrolance'
  weaponTemp = "rifle_flame_thrower", -- Weapon Template ex. 'lance_vibrolance'
  weaponClass = "UnarmedMeleeWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
  weaponEquipped = 1,
  weaponMinDamage = 450,
  weaponMaxDamage = 800,
  weaponAttackSpeed = 1,
  weaponDamageType = "HEAT", -- ELECTRICITY, KINETIC, etc
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

	tame = 0,
	datapadItemCRC = 0,
	mountCRC = 0,
	mountSpeed = 0,
	mountAcceleration = 0,

  milk = 0,

  boneType = "",
  boneMax = 0,

  hideType = "hide_scaley_yavin4",
  hideMax = 40,

  meatType = "meat_carnivore_yavin4",
  meatMax = 45,

  skills = { "geonosianEnhancedKliknikAttack1", "geonosianEnhancedKliknikAttack2",  "geonosianEnhancedKliknikAttack3", "geonosianEnhancedKliknikAttack4", "geonosianEnhancedKliknikAttack5" },
  respawnTimer = 300,

  behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(geonosianEnhancedKliknik, 2954898028) --  Add to Global Table
