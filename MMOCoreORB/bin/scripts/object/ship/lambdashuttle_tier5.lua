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


object_ship_lambdashuttle_tier5 = object_ship_shared_lambdashuttle_tier5:new {

	name = "lambdashuttle_tier5",
	slideFactor = 1.74,
	chassisHitpoints = 7372.8,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 6242.222, armor = 6080.36,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 6338.355, armor = 6321.384, speed = 45.6378, pitch = 24.85113, roll = 31.11807, yaw = 19.65078, acceleration = 11.09192, rollRate = 57.16019, pitchRate = 51.65817, deceleration = 9.674726, yawRate = 41.32491,},
	shield_0 = { name = "shd_generic", hitpoints = 6163.518, armor = 6360.452, regen = 46.2219, front = 50637.91, back = 49067.53,},
	armor_0 = { name = "arm_generic", hitpoints = 20352.64, armor = 19997.74,},
	armor_1 = { name = "arm_generic", hitpoints = 19665.71, armor = 19462.2,},
	capacitor = { name = "cap_generic", hitpoints = 6099.874, armor = 6243.958, rechargeRate = 96.82302, energy = 4917.168,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 6342.269, armor = 6171.396, rate = 0.7679115, drain = 0.9738122, maxDamage = 565.7877, shieldEfficiency = 0.5583234, minDamage = 344.7492, ammo = 0, ammo_type = 0, armorEfficiency = 0.5504801,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 6275.421, armor = 6355.725, rate = 0.7575498, drain = 0.956001, maxDamage = 557.3997, shieldEfficiency = 0.5430528, minDamage = 344.4149, ammo = 0, ammo_type = 0, armorEfficiency = 0.5438778,},
}

ObjectTemplates:addTemplate(object_ship_lambdashuttle_tier5, "object/ship/lambdashuttle_tier5.iff")
