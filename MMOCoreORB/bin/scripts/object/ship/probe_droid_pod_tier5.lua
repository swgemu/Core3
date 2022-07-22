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


object_ship_probe_droid_pod_tier5 = object_ship_shared_probe_droid_pod_tier5:new {

	name = "probe_droid_pod_tier5",
	slideFactor = 1.82,
	chassisHitpoints = 1228.8,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1572.348, armor = 1528.76,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 1583.38, armor = 1570.313, speed = 46.28887, pitch = 25.98373, roll = 30.59997, yaw = 20.34217, acceleration = 10.95679, rollRate = 56.63328, pitchRate = 51.20269, deceleration = 9.400769, yawRate = 43.0027,},
	shield_0 = { name = "shd_generic", hitpoints = 1589.718, armor = 1561.231, regen = 11.10242, front = 6279.181, back = 6159.011,},
	armor_0 = { name = "arm_generic", hitpoints = 3231.654, armor = 3394.242,},
	armor_1 = { name = "arm_generic", hitpoints = 3315.281, armor = 3231.936,},
	capacitor = { name = "cap_generic", hitpoints = 1577.837, armor = 1582.368, rechargeRate = 99.14593, energy = 4776.936,},
}

ObjectTemplates:addTemplate(object_ship_probe_droid_pod_tier5, "object/ship/probe_droid_pod_tier5.iff")
