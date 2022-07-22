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


object_ship_blacksun_medium_s01 = object_ship_shared_blacksun_medium_s01:new {

	name = "blacksun_medium_s01",
	slideFactor = 1.81,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 285.5983, armor = 290.1655,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 98.93473, armor = 95.95589, speed = 52.54455, pitch = 32.39491, roll = 32.54686, yaw = 33.31503, acceleration = 16.1324, rollRate = 59.67739, pitchRate = 59.03505, deceleration = 8.182605, yawRate = 58.01698,},
	shield_0 = { name = "shd_generic", hitpoints = 395.3677, armor = 481.0157, regen = 4.788142, front = 288.7187, back = 491.8087,},
	armor_0 = { name = "arm_generic", hitpoints = 288.4517, armor = 292.8065,},
	armor_1 = { name = "arm_generic", hitpoints = 298.9823, armor = 295.5588,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 35.03088, energy = 570.5404,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.3041, armor = 19.03032, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 191.1219, armor = 196.6724, rate = 0.3319671, drain = 23.38065, maxDamage = 238.707, shieldEfficiency = 0, minDamage = 118.8002, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 195.5838, armor = 196.9602, rate = 0.3448461, drain = 22.48913, maxDamage = 249.8848, shieldEfficiency = 0, minDamage = 117.6074, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_blacksun_medium_s01, "object/ship/blacksun_medium_s01.iff")
