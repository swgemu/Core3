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


object_ship_tieinterceptor = object_ship_shared_tieinterceptor:new {

	name = "tieinterceptor",
	slideFactor = 1.75,
	chassisHitpoints = 341,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 98.79093, armor = 99.18828,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 97.39794, armor = 97.18473, speed = 59.24911, pitch = 31.18094, roll = 31.62832, yaw = 31.97264, acceleration = 22.63162, rollRate = 61.39075, pitchRate = 63.80702, deceleration = 11.66156, yawRate = 62.56269,},
	shield_0 = { name = "shd_generic", hitpoints = 394.3506, armor = 489.3681, regen = 4.909234, front = 290.5319, back = 290.1466,},
	armor_0 = { name = "arm_generic", hitpoints = 598.3904, armor = 577.8597,},
	armor_1 = { name = "arm_generic", hitpoints = 577.6239, armor = 575.0683,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 55.90674, energy = 1419.559,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 193.2445, armor = 190.1814, rate = 0.5697581, drain = 26.4943, maxDamage = 335.5113, shieldEfficiency = 0, minDamage = 213.8195, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_sienar_heatseeker_missile_s01", hitpoints = 199.1122, armor = 199.4389, rate = 3.994777, drain = 26.36835, maxDamage = 26.46099, shieldEfficiency = 0, minDamage = 26.57586, ammo = 50, ammo_type = 3, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_tieinterceptor, "object/ship/tieinterceptor.iff")
