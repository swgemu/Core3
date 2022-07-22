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


object_ship_player_player_blacksun_heavy_s01 = object_ship_player_shared_player_blacksun_heavy_s01:new {

	name = "player_blacksun_heavy_s01",
	slideFactor = 1.91,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 292.9725, armor = 299.5309,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 96.6465, armor = 97.75994, speed = 40.43465, pitch = 20.62251, roll = 20.84657, yaw = 20.48238, acceleration = 11.59244, rollRate = 41.15862, pitchRate = 42.04427, deceleration = 15.05197, yawRate = 42.06062,},
	shield_0 = { name = "shd_generic", hitpoints = 783.6112, armor = 496.0798, regen = 4.791908, front = 585.0226, back = 766.2216,},
	armor_0 = { name = "arm_generic", hitpoints = 678.8878, armor = 697.2473,},
	armor_1 = { name = "arm_generic", hitpoints = 669.7052, armor = 680.1978,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 35.18039, energy = 569.5192,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.62413, armor = 19.77116, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 197.6348, armor = 198.6877, rate = 0.3358833, drain = 22.88481, maxDamage = 397.8456, shieldEfficiency = 0, minDamage = 310.6662, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 196.2011, armor = 192.69, rate = 0.3301291, drain = 23.57168, maxDamage = 22.8097, shieldEfficiency = 0, minDamage = 23.23072, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_incom_disruptor", hitpoints = 19.44605, armor = 19.74653, rate = 0.3429416, drain = 22.91661, maxDamage = 22.54667, shieldEfficiency = 0, minDamage = 22.86555, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_blacksun_heavy_s01, "object/ship/player/player_blacksun_heavy_s01.iff")
