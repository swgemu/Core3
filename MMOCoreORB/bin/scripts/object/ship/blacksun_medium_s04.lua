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


object_ship_blacksun_medium_s04 = object_ship_shared_blacksun_medium_s04:new {

	name = "blacksun_medium_s04",
	slideFactor = 1.81,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 293.356, armor = 293.432,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 98.68144, armor = 99.00797, speed = 53.25675, pitch = 33.11143, roll = 33.75666, yaw = 33.20242, acceleration = 16.72407, rollRate = 58.64577, pitchRate = 58.68729, deceleration = 8.331491, yawRate = 60.30414,},
	shield_0 = { name = "shd_generic", hitpoints = 381.2336, armor = 491.4098, regen = 4.954242, front = 299.5086, back = 486.1127,},
	armor_0 = { name = "arm_generic", hitpoints = 296.5755, armor = 298.7503,},
	armor_1 = { name = "arm_generic", hitpoints = 295.6232, armor = 298.6132,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 35.20037, energy = 559.4849,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.48644, armor = 19.61891, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 196.9919, armor = 192.8055, rate = 0.3321354, drain = 23.35678, maxDamage = 243.8342, shieldEfficiency = 0, minDamage = 118.1178, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 192.8759, armor = 195.6249, rate = 0.3418252, drain = 23.27326, maxDamage = 244.8474, shieldEfficiency = 0, minDamage = 115.0876, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_blacksun_medium_s04, "object/ship/blacksun_medium_s04.iff")
