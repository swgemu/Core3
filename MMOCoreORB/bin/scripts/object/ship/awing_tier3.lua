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


object_ship_awing_tier3 = object_ship_shared_awing_tier3:new {

	name = "awing_tier3",
	slideFactor = 1.62,
	chassisHitpoints = 1080,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 969.6296, armor = 936.7021,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 932.5218, armor = 948.3258, speed = 48.78349, pitch = 23.39157, roll = 30.24099, yaw = 19.13743, acceleration = 11.5839, rollRate = 52.78603, pitchRate = 47.71133, deceleration = 8.810146, yawRate = 40.27037,},
	shield_0 = { name = "shd_generic", hitpoints = 923.8101, armor = 963.0862, regen = 8.865992, front = 3774.678, back = 3825.416,},
	armor_0 = { name = "arm_generic", hitpoints = 2019.093, armor = 1989.285,},
	armor_1 = { name = "arm_generic", hitpoints = 1985.124, armor = 2039.036,},
	capacitor = { name = "cap_generic", hitpoints = 924.5656, armor = 927.7947, rechargeRate = 95.27341, energy = 4946.838,},
	weapon_0 = { name = "wpn_awing_blaster", hitpoints = 926.5228, armor = 967.9106, rate = 0.7724296, drain = 0.9773401, maxDamage = 161.5386, shieldEfficiency = 0.5517186, minDamage = 106.1153, ammo = 0, ammo_type = 0, armorEfficiency = 0.5340393,},
}

ObjectTemplates:addTemplate(object_ship_awing_tier3, "object/ship/awing_tier3.iff")
