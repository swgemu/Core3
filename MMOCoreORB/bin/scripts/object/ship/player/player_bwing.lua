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


object_ship_player_player_bwing = object_ship_player_shared_player_bwing:new {

	name = "player_bwing",
	slideFactor = 1.72,
	chassisHitpoints = 1765,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 291.346, armor = 292.5736,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 99.66038, armor = 96.96965, speed = 47.48062, pitch = 31.3734, roll = 41.80257, yaw = 21.08492, acceleration = 16.05369, rollRate = 51.62985, pitchRate = 47.80521, deceleration = 11.80832, yawRate = 37.00739,},
	shield_0 = { name = "shd_generic", hitpoints = 385.5213, armor = 495.9176, regen = 3.945815, front = 1470.033, back = 1503.827,},
	armor_0 = { name = "arm_generic", hitpoints = 634.9315, armor = 632.8993,},
	armor_1 = { name = "arm_generic", hitpoints = 635.6597, armor = 619.1967,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 41.09896, energy = 907.3763,},
	booster = { name = "bst_generic", hitpoints = 19.73722, armor = 19.49477, energy = 97.99065, acceleration = 19.81398, speed = 14.62997, energyUsage = 9.972981, rechargeRate = 4.941675,},
	weapon_0 = { name = "wpn_bwing_blaster", hitpoints = 197.8928, armor = 193.6946, rate = 0.3379803, drain = 21.6995, maxDamage = 778.6093, shieldEfficiency = 0, minDamage = 603.0428, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_bwing_blaster", hitpoints = 193.2332, armor = 191.1927, rate = 0.3366114, drain = 55.80855, maxDamage = 1526.396, shieldEfficiency = 0.6006526, minDamage = 859.6385, ammo = 32, ammo_type = 6, armorEfficiency = 0.5283666,},
	weapon_2 = { name = "wpn_bwing_blaster", hitpoints = 19.43774, armor = 19.04127, rate = 0.3371382, drain = 22.59248, maxDamage = 23.3445, shieldEfficiency = 0, minDamage = 23.21187, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_bwing_blaster", hitpoints = 19.9879, armor = 19.6372, rate = 0.333549, drain = 22.50311, maxDamage = 23.53538, shieldEfficiency = 0, minDamage = 23.35286, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_4 = { name = "wpn_std_countermeasure", hitpoints = 246.8604, armor = 245.1107, rate = 9.518538, drain = 22.57677, maxDamage = 99.23679, shieldEfficiency = 0, minDamage = 24.96139, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_bwing, "object/ship/player/player_bwing.iff")
