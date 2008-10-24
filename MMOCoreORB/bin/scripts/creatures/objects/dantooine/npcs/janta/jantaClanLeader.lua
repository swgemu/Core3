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
jantaClanLeader = Creature:new {
      objectName = "jantaClanLeader",  -- Lua Object Name
      creatureType = "NPC",
      faction = "Janta Tnbe",
      gender = "",

      name = "Janta Clan Leader",
      objectCRC = 4083847450, 
      socialGroup = "Janta Tnbe",
      named = FALSE, 

      level = 75,
      xp = 7207,

      combatFlags = ATTACKABLE_FLAG + ENEMY_FLAG,

      healthMax = 15000,
      healthMin = 12000,
      strength = 500,
      constitution = 500,

      actionMax = 15000,
      actionMin = 12000,
      quickness = 500,
      stamina = 500,

      mindMax = 15000,
      mindMin = 12000,
      focus = 500,
      willpower = 500,

      height = 1, -- Size of creature
      armor = 1, -- 0 = None; 1 = Light; 2 = Medium; 3 = Heavy
      kinetic = 0,
      energy = 60,
      electricity = 100,
      stun = -1,
      blast = -1,
      heat = 0,
      cold = 0,
      acid = 0,
      lightsaber = 0,

      accuracy = 300,

      healer = 0,

      pack = 1,
      herd = 1,
      stalker = 0,
      killer = 0,
      aggressive = 0,
      invincible = 0, 

	  meleeDefense = 1,  
	  rangedDefense = 1,

      attackCreatureOnSight = "", -- Enter socialGroups 

      weapon = "object/weapon/melee/polearm/shared_lance_staff_wood_s1.iff", -- File path to weapon -> object\xxx\xxx\xx
      weaponName = "a Wooden Staff", -- Name ex. 'a Vibrolance'
      weaponTemp = "lance_staff_wood_s1", -- Weapon Template ex. 'lance_vibrolance'
      weaponClass = "PolearmMeleeWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
      weaponEquipped = 1,
      weaponMinDamage = 50,
      weaponMaxDamage = 500,
      weaponAttackSpeed = 2,
      weaponDamageType = "KINETIC", -- ELECTRICITY, KINETIC, etc
      weaponArmorPiercing = "NONE", -- LIGHT, NONE, MEDIUM, HEAVY


      alternateWeapon = "object/weapon/melee/knife/shared_knife_stone.iff", -- File path to weapon -> object\xxx\xxx\xx
      alternateWeaponName = "a Stone Knife", -- Name ex. 'a Vibrolance'
      alternateWeaponTemp = "knife_stone", -- Weapon Template ex. 'lance_vibrolance'
      alternateWeaponClass = "OneHandedMeleeWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
      alternateWeaponEquipped = 1,
      alternateWeaponMinDamage = 20,
      alternateWeaponMaxDamage = 250,
      alternateWeaponAttackSpeed = 1,
      alternateWeaponDamageType = "KINETIC", -- ELECTRICITY, KINETIC, etc
      alternateWeaponArmorPiercing = "NONE", -- LIGHT, NONE, MEDIUM, HEAVY


      internalNPCDamageModifier = 0.3, -- Damage Modifier to other NPC's

      lootGroup = "0,11,15,19,33", -- Group it belongs to for lootoot

      tame = 0,  -- Likely hood to be tamed

      milk = 0,

      boneType = "",
      boneMax = 0,

      hideType = "",
      hideMax = 0,

      meatType = "",
      meatMax = 0,

      skills = { "kungaAttack01", "kungaAttack02", "kungaAttack03", "kungaAttack04", "kungaAttack05", "kungaAttack06", "kungaAttack07", "kungaAttack08", "kungaAttack09" }, 
      respawnTimer = 300, 

      behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(jantaClanLeader, 4083847450) --  Add to Global Table
