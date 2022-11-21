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


object_ship_player_player_tiebomber = object_ship_player_shared_player_tiebomber:new {

	name = "player_tiebomber",
	slideFactor = 1.88,
	chassisHitpoints = 2131,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 297.1225, armor = 298.5394,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 291.1327, armor = 291.4838, speed = 49.77505, pitch = 40.96615, roll = 40.48449, yaw = 20.71066, acceleration = 19.92171, rollRate = 59.77399, pitchRate = 59.32515, deceleration = 15.39316, yawRate = 40.19766,},
	shield_0 = { name = "shd_generic", hitpoints = 286.4963, armor = 293.7139, regen = 0, front = 1233.986, back = 1201.105,},
	armor_0 = { name = "arm_generic", hitpoints = 380.6682, armor = 390.2642,},
	armor_1 = { name = "arm_generic", hitpoints = 390.0657, armor = 395.0224,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 78.74741, energy = 1398.319,},
	booster = { name = "bst_generic", hitpoints = 19.57087, armor = 19.6666, energy = 97.41641, acceleration = 19.29302, speed = 14.83059, energyUsage = 9.64123, rechargeRate = 4.884814,},
	weapon_0 = { name = "wpn_generic", hitpoints = 196.8255, armor = 196.3449, rate = 0.2844186, drain = 27.02139, maxDamage = 571.19, shieldEfficiency = 0, minDamage = 503.3419, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_generic", hitpoints = 198.6888, armor = 193.5129, rate = 0.2754076, drain = 27.29931, maxDamage = 563.499, shieldEfficiency = 0.7923369, minDamage = 501.4572, ammo = 32, ammo_type = 4, armorEfficiency = 0.536827,},
	weapon_2 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 19.42762, armor = 19.98304, rate = 0.3448843, drain = 22.75517, maxDamage = 22.98563, shieldEfficiency = 0, minDamage = 23.4936, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 19.37656, armor = 19.90893, rate = 0.335216, drain = 22.67477, maxDamage = 22.79446, shieldEfficiency = 0, minDamage = 23.37662, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
	weapon_4 = { name = "wpn_std_countermeasure", hitpoints = 248.3909, armor = 244.0308, rate = 0.09544036, drain = 22.69649, maxDamage = 95.20827, shieldEfficiency = 0, minDamage = 23.93103, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_tiebomber, "object/ship/player/player_tiebomber.iff")
