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


object_ship_corvette = object_ship_shared_corvette:new {

	name = "corvette",
	slideFactor = 1.76,
	chassisHitpoints = 60000,
	chassisMass = 50000,
	reactor = { name = "rct_generic", hitpoints = 9674.288, armor = 4881.868,},
	engine = { name = "eng_generic", hitpoints = 9594.958, armor = 4978.163, speed = 31.9317, pitch = 2.944551, roll = 2.927662, yaw = 2.868505, acceleration = 7.821859, rollRate = 2.974, pitchRate = 2.871924, deceleration = 7.988746, yawRate = 2.910846,},
	shield_0 = { name = "shd_generic", hitpoints = 9892.057, armor = 4900.199, regen = 49.21274, front = 19544.95, back = 19007.78,},
	shield_1 = { name = "shd_generic", hitpoints = 9715.883, armor = 4923.668, regen = 38.44461, front = 19376.71, back = 19435.9,},
	armor_0 = { name = "arm_generic", hitpoints = 14480.05, armor = 14479.98,},
	armor_1 = { name = "arm_generic", hitpoints = 14752.64, armor = 14832.28,},
	capacitor = { name = "cap_generic", hitpoints = 9740.764, armor = 4758.048, rechargeRate = 126.9889, energy = 2246.532,},
	bridge = { name = "bdg_generic", hitpoints = 4750.398, armor = 4945.905,},
	hangar = { name = "hgr_generic", hitpoints = 9650.82, armor = 9845.282,},
	targeting_station = { name = "tst_generic", hitpoints = 9661.836, armor = 9978.678,},
	weapon_0 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 7703.324, armor = 3880.572, rate = 0.4672856, drain = 42.10088, maxDamage = 625.5246, shieldEfficiency = 0, minDamage = 499.1971, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 7857.867, armor = 3980.875, rate = 0.4670727, drain = 42.17555, maxDamage = 632.8209, shieldEfficiency = 0, minDamage = 518.6584, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 7922.351, armor = 3871.706, rate = 0.4668665, drain = 41.76069, maxDamage = 634.3734, shieldEfficiency = 0, minDamage = 504.8332, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 7634.258, armor = 3887.017, rate = 0.4585881, drain = 43.86401, maxDamage = 609.1431, shieldEfficiency = 0, minDamage = 504.0832, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_4 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 7657.807, armor = 3977.964, rate = 0.4528297, drain = 42.56411, maxDamage = 629.0568, shieldEfficiency = 0, minDamage = 496.6231, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_5 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 7865.533, armor = 3803.612, rate = 0.4593948, drain = 43.20669, maxDamage = 636.5024, shieldEfficiency = 0, minDamage = 502.6304, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_6 = { name = "wpn_corvette_turret_sm_s01", hitpoints = 7954.511, armor = 3934.32, rate = 0.4616615, drain = 42.60634, maxDamage = 621.5447, shieldEfficiency = 0, minDamage = 506.4337, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_corvette, "object/ship/corvette.iff")
