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


object_ship_droid_fighter_tier2 = object_ship_shared_droid_fighter_tier2:new {

	name = "droid_fighter_tier2",
	slideFactor = 1.92,
	chassisHitpoints = 600,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 431.221, armor = 439.3733,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 429.2235, armor = 436.9449, speed = 41.3972, pitch = 23.02021, roll = 28.12778, yaw = 18.20978, acceleration = 10.31623, rollRate = 51.85535, pitchRate = 45.80882, deceleration = 8.799036, yawRate = 38.40439,},
	shield_0 = { name = "shd_generic", hitpoints = 432.592, armor = 441.5667, regen = 5.188566, front = 1758.514, back = 1782.378,},
	armor_0 = { name = "arm_generic", hitpoints = 941.3755, armor = 946.6426,},
	armor_1 = { name = "arm_generic", hitpoints = 957.9215, armor = 922.8886,},
	capacitor = { name = "cap_generic", hitpoints = 441.0456, armor = 433.1365, rechargeRate = 97.29788, energy = 4838.289,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 429.762, armor = 443.0133, rate = 0.7442936, drain = 0.9689115, maxDamage = 83.89684, shieldEfficiency = 0.555871, minDamage = 62.6857, ammo = 0, ammo_type = 0, armorEfficiency = 0.5465298,},
}

ObjectTemplates:addTemplate(object_ship_droid_fighter_tier2, "object/ship/droid_fighter_tier2.iff")
