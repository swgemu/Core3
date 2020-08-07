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


object_ship_z95_tier4 = object_ship_shared_z95_tier4:new {

	name = "z95_tier4",
	slideFactor = 1.84,
	chassisHitpoints = 1920,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1994.635, armor = 2015.03,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 2030.5, armor = 1994.821, speed = 49.54393, pitch = 24.50714, roll = 30.20708, yaw = 19.33429, acceleration = 12.1328, rollRate = 56.36481, pitchRate = 50.22535, deceleration = 9.275075, yawRate = 40.70377,},
	shield_0 = { name = "shd_generic", hitpoints = 2060.675, armor = 2047.209, regen = 14.64976, front = 9092.767, back = 8763.016,},
	armor_0 = { name = "arm_generic", hitpoints = 3411.246, armor = 3397.123,},
	armor_1 = { name = "arm_generic", hitpoints = 3504.079, armor = 3501.493,},
	capacitor = { name = "cap_generic", hitpoints = 1988.392, armor = 2006.542, rechargeRate = 95.30588, energy = 4917,},
	booster = { name = "bst_generic", hitpoints = 1987.924, armor = 2021.7, energy = 98.85378, acceleration = 19.28028, speed = 14.70088, energyUsage = 9.972193, rechargeRate = 2.861164,},
	weapon_0 = { name = "wpn_z95_blaster", hitpoints = 2057.371, armor = 1982.409, rate = 0.760184, drain = 0.9671793, maxDamage = 234.6596, shieldEfficiency = 0.5333772, minDamage = 153.6613, ammo = 0, ammo_type = 0, armorEfficiency = 0.5501444,},
}

ObjectTemplates:addTemplate(object_ship_z95_tier4, "object/ship/z95_tier4.iff")
