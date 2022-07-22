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


object_ship_tieoppressor_tier5 = object_ship_shared_tieoppressor_tier5:new {

	name = "tieoppressor_tier5",
	slideFactor = 1.72,
	chassisHitpoints = 2703.36,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 3463.059, armor = 3352.067,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 3382.44, armor = 3395.669, speed = 46.39774, pitch = 24.79196, roll = 32.12483, yaw = 20.46766, acceleration = 11.05717, rollRate = 57.27812, pitchRate = 51.57566, deceleration = 9.52997, yawRate = 42.0938,},
	shield_0 = { name = "shd_generic", hitpoints = 3386.175, armor = 3447.283, regen = 25.18085, front = 13720.13, back = 13408.39,},
	armor_0 = { name = "arm_generic", hitpoints = 7455.786, armor = 7321.011,},
	armor_1 = { name = "arm_generic", hitpoints = 7230.481, armor = 7457.195,},
	capacitor = { name = "cap_generic", hitpoints = 3501.523, armor = 3417.932, rechargeRate = 96.27345, energy = 4890.466,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 3430.158, armor = 3433.769, rate = 0.7410728, drain = 0.969963, maxDamage = 324.3535, shieldEfficiency = 0.5469023, minDamage = 198.5026, ammo = 0, ammo_type = 0, armorEfficiency = 0.5347847,},
	weapon_1 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 3421.785, armor = 3363.495, rate = 2.955506, drain = 0.9816089, maxDamage = 978.393, shieldEfficiency = 0.7370496, minDamage = 389.6031, ammo = 4, ammo_type = 20, armorEfficiency = 0.7440822,},
}

ObjectTemplates:addTemplate(object_ship_tieoppressor_tier5, "object/ship/tieoppressor_tier5.iff")
