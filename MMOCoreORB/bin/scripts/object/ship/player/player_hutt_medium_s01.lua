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


object_ship_player_player_hutt_medium_s01 = object_ship_player_shared_player_hutt_medium_s01:new {

	name = "player_hutt_medium_s01",
	slideFactor = 1.76,
	chassisHitpoints = 1512,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 297.5141, armor = 294.1929,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 96.71855, armor = 98.71605, speed = 44.01991, pitch = 45.29466, roll = 52.87426, yaw = 27.10827, acceleration = 12.03298, rollRate = 80.12466, pitchRate = 70.31098, deceleration = 15.05467, yawRate = 76.31455,},
	shield_0 = { name = "shd_generic", hitpoints = 389.3865, armor = 499.0418, regen = 4.833342, front = 973.0168, back = 969.4529,},
	armor_0 = { name = "arm_generic", hitpoints = 199.1766, armor = 190.3229,},
	armor_1 = { name = "arm_generic", hitpoints = 196.6376, armor = 197.9128,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 30.7502, energy = 496.1897,},
	booster = { name = "bst_generic", hitpoints = 19.38919, armor = 19.12807, energy = 97.60387, acceleration = 19.84349, speed = 14.61098, energyUsage = 9.713359, rechargeRate = 4.909821,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 194.3624, armor = 197.9378, rate = 0.3292171, drain = 22.89369, maxDamage = 247.2647, shieldEfficiency = 0, minDamage = 118.9161, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_2 = { name = "wpn_std_countermeasure", hitpoints = 245.9457, armor = 246.4686, rate = 0.0992691, drain = 22.60886, maxDamage = 97.27991, shieldEfficiency = 0, minDamage = 23.78209, ammo = 25, ammo_type = 6, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_player_player_hutt_medium_s01, "object/ship/player/player_hutt_medium_s01.iff")
