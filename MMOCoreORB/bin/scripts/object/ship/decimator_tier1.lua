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


object_ship_decimator_tier1 = object_ship_shared_decimator_tier1:new {

	name = "decimator_tier1",
	slideFactor = 1.69,
	chassisHitpoints = 480,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 293.5404, armor = 287.8472,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 288.4495, armor = 286.0468, speed = 41.78825, pitch = 22.95482, roll = 28.57805, yaw = 18.06454, acceleration = 9.830862, rollRate = 49.67852, pitchRate = 44.8877, deceleration = 8.309277, yawRate = 38.29203,},
	shield_0 = { name = "shd_generic", hitpoints = 285.6295, armor = 290.0041, regen = 5.949239, front = 1196.092, back = 1159.598,},
	armor_0 = { name = "arm_generic", hitpoints = 615.5135, armor = 616.041,},
	armor_1 = { name = "arm_generic", hitpoints = 617.7331, armor = 608.2418,},
	capacitor = { name = "cap_generic", hitpoints = 299.8088, armor = 296.999, rechargeRate = 95.34566, energy = 4878.504,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 298.616, armor = 289.3673, rate = 0.7578185, drain = 0.9955444, maxDamage = 77.61373, shieldEfficiency = 0.5460684, minDamage = 57.92361, ammo = 0, ammo_type = 0, armorEfficiency = 0.5484538,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 291.0769, armor = 299.8797, rate = 0.7480574, drain = 0.9693886, maxDamage = 77.65221, shieldEfficiency = 0.5370379, minDamage = 57.85472, ammo = 0, ammo_type = 0, armorEfficiency = 0.5320773,},
	weapon_2 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 290.965, armor = 293.9679, rate = 2.881977, drain = 0.9946571, maxDamage = 235.25, shieldEfficiency = 0.7207777, minDamage = 114.2198, ammo = 5, ammo_type = 16, armorEfficiency = 0.7490097,},
}

ObjectTemplates:addTemplate(object_ship_decimator_tier1, "object/ship/decimator_tier1.iff")
