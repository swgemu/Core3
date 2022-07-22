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


object_ship_ykl37r_tier2 = object_ship_shared_ykl37r_tier2:new {

	name = "ykl37r_tier2",
	slideFactor = 1.79,
	chassisHitpoints = 1200,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 872.6747, armor = 869.894,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 888.89, armor = 879.7, speed = 41.47534, pitch = 23.42888, roll = 29.43946, yaw = 18.36957, acceleration = 10.39865, rollRate = 52.72282, pitchRate = 46.44775, deceleration = 8.840676, yawRate = 38.99073,},
	shield_0 = { name = "shd_generic", hitpoints = 867.1155, armor = 899.4497, regen = 10.79965, front = 3503.933, back = 3598.179,},
	armor_0 = { name = "arm_generic", hitpoints = 1827.938, armor = 1859.58,},
	armor_1 = { name = "arm_generic", hitpoints = 1830.636, armor = 1894.241,},
	capacitor = { name = "cap_generic", hitpoints = 864.7682, armor = 870.0262, rechargeRate = 95.88049, energy = 4779.38,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 886.391, armor = 863.4041, rate = 0.7740316, drain = 0.9976591, maxDamage = 175.2804, shieldEfficiency = 0.5487179, minDamage = 120.5857, ammo = 0, ammo_type = 0, armorEfficiency = 0.5568774,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 885.5485, armor = 877.8143, rate = 0.7748212, drain = 0.9610562, maxDamage = 175.0733, shieldEfficiency = 0.5378847, minDamage = 122.3426, ammo = 0, ammo_type = 0, armorEfficiency = 0.5396201,},
	weapon_2 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 898.4353, armor = 882.0982, rate = 2.981131, drain = 0.9909087, maxDamage = 503.0114, shieldEfficiency = 0.7317231, minDamage = 240.3649, ammo = 5, ammo_type = 17, armorEfficiency = 0.7321559,},
}

ObjectTemplates:addTemplate(object_ship_ykl37r_tier2, "object/ship/ykl37r_tier2.iff")
