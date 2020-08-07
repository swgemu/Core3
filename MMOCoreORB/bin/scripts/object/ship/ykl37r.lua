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


object_ship_ykl37r = object_ship_shared_ykl37r:new {

	name = "ykl37r",
	slideFactor = 1.81,
	chassisHitpoints = 654,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 95.82692, armor = 98.05847,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 98.70071, armor = 97.88046, speed = 44.55561, pitch = 20.9312, roll = 21.22866, yaw = 20.54779, acceleration = 7.812149, rollRate = 42.56039, pitchRate = 41.85131, deceleration = 12.09663, yawRate = 43.19313,},
	shield_0 = { name = "shd_generic", hitpoints = 382.9281, armor = 491.327, regen = 4.998025, front = 578.6795, back = 586.4003,},
	armor_0 = { name = "arm_generic", hitpoints = 673.0124, armor = 683.8469,},
	armor_1 = { name = "arm_generic", hitpoints = 675.7657, armor = 689.0214,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 32.12646, energy = 814.4739,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 191.0018, armor = 196.5669, rate = 0.4277721, drain = 15.39765, maxDamage = 333.7205, shieldEfficiency = 0, minDamage = 305.243, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_ykl37r, "object/ship/ykl37r.iff")
