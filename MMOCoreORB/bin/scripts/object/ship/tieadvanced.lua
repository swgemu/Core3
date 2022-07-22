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


object_ship_tieadvanced = object_ship_shared_tieadvanced:new {

	name = "tieadvanced",
	slideFactor = 1.84,
	chassisHitpoints = 322,
	chassisMass = 10000,
	reactor = { name = "rct_generic", hitpoints = 97.88988, armor = 95.11012,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 95.64938, armor = 99.06286, speed = 51.70359, pitch = 28.09003, roll = 27.92437, yaw = 27.93928, acceleration = 21.35566, rollRate = 51.70591, pitchRate = 53.52766, deceleration = 10.45788, yawRate = 52.58622,},
	shield_0 = { name = "shd_generic", hitpoints = 195.1856, armor = 194.0223, regen = 4.963309, front = 386.2133, back = 675.6202,},
	armor_0 = { name = "arm_generic", hitpoints = 483.2105, armor = 493.9247,},
	armor_1 = { name = "arm_generic", hitpoints = 492.3435, armor = 492.0125,},
	capacitor = { name = "cap_generic", hitpoints = 0, armor = 0, rechargeRate = 56.7245, energy = 1413.089,},
	weapon_0 = { name = "wpn_generic", hitpoints = 199.7925, armor = 192.111, rate = 0.5716904, drain = 27.27335, maxDamage = 308.5856, shieldEfficiency = 0, minDamage = 200.0856, ammo = 0, ammo_type = 0, armorEfficiency = 0,},
	weapon_1 = { name = "wpn_sienar_heatseeker_missile_s01", hitpoints = 190.3251, armor = 194.4109, rate = 2.917864, drain = 27.58492, maxDamage = 26.57997, shieldEfficiency = 0, minDamage = 26.43489, ammo = 50, ammo_type = 2, armorEfficiency = 0,},
}

ObjectTemplates:addTemplate(object_ship_tieadvanced, "object/ship/tieadvanced.iff")
