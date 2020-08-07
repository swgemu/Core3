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


object_ship_yt1300_tier2 = object_ship_shared_yt1300_tier2:new {

	name = "yt1300_tier2",
	slideFactor = 1.85,
	chassisHitpoints = 1200,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 893.6581, armor = 871.6714,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 880.6724, armor = 871.7419, speed = 43.10583, pitch = 23.63994, roll = 29.02296, yaw = 18.77757, acceleration = 10.02063, rollRate = 52.09806, pitchRate = 46.91024, deceleration = 8.712528, yawRate = 38.31315,},
	shield_0 = { name = "shd_generic", hitpoints = 882.2487, armor = 859.2103, regen = 10.26667, front = 3510.034, back = 3541.974,},
	armor_0 = { name = "arm_generic", hitpoints = 1893.917, armor = 1874.044,},
	armor_1 = { name = "arm_generic", hitpoints = 1851.749, armor = 1828.078,},
	capacitor = { name = "cap_generic", hitpoints = 895.0688, armor = 867.4343, rechargeRate = 96.19093, energy = 4762.29,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 862.7061, armor = 860.2844, rate = 0.7660165, drain = 0.9923657, maxDamage = 171.7632, shieldEfficiency = 0.5382692, minDamage = 124.7775, ammo = 0, ammo_type = 0, armorEfficiency = 0.5345374,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 858.6254, armor = 857.3098, rate = 0.7680718, drain = 0.9776484, maxDamage = 167.8077, shieldEfficiency = 0.5521404, minDamage = 124.3312, ammo = 0, ammo_type = 0, armorEfficiency = 0.5397847,},
}

ObjectTemplates:addTemplate(object_ship_yt1300_tier2, "object/ship/yt1300_tier2.iff")
