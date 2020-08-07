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


object_ship_escape_pod_tier3 = object_ship_shared_escape_pod_tier3:new {

	name = "escape_pod_tier3",
	slideFactor = 1.99,
	chassisHitpoints = 600,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 519.4321, armor = 536.1206,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 516.9468, armor = 534.5385, speed = 43.0627, pitch = 24.03469, roll = 29.0733, yaw = 18.66013, acceleration = 10.30784, rollRate = 52.90909, pitchRate = 47.68497, deceleration = 9.18014, yawRate = 40.40339,},
	shield_0 = { name = "shd_generic", hitpoints = 525.3044, armor = 521.213, regen = 4.424402, front = 2098.447, back = 2057.913,},
	armor_0 = { name = "arm_generic", hitpoints = 1137.104, armor = 1123.686,},
	armor_1 = { name = "arm_generic", hitpoints = 1118.558, armor = 1151.698,},
	capacitor = { name = "cap_generic", hitpoints = 538.4606, armor = 532.6387, rechargeRate = 98.81543, energy = 4925.965,},
}

ObjectTemplates:addTemplate(object_ship_escape_pod_tier3, "object/ship/escape_pod_tier3.iff")
