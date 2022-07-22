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


object_ship_ykl37r_tier1 = object_ship_shared_ykl37r_tier1:new {

	name = "ykl37r_tier1",
	slideFactor = 1.79,
	chassisHitpoints = 480,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 292.8192, armor = 287.2527,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 285.5395, armor = 291.4437, speed = 41.97559, pitch = 22.18296, roll = 28.52147, yaw = 17.76159, acceleration = 10.00992, rollRate = 52.08552, pitchRate = 45.40667, deceleration = 8.276476, yawRate = 37.13644,},
	shield_0 = { name = "shd_generic", hitpoints = 293.622, armor = 294.6464, regen = 5.945843, front = 1167.439, back = 1143.066,},
	armor_0 = { name = "arm_generic", hitpoints = 638.6033, armor = 621.0499,},
	armor_1 = { name = "arm_generic", hitpoints = 608.6528, armor = 635.1414,},
	capacitor = { name = "cap_generic", hitpoints = 287.7452, armor = 299.4228, rechargeRate = 96.08783, energy = 4805.798,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 294.4014, armor = 299.2868, rate = 0.7738502, drain = 0.9876657, maxDamage = 78.63071, shieldEfficiency = 0.5479504, minDamage = 59.84946, ammo = 0, ammo_type = 0, armorEfficiency = 0.538473,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 291.4161, armor = 299.9052, rate = 0.7737715, drain = 0.9912473, maxDamage = 78.31697, shieldEfficiency = 0.54124, minDamage = 59.64186, ammo = 0, ammo_type = 0, armorEfficiency = 0.5413358,},
	weapon_2 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 296.9327, armor = 288.4706, rate = 2.94689, drain = 0.9600315, maxDamage = 231.6065, shieldEfficiency = 0.7213454, minDamage = 119.9591, ammo = 5, ammo_type = 16, armorEfficiency = 0.7266638,},
}

ObjectTemplates:addTemplate(object_ship_ykl37r_tier1, "object/ship/ykl37r_tier1.iff")
