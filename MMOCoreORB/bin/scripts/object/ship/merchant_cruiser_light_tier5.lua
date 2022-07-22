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


object_ship_merchant_cruiser_light_tier5 = object_ship_shared_merchant_cruiser_light_tier5:new {

	name = "merchant_cruiser_light_tier5",
	slideFactor = 1.76,
	chassisHitpoints = 24576,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 31555.93, armor = 30527.7,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 31146.61, armor = 30816.52, speed = 46.50668, pitch = 25.23399, roll = 30.89483, yaw = 20.28164, acceleration = 11.47929, rollRate = 56.7858, pitchRate = 51.00734, deceleration = 9.465745, yawRate = 41.32277,},
	shield_0 = { name = "shd_generic", hitpoints = 30615.34, armor = 31087.78, regen = 33.47599, front = 124098.1, back = 121125.6,},
	armor_0 = { name = "arm_generic", hitpoints = 67597.22, armor = 64778.91,},
	armor_1 = { name = "arm_generic", hitpoints = 67189.88, armor = 67711.52,},
	capacitor = { name = "cap_generic", hitpoints = 31050.49, armor = 31843.32, rechargeRate = 98.041, energy = 4797.549,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 30299.98, armor = 30738.56, rate = 0.7799323, drain = 0.990948, maxDamage = 812.7977, shieldEfficiency = 0.5380484, minDamage = 493.2937, ammo = 0, ammo_type = 0, armorEfficiency = 0.5484046,},
}

ObjectTemplates:addTemplate(object_ship_merchant_cruiser_light_tier5, "object/ship/merchant_cruiser_light_tier5.iff")
