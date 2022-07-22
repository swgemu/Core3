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


object_ship_player_player_ykl37r = object_ship_player_shared_player_ykl37r:new {

	name = "player_ykl37r",
	slideFactor = 1.85,
	chassisHitpoints = 5000,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 393.4749, armor = 392.1788,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 97.38634, armor = 97.26779, speed = 64.8352, pitch = 53.1233, roll = 51.811, yaw = 20.72012, acceleration = 14.20368, rollRate = 81.44453, pitchRate = 74.89443, deceleration = 13.23707, yawRate = 36.14846,},
	shield_0 = { name = "shd_generic", hitpoints = 399.6198, armor = 488.0886, regen = 2.93632, front = 1559.694, back = 1589.634,},
	armor_0 = { name = "arm_generic", hitpoints = 1092.445, armor = 1065.585,},
	armor_1 = { name = "arm_generic", hitpoints = 1064.248, armor = 1095.966,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 35.55407, energy = 1101.659,},
	booster = { name = "bst_generic", hitpoints = 19.30068, armor = 19.50534, energy = 96.55447, acceleration = 19.0435, speed = 14.3576, energyUsage = 9.907719, rechargeRate = 4.798415,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 191.7337, armor = 198.4741, rate = 0.3354505, drain = 23.31645, maxDamage = 1452.662, shieldEfficiency = 0, minDamage = 727.0751, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 195.7502, armor = 193.4968, rate = 0.3280407, drain = 22.70662, maxDamage = 965.8762, shieldEfficiency = 0, minDamage = 601.3749, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_xwing_missile_s01", hitpoints = 19.53581, armor = 19.31941, rate = 5.815926, drain = 23.09743, maxDamage = 22.9824, shieldEfficiency = 0, minDamage = 23.42325, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_3 = { name = "wpn_std_countermeasure", hitpoints = 247.8035, armor = 245.5052, rate = 0.09767031, drain = 23.58665, maxDamage = 98.10107, shieldEfficiency = 0, minDamage = 24.81069, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
	lots = 4,
}

ObjectTemplates:addTemplate(object_ship_player_player_ykl37r, "object/ship/player/player_ykl37r.iff")
