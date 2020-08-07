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


object_ship_probe_droid_pod_tier4 = object_ship_shared_probe_droid_pod_tier4:new {

	name = "probe_droid_pod_tier4",
	slideFactor = 1.82,
	chassisHitpoints = 960,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 990.6934, armor = 1027.454,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 1033.523, armor = 1016.38, speed = 44.96768, pitch = 24.05437, roll = 30.02574, yaw = 19.07097, acceleration = 10.6453, rollRate = 54.97847, pitchRate = 48.0158, deceleration = 9.448467, yawRate = 41.51037,},
	shield_0 = { name = "shd_generic", hitpoints = 999.6947, armor = 990.5638, regen = 7.140603, front = 4103.88, back = 4102.205,},
	armor_0 = { name = "arm_generic", hitpoints = 2135.137, armor = 2127.492,},
	armor_1 = { name = "arm_generic", hitpoints = 2140.658, armor = 2136.533,},
	capacitor = { name = "cap_generic", hitpoints = 1001.799, armor = 1004.314, rechargeRate = 99.10792, energy = 4931.931,},
}

ObjectTemplates:addTemplate(object_ship_probe_droid_pod_tier4, "object/ship/probe_droid_pod_tier4.iff")
