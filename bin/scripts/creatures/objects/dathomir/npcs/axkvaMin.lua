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
axkvaMin = Creature:new {
      objectName = "axkvaMin",  -- Lua Object Name
      creatureType = "NPC",
      faction = "Nightsister",
      gender = "",

      stfName = "Axkva Min",
      objectCRC = 2853795094, 
      socialGroup = "Nightsister",
      named = TRUE, 

      level = 302,
      xp = 28549,

      combatFlags = ATTACKABLE_FLAG + ENEMY_FLAG + AGGRESSIVE_FLAG,

      healthMax = 471000,
      healthMin = 385000,
      strength = 0,
      constitution = 0,

      actionMax = 471000,
      actionMin = 385000,
      quickness = 0,
      stamina = 0,

      mindMax = 471000,
      mindMin = 385000,
      focus = 0,
      willpower = 0,

      height = 1, -- Size of creature
      armor = 3, -- 0 = None; 1 = Light; 2 = Medium; 3 = Heavy
      kinetic = 100,
      energy = 35,
      electricity = 100,
      stun = 100,
      blast = 35,
      heat = 100,
      cold = 100,
      acid = 100,
      lightsaber = 0,

      accuracy = 300,

      healer = 1,

      pack = 1,
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
      weaponEquipped = 1,
      weaponMinDamage = 800,
      weaponMaxDamage = 1600,
      weaponAttackSpeed = 1.5,
      weaponDamageType = "KINETIC", -- ELECTRICITY, KINETIC, etc
      weaponArmorPiercing = "LIGHT", -- LIGHT, NONE, MEDIUM, HEAVY

      alternateWeapon = "object/weapon/melee/baton/shared_baton_stun.iff", -- File path to weapon -> object\xxx\xxx\xx
      alternateWeaponName = "a Stun Baton", -- Name ex. 'a Vibrolance'
      alternateWeaponTemp = "shared_baton_stun", -- Weapon Template ex. 'lance_vibrolance'
      alternateWeaponClass = "OneHandedMeleeWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
      alternateWeaponEquipped = 1,
      alternateWeaponMinDamage = 900,
      alternateWeaponMaxDamage = 1700,
      alternateWeaponAttackSpeed = 1.5,
      alternateWeaponDamageType = "STUN", -- ELECTRICITY, KINETIC, etc
      alternateWeaponArmorPiercing = "LIGHT", -- LIGHT, NONE, MEDIUM, HEAVY

      internalNPCDamageModifier = 0.3, -- Damage Modifier to other NPC's

      lootGroup = "0,19,21,29,30,31,33,34,39,40", -- Group it belongs to for loot

      tame = 0,  -- Likely hood to be tamed

      milk = 0,

      boneType = "",
      boneMax = 0,

      hideType = "",
      hideMax = 0,

      meatType = "",
      meatMax = 0,

      skills = { "nightsisterAttack20", "nightsisterAttack21", "nightsisterAttack22", "nightsisterAttack23", "nightsisterAttack24",  "nightsisterAttack25", "nightsisterAttack26", "nightsisterAttack27", "nightsisterAttack28", "nightsisterAttack29", "nightsisterAttack30", "nightsisterAttack31" },
      respawnTimer = 43200,

      behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(axkvaMin, 2853795094) --  Add to Global Table
