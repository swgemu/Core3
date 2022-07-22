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


object_ship_xwing_tier2 = object_ship_shared_xwing_tier2:new {

	name = "xwing_tier2",
	slideFactor = 1.82,
	chassisHitpoints = 660,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 482.3348, armor = 481.0563,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 477.0069, armor = 480.2801, speed = 41.38926, pitch = 22.70479, roll = 29.45451, yaw = 18.09829, acceleration = 10.49041, rollRate = 52.07286, pitchRate = 46.42949, deceleration = 8.658398, yawRate = 38.09115,},
	shield_0 = { name = "shd_generic", hitpoints = 489.4815, armor = 484.3088, regen = 5.734832, front = 1973.891, back = 1963.238,},
	armor_0 = { name = "arm_generic", hitpoints = 945.3066, armor = 920.1929,},
	armor_1 = { name = "arm_generic", hitpoints = 946.9966, armor = 956.9358,},
	capacitor = { name = "cap_generic", hitpoints = 472.2729, armor = 486.5019, rechargeRate = 99.10021, energy = 4798.548,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 481.4132, armor = 484.6074, rate = 0.7685615, drain = 0.9797057, maxDamage = 95.84052, shieldEfficiency = 0.5362579, minDamage = 66.80991, ammo = 0, ammo_type = 0, armorEfficiency = 0.5546988,},
}

ObjectTemplates:addTemplate(object_ship_xwing_tier2, "object/ship/xwing_tier2.iff")
