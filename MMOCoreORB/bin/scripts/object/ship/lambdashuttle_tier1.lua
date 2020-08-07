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


object_ship_lambdashuttle_tier1 = object_ship_shared_lambdashuttle_tier1:new {

	name = "lambdashuttle_tier1",
	slideFactor = 1.74,
	chassisHitpoints = 720,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 285.68, armor = 298.2676,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 299.283, armor = 294.5394, speed = 41.129, pitch = 22.95603, roll = 28.41883, yaw = 17.40605, acceleration = 9.725169, rollRate = 51.35963, pitchRate = 43.9866, deceleration = 8.272143, yawRate = 37.72004,},
	shield_0 = { name = "shd_generic", hitpoints = 288.5633, armor = 293.6299, regen = 5.807582, front = 2343.125, back = 2308.976,},
	armor_0 = { name = "arm_generic", hitpoints = 916.5677, armor = 929.7176,},
	armor_1 = { name = "arm_generic", hitpoints = 947.576, armor = 950.4449,},
	capacitor = { name = "cap_generic", hitpoints = 290.0761, armor = 294.623, rechargeRate = 96.15826, energy = 4800.622,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 290.3717, armor = 296.8124, rate = 0.756663, drain = 0.9979237, maxDamage = 68.29969, shieldEfficiency = 0.5354194, minDamage = 50.03736, ammo = 0, ammo_type = 0, armorEfficiency = 0.5455383,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 290.5693, armor = 288.9181, rate = 0.7442187, drain = 0.9548433, maxDamage = 69.43947, shieldEfficiency = 0.5410325, minDamage = 49.97415, ammo = 0, ammo_type = 0, armorEfficiency = 0.5531934,},
}

ObjectTemplates:addTemplate(object_ship_lambdashuttle_tier1, "object/ship/lambdashuttle_tier1.iff")
