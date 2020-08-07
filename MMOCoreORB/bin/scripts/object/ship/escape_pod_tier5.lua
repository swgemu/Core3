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


object_ship_escape_pod_tier5 = object_ship_shared_escape_pod_tier5:new {

	name = "escape_pod_tier5",
	slideFactor = 1.99,
	chassisHitpoints = 1228.8,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1549.823, armor = 1579.176,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 1550.358, armor = 1568.769, speed = 46.75135, pitch = 25.80879, roll = 30.72774, yaw = 19.58718, acceleration = 11.36373, rollRate = 57.44636, pitchRate = 51.91076, deceleration = 9.648687, yawRate = 41.92791,},
	shield_0 = { name = "shd_generic", hitpoints = 1571.049, armor = 1518.04, regen = 11.01422, front = 6074.366, back = 6231.457,},
	armor_0 = { name = "arm_generic", hitpoints = 3379.133, armor = 3332.569,},
	armor_1 = { name = "arm_generic", hitpoints = 3325.75, armor = 3370.143,},
	capacitor = { name = "cap_generic", hitpoints = 1523.734, armor = 1589.167, rechargeRate = 97.80461, energy = 4796.313,},
}

ObjectTemplates:addTemplate(object_ship_escape_pod_tier5, "object/ship/escape_pod_tier5.iff")
