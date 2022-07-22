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


object_ship_tieoppressor = object_ship_shared_tieoppressor:new {

	name = "tieoppressor",
	slideFactor = 1.75,
	chassisHitpoints = 341,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 96.92564, armor = 99.23829,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 97.92104, armor = 98.94149, speed = 59.76754, pitch = 9.65837, roll = 9.785378, yaw = 9.671412, acceleration = 23.13995, rollRate = 22.2862, pitchRate = 21.21468, deceleration = 11.66852, yawRate = 21.25593,},
	shield_0 = { name = "shd_generic", hitpoints = 380.4287, armor = 482.3715, regen = 4.952908, front = 492.9891, back = 591.0677,},
	armor_0 = { name = "arm_generic", hitpoints = 667.3024, armor = 686.1801,},
	armor_1 = { name = "arm_generic", hitpoints = 689.6667, armor = 698.8655,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 57.03404, energy = 1452.302,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 199.6908, armor = 192.334, rate = 0.5640124, drain = 27.06128, maxDamage = 446.0307, shieldEfficiency = 0, minDamage = 306.6484, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 199.9991, armor = 195.7459, rate = 1.915418, drain = 26.76088, maxDamage = 27.14455, shieldEfficiency = 0, minDamage = 26.97079, ammo = 50, ammo_type = 2, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_tieoppressor, "object/ship/tieoppressor.iff")
