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


object_ship_escape_pod_tier2 = object_ship_shared_escape_pod_tier2:new {

	name = "escape_pod_tier2",
	slideFactor = 1.99,
	chassisHitpoints = 300,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 215.947, armor = 216.5833,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 222.5308, armor = 215.0814, speed = 41.19627, pitch = 23.76989, roll = 28.72633, yaw = 18.00831, acceleration = 10.18801, rollRate = 53.19677, pitchRate = 47.16774, deceleration = 8.902427, yawRate = 38.87392,},
	shield_0 = { name = "shd_generic", hitpoints = 216.1432, armor = 216.9752, regen = 2.659348, front = 869.7957, back = 856.6164,},
	armor_0 = { name = "arm_generic", hitpoints = 479.1068, armor = 468.8734,},
	armor_1 = { name = "arm_generic", hitpoints = 459.7636, armor = 470.3629,},
	capacitor = { name = "cap_generic", hitpoints = 216.1964, armor = 223.7111, rechargeRate = 97.18076, energy = 4863.069,},
}

ObjectTemplates:addTemplate(object_ship_escape_pod_tier2, "object/ship/escape_pod_tier2.iff")
