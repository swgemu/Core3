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


object_ship_merchant_cruiser_medium_tier4 = object_ship_shared_merchant_cruiser_medium_tier4:new {

	name = "merchant_cruiser_medium_tier4",
	slideFactor = 1.76,
	chassisHitpoints = 19200,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 19897.19, armor = 20161.13,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 19823.12, armor = 20504.59, speed = 45.14246, pitch = 24.05825, roll = 30.3284, yaw = 19.48501, acceleration = 10.78047, rollRate = 56.30042, pitchRate = 49.88011, deceleration = 9.406126, yawRate = 41.13876,},
	shield_0 = { name = "shd_generic", hitpoints = 20429.32, armor = 20275.75, regen = 21.39937, front = 79421.77, back = 81929.1,},
	armor_0 = { name = "arm_generic", hitpoints = 42245.71, armor = 43011.5,},
	armor_1 = { name = "arm_generic", hitpoints = 42780.85, armor = 43675.59,},
	capacitor = { name = "cap_generic", hitpoints = 20231.7, armor = 20728.5, rechargeRate = 98.13493, energy = 4846.457,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 20467.95, armor = 20484.93, rate = 0.7792344, drain = 0.9536395, maxDamage = 604.4889, shieldEfficiency = 0.5356234, minDamage = 399.1525, ammo = 0, ammo_type = 0, armorEfficiency = 0.5577201,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 20196.68, armor = 20166.57, rate = 0.7495695, drain = 0.9503247, maxDamage = 626.8235, shieldEfficiency = 0.5580019, minDamage = 394.3095, ammo = 0, ammo_type = 0, armorEfficiency = 0.5507296,},
	weapon_2 = { name = "wpn_incom_blaster", hitpoints = 20183.68, armor = 20320.88, rate = 0.7703784, drain = 0.9796497, maxDamage = 607.6391, shieldEfficiency = 0.55988, minDamage = 400.4679, ammo = 0, ammo_type = 0, armorEfficiency = 0.5591903,},
	weapon_3 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 20723.04, armor = 20668.72, rate = 2.901886, drain = 0.9859794, maxDamage = 1828.936, shieldEfficiency = 0.7343538, minDamage = 787.3807, ammo = 4, ammo_type = 19, armorEfficiency = 0.7347184,},
	weapon_4 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 20720.59, armor = 19875.05, rate = 2.936957, drain = 0.9639654, maxDamage = 1814.389, shieldEfficiency = 0.7439837, minDamage = 795.248, ammo = 4, ammo_type = 19, armorEfficiency = 0.7346666,},
}

ObjectTemplates:addTemplate(object_ship_merchant_cruiser_medium_tier4, "object/ship/merchant_cruiser_medium_tier4.iff")
