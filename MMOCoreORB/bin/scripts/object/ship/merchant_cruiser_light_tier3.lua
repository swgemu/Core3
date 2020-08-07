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


object_ship_merchant_cruiser_light_tier3 = object_ship_shared_merchant_cruiser_light_tier3:new {

	name = "merchant_cruiser_light_tier3",
	slideFactor = 1.76,
	chassisHitpoints = 12000,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 10280.47, armor = 10354.47,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 10368.07, armor = 10622.91, speed = 42.52817, pitch = 23.48374, roll = 30.08207, yaw = 19.25985, acceleration = 10.71831, rollRate = 53.3816, pitchRate = 47.8039, deceleration = 9.119418, yawRate = 40.12263,},
	shield_0 = { name = "shd_generic", hitpoints = 10359.47, armor = 10260.52, regen = 13.61836, front = 41308.59, back = 43009.62,},
	armor_0 = { name = "arm_generic", hitpoints = 21959.59, armor = 22459.14,},
	armor_1 = { name = "arm_generic", hitpoints = 22618.67, armor = 21996.24,},
	capacitor = { name = "cap_generic", hitpoints = 10337.06, armor = 10548.25, rechargeRate = 98.03333, energy = 4862.774,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 10397.86, armor = 10709.83, rate = 0.7605727, drain = 0.9907377, maxDamage = 397.5931, shieldEfficiency = 0.5392079, minDamage = 272.1431, ammo = 0, ammo_type = 0, armorEfficiency = 0.5472658,},
}

ObjectTemplates:addTemplate(object_ship_merchant_cruiser_light_tier3, "object/ship/merchant_cruiser_light_tier3.iff")
