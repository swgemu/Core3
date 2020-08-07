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


object_ship_player_player_hutt_light_s01 = object_ship_player_shared_player_hutt_light_s01:new {

	name = "player_hutt_light_s01",
	slideFactor = 1.95,
	chassisHitpoints = 6000,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 3088.099, armor = 1527.99,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 3136.135, armor = 1581.261, speed = 58.72906, pitch = 46.54525, roll = 47.6611, yaw = 46.58419, acceleration = 16.82825, rollRate = 70.91674, pitchRate = 70.14632, deceleration = 14.25979, yawRate = 69.08958,},
	shield_0 = { name = "shd_generic", hitpoints = 3135.652, armor = 1586.758, regen = 29.61802, front = 9606.966, back = 9779.191,},
	armor_0 = { name = "arm_generic", hitpoints = 7629.503, armor = 7855.571,},
	armor_1 = { name = "arm_generic", hitpoints = 7789.208, armor = 7609.071,},
	capacitor = { name = "cap_generic", hitpoints = 3047.057, armor = 1570.661, rechargeRate = 49.48987, energy = 975.1318,},
	booster = { name = "bst_generic", hitpoints = 19.47985, armor = 19.81534, energy = 96.9072, acceleration = 19.69485, speed = 14.44987, energyUsage = 9.768956, rechargeRate = 4.964502,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 3034.379, armor = 1565.307, rate = 0.3184879, drain = 29.52462, maxDamage = 5235.119, shieldEfficiency = 0, minDamage = 3900.653, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_std_countermeasure", hitpoints = 240.8438, armor = 249.4026, rate = 0.09872283, drain = 23.52345, maxDamage = 98.52152, shieldEfficiency = 0, minDamage = 24.50502, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_hutt_light_s01, "object/ship/player/player_hutt_light_s01.iff")
