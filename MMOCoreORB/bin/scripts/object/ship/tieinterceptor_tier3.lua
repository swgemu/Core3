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


object_ship_tieinterceptor_tier3 = object_ship_shared_tieinterceptor_tier3:new {

	name = "tieinterceptor_tier3",
	slideFactor = 1.64,
	chassisHitpoints = 1200,
	chassisMass = 5000,
	reactor = { name = "rct_generic", hitpoints = 1036.202, armor = 1042.217,},
	engine = { name = "eng_novaldex_eventhorizon", hitpoints = 1054.772, armor = 1033.652, speed = 52.44162, pitch = 23.49744, roll = 29.48959, yaw = 18.68942, acceleration = 11.33925, rollRate = 53.10143, pitchRate = 47.38976, deceleration = 8.974859, yawRate = 38.92603,},
	shield_0 = { name = "shd_generic", hitpoints = 1036.349, armor = 1074.613, regen = 7.575461, front = 3577.25, back = 3581.006,},
	armor_0 = { name = "arm_generic", hitpoints = 2203.739, armor = 2251.176,},
	armor_1 = { name = "arm_generic", hitpoints = 2214.205, armor = 2235.167,},
	capacitor = { name = "cap_generic", hitpoints = 1062.701, armor = 1077.748, rechargeRate = 95.89033, energy = 4992.074,},
	weapon_0 = { name = "wpn_tieadvanced_blaster", hitpoints = 1065.938, armor = 1051.375, rate = 0.7748152, drain = 0.9803374, maxDamage = 156.1448, shieldEfficiency = 0.5462673, minDamage = 108.996, ammo = 0, ammo_type = 0, armorEfficiency = 0.5592942,},
}

ObjectTemplates:addTemplate(object_ship_tieinterceptor_tier3, "object/ship/tieinterceptor_tier3.iff")
