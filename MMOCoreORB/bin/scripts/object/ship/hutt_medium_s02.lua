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


object_ship_hutt_medium_s02 = object_ship_shared_hutt_medium_s02:new {

	name = "hutt_medium_s02",
	slideFactor = 1.85,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 290.7723, armor = 295.0777,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 98.49388, armor = 96.60285, speed = 45.61077, pitch = 26.64678, roll = 27.92731, yaw = 26.78938, acceleration = 12.03924, rollRate = 53.23529, pitchRate = 53.8278, deceleration = 15.34299, yawRate = 53.51611,},
	shield_0 = { name = "shd_generic", hitpoints = 394.1819, armor = 493.0251, regen = 4.897365, front = 398.7292, back = 667.5689,},
	armor_0 = { name = "arm_generic", hitpoints = 475.6074, armor = 483.3208,},
	armor_1 = { name = "arm_generic", hitpoints = 498.1956, armor = 499.2024,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 35.12217, energy = 548.589,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.16059, armor = 19.09219, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 192.7758, armor = 192.9306, rate = 0.337097, drain = 22.43583, maxDamage = 313.0152, shieldEfficiency = 0, minDamage = 204.6888, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_hutt_medium_s02, "object/ship/hutt_medium_s02.iff")
