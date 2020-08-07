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


object_ship_imperial_gunboat_tier1 = object_ship_shared_imperial_gunboat_tier1:new {

	name = "imperial_gunboat_tier1",
	slideFactor = 1.81,
	chassisHitpoints = 2400,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1496.323, armor = 1433.725,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 1448.597, armor = 1497.429, speed = 41.91073, pitch = 22.91126, roll = 28.07258, yaw = 17.9514, acceleration = 9.951235, rollRate = 49.81882, pitchRate = 45.28458, deceleration = 8.687152, yawRate = 38.07715,},
	shield_0 = { name = "shd_generic", hitpoints = 1441.244, armor = 1433.361, regen = 4.423146, front = 5878.96, back = 5980.609,},
	armor_0 = { name = "arm_generic", hitpoints = 3071.642, armor = 3166.895,},
	armor_1 = { name = "arm_generic", hitpoints = 3128.012, armor = 3058.719,},
	capacitor = { name = "cap_generic", hitpoints = 1451.938, armor = 1477.331, rechargeRate = 96.01223, energy = 4980.338,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 1462.32, armor = 1437.442, rate = 0.7430714, drain = 0.9844221, maxDamage = 97.20923, shieldEfficiency = 0.5349555, minDamage = 73.70153, ammo = 0, ammo_type = 0, armorEfficiency = 0.5331927,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 1493.626, armor = 1474.14, rate = 0.7735398, drain = 0.9991081, maxDamage = 97.25191, shieldEfficiency = 0.5478529, minDamage = 71.98171, ammo = 0, ammo_type = 0, armorEfficiency = 0.5510976,},
	weapon_2 = { name = "wpn_tieadvanced_blaster", hitpoints = 1448.541, armor = 1446.683, rate = 0.7797201, drain = 0.9696248, maxDamage = 97.38015, shieldEfficiency = 0.5496696, minDamage = 73.7812, ammo = 0, ammo_type = 0, armorEfficiency = 0.5366559,},
	weapon_3 = { name = "wpn_tieadvanced_blaster", hitpoints = 1477.36, armor = 1462.887, rate = 0.7460926, drain = 0.9814803, maxDamage = 97.17272, shieldEfficiency = 0.5426858, minDamage = 74.22118, ammo = 0, ammo_type = 0, armorEfficiency = 0.5358465,},
	weapon_4 = { name = "wpn_tieadvanced_blaster", hitpoints = 1488.316, armor = 1474.419, rate = 0.7625096, drain = 0.9759084, maxDamage = 96.5268, shieldEfficiency = 0.5371077, minDamage = 74.43044, ammo = 0, ammo_type = 0, armorEfficiency = 0.5568292,},
	weapon_5 = { name = "wpn_tieadvanced_blaster", hitpoints = 1479.984, armor = 1468.199, rate = 0.7663631, drain = 0.9606003, maxDamage = 99.85787, shieldEfficiency = 0.5393257, minDamage = 71.94412, ammo = 0, ammo_type = 0, armorEfficiency = 0.5393692,},
}

ObjectTemplates:addTemplate(object_ship_imperial_gunboat_tier1, "object/ship/imperial_gunboat_tier1.iff")
