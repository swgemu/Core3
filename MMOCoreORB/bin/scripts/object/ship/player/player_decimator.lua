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


object_ship_player_player_decimator = object_ship_player_shared_player_decimator:new {

	name = "player_decimator",
	slideFactor = 1.85,
	chassisHitpoints = 5000,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 395.0898, armor = 393.2448,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 96.26176, armor = 96.47783, speed = 63.61601, pitch = 53.90641, roll = 53.77215, yaw = 20.96006, acceleration = 14.29806, rollRate = 80.7669, pitchRate = 73.72273, deceleration = 13.31472, yawRate = 37.25309,},
	shield_0 = { name = "shd_generic", hitpoints = 383.4029, armor = 490.7114, regen = 2.854131, front = 1576.617, back = 1591.529,},
	armor_0 = { name = "arm_generic", hitpoints = 1092.34, armor = 1052.53,},
	armor_1 = { name = "arm_generic", hitpoints = 1051.848, armor = 1070.727,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 35.51637, energy = 1101.85,},
	booster = { name = "bst_generic", hitpoints = 19.69023, armor = 19.73825, energy = 98.89352, acceleration = 19.44626, speed = 14.42604, energyUsage = 9.96958, rechargeRate = 4.918709,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 190.0977, armor = 192.0175, rate = 0.3419655, drain = 22.89144, maxDamage = 1468.528, shieldEfficiency = 0, minDamage = 745.0324, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 191.437, armor = 192.2777, rate = 0.331361, drain = 22.71493, maxDamage = 949.7935, shieldEfficiency = 0, minDamage = 609.7089, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_xwing_missile_s01", hitpoints = 19.22288, armor = 19.00229, rate = 5.818878, drain = 23.56116, maxDamage = 22.4802, shieldEfficiency = 0, minDamage = 23.33798, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_std_countermeasure", hitpoints = 243.146, armor = 243.0917, rate = 0.09659296, drain = 23.08529, maxDamage = 99.77181, shieldEfficiency = 0, minDamage = 24.74274, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
	lots = 4,
}

ObjectTemplates:addTemplate(object_ship_player_player_decimator, "object/ship/player/player_decimator.iff")
