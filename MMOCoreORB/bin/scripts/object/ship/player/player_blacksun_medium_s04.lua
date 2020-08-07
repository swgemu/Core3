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


object_ship_player_player_blacksun_medium_s04 = object_ship_player_shared_player_blacksun_medium_s04:new {

	name = "player_blacksun_medium_s04",
	slideFactor = 1.81,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 291.0834, armor = 289.3076,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 97.49711, armor = 98.88375, speed = 54.53903, pitch = 32.56627, roll = 33.46387, yaw = 33.49148, acceleration = 16.57997, rollRate = 59.83955, pitchRate = 59.48193, deceleration = 8.234636, yawRate = 59.67692,},
	shield_0 = { name = "shd_generic", hitpoints = 386.6447, armor = 498.0531, regen = 4.835435, front = 287.512, back = 490.744,},
	armor_0 = { name = "arm_generic", hitpoints = 294.0894, armor = 289.562,},
	armor_1 = { name = "arm_generic", hitpoints = 292.5082, armor = 295.594,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.11131, energy = 552.4064,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.64683, armor = 19.21716, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 197.5466, armor = 196.4034, rate = 0.3302174, drain = 23.58628, maxDamage = 249.7546, shieldEfficiency = 0, minDamage = 117.486, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 198.8782, armor = 195.1298, rate = 0.3394141, drain = 23.02138, maxDamage = 249.1827, shieldEfficiency = 0, minDamage = 117.2194, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_blacksun_medium_s04, "object/ship/player/player_blacksun_medium_s04.iff")
