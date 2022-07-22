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


object_ship_blacksun_transport_tier2 = object_ship_shared_blacksun_transport_tier2:new {

	name = "blacksun_transport_tier2",
	slideFactor = 1.83,
	chassisHitpoints = 1200,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 861.4613, armor = 864.7921,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 866.457, armor = 857.0409, speed = 41.6526, pitch = 23.12106, roll = 29.44894, yaw = 18.64507, acceleration = 10.05048, rollRate = 53.0173, pitchRate = 45.84038, deceleration = 8.543528, yawRate = 38.63207,},
	shield_0 = { name = "shd_generic", hitpoints = 896.6579, armor = 888.8243, regen = 5.24141, front = 5396.901, back = 5150.473,},
	armor_0 = { name = "arm_generic", hitpoints = 2746.117, armor = 2849.41,},
	armor_1 = { name = "arm_generic", hitpoints = 2827.131, armor = 2786.654,},
	capacitor = { name = "cap_generic", hitpoints = 861.0989, armor = 895.2436, rechargeRate = 99.61873, energy = 4882.786,},
}

ObjectTemplates:addTemplate(object_ship_blacksun_transport_tier2, "object/ship/blacksun_transport_tier2.iff")
