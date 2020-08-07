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


object_ship_player_player_hutt_light_s02 = object_ship_player_shared_player_hutt_light_s02:new {

	name = "player_hutt_light_s02",
	slideFactor = 1.75,
	chassisHitpoints = 1340,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 298.2066, armor = 293.7321,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 95.32785, armor = 95.15446, speed = 52.7619, pitch = 58.26368, roll = 58.92189, yaw = 39.02379, acceleration = 16.42248, rollRate = 78.1004, pitchRate = 80.05688, deceleration = 13.90281, yawRate = 70.91481,},
	shield_0 = { name = "shd_generic", hitpoints = 389.5561, armor = 486.0786, regen = 4.926981, front = 867.2077, back = 833.345,},
	armor_0 = { name = "arm_generic", hitpoints = 190.9982, armor = 196.7778,},
	armor_1 = { name = "arm_generic", hitpoints = 194.3873, armor = 197.3107,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.8511, energy = 122.9136,},
	booster = { name = "bst_generic", hitpoints = 19.28346, armor = 19.08301, energy = 95.53202, acceleration = 19.7022, speed = 14.90906, energyUsage = 9.674501, rechargeRate = 4.834077,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 190.2451, armor = 199.6195, rate = 0.3368293, drain = 22.63054, maxDamage = 243.6057, shieldEfficiency = 0, minDamage = 118.2645, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_std_countermeasure", hitpoints = 243.0658, armor = 244.4095, rate = 0.09646789, drain = 22.61854, maxDamage = 96.51807, shieldEfficiency = 0, minDamage = 24.82167, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_hutt_light_s02, "object/ship/player/player_hutt_light_s02.iff")
