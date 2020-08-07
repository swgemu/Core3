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


object_ship_player_player_tie_light_duty = object_ship_player_shared_player_tie_light_duty:new {

	name = "player_tie_light_duty",
	slideFactor = 1.78,
	chassisHitpoints = 1350,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 291.425, armor = 299.7746,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 292.1978, armor = 299.0364, speed = 46.44812, pitch = 59.78908, roll = 63.48967, yaw = 38.76865, acceleration = 16.25996, rollRate = 81.19094, pitchRate = 79.35983, deceleration = 15.23637, yawRate = 70.77897,},
	shield_0 = { name = "shd_generic", hitpoints = 291.746, armor = 294.7357, regen = 0, front = 0, back = 0,},
	armor_0 = { name = "arm_generic", hitpoints = 388.9816, armor = 394.4028,},
	armor_1 = { name = "arm_generic", hitpoints = 387.7423, armor = 384.4127,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 45.63763, energy = 790.3254,},
	weapon_0 = { name = "wpn_generic", hitpoints = 192.7384, armor = 194.3948, rate = 0.2769867, drain = 26.48631, maxDamage = 574.6135, shieldEfficiency = 0, minDamage = 493.8686, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 196.8598, armor = 192.7333, rate = 9.186328, drain = 31.2048, maxDamage = 802.5913, shieldEfficiency = 0.7774226, minDamage = 497.8733, ammo = 8, ammo_type = 2, armorEfficiency = 0.5474777,},
	weapon_2 = { name = "wpn_std_countermeasure", hitpoints = 243.6434, armor = 240.4096, rate = 0.09546758, drain = 23.2824, maxDamage = 96.26791, shieldEfficiency = 0, minDamage = 24.2269, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_tie_light_duty, "object/ship/player/player_tie_light_duty.iff")
