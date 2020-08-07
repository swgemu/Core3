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


object_ship_imperial_gunboat = object_ship_shared_imperial_gunboat:new {

	name = "imperial_gunboat",
	slideFactor = 1.76,
	chassisHitpoints = 30000,
	chassisMass = 50000,
	reactor = { name = "rct_generic", hitpoints = 4825.451, armor = 1941.35,},
	engine = { name = "eng_generic", hitpoints = 4921.962, armor = 1964.984, speed = 31.83185, pitch = 2.999185, roll = 2.872544, yaw = 2.977371, acceleration = 7.885826, rollRate = 2.9925, pitchRate = 2.960268, deceleration = 7.873787, yawRate = 2.918168,},
	shield_0 = { name = "shd_generic", hitpoints = 9852.832, armor = 2863.918, regen = 49.31765, front = 5843.854, back = 5754.08,},
	shield_1 = { name = "shd_generic", hitpoints = 4928.592, armor = 2909.667, regen = 38.82604, front = 2913.52, back = 2886.569,},
	armor_0 = { name = "arm_generic", hitpoints = 4900.25, armor = 4755.258,},
	armor_1 = { name = "arm_generic", hitpoints = 4879.095, armor = 4947.238,},
	capacitor = { name = "cap_generic", hitpoints = 4971.965, armor = 963.1585, rechargeRate = 123.8236, energy = 2250.378,},
	bridge = { name = "bdg_generic", hitpoints = 1998.63, armor = 1980.539,},
	hangar = { name = "hgr_generic", hitpoints = 1915.637, armor = 1911.79,},
	targeting_station = { name = "tst_generic", hitpoints = 1955.803, armor = 1974,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 192.3508, armor = 190.5189, rate = 0.3406295, drain = 21.05924, maxDamage = 145.2219, shieldEfficiency = 0, minDamage = 99.66513, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 190.5755, armor = 192.3423, rate = 0.3519415, drain = 22.01925, maxDamage = 145.5459, shieldEfficiency = 0, minDamage = 97.98459, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_tieadvanced_blaster", hitpoints = 196.7702, armor = 196.4153, rate = 0.3411139, drain = 21.42482, maxDamage = 147.8808, shieldEfficiency = 0, minDamage = 97.89068, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_tieadvanced_blaster", hitpoints = 199.0873, armor = 190.6066, rate = 0.3476186, drain = 21.21993, maxDamage = 142.7525, shieldEfficiency = 0, minDamage = 98.67496, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_4 = { name = "wpn_tieadvanced_blaster", hitpoints = 190.8191, armor = 196.4569, rate = 0.3400911, drain = 21.72886, maxDamage = 142.8256, shieldEfficiency = 0, minDamage = 95.5471, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_imperial_gunboat, "object/ship/imperial_gunboat.iff")
