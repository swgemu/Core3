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


object_ship_player_player_tieaggressor = object_ship_player_shared_player_tieaggressor:new {

	name = "player_tieaggressor",
	slideFactor = 1.75,
	chassisHitpoints = 1643.2,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 298.3295, armor = 288.2449,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 297.3029, armor = 299.7057, speed = 44.21876, pitch = 30.60036, roll = 30.88204, yaw = 30.50029, acceleration = 18.06754, rollRate = 51.71142, pitchRate = 52.11913, deceleration = 16.10659, yawRate = 51.59421,},
	shield_0 = { name = "shd_generic", hitpoints = 292.3809, armor = 285.8656, regen = 8.660581, front = 1115.249, back = 1090.203,},
	armor_0 = { name = "arm_generic", hitpoints = 381.2762, armor = 388.8333,},
	armor_1 = { name = "arm_generic", hitpoints = 381.7335, armor = 394.17,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 60.38781, energy = 1206.665,},
	booster = { name = "bst_generic", hitpoints = 19.58122, armor = 19.60542, energy = 96.02479, acceleration = 19.77308, speed = 14.30095, energyUsage = 9.64526, rechargeRate = 4.93048,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 198.2316, armor = 198.1158, rate = 0.3410668, drain = 21.98616, maxDamage = 579.8762, shieldEfficiency = 0, minDamage = 463.6437, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 194.1772, armor = 196.5391, rate = 0.3436212, drain = 21.87287, maxDamage = 580.8105, shieldEfficiency = 0, minDamage = 466.3842, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_std_countermeasure", hitpoints = 248.3474, armor = 249.6691, rate = 0.09565558, drain = 23.20383, maxDamage = 96.97808, shieldEfficiency = 0, minDamage = 24.1312, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_tieaggressor, "object/ship/player/player_tieaggressor.iff")
