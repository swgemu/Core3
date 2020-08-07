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


object_ship_player_player_tieoppressor = object_ship_player_shared_player_tieoppressor:new {

	name = "player_tieoppressor",
	slideFactor = 1.78,
	chassisHitpoints = 1765,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 294.0562, armor = 287.8408,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 285.8557, armor = 296.4928, speed = 57.99641, pitch = 31.37479, roll = 31.04428, yaw = 30.58509, acceleration = 32.38527, rollRate = 70.04829, pitchRate = 69.29912, deceleration = 38.49465, yawRate = 68.24411,},
	shield_0 = { name = "shd_generic", hitpoints = 289.5158, armor = 296.6571, regen = 7.958282, front = 1063.478, back = 1064.046,},
	armor_0 = { name = "arm_generic", hitpoints = 478.1561, armor = 495.2433,},
	armor_1 = { name = "arm_generic", hitpoints = 479.4083, armor = 490.7244,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 54.81933, energy = 887.7081,},
	booster = { name = "bst_generic", hitpoints = 19.02942, armor = 19.37799, energy = 99.82555, acceleration = 19.31529, speed = 14.31679, energyUsage = 9.992661, rechargeRate = 4.901127,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 197.4888, armor = 193.9926, rate = 0.3089833, drain = 24.2891, maxDamage = 637.2914, shieldEfficiency = 0, minDamage = 534.1018, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_sienar_heatseeker_missile_s01", hitpoints = 195.5367, armor = 195.2974, rate = 14.07183, drain = 52.63816, maxDamage = 1191.985, shieldEfficiency = 0.8767639, minDamage = 656.8978, ammo = 24, ammo_type = 3, armorEfficiency = 0.744046,},
	weapon_2 = { name = "wpn_std_countermeasure", hitpoints = 246.2163, armor = 244.9379, rate = 0.098791, drain = 22.49818, maxDamage = 99.56401, shieldEfficiency = 0, minDamage = 24.45855, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_tieoppressor, "object/ship/player/player_tieoppressor.iff")
