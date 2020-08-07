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


object_ship_hutt_transport_tier3 = object_ship_shared_hutt_transport_tier3:new {

	name = "hutt_transport_tier3",
	slideFactor = 1.83,
	chassisHitpoints = 2400,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 2056.295, armor = 2087.499,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 2091.004, armor = 2137.973, speed = 42.8317, pitch = 24.44358, roll = 29.68565, yaw = 18.73377, acceleration = 10.56898, rollRate = 53.60954, pitchRate = 46.89055, deceleration = 9.120584, yawRate = 38.89243,},
	shield_0 = { name = "shd_generic", hitpoints = 2103.241, armor = 2076.638, regen = 8.906879, front = 12478.71, back = 12906.38,},
	armor_0 = { name = "arm_generic", hitpoints = 6763.376, armor = 6636.556,},
	armor_1 = { name = "arm_generic", hitpoints = 6836.218, armor = 6776.762,},
	capacitor = { name = "cap_generic", hitpoints = 2075.366, armor = 2074.034, rechargeRate = 96.88681, energy = 4997.031,},
}

ObjectTemplates:addTemplate(object_ship_hutt_transport_tier3, "object/ship/hutt_transport_tier3.iff")
