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


object_ship_rebel_gunboat_tier2 = object_ship_shared_rebel_gunboat_tier2:new {

	name = "rebel_gunboat_tier2",
	slideFactor = 1.76,
	chassisHitpoints = 6000,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 4306.434, armor = 4290.42,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 4466.283, armor = 4363.873, speed = 42.36829, pitch = 22.99141, roll = 28.72104, yaw = 18.04197, acceleration = 10.09636, rollRate = 52.3083, pitchRate = 46.13125, deceleration = 8.717518, yawRate = 39.42461,},
	shield_0 = { name = "shd_generic", hitpoints = 4410.493, armor = 4281.361, regen = 7.93043, front = 17225.58, back = 17250.61,},
	armor_0 = { name = "arm_generic", hitpoints = 9137.128, armor = 9473.155,},
	armor_1 = { name = "arm_generic", hitpoints = 9405.384, armor = 9409.022,},
	capacitor = { name = "cap_generic", hitpoints = 4496.785, armor = 4468.329, rechargeRate = 96.69292, energy = 4806.693,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 4405.325, armor = 4491.803, rate = 0.769633, drain = 0.9677165, maxDamage = 214.3226, shieldEfficiency = 0.5468827, minDamage = 151.4535, ammo = 0, ammo_type = 0, armorEfficiency = 0.5421988,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 4467.263, armor = 4405.085, rate = 0.7431962, drain = 0.9730938, maxDamage = 209.0087, shieldEfficiency = 0.5417797, minDamage = 155.5438, ammo = 0, ammo_type = 0, armorEfficiency = 0.5388024,},
	weapon_2 = { name = "wpn_incom_disruptor", hitpoints = 4304.33, armor = 4477.133, rate = 0.7756609, drain = 0.9542989, maxDamage = 212.2054, shieldEfficiency = 0.5491979, minDamage = 149.7348, ammo = 0, ammo_type = 0, armorEfficiency = 0.5332336,},
	weapon_3 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 4374.007, armor = 4409.571, rate = 2.871089, drain = 0.9961456, maxDamage = 643.3702, shieldEfficiency = 0.7278856, minDamage = 305.3642, ammo = 5, ammo_type = 17, armorEfficiency = 0.7362959,},
}

ObjectTemplates:addTemplate(object_ship_rebel_gunboat_tier2, "object/ship/rebel_gunboat_tier2.iff")
