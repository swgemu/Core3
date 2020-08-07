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


object_ship_blacksun_heavy_s04 = object_ship_shared_blacksun_heavy_s04:new {

	name = "blacksun_heavy_s04",
	slideFactor = 1.91,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 292.1461, armor = 299.9766,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 99.05749, armor = 99.15884, speed = 41.03009, pitch = 19.98233, roll = 20.84031, yaw = 20.36813, acceleration = 11.85374, rollRate = 42.8932, pitchRate = 41.96444, deceleration = 15.40626, yawRate = 42.71998,},
	shield_0 = { name = "shd_generic", hitpoints = 766.7513, armor = 493.2606, regen = 4.892366, front = 576.5585, back = 772.7341,},
	armor_0 = { name = "arm_generic", hitpoints = 699.4678, armor = 679.7587,},
	armor_1 = { name = "arm_generic", hitpoints = 670.2651, armor = 675.7422,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.59371, energy = 554.7892,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.50498, armor = 19.24759, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 190.6598, armor = 199.4204, rate = 0.3417881, drain = 23.16432, maxDamage = 398.0238, shieldEfficiency = 0, minDamage = 313.1414, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 191.2408, armor = 194.4547, rate = 0.3281446, drain = 22.93784, maxDamage = 22.84879, shieldEfficiency = 0, minDamage = 23.29939, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_incom_disruptor", hitpoints = 19.62285, armor = 19.18173, rate = 0.3345007, drain = 22.85921, maxDamage = 22.47112, shieldEfficiency = 0, minDamage = 23.24685, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_xwing_missile_s01", hitpoints = 196.0406, armor = 193.7117, rate = 5.791743, drain = 43.39466, maxDamage = 1518.178, shieldEfficiency = 0.8794746, minDamage = 456.2561, ammo = 12, ammo_type = 5, armorEfficiency = 0.2188078,},
}

ObjectTemplates:addTemplate(object_ship_blacksun_heavy_s04, "object/ship/blacksun_heavy_s04.iff")
