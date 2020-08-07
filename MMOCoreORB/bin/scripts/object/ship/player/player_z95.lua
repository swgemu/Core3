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


object_ship_player_player_z95 = object_ship_player_shared_player_z95:new {

	name = "player_z95",
	slideFactor = 1.91,
	chassisHitpoints = 1442,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 291.9245, armor = 294.534,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 97.8401, armor = 98.43731, speed = 43.14625, pitch = 48.00814, roll = 63.63562, yaw = 31.22159, acceleration = 13.34253, rollRate = 80.73061, pitchRate = 65.09782, deceleration = 9.902062, yawRate = 53.09187,},
	shield_0 = { name = "shd_generic", hitpoints = 399.2392, armor = 491.8932, regen = 3.840435, front = 874.7614, back = 863.0849,},
	armor_0 = { name = "arm_generic", hitpoints = 398.3972, armor = 382.703,},
	armor_1 = { name = "arm_generic", hitpoints = 388.658, armor = 394.4496,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 31.97693, energy = 490.1118,},
	booster = { name = "bst_generic", hitpoints = 19.29568, armor = 19.56404, energy = 99.33602, acceleration = 19.80807, speed = 14.41072, energyUsage = 9.796299, rechargeRate = 4.778286,},
	weapon_0 = { name = "wpn_z95_blaster", hitpoints = 196.8257, armor = 199.8533, rate = 0.3368513, drain = 27.06423, maxDamage = 477.9673, shieldEfficiency = 0, minDamage = 459.7931, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_xwing_missile_s01", hitpoints = 196.9528, armor = 195.2987, rate = 8.773458, drain = 43.39822, maxDamage = 1525.757, shieldEfficiency = 0.8838704, minDamage = 461.1451, ammo = 10, ammo_type = 4, armorEfficiency = 0.2277464,},
	weapon_2 = { name = "wpn_std_countermeasure", hitpoints = 241.9698, armor = 249.2348, rate = 0.09547641, drain = 22.92062, maxDamage = 99.79048, shieldEfficiency = 0, minDamage = 24.22562, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_z95, "object/ship/player/player_z95.iff")
