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


object_ship_hutt_heavy_s01 = object_ship_shared_hutt_heavy_s01:new {

	name = "hutt_heavy_s01",
	slideFactor = 1.91,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 297.4442, armor = 289.4253,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 96.76161, armor = 97.44018, speed = 40.78115, pitch = 20.56229, roll = 20.71312, yaw = 20.68417, acceleration = 11.67269, rollRate = 42.95709, pitchRate = 42.36866, deceleration = 15.17854, yawRate = 42.11485,},
	shield_0 = { name = "shd_generic", hitpoints = 782.3589, armor = 491.2992, regen = 4.952502, front = 588.1797, back = 794.2305,},
	armor_0 = { name = "arm_generic", hitpoints = 692.7128, armor = 688.5148,},
	armor_1 = { name = "arm_generic", hitpoints = 693.2496, armor = 681.1437,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.69736, energy = 563.9179,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.79312, armor = 19.91542, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 195.8733, armor = 192.4973, rate = 0.332729, drain = 22.52327, maxDamage = 396.009, shieldEfficiency = 0, minDamage = 318.6275, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 195.576, armor = 195.8992, rate = 0.3408385, drain = 22.82261, maxDamage = 23.26119, shieldEfficiency = 0, minDamage = 22.91692, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_incom_disruptor", hitpoints = 19.33254, armor = 19.99512, rate = 0.3434378, drain = 23.54662, maxDamage = 22.49919, shieldEfficiency = 0, minDamage = 23.2319, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_hutt_heavy_s01, "object/ship/hutt_heavy_s01.iff")
