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


object_ship_blacksun_heavy_s02 = object_ship_shared_blacksun_heavy_s02:new {

	name = "blacksun_heavy_s02",
	slideFactor = 1.91,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 289.257, armor = 296.9248,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 96.91313, armor = 99.06725, speed = 41.25237, pitch = 20.84941, roll = 20.05498, yaw = 20.97178, acceleration = 11.8811, rollRate = 41.48341, pitchRate = 42.08025, deceleration = 15.36708, yawRate = 41.34274,},
	shield_0 = { name = "shd_generic", hitpoints = 781.8044, armor = 492.0551, regen = 4.904438, front = 593.3419, back = 795.2986,},
	armor_0 = { name = "arm_generic", hitpoints = 685.8979, armor = 670.9169,},
	armor_1 = { name = "arm_generic", hitpoints = 675.7996, armor = 698.5225,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.37733, energy = 545.6757,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.51027, armor = 19.0483, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 196.5308, armor = 192.6455, rate = 0.3317102, drain = 23.01148, maxDamage = 396.2686, shieldEfficiency = 0, minDamage = 313.6201, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 194.3995, armor = 191.7472, rate = 0.3362818, drain = 23.29151, maxDamage = 23.18861, shieldEfficiency = 0, minDamage = 22.59388, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_incom_disruptor", hitpoints = 19.57657, armor = 19.44282, rate = 0.3346006, drain = 23.19162, maxDamage = 22.60096, shieldEfficiency = 0, minDamage = 22.83895, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_xwing_missile_s01", hitpoints = 195.3844, armor = 195.7436, rate = 5.79167, drain = 43.1535, maxDamage = 1499.29, shieldEfficiency = 0.895201, minDamage = 461.4136, ammo = 12, ammo_type = 5, armorEfficiency = 0.225759,},
}

ObjectTemplates:addTemplate(object_ship_blacksun_heavy_s02, "object/ship/blacksun_heavy_s02.iff")
