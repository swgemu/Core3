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


object_ship_player_player_hutt_heavy_s02 = object_ship_player_shared_player_hutt_heavy_s02:new {

	name = "player_hutt_heavy_s02",
	slideFactor = 1.76,
	chassisHitpoints = 1512,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 290.6318, armor = 288.9599,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 99.67373, armor = 96.38962, speed = 43.82066, pitch = 39.0956, roll = 39.79986, yaw = 20.25624, acceleration = 12.00114, rollRate = 59.70396, pitchRate = 60.09761, deceleration = 15.62894, yawRate = 40.6769,},
	shield_0 = { name = "shd_generic", hitpoints = 383.7082, armor = 478.7005, regen = 4.900551, front = 970.2797, back = 976.8123,},
	armor_0 = { name = "arm_generic", hitpoints = 192.5412, armor = 190.5703,},
	armor_1 = { name = "arm_generic", hitpoints = 194.2573, armor = 193.0681,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 30.9446, energy = 491.727,},
	booster = { name = "bst_generic", hitpoints = 19.12139, armor = 19.22683, energy = 96.64861, acceleration = 19.64554, speed = 14.64753, energyUsage = 9.788589, rechargeRate = 4.914062,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 194.4251, armor = 192.6112, rate = 0.3387578, drain = 22.58564, maxDamage = 245.8094, shieldEfficiency = 0, minDamage = 115.7852, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 199.9824, armor = 194.3572, rate = 0.3296726, drain = 22.74107, maxDamage = 22.46696, shieldEfficiency = 0, minDamage = 22.4629, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_incom_disruptor", hitpoints = 19.59701, armor = 19.88243, rate = 0.3281354, drain = 22.96898, maxDamage = 22.56611, shieldEfficiency = 0, minDamage = 22.68828, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_4 = { name = "wpn_std_countermeasure", hitpoints = 248.3284, armor = 242.9545, rate = 9.966114, drain = 23.53407, maxDamage = 97.73397, shieldEfficiency = 0, minDamage = 24.97156, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_hutt_heavy_s02, "object/ship/player/player_hutt_heavy_s02.iff")
