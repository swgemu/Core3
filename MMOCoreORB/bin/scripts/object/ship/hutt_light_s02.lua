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


object_ship_hutt_light_s02 = object_ship_shared_hutt_light_s02:new {

	name = "hutt_light_s02",
	slideFactor = 1.81,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 289.373, armor = 297.2937,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 98.41382, armor = 95.98478, speed = 52.91775, pitch = 32.82121, roll = 33.87024, yaw = 33.9141, acceleration = 15.97858, rollRate = 58.50536, pitchRate = 60.82196, deceleration = 8.305563, yawRate = 60.23152,},
	shield_0 = { name = "shd_generic", hitpoints = 385.8282, armor = 494.1139, regen = 4.816782, front = 298.2745, back = 490.4568,},
	armor_0 = { name = "arm_generic", hitpoints = 293.9883, armor = 286.9332,},
	armor_1 = { name = "arm_generic", hitpoints = 286.7292, armor = 292.3092,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.28038, energy = 545.4581,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.90373, armor = 19.92349, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 198.8108, armor = 192.7256, rate = 0.3445816, drain = 22.85086, maxDamage = 242.8218, shieldEfficiency = 0, minDamage = 119.2512, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_hutt_light_s02, "object/ship/hutt_light_s02.iff")
