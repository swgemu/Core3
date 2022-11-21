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


object_ship_blacksun_heavy_s01 = object_ship_shared_blacksun_heavy_s01:new {

	name = "blacksun_heavy_s01",
	slideFactor = 1.91,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 292.1168, armor = 287.4563,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 96.13712, armor = 96.53938, speed = 40.83212, pitch = 20.29032, roll = 20.26504, yaw = 20.7813, acceleration = 11.60626, rollRate = 42.26531, pitchRate = 41.75356, deceleration = 14.92155, yawRate = 41.42518,},
	shield_0 = { name = "shd_generic", hitpoints = 792.137, armor = 479.3623, regen = 4.953176, front = 591.0793, back = 774.5934,},
	armor_0 = { name = "arm_generic", hitpoints = 667.6582, armor = 681.3739,},
	armor_1 = { name = "arm_generic", hitpoints = 691.666, armor = 699.6349,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.94182, energy = 559.7447,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.72693, armor = 19.48062, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 198.7599, armor = 197.0094, rate = 0.3409268, drain = 22.87353, maxDamage = 408.2436, shieldEfficiency = 0, minDamage = 316.5556, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 191.5975, armor = 198.3509, rate = 0.3339383, drain = 22.88681, maxDamage = 23.11802, shieldEfficiency = 0, minDamage = 23.51607, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_incom_disruptor", hitpoints = 19.40996, armor = 19.26176, rate = 0.3334805, drain = 22.82965, maxDamage = 22.52002, shieldEfficiency = 0, minDamage = 23.29776, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_xwing_missile_s01", hitpoints = 194.675, armor = 193.6782, rate = 5.972951, drain = 43.18543, maxDamage = 1493.766, shieldEfficiency = 0.8716478, minDamage = 448.0993, ammo = 12, ammo_type = 5, armorEfficiency = 0.2274433,},
}

ObjectTemplates:addTemplate(object_ship_blacksun_heavy_s01, "object/ship/blacksun_heavy_s01.iff")
