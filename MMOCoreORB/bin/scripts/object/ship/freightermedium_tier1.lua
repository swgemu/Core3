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


object_ship_freightermedium_tier1 = object_ship_shared_freightermedium_tier1:new {

	name = "freightermedium_tier1",
	slideFactor = 1.87,
	chassisHitpoints = 480,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 289.1444, armor = 294.7455,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 293.2422, armor = 286.134, speed = 41.19086, pitch = 23.02533, roll = 27.36238, yaw = 17.97859, acceleration = 9.792842, rollRate = 49.59842, pitchRate = 44.73364, deceleration = 8.339143, yawRate = 36.98573,},
	shield_0 = { name = "shd_generic", hitpoints = 288.3432, armor = 299.8867, regen = 3.610263, front = 2286.391, back = 2300.543,},
	armor_0 = { name = "arm_generic", hitpoints = 1239.206, armor = 1230.608,},
	armor_1 = { name = "arm_generic", hitpoints = 1232.675, armor = 1223.599,},
	capacitor = { name = "cap_generic", hitpoints = 293.5763, armor = 291.1443, rechargeRate = 99.43906, energy = 4875.422,},
}

ObjectTemplates:addTemplate(object_ship_freightermedium_tier1, "object/ship/freightermedium_tier1.iff")
