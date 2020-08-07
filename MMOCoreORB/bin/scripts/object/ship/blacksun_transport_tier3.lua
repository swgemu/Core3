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


object_ship_blacksun_transport_tier3 = object_ship_shared_blacksun_transport_tier3:new {

	name = "blacksun_transport_tier3",
	slideFactor = 1.83,
	chassisHitpoints = 2400,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 2139.659, armor = 2104.075,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 2153.696, armor = 2152.475, speed = 44.53595, pitch = 23.59706, roll = 29.62826, yaw = 19.15487, acceleration = 10.57976, rollRate = 54.17632, pitchRate = 48.11368, deceleration = 9.053322, yawRate = 40.1973,},
	shield_0 = { name = "shd_generic", hitpoints = 2102.117, armor = 2073.401, regen = 9.15235, front = 12574.85, back = 12626.26,},
	armor_0 = { name = "arm_generic", hitpoints = 6617.856, armor = 6704.801,},
	armor_1 = { name = "arm_generic", hitpoints = 6785.054, armor = 6716.358,},
	capacitor = { name = "cap_generic", hitpoints = 2126.65, armor = 2062.331, rechargeRate = 97.55612, energy = 4938.59,},
}

ObjectTemplates:addTemplate(object_ship_blacksun_transport_tier3, "object/ship/blacksun_transport_tier3.iff")
