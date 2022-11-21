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


object_ship_decimator = object_ship_shared_decimator:new {

	name = "decimator",
	slideFactor = 1.81,
	chassisHitpoints = 654,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 95.90758, armor = 98.60257,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 98.38642, armor = 95.57016, speed = 44.93588, pitch = 20.53907, roll = 21.25076, yaw = 20.4151, acceleration = 7.727978, rollRate = 42.63755, pitchRate = 41.06813, deceleration = 12.11134, yawRate = 42.63313,},
	shield_0 = { name = "shd_generic", hitpoints = 390.8747, armor = 488.2868, regen = 4.816055, front = 584.2844, back = 588.1197,},
	armor_0 = { name = "arm_generic", hitpoints = 690.6407, armor = 689.4864,},
	armor_1 = { name = "arm_generic", hitpoints = 677.5273, armor = 686.4539,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 31.26661, energy = 816.7931,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 191.1592, armor = 192.9333, rate = 0.4277923, drain = 15.28074, maxDamage = 329.2509, shieldEfficiency = 0, minDamage = 318.1564, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_decimator, "object/ship/decimator.iff")
