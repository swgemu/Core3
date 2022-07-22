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


object_ship_player_player_tieadvanced = object_ship_player_shared_player_tieadvanced:new {

	name = "player_tieadvanced",
	slideFactor = 1.82,
	chassisHitpoints = 1462.5,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 294.2302, armor = 287.5432,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 294.3204, armor = 288.2111, speed = 51.82899, pitch = 55.80734, roll = 58.94701, yaw = 41.16174, acceleration = 20.90797, rollRate = 82.30802, pitchRate = 68.94418, deceleration = 14.18084, yawRate = 56.31701,},
	shield_0 = { name = "shd_generic", hitpoints = 293.7551, armor = 297.3301, regen = 5.963708, front = 972.2947, back = 981.0896,},
	armor_0 = { name = "arm_generic", hitpoints = 396.66, armor = 385.0567,},
	armor_1 = { name = "arm_generic", hitpoints = 388.2775, armor = 399.6975,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 41.92297, energy = 1071.557,},
	booster = { name = "bst_generic", hitpoints = 19.43983, armor = 19.12926, energy = 97.1799, acceleration = 19.27003, speed = 14.58291, energyUsage = 9.821065, rechargeRate = 4.877397,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 193.3158, armor = 198.8849, rate = 0.3547659, drain = 21.87364, maxDamage = 588.3181, shieldEfficiency = 0, minDamage = 457.5086, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_sienar_heatseeker_missile_s01", hitpoints = 198.7069, armor = 197.4441, rate = 12.01178, drain = 69.76207, maxDamage = 1363.26, shieldEfficiency = 0.5815977, minDamage = 718.3189, ammo = 16, ammo_type = 4, armorEfficiency = 0.417339,},
	weapon_2 = { name = "wpn_std_countermeasure", hitpoints = 245.509, armor = 245.3485, rate = 9.876356, drain = 23.4104, maxDamage = 95.39288, shieldEfficiency = 0, minDamage = 24.29316, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_tieadvanced, "object/ship/player/player_tieadvanced.iff")
