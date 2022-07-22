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


object_ship_transport_science_tier2 = object_ship_shared_transport_science_tier2:new {

	name = "transport_science_tier2",
	slideFactor = 1.83,
	chassisHitpoints = 1200,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 891.2219, armor = 876.3356,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 881.9156, armor = 886.8528, speed = 42.50351, pitch = 23.51701, roll = 29.14128, yaw = 18.70569, acceleration = 10.46079, rollRate = 52.04927, pitchRate = 47.20134, deceleration = 8.959543, yawRate = 38.71436,},
	shield_0 = { name = "shd_generic", hitpoints = 897.2228, armor = 889.6105, regen = 5.245762, front = 5300.898, back = 5157.654,},
	armor_0 = { name = "arm_generic", hitpoints = 2877.409, armor = 2822.861,},
	armor_1 = { name = "arm_generic", hitpoints = 2740.144, armor = 2837.776,},
	capacitor = { name = "cap_generic", hitpoints = 893.1899, armor = 878.6575, rechargeRate = 99.25458, energy = 4955.924,},
}

ObjectTemplates:addTemplate(object_ship_transport_science_tier2, "object/ship/transport_science_tier2.iff")
