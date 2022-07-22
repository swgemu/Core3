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


object_ship_hutt_heavy_s02 = object_ship_shared_hutt_heavy_s02:new {

	name = "hutt_heavy_s02",
	slideFactor = 1.91,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 289.5616, armor = 286.5511,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 99.76371, armor = 98.69742, speed = 40.94764, pitch = 20.49002, roll = 20.93955, yaw = 20.38556, acceleration = 11.95677, rollRate = 41.72429, pitchRate = 42.94921, deceleration = 15.22245, yawRate = 42.79782,},
	shield_0 = { name = "shd_generic", hitpoints = 779.4025, armor = 485.6872, regen = 4.796007, front = 593.4938, back = 761.457,},
	armor_0 = { name = "arm_generic", hitpoints = 698.0486, armor = 697.7805,},
	armor_1 = { name = "arm_generic", hitpoints = 670.7258, armor = 683.1326,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.68277, energy = 559.967,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.06267, armor = 19.2682, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 199.2905, armor = 194.6028, rate = 0.3434319, drain = 22.58564, maxDamage = 399.6337, shieldEfficiency = 0, minDamage = 307.8379, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 195.6924, armor = 191.4443, rate = 0.336146, drain = 22.88829, maxDamage = 22.6826, shieldEfficiency = 0, minDamage = 23.57692, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_incom_disruptor", hitpoints = 19.04434, armor = 19.15512, rate = 0.3297685, drain = 23.16837, maxDamage = 22.89623, shieldEfficiency = 0, minDamage = 22.65446, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_hutt_heavy_s02, "object/ship/hutt_heavy_s02.iff")
