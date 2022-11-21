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


object_ship_yt1300 = object_ship_shared_yt1300:new {

	name = "yt1300",
	slideFactor = 1.81,
	chassisHitpoints = 654,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 99.15134, armor = 96.66331,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 95.34004, armor = 95.04004, speed = 45.03492, pitch = 20.85829, roll = 20.82134, yaw = 20.78702, acceleration = 8.003607, rollRate = 42.51056, pitchRate = 41.29465, deceleration = 12.27452, yawRate = 42.51198,},
	shield_0 = { name = "shd_generic", hitpoints = 389.0215, armor = 480.4506, regen = 4.963403, front = 580.5545, back = 599.5178,},
	armor_0 = { name = "arm_generic", hitpoints = 688.0748, armor = 683.0371,},
	armor_1 = { name = "arm_generic", hitpoints = 679.6068, armor = 671.7661,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 32.06187, energy = 793.5941,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 193.5208, armor = 193.8033, rate = 0.410849, drain = 15.4138, maxDamage = 325.5639, shieldEfficiency = 0, minDamage = 312.924, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_yt1300, "object/ship/yt1300.iff")
