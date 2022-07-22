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


object_ship_tiefighter_tier1 = object_ship_shared_tiefighter_tier1:new {

	name = "tiefighter_tier1",
	slideFactor = 1.85,
	chassisHitpoints = 360,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 147.7421, armor = 143.1861,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 146.4119, armor = 144.6718, speed = 41.46351, pitch = 22.50168, roll = 28.38925, yaw = 17.46341, acceleration = 9.848171, rollRate = 49.62187, pitchRate = 45.06511, deceleration = 8.492247, yawRate = 36.99653,},
	shield_0 = { name = "shd_generic", hitpoints = 146.6649, armor = 144.4499, regen = 0, front = 0, back = 0,},
	armor_0 = { name = "arm_generic", hitpoints = 466.9262, armor = 468.298,},
	armor_1 = { name = "arm_generic", hitpoints = 460.0915, armor = 462.3284,},
	capacitor = { name = "cap_generic", hitpoints = 147.8517, armor = 149.0095, rechargeRate = 98.93721, energy = 4835.17,},
	weapon_0 = { name = "wpn_generic", hitpoints = 146.541, armor = 147.7992, rate = 0.7452397, drain = 0.9544527, maxDamage = 39.09395, shieldEfficiency = 0.5595694, minDamage = 29.5962, ammo = 0, ammo_type = 0, armorEfficiency = 0.5459821,},
}

ObjectTemplates:addTemplate(object_ship_tiefighter_tier1, "object/ship/tiefighter_tier1.iff")
