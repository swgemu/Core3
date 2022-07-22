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


object_ship_player_player_ywing = object_ship_player_shared_player_ywing:new {

	name = "player_ywing",
	slideFactor = 1.85,
	chassisHitpoints = 1942,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 391.301, armor = 395.5459,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 95.1216, armor = 98.82816, speed = 33.94477, pitch = 29.14914, roll = 46.04024, yaw = 36.51349, acceleration = 12.86286, rollRate = 71.91398, pitchRate = 40.69682, deceleration = 10.73087, yawRate = 60.91904,},
	shield_0 = { name = "shd_generic", hitpoints = 387.716, armor = 478.333, regen = 2.9559, front = 1226.369, back = 1208.254,},
	armor_0 = { name = "arm_generic", hitpoints = 1084.257, armor = 1050.654,},
	armor_1 = { name = "arm_generic", hitpoints = 1084.771, armor = 1065.881,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 42.08575, energy = 1302.091,},
	booster = { name = "bst_generic", hitpoints = 19.20536, armor = 19.4511, energy = 98.32303, acceleration = 19.88879, speed = 14.91796, energyUsage = 9.789608, rechargeRate = 4.757387,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 195.4548, armor = 198.3018, rate = 0.3431529, drain = 22.86427, maxDamage = 801.0384, shieldEfficiency = 0, minDamage = 605.5146, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 190.9953, armor = 197.2816, rate = 15.52149, drain = 82.60093, maxDamage = 1862.454, shieldEfficiency = 0.4766501, minDamage = 312.614, ammo = 24, ammo_type = 5, armorEfficiency = 0.7733029,},
	weapon_2 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 19.54943, armor = 19.33636, rate = 0.3314228, drain = 23.01111, maxDamage = 22.5608, shieldEfficiency = 0, minDamage = 22.85924, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_std_countermeasure", hitpoints = 239.9798, armor = 239.9064, rate = 0.09811106, drain = 23.0503, maxDamage = 96.10748, shieldEfficiency = 0, minDamage = 24.39878, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_ywing, "object/ship/player/player_ywing.iff")
