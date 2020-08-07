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


object_ship_bwing_tier3 = object_ship_shared_bwing_tier3:new {

	name = "bwing_tier3",
	slideFactor = 1.67,
	chassisHitpoints = 1440,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1251.367, armor = 1277.358,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 1294.494, armor = 1251.52, speed = 43.04839, pitch = 23.79724, roll = 29.31953, yaw = 18.77524, acceleration = 10.31409, rollRate = 52.87086, pitchRate = 48.79776, deceleration = 8.80135, yawRate = 39.49655,},
	shield_0 = { name = "shd_generic", hitpoints = 1295.111, armor = 1258.674, regen = 9.092702, front = 5130.554, back = 5040.955,},
	armor_0 = { name = "arm_generic", hitpoints = 2745.648, armor = 2692.652,},
	armor_1 = { name = "arm_generic", hitpoints = 2679.031, armor = 2674.029,},
	capacitor = { name = "cap_generic", hitpoints = 1242.183, armor = 1270.691, rechargeRate = 97.16441, energy = 4943.17,},
	weapon_0 = { name = "wpn_bwing_blaster", hitpoints = 1260.622, armor = 1245.476, rate = 0.7735615, drain = 0.9681385, maxDamage = 173.823, shieldEfficiency = 0.5327783, minDamage = 116.5814, ammo = 0, ammo_type = 0, armorEfficiency = 0.5366241,},
	weapon_1 = { name = "wpn_bwing_blaster", hitpoints = 1270.405, armor = 1263.318, rate = 0.7586988, drain = 0.9635783, maxDamage = 172.0125, shieldEfficiency = 0.5572127, minDamage = 117.5625, ammo = 0, ammo_type = 0, armorEfficiency = 0.5577734,},
	weapon_2 = { name = "wpn_bwing_blaster", hitpoints = 1262.569, armor = 1236.792, rate = 0.759927, drain = 0.9784933, maxDamage = 175.3067, shieldEfficiency = 0.5549349, minDamage = 120.7911, ammo = 0, ammo_type = 0, armorEfficiency = 0.550242,},
	weapon_3 = { name = "wpn_bwing_blaster", hitpoints = 1279.769, armor = 1242.429, rate = 0.75776, drain = 0.9845731, maxDamage = 174.4515, shieldEfficiency = 0.5575203, minDamage = 118.6537, ammo = 0, ammo_type = 0, armorEfficiency = 0.5475648,},
	weapon_4 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 1280.948, armor = 1232.509, rate = 2.939808, drain = 0.9872841, maxDamage = 519.4327, shieldEfficiency = 0.7321023, minDamage = 240.5462, ammo = 4, ammo_type = 18, armorEfficiency = 0.7321601,},
}

ObjectTemplates:addTemplate(object_ship_bwing_tier3, "object/ship/bwing_tier3.iff")
