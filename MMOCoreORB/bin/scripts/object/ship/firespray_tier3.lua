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


object_ship_firespray_tier3 = object_ship_shared_firespray_tier3:new {

	name = "firespray_tier3",
	slideFactor = 1.81,
	chassisHitpoints = 1560,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1356.765, armor = 1339.391,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 1364.179, armor = 1344.244, speed = 43.15681, pitch = 24.38127, roll = 30.05296, yaw = 19.29794, acceleration = 10.29006, rollRate = 54.9911, pitchRate = 47.84895, deceleration = 9.040998, yawRate = 39.41249,},
	shield_0 = { name = "shd_generic", hitpoints = 1387.6, armor = 1377.389, regen = 11.76928, front = 5587.229, back = 5591.351,},
	armor_0 = { name = "arm_generic", hitpoints = 2866.321, armor = 2908.273,},
	armor_1 = { name = "arm_generic", hitpoints = 2929.674, armor = 2883.648,},
	capacitor = { name = "cap_generic", hitpoints = 1403.177, armor = 1334.859, rechargeRate = 99.9101, energy = 4909.16,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 1389.305, armor = 1386.69, rate = 0.7691214, drain = 0.9947638, maxDamage = 206.6859, shieldEfficiency = 0.551897, minDamage = 143.743, ammo = 0, ammo_type = 0, armorEfficiency = 0.5370359,},
}

ObjectTemplates:addTemplate(object_ship_firespray_tier3, "object/ship/firespray_tier3.iff")
