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


object_ship_blacksun_transport_tier4 = object_ship_shared_blacksun_transport_tier4:new {

	name = "blacksun_transport_tier4",
	slideFactor = 1.83,
	chassisHitpoints = 3840,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 4077.187, armor = 4003.469,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 3997.969, armor = 4049.178, speed = 43.83539, pitch = 24.60927, roll = 30.98376, yaw = 19.28909, acceleration = 10.68451, rollRate = 54.54457, pitchRate = 48.32886, deceleration = 9.4805, yawRate = 41.41905,},
	shield_0 = { name = "shd_generic", hitpoints = 4010.646, armor = 4137.488, regen = 14.46415, front = 24666.72, back = 24417,},
	armor_0 = { name = "arm_generic", hitpoints = 13262.93, armor = 12983.71,},
	armor_1 = { name = "arm_generic", hitpoints = 12755.81, armor = 13179.35,},
	capacitor = { name = "cap_generic", hitpoints = 4059.065, armor = 4027.166, rechargeRate = 99.8033, energy = 4994.764,},
}

ObjectTemplates:addTemplate(object_ship_blacksun_transport_tier4, "object/ship/blacksun_transport_tier4.iff")
