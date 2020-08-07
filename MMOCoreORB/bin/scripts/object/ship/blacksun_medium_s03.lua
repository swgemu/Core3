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


object_ship_blacksun_medium_s03 = object_ship_shared_blacksun_medium_s03:new {

	name = "blacksun_medium_s03",
	slideFactor = 1.81,
	chassisHitpoints = 519,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 292.4194, armor = 288.075,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 97.02459, armor = 97.30877, speed = 54.15833, pitch = 33.45908, roll = 33.53534, yaw = 32.57337, acceleration = 15.96529, rollRate = 58.43188, pitchRate = 58.70506, deceleration = 8.352623, yawRate = 60.07788,},
	shield_0 = { name = "shd_generic", hitpoints = 387.5611, armor = 498.3128, regen = 4.785199, front = 295.9114, back = 496.1997,},
	armor_0 = { name = "arm_generic", hitpoints = 290.726, armor = 297.8397,},
	armor_1 = { name = "arm_generic", hitpoints = 292.3528, armor = 293.1425,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 35.23045, energy = 557.8842,},
	booster = { name = "bst_xwing_booster_s01", hitpoints = 19.44332, armor = 19.94311, energy = 0, acceleration = 0, speed = 0, energyUsage = 0, rechargeRate = 0,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 197.1894, armor = 191.8649, rate = 0.3329031, drain = 23.38749, maxDamage = 238.2907, shieldEfficiency = 0, minDamage = 114.9146, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_incom_disruptor", hitpoints = 190.765, armor = 197.0769, rate = 0.3311194, drain = 23.50818, maxDamage = 240.3175, shieldEfficiency = 0, minDamage = 115.5309, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_blacksun_medium_s03, "object/ship/blacksun_medium_s03.iff")
