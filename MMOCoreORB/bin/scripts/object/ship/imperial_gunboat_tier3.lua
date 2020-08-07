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


object_ship_imperial_gunboat_tier3 = object_ship_shared_imperial_gunboat_tier3:new {

	name = "imperial_gunboat_tier3",
	slideFactor = 1.81,
	chassisHitpoints = 12000,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 10761.92, armor = 10649.73,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 10748.74, armor = 10585.94, speed = 43.73413, pitch = 24.38476, roll = 29.04128, yaw = 18.63824, acceleration = 10.81688, rollRate = 53.39226, pitchRate = 47.65085, deceleration = 8.87024, yawRate = 40.32088,},
	shield_0 = { name = "shd_generic", hitpoints = 10798.42, armor = 10694.76, regen = 13.82452, front = 42079.57, back = 42959.41,},
	armor_0 = { name = "arm_generic", hitpoints = 22608.06, armor = 22110.39,},
	armor_1 = { name = "arm_generic", hitpoints = 22536.55, armor = 23026.12,},
	capacitor = { name = "cap_generic", hitpoints = 10520.84, armor = 10554.68, rechargeRate = 96.60434, energy = 4906.71,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 10708.18, armor = 10301.62, rate = 0.7624281, drain = 0.9705418, maxDamage = 403.3317, shieldEfficiency = 0.5568329, minDamage = 276.8091, ammo = 0, ammo_type = 0, armorEfficiency = 0.5581059,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 10308.1, armor = 10266.85, rate = 0.751726, drain = 0.9688557, maxDamage = 405.3387, shieldEfficiency = 0.5399861, minDamage = 266.1585, ammo = 0, ammo_type = 0, armorEfficiency = 0.5512564,},
	weapon_2 = { name = "wpn_tieadvanced_blaster", hitpoints = 10611.38, armor = 10409.54, rate = 0.7471573, drain = 0.973536, maxDamage = 389.8255, shieldEfficiency = 0.5336503, minDamage = 269.2772, ammo = 0, ammo_type = 0, armorEfficiency = 0.5479162,},
	weapon_3 = { name = "wpn_tieadvanced_blaster", hitpoints = 10645.71, armor = 10692.4, rate = 0.7443343, drain = 0.9966478, maxDamage = 389.9738, shieldEfficiency = 0.5501269, minDamage = 266.5001, ammo = 0, ammo_type = 0, armorEfficiency = 0.5512103,},
	weapon_4 = { name = "wpn_tieadvanced_blaster", hitpoints = 10266.78, armor = 10271.81, rate = 0.7683082, drain = 0.9716197, maxDamage = 403.7081, shieldEfficiency = 0.5345104, minDamage = 267.2189, ammo = 0, ammo_type = 0, armorEfficiency = 0.5566973,},
	weapon_5 = { name = "wpn_tieadvanced_blaster", hitpoints = 10560.16, armor = 10344.79, rate = 0.7746773, drain = 0.9602111, maxDamage = 402.1593, shieldEfficiency = 0.546963, minDamage = 268.9198, ammo = 0, ammo_type = 0, armorEfficiency = 0.5470427,},
}

ObjectTemplates:addTemplate(object_ship_imperial_gunboat_tier3, "object/ship/imperial_gunboat_tier3.iff")
