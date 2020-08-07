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


object_ship_xwing = object_ship_shared_xwing:new {

	name = "xwing",
	slideFactor = 1.75,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 96.69081, armor = 97.42879,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 95.81568, armor = 99.13993, speed = 48.93302, pitch = 28.37103, roll = 27.76255, yaw = 27.82128, acceleration = 11.80688, rollRate = 54.09831, pitchRate = 55.71315, deceleration = 3.191922, yawRate = 54.81736,},
	shield_0 = { name = "shd_generic", hitpoints = 399.7256, armor = 485.7532, regen = 4.800375, front = 479.5626, back = 580.6174,},
	armor_0 = { name = "arm_generic", hitpoints = 490.4126, armor = 489.5004,},
	armor_1 = { name = "arm_generic", hitpoints = 483.9158, armor = 498.2762,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.81926, energy = 548.5037,},
	droid_interface = { name = "ddi_generic", hitpoints = 19.59281, armor = 19.39399,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 198.5576, armor = 197.0712, rate = 0.3380315, drain = 22.99146, maxDamage = 226.5862, shieldEfficiency = 0, minDamage = 184.2287, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 193.8946, armor = 195.9465, rate = 0.3332753, drain = 22.88859, maxDamage = 23.48292, shieldEfficiency = 0, minDamage = 22.63813, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_incom_proton_missile_s01", hitpoints = 19.99748, armor = 19.65753, rate = 2.857407, drain = 23.48966, maxDamage = 23.17945, shieldEfficiency = 0, minDamage = 22.86777, ammo = 50, ammo_type = 5, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_xwing, "object/ship/xwing.iff")
