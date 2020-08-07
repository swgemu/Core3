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


object_ship_tiefighter_tier4 = object_ship_shared_tiefighter_tier4:new {

	name = "tiefighter_tier4",
	slideFactor = 1.85,
	chassisHitpoints = 2880,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 2039.228, armor = 1987.626,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 1988.873, armor = 2013.737, speed = 45.87234, pitch = 24.36535, roll = 29.88449, yaw = 19.39411, acceleration = 10.94116, rollRate = 56.57346, pitchRate = 49.51484, deceleration = 9.055758, yawRate = 41.44237,},
	shield_0 = { name = "shd_generic", hitpoints = 2052.427, armor = 2053.93, regen = 0, front = 0, back = 0,},
	armor_0 = { name = "arm_generic", hitpoints = 6358.818, armor = 6614.07,},
	armor_1 = { name = "arm_generic", hitpoints = 6434.78, armor = 6628.262,},
	capacitor = { name = "cap_generic", hitpoints = 2005.163, armor = 1979.602, rechargeRate = 95.49085, energy = 4876.987,},
	weapon_0 = { name = "wpn_generic", hitpoints = 2067.456, armor = 2067.448, rate = 0.7678688, drain = 0.9530629, maxDamage = 251.1898, shieldEfficiency = 0.5387219, minDamage = 161.1168, ammo = 0, ammo_type = 0, armorEfficiency = 0.553942,},
}

ObjectTemplates:addTemplate(object_ship_tiefighter_tier4, "object/ship/tiefighter_tier4.iff")
