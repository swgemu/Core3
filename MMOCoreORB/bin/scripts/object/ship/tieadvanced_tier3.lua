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


object_ship_tieadvanced_tier3 = object_ship_shared_tieadvanced_tier3:new {

	name = "tieadvanced_tier3",
	slideFactor = 1.76,
	chassisHitpoints = 1440,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1282.249, armor = 1256.177,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 1245.583, armor = 1265.61, speed = 44.37777, pitch = 23.32588, roll = 29.06681, yaw = 18.8111, acceleration = 10.44071, rollRate = 53.01935, pitchRate = 47.86562, deceleration = 9.088488, yawRate = 39.3404,},
	shield_0 = { name = "shd_generic", hitpoints = 1234.764, armor = 1249.142, regen = 10.85143, front = 5102.762, back = 5027.613,},
	armor_0 = { name = "arm_generic", hitpoints = 2726.712, armor = 2674.76,},
	armor_1 = { name = "arm_generic", hitpoints = 2635.573, armor = 2728.102,},
	capacitor = { name = "cap_generic", hitpoints = 1247.164, armor = 1265.883, rechargeRate = 95.36397, energy = 4915.364,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 1260.331, armor = 1279.49, rate = 0.7717382, drain = 0.9803177, maxDamage = 192.7638, shieldEfficiency = 0.5559489, minDamage = 126.7316, ammo = 0, ammo_type = 0, armorEfficiency = 0.541214,},
}

ObjectTemplates:addTemplate(object_ship_tieadvanced_tier3, "object/ship/tieadvanced_tier3.iff")
