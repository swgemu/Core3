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


object_ship_xwing_tier5 = object_ship_shared_xwing_tier5:new {

	name = "xwing_tier5",
	slideFactor = 1.82,
	chassisHitpoints = 2703.36,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 3333.478, armor = 3473.092,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 3468.217, armor = 3331.086, speed = 45.65501, pitch = 25.43775, roll = 31.08363, yaw = 19.89735, acceleration = 11.30402, rollRate = 58.43615, pitchRate = 51.96029, deceleration = 9.355584, yawRate = 42.37018,},
	shield_0 = { name = "shd_generic", hitpoints = 3411.882, armor = 3351.479, regen = 25.30956, front = 13976.35, back = 13817.39,},
	armor_0 = { name = "arm_generic", hitpoints = 6654.104, armor = 6507.323,},
	armor_1 = { name = "arm_generic", hitpoints = 6745.794, armor = 6501.23,},
	capacitor = { name = "cap_generic", hitpoints = 3407.205, armor = 3389.327, rechargeRate = 95.08839, energy = 4786.771,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 3350.732, armor = 3369.467, rate = 0.7691118, drain = 0.9869733, maxDamage = 350.7094, shieldEfficiency = 0.5328934, minDamage = 216.4678, ammo = 0, ammo_type = 0, armorEfficiency = 0.5388327,},
}

ObjectTemplates:addTemplate(object_ship_xwing_tier5, "object/ship/xwing_tier5.iff")
