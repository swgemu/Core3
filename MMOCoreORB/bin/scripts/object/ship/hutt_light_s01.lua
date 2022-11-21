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


object_ship_hutt_light_s01 = object_ship_shared_hutt_light_s01:new {

	name = "hutt_light_s01",
	slideFactor = 1.81,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 285.1479, armor = 295.0122,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 96.76293, armor = 99.59937, speed = 53.13794, pitch = 33.21452, roll = 33.83427, yaw = 33.66465, acceleration = 16.59954, rollRate = 59.55499, pitchRate = 59.26021, deceleration = 8.056838, yawRate = 59.80057,},
	shield_0 = { name = "shd_generic", hitpoints = 385.6078, armor = 489.0244, regen = 4.882521, front = 290.288, back = 475.1198,},
	armor_0 = { name = "arm_generic", hitpoints = 286.8041, armor = 291.5036,},
	armor_1 = { name = "arm_generic", hitpoints = 285.8856, armor = 288.627,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.35004, energy = 557.7441,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.06699, armor = 19.84051, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 199.6401, armor = 191.3367, rate = 0.3371574, drain = 23.38488, maxDamage = 243.9093, shieldEfficiency = 0, minDamage = 114.018, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_hutt_light_s01, "object/ship/hutt_light_s01.iff")
