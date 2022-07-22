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


object_ship_rebel_gunboat_tier1 = object_ship_shared_rebel_gunboat_tier1:new {

	name = "rebel_gunboat_tier1",
	slideFactor = 1.76,
	chassisHitpoints = 2400,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1426.782, armor = 1455.064,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 1429.457, armor = 1484.494, speed = 40.09155, pitch = 22.91716, roll = 27.27288, yaw = 17.70564, acceleration = 10.19484, rollRate = 49.81757, pitchRate = 44.73775, deceleration = 8.306601, yawRate = 37.59917,},
	shield_0 = { name = "shd_generic", hitpoints = 1439.26, armor = 1466.984, regen = 4.325983, front = 5767.283, back = 5823.845,},
	armor_0 = { name = "arm_generic", hitpoints = 3091.174, armor = 3117.003,},
	armor_1 = { name = "arm_generic", hitpoints = 3145.075, armor = 3119.767,},
	capacitor = { name = "cap_generic", hitpoints = 1427.951, armor = 1454.223, rechargeRate = 96.1363, energy = 4917.434,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 1466.33, armor = 1483.811, rate = 0.7438991, drain = 0.9685181, maxDamage = 98.8499, shieldEfficiency = 0.5332946, minDamage = 73.73775, ammo = 0, ammo_type = 0, armorEfficiency = 0.5330976,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 1489.37, armor = 1486.835, rate = 0.7694949, drain = 0.9917549, maxDamage = 97.38596, shieldEfficiency = 0.5366369, minDamage = 73.06252, ammo = 0, ammo_type = 0, armorEfficiency = 0.5404461,},
	weapon_2 = { name = "wpn_incom_disruptor", hitpoints = 1483.641, armor = 1432.994, rate = 0.7550499, drain = 0.9894024, maxDamage = 98.29032, shieldEfficiency = 0.5347142, minDamage = 73.9912, ammo = 0, ammo_type = 0, armorEfficiency = 0.5374154,},
	weapon_3 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 1468.358, armor = 1443.664, rate = 2.93651, drain = 0.9597448, maxDamage = 288.3093, shieldEfficiency = 0.7126774, minDamage = 147.0603, ammo = 5, ammo_type = 16, armorEfficiency = 0.7308846,},
}

ObjectTemplates:addTemplate(object_ship_rebel_gunboat_tier1, "object/ship/rebel_gunboat_tier1.iff")
