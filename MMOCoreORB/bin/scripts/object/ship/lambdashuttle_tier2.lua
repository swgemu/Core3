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


object_ship_lambdashuttle_tier2 = object_ship_shared_lambdashuttle_tier2:new {

	name = "lambdashuttle_tier2",
	slideFactor = 1.74,
	chassisHitpoints = 1800,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 865.1782, armor = 874.7692,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 880.2438, armor = 866.7061, speed = 41.24768, pitch = 23.59143, roll = 29.10194, yaw = 18.45751, acceleration = 10.43309, rollRate = 52.43796, pitchRate = 45.83737, deceleration = 8.644974, yawRate = 37.62566,},
	shield_0 = { name = "shd_generic", hitpoints = 891.1452, armor = 892.6784, regen = 10.5634, front = 7006.907, back = 6923.892,},
	armor_0 = { name = "arm_generic", hitpoints = 2879.258, armor = 2792.871,},
	armor_1 = { name = "arm_generic", hitpoints = 2843.907, armor = 2787.673,},
	capacitor = { name = "cap_generic", hitpoints = 899.7395, armor = 886.7674, rechargeRate = 97.7238, energy = 4944.763,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 890.0768, armor = 890.7482, rate = 0.7623727, drain = 0.9780203, maxDamage = 147.6867, shieldEfficiency = 0.555397, minDamage = 108.8814, ammo = 0, ammo_type = 0, armorEfficiency = 0.5341991,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 855.5171, armor = 860.9503, rate = 0.7561293, drain = 0.9970815, maxDamage = 149.7757, shieldEfficiency = 0.5448588, minDamage = 110.0711, ammo = 0, ammo_type = 0, armorEfficiency = 0.5459593,},
}

ObjectTemplates:addTemplate(object_ship_lambdashuttle_tier2, "object/ship/lambdashuttle_tier2.iff")
