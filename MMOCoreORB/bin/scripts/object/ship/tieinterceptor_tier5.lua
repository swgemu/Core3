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


object_ship_tieinterceptor_tier5 = object_ship_shared_tieinterceptor_tier5:new {

	name = "tieinterceptor_tier5",
	slideFactor = 1.64,
	chassisHitpoints = 2457.6,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 3119.745, armor = 3174.086,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 3162.052, armor = 3168.353, speed = 56.32716, pitch = 25.28587, roll = 31.33988, yaw = 20.22029, acceleration = 12.0147, rollRate = 57.96843, pitchRate = 50.36168, deceleration = 9.374903, yawRate = 41.11756,},
	shield_0 = { name = "shd_generic", hitpoints = 3089.766, armor = 3184.87, regen = 19.46097, front = 10308.13, back = 10779.2,},
	armor_0 = { name = "arm_generic", hitpoints = 6759.511, armor = 6696.492,},
	armor_1 = { name = "arm_generic", hitpoints = 6501.665, armor = 6782.427,},
	capacitor = { name = "cap_generic", hitpoints = 3083.857, armor = 3095.533, rechargeRate = 99.69005, energy = 4922.13,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 3047.327, armor = 3051.421, rate = 0.7502038, drain = 0.9677419, maxDamage = 322.9265, shieldEfficiency = 0.5400605, minDamage = 202.5299, ammo = 0, ammo_type = 0, armorEfficiency = 0.5414875,},
}

ObjectTemplates:addTemplate(object_ship_tieinterceptor_tier5, "object/ship/tieinterceptor_tier5.iff")
