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


object_ship_player_player_blacksun_heavy_s03 = object_ship_player_shared_player_blacksun_heavy_s03:new {

	name = "player_blacksun_heavy_s03",
	slideFactor = 1.91,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 291.5533, armor = 296.2093,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 98.18987, armor = 97.04291, speed = 39.96843, pitch = 20.48805, roll = 20.85472, yaw = 20.30706, acceleration = 11.97249, rollRate = 41.88421, pitchRate = 41.67138, deceleration = 15.38523, yawRate = 41.48264,},
	shield_0 = { name = "shd_generic", hitpoints = 785.5859, armor = 489.2968, regen = 4.77468, front = 584.1962, back = 768.0731,},
	armor_0 = { name = "arm_generic", hitpoints = 670.9449, armor = 692.0453,},
	armor_1 = { name = "arm_generic", hitpoints = 671.141, armor = 696.1824,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 33.83805, energy = 566.9453,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.07374, armor = 19.391, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 194.6955, armor = 197.2448, rate = 0.3343826, drain = 22.70932, maxDamage = 408.9066, shieldEfficiency = 0, minDamage = 318.3311, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 194.4305, armor = 192.9223, rate = 0.3374817, drain = 23.37844, maxDamage = 23.47502, shieldEfficiency = 0, minDamage = 22.74906, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_incom_disruptor", hitpoints = 19.07644, armor = 19.65449, rate = 0.3281578, drain = 22.84289, maxDamage = 22.66249, shieldEfficiency = 0, minDamage = 22.71292, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_xwing_missile_s01", hitpoints = 0, armor = 0, rate = 0, drain = 0, maxDamage = 0, shieldEfficiency = 0, minDamage = 0, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_blacksun_heavy_s03, "object/ship/player/player_blacksun_heavy_s03.iff")
