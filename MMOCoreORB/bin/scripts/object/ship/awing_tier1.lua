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


object_ship_awing_tier1 = object_ship_shared_awing_tier1:new {

	name = "awing_tier1",
	slideFactor = 1.62,
	chassisHitpoints = 216,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 134.7577, armor = 132.1757,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 132.9335, armor = 132.1672, speed = 45.20823, pitch = 22.11889, roll = 28.44787, yaw = 18.26192, acceleration = 10.72379, rollRate = 51.97543, pitchRate = 44.64702, deceleration = 8.345466, yawRate = 37.75652,},
	shield_0 = { name = "shd_generic", hitpoints = 130.0415, armor = 132.7427, regen = 2.863892, front = 524.4418, back = 521.3329,},
	armor_0 = { name = "arm_generic", hitpoints = 282.0277, armor = 280.1363,},
	armor_1 = { name = "arm_generic", hitpoints = 285.6106, armor = 276.8599,},
	capacitor = { name = "cap_generic", hitpoints = 133.7259, armor = 132.0617, rechargeRate = 99.04901, energy = 4942.09,},
	weapon_0 = { name = "wpn_awing_blaster", hitpoints = 130.6513, armor = 128.9964, rate = 0.7558241, drain = 0.9729614, maxDamage = 38.44024, shieldEfficiency = 0.5476517, minDamage = 28.88272, ammo = 0, ammo_type = 0, armorEfficiency = 0.5581267,},
}

ObjectTemplates:addTemplate(object_ship_awing_tier1, "object/ship/awing_tier1.iff")
