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


object_ship_awing = object_ship_shared_awing:new {

	name = "awing",
	slideFactor = 1.91,
	chassisHitpoints = 300,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 96.9286, armor = 99.09653,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 95.31961, armor = 96.64877, speed = 57.55035, pitch = 31.86163, roll = 31.91895, yaw = 30.78357, acceleration = 21.43661, rollRate = 61.09378, pitchRate = 63.00252, deceleration = 11.00017, yawRate = 63.16784,},
	shield_0 = { name = "shd_generic", hitpoints = 194.4761, armor = 199.3203, regen = 4.820557, front = 491.7482, back = 584.5766,},
	armor_0 = { name = "arm_generic", hitpoints = 484.8529, armor = 498.4129,},
	armor_1 = { name = "arm_generic", hitpoints = 475.0292, armor = 490.1254,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 50.30707, energy = 1259.069,},
	weapon_0 = { name = "wpn_awing_blaster", hitpoints = 196.6696, armor = 195.2839, rate = 0.5019104, drain = 23.47025, maxDamage = 247.3325, shieldEfficiency = 0, minDamage = 171.2778, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_slayn_imagerec_missile_s01", hitpoints = 199.6401, armor = 191.2848, rate = 2.90037, drain = 24.39336, maxDamage = 23.70117, shieldEfficiency = 0, minDamage = 24.4752, ammo = 50, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_awing, "object/ship/awing.iff")
