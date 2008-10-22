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
darkJawa = Creature:new {
      objectName = "darkJawa",  -- Lua Object Name
      creatureType = "NPC",
      faction = "Jawa",
      gender = "",

      stfName = "Dark Jawa",
      objectCRC = 3444186231, 
      socialGroup = "Jawa",
      named = FALSE, 

      level = 6,
      xp = 147,

      combatFlags = ATTACKABLE_FLAG + ENEMY_FLAG + AGGRESSIVE_FLAG,

      healthMax = 500000,
      healthMin = 480000,
      strength = 80000,
      constitution = 80000,

      actionMax = 500000,
      actionMin = 480000,
      quickness = 80000,
      stamina = 80000,

      mindMax = 500000,
      mindMin = 480000,
      focus = 80000,
      willpower = 80000,

      height = 1, -- Size of creature
      armor = 3, -- 0 = None; 1 = Light; 2 = Medium; 3 = Heavy
      kinetic = 85,
      energy = 85,
      electricity = 85,
      stun = -1,
      blast = 85,
      heat = 85,
      cold = 85,
      acid = 85,
      lightsaber = 85,

      accuracy = 0,

      healer = 0,

      pack = 1,
      herd = 0,
      stalker = 1,
      killer = 1,
      aggressive = 0,
      invincible = 0, 

	  meleeDefense = 1,  
	  rangedDefense = 1,

      attackCreatureOnSight = "", -- Enter socialGroups 

      weapon = "object/weapon/melee/sword/shared_sword_lightsaber_mace.iff", -- File path to weapon -> object\xxx\xxx\xx
      weaponName = "Jawa Saber", -- Name ex. 'a Vibrolance'
      weaponTemp = "sword_lightsaber_mace", -- Weapon Template ex. 'lance_vibrolance'
      weaponClass = "TwoHandedJediWeapon", -- Weapon Class ex. 'PolearmMeleeWeapon'
      weaponEquipped = 1,
      weaponMinDamage = 650,
      weaponMaxDamage = 950,
      weaponAttackSpeed = 1,
      weaponDamageType = "LIGHTSABER", -- ELECTRICITY, KINETIC, etc
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

      lootGroup = 0, -- Group it belongs to for loot

      tame = 0,  -- Likely hood to be tamed

      milk = 0,

      boneType = "",
      boneMax = 0,

      hideType = "",
      hideMax = 0,

      meatType = "",
      meatMax = 0,

      skills = { "twoHandedJediAttack4" },
      respawnTimer = 42300,

      behaviorScript = "", -- Link to the behavior script for this object
}

Creatures:addCreature(darkJawa, 3444186231) --  Add to Global Table
