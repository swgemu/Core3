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


object_ship_droid_fighter_tier1 = object_ship_shared_droid_fighter_tier1:new {

	name = "droid_fighter_tier1",
	slideFactor = 1.92,
	chassisHitpoints = 240,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 146.4117, armor = 148.9926,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 146.4479, armor = 149.7771, speed = 41.10249, pitch = 22.49939, roll = 28.17, yaw = 17.84114, acceleration = 10.13847, rollRate = 49.88538, pitchRate = 44.22903, deceleration = 8.360931, yawRate = 37.47222,},
	shield_0 = { name = "shd_generic", hitpoints = 147.4523, armor = 148.937, regen = 2.908594, front = 596.8306, back = 580.8926,},
	armor_0 = { name = "arm_generic", hitpoints = 307.6643, armor = 305.4179,},
	armor_1 = { name = "arm_generic", hitpoints = 311.5382, armor = 310.5611,},
	capacitor = { name = "cap_generic", hitpoints = 142.8285, armor = 144.1762, rechargeRate = 97.308, energy = 4791.954,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 143.3939, armor = 143.8395, rate = 0.7732094, drain = 0.9802904, maxDamage = 39.22572, shieldEfficiency = 0.5410031, minDamage = 29.70125, ammo = 0, ammo_type = 0, armorEfficiency = 0.5347064,},
}

ObjectTemplates:addTemplate(object_ship_droid_fighter_tier1, "object/ship/droid_fighter_tier1.iff")
