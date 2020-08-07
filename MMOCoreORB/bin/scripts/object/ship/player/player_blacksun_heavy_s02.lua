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


object_ship_player_player_blacksun_heavy_s02 = object_ship_player_shared_player_blacksun_heavy_s02:new {

	name = "player_blacksun_heavy_s02",
	slideFactor = 1.91,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 298.5643, armor = 290.8233,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 99.33198, armor = 97.57671, speed = 40.67111, pitch = 20.59248, roll = 20.88879, yaw = 20.75872, acceleration = 11.85273, rollRate = 42.78871, pitchRate = 42.86503, deceleration = 15.57675, yawRate = 42.67835,},
	shield_0 = { name = "shd_generic", hitpoints = 773.0718, armor = 486.4986, regen = 4.869394, front = 577.5036, back = 790.7836,},
	armor_0 = { name = "arm_generic", hitpoints = 687.2841, armor = 693.7894,},
	armor_1 = { name = "arm_generic", hitpoints = 689.0114, armor = 673.8834,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 33.68177, energy = 562.0052,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.42347, armor = 19.25525, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 197.6118, armor = 191.2112, rate = 0.3379147, drain = 23.23726, maxDamage = 394.2346, shieldEfficiency = 0, minDamage = 310.9335, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 198.2586, armor = 192.2109, rate = 0.3415117, drain = 22.8, maxDamage = 23.43193, shieldEfficiency = 0, minDamage = 22.95926, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_incom_disruptor", hitpoints = 19.93216, armor = 19.87826, rate = 0.3423414, drain = 23.1964, maxDamage = 22.66079, shieldEfficiency = 0, minDamage = 22.90214, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_xwing_missile_s01", hitpoints = 0, armor = 0, rate = 0, drain = 0, maxDamage = 0, shieldEfficiency = 0, minDamage = 0, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_blacksun_heavy_s02, "object/ship/player/player_blacksun_heavy_s02.iff")
