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


object_ship_xwing_tier1 = object_ship_shared_xwing_tier1:new {

	name = "xwing_tier1",
	slideFactor = 1.82,
	chassisHitpoints = 264,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 164.4245, armor = 161.6525,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 161.0701, armor = 157.0449, speed = 41.6953, pitch = 22.14303, roll = 27.96346, yaw = 17.83877, acceleration = 9.877025, rollRate = 51.24115, pitchRate = 45.44153, deceleration = 8.442305, yawRate = 36.55953,},
	shield_0 = { name = "shd_generic", hitpoints = 164.0397, armor = 163.0853, regen = 3.185945, front = 635.3815, back = 650.0144,},
	armor_0 = { name = "arm_generic", hitpoints = 309.1935, armor = 311.2391,},
	armor_1 = { name = "arm_generic", hitpoints = 308.3029, armor = 318.2279,},
	capacitor = { name = "cap_generic", hitpoints = 161.0113, armor = 157.7789, rechargeRate = 95.80184, energy = 4769.414,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 159.3396, armor = 161.854, rate = 0.7767842, drain = 0.9588504, maxDamage = 43.49759, shieldEfficiency = 0.5539361, minDamage = 32.95609, ammo = 0, ammo_type = 0, armorEfficiency = 0.5367047,},
}

ObjectTemplates:addTemplate(object_ship_xwing_tier1, "object/ship/xwing_tier1.iff")
