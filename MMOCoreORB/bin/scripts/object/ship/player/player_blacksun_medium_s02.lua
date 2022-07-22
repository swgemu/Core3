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


object_ship_player_player_blacksun_medium_s02 = object_ship_player_shared_player_blacksun_medium_s02:new {

	name = "player_blacksun_medium_s02",
	slideFactor = 1.81,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 292.3597, armor = 289.2545,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 95.02632, armor = 97.37484, speed = 54.40914, pitch = 33.22331, roll = 33.01411, yaw = 32.59493, acceleration = 16.70522, rollRate = 58.00322, pitchRate = 58.84709, deceleration = 8.202561, yawRate = 60.46803,},
	shield_0 = { name = "shd_generic", hitpoints = 385.7991, armor = 482.139, regen = 4.797288, front = 290.7639, back = 481.7832,},
	armor_0 = { name = "arm_generic", hitpoints = 286.1625, armor = 293.4482,},
	armor_1 = { name = "arm_generic", hitpoints = 298.4027, armor = 288.8897,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 33.86935, energy = 543.3336,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.56373, armor = 19.69364, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 194.711, armor = 197.5858, rate = 0.3354039, drain = 22.85619, maxDamage = 241.4807, shieldEfficiency = 0, minDamage = 118.5293, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 190.9026, armor = 199.351, rate = 0.3305117, drain = 23.30432, maxDamage = 238.1044, shieldEfficiency = 0, minDamage = 117.2669, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_blacksun_medium_s02, "object/ship/player/player_blacksun_medium_s02.iff")
