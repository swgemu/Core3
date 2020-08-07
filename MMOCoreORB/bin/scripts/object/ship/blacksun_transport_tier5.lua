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


object_ship_blacksun_transport_tier5 = object_ship_shared_blacksun_transport_tier5:new {

	name = "blacksun_transport_tier5",
	slideFactor = 1.83,
	chassisHitpoints = 4915.2,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 6056.049, armor = 6055.759,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 6278.898, armor = 6182.442, speed = 46.25061, pitch = 25.24295, roll = 31.16173, yaw = 20.50418, acceleration = 10.94334, rollRate = 56.90259, pitchRate = 50.54977, deceleration = 9.480227, yawRate = 42.14759,},
	shield_0 = { name = "shd_generic", hitpoints = 6279.458, armor = 6355.366, regen = 22.77335, front = 37247.15, back = 37735.27,},
	armor_0 = { name = "arm_generic", hitpoints = 20328.66, armor = 19474.75,},
	armor_1 = { name = "arm_generic", hitpoints = 19472.76, armor = 19592.8,},
	capacitor = { name = "cap_generic", hitpoints = 6267.797, armor = 6245.303, rechargeRate = 96.19553, energy = 4918.252,},
}

ObjectTemplates:addTemplate(object_ship_blacksun_transport_tier5, "object/ship/blacksun_transport_tier5.iff")
