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


object_ship_imperial_gunboat_tier2 = object_ship_shared_imperial_gunboat_tier2:new {

	name = "imperial_gunboat_tier2",
	slideFactor = 1.81,
	chassisHitpoints = 6000,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 4354.354, armor = 4398.079,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 4429.515, armor = 4474.321, speed = 42.91095, pitch = 22.62639, roll = 28.39916, yaw = 18.23633, acceleration = 10.39188, rollRate = 53.18192, pitchRate = 47.23963, deceleration = 8.653737, yawRate = 39.15161,},
	shield_0 = { name = "shd_generic", hitpoints = 4320.633, armor = 4436.872, regen = 7.997239, front = 17524.19, back = 17495.07,},
	armor_0 = { name = "arm_generic", hitpoints = 9384.212, armor = 9250.882,},
	armor_1 = { name = "arm_generic", hitpoints = 9492.329, armor = 9576.867,},
	capacitor = { name = "cap_generic", hitpoints = 4277.164, armor = 4413.979, rechargeRate = 95.83939, energy = 4866.605,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 4391.746, armor = 4430.368, rate = 0.7666303, drain = 0.9665427, maxDamage = 211.379, shieldEfficiency = 0.5576791, minDamage = 154.8593, ammo = 0, ammo_type = 0, armorEfficiency = 0.5553802,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 4483.669, armor = 4299.125, rate = 0.7429315, drain = 0.9681085, maxDamage = 219.181, shieldEfficiency = 0.5503492, minDamage = 157.4311, ammo = 0, ammo_type = 0, armorEfficiency = 0.5344643,},
	weapon_2 = { name = "wpn_tieadvanced_blaster", hitpoints = 4322.03, armor = 4283.3, rate = 0.7786904, drain = 0.9810778, maxDamage = 210.5447, shieldEfficiency = 0.5358186, minDamage = 153.6607, ammo = 0, ammo_type = 0, armorEfficiency = 0.5361429,},
	weapon_3 = { name = "wpn_tieadvanced_blaster", hitpoints = 4444.815, armor = 4451.11, rate = 0.7431949, drain = 0.9959613, maxDamage = 212.8519, shieldEfficiency = 0.5427443, minDamage = 153.1492, ammo = 0, ammo_type = 0, armorEfficiency = 0.5402256,},
	weapon_4 = { name = "wpn_tieadvanced_blaster", hitpoints = 4359.648, armor = 4277.894, rate = 0.7458646, drain = 0.9695191, maxDamage = 217.7049, shieldEfficiency = 0.5420979, minDamage = 150.785, ammo = 0, ammo_type = 0, armorEfficiency = 0.5384629,},
	weapon_5 = { name = "wpn_tieadvanced_blaster", hitpoints = 4353.339, armor = 4450.987, rate = 0.7740715, drain = 0.9554609, maxDamage = 219.8736, shieldEfficiency = 0.5554333, minDamage = 154.5607, ammo = 0, ammo_type = 0, armorEfficiency = 0.5551569,},
}

ObjectTemplates:addTemplate(object_ship_imperial_gunboat_tier2, "object/ship/imperial_gunboat_tier2.iff")
