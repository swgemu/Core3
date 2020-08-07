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


object_ship_freightermedium_tier3 = object_ship_shared_freightermedium_tier3:new {

	name = "freightermedium_tier3",
	slideFactor = 1.87,
	chassisHitpoints = 2400,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 2137.504, armor = 2072.528,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 2119.626, armor = 2154.599, speed = 43.44228, pitch = 23.34284, roll = 30.24805, yaw = 19.04215, acceleration = 10.49199, rollRate = 53.40024, pitchRate = 46.78446, deceleration = 9.222301, yawRate = 40.04214,},
	shield_0 = { name = "shd_generic", hitpoints = 2109.113, armor = 2145.308, regen = 11.48495, front = 16971.12, back = 16919.22,},
	armor_0 = { name = "arm_generic", hitpoints = 9023.489, armor = 8960.555,},
	armor_1 = { name = "arm_generic", hitpoints = 8759.734, armor = 8921.938,},
	capacitor = { name = "cap_generic", hitpoints = 2110.199, armor = 2054.25, rechargeRate = 95.67603, energy = 4779.484,},
}

ObjectTemplates:addTemplate(object_ship_freightermedium_tier3, "object/ship/freightermedium_tier3.iff")
