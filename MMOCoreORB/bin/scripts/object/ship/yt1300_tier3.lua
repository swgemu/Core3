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


object_ship_yt1300_tier3 = object_ship_shared_yt1300_tier3:new {

	name = "yt1300_tier3",
	slideFactor = 1.85,
	chassisHitpoints = 2400,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 2090.954, armor = 2052.401,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 2091.144, armor = 2115.262, speed = 44.20745, pitch = 24.19577, roll = 30.13369, yaw = 19.29313, acceleration = 10.56992, rollRate = 53.276, pitchRate = 47.90217, deceleration = 9.202867, yawRate = 38.95155,},
	shield_0 = { name = "shd_generic", hitpoints = 2154.436, armor = 2065.636, regen = 18.44824, front = 8258.109, back = 8429.642,},
	armor_0 = { name = "arm_generic", hitpoints = 4392.858, armor = 4388.932,},
	armor_1 = { name = "arm_generic", hitpoints = 4517.886, armor = 4483.257,},
	capacitor = { name = "cap_generic", hitpoints = 2091.26, armor = 2117.334, rechargeRate = 99.03902, energy = 4841.878,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 2136.974, armor = 2122.331, rate = 0.7786305, drain = 0.9904791, maxDamage = 322.8206, shieldEfficiency = 0.5383444, minDamage = 218.1174, ammo = 0, ammo_type = 0, armorEfficiency = 0.5388076,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 2082.176, armor = 2156.647, rate = 0.7514755, drain = 0.9693829, maxDamage = 318.5084, shieldEfficiency = 0.5508767, minDamage = 215.2661, ammo = 0, ammo_type = 0, armorEfficiency = 0.5534758,},
}

ObjectTemplates:addTemplate(object_ship_yt1300_tier3, "object/ship/yt1300_tier3.iff")
