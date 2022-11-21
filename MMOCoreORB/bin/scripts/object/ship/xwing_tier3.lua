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


object_ship_xwing_tier3 = object_ship_shared_xwing_tier3:new {

	name = "xwing_tier3",
	slideFactor = 1.82,
	chassisHitpoints = 1320,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1173.496, armor = 1132.984,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 1164.205, armor = 1139.589, speed = 42.72108, pitch = 24.25816, roll = 29.88142, yaw = 19.24585, acceleration = 10.30818, rollRate = 53.5662, pitchRate = 46.82452, deceleration = 9.011065, yawRate = 39.21711,},
	shield_0 = { name = "shd_generic", hitpoints = 1180.476, armor = 1143.748, regen = 9.683233, front = 4528.565, back = 4520.678,},
	armor_0 = { name = "arm_generic", hitpoints = 2231.581, armor = 2238.058,},
	armor_1 = { name = "arm_generic", hitpoints = 2237.434, armor = 2242.857,},
	capacitor = { name = "cap_generic", hitpoints = 1163.303, armor = 1140.882, rechargeRate = 99.55075, energy = 4812.012,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 1181.102, armor = 1141.4, rate = 0.7726409, drain = 0.9800557, maxDamage = 173.128, shieldEfficiency = 0.5324696, minDamage = 121.7795, ammo = 0, ammo_type = 0, armorEfficiency = 0.5565706,},
}

ObjectTemplates:addTemplate(object_ship_xwing_tier3, "object/ship/xwing_tier3.iff")
