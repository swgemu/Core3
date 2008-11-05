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
jabbaEnforcer = Creature:new {
      objectName = "jabbaEnforcer",  -- Lua Object Name
      creatureType = "NPC",
      faction = "Jabba",
      gender = "",

      name = "Jabba's enforcer",
      objectCRC = 3315833874, 
      socialGroup = "Jabba",
      named = FALSE, 

      level = 46,
      

      combatFlags = ATTACKABLE_FLAG + ENEMY_FLAG,

      healthMax = 3500,
      healthMin = 2900,
      strength = 500,
      constitution = 500,

      actionMax = 3500,
      actionMin = 2900,
      quickness = 500,
      stamina = 500,

      mindMax = 3500,
      mindMin = 2900,
      focus = 500,
      willpower = 500,

      height = 1, -- Size of creature
      armor = 1, -- 0 = None; 1 = Light; 2 = Medium; 3 = Heavy
      kinetic = 0,
      energy = 0,
      electricity = 0,
      stun = -1,
      blast = 0,
      heat = 0,
      cold = 0,
      acid = 0,
      lightsaber = 0,

      accuracy = 300,

      healer = 0,

      pack = 1,
      herd = 0,
      stalker = 0,
      killer = 0,
      aggressive = 0,
      invincible = 0, 

	  meleeDefense = 1,  
	  rangedDefense = 1,

      attackCreatureOnSight = "", -- Enter socialGroups 

      weapon = "object/weapon/melee/baton/shared_baton_stun.iff", -- File path to weapon -> object\xxx\xxx\xx
      weaponName = "a Stun Baton", -- Name ex. 'a Vibrolance'
      weaponTemp = "baton_stun", -- Weapon Template ex. 'lance_vibrolance'
      weaponClass = "OneHandedMeleeWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
      weaponEquipped = 1,
      weaponMinDamage = 175,
      weaponMaxDamage = 250,
      weaponAttackSpeed = 1.5,
      weaponDamageType = "STUN", -- ELECTRICITY, KINETIC, etc
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

      lootGroup = "0,11,15,19,33,39", -- Group it belongs to for loot

      tame = 0,  -- Likely hood to be tamed

      milk = 0,

      boneType = "",
      boneMax = 0,

      hideType = "",
      hideMax = 0,

      meatType = "",
      meatMax = 0,

      skills = { "jabbaAttack40", "jabbaAttack41", "jabbaAttack42" },
      respawnTimer = 300,

      behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(jabbaEnforcer, 3315833874) --  Add to Global Table
