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


object_ship_transport_science_tier1 = object_ship_shared_transport_science_tier1:new {

	name = "transport_science_tier1",
	slideFactor = 1.83,
	chassisHitpoints = 480,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 289.9994, armor = 294.7484,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 296.2821, armor = 287.7006, speed = 41.77113, pitch = 22.96324, roll = 27.96115, yaw = 18.12908, acceleration = 9.820935, rollRate = 50.69027, pitchRate = 46.1183, deceleration = 8.692489, yawRate = 37.59164,},
	shield_0 = { name = "shd_generic", hitpoints = 295.1124, armor = 294.6839, regen = 2.998448, front = 1750.041, back = 1747.865,},
	armor_0 = { name = "arm_generic", hitpoints = 916.1595, armor = 932.8237,},
	armor_1 = { name = "arm_generic", hitpoints = 927.0078, armor = 955.1097,},
	capacitor = { name = "cap_generic", hitpoints = 295.1595, armor = 291.2751, rechargeRate = 97.63782, energy = 4997.405,},
}

ObjectTemplates:addTemplate(object_ship_transport_science_tier1, "object/ship/transport_science_tier1.iff")
