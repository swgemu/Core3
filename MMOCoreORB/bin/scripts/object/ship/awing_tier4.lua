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


object_ship_awing_tier4 = object_ship_shared_awing_tier4:new {

	name = "awing_tier4",
	slideFactor = 1.62,
	chassisHitpoints = 1728,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1865.39, armor = 1858.281,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 1817.45, armor = 1779.09, speed = 50.22786, pitch = 24.22741, roll = 30.23187, yaw = 19.22723, acceleration = 11.65444, rollRate = 55.54942, pitchRate = 49.3686, deceleration = 9.061271, yawRate = 40.10781,},
	shield_0 = { name = "shd_generic", hitpoints = 1815.266, armor = 1851.839, regen = 14.63671, front = 7129.199, back = 7459.819,},
	armor_0 = { name = "arm_generic", hitpoints = 3979.71, armor = 3955.833,},
	armor_1 = { name = "arm_generic", hitpoints = 3968.089, armor = 3934.492,},
	capacitor = { name = "cap_generic", hitpoints = 1791.506, armor = 1790.958, rechargeRate = 96.55721, energy = 4897.22,},
	weapon_0 = { name = "wpn_awing_blaster", hitpoints = 1811.481, armor = 1865.079, rate = 0.7757519, drain = 0.9646059, maxDamage = 250.7197, shieldEfficiency = 0.5387068, minDamage = 161.7296, ammo = 0, ammo_type = 0, armorEfficiency = 0.554134,},
}

ObjectTemplates:addTemplate(object_ship_awing_tier4, "object/ship/awing_tier4.iff")
