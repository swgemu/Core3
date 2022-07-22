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


object_ship_merchant_cruiser_light_tier4 = object_ship_shared_merchant_cruiser_light_tier4:new {

	name = "merchant_cruiser_light_tier4",
	slideFactor = 1.76,
	chassisHitpoints = 19200,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 20580.46, armor = 20329.61,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 19952.66, armor = 20392.64, speed = 43.7425, pitch = 24.49139, roll = 30.12407, yaw = 19.83489, acceleration = 11.03569, rollRate = 56.63684, pitchRate = 48.52476, deceleration = 9.038428, yawRate = 39.90187,},
	shield_0 = { name = "shd_generic", hitpoints = 19742.45, armor = 19811.1, regen = 22.25517, front = 82943.96, back = 82347.78,},
	armor_0 = { name = "arm_generic", hitpoints = 42657.19, armor = 42148.22,},
	armor_1 = { name = "arm_generic", hitpoints = 43349, armor = 44101.23,},
	capacitor = { name = "cap_generic", hitpoints = 20567.46, armor = 20667.59, rechargeRate = 98.13097, energy = 4751.08,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 20166.11, armor = 20570.8, rate = 0.7799047, drain = 0.9972451, maxDamage = 629.1267, shieldEfficiency = 0.550395, minDamage = 410.923, ammo = 0, ammo_type = 0, armorEfficiency = 0.5485765,},
}

ObjectTemplates:addTemplate(object_ship_merchant_cruiser_light_tier4, "object/ship/merchant_cruiser_light_tier4.iff")
