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


object_ship_player_player_blacksun_light_s04 = object_ship_player_shared_player_blacksun_light_s04:new {

	name = "player_blacksun_light_s04",
	slideFactor = 1.81,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 295.0436, armor = 293.24,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 98.30356, armor = 97.88931, speed = 52.62028, pitch = 32.68404, roll = 32.41749, yaw = 33.41313, acceleration = 15.96255, rollRate = 59.74601, pitchRate = 60.37212, deceleration = 8.003306, yawRate = 60.8251,},
	shield_0 = { name = "shd_generic", hitpoints = 398.3103, armor = 476.1999, regen = 4.782587, front = 295.0487, back = 480.9888,},
	armor_0 = { name = "arm_generic", hitpoints = 295.749, armor = 298.8542,},
	armor_1 = { name = "arm_generic", hitpoints = 287.2855, armor = 297.9694,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 35.01874, energy = 555.002,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.93907, armor = 19.89808, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 197.3677, armor = 199.564, rate = 0.3323911, drain = 23.55841, maxDamage = 248.4767, shieldEfficiency = 0, minDamage = 118.0815, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_blacksun_light_s04, "object/ship/player/player_blacksun_light_s04.iff")
