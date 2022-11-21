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


object_ship_firespray_tier4 = object_ship_shared_firespray_tier4:new {

	name = "firespray_tier4",
	slideFactor = 1.81,
	chassisHitpoints = 2496,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 2648.236, armor = 2682.571,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 2616.732, armor = 2634.158, speed = 44.65596, pitch = 24.73479, roll = 30.50234, yaw = 19.60738, acceleration = 11.02491, rollRate = 56.32331, pitchRate = 49.67889, deceleration = 9.435044, yawRate = 40.43691,},
	shield_0 = { name = "shd_generic", hitpoints = 2672.971, armor = 2602.713, regen = 18.53519, front = 10461.3, back = 10304.12,},
	armor_0 = { name = "arm_generic", hitpoints = 5658.893, armor = 5488.758,},
	armor_1 = { name = "arm_generic", hitpoints = 5620.301, armor = 5560.779,},
	capacitor = { name = "cap_generic", hitpoints = 2593.1, armor = 2657.869, rechargeRate = 96.50132, energy = 4768.286,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 2632.16, armor = 2610.717, rate = 0.7595221, drain = 0.9540119, maxDamage = 322.7609, shieldEfficiency = 0.5452554, minDamage = 209.1642, ammo = 0, ammo_type = 0, armorEfficiency = 0.5472892,},
}

ObjectTemplates:addTemplate(object_ship_firespray_tier4, "object/ship/firespray_tier4.iff")
