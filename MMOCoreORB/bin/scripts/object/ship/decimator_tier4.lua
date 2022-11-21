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


object_ship_decimator_tier4 = object_ship_shared_decimator_tier4:new {

	name = "decimator_tier4",
	slideFactor = 1.69,
	chassisHitpoints = 3840,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 4133.846, armor = 4071.184,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 4087.938, armor = 4087.857, speed = 43.86506, pitch = 24.14179, roll = 30.21412, yaw = 19.47014, acceleration = 10.85219, rollRate = 55.65141, pitchRate = 48.66443, deceleration = 9.440614, yawRate = 41.11155,},
	shield_0 = { name = "shd_generic", hitpoints = 4077.5, armor = 4083, regen = 28.69526, front = 16084.86, back = 16352.37,},
	armor_0 = { name = "arm_generic", hitpoints = 8755.789, armor = 8816.638,},
	armor_1 = { name = "arm_generic", hitpoints = 8732.088, armor = 8599.035,},
	capacitor = { name = "cap_generic", hitpoints = 4003.84, armor = 4008.555, rechargeRate = 97.30539, energy = 4885.025,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 4008.745, armor = 4124.237, rate = 0.7729059, drain = 0.9900922, maxDamage = 499.4511, shieldEfficiency = 0.5590654, minDamage = 322.3109, ammo = 0, ammo_type = 0, armorEfficiency = 0.5597746,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 4092.205, armor = 4053.89, rate = 0.7792626, drain = 0.9613841, maxDamage = 488.6958, shieldEfficiency = 0.544072, minDamage = 323.6175, ammo = 0, ammo_type = 0, armorEfficiency = 0.537578,},
	weapon_2 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 3982.22, armor = 4144.263, rate = 2.995004, drain = 0.9598106, maxDamage = 1442.886, shieldEfficiency = 0.7272822, minDamage = 649.3703, ammo = 4, ammo_type = 19, armorEfficiency = 0.7195514,},
}

ObjectTemplates:addTemplate(object_ship_decimator_tier4, "object/ship/decimator_tier4.iff")
