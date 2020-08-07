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


object_ship_player_player_firespray = object_ship_player_shared_player_firespray:new {

	name = "player_firespray",
	slideFactor = 1.68,
	chassisHitpoints = 1650,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 98.64068, armor = 98.83962,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 97.52977, armor = 97.78248, speed = 54.21301, pitch = 68.48127, roll = 78.06176, yaw = 49.14983, acceleration = 27.58748, rollRate = 91.24681, pitchRate = 87.73351, deceleration = 14.02503, yawRate = 84.78439,},
	shield_0 = { name = "shd_generic", hitpoints = 398.4799, armor = 488.6996, regen = 4.917778, front = 1397.665, back = 1356.204,},
	armor_0 = { name = "arm_generic", hitpoints = 194.2605, armor = 196.2654,},
	armor_1 = { name = "arm_generic", hitpoints = 192.349, armor = 199.9833,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 26.24701, energy = 667.1345,},
	booster = { name = "bst_generic", hitpoints = 19.89734, armor = 19.65063, energy = 95.81511, acceleration = 19.54564, speed = 14.66021, energyUsage = 9.593817, rechargeRate = 4.977661,},
	droid_interface = { name = "ddi_generic", hitpoints = 19.47379, armor = 19.89639,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 196.1458, armor = 192.6049, rate = 0.3447307, drain = 23.1472, maxDamage = 240.1277, shieldEfficiency = 0, minDamage = 118.379, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 199.0284, armor = 190.1464, rate = 0.3285807, drain = 22.91145, maxDamage = 23.30607, shieldEfficiency = 0, minDamage = 23.42046, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_std_countermeasure", hitpoints = 240.6413, armor = 245.1019, rate = 0.09599161, drain = 22.66683, maxDamage = 96.29526, shieldEfficiency = 0, minDamage = 24.61045, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_firespray, "object/ship/player/player_firespray.iff")
