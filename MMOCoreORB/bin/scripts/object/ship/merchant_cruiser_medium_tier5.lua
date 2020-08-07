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


object_ship_merchant_cruiser_medium_tier5 = object_ship_shared_merchant_cruiser_medium_tier5:new {

	name = "merchant_cruiser_medium_tier5",
	slideFactor = 1.76,
	chassisHitpoints = 24576,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 31374.25, armor = 31473.09,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 31715.44, armor = 31322.01, speed = 46.00034, pitch = 25.52698, roll = 31.7774, yaw = 20.58438, acceleration = 11.12726, rollRate = 57.04425, pitchRate = 50.90641, deceleration = 9.580009, yawRate = 41.4047,},
	shield_0 = { name = "shd_generic", hitpoints = 31406.62, armor = 31011.88, regen = 33.87177, front = 124402.8, back = 127368.4,},
	armor_0 = { name = "arm_generic", hitpoints = 66250.25, armor = 66480.52,},
	armor_1 = { name = "arm_generic", hitpoints = 67037.62, armor = 66882.09,},
	capacitor = { name = "cap_generic", hitpoints = 30760.99, armor = 31341.01, rechargeRate = 99.1574, energy = 4754.951,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 31378.05, armor = 31709.45, rate = 0.7577992, drain = 0.9805011, maxDamage = 791.7409, shieldEfficiency = 0.541249, minDamage = 503.3585, ammo = 0, ammo_type = 0, armorEfficiency = 0.5526683,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 30514.77, armor = 30504.45, rate = 0.7509074, drain = 0.9799721, maxDamage = 797.0836, shieldEfficiency = 0.5496975, minDamage = 508.0051, ammo = 0, ammo_type = 0, armorEfficiency = 0.55691,},
	weapon_2 = { name = "wpn_incom_blaster", hitpoints = 30654.87, armor = 31358.1, rate = 0.7549043, drain = 0.9532104, maxDamage = 791.2296, shieldEfficiency = 0.5452173, minDamage = 489.9865, ammo = 0, ammo_type = 0, armorEfficiency = 0.5504653,},
	weapon_3 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 31564.13, armor = 31448.54, rate = 2.984567, drain = 0.9888422, maxDamage = 2464.714, shieldEfficiency = 0.7487413, minDamage = 995.6216, ammo = 4, ammo_type = 20, armorEfficiency = 0.7453952,},
	weapon_4 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 30567.44, armor = 31831.83, rate = 2.991441, drain = 0.9994885, maxDamage = 2406.495, shieldEfficiency = 0.7189596, minDamage = 976.4769, ammo = 4, ammo_type = 20, armorEfficiency = 0.7176121,},
}

ObjectTemplates:addTemplate(object_ship_merchant_cruiser_medium_tier5, "object/ship/merchant_cruiser_medium_tier5.iff")
