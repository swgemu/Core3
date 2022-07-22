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


object_ship_player_player_blacksun_medium_s03 = object_ship_player_shared_player_blacksun_medium_s03:new {

	name = "player_blacksun_medium_s03",
	slideFactor = 1.81,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 285.8691, armor = 297.7704,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 98.94013, armor = 96.83083, speed = 52.67792, pitch = 33.38629, roll = 33.80513, yaw = 32.58237, acceleration = 16.22077, rollRate = 59.31021, pitchRate = 59.7647, deceleration = 8.263986, yawRate = 60.04031,},
	shield_0 = { name = "shd_generic", hitpoints = 388.7778, armor = 485.3872, regen = 4.956139, front = 286.9203, back = 491.3724,},
	armor_0 = { name = "arm_generic", hitpoints = 289.1444, armor = 294.4124,},
	armor_1 = { name = "arm_generic", hitpoints = 288.6785, armor = 295.0154,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 33.83265, energy = 564.4677,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.64533, armor = 19.09215, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 193.2914, armor = 198.8204, rate = 0.3369405, drain = 23.02787, maxDamage = 244.5285, shieldEfficiency = 0, minDamage = 114.5678, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 198.9391, armor = 199.2292, rate = 0.3357915, drain = 22.42832, maxDamage = 239.5728, shieldEfficiency = 0, minDamage = 117.0367, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_blacksun_medium_s03, "object/ship/player/player_blacksun_medium_s03.iff")
