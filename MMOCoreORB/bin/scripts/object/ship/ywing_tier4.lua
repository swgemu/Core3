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


object_ship_ywing_tier4 = object_ship_shared_ywing_tier4:new {

	name = "ywing_tier4",
	slideFactor = 1.77,
	chassisHitpoints = 1920,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1979.902, armor = 1976.115,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 1999.819, armor = 2044.404, speed = 43.95061, pitch = 24.79912, roll = 29.76071, yaw = 19.3964, acceleration = 10.65536, rollRate = 55.51757, pitchRate = 49.11041, deceleration = 9.134749, yawRate = 40.44541,},
	shield_0 = { name = "shd_generic", hitpoints = 2009.018, armor = 2065.59, regen = 14.78744, front = 8098.977, back = 7981.04,},
	armor_0 = { name = "arm_generic", hitpoints = 4768.317, armor = 4813.546,},
	armor_1 = { name = "arm_generic", hitpoints = 4654.232, armor = 4861.082,},
	capacitor = { name = "cap_generic", hitpoints = 2054.615, armor = 2010.797, rechargeRate = 99.63555, energy = 4849.377,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 2067.688, armor = 2029.737, rate = 0.7674853, drain = 0.98922, maxDamage = 252.4187, shieldEfficiency = 0.5489095, minDamage = 159.7168, ammo = 0, ammo_type = 0, armorEfficiency = 0.5591003,},
	weapon_1 = { name = "wpn_slayn_ioncannon", hitpoints = 2067.888, armor = 2072.527, rate = 0.7413402, drain = 0.9790266, maxDamage = 248.1499, shieldEfficiency = 0.5426723, minDamage = 164.6277, ammo = 0, ammo_type = 0, armorEfficiency = 0.5326373,},
	weapon_2 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 2023.764, armor = 2010.637, rate = 2.900287, drain = 0.9731701, maxDamage = 720.8145, shieldEfficiency = 0.745426, minDamage = 319.3767, ammo = 4, ammo_type = 19, armorEfficiency = 0.749786,},
}

ObjectTemplates:addTemplate(object_ship_ywing_tier4, "object/ship/ywing_tier4.iff")
