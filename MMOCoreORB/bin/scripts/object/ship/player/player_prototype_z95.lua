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


object_ship_player_player_prototype_z95 = object_ship_player_shared_player_prototype_z95:new {

	name = "player_prototype_z95",
	slideFactor = 1.95,
	chassisHitpoints = 800,
	chassisMass = 11000,
	reactor = { name = "rct_prototype", hitpoints = 198.6076, armor = 98.58342,},
	engine = { name = "eng_prototype", hitpoints = 193.1231, armor = 99.77211, speed = 44.91402, pitch = 46.40807, roll = 49.72561, yaw = 45.87107, acceleration = 14.01144, rollRate = 75.18142, pitchRate = 71.61748, deceleration = 12.15011, yawRate = 69.51454,},
	shield_0 = { name = "shd_prototype", hitpoints = 195.2813, armor = 96.5105, regen = 1.989931, front = 290.9135, back = 297.9356,},
	armor_0 = { name = "arm_prototype", hitpoints = 245.9183, armor = 248.944,},
	armor_1 = { name = "arm_prototype", hitpoints = 239.831, armor = 240.3884,},
	capacitor = { name = "cap_prototype", hitpoints = 196.7573, armor = 99.72215, rechargeRate = 19.40641, energy = 475.8217,},
}

ObjectTemplates:addTemplate(object_ship_player_player_prototype_z95, "object/ship/player/player_prototype_z95.iff")
