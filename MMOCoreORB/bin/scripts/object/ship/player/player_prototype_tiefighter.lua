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


object_ship_player_player_prototype_tiefighter = object_ship_player_shared_player_prototype_tiefighter:new {

	name = "player_prototype_tiefighter",
	slideFactor = 1.95,
	chassisHitpoints = 800,
	chassisMass = 11000,
	reactor = { name = "rct_prototype", hitpoints = 198.7087, armor = 98.2579,},
	engine = { name = "eng_prototype", hitpoints = 190.9079, armor = 99.93941, speed = 48.28564, pitch = 47.30927, roll = 51.36045, yaw = 46.8244, acceleration = 15.75394, rollRate = 75.24479, pitchRate = 71.66323, deceleration = 13.66962, yawRate = 69.7346,},
	shield_0 = { name = "shd_prototype", hitpoints = 198.0411, armor = 98.43318, regen = 1.90137, front = 289.3702, back = 295.8642,},
	armor_0 = { name = "arm_prototype", hitpoints = 241.4306, armor = 249.378,},
	armor_1 = { name = "arm_prototype", hitpoints = 246.3849, armor = 241.1599,},
	capacitor = { name = "cap_prototype", hitpoints = 199.9194, armor = 97.33989, rechargeRate = 19.64005, energy = 482.3818,},
}

ObjectTemplates:addTemplate(object_ship_player_player_prototype_tiefighter, "object/ship/player/player_prototype_tiefighter.iff")
