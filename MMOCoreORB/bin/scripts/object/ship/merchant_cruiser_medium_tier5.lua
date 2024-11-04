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
	objectName = "@space/space_mobile_type:merchant_cruiser_medium_tier5",

	name = "merchant_cruiser_medium_tier5",
	type = "merchant_cruiser_medium_tier5",
	faction = "civilian",
	difficulty = "tier5",

	slideFactor = 1.76,
	chassisHitpoints = 24576,
	chassisMass = 5000,

	gameObjectType = 536870919,

	reactor = {name = "rct_generic", hitpoints = 31850.5, armor = 31850.5},
	engine = {name = "eng_incom_fusialthrust", hitpoints = 31850.5, armor = 31850.5, speed = 47.27, acceleration = 11.48, deceleration = 9.79, yaw = 20.6, yawRate = 43.22, pitch = 26, pitchRate = 52, roll = 32.19, rollRate = 58.64},
	shield_0 = {name = "shd_generic", hitpoints = 31850.5, armor = 31850.5, front = 127402, back = 127402, regen = 34.73},
	armor_0 = {name = "arm_generic", hitpoints = 67947.7, armor = 67947.7},
	armor_1 = {name = "arm_generic", hitpoints = 67947.7, armor = 67947.7},
	capacitor = {name = "cap_generic", hitpoints = 31850.5, armor = 31850.5, energy = 5000, rechargeRate = 100},
	weapon_0 = {name = "wpn_incom_blaster", hitpoints = 31850.5, armor = 31850.5, rate = 0.78, drain = 1, maxDamage = 822.94, minDamage = 512.41, shieldEfficiency = 0.56, armorEfficiency = 0.56, ammo = 0, ammo_type = 0},
	weapon_1 = {name = "wpn_incom_blaster", hitpoints = 31850.5, armor = 31850.5, rate = 0.78, drain = 1, maxDamage = 822.94, minDamage = 512.41, shieldEfficiency = 0.56, armorEfficiency = 0.56, ammo = 0, ammo_type = 0},
	weapon_2 = {name = "wpn_incom_blaster", hitpoints = 31850.5, armor = 31850.5, rate = 0.78, drain = 1, maxDamage = 822.94, minDamage = 512.41, shieldEfficiency = 0.56, armorEfficiency = 0.56, ammo = 0, ammo_type = 0},
	weapon_3 = {name = "wpn_seinar_concussion_missile_s01", hitpoints = 31850.5, armor = 31850.5, rate = 3, drain = 1, maxDamage = 2468.82, minDamage = 1024.82, shieldEfficiency = 0.75, armorEfficiency = 0.75, ammo = 4, ammo_type = 20},
	weapon_4 = {name = "wpn_seinar_concussion_missile_s01", hitpoints = 31850.5, armor = 31850.5, rate = 3, drain = 1, maxDamage = 2468.82, minDamage = 1024.82, shieldEfficiency = 0.75, armorEfficiency = 0.75, ammo = 4, ammo_type = 20},
}

ObjectTemplates:addTemplate(object_ship_merchant_cruiser_medium_tier5, "object/ship/merchant_cruiser_medium_tier5.iff")
