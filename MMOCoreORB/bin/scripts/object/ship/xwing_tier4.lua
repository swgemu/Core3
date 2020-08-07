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


object_ship_xwing_tier4 = object_ship_shared_xwing_tier4:new {

	name = "xwing_tier4",
	slideFactor = 1.82,
	chassisHitpoints = 2112,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 2199.963, armor = 2248.208,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 2208.172, armor = 2212.597, speed = 44.75935, pitch = 24.20215, roll = 30.52634, yaw = 19.05796, acceleration = 10.64928, rollRate = 56.84783, pitchRate = 48.40015, deceleration = 9.399098, yawRate = 40.06662,},
	shield_0 = { name = "shd_generic", hitpoints = 2260.249, armor = 2270.406, regen = 16.0259, front = 8985.227, back = 8771.726,},
	armor_0 = { name = "arm_generic", hitpoints = 4326.296, armor = 4239.774,},
	armor_1 = { name = "arm_generic", hitpoints = 4340.269, armor = 4389.762,},
	capacitor = { name = "cap_generic", hitpoints = 2247.919, armor = 2263.257, rechargeRate = 97.0752, energy = 4789.32,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 2233.444, armor = 2246.856, rate = 0.7515899, drain = 0.9857258, maxDamage = 273.716, shieldEfficiency = 0.5451456, minDamage = 180.0491, ammo = 0, ammo_type = 0, armorEfficiency = 0.5505669,},
}

ObjectTemplates:addTemplate(object_ship_xwing_tier4, "object/ship/xwing_tier4.iff")
