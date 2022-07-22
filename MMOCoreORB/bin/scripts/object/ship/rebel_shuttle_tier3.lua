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


object_ship_rebel_shuttle_tier3 = object_ship_shared_rebel_shuttle_tier3:new {

	name = "rebel_shuttle_tier3",
	slideFactor = 1.74,
	chassisHitpoints = 3600,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 2158.54, armor = 2133.173,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 2069.507, armor = 2103.26, speed = 42.386, pitch = 23.40046, roll = 29.68691, yaw = 19.27076, acceleration = 10.47821, rollRate = 53.62675, pitchRate = 47.22021, deceleration = 9.121039, yawRate = 40.17486,},
	shield_0 = { name = "shd_generic", hitpoints = 2066.135, armor = 2119.483, regen = 17.58241, front = 17026.3, back = 17125.06,},
	armor_0 = { name = "arm_generic", hitpoints = 6758.562, armor = 6593.218,},
	armor_1 = { name = "arm_generic", hitpoints = 6640.543, armor = 6811.472,},
	capacitor = { name = "cap_generic", hitpoints = 2074.061, armor = 2066.235, rechargeRate = 96.58902, energy = 4797.708,},
}

ObjectTemplates:addTemplate(object_ship_rebel_shuttle_tier3, "object/ship/rebel_shuttle_tier3.iff")
