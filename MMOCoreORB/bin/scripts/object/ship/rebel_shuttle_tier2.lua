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


object_ship_rebel_shuttle_tier2 = object_ship_shared_rebel_shuttle_tier2:new {

	name = "rebel_shuttle_tier2",
	slideFactor = 1.74,
	chassisHitpoints = 1800,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 870.1052, armor = 883.1102,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 892.7454, armor = 877.7985, speed = 41.1066, pitch = 23.61261, roll = 28.94217, yaw = 18.64984, acceleration = 10.30313, rollRate = 52.42613, pitchRate = 46.65723, deceleration = 8.823172, yawRate = 38.77637,},
	shield_0 = { name = "shd_generic", hitpoints = 886.3363, armor = 888.8769, regen = 10.46698, front = 7074.743, back = 6918.125,},
	armor_0 = { name = "arm_generic", hitpoints = 2756.615, armor = 2748.506,},
	armor_1 = { name = "arm_generic", hitpoints = 2833.431, armor = 2833.891,},
	capacitor = { name = "cap_generic", hitpoints = 873.3292, armor = 889.7833, rechargeRate = 97.69441, energy = 4798.872,},
}

ObjectTemplates:addTemplate(object_ship_rebel_shuttle_tier2, "object/ship/rebel_shuttle_tier2.iff")
