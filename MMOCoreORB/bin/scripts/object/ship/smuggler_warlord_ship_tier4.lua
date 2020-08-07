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


object_ship_smuggler_warlord_ship_tier4 = object_ship_shared_smuggler_warlord_ship_tier4:new {

	name = "smuggler_warlord_ship_tier4",
	slideFactor = 1.76,
	chassisHitpoints = 19200,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 20723.03, armor = 20530.73,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 20265.11, armor = 20374.24, speed = 45.38646, pitch = 24.90459, roll = 30.97887, yaw = 19.59879, acceleration = 10.9342, rollRate = 55.91019, pitchRate = 48.2766, deceleration = 9.120949, yawRate = 41.73053,},
	shield_0 = { name = "shd_generic", hitpoints = 20321.7, armor = 20674.65, regen = 22.15231, front = 80770.89, back = 79817.3,},
	armor_0 = { name = "arm_generic", hitpoints = 43610.25, armor = 42127.84,},
	armor_1 = { name = "arm_generic", hitpoints = 43744.45, armor = 43812.73,},
	capacitor = { name = "cap_generic", hitpoints = 20342.64, armor = 20114.19, rechargeRate = 98.29565, energy = 4778.034,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 20729.28, armor = 19749.14, rate = 0.7618723, drain = 0.9940739, maxDamage = 625.5294, shieldEfficiency = 0.5508458, minDamage = 391.4424, ammo = 0, ammo_type = 0, armorEfficiency = 0.5377479,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 19837.97, armor = 20258.54, rate = 0.7448129, drain = 0.9587756, maxDamage = 627.0066, shieldEfficiency = 0.5450514, minDamage = 408.2849, ammo = 0, ammo_type = 0, armorEfficiency = 0.5350713,},
	weapon_2 = { name = "wpn_incom_blaster", hitpoints = 20233, armor = 19922.3, rate = 0.7651127, drain = 0.9666274, maxDamage = 606.9312, shieldEfficiency = 0.5592085, minDamage = 393.64, ammo = 0, ammo_type = 0, armorEfficiency = 0.5568812,},
	weapon_3 = { name = "wpn_incom_disruptor", hitpoints = 20709.12, armor = 20042.42, rate = 0.7694248, drain = 0.9814006, maxDamage = 619.0355, shieldEfficiency = 0.5569389, minDamage = 391.1298, ammo = 0, ammo_type = 0, armorEfficiency = 0.5479581,},
	weapon_4 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 20594.55, armor = 19821.95, rate = 2.96422, drain = 0.9509389, maxDamage = 1888.329, shieldEfficiency = 0.7162275, minDamage = 807.7863, ammo = 4, ammo_type = 19, armorEfficiency = 0.7365171,},
}

ObjectTemplates:addTemplate(object_ship_smuggler_warlord_ship_tier4, "object/ship/smuggler_warlord_ship_tier4.iff")
