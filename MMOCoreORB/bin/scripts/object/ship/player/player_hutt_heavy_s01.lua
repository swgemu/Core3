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


object_ship_player_player_hutt_heavy_s01 = object_ship_player_shared_player_hutt_heavy_s01:new {

	name = "player_hutt_heavy_s01",
	slideFactor = 1.95,
	chassisHitpoints = 6000,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 3132.696, armor = 1588.452,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 3177.075, armor = 1560.314, speed = 59.2011, pitch = 45.70192, roll = 46.76923, yaw = 45.68584, acceleration = 16.38588, rollRate = 71.96271, pitchRate = 71.1189, deceleration = 14.32747, yawRate = 68.89223,},
	shield_0 = { name = "shd_generic", hitpoints = 3167.762, armor = 1571.964, regen = 28.76218, front = 9736.661, back = 9566.941,},
	armor_0 = { name = "arm_generic", hitpoints = 7871.088, armor = 7775.017,},
	armor_1 = { name = "arm_generic", hitpoints = 7903.808, armor = 7700.184,},
	capacitor = { name = "cap_generic", hitpoints = 3101.883, armor = 1588.53, rechargeRate = 47.75232, energy = 967.9125,},
	booster = { name = "bst_generic", hitpoints = 19.3141, armor = 19.11369, energy = 98.73798, acceleration = 19.63684, speed = 14.54045, energyUsage = 9.681401, rechargeRate = 4.961435,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 3166.254, armor = 1562.477, rate = 0.3102954, drain = 29.88041, maxDamage = 5309.712, shieldEfficiency = 0, minDamage = 3808.266, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 3139.729, armor = 1528.717, rate = 0.3083006, drain = 29.2402, maxDamage = 5196.395, shieldEfficiency = 0, minDamage = 3938.993, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_incom_disruptor", hitpoints = 3090.025, armor = 1552.911, rate = 0.313054, drain = 29.51766, maxDamage = 5305.413, shieldEfficiency = 0, minDamage = 3904.571, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_4 = { name = "wpn_std_countermeasure", hitpoints = 249.2039, armor = 244.1954, rate = 9.704676, drain = 23.5454, maxDamage = 99.44479, shieldEfficiency = 0, minDamage = 24.19794, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_hutt_heavy_s01, "object/ship/player/player_hutt_heavy_s01.iff")
