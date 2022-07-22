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


object_ship_bwing = object_ship_shared_bwing:new {

	name = "bwing",
	slideFactor = 1.76,
	chassisHitpoints = 300,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 97.01817, armor = 99.47314,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 95.05576, armor = 97.09964, speed = 47.32478, pitch = 21.87753, roll = 21.96897, yaw = 22.1137, acceleration = 15.78258, rollRate = 50.68687, pitchRate = 52.55415, deceleration = 8.0465, yawRate = 52.0341,},
	shield_0 = { name = "shd_generic", hitpoints = 195.2314, armor = 194.8301, regen = 4.87457, front = 597.3931, back = 684.5637,},
	armor_0 = { name = "arm_generic", hitpoints = 783.9377, armor = 761.3621,},
	armor_1 = { name = "arm_generic", hitpoints = 771.8947, armor = 793.6621,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 69.08517, energy = 1705.532,},
	weapon_0 = { name = "wpn_bwing_blaster", hitpoints = 191.8313, armor = 199.1473, rate = 0.6737685, drain = 31.33705, maxDamage = 303.8985, shieldEfficiency = 0, minDamage = 190.2288, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_bwing_blaster", hitpoints = 198.5948, armor = 193.0309, rate = 0.6452643, drain = 31.25683, maxDamage = 31.70825, shieldEfficiency = 0, minDamage = 31.34731, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_bwing_blaster", hitpoints = 19.09847, armor = 19.98873, rate = 0.6637544, drain = 32.12992, maxDamage = 31.73752, shieldEfficiency = 0, minDamage = 31.91447, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_bwing_blaster", hitpoints = 19.16829, armor = 19.47907, rate = 0.6721096, drain = 32.55756, maxDamage = 32.69202, shieldEfficiency = 0, minDamage = 31.58299, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_bwing, "object/ship/bwing.iff")
