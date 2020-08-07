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


object_ship_lambdashuttle_tier3 = object_ship_shared_lambdashuttle_tier3:new {

	name = "lambdashuttle_tier3",
	slideFactor = 1.74,
	chassisHitpoints = 3600,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 2054.966, armor = 2111.472,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 2054.868, armor = 2089.759, speed = 42.38141, pitch = 23.60909, roll = 29.37815, yaw = 18.79306, acceleration = 10.66354, rollRate = 54.07703, pitchRate = 47.77102, deceleration = 8.903277, yawRate = 40.59714,},
	shield_0 = { name = "shd_generic", hitpoints = 2122.186, armor = 2097.433, regen = 18.01411, front = 16667.97, back = 16843.17,},
	armor_0 = { name = "arm_generic", hitpoints = 6644.055, armor = 6723.215,},
	armor_1 = { name = "arm_generic", hitpoints = 6616.647, armor = 6774.833,},
	capacitor = { name = "cap_generic", hitpoints = 2095.551, armor = 2099.49, rechargeRate = 96.75986, energy = 4844.713,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 2116.935, armor = 2078.662, rate = 0.7493284, drain = 0.9563532, maxDamage = 276.0558, shieldEfficiency = 0.5570046, minDamage = 190.2787, ammo = 0, ammo_type = 0, armorEfficiency = 0.5598789,},
	weapon_1 = { name = "wpn_tieadvanced_blaster", hitpoints = 2085.622, armor = 2075.806, rate = 0.7663828, drain = 0.9840569, maxDamage = 279.5765, shieldEfficiency = 0.5435246, minDamage = 193.5923, ammo = 0, ammo_type = 0, armorEfficiency = 0.5490316,},
}

ObjectTemplates:addTemplate(object_ship_lambdashuttle_tier3, "object/ship/lambdashuttle_tier3.iff")
