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


object_ship_player_player_hutt_turret_ship = object_ship_player_shared_player_hutt_turret_ship:new {

	name = "player_hutt_turret_ship",
	slideFactor = 1.76,
	chassisHitpoints = 1512,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 298.5859, armor = 293.59,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 99.05453, armor = 99.5019, speed = 45.28425, pitch = 39.07172, roll = 39.94278, yaw = 20.39184, acceleration = 12.03205, rollRate = 59.10788, pitchRate = 60.85636, deceleration = 15.43395, yawRate = 39.61805,},
	shield_0 = { name = "shd_generic", hitpoints = 389.1004, armor = 488.346, regen = 4.906437, front = 944.6312, back = 956.4858,},
	armor_0 = { name = "arm_generic", hitpoints = 199.7896, armor = 193.4351,},
	armor_1 = { name = "arm_generic", hitpoints = 194.2157, armor = 192.6566,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 31.81267, energy = 509.1956,},
	booster = { name = "bst_generic", hitpoints = 19.15845, armor = 19.07937, energy = 95.04938, acceleration = 19.82329, speed = 14.27864, energyUsage = 9.834052, rechargeRate = 4.996946,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 197.9332, armor = 193.0661, rate = 0.3303496, drain = 23.39249, maxDamage = 245.888, shieldEfficiency = 0, minDamage = 116.536, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 193.6815, armor = 194.5917, rate = 0.3333288, drain = 23.02759, maxDamage = 22.62797, shieldEfficiency = 0, minDamage = 23.58794, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_incom_disruptor", hitpoints = 19.27279, armor = 19.80032, rate = 0.3447994, drain = 23.09595, maxDamage = 22.60188, shieldEfficiency = 0, minDamage = 23.1928, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_incom_disruptor", hitpoints = 19.91959, armor = 19.5616, rate = 0.3411166, drain = 22.83431, maxDamage = 23.2063, shieldEfficiency = 0, minDamage = 22.55597, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_4 = { name = "wpn_std_countermeasure", hitpoints = 242.1129, armor = 242.1036, rate = 9.918377, drain = 22.79713, maxDamage = 98.86002, shieldEfficiency = 0, minDamage = 24.51417, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_hutt_turret_ship, "object/ship/player/player_hutt_turret_ship.iff")
