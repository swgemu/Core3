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


object_ship_tiefighter_tier3 = object_ship_shared_tiefighter_tier3:new {

	name = "tiefighter_tier3",
	slideFactor = 1.85,
	chassisHitpoints = 1800,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1061.419, armor = 1066.421,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 1069.123, armor = 1066.801, speed = 44.48717, pitch = 23.80115, roll = 29.21223, yaw = 19.402, acceleration = 10.59842, rollRate = 53.31084, pitchRate = 47.72027, deceleration = 8.914718, yawRate = 39.82682,},
	shield_0 = { name = "shd_generic", hitpoints = 1069.792, armor = 1067.804, regen = 0, front = 0, back = 0,},
	armor_0 = { name = "arm_generic", hitpoints = 3401.784, armor = 3422.352,},
	armor_1 = { name = "arm_generic", hitpoints = 3336.51, armor = 3304.861,},
	capacitor = { name = "cap_generic", hitpoints = 1072.02, armor = 1038.599, rechargeRate = 96.27643, energy = 4790.24,},
	weapon_0 = { name = "wpn_generic", hitpoints = 1056.958, armor = 1041.597, rate = 0.7525648, drain = 0.9913671, maxDamage = 161.6269, shieldEfficiency = 0.5410321, minDamage = 106.3811, ammo = 0, ammo_type = 0, armorEfficiency = 0.5464742,},
}

ObjectTemplates:addTemplate(object_ship_tiefighter_tier3, "object/ship/tiefighter_tier3.iff")
