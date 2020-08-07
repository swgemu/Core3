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


object_ship_rebel_gunboat = object_ship_shared_rebel_gunboat:new {

	name = "rebel_gunboat",
	slideFactor = 1.76,
	chassisHitpoints = 30000,
	chassisMass = 50000,
	reactor = { name = "rct_generic", hitpoints = 4934.843, armor = 1964.696,},
	engine = { name = "eng_generic", hitpoints = 4868.036, armor = 1931.941, speed = 30.92377, pitch = 2.984192, roll = 2.88726, yaw = 2.856609, acceleration = 7.943364, rollRate = 2.982613, pitchRate = 2.966784, deceleration = 7.718737, yawRate = 2.93682,},
	shield_0 = { name = "shd_generic", hitpoints = 9930.7, armor = 2933.756, regen = 48.60147, front = 5875.456, back = 58885.01,},
	shield_1 = { name = "shd_generic", hitpoints = 4983.691, armor = 2934.741, regen = 38.04778, front = 2990.665, back = 2998.197,},
	armor_0 = { name = "arm_generic", hitpoints = 4866.138, armor = 4933.158,},
	armor_1 = { name = "arm_generic", hitpoints = 4834.559, armor = 4927.475,},
	capacitor = { name = "cap_generic", hitpoints = 4812.914, armor = 978.3821, rechargeRate = 126.4052, energy = 2280.75,},
	bridge = { name = "bdg_generic", hitpoints = 1979.376, armor = 1979.795,},
	hangar = { name = "hgr_generic", hitpoints = 1920.075, armor = 1994.931,},
	targeting_station = { name = "tst_generic", hitpoints = 1911.839, armor = 1974.132,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 193.0898, armor = 199.38, rate = 0.3436731, drain = 22.68404, maxDamage = 142.6422, shieldEfficiency = 0, minDamage = 99.10276, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 192.8469, armor = 197.4728, rate = 0.3379266, drain = 22.7654, maxDamage = 145.1237, shieldEfficiency = 0, minDamage = 98.19164, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_incom_blaster", hitpoints = 196.2849, armor = 199.9853, rate = 0.3315327, drain = 23.11151, maxDamage = 146.2559, shieldEfficiency = 0, minDamage = 96.5614, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_rebel_gunboat, "object/ship/rebel_gunboat.iff")
