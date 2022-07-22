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


object_ship_player_player_tie_in = object_ship_player_shared_player_tie_in:new {

	name = "player_tie_in",
	slideFactor = 1.78,
	chassisHitpoints = 1350,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 298.64, armor = 287.6893,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 289.3276, armor = 299.3239, speed = 46.66897, pitch = 58.4896, roll = 63.43312, yaw = 38.4486, acceleration = 16.74496, rollRate = 81.27548, pitchRate = 79.0061, deceleration = 15.20113, yawRate = 72.29495,},
	shield_0 = { name = "shd_generic", hitpoints = 299.9817, armor = 292.5083, regen = 0, front = 0, back = 0,},
	armor_0 = { name = "arm_generic", hitpoints = 399.2632, armor = 396.0279,},
	armor_1 = { name = "arm_generic", hitpoints = 380.4937, armor = 398.0653,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 46.36437, energy = 772.0099,},
	weapon_0 = { name = "wpn_generic", hitpoints = 199.192, armor = 199.9691, rate = 0.27354, drain = 26.82865, maxDamage = 559.7731, shieldEfficiency = 0, minDamage = 497.5668, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 197.5431, armor = 196.5674, rate = 9.159794, drain = 30.68873, maxDamage = 803.181, shieldEfficiency = 0.7717161, minDamage = 507.7298, ammo = 8, ammo_type = 2, armorEfficiency = 0.5542418,},
	weapon_2 = { name = "wpn_std_countermeasure", hitpoints = 245.2573, armor = 240.0122, rate = 0.09882718, drain = 23.22336, maxDamage = 95.98, shieldEfficiency = 0, minDamage = 24.23151, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_tie_in, "object/ship/player/player_tie_in.iff")
