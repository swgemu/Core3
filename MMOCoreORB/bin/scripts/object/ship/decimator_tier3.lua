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


object_ship_decimator_tier3 = object_ship_shared_decimator_tier3:new {

	name = "decimator_tier3",
	slideFactor = 1.69,
	chassisHitpoints = 2400,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 2088.764, armor = 2074.431,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 2127.908, armor = 2148.744, speed = 42.93281, pitch = 23.65319, roll = 29.25696, yaw = 18.92082, acceleration = 10.39667, rollRate = 54.92654, pitchRate = 47.59444, deceleration = 9.046643, yawRate = 39.51192,},
	shield_0 = { name = "shd_generic", hitpoints = 2067.196, armor = 2143.976, regen = 17.76028, front = 8336.578, back = 8363.718,},
	armor_0 = { name = "arm_generic", hitpoints = 4545.104, armor = 4582.132,},
	armor_1 = { name = "arm_generic", hitpoints = 4603.848, armor = 4405.83,},
	capacitor = { name = "cap_generic", hitpoints = 2078.018, armor = 2153.423, rechargeRate = 95.13768, energy = 4868.716,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 2137.146, armor = 2102.185, rate = 0.7729844, drain = 0.981162, maxDamage = 313.044, shieldEfficiency = 0.5425357, minDamage = 219.858, ammo = 0, ammo_type = 0, armorEfficiency = 0.5327591,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 2120.348, armor = 2085.103, rate = 0.7586476, drain = 0.9614362, maxDamage = 324.1248, shieldEfficiency = 0.5359842, minDamage = 212.8965, ammo = 0, ammo_type = 0, armorEfficiency = 0.5465763,},
	weapon_2 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 2099.427, armor = 2125.164, rate = 2.980813, drain = 0.9555786, maxDamage = 933.5081, shieldEfficiency = 0.7469188, minDamage = 426.1834, ammo = 4, ammo_type = 18, armorEfficiency = 0.7143607,},
}

ObjectTemplates:addTemplate(object_ship_decimator_tier3, "object/ship/decimator_tier3.iff")
