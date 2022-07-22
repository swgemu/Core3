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


object_ship_droid_fighter_tier5 = object_ship_shared_droid_fighter_tier5:new {

	name = "droid_fighter_tier5",
	slideFactor = 1.92,
	chassisHitpoints = 2457.6,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 3072.315, armor = 3070.285,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 3036.146, armor = 3046.169, speed = 47.15306, pitch = 25.04946, roll = 31.87171, yaw = 19.58268, acceleration = 11.1619, rollRate = 56.72858, pitchRate = 51.78788, deceleration = 9.710927, yawRate = 43.05931,},
	shield_0 = { name = "shd_generic", hitpoints = 3067.217, armor = 3065.198, regen = 23.01505, front = 12250.05, back = 12670.42,},
	armor_0 = { name = "arm_generic", hitpoints = 6602.949, armor = 6639.519,},
	armor_1 = { name = "arm_generic", hitpoints = 6679.931, armor = 6751.296,},
	capacitor = { name = "cap_generic", hitpoints = 3074.455, armor = 3041.435, rechargeRate = 97.70374, energy = 4835.508,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 3081.829, armor = 3081.022, rate = 0.7491333, drain = 0.9516613, maxDamage = 322.1258, shieldEfficiency = 0.5482152, minDamage = 199.3519, ammo = 0, ammo_type = 0, armorEfficiency = 0.53555,},
}

ObjectTemplates:addTemplate(object_ship_droid_fighter_tier5, "object/ship/droid_fighter_tier5.iff")
