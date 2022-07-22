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


object_ship_hutt_medium_s01 = object_ship_shared_hutt_medium_s01:new {

	name = "hutt_medium_s01",
	slideFactor = 1.85,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 293.7732, armor = 286.008,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 97.11028, armor = 97.51603, speed = 44.5535, pitch = 26.99002, roll = 27.42445, yaw = 26.67104, acceleration = 12.11497, rollRate = 53.69298, pitchRate = 52.91653, deceleration = 14.98393, yawRate = 54.45977,},
	shield_0 = { name = "shd_generic", hitpoints = 398.9885, armor = 499.7048, regen = 4.874917, front = 391.3164, back = 690.6237,},
	armor_0 = { name = "arm_generic", hitpoints = 496.9135, armor = 499.5482,},
	armor_1 = { name = "arm_generic", hitpoints = 482.4214, armor = 481.6833,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 33.64884, energy = 546.9104,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.35176, armor = 19.95021, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 193.4433, armor = 192.1093, rate = 0.330191, drain = 22.78698, maxDamage = 309.5438, shieldEfficiency = 0, minDamage = 199.6489, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_hutt_medium_s01, "object/ship/hutt_medium_s01.iff")
