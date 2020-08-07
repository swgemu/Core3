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


object_ship_smuggler_warlord_ship_tier5 = object_ship_shared_smuggler_warlord_ship_tier5:new {

	name = "smuggler_warlord_ship_tier5",
	slideFactor = 1.76,
	chassisHitpoints = 24576,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 31386.49, armor = 30293.33,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 30389.72, armor = 30835.02, speed = 47.26063, pitch = 25.03313, roll = 31.91826, yaw = 19.66456, acceleration = 11.11269, rollRate = 57.05925, pitchRate = 51.61772, deceleration = 9.771538, yawRate = 41.20433,},
	shield_0 = { name = "shd_generic", hitpoints = 31402.46, armor = 31010.43, regen = 33.14576, front = 122274.7, back = 121739.1,},
	armor_0 = { name = "arm_generic", hitpoints = 66708.64, armor = 65379.82,},
	armor_1 = { name = "arm_generic", hitpoints = 66254.77, armor = 67684.44,},
	capacitor = { name = "cap_generic", hitpoints = 31114.65, armor = 30418.6, rechargeRate = 96.73544, energy = 4795.968,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 31080.04, armor = 31538.75, rate = 0.7740622, drain = 0.9541933, maxDamage = 822.608, shieldEfficiency = 0.543123, minDamage = 500.4481, ammo = 0, ammo_type = 0, armorEfficiency = 0.5484719,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 30631.83, armor = 31157.42, rate = 0.7592158, drain = 0.9543359, maxDamage = 786.8008, shieldEfficiency = 0.5462517, minDamage = 499.3675, ammo = 0, ammo_type = 0, armorEfficiency = 0.5474174,},
	weapon_2 = { name = "wpn_incom_blaster", hitpoints = 30718.37, armor = 31543.01, rate = 0.7739112, drain = 0.9513081, maxDamage = 793.236, shieldEfficiency = 0.5322735, minDamage = 504.7442, ammo = 0, ammo_type = 0, armorEfficiency = 0.5376089,},
	weapon_3 = { name = "wpn_incom_disruptor", hitpoints = 31456.62, armor = 30455.06, rate = 0.7774477, drain = 0.9541983, maxDamage = 807.7487, shieldEfficiency = 0.5575209, minDamage = 492.3758, ammo = 0, ammo_type = 0, armorEfficiency = 0.5576629,},
	weapon_4 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 30513.63, armor = 30367.95, rate = 2.948318, drain = 0.9596375, maxDamage = 2372.608, shieldEfficiency = 0.7232905, minDamage = 1000.985, ammo = 4, ammo_type = 20, armorEfficiency = 0.719323,},
}

ObjectTemplates:addTemplate(object_ship_smuggler_warlord_ship_tier5, "object/ship/smuggler_warlord_ship_tier5.iff")
