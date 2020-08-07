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


object_ship_freighterlight = object_ship_shared_freighterlight:new {

	name = "freighterlight",
	slideFactor = 2,
	chassisHitpoints = 300,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 95.67672, armor = 98.67852,},
	engine = { name = "eng_generic", hitpoints = 99.92226, armor = 98.52696, speed = 19.52843, pitch = 18.75626, roll = 18.3391, yaw = 18.61446, acceleration = 33.48952, rollRate = 23.65349, pitchRate = 23.83459, deceleration = 29.76271, yawRate = 23.11585,},
	shield_0 = { name = "shd_generic", hitpoints = 199.0001, armor = 194.5894, regen = 4.832321, front = 289.9491, back = 579.186,},
	armor_0 = { name = "arm_generic", hitpoints = 481.9307, armor = 483.9367,},
	armor_1 = { name = "arm_generic", hitpoints = 499.1988, armor = 484.5253,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 17.10498, energy = 414.4222,},
	weapon_0 = { name = "wpn_generic", hitpoints = 197.9496, armor = 198.8005, rate = 0.1698542, drain = 8.066095, maxDamage = 466.3789, shieldEfficiency = 0, minDamage = 237.6042, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_freighterlight, "object/ship/freighterlight.iff")
