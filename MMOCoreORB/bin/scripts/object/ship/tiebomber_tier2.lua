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


object_ship_tiebomber_tier2 = object_ship_shared_tiebomber_tier2:new {

	name = "tiebomber_tier2",
	slideFactor = 1.66,
	chassisHitpoints = 900,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 428.1471, armor = 435.3303,},
	engine = { name = "eng_qualdex_kyromaster", hitpoints = 428.0607, armor = 445.9983, speed = 42.92041, pitch = 23.25889, roll = 28.19028, yaw = 17.98068, acceleration = 10.12533, rollRate = 52.09534, pitchRate = 46.71903, deceleration = 8.523304, yawRate = 39.38122,},
	shield_0 = { name = "shd_generic", hitpoints = 439.4425, armor = 444.5743, regen = 3.927353, front = 1292.408, back = 1348.52,},
	armor_0 = { name = "arm_generic", hitpoints = 1408.772, armor = 1405.247,},
	armor_1 = { name = "arm_generic", hitpoints = 1406.202, armor = 1401.865,},
	capacitor = { name = "cap_generic", hitpoints = 429.1382, armor = 443.5058, rechargeRate = 96.48699, energy = 4986.825,},
	weapon_0 = { name = "wpn_generic", hitpoints = 435.8378, armor = 430.5501, rate = 0.7557479, drain = 0.979591, maxDamage = 85.84564, shieldEfficiency = 0.5557585, minDamage = 62.09147, ammo = 0, ammo_type = 0, armorEfficiency = 0.5327722,},
	weapon_1 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 438.4771, armor = 442.2261, rate = 2.856867, drain = 0.973939, maxDamage = 260.3927, shieldEfficiency = 0.7495818, minDamage = 125.0909, ammo = 4, ammo_type = 17, armorEfficiency = 0.7335442,},
}

ObjectTemplates:addTemplate(object_ship_tiebomber_tier2, "object/ship/tiebomber_tier2.iff")
