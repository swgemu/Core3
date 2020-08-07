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


object_ship_escape_pod_tier1 = object_ship_shared_escape_pod_tier1:new {

	name = "escape_pod_tier1",
	slideFactor = 1.99,
	chassisHitpoints = 120,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 72.72079, armor = 74.6375,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 72.50068, armor = 72.66665, speed = 40.3746, pitch = 22.22906, roll = 27.71842, yaw = 17.88419, acceleration = 9.880699, rollRate = 51.28959, pitchRate = 44.94685, deceleration = 8.481543, yawRate = 37.01615,},
	shield_0 = { name = "shd_generic", hitpoints = 72.7999, armor = 72.83786, regen = 1.458847, front = 293.7108, back = 287.0549,},
	armor_0 = { name = "arm_generic", hitpoints = 158.4473, armor = 159.0218,},
	armor_1 = { name = "arm_generic", hitpoints = 159.2785, armor = 153.0147,},
	capacitor = { name = "cap_generic", hitpoints = 74.27911, armor = 71.51224, rechargeRate = 97.69896, energy = 4828.993,},
}

ObjectTemplates:addTemplate(object_ship_escape_pod_tier1, "object/ship/escape_pod_tier1.iff")
