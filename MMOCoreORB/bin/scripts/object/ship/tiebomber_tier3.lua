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


object_ship_tiebomber_tier3 = object_ship_shared_tiebomber_tier3:new {

	name = "tiebomber_tier3",
	slideFactor = 1.66,
	chassisHitpoints = 1800,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1062.4, armor = 1034.68,},
	engine = { name = "eng_qualdex_kyromaster", hitpoints = 1056.757, armor = 1077.655, speed = 42.44791, pitch = 24.32127, roll = 29.49271, yaw = 19.23521, acceleration = 10.47122, rollRate = 54.65039, pitchRate = 48.38107, deceleration = 9.055164, yawRate = 40.67599,},
	shield_0 = { name = "shd_generic", hitpoints = 1063.775, armor = 1078.713, regen = 6.751621, front = 3135.25, back = 3166.239,},
	armor_0 = { name = "arm_generic", hitpoints = 3409.809, armor = 3338.126,},
	armor_1 = { name = "arm_generic", hitpoints = 3334.148, armor = 3347.107,},
	capacitor = { name = "cap_generic", hitpoints = 1069.451, armor = 1070.939, rechargeRate = 96.84188, energy = 4956.497,},
	weapon_0 = { name = "wpn_generic", hitpoints = 1041.906, armor = 1065.521, rate = 0.7589049, drain = 0.9536713, maxDamage = 156.4514, shieldEfficiency = 0.541214, minDamage = 106.0658, ammo = 0, ammo_type = 0, armorEfficiency = 0.5520463,},
	weapon_1 = { name = "wpn_seinar_concussion_missile_s01", hitpoints = 1069.036, armor = 1057.804, rate = 2.94014, drain = 0.9921105, maxDamage = 463.5673, shieldEfficiency = 0.7157883, minDamage = 211.4987, ammo = 4, ammo_type = 18, armorEfficiency = 0.7423626,},
}

ObjectTemplates:addTemplate(object_ship_tiebomber_tier3, "object/ship/tiebomber_tier3.iff")
