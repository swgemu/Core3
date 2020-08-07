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


object_ship_player_player_corvette = object_ship_player_shared_player_corvette:new {

	name = "player_corvette",
	slideFactor = 1.76,
	chassisHitpoints = 60000,
	chassisMass = 50000,
	reactor = { name = "rct_generic", hitpoints = 9752.661, armor = 4989.694,},
	engine = { name = "eng_generic", hitpoints = 9588.516, armor = 4844.097, speed = 31.86467, pitch = 2.930267, roll = 2.884028, yaw = 2.889462, acceleration = 7.765073, rollRate = 2.964135, pitchRate = 2.943088, deceleration = 7.992248, yawRate = 2.946589,},
	shield_0 = { name = "shd_generic", hitpoints = 9733.806, armor = 4785.299, regen = 48.9024, front = 19057.25, back = 19275.46,},
	shield_1 = { name = "shd_generic", hitpoints = 9545.08, armor = 4832.996, regen = 39.88941, front = 19617.26, back = 19333.25,},
	armor_0 = { name = "arm_generic", hitpoints = 14753.46, armor = 14338.56,},
	armor_1 = { name = "arm_generic", hitpoints = 14759.64, armor = 14848.18,},
	capacitor = { name = "cap_generic", hitpoints = 9942.104, armor = 4976.277, rechargeRate = 125.4661, energy = 2256.647,},
	bridge = { name = "bdg_generic", hitpoints = 4848.984, armor = 4870.515,},
	hangar = { name = "hgr_generic", hitpoints = 9983.024, armor = 9686.308,},
	targeting_station = { name = "tst_generic", hitpoints = 9780.072, armor = 9668.867,},
	weapon_0 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 7725.799, armor = 3949.11, rate = 0.4580307, drain = 42.03432, maxDamage = 631.7401, shieldEfficiency = 0, minDamage = 508.552, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 7975.879, armor = 3901.212, rate = 0.4563584, drain = 43.30898, maxDamage = 613.6996, shieldEfficiency = 0, minDamage = 509.4561, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 7750.647, armor = 3961.394, rate = 0.4647901, drain = 42.03119, maxDamage = 630.2078, shieldEfficiency = 0, minDamage = 510.1221, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 7681.285, armor = 3877.711, rate = 0.457445, drain = 42.10054, maxDamage = 613.1294, shieldEfficiency = 0, minDamage = 508.9873, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_4 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 7734.926, armor = 3850.481, rate = 0.4509488, drain = 41.72525, maxDamage = 613.5706, shieldEfficiency = 0, minDamage = 494.9903, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_5 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 7762.041, armor = 3909.015, rate = 0.4500448, drain = 43.4888, maxDamage = 618.8244, shieldEfficiency = 0, minDamage = 505.5719, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_6 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 7945.842, armor = 3882.898, rate = 0.4563857, drain = 42.05074, maxDamage = 634.2711, shieldEfficiency = 0, minDamage = 502.3967, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_corvette, "object/ship/player/player_corvette.iff")
