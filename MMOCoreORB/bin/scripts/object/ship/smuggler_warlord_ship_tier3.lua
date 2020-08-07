--Copyright (C) 2010 <SWGEmu>


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


object_ship_smuggler_warlord_ship_tier3 = object_ship_shared_smuggler_warlord_ship_tier3:new {

	name = "smuggler_warlord_ship_tier3",
	slideFactor = 1.76,
	chassisHitpoints = 12000,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 10345.78, armor = 10682.2,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 10571.6, armor = 10324.2, speed = 42.92272, pitch = 23.96437, roll = 29.50765, yaw = 19.0815, acceleration = 10.32613, rollRate = 53.31849, pitchRate = 46.59908, deceleration = 8.781643, yawRate = 38.73058,},
	shield_0 = { name = "shd_generic", hitpoints = 10442.55, armor = 10590.7, regen = 13.60242, front = 42664.35, back = 41289.79,},
	armor_0 = { name = "arm_generic", hitpoints = 22139.69, armor = 21891.27,},
	armor_1 = { name = "arm_generic", hitpoints = 22657.45, armor = 22854.03,},
	capacitor = { name = "cap_generic", hitpoints = 10656.9, armor = 10315.51, rechargeRate = 98.87451, energy = 4955.774,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 10690.47, armor = 10320.19, rate = 0.7562761, drain = 0.9598417, maxDamage = 405.5001, shieldEfficiency = 0.5509334, minDamage = 266.7214, ammo = 0, ammo_type = 0, armorEfficiency = 0.5524762,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 10701.86, armor = 10493.79, rate = 0.7594435, drain = 0.9602094, maxDamage = 402.7565, shieldEfficiency = 0.5406767, minDamage = 275.0874, ammo = 0, ammo_type = 0, armorEfficiency = 0.5375234,},
	weapon_2 = { name = "wpn_incom_blaster", hitpoints = 10496.02, armor = 10697.71, rate = 0.7585117, drain = 0.9810463, maxDamage = 395.4433, shieldEfficiency = 0.5542539, minDamage = 276.5071, ammo = 0, ammo_type = 0, armorEfficiency = 0.5581003,},
	weapon_3 = { name = "wpn_incom_disruptor", hitpoints = 10636.1, armor = 10735.6, rate = 0.7692499, drain = 0.9629639, maxDamage = 392.1855, shieldEfficiency = 0.5414623, minDamage = 273.4537, ammo = 0, ammo_type = 0, armorEfficiency = 0.5524791,},
	weapon_4 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 10565.32, armor = 10619.47, rate = 2.894074, drain = 0.967117, maxDamage = 1208.931, shieldEfficiency = 0.7295969, minDamage = 547.1894, ammo = 4, ammo_type = 18, armorEfficiency = 0.7349598,},
}

ObjectTemplates:addTemplate(object_ship_smuggler_warlord_ship_tier3, "object/ship/smuggler_warlord_ship_tier3.iff")
