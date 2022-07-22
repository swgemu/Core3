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


object_ship_freighterlight_tier4 = object_ship_shared_freighterlight_tier4:new {

	name = "freighterlight_tier4",
	slideFactor = 1.83,
	chassisHitpoints = 3840,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 3978.618, armor = 3955.427,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 4017.551, armor = 4079.085, speed = 43.84938, pitch = 24.52036, roll = 30.93801, yaw = 19.57981, acceleration = 10.94364, rollRate = 54.39413, pitchRate = 50.46195, deceleration = 9.418634, yawRate = 41.64349,},
	shield_0 = { name = "shd_generic", hitpoints = 3954.225, armor = 4124.272, regen = 14.25008, front = 24468.92, back = 24461.84,},
	armor_0 = { name = "arm_generic", hitpoints = 13119.07, armor = 13115.31,},
	armor_1 = { name = "arm_generic", hitpoints = 13031.58, armor = 13090.42,},
	capacitor = { name = "cap_generic", hitpoints = 3974.839, armor = 4093.61, rechargeRate = 97.72363, energy = 4849.223,},
}

ObjectTemplates:addTemplate(object_ship_freighterlight_tier4, "object/ship/freighterlight_tier4.iff")
