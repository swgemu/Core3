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


object_ship_tieoppressor_tier1 = object_ship_shared_tieoppressor_tier1:new {

	name = "tieoppressor_tier1",
	slideFactor = 1.72,
	chassisHitpoints = 264,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 158.1606, armor = 162.6208,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 164.7506, armor = 163.7923, speed = 41.05244, pitch = 22.93466, roll = 28.01721, yaw = 17.85357, acceleration = 9.85999, rollRate = 50.44875, pitchRate = 44.04512, deceleration = 8.276219, yawRate = 38.21503,},
	shield_0 = { name = "shd_generic", hitpoints = 160.4735, armor = 160.7757, regen = 3.139486, front = 635.726, back = 632.215,},
	armor_0 = { name = "arm_generic", hitpoints = 350.9394, armor = 336.9355,},
	armor_1 = { name = "arm_generic", hitpoints = 338.0472, armor = 350.6096,},
	capacitor = { name = "cap_generic", hitpoints = 159.1802, armor = 163.602, rechargeRate = 98.72665, energy = 4971.883,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 162.9331, armor = 159.8081, rate = 0.7786933, drain = 0.992723, maxDamage = 38.31608, shieldEfficiency = 0.537851, minDamage = 29.88497, ammo = 0, ammo_type = 0, armorEfficiency = 0.5330193,},
	weapon_1 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 163.6245, armor = 163.4754, rate = 2.995929, drain = 0.9920316, maxDamage = 115.1967, shieldEfficiency = 0.7156369, minDamage = 58.46639, ammo = 4, ammo_type = 16, armorEfficiency = 0.7472502,},
}

ObjectTemplates:addTemplate(object_ship_tieoppressor_tier1, "object/ship/tieoppressor_tier1.iff")
