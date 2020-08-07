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


object_ship_merchant_cruiser_light_tier2 = object_ship_shared_merchant_cruiser_light_tier2:new {

	name = "merchant_cruiser_light_tier2",
	slideFactor = 1.76,
	chassisHitpoints = 6000,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 4347.321, armor = 4328.156,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 4423.859, armor = 4371.578, speed = 41.44782, pitch = 23.09884, roll = 28.99439, yaw = 18.37297, acceleration = 10.4846, rollRate = 51.97251, pitchRate = 45.76473, deceleration = 8.850859, yawRate = 38.41758,},
	shield_0 = { name = "shd_generic", hitpoints = 4307.012, armor = 4318.098, regen = 7.817811, front = 17394.71, back = 17566.64,},
	armor_0 = { name = "arm_generic", hitpoints = 9365.46, armor = 9452.584,},
	armor_1 = { name = "arm_generic", hitpoints = 9256.517, armor = 9161.956,},
	capacitor = { name = "cap_generic", hitpoints = 4290.778, armor = 4408.794, rechargeRate = 95.03651, energy = 4784.807,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 4442.517, armor = 4300.353, rate = 0.7731364, drain = 0.9581708, maxDamage = 217.4103, shieldEfficiency = 0.5367162, minDamage = 153.7688, ammo = 0, ammo_type = 0, armorEfficiency = 0.5576748,},
}

ObjectTemplates:addTemplate(object_ship_merchant_cruiser_light_tier2, "object/ship/merchant_cruiser_light_tier2.iff")
