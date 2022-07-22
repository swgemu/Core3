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


object_ship_hutt_transport_tier5 = object_ship_shared_hutt_transport_tier5:new {

	name = "hutt_transport_tier5",
	slideFactor = 1.83,
	chassisHitpoints = 4915.2,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 6166.193, armor = 6097.097,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 6065.175, armor = 6242.405, speed = 46.59774, pitch = 25.35111, roll = 30.92851, yaw = 20.30697, acceleration = 11.20307, rollRate = 56.06475, pitchRate = 51.61685, deceleration = 9.445853, yawRate = 42.3082,},
	shield_0 = { name = "shd_generic", hitpoints = 6367.522, armor = 6363.888, regen = 22.5079, front = 36693.8, back = 36789.91,},
	armor_0 = { name = "arm_generic", hitpoints = 19988.54, armor = 19884.95,},
	armor_1 = { name = "arm_generic", hitpoints = 19737.24, armor = 19951.7,},
	capacitor = { name = "cap_generic", hitpoints = 6362.257, armor = 6100.617, rechargeRate = 99.42552, energy = 4950.867,},
}

ObjectTemplates:addTemplate(object_ship_hutt_transport_tier5, "object/ship/hutt_transport_tier5.iff")
