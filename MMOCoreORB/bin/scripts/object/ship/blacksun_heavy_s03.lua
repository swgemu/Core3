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


object_ship_blacksun_heavy_s03 = object_ship_shared_blacksun_heavy_s03:new {

	name = "blacksun_heavy_s03",
	slideFactor = 1.91,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 287.3099, armor = 288.0729,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 95.20724, armor = 98.14094, speed = 41.90319, pitch = 20.66788, roll = 20.67283, yaw = 20.06975, acceleration = 11.69386, rollRate = 41.13512, pitchRate = 42.75179, deceleration = 15.33678, yawRate = 42.54443,},
	shield_0 = { name = "shd_generic", hitpoints = 794.6674, armor = 484.2393, regen = 4.759703, front = 580.9474, back = 763.0298,},
	armor_0 = { name = "arm_generic", hitpoints = 676.2538, armor = 668.3644,},
	armor_1 = { name = "arm_generic", hitpoints = 684.7626, armor = 699.6224,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.07034, energy = 561.3565,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.19639, armor = 19.77542, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 190.5733, armor = 195.3184, rate = 0.3378442, drain = 23.51002, maxDamage = 406.0521, shieldEfficiency = 0, minDamage = 309.6794, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 191.82, armor = 199.2871, rate = 0.3415413, drain = 22.60064, maxDamage = 22.93218, shieldEfficiency = 0, minDamage = 23.40323, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_incom_disruptor", hitpoints = 19.22737, armor = 19.43498, rate = 0.3410545, drain = 23.42756, maxDamage = 22.6515, shieldEfficiency = 0, minDamage = 23.4563, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_xwing_missile_s01", hitpoints = 192.8066, armor = 190.133, rate = 5.847064, drain = 41.83318, maxDamage = 1502.547, shieldEfficiency = 0.8760692, minDamage = 462.232, ammo = 12, ammo_type = 5, armorEfficiency = 0.2199907,},
}

ObjectTemplates:addTemplate(object_ship_blacksun_heavy_s03, "object/ship/blacksun_heavy_s03.iff")
