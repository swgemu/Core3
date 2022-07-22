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


object_ship_firespray_tier2 = object_ship_shared_firespray_tier2:new {

	name = "firespray_tier2",
	slideFactor = 1.81,
	chassisHitpoints = 780,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 580.2235, armor = 568.9439,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 561.755, armor = 569.5377, speed = 41.8966, pitch = 23.02787, roll = 28.76909, yaw = 18.36717, acceleration = 10.03101, rollRate = 52.89725, pitchRate = 46.42007, deceleration = 8.682129, yawRate = 39.39732,},
	shield_0 = { name = "shd_generic", hitpoints = 582.4368, armor = 561.671, regen = 6.883695, front = 2242.431, back = 2249.346,},
	armor_0 = { name = "arm_generic", hitpoints = 1202.376, armor = 1225.134,},
	armor_1 = { name = "arm_generic", hitpoints = 1206.236, armor = 1204.046,},
	capacitor = { name = "cap_generic", hitpoints = 565.4958, armor = 582.6385, rechargeRate = 98.43176, energy = 4766.03,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 570.5107, armor = 570.4646, rate = 0.7790554, drain = 0.9965656, maxDamage = 111.1165, shieldEfficiency = 0.5374302, minDamage = 80.18774, ammo = 0, ammo_type = 0, armorEfficiency = 0.546164,},
}

ObjectTemplates:addTemplate(object_ship_firespray_tier2, "object/ship/firespray_tier2.iff")
