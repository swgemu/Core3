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


object_ship_freighterheavy_tier3 = object_ship_shared_freighterheavy_tier3:new {

	name = "freighterheavy_tier3",
	slideFactor = 1.91,
	chassisHitpoints = 2400,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 2089.87, armor = 2094.871,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 2111.033, armor = 2135.751, speed = 43.26037, pitch = 24.47098, roll = 29.63879, yaw = 19.3651, acceleration = 10.37635, rollRate = 53.11479, pitchRate = 48.8131, deceleration = 8.873391, yawRate = 39.52461,},
	shield_0 = { name = "shd_generic", hitpoints = 2105.108, armor = 2119.919, regen = 13.78942, front = 21231.01, back = 21355.88,},
	armor_0 = { name = "arm_generic", hitpoints = 11409.09, armor = 11318.63,},
	armor_1 = { name = "arm_generic", hitpoints = 11066.27, armor = 11385.63,},
	capacitor = { name = "cap_generic", hitpoints = 2092.672, armor = 2097.111, rechargeRate = 95.47742, energy = 4794.566,},
}

ObjectTemplates:addTemplate(object_ship_freighterheavy_tier3, "object/ship/freighterheavy_tier3.iff")
