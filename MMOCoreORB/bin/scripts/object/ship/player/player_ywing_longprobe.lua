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


object_ship_player_player_ywing_longprobe = object_ship_player_shared_player_ywing_longprobe:new {

	name = "player_ywing_longprobe",
	slideFactor = 1.85,
	chassisHitpoints = 1942,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 398.2837, armor = 394.4893,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 95.6149, armor = 99.55, speed = 32.88455, pitch = 28.54158, roll = 45.71789, yaw = 37.11726, acceleration = 12.35336, rollRate = 70.40501, pitchRate = 41.73699, deceleration = 10.71079, yawRate = 60.28631,},
	shield_0 = { name = "shd_generic", hitpoints = 391.9203, armor = 480.1941, regen = 2.95838, front = 1236.746, back = 1221.614,},
	armor_0 = { name = "arm_generic", hitpoints = 1076.184, armor = 1051.792,},
	armor_1 = { name = "arm_generic", hitpoints = 1067.785, armor = 1081.967,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 40.92189, energy = 1282.863,},
	booster = { name = "bst_generic", hitpoints = 19.5545, armor = 19.49567, energy = 98.75519, acceleration = 19.38715, speed = 14.85137, energyUsage = 9.928226, rechargeRate = 4.920537,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 193.335, armor = 190.9748, rate = 0.3334711, drain = 22.5674, maxDamage = 789.3185, shieldEfficiency = 0, minDamage = 591.7603, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 195.9654, armor = 190.6203, rate = 15.90339, drain = 85.45589, maxDamage = 1819.546, shieldEfficiency = 0.4992857, minDamage = 306.6322, ammo = 24, ammo_type = 5, armorEfficiency = 0.7910516,},
	weapon_2 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 19.12318, armor = 19.33368, rate = 0.3313202, drain = 22.9849, maxDamage = 22.68814, shieldEfficiency = 0, minDamage = 23.50545, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_std_countermeasure", hitpoints = 245.4934, armor = 245.7292, rate = 0.0981887, drain = 23.00684, maxDamage = 99.22425, shieldEfficiency = 0, minDamage = 24.37101, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_ywing_longprobe, "object/ship/player/player_ywing_longprobe.iff")
