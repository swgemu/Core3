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


object_ship_yt1300_tier5 = object_ship_shared_yt1300_tier5:new {

	name = "yt1300_tier5",
	slideFactor = 1.85,
	chassisHitpoints = 4915.2,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 6214.106, armor = 6193.729,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 6102.937, armor = 6119.198, speed = 45.59132, pitch = 25.15963, roll = 31.7135, yaw = 20.33835, acceleration = 11.3687, rollRate = 56.36992, pitchRate = 50.05061, deceleration = 9.325627, yawRate = 42.34739,},
	shield_0 = { name = "shd_generic", hitpoints = 6144.763, armor = 6156.865, regen = 44.74485, front = 25357.68, back = 25464.28,},
	armor_0 = { name = "arm_generic", hitpoints = 13287.58, armor = 13520.52,},
	armor_1 = { name = "arm_generic", hitpoints = 13461.97, armor = 13190.99,},
	capacitor = { name = "cap_generic", hitpoints = 6270.202, armor = 6226.238, rechargeRate = 95.04542, energy = 4903.865,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 6261.076, armor = 6356.028, rate = 0.7580501, drain = 0.987497, maxDamage = 629.0059, shieldEfficiency = 0.5457245, minDamage = 394.5448, ammo = 0, ammo_type = 0, armorEfficiency = 0.5350528,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 6192.769, armor = 6208.924, rate = 0.7416084, drain = 0.958576, maxDamage = 635.5406, shieldEfficiency = 0.5326478, minDamage = 404.89, ammo = 0, ammo_type = 0, armorEfficiency = 0.5556239,},
}

ObjectTemplates:addTemplate(object_ship_yt1300_tier5, "object/ship/yt1300_tier5.iff")
