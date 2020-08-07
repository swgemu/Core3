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


object_ship_z95_tier2 = object_ship_shared_z95_tier2:new {

	name = "z95_tier2",
	slideFactor = 1.84,
	chassisHitpoints = 600,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 440.7987, armor = 445.9872,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 438.3741, armor = 443.3789, speed = 45.74054, pitch = 23.20255, roll = 28.0647, yaw = 18.07193, acceleration = 11.42927, rollRate = 52.44942, pitchRate = 46.82407, deceleration = 8.835044, yawRate = 37.80058,},
	shield_0 = { name = "shd_generic", hitpoints = 441.599, armor = 442.5183, regen = 5.231143, front = 1913.943, back = 1953.731,},
	armor_0 = { name = "arm_generic", hitpoints = 729.6221, armor = 755.8477,},
	armor_1 = { name = "arm_generic", hitpoints = 736.4781, armor = 746.6008,},
	capacitor = { name = "cap_generic", hitpoints = 449.4066, armor = 444.8651, rechargeRate = 95.57732, energy = 4831.352,},
	weapon_0 = { name = "wpn_z95_blaster", hitpoints = 440.9713, armor = 443.8295, rate = 0.7714736, drain = 0.9793235, maxDamage = 79.83333, shieldEfficiency = 0.5581539, minDamage = 59.24998, ammo = 0, ammo_type = 0, armorEfficiency = 0.5562814,},
}

ObjectTemplates:addTemplate(object_ship_z95_tier2, "object/ship/z95_tier2.iff")
