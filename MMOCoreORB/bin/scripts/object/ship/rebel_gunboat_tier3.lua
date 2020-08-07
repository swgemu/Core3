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


object_ship_rebel_gunboat_tier3 = object_ship_shared_rebel_gunboat_tier3:new {

	name = "rebel_gunboat_tier3",
	slideFactor = 1.76,
	chassisHitpoints = 12000,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 10274.32, armor = 10665.58,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 10337.58, armor = 10676.53, speed = 42.75221, pitch = 23.84349, roll = 30.02824, yaw = 18.76913, acceleration = 10.74359, rollRate = 55.20356, pitchRate = 47.02589, deceleration = 8.837842, yawRate = 39.92463,},
	shield_0 = { name = "shd_generic", hitpoints = 10742.18, armor = 10505.14, regen = 13.58685, front = 42798.16, back = 41652.6,},
	armor_0 = { name = "arm_generic", hitpoints = 22343.97, armor = 22299.9,},
	armor_1 = { name = "arm_generic", hitpoints = 22320.88, armor = 22498.42,},
	capacitor = { name = "cap_generic", hitpoints = 10631.83, armor = 10263.94, rechargeRate = 96.24628, energy = 4937.143,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 10382.89, armor = 10661.86, rate = 0.7604854, drain = 0.9592716, maxDamage = 397.7962, shieldEfficiency = 0.5366882, minDamage = 271.4058, ammo = 0, ammo_type = 0, armorEfficiency = 0.5341818,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 10590.64, armor = 10732.33, rate = 0.7754498, drain = 0.9541319, maxDamage = 387.453, shieldEfficiency = 0.5457196, minDamage = 276.358, ammo = 0, ammo_type = 0, armorEfficiency = 0.5362667,},
	weapon_2 = { name = "wpn_incom_disruptor", hitpoints = 10312.72, armor = 10754.29, rate = 0.7475817, drain = 0.9682286, maxDamage = 402.331, shieldEfficiency = 0.5462911, minDamage = 268.8446, ammo = 0, ammo_type = 0, armorEfficiency = 0.5389304,},
	weapon_3 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 10776, armor = 10261.51, rate = 2.86453, drain = 0.9526157, maxDamage = 1173.166, shieldEfficiency = 0.7473319, minDamage = 534.4631, ammo = 4, ammo_type = 18, armorEfficiency = 0.7199593,},
}

ObjectTemplates:addTemplate(object_ship_rebel_gunboat_tier3, "object/ship/rebel_gunboat_tier3.iff")
