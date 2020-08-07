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


object_ship_rebel_gunboat_tier5 = object_ship_shared_rebel_gunboat_tier5:new {

	name = "rebel_gunboat_tier5",
	slideFactor = 1.76,
	chassisHitpoints = 24576,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 30302.7, armor = 30302.01,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 31483.76, armor = 31167.5, speed = 46.94733, pitch = 25.24448, roll = 30.83809, yaw = 20.55577, acceleration = 11.18762, rollRate = 58.16631, pitchRate = 50.20848, deceleration = 9.367893, yawRate = 41.47243,},
	shield_0 = { name = "shd_generic", hitpoints = 31336.87, armor = 30806.52, regen = 33.72548, front = 122346.1, back = 124152.1,},
	armor_0 = { name = "arm_generic", hitpoints = 66647.25, armor = 66419.81,},
	armor_1 = { name = "arm_generic", hitpoints = 65835.32, armor = 67582.23,},
	capacitor = { name = "cap_generic", hitpoints = 31729.93, armor = 31076.57, rechargeRate = 96.76312, energy = 4811.185,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 31155.16, armor = 31249.96, rate = 0.7465443, drain = 0.9657047, maxDamage = 817.5482, shieldEfficiency = 0.5499309, minDamage = 512.1674, ammo = 0, ammo_type = 0, armorEfficiency = 0.5332412,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 30276.44, armor = 31604.48, rate = 0.7639401, drain = 0.9506961, maxDamage = 806.1876, shieldEfficiency = 0.5390739, minDamage = 512.0313, ammo = 0, ammo_type = 0, armorEfficiency = 0.535628,},
	weapon_2 = { name = "wpn_incom_disruptor", hitpoints = 31338.07, armor = 30288.72, rate = 0.758294, drain = 0.9921374, maxDamage = 796.3923, shieldEfficiency = 0.539456, minDamage = 488.38, ammo = 0, ammo_type = 0, armorEfficiency = 0.5436608,},
	weapon_3 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 30854.5, armor = 31100.93, rate = 2.890074, drain = 0.9580124, maxDamage = 2459.833, shieldEfficiency = 0.7261251, minDamage = 988.1154, ammo = 4, ammo_type = 20, armorEfficiency = 0.7342832,},
}

ObjectTemplates:addTemplate(object_ship_rebel_gunboat_tier5, "object/ship/rebel_gunboat_tier5.iff")
