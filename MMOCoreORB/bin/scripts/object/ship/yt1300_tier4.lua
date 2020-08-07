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


object_ship_yt1300_tier4 = object_ship_shared_yt1300_tier4:new {

	name = "yt1300_tier4",
	slideFactor = 1.85,
	chassisHitpoints = 3840,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 3989.147, armor = 4026.441,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 3984.196, armor = 3969.03, speed = 45.63525, pitch = 25.02934, roll = 30.07253, yaw = 19.01323, acceleration = 11.13537, rollRate = 55.74306, pitchRate = 49.24485, deceleration = 9.066781, yawRate = 40.61832,},
	shield_0 = { name = "shd_generic", hitpoints = 4107.593, armor = 4096.962, regen = 29.7376, front = 15817.89, back = 15834.17,},
	armor_0 = { name = "arm_generic", hitpoints = 8799.818, armor = 8730.294,},
	armor_1 = { name = "arm_generic", hitpoints = 8528.398, armor = 8672.861,},
	capacitor = { name = "cap_generic", hitpoints = 3982.08, armor = 4070.784, rechargeRate = 97.97833, energy = 4827.833,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 4014.828, armor = 4133.497, rate = 0.7545694, drain = 0.9852818, maxDamage = 484.9327, shieldEfficiency = 0.5340691, minDamage = 323.2264, ammo = 0, ammo_type = 0, armorEfficiency = 0.5595741,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 4011.703, armor = 4074.778, rate = 0.7412745, drain = 0.9659067, maxDamage = 501.2326, shieldEfficiency = 0.5329059, minDamage = 327.5488, ammo = 0, ammo_type = 0, armorEfficiency = 0.5533201,},
}

ObjectTemplates:addTemplate(object_ship_yt1300_tier4, "object/ship/yt1300_tier4.iff")
