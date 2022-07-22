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


object_ship_merchant_cruiser_medium_tier2 = object_ship_shared_merchant_cruiser_medium_tier2:new {

	name = "merchant_cruiser_medium_tier2",
	slideFactor = 1.76,
	chassisHitpoints = 6000,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 4489.618, armor = 4381.367,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 4365.197, armor = 4397.695, speed = 41.21326, pitch = 22.90241, roll = 28.17224, yaw = 18.74071, acceleration = 10.16129, rollRate = 52.61631, pitchRate = 47.11389, deceleration = 8.675982, yawRate = 39.53732,},
	shield_0 = { name = "shd_generic", hitpoints = 4293.744, armor = 4301.271, regen = 7.88596, front = 17443.23, back = 17608.15,},
	armor_0 = { name = "arm_generic", hitpoints = 9409.773, armor = 9257.783,},
	armor_1 = { name = "arm_generic", hitpoints = 9315.726, armor = 9240.271,},
	capacitor = { name = "cap_generic", hitpoints = 4334.665, armor = 4459.749, rechargeRate = 95.53326, energy = 4824.985,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 4391.136, armor = 4304.279, rate = 0.7450342, drain = 0.9765325, maxDamage = 210.6662, shieldEfficiency = 0.5539984, minDamage = 154.5177, ammo = 0, ammo_type = 0, armorEfficiency = 0.5458419,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 4405.522, armor = 4438.681, rate = 0.7629908, drain = 0.9951139, maxDamage = 215.419, shieldEfficiency = 0.551863, minDamage = 154.3544, ammo = 0, ammo_type = 0, armorEfficiency = 0.5527091,},
	weapon_2 = { name = "wpn_incom_blaster", hitpoints = 4415.027, armor = 4431.829, rate = 0.7712641, drain = 0.9642957, maxDamage = 219.5453, shieldEfficiency = 0.5380406, minDamage = 152.6045, ammo = 0, ammo_type = 0, armorEfficiency = 0.5565039,},
	weapon_3 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 4379.866, armor = 4326.969, rate = 2.996723, drain = 0.9936015, maxDamage = 638.8206, shieldEfficiency = 0.7223246, minDamage = 302.653, ammo = 5, ammo_type = 17, armorEfficiency = 0.7219664,},
	weapon_4 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 4445.275, armor = 4321.205, rate = 2.909174, drain = 0.9625892, maxDamage = 632.3728, shieldEfficiency = 0.726876, minDamage = 310.8459, ammo = 5, ammo_type = 17, armorEfficiency = 0.7184557,},
}

ObjectTemplates:addTemplate(object_ship_merchant_cruiser_medium_tier2, "object/ship/merchant_cruiser_medium_tier2.iff")
