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


object_ship_player_player_sorosuub_space_yacht = object_ship_player_shared_player_sorosuub_space_yacht:new {

	name = "player_sorosuub_space_yacht",
	slideFactor = 1.76,
	chassisHitpoints = 1512,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 285.402, armor = 291.3666,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 97.83093, armor = 99.44305, speed = 45.67611, pitch = 39.10896, roll = 39.2719, yaw = 20.1447, acceleration = 11.72711, rollRate = 58.29478, pitchRate = 58.64743, deceleration = 15.42485, yawRate = 39.86395,},
	shield_0 = { name = "shd_generic", hitpoints = 397.8397, armor = 489.1867, regen = 4.848504, front = 953.884, back = 941.7534,},
	armor_0 = { name = "arm_generic", hitpoints = 192.2914, armor = 191.1192,},
	armor_1 = { name = "arm_generic", hitpoints = 190.1474, armor = 197.6478,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 31.42095, energy = 490.3307,},
	booster = { name = "bst_generic", hitpoints = 19.26239, armor = 19.92333, energy = 97.1871, acceleration = 19.26703, speed = 14.25545, energyUsage = 9.939795, rechargeRate = 4.928347,},
	lots = 4,
}

ObjectTemplates:addTemplate(object_ship_player_player_sorosuub_space_yacht, "object/ship/player/player_sorosuub_space_yacht.iff")
