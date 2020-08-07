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


object_ship_transport_science_tier3 = object_ship_shared_transport_science_tier3:new {

	name = "transport_science_tier3",
	slideFactor = 1.83,
	chassisHitpoints = 2400,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 2070.576, armor = 2136.226,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 2080.042, armor = 2139.501, speed = 42.39302, pitch = 23.64267, roll = 29.17825, yaw = 18.94036, acceleration = 10.43443, rollRate = 54.91575, pitchRate = 46.61916, deceleration = 9.078002, yawRate = 40.50225,},
	shield_0 = { name = "shd_generic", hitpoints = 2108.359, armor = 2119.863, regen = 9.183777, front = 12912.43, back = 12506.32,},
	armor_0 = { name = "arm_generic", hitpoints = 6791.837, armor = 6670.308,},
	armor_1 = { name = "arm_generic", hitpoints = 6625.29, armor = 6873.353,},
	capacitor = { name = "cap_generic", hitpoints = 2111.69, armor = 2156.3, rechargeRate = 96.73582, energy = 4801.011,},
}

ObjectTemplates:addTemplate(object_ship_transport_science_tier3, "object/ship/transport_science_tier3.iff")
