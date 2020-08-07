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


object_ship_bwing_tier4 = object_ship_shared_bwing_tier4:new {

	name = "bwing_tier4",
	slideFactor = 1.67,
	chassisHitpoints = 2304,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 2396.823, armor = 2481.65,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 2477.836, armor = 2455.613, speed = 45.05735, pitch = 24.70127, roll = 30.81115, yaw = 19.2093, acceleration = 11.10555, rollRate = 55.44261, pitchRate = 48.77937, deceleration = 9.054961, yawRate = 41.36264,},
	shield_0 = { name = "shd_generic", hitpoints = 2464.322, armor = 2376.63, regen = 14.47356, front = 9492.574, back = 9532.168,},
	armor_0 = { name = "arm_generic", hitpoints = 5234.923, armor = 5045.939,},
	armor_1 = { name = "arm_generic", hitpoints = 5087.338, armor = 5208.458,},
	capacitor = { name = "cap_generic", hitpoints = 2384.094, armor = 2403.74, rechargeRate = 99.42451, energy = 4830.62,},
	weapon_0 = { name = "wpn_bwing_blaster", hitpoints = 2429.94, armor = 2434.238, rate = 0.749474, drain = 0.9929225, maxDamage = 267.0337, shieldEfficiency = 0.5503859, minDamage = 180.9278, ammo = 0, ammo_type = 0, armorEfficiency = 0.5352822,},
	weapon_1 = { name = "wpn_bwing_blaster", hitpoints = 2382.056, armor = 2372.948, rate = 0.770486, drain = 0.9970462, maxDamage = 272.1023, shieldEfficiency = 0.5366835, minDamage = 173.2651, ammo = 0, ammo_type = 0, armorEfficiency = 0.5396137,},
	weapon_2 = { name = "wpn_bwing_blaster", hitpoints = 2377.097, armor = 2387.208, rate = 0.7462349, drain = 0.9989737, maxDamage = 264.6347, shieldEfficiency = 0.5534288, minDamage = 172.2555, ammo = 0, ammo_type = 0, armorEfficiency = 0.5502954,},
	weapon_3 = { name = "wpn_bwing_blaster", hitpoints = 2461.479, armor = 2382.379, rate = 0.7713439, drain = 0.9848549, maxDamage = 264.9861, shieldEfficiency = 0.5331391, minDamage = 173.3985, ammo = 0, ammo_type = 0, armorEfficiency = 0.5520632,},
	weapon_4 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 2477.055, armor = 2391.612, rate = 2.852365, drain = 0.9985459, maxDamage = 802.3948, shieldEfficiency = 0.7376821, minDamage = 348.5668, ammo = 4, ammo_type = 19, armorEfficiency = 0.7234247,},
}

ObjectTemplates:addTemplate(object_ship_bwing_tier4, "object/ship/bwing_tier4.iff")
