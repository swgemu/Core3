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


object_ship_player_player_blacksun_heavy_s04 = object_ship_player_shared_player_blacksun_heavy_s04:new {

	name = "player_blacksun_heavy_s04",
	slideFactor = 1.91,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 288.6568, armor = 290.3434,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 95.81405, armor = 96.74408, speed = 41.05715, pitch = 20.29385, roll = 20.07003, yaw = 20.90281, acceleration = 11.60822, rollRate = 41.43303, pitchRate = 42.6875, deceleration = 14.98052, yawRate = 41.40241,},
	shield_0 = { name = "shd_generic", hitpoints = 785.334, armor = 492.5698, regen = 4.79799, front = 594.6714, back = 789.2192,},
	armor_0 = { name = "arm_generic", hitpoints = 674.7458, armor = 697.7799,},
	armor_1 = { name = "arm_generic", hitpoints = 697.4012, armor = 667.9643,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.38279, energy = 565.7834,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.37678, armor = 19.56945, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 192.8261, armor = 197.6119, rate = 0.3332738, drain = 23.4945, maxDamage = 399.6004, shieldEfficiency = 0, minDamage = 308.6718, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 195.4651, armor = 191.4426, rate = 0.3367485, drain = 22.87436, maxDamage = 22.90322, shieldEfficiency = 0, minDamage = 23.14557, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_incom_disruptor", hitpoints = 19.86217, armor = 19.50508, rate = 0.3435956, drain = 23.23153, maxDamage = 23.45263, shieldEfficiency = 0, minDamage = 23.3075, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_xwing_missile_s01", hitpoints = 0, armor = 0, rate = 0, drain = 0, maxDamage = 0, shieldEfficiency = 0, minDamage = 0, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_blacksun_heavy_s04, "object/ship/player/player_blacksun_heavy_s04.iff")
