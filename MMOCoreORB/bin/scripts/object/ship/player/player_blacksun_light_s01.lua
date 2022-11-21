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


object_ship_player_player_blacksun_light_s01 = object_ship_player_shared_player_blacksun_light_s01:new {

	name = "player_blacksun_light_s01",
	slideFactor = 1.81,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 287.8142, armor = 287.9694,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 95.56121, armor = 97.31476, speed = 54.51305, pitch = 33.4327, roll = 33.04952, yaw = 32.42641, acceleration = 16.76877, rollRate = 58.41513, pitchRate = 59.20968, deceleration = 8.071388, yawRate = 60.17678,},
	shield_0 = { name = "shd_generic", hitpoints = 381.9661, armor = 479.58, regen = 4.926902, front = 286.0273, back = 475.3774,},
	armor_0 = { name = "arm_generic", hitpoints = 296.5002, armor = 294.2959,},
	armor_1 = { name = "arm_generic", hitpoints = 296.8922, armor = 297.8156,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.60049, energy = 556.8726,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.97504, armor = 19.43354, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 193.6237, armor = 192.9486, rate = 0.3404445, drain = 22.99194, maxDamage = 239.8239, shieldEfficiency = 0, minDamage = 115.6269, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_blacksun_light_s01, "object/ship/player/player_blacksun_light_s01.iff")
