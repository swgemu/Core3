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


object_ship_tiebomber_tier5 = object_ship_shared_tiebomber_tier5:new {

	name = "tiebomber_tier5",
	slideFactor = 1.66,
	chassisHitpoints = 3686.4,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 3141.983, armor = 3155.309,},
	engine = { name = "eng_qualdex_kyromaster", hitpoints = 3063.181, armor = 3073.784, speed = 45.8022, pitch = 25.79286, roll = 32.14608, yaw = 19.61679, acceleration = 11.12937, rollRate = 56.71141, pitchRate = 51.96689, deceleration = 9.541771, yawRate = 42.06806,},
	shield_0 = { name = "shd_generic", hitpoints = 3155.146, armor = 3036.634, regen = 16.89808, front = 9393.041, back = 9160.638,},
	armor_0 = { name = "arm_generic", hitpoints = 10154.12, armor = 9963.289,},
	armor_1 = { name = "arm_generic", hitpoints = 10081.48, armor = 10079.79,},
	capacitor = { name = "cap_generic", hitpoints = 3032.32, armor = 3086.785, rechargeRate = 98.03413, energy = 4848.718,},
	weapon_0 = { name = "wpn_generic", hitpoints = 3176.51, armor = 3138.366, rate = 0.7458783, drain = 0.9643333, maxDamage = 313.0116, shieldEfficiency = 0.5434121, minDamage = 194.7827, ammo = 0, ammo_type = 0, armorEfficiency = 0.5359623,},
	weapon_1 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 3081.964, armor = 3118.871, rate = 2.955065, drain = 0.9595261, maxDamage = 961.2502, shieldEfficiency = 0.7267202, minDamage = 391.5465, ammo = 4, ammo_type = 20, armorEfficiency = 0.7243592,},
}

ObjectTemplates:addTemplate(object_ship_tiebomber_tier5, "object/ship/tiebomber_tier5.iff")
