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


object_ship_droid_fighter_tier4 = object_ship_shared_droid_fighter_tier4:new {

	name = "droid_fighter_tier4",
	slideFactor = 1.92,
	chassisHitpoints = 1920,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 2059.873, armor = 2055.98,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 2044.096, armor = 1998.473, speed = 44.8854, pitch = 24.72549, roll = 29.81529, yaw = 19.14608, acceleration = 10.79832, rollRate = 55.65337, pitchRate = 50.18822, deceleration = 9.384644, yawRate = 40.09525,},
	shield_0 = { name = "shd_generic", hitpoints = 1993.237, armor = 2045.874, regen = 14.62505, front = 8089.994, back = 7956.828,},
	armor_0 = { name = "arm_generic", hitpoints = 4351.913, armor = 4351.372,},
	armor_1 = { name = "arm_generic", hitpoints = 4324.767, armor = 4409.92,},
	capacitor = { name = "cap_generic", hitpoints = 2015.354, armor = 2073.416, rechargeRate = 97.49385, energy = 4792.98,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 2056.918, armor = 2050.273, rate = 0.7639044, drain = 0.9809104, maxDamage = 249.6993, shieldEfficiency = 0.5464978, minDamage = 158.4243, ammo = 0, ammo_type = 0, armorEfficiency = 0.5393805,},
}

ObjectTemplates:addTemplate(object_ship_droid_fighter_tier4, "object/ship/droid_fighter_tier4.iff")
