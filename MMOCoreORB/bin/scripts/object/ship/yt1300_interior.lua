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


object_ship_yt1300_interior = object_ship_shared_yt1300_interior:new {

	name = "yt1300_interior",
	slideFactor = 1.81,
	chassisHitpoints = 654,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 98.24966, armor = 97.1135,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 96.68863, armor = 95.77509, speed = 46.5601, pitch = 20.41633, roll = 21.31101, yaw = 20.71701, acceleration = 7.889253, rollRate = 41.62087, pitchRate = 41.12764, deceleration = 11.9265, yawRate = 41.06276,},
	shield_0 = { name = "shd_generic", hitpoints = 395.1289, armor = 489.5832, regen = 4.791471, front = 570.4082, back = 591.0665,},
	armor_0 = { name = "arm_generic", hitpoints = 665.5047, armor = 677.7966,},
	armor_1 = { name = "arm_generic", hitpoints = 697.936, armor = 695.6458,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 31.83912, energy = 795.0894,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 193.9292, armor = 198.6048, rate = 0.4110003, drain = 15.0666, maxDamage = 335.8782, shieldEfficiency = 0, minDamage = 308.376, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_yt1300_interior, "object/ship/yt1300_interior.iff")
