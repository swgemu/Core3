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


object_ship_rebel_shuttle_tier1 = object_ship_shared_rebel_shuttle_tier1:new {

	name = "rebel_shuttle_tier1",
	slideFactor = 1.74,
	chassisHitpoints = 720,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 299.9077, armor = 293.6346,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 297.1208, armor = 299.4472, speed = 41.2334, pitch = 22.47279, roll = 27.88967, yaw = 17.45551, acceleration = 10.00138, rollRate = 50.53764, pitchRate = 44.13609, deceleration = 8.458522, yawRate = 36.79752,},
	shield_0 = { name = "shd_generic", hitpoints = 299.2231, armor = 292.0293, regen = 5.757789, front = 2290.133, back = 2299.5,},
	armor_0 = { name = "arm_generic", hitpoints = 938.9934, armor = 941.7742,},
	armor_1 = { name = "arm_generic", hitpoints = 927.4939, armor = 918.2663,},
	capacitor = { name = "cap_generic", hitpoints = 286.9182, armor = 289.49, rechargeRate = 98.48814, energy = 4961.039,},
}

ObjectTemplates:addTemplate(object_ship_rebel_shuttle_tier1, "object/ship/rebel_shuttle_tier1.iff")
