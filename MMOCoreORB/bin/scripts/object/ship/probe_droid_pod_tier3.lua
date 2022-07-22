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


object_ship_probe_droid_pod_tier3 = object_ship_shared_probe_droid_pod_tier3:new {

	name = "probe_droid_pod_tier3",
	slideFactor = 1.82,
	chassisHitpoints = 600,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 522.5272, armor = 527.017,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 522.3317, armor = 534.8004, speed = 43.12088, pitch = 24.44327, roll = 29.80186, yaw = 19.37632, acceleration = 10.78134, rollRate = 54.89376, pitchRate = 48.7459, deceleration = 8.786044, yawRate = 40.30113,},
	shield_0 = { name = "shd_generic", hitpoints = 533.8356, armor = 534.3179, regen = 4.565765, front = 2052.905, back = 2144.306,},
	armor_0 = { name = "arm_generic", hitpoints = 1094.742, armor = 1141.447,},
	armor_1 = { name = "arm_generic", hitpoints = 1135.697, armor = 1094.86,},
	capacitor = { name = "cap_generic", hitpoints = 516.4584, armor = 534.5623, rechargeRate = 98.30025, energy = 4774.806,},
}

ObjectTemplates:addTemplate(object_ship_probe_droid_pod_tier3, "object/ship/probe_droid_pod_tier3.iff")
