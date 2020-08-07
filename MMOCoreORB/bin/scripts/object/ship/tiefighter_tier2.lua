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


object_ship_tiefighter_tier2 = object_ship_shared_tiefighter_tier2:new {

	name = "tiefighter_tier2",
	slideFactor = 1.85,
	chassisHitpoints = 900,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 429.8788, armor = 448.7209,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 439.4091, armor = 445.7355, speed = 42.25571, pitch = 23.50561, roll = 28.19992, yaw = 18.65842, acceleration = 10.21904, rollRate = 52.19166, pitchRate = 46.76221, deceleration = 8.653589, yawRate = 38.86872,},
	shield_0 = { name = "shd_generic", hitpoints = 448.9271, armor = 439.8431, regen = 0, front = 0, back = 0,},
	armor_0 = { name = "arm_generic", hitpoints = 1421.713, armor = 1391.74,},
	armor_1 = { name = "arm_generic", hitpoints = 1420.758, armor = 1393.852,},
	capacitor = { name = "cap_generic", hitpoints = 442.9701, armor = 446.2894, rechargeRate = 97.93583, energy = 4810.564,},
	weapon_0 = { name = "wpn_generic", hitpoints = 438.7333, armor = 428.4671, rate = 0.7573761, drain = 0.9643904, maxDamage = 83.77296, shieldEfficiency = 0.551166, minDamage = 60.47337, ammo = 0, ammo_type = 0, armorEfficiency = 0.5425867,},
}

ObjectTemplates:addTemplate(object_ship_tiefighter_tier2, "object/ship/tiefighter_tier2.iff")
