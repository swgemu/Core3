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


object_ship_freighterlight_tier5 = object_ship_shared_freighterlight_tier5:new {

	name = "freighterlight_tier5",
	slideFactor = 1.83,
	chassisHitpoints = 4915.2,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 6188.846, armor = 6211.634,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 6366.227, armor = 6239.489, speed = 46.96305, pitch = 25.90539, roll = 32.05947, yaw = 20.35579, acceleration = 11.05263, rollRate = 58.57137, pitchRate = 51.54363, deceleration = 9.516104, yawRate = 41.14437,},
	shield_0 = { name = "shd_generic", hitpoints = 6232.94, armor = 6149.095, regen = 22.50195, front = 37994.14, back = 37006.86,},
	armor_0 = { name = "arm_generic", hitpoints = 19566.24, armor = 20216.45,},
	armor_1 = { name = "arm_generic", hitpoints = 20206.63, armor = 20255.35,},
	capacitor = { name = "cap_generic", hitpoints = 6121.314, armor = 6360.015, rechargeRate = 97.98869, energy = 4956.381,},
}

ObjectTemplates:addTemplate(object_ship_freighterlight_tier5, "object/ship/freighterlight_tier5.iff")
