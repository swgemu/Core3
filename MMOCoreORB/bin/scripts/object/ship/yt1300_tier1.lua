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


object_ship_yt1300_tier1 = object_ship_shared_yt1300_tier1:new {

	name = "yt1300_tier1",
	slideFactor = 1.85,
	chassisHitpoints = 480,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 296.446, armor = 298.3253,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 294.0431, armor = 291.7648, speed = 41.53269, pitch = 21.95848, roll = 28.08244, yaw = 18.18629, acceleration = 10.18999, rollRate = 49.57483, pitchRate = 44.3453, deceleration = 8.371966, yawRate = 37.22975,},
	shield_0 = { name = "shd_generic", hitpoints = 285.426, armor = 290.4554, regen = 5.969812, front = 1177.697, back = 1172.797,},
	armor_0 = { name = "arm_generic", hitpoints = 633.325, armor = 613.3694,},
	armor_1 = { name = "arm_generic", hitpoints = 611.7607, armor = 614.1398,},
	capacitor = { name = "cap_generic", hitpoints = 296.1933, armor = 295.9722, rechargeRate = 97.39583, energy = 4756.746,},
	weapon_0 = { name = "wpn_incom_blaster", hitpoints = 290.1503, armor = 295.6969, rate = 0.7608693, drain = 0.9835368, maxDamage = 77.05468, shieldEfficiency = 0.5457537, minDamage = 57.25512, ammo = 0, ammo_type = 0, armorEfficiency = 0.5492563,},
	weapon_1 = { name = "wpn_incom_blaster", hitpoints = 286.234, armor = 294.2984, rate = 0.7626862, drain = 0.9819077, maxDamage = 76.73888, shieldEfficiency = 0.5477169, minDamage = 58.43122, ammo = 0, ammo_type = 0, armorEfficiency = 0.5334676,},
}

ObjectTemplates:addTemplate(object_ship_yt1300_tier1, "object/ship/yt1300_tier1.iff")
