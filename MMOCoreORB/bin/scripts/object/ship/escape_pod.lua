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


object_ship_escape_pod = object_ship_shared_escape_pod:new {

	name = "escape_pod",
	slideFactor = 1.68,
	chassisHitpoints = 400,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 291.2155, armor = 289.6385,},
	engine = { name = "eng_incom_fusialthrust", hitpoints = 96.53973, armor = 98.12772, speed = 43.92602, pitch = 20.52301, roll = 20.56395, yaw = 20.15412, acceleration = 10.00901, rollRate = 49.16325, pitchRate = 48.56995, deceleration = 4.499815, yawRate = 49.2527,},
	shield_0 = { name = "shd_generic", hitpoints = 380.0533, armor = 495.5604, regen = 3.817568, front = 193.2955, back = 197.5195,},
	armor_0 = { name = "arm_generic", hitpoints = 193.1092, armor = 195.9394,},
	armor_1 = { name = "arm_generic", hitpoints = 193.1561, armor = 194.7771,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 34.55256, energy = 124.896,},
	weapon_0 = { name = "wpn_incom_disruptor", hitpoints = 192.9565, armor = 190.0335, rate = 0.331838, drain = 26.31627, maxDamage = 482.4412, shieldEfficiency = 0, minDamage = 469.5264, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_escape_pod, "object/ship/escape_pod.iff")
