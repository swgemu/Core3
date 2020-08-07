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


object_ship_ywing = object_ship_shared_ywing:new {

	name = "ywing",
	slideFactor = 1.88,
	chassisHitpoints = 339,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 99.58519, armor = 98.23579,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 98.89811, armor = 95.54722, speed = 33.02378, pitch = 16.59647, roll = 15.87258, yaw = 16.47365, acceleration = 8.238178, rollRate = 31.17675, pitchRate = 30.61561, deceleration = 9.049246, yawRate = 31.84087,},
	shield_0 = { name = "shd_generic", hitpoints = 397.123, armor = 483.2599, regen = 4.862548, front = 475.0192, back = 596.6861,},
	armor_0 = { name = "arm_generic", hitpoints = 580.8756, armor = 596.1696,},
	armor_1 = { name = "arm_generic", hitpoints = 572.2704, armor = 599.5636,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.14708, energy = 553.6282,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 197.61, armor = 190.4156, rate = 0.3376555, drain = 22.52383, maxDamage = 317.557, shieldEfficiency = 0, minDamage = 219.3932, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 194.2161, armor = 199.5413, rate = 0.3294459, drain = 22.88088, maxDamage = 22.76139, shieldEfficiency = 0, minDamage = 22.9218, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_ywing, "object/ship/ywing.iff")
