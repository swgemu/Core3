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


object_ship_player_player_prototype_hutt_light = object_ship_player_shared_player_prototype_hutt_light:new {

	name = "player_prototype_hutt_light",
	slideFactor = 1.95,
	chassisHitpoints = 800,
	chassisMass = 11000,
	reactor = { name = "rct_prototype", hitpoints = 193.7032, armor = 99.98684,},
	engine = { name = "eng_prototype", hitpoints = 197.7267, armor = 96.38854, speed = 43.77223, pitch = 47.23177, roll = 51.3638, yaw = 46.04821, acceleration = 14.08185, rollRate = 73.90607, pitchRate = 69.0374, deceleration = 11.98672, yawRate = 71.16778,},
	shield_0 = { name = "shd_prototype", hitpoints = 197.9996, armor = 99.92703, regen = 1.924725, front = 295.8247, back = 296.5784,},
	armor_0 = { name = "arm_prototype", hitpoints = 244.184, armor = 238.0205,},
	armor_1 = { name = "arm_prototype", hitpoints = 248.1519, armor = 238.8024,},
	capacitor = { name = "cap_prototype", hitpoints = 192.0426, armor = 95.37726, rechargeRate = 19.95948, energy = 477.9689,},
}

ObjectTemplates:addTemplate(object_ship_player_player_prototype_hutt_light, "object/ship/player/player_prototype_hutt_light.iff")
