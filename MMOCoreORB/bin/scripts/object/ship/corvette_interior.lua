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


object_ship_corvette_interior = object_ship_shared_corvette_interior:new {

	name = "corvette_interior",
	slideFactor = 1.76,
	chassisHitpoints = 30000,
	chassisMass = 50000,
	reactor = { name = "rct_generic", hitpoints = 4804.422, armor = 1970.196,},
	engine = { name = "eng_generic", hitpoints = 4963.667, armor = 1937.152, speed = 30.60647, pitch = 2.889934, roll = 2.900048, yaw = 2.95273, acceleration = 7.938663, rollRate = 2.950962, pitchRate = 2.923276, deceleration = 7.912291, yawRate = 2.940777,},
	shield_0 = { name = "shd_generic", hitpoints = 9748.484, armor = 2932.082, regen = 48.52613, front = 5984.953, back = 5996.455,},
	shield_1 = { name = "shd_generic", hitpoints = 4860.984, armor = 2883.421, regen = 39.03818, front = 2963.118, back = 2923.01,},
	armor_0 = { name = "arm_generic", hitpoints = 4834.403, armor = 4816.615,},
	armor_1 = { name = "arm_generic", hitpoints = 4852.749, armor = 4906.538,},
	capacitor = { name = "cap_generic", hitpoints = 4937.227, armor = 994.8969, rechargeRate = 127.5653, energy = 2312.452,},
	bridge = { name = "bdg_generic", hitpoints = 4808.085, armor = 4984.758,},
	hangar = { name = "hgr_generic", hitpoints = 9665.141, armor = 9510.316,},
	targeting_station = { name = "tst_generic", hitpoints = 1977.683, armor = 1925.883,},
	weapon_0 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 960.4971, armor = 584.9735, rate = 0.4627544, drain = 42.41002, maxDamage = 639.845, shieldEfficiency = 0, minDamage = 502.185, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 963.1765, armor = 574.8383, rate = 0.4604894, drain = 43.60727, maxDamage = 629.8862, shieldEfficiency = 0, minDamage = 508.5163, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 990.0389, armor = 589.8812, rate = 0.4499912, drain = 42.99593, maxDamage = 617.4939, shieldEfficiency = 0, minDamage = 508.2635, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 982.6238, armor = 575.062, rate = 0.4687122, drain = 42.32259, maxDamage = 622.2676, shieldEfficiency = 0, minDamage = 516.2555, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_4 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 980.2834, armor = 584.1869, rate = 0.470078, drain = 41.77011, maxDamage = 638.7194, shieldEfficiency = 0, minDamage = 507.8376, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_5 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 954.9688, armor = 575.6172, rate = 0.4695181, drain = 42.65598, maxDamage = 611.2302, shieldEfficiency = 0, minDamage = 509.77, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_6 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 982.5795, armor = 578.5784, rate = 0.4682359, drain = 42.43586, maxDamage = 610.5309, shieldEfficiency = 0, minDamage = 497.47, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_corvette_interior, "object/ship/corvette_interior.iff")
