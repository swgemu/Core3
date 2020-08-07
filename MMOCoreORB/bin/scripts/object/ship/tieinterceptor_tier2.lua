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


object_ship_tieinterceptor_tier2 = object_ship_shared_tieinterceptor_tier2:new {

	name = "tieinterceptor_tier2",
	slideFactor = 1.64,
	chassisHitpoints = 600,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 434.3831, armor = 438.5086,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 430.923, armor = 447.5631, speed = 51.18006, pitch = 23.13741, roll = 29.44715, yaw = 17.9482, acceleration = 11.17562, rollRate = 52.13704, pitchRate = 45.866, deceleration = 8.526236, yawRate = 39.17719,},
	shield_0 = { name = "shd_generic", hitpoints = 445.0368, armor = 440.493, regen = 4.435182, front = 1489.781, back = 1528.29,},
	armor_0 = { name = "arm_generic", hitpoints = 918.5671, armor = 932.8228,},
	armor_1 = { name = "arm_generic", hitpoints = 912.8196, armor = 958.9889,},
	capacitor = { name = "cap_generic", hitpoints = 449.4486, armor = 430.2035, rechargeRate = 99.38507, energy = 4859.149,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 449.7253, armor = 444.8842, rate = 0.7660376, drain = 0.9951435, maxDamage = 87.76165, shieldEfficiency = 0.5479486, minDamage = 61.50211, ammo = 0, ammo_type = 0, armorEfficiency = 0.5362571,},
}

ObjectTemplates:addTemplate(object_ship_tieinterceptor_tier2, "object/ship/tieinterceptor_tier2.iff")
