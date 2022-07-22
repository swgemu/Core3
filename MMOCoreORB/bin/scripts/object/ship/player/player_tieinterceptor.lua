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


object_ship_player_player_tieinterceptor = object_ship_player_shared_player_tieinterceptor:new {

	name = "player_tieinterceptor",
	slideFactor = 1.95,
	chassisHitpoints = 6000,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 3121.869, armor = 1536.193,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 3142.305, armor = 1518.367, speed = 59.74054, pitch = 47.48366, roll = 45.87457, yaw = 46.3578, acceleration = 16.51296, rollRate = 71.13919, pitchRate = 68.87661, deceleration = 14.90916, yawRate = 71.39978,},
	shield_0 = { name = "shd_generic", hitpoints = 3056.586, armor = 1544.068, regen = 29.96742, front = 9790.87, back = 9655.143,},
	armor_0 = { name = "arm_generic", hitpoints = 7994.37, armor = 7776.441,},
	armor_1 = { name = "arm_generic", hitpoints = 7840.048, armor = 7681.589,},
	capacitor = { name = "cap_generic", hitpoints = 3049.717, armor = 1545.358, rechargeRate = 47.68914, energy = 995.4575,},
	booster = { name = "bst_generic", hitpoints = 19.5317, armor = 19.35275, energy = 98.4522, acceleration = 19.16425, speed = 14.65189, energyUsage = 9.533919, rechargeRate = 4.80651,},
	weapon_0 = { name = "wpn_generic", hitpoints = 3031.25, armor = 1553.814, rate = 0.3080769, drain = 29.32105, maxDamage = 5278.455, shieldEfficiency = 0, minDamage = 3910.032, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_sienar_heatseeker_missile_s01", hitpoints = 3132.48, armor = 1525.354, rate = 0.9553757, drain = 285.002, maxDamage = 11949.5, shieldEfficiency = 0.8711885, minDamage = 9623.874, ammo = 12, ammo_type = 3, armorEfficiency = 0.7309372,},
	weapon_2 = { name = "wpn_std_countermeasure", hitpoints = 247.7015, armor = 243.9529, rate = 0.09653933, drain = 22.77921, maxDamage = 98.3455, shieldEfficiency = 0, minDamage = 24.10794, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_tieinterceptor, "object/ship/player/player_tieinterceptor.iff")
