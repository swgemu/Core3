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


object_ship_merchant_cruiser_medium_tier3 = object_ship_shared_merchant_cruiser_medium_tier3:new {

	name = "merchant_cruiser_medium_tier3",
	slideFactor = 1.76,
	chassisHitpoints = 12000,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 10690.84, armor = 10576.56,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 10597.17, armor = 10276.01, speed = 43.28926, pitch = 24.17556, roll = 30.20519, yaw = 19.3596, acceleration = 10.36408, rollRate = 53.6869, pitchRate = 47.58229, deceleration = 8.856448, yawRate = 39.0793,},
	shield_0 = { name = "shd_generic", hitpoints = 10773.29, armor = 10671.96, regen = 13.30877, front = 42830.36, back = 42877.58,},
	armor_0 = { name = "arm_generic", hitpoints = 22196.62, armor = 22592.94,},
	armor_1 = { name = "arm_generic", hitpoints = 22718.34, armor = 22111.9,},
	capacitor = { name = "cap_generic", hitpoints = 10581.5, armor = 10508.78, rechargeRate = 95.02969, energy = 4762.554,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 10682.54, armor = 10289.86, rate = 0.7579356, drain = 0.9702955, maxDamage = 389.9348, shieldEfficiency = 0.5436607, minDamage = 265.981, ammo = 0, ammo_type = 0, armorEfficiency = 0.5410048,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 10341.02, armor = 10570.36, rate = 0.7627427, drain = 0.9991128, maxDamage = 404.8998, shieldEfficiency = 0.5416773, minDamage = 274.947, ammo = 0, ammo_type = 0, armorEfficiency = 0.5543449,},
	weapon_2 = { name = "wpn_incom_blaster", hitpoints = 10534.71, armor = 10369.17, rate = 0.7666565, drain = 0.9822307, maxDamage = 396.2336, shieldEfficiency = 0.5391278, minDamage = 264.4042, ammo = 0, ammo_type = 0, armorEfficiency = 0.545708,},
	weapon_3 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 10385.48, armor = 10567.37, rate = 2.923486, drain = 0.9924983, maxDamage = 1195.973, shieldEfficiency = 0.726214, minDamage = 538.1055, ammo = 4, ammo_type = 18, armorEfficiency = 0.7289072,},
	weapon_4 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 10518.74, armor = 10750.97, rate = 2.987611, drain = 0.9907716, maxDamage = 1212.855, shieldEfficiency = 0.7477772, minDamage = 554.8812, ammo = 4, ammo_type = 18, armorEfficiency = 0.7419452,},
}

ObjectTemplates:addTemplate(object_ship_merchant_cruiser_medium_tier3, "object/ship/merchant_cruiser_medium_tier3.iff")
