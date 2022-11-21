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


object_ship_ywing_tier2 = object_ship_shared_ywing_tier2:new {

	name = "ywing_tier2",
	slideFactor = 1.77,
	chassisHitpoints = 600,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 445.0043, armor = 434.877,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 438.2476, armor = 431.5118, speed = 42.70076, pitch = 23.05896, roll = 28.26923, yaw = 18.58615, acceleration = 10.27646, rollRate = 51.66872, pitchRate = 47.08105, deceleration = 8.86182, yawRate = 39.46039,},
	shield_0 = { name = "shd_generic", hitpoints = 429.1438, armor = 447.433, regen = 5.145575, front = 1759.123, back = 1745.841,},
	armor_0 = { name = "arm_generic", hitpoints = 1030.453, armor = 1009.185,},
	armor_1 = { name = "arm_generic", hitpoints = 1053.618, armor = 1043.182,},
	capacitor = { name = "cap_generic", hitpoints = 445.8772, armor = 435.7293, rechargeRate = 97.91825, energy = 4779.55,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 436.8438, armor = 441.8253, rate = 0.7662566, drain = 0.9645161, maxDamage = 84.31668, shieldEfficiency = 0.547462, minDamage = 61.27518, ammo = 0, ammo_type = 0, armorEfficiency = 0.5338033,},
	weapon_1 = { name = "wpn_slayn_ioncannon", hitpoints = 436.8471, armor = 429.3358, rate = 0.7512724, drain = 0.9929672, maxDamage = 85.58548, shieldEfficiency = 0.5344715, minDamage = 59.85552, ammo = 0, ammo_type = 0, armorEfficiency = 0.5465667,},
	weapon_2 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 442.7952, armor = 432.0674, rate = 2.957389, drain = 0.980367, maxDamage = 251.3224, shieldEfficiency = 0.7203062, minDamage = 123.2273, ammo = 4, ammo_type = 17, armorEfficiency = 0.7355347,},
}

ObjectTemplates:addTemplate(object_ship_ywing_tier2, "object/ship/ywing_tier2.iff")
