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


object_ship_probe_droid_pod = object_ship_shared_probe_droid_pod:new {

	name = "probe_droid_pod",
	slideFactor = 1.82,
	chassisHitpoints = 400,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 287.4185, armor = 297.875,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 99.98618, armor = 97.68327, speed = 43.9583, pitch = 13.98659, roll = 13.40921, yaw = 13.9865, acceleration = 10.07095, rollRate = 21.10994, pitchRate = 21.99307, deceleration = 4.300864, yawRate = 21.87938,},
	shield_0 = { name = "shd_generic", hitpoints = 395.0984, armor = 499.6053, regen = 3.924476, front = 196.9313, back = 193.6596,},
	armor_0 = { name = "arm_generic", hitpoints = 386.2583, armor = 382.8448,},
	armor_1 = { name = "arm_generic", hitpoints = 392.9349, armor = 397.0097,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.87373, energy = 121.9278,},
}

ObjectTemplates:addTemplate(object_ship_probe_droid_pod, "object/ship/probe_droid_pod.iff")
