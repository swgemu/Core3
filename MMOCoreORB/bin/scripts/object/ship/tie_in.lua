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


object_ship_tie_in = object_ship_shared_tie_in:new {

	name = "tie_in",
	slideFactor = 1.75,
	chassisHitpoints = 412,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 97.9703, armor = 96.82117,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 98.38796, armor = 96.48996, speed = 46.44867, pitch = 25.41997, roll = 25.3077, yaw = 26.03273, acceleration = 13.58535, rollRate = 49.74815, pitchRate = 50.02429, deceleration = 6.010502, yawRate = 51.67767,},
	shield_0 = { name = "shd_generic", hitpoints = 191.983, armor = 198.7326, regen = 4.925221, front = 0, back = 0,},
	armor_0 = { name = "arm_generic", hitpoints = 494.4838, armor = 489.7073,},
	armor_1 = { name = "arm_generic", hitpoints = 485.3305, armor = 475.5244,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 49.73822, energy = 1252.217,},
	weapon_0 = { name = "wpn_generic", hitpoints = 192.6737, armor = 197.0276, rate = 0.4908042, drain = 24.09557, maxDamage = 212.0546, shieldEfficiency = 0, minDamage = 178.5757, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 190.9543, armor = 199.5383, rate = 2.995811, drain = 24.16496, maxDamage = 23.70049, shieldEfficiency = 0, minDamage = 24.52886, ammo = 50, ammo_type = 2, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_std_countermeasure", hitpoints = 19.34585, armor = 19.65992, rate = 0.9652068, drain = 24.1164, maxDamage = 23.97001, shieldEfficiency = 0, minDamage = 24.24528, ammo = 50, ammo_type = 7, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_tie_in, "object/ship/tie_in.iff")
