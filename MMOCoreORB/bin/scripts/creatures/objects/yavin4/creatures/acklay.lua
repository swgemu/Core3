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
acklay = Creature:new {
      objectName = "acklay",  -- Lua Object Name
      creatureType = "ANIMAL",
      faction = "Acklay",
      gender = "male",

      stfName = "Acklay Ravager",
      objectCRC = 258679778, 
      socialGroup = "Acklay",
      named = FALSE, 

      level = 1024,
      xp = 28549,

      combatFlags = ATTACKABLE_FLAG + ENEMY_FLAG,

      healthMax = 4500000,
      healthMin = 3000000,
      strength = 500000,
      constitution = 500000,

      actionMax = 4500000,
      actionMin = 3000000,
      quickness = 500000,
      stamina = 500000,

      mindMax = 4500000,
      mindMin = 3000000,
      focus = 500000,
      willpower = 500000,

      height = 5, -- Size of creature
      armor = 3, -- 0 = None; 1 = Light; 2 = Medium; 3 = Heavy
      kinetic = 95,
      energy = 99,
      electricity = 95,
      stun = 95,
      blast = 95,
      heat = 95,
      cold = 95,
      acid = 99,
      lightsaber = 0,

      accuracy = 300,

      healer = 0,

      pack = 0,
      herd = 0,
      stalker = 0,
      killer = 1,
      aggressive = 1,
      invincible = 0,

      attackCreatureOnSight = "", -- Enter socialGroups 

      weapon = "object/weapon/melee/baton/shared_baton_gaderiffi.iff", -- File path to weapon -> object\xxx\xxx\xx
      weaponName = "a Gaderiffi", -- Name ex. 'a Vibrolance'
      weaponTemp = "shared_baton_gaderiffi", -- Weapon Template ex. 'lance_vibrolance'
      weaponClass = "OneHandedMeleeWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
      weaponEquipped = 0,
      weaponMinDamage = 550,
      weaponMaxDamage = 950,
      weaponAttackSpeed = 1.5,
      weaponDamageType = "KINETIC", -- ELECTRICITY, KINETIC, etc
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

      lootGroup = "0,11,5,19,21,33,34,39,40,46,47,49,50", -- Group it belongs to for loot

      tame = 0,  -- Likely hood to be tamed

      milk = 0,

      boneType = "bone_mammal_yavin4",
      boneMax = 675,

      hideType = "hide_scaley_yavin4",
      hideMax = 750,

      meatType = "meat_insect_yavin4",
      meatMax = 1250,

      skills = { "acklayAttack1", "acklayAttack2", "acklayAttack3", "acklayAttack4", "acklayAttack5", "acklayAttack6", "acklayAttack7", "acklayAttack8", "acklayAttack9", "acklayAttack10" },
      respawnTimer = 9000,

      behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(acklay, 258679778) --  Add to Global Table
