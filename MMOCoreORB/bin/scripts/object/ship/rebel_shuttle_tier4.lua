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


object_ship_rebel_shuttle_tier4 = object_ship_shared_rebel_shuttle_tier4:new {

	name = "rebel_shuttle_tier4",
	slideFactor = 1.74,
	chassisHitpoints = 5760,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 4115.319, armor = 4145.254,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 3999.789, armor = 4139.17, speed = 43.97105, pitch = 24.05534, roll = 31.07307, yaw = 19.04632, acceleration = 11.05519, rollRate = 56.59566, pitchRate = 47.95974, deceleration = 9.347069, yawRate = 40.9987,},
	shield_0 = { name = "shd_generic", hitpoints = 4125.519, armor = 4078.18, regen = 29.01054, front = 32780.01, back = 32808,},
	armor_0 = { name = "arm_generic", hitpoints = 12897.76, armor = 12705.93,},
	armor_1 = { name = "arm_generic", hitpoints = 12930.49, armor = 12806.31,},
	capacitor = { name = "cap_generic", hitpoints = 4119.062, armor = 4001.313, rechargeRate = 97.84137, energy = 4876.488,},
}

ObjectTemplates:addTemplate(object_ship_rebel_shuttle_tier4, "object/ship/rebel_shuttle_tier4.iff")
