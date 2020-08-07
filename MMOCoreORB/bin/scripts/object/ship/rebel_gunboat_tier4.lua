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


object_ship_rebel_gunboat_tier4 = object_ship_shared_rebel_gunboat_tier4:new {

	name = "rebel_gunboat_tier4",
	slideFactor = 1.76,
	chassisHitpoints = 19200,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 20689.76, armor = 20160.51,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 19831.62, armor = 20308.09, speed = 44.62583, pitch = 24.40885, roll = 31.16408, yaw = 19.79517, acceleration = 10.62157, rollRate = 56.39635, pitchRate = 50.25218, deceleration = 9.212252, yawRate = 40.91048,},
	shield_0 = { name = "shd_generic", hitpoints = 19836.73, armor = 20107.86, regen = 21.66754, front = 80830.34, back = 79382.41,},
	armor_0 = { name = "arm_generic", hitpoints = 42952.93, armor = 42677.14,},
	armor_1 = { name = "arm_generic", hitpoints = 43606.6, armor = 42757.31,},
	capacitor = { name = "cap_generic", hitpoints = 20580.25, armor = 19968, rechargeRate = 96.20575, energy = 4832.38,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 19710.62, armor = 19925.59, rate = 0.7751553, drain = 0.9598163, maxDamage = 610.3936, shieldEfficiency = 0.5345271, minDamage = 404.8562, ammo = 0, ammo_type = 0, armorEfficiency = 0.5565413,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 20675.93, armor = 19974.53, rate = 0.7509446, drain = 0.9810871, maxDamage = 621.6217, shieldEfficiency = 0.5419436, minDamage = 403.8316, ammo = 0, ammo_type = 0, armorEfficiency = 0.5497357,},
	weapon_2 = { name = "wpn_incom_disruptor", hitpoints = 20606.04, armor = 20082.83, rate = 0.7715054, drain = 0.9626082, maxDamage = 610.6752, shieldEfficiency = 0.5336035, minDamage = 393.4675, ammo = 0, ammo_type = 0, armorEfficiency = 0.5469897,},
	weapon_3 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 20255.23, armor = 20192.81, rate = 2.959037, drain = 0.9609458, maxDamage = 1813.363, shieldEfficiency = 0.7399473, minDamage = 794.9932, ammo = 4, ammo_type = 19, armorEfficiency = 0.7317688,},
}

ObjectTemplates:addTemplate(object_ship_rebel_gunboat_tier4, "object/ship/rebel_gunboat_tier4.iff")
