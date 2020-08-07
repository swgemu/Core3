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


object_ship_player_player_hutt_medium_s02 = object_ship_player_shared_player_hutt_medium_s02:new {

	name = "player_hutt_medium_s02",
	slideFactor = 1.76,
	chassisHitpoints = 1512,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 298.1105, armor = 298.715,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 96.08215, armor = 97.71975, speed = 44.1099, pitch = 43.80634, roll = 52.2076, yaw = 26.66313, acceleration = 11.77163, rollRate = 79.58759, pitchRate = 67.73086, deceleration = 15.22928, yawRate = 76.32036,},
	shield_0 = { name = "shd_generic", hitpoints = 396.9262, armor = 498.7002, regen = 4.843915, front = 939.5843, back = 950.832,},
	armor_0 = { name = "arm_generic", hitpoints = 197.1332, armor = 197.1565,},
	armor_1 = { name = "arm_generic", hitpoints = 199.6718, armor = 193.8375,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 31.40651, energy = 494.3975,},
	booster = { name = "bst_generic", hitpoints = 19.05527, armor = 19.83886, energy = 98.34339, acceleration = 19.14887, speed = 14.25113, energyUsage = 9.686683, rechargeRate = 4.868037,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 192.3085, armor = 199.414, rate = 0.3291892, drain = 22.67983, maxDamage = 241.4728, shieldEfficiency = 0, minDamage = 119.2315, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_std_countermeasure", hitpoints = 242.6855, armor = 240.7494, rate = 0.09984232, drain = 22.42602, maxDamage = 97.34396, shieldEfficiency = 0, minDamage = 24.60987, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_hutt_medium_s02, "object/ship/player/player_hutt_medium_s02.iff")
